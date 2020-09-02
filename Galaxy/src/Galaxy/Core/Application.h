#pragma once

#include "Core.h"

#include "Galaxy/Core/LayerStack.h"
#include "Galaxy/Events/Event.h"
#include "Galaxy/Events/ApplicationEvent.h"
#include "Galaxy/Events/KeyEvent.h"
#include "Galaxy/Events/MouseEvent.h"
#include "Window.h"

#include "Galaxy/Core/Timestep.h"

#include "Galaxy/ImGui/ImGuiLayer.h"

namespace Galaxy
{
	class  Application
	{
	public:
		Application(const std::string& name = "Galaxy App");
		virtual ~Application();

		virtual void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		void Close();

		static inline Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0;
		static Application* s_Instance;
	};

	//Defined by client
	Application* CreateApplication();
}



