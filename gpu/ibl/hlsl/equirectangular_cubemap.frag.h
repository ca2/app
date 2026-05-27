// This file was automatically generated from a command line like:
// application_build_helper --inline-text "equirectangular_cubemap.frag"
#pragma once


const ::i8 g_psz_equirectangular_cubemap_frag[] = R"frag_text(Texture2D hdri        : register(t0);
SamplerState samLinear : register(s0);

static const f322 inverseAtan = f322(0.1591, 0.3183);

f322 sphericalToCartesian(f323 v)
{
    f322 uv;
    uv.x = atan2(v.z, v.x);
    uv.y = asin(v.y);
    uv *= inverseAtan;
    uv += 0.5;
    return uv;
}

struct PS_INPUT
{
    f324 position : SV_POSITION;
    f323 modelCoordinates : TEXCOORD0;
};

f324 main(PS_INPUT input) : SV_TARGET
{
    f323 dir = normalize(input.modelCoordinates);
    f322 uv  = sphericalToCartesian(dir);
    ::f32 u = uv.x;
    ::f32 v = uv.y;
    u = fmod(u + 0.75, 1.0);
    f323 color = hdri.Sample(samLinear, f322(1.0 - u, v)).rgb;
    return f324(color,1.0f);
}
)frag_text";




