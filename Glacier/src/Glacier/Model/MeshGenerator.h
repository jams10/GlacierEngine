#pragma once

#include "Glacier/Core/Core.h"
#include "Mesh.h"

#include <memory>

namespace Glacier
{
	using std::shared_ptr;

	class MeshGenerator
	{
	public:
		static shared_ptr<Mesh> MakeTriangle();
		static shared_ptr<Mesh> MakeSqaure();
		static shared_ptr<Mesh> MakeCube();
	};
}