
cbuffer CameraTransformConstant : register(b0)
{
    matrix view;
    matrix proj;
    matrix viewProj;
}

cbuffer WorldTransformConstant : register(b1)
{
    matrix world;
}

struct VertexShaderInput
{
    float3 posModel : POSITION; //모델 좌표계의 위치 position
    float3 color : COLOR0;
};

struct PixelShaderInput
{
    float4 pos : SV_POSITION;
    float3 color : COLOR0;
};

PixelShaderInput main(VertexShaderInput input)
{
    PixelShaderInput output;
    float4 pos = float4(input.posModel, 1.0f);  // 트랜스폼 행렬을 적용하기 위해 아핀 공간으로 바꿔줌.
    pos = mul(pos, world);
    pos = mul(pos, view);
    pos = mul(pos, proj);
    output.pos = pos;
    output.color = input.color;
    
    return output;
}