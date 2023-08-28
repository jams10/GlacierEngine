#pragma once

#include "Glacier/Core/Core.h"
#include "Glacier/Types.h"

#include <set>
#include <memory>
#include <string>

namespace Glacier
{
	class ModelComponent;
	class TransformComponent;

	class GLACIER_API Object
	{
		friend class Scene;
	public:
		Object(const std::wstring& name, const uint32& id);
		~Object();

		void Submit();

		std::shared_ptr<ModelComponent> ModelComp;
		std::unique_ptr<TransformComponent> TransformComp;

		const std::set<std::shared_ptr<Object>>& GetChildren() const { return m_Children; }

		// TODO : ������Ʈ �� �ڽ�, �θ� ���谡 �����Ǹ� Ʈ������ ������Ʈ�� ��쿡 �θ��� Ʈ�������� �ڽ� ������Ʈ�� ����Ǿ�� ��.
		std::wstring Name;
		uint32 ID;

	private:
		std::shared_ptr<Object> m_Parent;
		std::set<std::shared_ptr<Object>> m_Children;

	};
}