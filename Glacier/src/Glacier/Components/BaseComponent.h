#pragma once

#include "Glacier/Core/Core.h"

namespace Glacier
{
	class GLACIER_API BaseComponent
	{
	public:
		virtual ~BaseComponent() {}

		virtual void Bind() = 0;
	};
}