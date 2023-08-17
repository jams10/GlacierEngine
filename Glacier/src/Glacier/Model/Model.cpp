#include "pch.h"
#include "Model.h"

#include "Glacier/Model/Mesh.h"
#include "Glacier/Renderer/Shading/Material.h"
#include "Glacier/Components/TransformComponent.h"

namespace Glacier
{
	Model::Model(std::shared_ptr<Mesh>& mesh)
		:m_Mesh(mesh), m_Material(nullptr)
	{
		m_Transform.reset(Glacier::TransformComponent::Create());
	}

	Model::~Model()
	{

	}

	void Model::Submit() const
	{
		// ���� ���������� state, shader, input layout�� ���� bind�ϰ� vertex, index ���� ���ε�.
		if (m_Material != nullptr)
		{
			m_Material->Bind();
		}
		m_Mesh->Bind(m_Material->m_PipelineState->GetVertexLayout()->GetVertexStride());
		m_Transform->Bind();
	}
	
	void Model::SetMaterial(std::shared_ptr<Material> material)
	{
		m_Material = material;
	}
}