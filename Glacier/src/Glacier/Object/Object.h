#pragma once

#include "Glacier/Core/Core.h"

#include <memory>

namespace Glacier
{
	class ModelComponent;
	class TransformComponent;

	class GLACIER_API Object
	{
	public:
		Object(const uint32 objectID);
		~Object();

		void Submit();
		void SetName(std::wstring name);

		std::shared_ptr<ModelComponent> ModelComp;
		std::unique_ptr<TransformComponent> TransformComp;

	private:
		uint32 m_ObjectID;
		std::wstring m_ObjectName;
	};
}