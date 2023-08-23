#include "pch.h"
#include "ModelComponent.h"

#include "Glacier/Mesh/Mesh.h"
#include "Glacier/Renderer/Shading/Material.h"
#include "Glacier/Components/TransformComponent.h"

namespace Glacier
{
	ModelComponent::ModelComponent(std::shared_ptr<Mesh>& mesh)
		:m_Mesh(mesh), m_Material(nullptr)
	{
	}

	ModelComponent::~ModelComponent()
	{
		m_Material = nullptr;
		m_Mesh = nullptr;
	}

	void ModelComponent::Bind()
	{
		// ���� ���������� state, shader, input layout�� ���� bind�ϰ� vertex, index ���� ���ε�.
		if (m_Material != nullptr)
		{
			m_Material->Bind();
			m_Mesh->Bind(m_Material->m_PipelineState->GetVertexLayout()->GetVertexStride());
		}
	}
	
	void ModelComponent::SetMaterial(std::shared_ptr<Material> material)
	{
		m_Material = material;
	}
}