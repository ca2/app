// ca2 reserves b0 for the global UBO and binds shared push properties at b1.
cbuffer QuadConstants : register(b1)
{
    // left, top, right, bottom (DirectX/ca2 top-left texture coordinates)
    float4 quad;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float2 uv       : TEXCOORD0;
};

VS_OUTPUT main(uint vertexId : SV_VertexID)
{
    static const float2 positions[3] =
    {
        float2(-1.0f, -1.0f),
        float2(-1.0f,  3.0f),
        float2( 3.0f, -1.0f)
    };

    // The fullscreen triangle starts at clip-space bottom-left, while
    // DirectX texture V=0 is the top row. Reverse V at this backend boundary.
    static const float2 textureCoordinates[3] =
    {
        float2(0.0f,  1.0f),
        float2(0.0f, -1.0f),
        float2(2.0f,  1.0f)
    };

    VS_OUTPUT output;

    output.position =
        float4(positions[vertexId], 0.0f, 1.0f);

    float2 uvFull = textureCoordinates[vertexId];

    // HLSL lerp() is equivalent to GLSL mix().
    output.uv = float2(
        lerp(quad.x, quad.z, uvFull.x),
        lerp(quad.y, quad.w, uvFull.y));

    return output;
}
