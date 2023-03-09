#include <Tiny.h>

class Sandbox : public Tiny::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox() override
	{

	}
};


Tiny::Application* Tiny::CreateApplication()
{
	return new Sandbox();
}