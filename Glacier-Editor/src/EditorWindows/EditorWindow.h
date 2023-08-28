#pragma once

#include "Glacier.h"

namespace Glacier
{
	class EditorWindow
	{
	public:
		virtual ~EditorWindow() {}

		virtual void Update(float dt) = 0;
		virtual void Render() = 0;
	};
}