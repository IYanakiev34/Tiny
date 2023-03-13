#include "TNpch.h"
#include "Tiny/Application.h"
#include "Tiny/Core.h"
#include "Tiny/Layer.h"
#include "Tiny/Log.h"


#include <glad/glad.h>


namespace Tiny
{
	Application* Application::s_applicationInstance;

	Application::Application()
		: b_isRunning(true)
	{
		TN_CORE_ASSERT(!s_applicationInstance,"Application is already initialized");
		s_applicationInstance = this;

		d_window = std::unique_ptr<Window>(Window::Create());
		d_window->SetEventCallback(TN_BIND_EVENT_FN(Application::OnEvent));

	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& ev)
	{
		EventDispatcher dispatcher(ev);
		dispatcher.Dispatch<WindowClosedEvent>(TN_BIND_EVENT_FN(Application::OnWindowClosed));

		for (auto it = d_layerStack.begin(); it != d_layerStack.end(); ++it)
		{
			if (ev.b_Handled)
				break;
			(*it)->OnEvent(ev);
		}

	}

	void Application::Run()
	{
		int i = 0;
	
		while (b_isRunning)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (auto it = d_layerStack.begin(); it != d_layerStack.end(); ++it)
				(*it)->OnUpdate();

			d_window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		d_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		d_layerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowClosed(WindowClosedEvent& ev)
	{
		b_isRunning = false;
		return true;
	}
}