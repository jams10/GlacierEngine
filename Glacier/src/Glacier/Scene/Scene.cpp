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
			// ���� �߰��� ������Ʈ���� ������.
			Renderer::Submit(it->second);
		}
	}

	void Scene::AddObject(std::shared_ptr<Object>& parent)
	{
		// ������Ʈ�� ��� ���� �޴��� �߰�.
		// ������Ʈ �߰��� �� �� ��Ʈ�� �߰��� ��, Ư�� ���� ������Ʈ �Ʒ� �߰��� �� �����ؾ� ��.

		m_ObjectIDCounter++;

		// ���� ������Ʈ �߰� �޴��� ���� �߰�.
		//// �� ����.
		//std::shared_ptr<ModelComponent> model = std::make_shared<ModelComponent>(MeshGenerator::MakeCube(Vector3::Zero));

		//// �ؽ��� �ڿ� ����.
		//std::shared_ptr<Texture2D> textureResource = Glacier::Texture2D::Create(L"../Resources/Texture/rabbit.png");

		//// Material ����.
		//std::shared_ptr<Material> materal{ Material::Create() };
		//materal->AddTexture(textureResource);
		//materal->SetPipelineState(TexureSamplingPipelineState);

		//model->SetMaterial(materal);
		std::wostringstream ws;
		ws << L"Object" << m_ObjectIDCounter;
		std::wstring name = ws.str();

		std::shared_ptr<Object> objectToAdd = std::make_shared<Object>(name, m_ObjectIDCounter);
		objectToAdd->m_Parent = parent;           // ���� ������ ������Ʈ�� �θ� ������Ʈ�� ���ڷ� ���� ������Ʈ�� ����.
		parent->m_Children.insert(objectToAdd);   // ���ڷ� ���� ������Ʈ�� �ڽ� ������Ʈ�� ���� �߰��ϴ� ������Ʈ�� ��.

		auto element = std::pair<uint32, std::shared_ptr<Object>>(m_ObjectIDCounter, objectToAdd);
		m_Objects.emplace(element);

	}

	void Scene::RemoveObject(const uint32& objectID)
	{
		// ������ ������Ʈ�� �ڽĵ��� ��������� ����
		for (shared_ptr<Object> child : m_Objects[objectID]->m_Children)
		{
			RemoveObjectRecursively(child);
		}

		// ������ ������Ʈ�� �ڽ� ������Ʈ���� �����ϰ� �ִ� set�� ������. ref count�� �����ϸ鼭 ��� �ڽ� ������Ʈ���� ������.
		m_Objects[objectID]->m_Children.clear();
		// ������ ������Ʈ�� �θ� ������Ʈ�� �� �̻� ������ ������Ʈ�� ����Ű�� �ʵ��� set���� ������.
		m_Objects[objectID]->m_Parent->m_Children.erase(m_Objects[objectID]);
		// Scene���� ������ ������Ʈ�� set�� ��� �־��µ�, ���� set������ ��������.
		m_Objects.erase(objectID);
	}

	void Scene::RemoveObjectRecursively(std::shared_ptr<Object>& objectToRemove)
	{
		// ���� ������Ʈ�� �ڽĵ��� ��������� ����
		for (shared_ptr<Object> child : objectToRemove->m_Children) 
		{
			RemoveObjectRecursively(child);
		}

		// ������Ʈ�� ����Ű�� �θ� �� �̻� ����Ű�� �ʵ��� ��. ref count ����.
		if (objectToRemove->m_Parent) 
		{
			objectToRemove->m_Parent = nullptr;
		}

		// Scene�� ��� �ִ� set���� ������Ʈ�� ����. ref count ����.
		m_Objects.erase(objectToRemove->ID);
	}

}