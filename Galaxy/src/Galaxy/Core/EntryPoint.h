#pragma once

#ifdef GX_PLATFORM_WINDOWS

extern Galaxy::Application* Galaxy::CreateApplication();

int main(int argc, char** argv)
{ 
	Galaxy::Log::Init();

	GX_PROFILE_BEGIN_SESSION("Startup", "GalaxyProfile-Startup.json");
	auto app = Galaxy::CreateApplication();
	GX_PROFILE_END_SESSION();

	GX_PROFILE_BEGIN_SESSION("Runtime", "GalaxyProfile-Runtime.json");
	app->Run();
	GX_PROFILE_END_SESSION();

	GX_PROFILE_BEGIN_SESSION("Shutdown", "GalaxyProfile-Shutdown.json");
	delete app;
	GX_PROFILE_END_SESSION();
	return 0;
}

#endif