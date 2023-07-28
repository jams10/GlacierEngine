#pragma once

#include "Glacier/Core.h"
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
		virtual void OnUpdate() {} // ���̾ ������Ʈ �Ǿ�� �� �� ���ø����̼ǿ� ���� ȣ��.
		virtual void OnImGuiRender() {} // ImGui�� ����� UI�� �׸��� ���.

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName; // ���̾��� �̸�
	};
}