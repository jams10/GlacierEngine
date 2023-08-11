#pragma once

#include "Glacier/Core/Core.h"

#include "Glacier/Types.h"
#include <memory>
#include <string>

namespace Glacier
{
	class GLACIER_API Texture
	{
	public:
		virtual ~Texture(){}

		virtual uint32 GetWidth() = 0;
		virtual uint32 GetHeight() = 0;

		virtual void Bind(uint32 slot) const = 0;
	};

	class GLACIER_API Texture2D : public Texture
	{
	public:
		static std::shared_ptr<Texture2D> Create(const std::wstring& filePath);
	};
}