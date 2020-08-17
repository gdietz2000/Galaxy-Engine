#include <Galaxy.h>

class Sandbox : public Galaxy::Application
{
public:
	Sandbox(){}

	~Sandbox(){}
};

Galaxy::Application* Galaxy::CreateApplication()
{
	return new Sandbox();
}