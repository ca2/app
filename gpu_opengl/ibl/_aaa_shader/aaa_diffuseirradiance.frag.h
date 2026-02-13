// This file was automatically generated from a command line like:
// application_build_helper --inline-text "diffuse_irradiance_map.frag"
#pragma once


const char g_psz_diffuseirradiance_frag[] = R"frag_text(#version 330 core

out vec4 FragColor;
in vec3 modelCoordinates;

uniform samplerCube environmentCubemap;

const float PI = 3.14159265359;
const vec3 up = vec3(0.0, 0.0, 1.0);

void main() {
	vec3 normal = normalize(modelCoordinates);
	vec3 tangent = normalize(cross(up, normal));
	vec3 bitangent = normalize(cross(normal, tangent));

	vec3 irradiance = vec3(0.0);

	// integrate the incoming light from the environment cubemap
	// over the hemisphere centered around our sample direction
	// this uses spherical coordinates phi/theta

	float numSamples = 0.0;
	float delta = 0.025; // radians

	for (float phi = 0.0; phi < 2.0 * PI; phi += delta) { // 360 degrees around
		for (float theta = 0.0; theta < PI / 2.0; theta += delta) { // 90 degrees up/down

			vec3 sampleDirectionTangent = vec3(
				sin(theta) * cos(phi),
				sin(theta) * sin(phi),
				cos(theta)
			);

			vec3 sampleDirectionWorld = sampleDirectionTangent.x * tangent +
			sampleDirectionTangent.y * bitangent +
			sampleDirectionTangent.z * normal;

			vec3 hdrColor = texture(environmentCubemap, sampleDirectionWorld).rgb;

    //outColor = vec4(, 1.0);
        // 1. Fetch HDR color (linear values, can be > 1.0)
    //vec3 hdrColor = texture(skybox, dir).rgb;

    // 2. Apply tonemapping
    // Reinhard operator
    //vec3 mapped = hdrColor / (hdrColor + vec3(1.0));

    // Or ACES tonemap (nicer looking, optional):
    float a = 2.51;
    float b = 0.03;
    float c = 2.43;
    float d = 0.59;
    float e = 0.14;
    vec3 mapped = clamp((hdrColor*(a*hdrColor+b)) / (hdrColor*(c*hdrColor+d)+e), 0.0, 1.0);

    // 3. Gamma correction (convert from linear → sRGB)
    vec3 sampleValue = pow(mapped, vec3(1.0/2.2));

			// compensate for the fact that angles at the base of the hemisphere
			// have bigger deltaArea
			sampleValue *= sin(theta);

			// light rays more aligned with the normal are stronger (think lambertion diffuse)
			sampleValue *= cos(theta);

			irradiance += sampleValue;
			numSamples++;
		}
	}

	irradiance = PI * irradiance * (1.0 / numSamples);
	FragColor = vec4(irradiance, 1.0);
})frag_text";




