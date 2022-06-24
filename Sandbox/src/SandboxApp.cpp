#include <Sloth.h>
#include <Sloth/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"



class ExampleLayer : public Sloth::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280 / 720.0f, true)
	{
		m_VertexArray = Sloth::VertexArray::Create();

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

		m_SquareVA = Sloth::VertexArray::Create();

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

		m_Shader = Sloth::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

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

		m_FlatColorShader = Sloth::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Sloth::Texture2D::Create("assets/textures/Grass2.png");
		m_AlphaTexture = Sloth::Texture2D::Create("assets/textures/0.png");

		for (int i = 0; i <= 19; i++)
		{
			texture = Sloth::Texture2D::Create("assets/textures/" + std::to_string(i) + ".png");
			m_Textures.push_back(texture);
		}
		auto start = std::chrono::system_clock::now();
		int time = std::chrono::system_clock::to_time_t(start);
		srand(time);
		auto end = std::chrono::system_clock::now();
		for (int i = 0; i < 20 * 10; i++)
		{
			// rand() % (max_number + 1 - minimum_number) + minimum_number
			int randNum = rand() % (19 + 1 - 0) + 0;
			//int randNum = rand() % 36;
			map.push_back(randNum);
		}

		logTexture = Sloth::Texture2D::Create("assets/textures/Log For Test1.png");
		stumpTexture = Sloth::Texture2D::Create("assets/textures/stump.png");


		std::dynamic_pointer_cast<Sloth::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Sloth::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Sloth::Timestep ts) override
	{
		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		Sloth::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Sloth::RenderCommand::Clear();

		Sloth::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Sloth::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Sloth::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);


		// Group of blue squares
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				//Sloth::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		// big grass texture
		//m_Texture->Bind();
		//Sloth::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));


		// Small Group of grass tiles
		scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.25, 1));
		m_AlphaTexture->Bind();

		int mapIndex = 0;
		for (int y = 20; y > 0; y--)
		{
			for (int x = 0; x < 10; x++)
			{
				m_Textures.at(map.at(mapIndex))->Bind();
				if (y % 2 == 0)
				{
					glm::vec3 pos((x * 0.24f) +0.12f, (y * 0.06f), 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
					Sloth::Renderer::Submit(textureShader, m_SquareVA, transform);
				}
				else
				{
					glm::vec3 pos(x * 0.24f, y * 0.06f, 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
					Sloth::Renderer::Submit(textureShader, m_SquareVA, transform);
				}

				mapIndex++;
			}
		}

		// Log Texture
		logTexture->Bind();
		glm::vec3 pos(1.0f, 0.5f, 0.0f);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
		Sloth::Renderer::Submit(textureShader, m_SquareVA, transform);

		{stumpTexture->Bind();
		glm::vec3 pos(0.8f, 0.5f, 0.0f);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
		Sloth::Renderer::Submit(textureShader, m_SquareVA, transform); }

		//m_AlphaTexture->Bind();
		//Sloth::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		// Triangle
		//Sloth::Renderer::Submit(m_Shader, m_VertexArray);

		//Sloth::Renderer::EndScene();

		//Renderer::Flush();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Sloth::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	Sloth::ShaderLibrary m_ShaderLibrary;
	Sloth::Ref<Sloth::Shader> m_Shader;
	Sloth::Ref<Sloth::VertexArray> m_VertexArray;

	Sloth::Ref<Sloth::Shader> m_FlatColorShader;
	Sloth::Ref<Sloth::VertexArray> m_SquareVA;

	Sloth::Ref<Sloth::Texture2D> m_Texture;
	Sloth::Ref<Sloth::Texture2D> m_AlphaTexture;

	// random map textures
	Sloth::Ref<Sloth::Texture2D> texture;
	std::vector<Sloth::Ref<Sloth::Texture2D>> m_Textures;
	std::vector<int> map;
	Sloth::Ref<Sloth::Texture2D> logTexture;
	Sloth::Ref<Sloth::Texture2D> stumpTexture;

	Sloth::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Sloth::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}

};

Sloth::Application* Sloth::CreateApplication()
{
	return new Sandbox();

}