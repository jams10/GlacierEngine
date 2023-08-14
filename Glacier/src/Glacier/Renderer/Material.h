#pragma once

#include "Glacier/Core/Core.h"

namespace Glacier
{
	class GLACIER_API Material
	{
	public:
		virtual ~Material() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Material* Create();
	};
}