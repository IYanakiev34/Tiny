#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/Event.h"

namespace Tiny
{
	class TINY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& ev);
	private:
		std::unique_ptr<Window> d_window;
		bool b_isRunning;
	};

	// TO BE DEFINED IN CLIENT
	Application* CreateApplication();

}


