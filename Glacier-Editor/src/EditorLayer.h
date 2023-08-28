#pragma once

#include "Glacier.h"

#include "EditorWindows/SceneHierarchyWindow.h"

namespace Glacier
{
	class EditorLayer : public Glacier::Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(float dt) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Glacier::Event& e) override;

		void SceneHierarchy();
		void SceneViewPort();
		void SceneProperty();

	private:
		std::shared_ptr<Glacier::ModelComponent> m_Model;
		std::shared_ptr<Glacier::Texture2D> m_TextureResource;
		std::shared_ptr<Glacier::Material> m_Material;

		std::shared_ptr<Glacier::Object> m_Object;

		std::shared_ptr<Glacier::Scene> m_Scene;

		std::unique_ptr<Glacier::CameraController> m_SceneCameraController;

		SceneHierarchyWindow m_SceneHierarchy;
	};
}
