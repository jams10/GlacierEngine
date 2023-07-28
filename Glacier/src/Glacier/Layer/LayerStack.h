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
		std::vector<Layer*> m_Layers;                 // 레이어들을 가지는 벡터.
		unsigned int m_LayerInsertIndex = 0;          // Layer를 삽입할 위치를 가리키는 index.
	};
	// 레이어 목록을 앞에서부터 순차적으로 훑어 가면서 렌더링이나 업데이트 작업을 수행하고, 끝에서부터 반대로 훑어가면서 이벤트를 처리함.
	// 최상위 레이어에 버튼이 있다면 해당 버튼에 대한 이벤트를 먼저 처리해야 하기 때문.
}