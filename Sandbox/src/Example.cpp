#include <Galaxy.h>

class ExampleLayer : public Galaxy::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override 
	{
		GX_INFO("ExampleLayer::Update");
	}

	void OnEvent(Galaxy::Event& event) override
	{
		GX_TRACE("{0}", event);
	}
};

class Sandbox : public Galaxy::Application
{
public:
	Sandbox() 
	{ 
		PushLayer(new ExampleLayer());
		PushOverlay(new Galaxy::ImGuiLayer());
	}

	~Sandbox(){}
};

Galaxy::Application* Galaxy::CreateApplication()
{
	return new Sandbox();
}