#pragma once

#include "Core.h"

namespace Tiny
{
	class TINY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// TO BE DEFINED IN CLIENT
	Application* CreateApplication();
}


