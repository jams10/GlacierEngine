#include "pch.h"
#include "Scene.h"

#include "Glacier/Renderer/Renderer.h"
#include "Glacier/Components/ModelComponent.h"
#include "Glacier/Renderer/Shading/Material.h"
#include "Glacier/Renderer/Shading/Texture.h"
#include "Glacier/Mesh/MeshGenerator.h"
#include "Glacier/Object/Object.h"

namespace Glacier
{
	Scene::Scene()
	{
		m_SceneRoot = std::make_shared<Object>(L"Scene Root", 0);
	}

	Scene::~Scene()
	{
		m_SceneRoot = nullptr;
	}

	void Scene::Update(float dt)
	{
	}

	void Scene::Render()
	{
		for (auto it = m_Objects.begin(); it != m_Objects.end(); ++it)
		{
			// 씬에 추가된 오브젝트들을 렌더링.
			Renderer::Submit(it->second);
		}
	}

	void Scene::AddObject(std::shared_ptr<Object>& parent)
	{
		// 컴포넌트의 경우 따로 메뉴를 추가.
		// 오브젝트 추가할 때 씬 루트에 추가할 지, 특정 게임 오브젝트 아래 추가할 지 결정해야 함.

		m_ObjectIDCounter++;

		// 따로 컴포넌트 추가 메뉴를 통해 추가.
		//// 모델 생성.
		//std::shared_ptr<ModelComponent> model = std::make_shared<ModelComponent>(MeshGenerator::MakeCube(Vector3::Zero));

		//// 텍스쳐 자원 생성.
		//std::shared_ptr<Texture2D> textureResource = Glacier::Texture2D::Create(L"../Resources/Texture/rabbit.png");

		//// Material 생성.
		//std::shared_ptr<Material> materal{ Material::Create() };
		//materal->AddTexture(textureResource);
		//materal->SetPipelineState(TexureSamplingPipelineState);

		//model->SetMaterial(materal);
		std::wostringstream ws;
		ws << L"Object" << m_ObjectIDCounter;
		std::wstring name = ws.str();

		std::shared_ptr<Object> objectToAdd = std::make_shared<Object>(name, m_ObjectIDCounter);
		objectToAdd->m_Parent = parent;           // 새로 생성할 오브젝트의 부모 오브젝트를 인자로 들어온 오브젝트로 설정.
		parent->m_Children.insert(objectToAdd);   // 인자로 들어온 오브젝트의 자식 오브젝트는 새로 추가하는 오브젝트가 됨.

		auto element = std::pair<uint32, std::shared_ptr<Object>>(m_ObjectIDCounter, objectToAdd);
		m_Objects.emplace(element);

	}

	void Scene::RemoveObject(const uint32& objectID)
	{
		// 삭제할 오브젝트의 자식들을 재귀적으로 제거
		for (shared_ptr<Object> child : m_Objects[objectID]->m_Children)
		{
			RemoveObjectRecursively(child);
		}

		// 삭제할 오브젝트의 자식 오브젝트들을 저장하고 있던 set을 날려줌. ref count가 감소하면서 모든 자식 오브젝트들은 해제됨.
		m_Objects[objectID]->m_Children.clear();
		// 삭제할 오브젝트의 부모 오브젝트가 더 이상 삭제할 오브젝트를 가리키지 않도록 set에서 지워줌.
		m_Objects[objectID]->m_Parent->m_Children.erase(m_Objects[objectID]);
		// Scene에서 삭제할 오브젝트를 set에 담아 주었는데, 이제 set에서도 제거해줌.
		m_Objects.erase(objectID);
	}

	void Scene::RemoveObjectRecursively(std::shared_ptr<Object>& objectToRemove)
	{
		// 현재 오브젝트의 자식들을 재귀적으로 제거
		for (shared_ptr<Object> child : objectToRemove->m_Children) 
		{
			RemoveObjectRecursively(child);
		}

		// 오브젝트가 가리키던 부모를 더 이상 가리키지 않도록 함. ref count 감소.
		if (objectToRemove->m_Parent) 
		{
			objectToRemove->m_Parent = nullptr;
		}

		// Scene이 들고 있는 set에서 오브젝트를 제거. ref count 감소.
		m_Objects.erase(objectToRemove->ID);
	}

}