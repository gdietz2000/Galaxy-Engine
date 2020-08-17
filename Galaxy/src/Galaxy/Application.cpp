#include "gxpch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Galaxy
{
	Application::Application()
	{
	
	}

	Application::~Application()
	{
	
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(CategoryApplication))
			GX_ERROR(e);
		if (e.IsInCategory(CategoryInput))
			GX_TRACE(e);

		while (true);
	}
}