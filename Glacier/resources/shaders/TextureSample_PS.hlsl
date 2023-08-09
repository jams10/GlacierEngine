
struct PixelShaderInput
{
    float4 pos : SV_POSITION;
    float2 texcoord : TEXCOORD0;
};

Texture2D g_texture0 : register(t0);
SamplerState g_sampler : register(s0);

float4 main(PixelShaderInput input) : SV_TARGET
{
    return g_texture0.Sample(g_sampler, input.texcoord);
}