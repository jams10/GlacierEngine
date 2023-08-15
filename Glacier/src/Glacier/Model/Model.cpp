#include "pch.h"
#include "Model.h"

namespace Glacier
{
	Model::Model(std::shared_ptr<Mesh>& mesh)
		:m_Mesh(mesh), m_Material(nullptr)
	{
	}

	Model::~Model()
	{

	}

	void Model::Submit() const
	{
		// 각종 파이프라인 state, shader, input layout을 먼저 bind하고 vertex, index 버퍼 바인딩.
		if (m_Material != nullptr)
		{
			m_Material->Bind();
		}
		m_Mesh->Bind(m_Material->m_PipelineState->GetVertexLayout()->GetVertexStride());
	}
	
	void Model::SetMaterial(std::shared_ptr<Material> material)
	{
		m_Material = material;
	}
}