#pragma once

#include "Core.h"

#include "Window.h"
#include "Sloth/LayerStack.h"
#include "Sloth/Events/Event.h"
#include "Sloth/Events/ApplicationEvent.h"

#include "Sloth/Core/Timestep.h"

#include "Sloth/ImGui/ImGuiLayer.h"

namespace Sloth {

	class SLOTH_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		
		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}