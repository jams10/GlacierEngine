
struct PixelShaderInput
{
    float4 pos : SV_POSITION;
    float3 color : COLOR0;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
    // 정점이 보간되어 들어오기 때문에 위치와 마찬가지로 색 또한 보간되어 들어옴.
    return float4(input.color, 1.0);
}