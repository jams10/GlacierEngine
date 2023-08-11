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
	std::shared_ptr<Glacier::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Glacier::IndexBuffer> m_IndexBuffer;
	std::shared_ptr<Glacier::ShaderBuffer> m_WorldTransformBuffer;
	std::shared_ptr<Glacier::ShaderBuffer> m_CameraTransformBuffer;
	std::shared_ptr<Glacier::Texture2D> m_TextureResource;

	Glacier::CameraController m_CameraController;

	Glacier::WorldTransformConstant m_WorldTransformConstant;
	Glacier::CameraTransformConstant m_CameraTransformConstant;
};