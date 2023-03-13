#include "TNpch.h"
#include "ImGuiLayer.h"

#include <imgui.h>


//////////////// TEMPORARY /////////////////////
#include <GLFW/glfw3.h>						 //
#include <glad/glad.h>					    //
/////////////////////////////////////////////

#include "Tiny/Application.h"
#include "Tiny/Core.h"
#include "Tiny/Events/Event.h"
#include "Tiny/Events/ApplicationEvent.h"
#include "Tiny/Events/KeyEvent.h"
#include "Tiny/Events/MouseEvent.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

namespace Tiny
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer"),
		  d_time(0.f)
	{
	}
	ImGuiLayer::~ImGuiLayer()
	{
	}
	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TEMP KEY MAP: Should use Tiny keycodes
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410 core");


	}
	void ImGuiLayer::OnDetach()
	{
	}
	void ImGuiLayer::OnUpdate()
	{
		// Set display size
		Application* app = Application::GetApplication();
		Window& appWindow = app->GetWindow();

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(appWindow.GetWidth(), appWindow.GetHeight());

		// Set delta time
		float deltaTime = (float)glfwGetTime();
		io.DeltaTime = d_time > 0.f ? (deltaTime - d_time) : (1.f / 60.f);
		d_time = deltaTime;

		// New frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();


		// Show demo window
		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		// Render the window
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	

	void ImGuiLayer::OnEvent(Event& ev) 
	{
		EventDispatcher dispatcher(ev);

		dispatcher.Dispatch<MouseButtonPressedEvent>(TN_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(TN_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(TN_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(TN_BIND_EVENT_FN(ImGuiLayer::OnMouseScrollEvent));
		dispatcher.Dispatch<KeyPressedEvent>(TN_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(TN_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(TN_BIND_EVENT_FN(ImGuiLayer::OnWindowResizedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(TN_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& ev)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[ev.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& ev)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[ev.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& ev)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(ev.GetX(), ev.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrollEvent(MouseScrolledEvent& ev)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += ev.GetXOffset();
		io.MouseWheel += ev.GetYOffset();


		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& ev)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[ev.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& ev)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[ev.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnWindowResizedEvent(WindowResizeEvent& ev)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(ev.GetWidth(), ev.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.f, 1.f);

		// Probably move it from here
		glViewport(0.f, 0.f, ev.GetWidth(), ev.GetHeight());

		return false;
	}
	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& ev)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keyCode = ev.GetKeyCode();


		if (keyCode > 0 && keyCode < 0x10000)
			io.AddInputCharacter((unsigned short)keyCode);

		return false;
	}
}