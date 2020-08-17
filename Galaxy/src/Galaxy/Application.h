#pragma once

#include "Core.h"

namespace Galaxy
{
	class GALAXY_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();
	};

	//Defined by client
	Application* CreateApplication();
}



