#pragma once

#include "Glacier/Core/Core.h"

#include "SimpleMath.h"

namespace Glacier
{
    using DirectX::SimpleMath::Matrix;

    // 모델 카메라 변환 행렬 버퍼는 무조건 제일 첫 번째 슬롯에 바인딩.
    const uint8 CameraTransformSlot = 0;
    const uint8 WorldTransformSlot = 1;

    struct WorldTransformConstant
    {
        Matrix world = Matrix::Identity;
    };

    static_assert((sizeof(WorldTransformConstant) % 16) == 0,
        "Constant Buffer size must be 16-byte aligned");

    struct CameraTransformConstant
    {
        Matrix view = Matrix::Identity;
        Matrix proj = Matrix::Identity;
        Matrix viewProj = Matrix::Identity;
    };

    static_assert((sizeof(CameraTransformConstant) % 16) == 0,
        "Constant Buffer size must be 16-byte aligned");
}