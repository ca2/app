// Input from vertex shader
struct PS_INPUT {
    float4 pos             : SV_POSITION;
    float3 fragColor       : COLOR0;
    float3 fragPosWorld    : TEXCOORD1;
    float3 fragNormalWorld : TEXCOORD2;
};

// Match GLSL std140 layout (float4-aligned)
struct PointLight {
    float4 position;
    float4 color;
};

// ---------- Global UBO (set 0 binding 0) ----------
cbuffer GlobalUbo : register(b0)
{
    column_major float4x4 projection;
    column_major float4x4 view;
    column_major float4x4 invView;
    float4 ambientLightColor;
    float3 cameraPosition;
    PointLight pointLights[10];
    int numLights;
};



// Output
float4 main(PS_INPUT input) : SV_TARGET
{
    float3 diffuseLight = ambientLightColor.rgb * ambientLightColor.a;
    float3 specularLight = float3(0.0, 0.0, 0.0);
    float3 surfaceNormal = normalize(input.fragNormalWorld);

    // Extract camera position from invView matrix (row-major)
    float3 cameraPosWorld = cameraPosition;
    float3 viewDirection = normalize(cameraPosWorld - input.fragPosWorld);

    for (int i = 0; i < numLights; ++i)
    {

        PointLight light = pointLights[i];
        float3 directionToLight = light.position.xyz - input.fragPosWorld;
        float attenuation = 1.0 / dot(directionToLight, directionToLight);
        directionToLight = normalize(directionToLight);

        float cosAngIncidence = max(dot(surfaceNormal, directionToLight), 0.0f);
        float3 intensity = light.color.rgb * light.color.a * attenuation;

        diffuseLight += intensity * cosAngIncidence;

        float3 halfAngle = normalize(directionToLight + viewDirection);
        float blinnTerm = dot(surfaceNormal, halfAngle);
        blinnTerm = saturate(blinnTerm);
        blinnTerm = pow(blinnTerm, 64.0f);

        specularLight += intensity * blinnTerm;

    }

    float3 lightIntensity = diffuseLight + specularLight;

    float4 oColor = float4(lightIntensity * input.fragColor, 1.0f);
    clip(oColor.a < 0.01f ? -1.0f : 1.0f); // discard fragment if alpha < 0.01
    //oColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
    return oColor;
}
