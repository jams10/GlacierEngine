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

		// TODO : 오브젝트 간 자식, 부모 관계가 형성되면 트랜스폼 컴포넌트의 경우에 부모의 트랜스폼이 자식 오브젝트에 적용되어야 함.
		std::wstring Name;
		uint32 ID;

	private:
		std::shared_ptr<Object> m_Parent;
		std::set<std::shared_ptr<Object>> m_Children;

	};
}