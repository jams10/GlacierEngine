#include "pch.h"
#include "Model.h"

namespace Glacier
{
	Model::Model(std::shared_ptr<Mesh>& mesh)
		:m_Mesh(mesh)
	{
	}

	Model::~Model()
	{

	}

	void Model::Submit(const uint32& stride) const
	{
		m_Mesh->Bind(stride);
	}
}