#pragma once

#include "Glacier.h"

namespace Glacier
{
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
	};
}
