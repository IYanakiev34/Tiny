#pragma once

#include "Tiny/Core.h"
#include "Tiny/Window.h"
#include "Tiny/LayerStack.h"
#include "Tiny/Events/Event.h"
#include "Tiny/Events/ApplicationEvent.h"


namespace Tiny
{
	class Layer;

	class TINY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void OnEvent(Event& ev);

		inline static Application* GetApplication() { return s_applicationInstance; }
		inline Window& GetWindow() { return *d_window; }
	private:
		bool OnWindowClosed(WindowClosedEvent& ev);

	private:
		static Application* s_applicationInstance;

		std::unique_ptr<Window> d_window;
		LayerStack d_layerStack;
		bool b_isRunning;
	};

	// TO BE DEFINED IN CLIENT
	Application* CreateApplication();

}


