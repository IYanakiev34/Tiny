#pragma once
#include "Tiny/Layer.h"
#include "Tiny/Core.h"

namespace Tiny
{
	//Forward declare
	class Event;
	class MouseButtonReleasedEvent;
	class MouseButtonPressedEvent;
	class MouseMovedEvent;
	class KeyPressedEvent;
	class KeyReleasedEvent;
	class MouseScrolledEvent;
	class WindowResizeEvent;
	class KeyTypedEvent;

	class TINY_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() override;
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& ev);

		inline std::string GetDebugName() { return d_debugName; }

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& ev);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& ev);
		bool OnMouseMovedEvent(MouseMovedEvent& ev);
		bool OnMouseScrollEvent(MouseScrolledEvent& ev);
		bool OnKeyPressedEvent(KeyPressedEvent& ev);
		bool OnKeyReleasedEvent(KeyReleasedEvent& ev);
		bool OnWindowResizedEvent(WindowResizeEvent& ev);
		bool OnKeyTypedEvent(KeyTypedEvent& ev);
	private:
		float d_time;
	};
}

