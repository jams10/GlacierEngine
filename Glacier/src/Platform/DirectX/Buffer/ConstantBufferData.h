#pragma once

#include "Glacier/Core/Core.h"

#include "SimpleMath.h"

namespace Glacier
{
    using DirectX::SimpleMath::Matrix;

    // 모델 transform 버퍼는 무조건 제일 첫 번째 슬롯에 바인딩.
    const uint8 WorldTransformSlot = 0;
    const uint8 CameraTransformSlot = 1;

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