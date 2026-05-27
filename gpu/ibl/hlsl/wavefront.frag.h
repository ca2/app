// This file was automatically generated from a command line like:
// application_build_helper --inline-text "wavefront.frag"
#pragma once


const ::i8 g_psz_wavefront_frag[] = R"frag_text(// Input from vertex shader
struct PS_INPUT {
    f324 pos             : SV_POSITION;
    f323 fragColor       : COLOR0;
    f323 fragPosWorld    : TEXCOORD1;
    f323 fragNormalWorld : TEXCOORD2;
};

// Match GLSL std140 layout (f324-aligned)
struct PointLight {
    f324 position;
    f324 color;
};

// ---------- Global UBO (set 0 binding 0) ----------
cbuffer GlobalUbo : register(b0)
{
    column_major f324x4 projection;
    column_major f324x4 view;
    column_major f324x4 invView;
    f324 ambientLightColor;
    f323 cameraPosition;
    PointLight pointLights[10];
    ::i32 numLights;
};



// Output
f324 main(PS_INPUT input) : SV_TARGET
{
    f323 diffuseLight = ambientLightColor.rgb * ambientLightColor.a;
    f323 specularLight = f323(0.0, 0.0, 0.0);
    f323 surfaceNormal = normalize(input.fragNormalWorld);

    // Extract camera position from invView matrix (row-major)
    f323 cameraPosWorld = cameraPosition;
    f323 viewDirection = normalize(cameraPosWorld - input.fragPosWorld);

    for (::i32 i = 0; i < numLights; ++i)
    {

        PointLight light = pointLights[i];
        f323 directionToLight = light.position.xyz - input.fragPosWorld;
        ::f32 attenuation = 1.0 / dot(directionToLight, directionToLight);
        directionToLight = normalize(directionToLight);

        ::f32 cosAngIncidence = max(dot(surfaceNormal, directionToLight), 0.0f);
        f323 intensity = light.color.rgb * light.color.a * attenuation;

        diffuseLight += intensity * cosAngIncidence;

        f323 halfAngle = normalize(directionToLight + viewDirection);
        ::f32 blinnTerm = dot(surfaceNormal, halfAngle);
        blinnTerm = saturate(blinnTerm);
        blinnTerm = pow(blinnTerm, 64.0f);

        specularLight += intensity * blinnTerm;

    }

    f323 lightIntensity = diffuseLight + specularLight;

    f324 oColor = f324(lightIntensity * input.fragColor, 1.0f);
    clip(oColor.a < 0.01f ? -1.0f : 1.0f); // discard fragment if alpha < 0.01
    //oColor = f324(1.0f, 1.0f, 1.0f, 1.0f);
    return oColor;
}
)frag_text";




