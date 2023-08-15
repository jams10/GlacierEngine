#include "pch.h"
#include "DirectX11Material.h"

namespace Glacier
{
	DirectX11Material::DirectX11Material()
	{

	}

	DirectX11Material::~DirectX11Material()
	{

	}

	void DirectX11Material::Bind() const
	{
		m_PipelineState->Bind(); 
		uint8 len = static_cast<uint8>(m_Textures.size());
		for (uint8 i = 0; i < len; ++i)
		{
			m_Textures[i]->Bind(i);
		}
	}

	void DirectX11Material::Unbind() const
	{
		m_PipelineState->UnBind();
	}

	void DirectX11Material::AddTexture(std::shared_ptr<Texture> texture)
	{
		m_Textures.emplace_back(texture);
	}

	void DirectX11Material::SetPipelineState(std::shared_ptr<RenderPipelineState> pipelineState)
	{
		m_PipelineState = pipelineState;
	}

	void DirectX11Material::OnImGuiRender() const
	{
	}
}