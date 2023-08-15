#pragma once

// 실제 SandBox 프로젝트의 application에서 사용할 헤더 파일들을 여기 추가해줌.
#include "Glacier/Application.h"
#include "Glacier/Log.h"
#include "Glacier/Layer/Layer.h"
#include "Glacier/Event/ApplicationEvent.h"

//--------------입력---------------
#include "Glacier/Input/Input.h"
#include "Glacier/Event/KeyboardEvent.h"
#include "Glacier/Event/MouseEvent.h"
//---------------------------------

//-------------렌더링---------------
#include "Glacier/Renderer/Renderer.h"
#include "Glacier/Renderer/RenderCommand.h"

#include "Glacier/Renderer/Buffer.h"
#include "Glacier/Renderer/Shader.h"
#include "Glacier/Renderer/Texture.h"
#include "Glacier/Renderer/RenderPipelineState.h"
#include "Glacier/Renderer/Material.h"

#include "Platform/DirectX/Buffer/ConstantBufferData.h"

#include "Glacier/Renderer/Camera.h"
#include "Glacier/Renderer/CameraController.h"
//---------------------------------

//--------------모델----------------
#include "Glacier/Model/Model.h"
#include "Glacier/Model/MeshGenerator.h"

//---------------------------------