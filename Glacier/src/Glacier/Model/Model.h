#pragma once

#include "Glacier/Core/Core.h"

#include <memory>

namespace Glacier
{
	class Mesh;
	class Material;
	class TransformComponent;

	class GLACIER_API Model
	{
	public:
		Model(std::shared_ptr<Mesh>& mesh);
		~Model();

		void Submit() const;
		void SetMaterial(std::shared_ptr<Material> material);
		TransformComponent* GetTransform() { return m_Transform.get(); }

	private:
		std::shared_ptr<Mesh> m_Mesh;
		std::shared_ptr<Material> m_Material;
		std::unique_ptr<TransformComponent> m_Transform;
	};
}