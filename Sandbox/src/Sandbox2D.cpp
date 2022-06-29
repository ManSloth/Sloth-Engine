#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{

}

void Sandbox2D::OnAttach()
{
	SLTH_PROFILE_FUNCTION();

	m_Texture = Sloth::Texture2D::Create("assets/textures/checkerboard.png");
	m_SpriteSheet = Sloth::Texture2D::Create("assets/textures/RPG_Sprites.png");
}

void Sandbox2D::OnDetach()
{
	SLTH_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(Sloth::Timestep ts)
{
	SLTH_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Sloth::Renderer2D::ResetStats();
	{
		SLTH_PROFILE_SCOPE("Renderer Prep");
		Sloth::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Sloth::RenderCommand::Clear();
	}


	{
#if 0
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		SLTH_PROFILE_SCOPE("Renderer Draw");
		Sloth::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Sloth::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, rotation, { 0.8f, 0.2f, 0.3f, 1.0f });
		Sloth::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.80f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Sloth::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Sloth::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_Texture, 10.0f);
		Sloth::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_Texture, 20.0f);
		Sloth::Renderer2D::EndScene();

		//Sloth::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, ( y + 5.0f) / 10.0f, 0.7f };
				Sloth::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
#endif
		Sloth::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Sloth::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, m_SpriteSheet);

		Sloth::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	SLTH_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = Sloth::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Sloth::Event& e)
{
	m_CameraController.OnEvent(e);
}
