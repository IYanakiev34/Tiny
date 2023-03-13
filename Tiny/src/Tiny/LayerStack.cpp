#include "TNpch.h"
#include "Tiny/LayerStack.h"
#include "Tiny/Layer.h"
#include "Tiny/Log.h"

namespace Tiny
{
	LayerStack::LayerStack()
		: d_insertIndex(0)
	{

	}

	LayerStack::~LayerStack()
	{
		for (auto layer : d_layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		int position = 0;
		for (auto it = d_layers.begin(); it != d_layers.end(); ++it)
		{
			if (position == d_insertIndex)
			{
				d_layers.insert(it, layer);
				break;
			}
			++position;
		}

		if (position == 0)
			d_layers.insert(d_layers.begin(), layer);

		++d_insertIndex;
	}

	void LayerStack::PushOverlay(Layer* layer)
	{
		d_layers.push_back(layer);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		if (RemoveLayer(layer))
			--d_insertIndex;
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		RemoveLayer(overlay);
	}


	bool LayerStack::RemoveLayer(Layer* layer)
	{
		auto it = std::find(d_layers.begin(), d_layers.end(), layer);
		if (it != d_layers.end())
		{
			d_layers.erase(it);
			return true;
		}

		return false;
	}
}
