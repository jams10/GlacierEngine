#pragma once

#include "Glacier/Core.h"
#include "Layer.h"

#include <vector>

namespace Glacier
{
	class GLACIER_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;                 // ���̾���� ������ ����.
		unsigned int m_LayerInsertIndex = 0;          // Layer�� ������ ��ġ�� ����Ű�� index.
	};
	// ���̾� ����� �տ������� ���������� �Ⱦ� ���鼭 �������̳� ������Ʈ �۾��� �����ϰ�, ���������� �ݴ�� �Ⱦ�鼭 �̺�Ʈ�� ó����.
	// �ֻ��� ���̾ ��ư�� �ִٸ� �ش� ��ư�� ���� �̺�Ʈ�� ���� ó���ؾ� �ϱ� ����.
}