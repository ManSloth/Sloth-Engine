#pragma once

#include "Sloth.h"

class ExampleLayer : public Sloth::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Sloth::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Sloth::Event& e) override;
private:
	Sloth::ShaderLibrary m_ShaderLibrary;
	Sloth::Ref<Sloth::Shader> m_Shader;
	Sloth::Ref<Sloth::VertexArray> m_VertexArray;

	Sloth::Ref<Sloth::Shader> m_FlatColorShader;
	Sloth::Ref<Sloth::VertexArray> m_SquareVA;

	Sloth::Ref<Sloth::Texture2D> m_Texture, m_ChernoLogoTexture;

	Sloth::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};