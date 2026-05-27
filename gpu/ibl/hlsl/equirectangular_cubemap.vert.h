// This file was automatically generated from a command line like:
// application_build_helper --inline-text "equirectangular_cubemap.vert"
#pragma once


const ::i8 g_psz_equirectangular_cubemap_vert[] = R"vert_text(struct VS_INPUT
{
    f323 position : POSITION;
    f323 normal   : NORMAL;
    f322 uv       : TEXCOORD0;
};

struct VS_OUTPUT
{
    f324 position : SV_POSITION;
    f323 modelCoordinates : TEXCOORD0;
};

// register(b1) for "push constants"
cbuffer MatrixBuffer : register(b1)
{
    f324x4 mvp;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;

    //f324 worldPos = mul(f324(input.position,1), model);
    //f324 viewPos  = mul(worldPos, view);
    //output.position = mul(viewPos, projection);
    output.position = mul(f324(input.position,1), mvp);

    output.modelCoordinates = input.position; // for HDRI lookup
    return output;
}
)vert_text";




