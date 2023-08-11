#pragma once

#include "Glacier/Core/Core.h"
#include "Glacier/Event/Event.h"
#include <string>

namespace Glacier
{
	class GLACIER_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {} // 레이어를 추가할 때 처리할 작업.
		virtual void OnDetach() {} // 레이어를 제거할 때 처리할 작업.
		virtual void OnUpdate(float dt) {} // 레이어가 업데이트 되어야 할 때 애플리케이션에 의해 호출.
		virtual void OnImGuiRender() {} // ImGui를 사용해 UI를 그리는 경우.
		virtual void OnEvent(Event& event) {} // 레이어로 이벤트가 들어오면 처리.

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName; // 레이어의 이름
	};
}