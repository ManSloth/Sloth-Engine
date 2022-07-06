#pragma once

#include "Sloth/Core/Layer.h"

#include "Sloth/Events/ApplicationEvent.h"
#include "Sloth/Events/KeyEvent.h"
#include "Sloth/Events/MouseEvent.h"


namespace Sloth {

	class SLOTH_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
		void BlockEvents(bool block) { m_BlockEvents = block; }
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}