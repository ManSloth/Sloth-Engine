#include <Sloth.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "../vendor/imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public Sloth::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Sloth::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
		};

		Sloth::Ref<Sloth::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Sloth::VertexBuffer::Create(vertices, sizeof(vertices)));

		Sloth::BufferLayout layout = {
			{ Sloth::ShaderDataType::Float3, "a_Position" },
			{ Sloth::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Sloth::Ref<Sloth::IndexBuffer> indexBuffer;
		indexBuffer.reset(Sloth::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Sloth::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Sloth::Ref<Sloth::VertexBuffer> squareVB;
		squareVB.reset(Sloth::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Sloth::ShaderDataType::Float3, "a_Position" },
			{ Sloth::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Sloth::Ref<Sloth::IndexBuffer> squareIB;
		squareIB.reset(Sloth::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
			
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(Sloth::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;
			
			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";

		m_FlatColorShader.reset(Sloth::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

		std::string textureShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;
			
			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_TextureShader.reset(Sloth::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

		m_Texture = Sloth::Texture2D::Create("assets/textures/Grass2.png");
		m_AlphaTexture = Sloth::Texture2D::Create("assets/textures/Grass.png");

		std::dynamic_pointer_cast<Sloth::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Sloth::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Sloth::Timestep ts) override
	{

		if (Sloth::Input::IsKeyPressed(SLTH_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;

		else if (Sloth::Input::IsKeyPressed(SLTH_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Sloth::Input::IsKeyPressed(SLTH_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		else if (Sloth::Input::IsKeyPressed(SLTH_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Sloth::Input::IsKeyPressed(SLTH_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Sloth::Input::IsKeyPressed(SLTH_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;


		Sloth::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Sloth::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Sloth::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Sloth::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Sloth::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);


		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Sloth::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();
		Sloth::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));


		scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.25, 1));
		m_AlphaTexture->Bind();
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				if (y % 2 == 0)
				{
					glm::vec3 pos((x * 0.24f) +0.12f, (y * 0.06f), 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
					Sloth::Renderer::Submit(m_TextureShader, m_SquareVA, transform);
				}
				else
				{
					glm::vec3 pos(x * 0.24f, y * 0.06f, 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
					Sloth::Renderer::Submit(m_TextureShader, m_SquareVA, transform);
				}
			}
		}

		//m_AlphaTexture->Bind();
		//Sloth::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		// Triangle
		// Sloth::Renderer::Submit(m_Shader, m_VertexArray);

		Sloth::Renderer::EndScene();

		//Renderer::Flush();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Sloth::Event& event) override
	{

	}

private:
	Sloth::Ref<Sloth::Shader> m_Shader;
	Sloth::Ref<Sloth::VertexArray> m_VertexArray;

	Sloth::Ref<Sloth::Shader> m_FlatColorShader, m_TextureShader;
	Sloth::Ref<Sloth::VertexArray> m_SquareVA;

	Sloth::Ref<Sloth::Texture2D> m_Texture;
	Sloth::Ref<Sloth::Texture2D> m_AlphaTexture;

	Sloth::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 2.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Sloth::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Sloth::Application* Sloth::CreateApplication()
{
	return new Sandbox();

}