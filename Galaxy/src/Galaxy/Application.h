#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Galaxy
{
	class GALAXY_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//Defined by client
	Application* CreateApplication();
}



