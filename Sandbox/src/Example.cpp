#include <Galaxy.h>

#include "ImGui/imgui.h"

class ExampleLayer : public Galaxy::Layer
{
public:
	ExampleLayer() : Layer("Example") 
	{

	}

	void OnUpdate() override 
	{
		if (Galaxy::Input::IsKeyPressed(GX_KEY_TAB))
			GX_TRACE("Tab key is pressed!");
	}

	void OnEvent(Galaxy::Event& event) override
	{
		if (event.GetEventType() == Galaxy::EventType::KeyPressed)
		{
			Galaxy::KeyPressedEvent& e = (Galaxy::KeyPressedEvent&)event;
			GX_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

	void OnImGuiRender() override
	{

	}
};

class Sandbox : public Galaxy::Application
{
public:
	Sandbox() 
	{ 
		PushLayer(new ExampleLayer());
	}

	~Sandbox(){}
};

Galaxy::Application* Galaxy::CreateApplication()
{
	return new Sandbox();
}