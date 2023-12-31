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
#include "Glacier/Renderer/Shading/Shader.h"
#include "Glacier/Renderer/Shading/Texture.h"
#include "Glacier/Renderer/RenderPipelineState.h"
#include "Glacier/Renderer/Shading/Material.h"

#include "Glacier/Renderer/Camera/Camera.h"
#include "Glacier/Renderer/Camera/CameraController.h"
//---------------------------------

//--------------메쉬----------------
#include "Glacier/Mesh/Mesh.h"
#include "Glacier/Mesh/MeshGenerator.h"

//---------------------------------

//-------------컴포넌트-------------
#include "Glacier/Components/ModelComponent.h"
#include "Glacier/Components/TransformComponent.h"
//---------------------------------

//-------------오브젝트-------------
#include "Glacier/Object/Object.h"
//---------------------------------

//---------------씬----------------
#include "Glacier/Scene/Scene.h"
//---------------------------------

//--------------유틸----------------
#include "Glacier/Utils/StringEncode.h"
//----------------------------------
