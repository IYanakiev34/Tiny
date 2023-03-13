#pragma once


#include "Tiny/Core.h"

namespace Tiny
{
	class Layer;


	class TINY_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return d_layers.begin(); }
		std::vector<Layer*>::iterator end() { return d_layers.end(); }

	private:
		bool RemoveLayer(Layer* layer);
	private:
		std::vector<Layer*> d_layers;
		size_t d_insertIndex;
	};
}


