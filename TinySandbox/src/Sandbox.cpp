#include <Tiny.h>

class ExampleLayer : public Tiny::Layer
{
public:

	void OnAttach() override
	{
		TN_INFO("Example Layer has Attached");
	}

};

class Sandbox : public Tiny::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Tiny::ImGuiLayer());
	}

	~Sandbox() override
	{

	}
};


Tiny::Application* Tiny::CreateApplication()
{
	return new Sandbox();
}