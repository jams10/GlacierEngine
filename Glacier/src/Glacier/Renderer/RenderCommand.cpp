#include "pch.h"
#include "RenderCommand.h"

#include "Platform/DirectX/DirectX11RenderAPI.h"

namespace Glacier 
{
	RenderAPI* RenderCommand::s_RenderAPI = new DirectX11RenderAPI;

}