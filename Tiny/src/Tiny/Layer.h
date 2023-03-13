#pragma once

#include "Tiny/Core.h"
#include <string>


namespace Tiny
{
	class Event;
	class TINY_API Layer
	{

	public:
		Layer(std::string const& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {} // Logic when attaching the layer
		virtual void OnDetach() {} // Logic when detaching the layer
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& ev) {}// Handle event

		inline std::string GetDebugName() { return d_debugName; }

	protected:
		std::string d_debugName;
	};
}


