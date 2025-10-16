// diffuseirradiance_ps.hlsl
// Converted from OpenGL GLSL (version 330 core) to HLSL for DirectX 11

TextureCube environmentCubemap : register(t0);
SamplerState samplerLinear : register(s0);

static const float PI = 3.14159265359f;
static const float3 up = float3(0.0f, 0.0f, 1.0f);

struct PSInput
{
    float4 position : SV_POSITION;
    float3 modelCoordinates : TEXCOORD0;
};

float4 main(PSInput input) : SV_TARGET
{
    float3 normal = normalize(input.modelCoordinates);
    float3 tangent = normalize(cross(up, normal));
    float3 bitangent = normalize(cross(normal, tangent));

    float3 irradiance = 0.0f.xxx;

    float numSamples = 0.0f;
    float delta = 0.025f;

    // integrate over hemisphere
    for (float phi = 0.0f; phi < 2.0f * PI; phi += delta)
    {
        for (float theta = 0.0f; theta < (PI * 0.5f); theta += delta)
        {
            float3 sampleDirectionTangent = float3(
                sin(theta) * cos(phi),
                sin(theta) * sin(phi),
                cos(theta)
            );

            float3 sampleDirectionWorld =
                sampleDirectionTangent.x * tangent +
                sampleDirectionTangent.y * bitangent +
                sampleDirectionTangent.z * normal;

            float3 hdrColor = environmentCubemap.Sample(samplerLinear, sampleDirectionWorld).rgb;

            // ACES filmic tonemap
            float a = 2.51f;
            float b = 0.03f;
            float c = 2.43f;
            float d = 0.59f;
            float e = 0.14f;
            float3 mapped = saturate((hdrColor * (a * hdrColor + b)) / (hdrColor * (c * hdrColor + d) + e));

            // gamma correction (linear -> sRGB)
            float3 sampleValue = pow(mapped, 1.0f / 2.2f);

            // compensate for solid angle
            sampleValue *= sin(theta);

            // Lambertian cosine weighting
            sampleValue *= cos(theta);

            irradiance += sampleValue;
            numSamples += 1.0f;
        }
    }

    irradiance = PI * irradiance * (1.0f / numSamples);
    return float4(irradiance, 1.0f);
}
