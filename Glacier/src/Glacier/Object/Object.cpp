#include "pch.h"
#include "Object.h"

#include "Glacier/Components/ModelComponent.h"
#include "Glacier/Components/TransformComponent.h"

namespace Glacier
{
	Object::Object(const uint32 objectID)
	{
		TransformComp = std::make_unique<TransformComponent>();
		m_ObjectID = objectID;
		std::wostringstream ws;
		ws << L"Object" << objectID;
		m_ObjectName = ws.str();
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

	void Object::SetName(std::wstring name)
	{
		m_ObjectName = name;
	}
}