// This file was automatically generated from a command line like:
// application_build_helper --inline-text "_001Blend.frag"
#pragma once


const char g_psz__001Blend_frag[] = R"frag_text(Texture2D uTexture : register(t0);
SamplerState uSampler : register(s0);

struct PSInput
{
    float4 position : SV_POSITION;
    float2 uv       : TEXCOORD0;
};

float4 main(PSInput input) : SV_TARGET
{
    return uTexture.Sample(uSampler, input.uv);
})frag_text";




