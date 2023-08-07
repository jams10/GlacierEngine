#include "pch.h"
#include "RenderCommand.h"

#include "Platform/DirectX/DirectX11GraphicsAPI.h"

namespace Glacier 
{
	GraphicsAPI* RenderCommand::s_GraphicsAPI = new DirectX11GraphicsAPI;

}