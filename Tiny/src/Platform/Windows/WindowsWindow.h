#pragma once

#include "Tiny/Window.h"
#include <GLFW/glfw3.h>


namespace Tiny
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(WindowProps const &props);
		~WindowsWindow() override;


		void OnUpdate() override;

		unsigned GetWidth() const override{ return d_windowData.d_width; }
		unsigned GetHeight() const override { return d_windowData.d_height; }

		// Window Attributes
		void SetEventCallback(EventFn const& cb) override { d_windowData.d_eventCallback = cb; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	private:
		virtual void Init(WindowProps const &props);
		virtual void Shutdown();
	private:

		GLFWwindow* d_window;
		struct WindowData
		{
			std::string d_title;
			unsigned d_width;
			unsigned d_height;
			bool b_isVSync;
			EventFn d_eventCallback;
		};

		WindowData d_windowData;
	};
}