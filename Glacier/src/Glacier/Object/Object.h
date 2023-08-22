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
		Object();
		~Object();

		void Submit();

		std::shared_ptr<ModelComponent> ModelComp;
		std::unique_ptr<TransformComponent> TransformComp;
	private:

	};
}