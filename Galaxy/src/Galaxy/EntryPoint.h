#pragma once

#ifdef GX_PLATFORM_WINDOWS

extern Galaxy::Application* Galaxy::CreateApplication();

int main(int argc, char** argv)
{ 
	Galaxy::Log::Init();
	GX_CORE_INFO("Welcome to Galaxy Engine");
	GX_TRACE("Suck my ass bitch, wooooooooooo");

	auto app = Galaxy::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif