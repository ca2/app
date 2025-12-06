Texture2D hdri        : register(t0);
SamplerState samLinear : register(s0);

static const float2 inverseAtan = float2(0.1591, 0.3183);

float2 sphericalToCartesian(float3 v)
{
    float2 uv;
    uv.x = atan2(v.z, v.x);
    uv.y = asin(v.y);
    uv *= inverseAtan;
    uv += 0.5;
    return uv;
}

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 modelCoordinates : TEXCOORD0;
};

float4 main(PS_INPUT input) : SV_TARGET
{
    float3 dir = normalize(input.modelCoordinates);
    float2 uv  = sphericalToCartesian(dir);
    float u = uv.x;
    float v = uv.y;
    u = fmod(u + 0.75, 1.0);
    float3 color = hdri.Sample(samLinear, float2(1.0 - u, v)).rgb;
    return float4(color,1.0f);
}
