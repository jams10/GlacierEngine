#pragma once

#include "Glacier/Core/Core.h"

#include "Texture.h"
#include "Glacier/Renderer/RenderPipelineState.h"

namespace Glacier
{
	class GLACIER_API Material
	{
		friend class Model;
	public:
		virtual ~Material() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddTexture(std::shared_ptr<Texture> texture) = 0;
		virtual void SetPipelineState(std::shared_ptr<RenderPipelineState> pipelineState) = 0;

		virtual void OnImGuiRender() const = 0;

		static Material* Create();

	protected:
		std::vector<std::shared_ptr<Texture>> m_Textures;
		std::shared_ptr<RenderPipelineState> m_PipelineState;
	};
}