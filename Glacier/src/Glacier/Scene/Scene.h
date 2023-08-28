#pragma once

#include "Glacier/Core/Core.h"
#include "Glacier/Types.h"

#include <map>
#include <memory>
#include <string>

namespace Glacier
{
	class Object;

	class GLACIER_API Scene
	{
	public:
		Scene();
		~Scene();

		void Update(float dt);
		void Render();
		void AddObject(std::shared_ptr<Object>& parent);
		void RemoveObject(const uint32& objectID);

		std::shared_ptr<Object>& GetSceneRootObject() { return m_SceneRoot; }

	private:
		void RemoveObjectRecursively(std::shared_ptr<Object>& objectToRemove);

	private:
		std::shared_ptr<Object> m_SceneRoot;
		std::map<uint32, std::shared_ptr<Object>> m_Objects;
		uint32 m_ObjectIDCounter = 0;
	};
}