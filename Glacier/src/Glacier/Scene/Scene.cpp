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
		m_ObjectCounts = 0;
	}

	Scene::~Scene()
	{
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

	void Scene::AddObject()
	{
		m_ObjectCounts++;

		// 모델 생성.
		std::shared_ptr<ModelComponent> model = std::make_shared<ModelComponent>(MeshGenerator::MakeCube(Vector3::Zero));

		// 텍스쳐 자원 생성.
		std::shared_ptr<Texture2D> textureResource = Glacier::Texture2D::Create(L"../Resources/Texture/rabbit.png");

		// Material 생성.
		std::shared_ptr<Material> materal{ Material::Create() };
		materal->AddTexture(textureResource);
		materal->SetPipelineState(TexureSamplingPipelineState);

		model->SetMaterial(materal);

		std::shared_ptr<Object> objectToAdd = std::make_shared<Object>(m_ObjectCounts);
		objectToAdd->ModelComp = model;

		auto element = std::pair<uint32, std::shared_ptr<Object>>(m_ObjectCounts, objectToAdd);
		m_Objects.emplace(element);

		selectedObjectID = m_ObjectCounts;
	}

	void Scene::RemoveObject(const uint32& objectID)
	{
		m_Objects.erase(objectID);
		m_ObjectCounts++;
	}

	std::shared_ptr<Object> Scene::GetSelectedObject()
	{
		return m_Objects[selectedObjectID];
	}
}