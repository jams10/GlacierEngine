#pragma once

#include "Glacier/Core/Core.h"
#include "Glacier/Model/Mesh.h"
#include "Glacier/Renderer/Material.h"

#include <memory>

namespace Glacier
{
	class GLACIER_API Model
	{
	public:
		Model(std::shared_ptr<Mesh>& mesh);
		~Model();

		void Submit() const;
		void SetMaterial(std::shared_ptr<Material> material);

	private:
		std::shared_ptr<Mesh> m_Mesh;
		std::shared_ptr<Material> m_Material;
	};
}