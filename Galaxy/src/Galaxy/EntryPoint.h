#pragma once
#include "Application.h"

#ifdef GX_PLATFORM_WINDOWS

extern Galaxy::Application* Galaxy::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Galaxy::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif