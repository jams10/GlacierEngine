#pragma once

#include "Glacier/Core/Core.h"

#include "VertexLayout.h"

namespace Glacier
{
	class GLACIER_API RenderPipelineState
	{
	public:
		virtual ~RenderPipelineState(){}

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual std::shared_ptr<VertexLayout> GetVertexLayout() = 0;

		static RenderPipelineState* Create();
	};

	// Pipeline States
	extern std::shared_ptr<RenderPipelineState> VertexColorPipelineState;
	extern std::shared_ptr<RenderPipelineState> VertexColorWirePipelineState;
	extern std::shared_ptr<RenderPipelineState> TexureSamplingPipelineState;
}