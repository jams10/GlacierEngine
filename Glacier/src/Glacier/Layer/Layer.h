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

		virtual void OnAttach() {} // ���̾ �߰��� �� ó���� �۾�.
		virtual void OnDetach() {} // ���̾ ������ �� ó���� �۾�.
		virtual void OnUpdate(float dt) {} // ���̾ ������Ʈ �Ǿ�� �� �� ���ø����̼ǿ� ���� ȣ��.
		virtual void OnImGuiRender() {} // ImGui�� ����� UI�� �׸��� ���.
		virtual void OnEvent(Event& event) {} // ���̾�� �̺�Ʈ�� ������ ó��.

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName; // ���̾��� �̸�
	};
}