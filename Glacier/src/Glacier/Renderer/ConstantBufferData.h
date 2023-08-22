#pragma once

#include "Glacier/Core/Core.h"

#include "SimpleMath.h"

namespace Glacier
{
    using DirectX::SimpleMath::Matrix;

    // �� ī�޶� ��ȯ ��� ���۴� ������ ���� ù ��° ���Կ� ���ε�.
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