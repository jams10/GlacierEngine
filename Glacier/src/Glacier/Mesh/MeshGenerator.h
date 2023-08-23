#pragma once

#include "Glacier/Core/Core.h"
#include "Mesh.h"
#include "SimpleMath.h"

#include <memory>

namespace Glacier
{
	using std::shared_ptr;
	using DirectX::SimpleMath::Vector3;

	class MeshGenerator
	{
	public:
		static shared_ptr<Mesh> MakeTriangle(Vector3 location);
		static shared_ptr<Mesh> MakeSqaure(Vector3 location);
		static shared_ptr<Mesh> MakeCube(Vector3 location);
	};
}