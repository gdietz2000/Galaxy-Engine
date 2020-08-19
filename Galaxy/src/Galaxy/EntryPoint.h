#pragma once

#ifdef GX_PLATFORM_WINDOWS

extern Galaxy::Application* Galaxy::CreateApplication();

int main(int argc, char** argv)
{ 
	Galaxy::Log::Init();

	auto app = Galaxy::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif