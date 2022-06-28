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

	m_Texture = Sloth::Texture2D::Create("assets/textures/Shield.png");
}

void Sandbox2D::OnDetach()
{
	SLTH_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(Sloth::Timestep ts)
{
	SLTH_PROFILE_FUNCTION();

	//Update
	m_CameraController.OnUpdate(ts);

	//Render
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	{
		SLTH_PROFILE_SCOPE("Renderer Prep");
		Sloth::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Sloth::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		SLTH_PROFILE_SCOPE("Renderer Draw");
		Sloth::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Sloth::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, rotation, { 0.8f, 0.2f, 0.3f, 1.0f });
		Sloth::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.80f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Sloth::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Sloth::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture, 10.0f);
		Sloth::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_Texture, 20.0f);
		Sloth::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	SLTH_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Sloth::Event& e)
{
	m_CameraController.OnEvent(e);
}
