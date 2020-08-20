#pragma once

#include "Core.h"

#include "Galaxy/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Window.h"

#include "Galaxy/ImGui/ImGuiLayer.h"

#include "Galaxy/Renderer/Shader.h"
#include "Galaxy/Renderer/Buffer.h"
#include "Galaxy/Renderer/VertexArray.h"

#include "Galaxy/Renderer/OrthographicCamera.h"

namespace Galaxy
{
	class GALAXY_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		static inline Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Shader> m_BlueShader;

		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexArray> m_SquareVA;

		OrthographicCamera m_Camera;

		static Application* s_Instance;
	};

	//Defined by client
	Application* CreateApplication();
}



