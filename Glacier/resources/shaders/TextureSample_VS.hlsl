
cbuffer WorldTransformConstant : register(b0)
{
    matrix world;
}

cbuffer CameraTransformConstant : register(b1)
{
    matrix view;
    matrix proj;
    matrix viewProj;
}

struct VertexShaderInput
{
    float3 posModel : POSITION; //모델 좌표계의 위치 position
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
};

struct PixelShaderInput
{
    float4 pos : SV_POSITION;
    float2 texcoord : TEXCOORD0;
};

PixelShaderInput main(VertexShaderInput input)
{
    PixelShaderInput output;
    float4 pos = float4(input.posModel, 1.0f); // 트랜스폼 행렬을 적용하기 위해 아핀 공간으로 바꿔줌.
    pos = mul(pos, world);
    pos = mul(pos, view);
    pos = mul(pos, proj);
    output.pos = pos;
    output.texcoord = input.texcoord;
    
    return output;
}