#pragma once

#include "Glacier/Core/Core.h"

#include <map>
#include <memory>

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
		void AddObject();
		void RemoveObject(const uint32& objectID);

		std::shared_ptr<Object> GetSelectedObject();

	private:
		std::map<uint32, std::shared_ptr<Object>> m_Objects;
		uint32 m_ObjectCounts;

	public:
		uint32 selectedObjectID;
	};
}