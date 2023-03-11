#include "TNpch.h"
#include "Application.h"
#include "Core.h"
#include "Tiny/Log.h"

#include <GLFW/glfw3.h>

namespace Tiny
{
	Application::Application()
		: b_isRunning(true)
	{
		d_window = std::unique_ptr<Window>(Window::Create());
		// Make macro for this
		d_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& ev)
	{
		TN_CORE_INFO("{0}", ev);
	}

	void Application::Run()
	{
		while (b_isRunning)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			d_window->OnUpdate();
		}
	}
}