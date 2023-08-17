#pragma once

#include "Glacier/Renderer/Shading/Material.h"

#include "Platform/DirectX/Texture/DirectX11Texture2D.h"
#include "Platform/DirectX/DirectX11PipelineState.h"
#include <vector>

namespace Glacier
{
	class GLACIER_API DirectX11Material : public Material
	{
	public:
		DirectX11Material();
		~DirectX11Material();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddTexture(std::shared_ptr<Texture> texture) override;
		virtual void SetPipelineState(std::shared_ptr<RenderPipelineState> pipelineState) override;

		virtual void OnImGuiRender() const override;

	};
}