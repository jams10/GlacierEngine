#include "pch.h"
#include "LayerStack.h"

namespace Glacier
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer) // �տ��� ���� ����.
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay) // �ڿ��� ���� ����.
	{
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer) // �տ��� ���� ��.
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
			layer->OnDetach();
		}
	}

	void LayerStack::PopOverlay(Layer* overlay) // �ڿ��� ���� ��.
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			overlay->OnDetach();
		}
	}
}

