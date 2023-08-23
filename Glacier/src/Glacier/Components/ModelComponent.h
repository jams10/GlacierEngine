#pragma once

#include "Glacier/Core/Core.h"
#include "Glacier/Components/BaseComponent.h"

#include <memory>

namespace Glacier
{
	class Mesh;
	class Material;
	class TransformComponent;

	class GLACIER_API ModelComponent : public BaseComponent
	{
	public:
		ModelComponent(std::shared_ptr<Mesh>& mesh);
		~ModelComponent();

		virtual void Bind() override;
		void SetMaterial(std::shared_ptr<Material> material);

	private:
		std::shared_ptr<Mesh> m_Mesh;
		std::shared_ptr<Material> m_Material;
	};
}