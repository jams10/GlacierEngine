#pragma once

#include "Glacier.h"

class SandBox3D : public Glacier::Layer
{
public:
	SandBox3D();
	virtual ~SandBox3D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(float dt) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Glacier::Event& e) override;

private:
	std::shared_ptr<Glacier::ShaderBuffer> m_CameraTransformBuffer;

	std::shared_ptr<Glacier::Model> m_Model;
	std::shared_ptr<Glacier::Texture2D> m_TextureResource;
	std::shared_ptr<Glacier::Material> m_Material;

	Glacier::CameraController m_CameraController;

	Glacier::CameraTransformConstant m_CameraTransformConstant;
};