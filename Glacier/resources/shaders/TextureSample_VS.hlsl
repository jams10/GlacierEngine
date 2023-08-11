
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
    float3 posModel : POSITION; //�� ��ǥ���� ��ġ position
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
    float4 pos = float4(input.posModel, 1.0f); // Ʈ������ ����� �����ϱ� ���� ���� �������� �ٲ���.
    pos = mul(pos, world);
    pos = mul(pos, view);
    pos = mul(pos, proj);
    output.pos = pos;
    output.texcoord = input.texcoord;
    
    return output;
}