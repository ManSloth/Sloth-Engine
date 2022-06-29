#pragma once

#include "Sloth.h"

class Sandbox2D : public Sloth::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Sloth::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Sloth::Event& e) override;
private:
	Sloth::OrthographicCameraController m_CameraController;

	 //Temp
	Sloth::Ref<Sloth::VertexArray> m_SquareVA;
	Sloth::Ref<Sloth::Shader> m_FlatColorShader;

	Sloth::Ref<Sloth::Texture2D> m_Texture;
	Sloth::Ref<Sloth::Texture2D> m_SpriteSheet;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};