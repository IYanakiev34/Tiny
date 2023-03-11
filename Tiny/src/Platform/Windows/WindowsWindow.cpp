#include "TNpch.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Tiny/Log.h"


#include "Tiny/Events/ApplicationEvent.h"
#include "Tiny/Events/MouseEvent.h"
#include "Tiny/Events/KeyEvent.h"
#include <GLFW/glfw3.h>

namespace Tiny
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int code,const char *msg)
	{
		TN_CORE_ERROR("GLWF Error ({0}): {1}", code, msg);
	}

	Window* Window::Create(WindowProps const& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(WindowProps const &props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{

	}

	void WindowsWindow::Init(WindowProps const& props)
	{
		d_windowData.d_title = props.d_title;
		d_windowData.d_width = props.d_width;
		d_windowData.d_height = props.d_height;

		TN_CORE_INFO("Creating window {0} ({1},{2})", props.d_title, props.d_width, props.d_height);

		if (!s_GLFWInitialized)
		{
			// TODO shutdown on system teminate
			int success = glfwInit();
			if (!success)
			{
				TN_CORE_ASSERT(success, "Could not initialize glfw.");
				s_GLFWInitialized = true;
				glfwSetErrorCallback(GLFWErrorCallback);
			}
		}

		d_window = glfwCreateWindow(d_windowData.d_width, d_windowData.d_height, d_windowData.d_title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(d_window);
		glfwSetWindowUserPointer(d_window, &d_windowData);
		SetVSync(true);

		// Set glfw callbacks
		glfwSetWindowSizeCallback(d_window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.d_width = width;
				data.d_height = height;

				WindowResizeEvent event(width, height);
				data.d_eventCallback(event);
		});

		glfwSetWindowCloseCallback(d_window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData *)glfwGetWindowUserPointer(window);
			
			WindowClosedEvent event{};
			data.d_eventCallback(event);
		});

		glfwSetKeyCallback(d_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent keyEvent(key, 0);
				data.d_eventCallback(keyEvent);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent keyEvent(key);
				data.d_eventCallback(keyEvent);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent keyEvent(key, 1);
				data.d_eventCallback(keyEvent);
				break;
			}
			}
		});

		glfwSetMouseButtonCallback(d_window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent mouseEvent(button);
				data.d_eventCallback(mouseEvent);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent mouseEvent(button);
				data.d_eventCallback(mouseEvent);
				break;
			}
			}
		});

		glfwSetScrollCallback(d_window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent mouseScroll((float)xoffset, (float)yoffset);
			data.d_eventCallback(mouseScroll);
		});

		glfwSetCursorPosCallback(d_window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent mouseMoved((float)xpos, (float)ypos);
			data.d_eventCallback(mouseMoved);
		});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(d_window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(d_window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}

	bool WindowsWindow::IsVSync() const
	{
		return d_windowData.b_isVSync;
	}
}