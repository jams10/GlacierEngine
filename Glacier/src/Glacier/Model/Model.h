#pragma once

#include "Glacier/Core/Core.h"
#include "Glacier/Model/Mesh.h"

#include <memory>

namespace Glacier
{
	class GLACIER_API Model
	{
	public:
		Model(std::shared_ptr<Mesh>& mesh);
		~Model();

		void Submit(const uint32& stride) const;

	private:
		std::shared_ptr<Mesh> m_Mesh;
	};
}