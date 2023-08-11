#pragma once

#include "Glacier/Core/Core.h"

#include "SimpleMath.h"

namespace Glacier
{
    using DirectX::SimpleMath::Matrix;

    struct WorldTransformConstant
    {
        Matrix world;
    };

    static_assert((sizeof(WorldTransformConstant) % 16) == 0,
        "Constant Buffer size must be 16-byte aligned");

    struct CameraTransformConstant
    {
        Matrix view;
        Matrix proj;
        Matrix viewProj;
    };

    static_assert((sizeof(CameraTransformConstant) % 16) == 0,
        "Constant Buffer size must be 16-byte aligned");
}