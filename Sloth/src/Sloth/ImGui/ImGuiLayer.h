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
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}