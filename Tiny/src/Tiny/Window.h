#pragma once

#include <string>
#include <functional>
#include "Tiny/Core.h"
#include "Tiny/Events/Event.h"

namespace Tiny
{
	struct WindowProps
	{
		WindowProps(std::string const &title = "Tiny Engine", unsigned width = 1024, unsigned height = 768)
			: d_title(title),
			  d_width(width),
			  d_height(height)
		{ }

		unsigned d_width;
		unsigned d_height;
		std::string d_title;
	};

	class TINY_API Window
	{
	public:
		using EventFn = std::function<void(Event& ev)>;

		virtual ~Window(){}

		virtual void OnUpdate() = 0;

		virtual unsigned GetWidth() const = 0;
		virtual unsigned GetHeight() const = 0;

		// Window Attributes
		virtual void SetEventCallback(EventFn const& cb) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(WindowProps const& props = WindowProps());
	};

}