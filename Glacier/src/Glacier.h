#pragma once

// ���� SandBox ������Ʈ�� application���� ����� ��� ���ϵ��� ���� �߰�����.
#include "Glacier/Application.h"
#include "Glacier/Log.h"
#include "Glacier/Layer/Layer.h"
#include "Glacier/Event/ApplicationEvent.h"

//--------------�Է�---------------
#include "Glacier/Input/Input.h"
#include "Glacier/Event/KeyboardEvent.h"
#include "Glacier/Event/MouseEvent.h"
//---------------------------------

//-------------������---------------
#include "Glacier/Renderer/Renderer.h"
#include "Glacier/Renderer/RenderCommand.h"

#include "Glacier/Renderer/Buffer.h"
#include "Glacier/Renderer/Shading/Shader.h"
#include "Glacier/Renderer/Shading/Texture.h"
#include "Glacier/Renderer/RenderPipelineState.h"
#include "Glacier/Renderer/Shading/Material.h"

#include "Platform/DirectX/Buffer/ConstantBufferData.h"

#include "Glacier/Renderer/Camera/Camera.h"
#include "Glacier/Renderer/Camera/CameraController.h"
//---------------------------------

//--------------��----------------
#include "Glacier/Model/Model.h"
#include "Glacier/Model/MeshGenerator.h"

//---------------------------------

//-------------������Ʈ-------------
#include "Glacier/Components/TransformComponent.h"


//---------------------------------