#include "pch.h"
#include "Object.h"

#include "Glacier/Components/ModelComponent.h"
#include "Glacier/Components/TransformComponent.h"

namespace Glacier
{
	Object::Object()
	{
		TransformComp = std::make_unique<TransformComponent>();
	}

	Object::~Object()
	{
		TransformComp = nullptr;
		ModelComp = nullptr;
	}

	void Object::Submit()
	{
		if (ModelComp != nullptr)
		{
			ModelComp->Bind();
		}
		if (TransformComp != nullptr)
		{
			TransformComp->Bind();
		}
	}
}