// Shared brush evaluation for GPU shape fills. Keep coordinates in draw2d user space.
#pragma once
#include <string>

namespace gpu::brush_fill_source
{
inline constexpr char vertex_glsl[] = R"shader(
layout(location = 0) in vec2 inputPosition;
layout(location = 1) in vec2 inputLocalPosition;
#ifdef GPU_BRUSH_VULKAN
layout(location = 0) out vec2 brushPosition;
#else
out vec2 brushPosition;
#endif
void main()
{
   gl_Position = vec4(inputPosition, 0.0, 1.0);
   brushPosition = inputLocalPosition;
}
)shader";

inline constexpr char fragment_glsl[] = R"shader(
#ifdef GPU_BRUSH_VULKAN
layout(location = 0) in vec2 brushPosition;
layout(location = 0) out vec4 fragmentColor;
layout(push_constant) uniform BrushFillConstants
{
   vec4 brushColor0;
   vec4 brushColor1;
   vec4 brushData0;
   vec4 brushData1;
   vec4 fillShape;
   vec4 brushParameters;
   vec4 textureInformation;
};
#ifdef GPU_BRUSH_PATTERN
layout(set = 0, binding = 0) uniform sampler2D uTexture;
#endif
#else
in vec2 brushPosition;
out vec4 fragmentColor;
uniform vec4 brushColor0;
uniform vec4 brushColor1;
uniform vec4 brushData0;
uniform vec4 brushData1;
uniform vec4 fillShape;
uniform vec4 brushParameters;
uniform vec4 textureInformation;
#ifdef GPU_BRUSH_PATTERN
uniform sampler2D uTexture;
#endif
#endif
#ifdef GPU_BRUSH_VULKAN
#define GPU_BRUSH_SAMPLE(uv) textureLod(uTexture, uv, 0.0)
#else
// draw2d coordinates start at the top; OpenGL stores its texture rows bottom first.
#define GPU_BRUSH_SAMPLE(uv) textureLod(uTexture, vec2((uv).x, 1.0 - (uv).y), 0.0)
#endif
)shader";

inline constexpr char vertex_hlsl[] = R"shader(
struct VertexInput { float2 position : POSITION; float2 localPosition : TEXCOORD0; };
struct PixelInput { float4 position : SV_Position; float2 brushPosition : TEXCOORD0; };
PixelInput main(VertexInput input)
{
   PixelInput output;
   output.position = float4(input.position, 0.0, 1.0);
   output.brushPosition = input.localPosition;
   return output;
}
)shader";

inline constexpr char fragment_hlsl[] = R"shader(
cbuffer BrushFillConstants : register(b1)
{
   float4 brushColor0;
   float4 brushColor1;
   float4 brushData0;
   float4 brushData1;
   float4 fillShape;
   float4 brushParameters;
   float4 textureInformation;
};
struct PixelInput { float4 position : SV_Position; float2 brushPosition : TEXCOORD0; };
#ifdef GPU_BRUSH_PATTERN
Texture2D uTexture : register(t0);
SamplerState uSampler : register(s0);
#endif
#define vec2 float2
#define vec4 float4
#define mix lerp
#define fract frac
#define dFdx ddx
#define dFdy ddy
#define GPU_BRUSH_SAMPLE(uv) uTexture.SampleLevel(uSampler, uv, 0.0)
)shader";

inline constexpr char fragment_common[] = R"shader(
#ifdef GPU_BRUSH_PATTERN
vec4 patternTexel(vec2 index)
{
   // Wrap inside the logical image, including negative coordinates. Sampling
   // texel centers explicitly avoids bleeding into an atlas or padded backing.
   vec2 size = brushData1.zw;
   vec2 wrapped = index - floor(index / size) * size;
   return GPU_BRUSH_SAMPLE((brushData1.xy + wrapped + vec2(0.5, 0.5)) * textureInformation.xy);
}
vec4 patternColor(vec2 p)
{
   vec2 pixel = p / brushData0.xy * brushData1.zw - vec2(0.5, 0.5);
   vec2 base = floor(pixel);
   vec2 weight = fract(pixel);
   return mix(mix(patternTexel(base), patternTexel(base + vec2(1.0, 0.0)), weight.x),
              mix(patternTexel(base + vec2(0.0, 1.0)), patternTexel(base + vec2(1.0, 1.0)), weight.x), weight.y);
}
#endif
vec4 brushFillColor(vec2 p)
{
#ifdef GPU_BRUSH_PATTERN
   vec4 color = patternColor(p);
#else
   float t = 0.0;
   if (brushParameters.x < 0.5)
      t = 0.0;
   else if (brushParameters.x < 1.5)
   {
      vec2 direction = brushData0.zw - brushData0.xy;
      float denominator = dot(direction, direction);
      if (denominator > 0.0)
         t = dot(p - brushData0.xy, direction) / denominator;
   }
   else if (brushParameters.x < 2.5)
   {
      // draw2d radial brushes express two radii, not a diameter.
      t = length((p - brushData0.xy) / max(abs(brushData0.zw), vec2(0.000001, 0.000001)));
   }
   else
   {
      // Rounded-box gradient: point/size describe its box; radius describes
      // the corner and the transition from the inner to the outer color.
      float radius = max(brushParameters.z, 0.000001);
      vec2 halfSize = abs(brushData0.zw) * 0.5;
      vec2 q = abs(p - (brushData0.xy + halfSize)) - halfSize + vec2(radius, radius);
      float distance = length(max(q, vec2(0.0, 0.0))) + min(max(q.x, q.y), 0.0) - radius;
      t = (distance + radius) / (2.0 * radius);
   }
   vec4 color = mix(brushColor0, brushColor1, clamp(t, 0.0, 1.0));
#endif
   if (brushParameters.y > 0.5)
   {
      vec2 local = (p - fillShape.xy) / fillShape.zw;
      float distance = length(local) - 1.0;
      float pixelWidth = max(length(vec2(dFdx(distance), dFdy(distance))), 0.000001);
      float coverage = clamp(0.5 - distance / pixelWidth, 0.0, 1.0);
      if (coverage <= 0.0)
         discard;
      color *= coverage;
   }
   return color;
}
)shader";

inline std::string source(bool hlsl, bool fragment, bool pattern, bool vulkan = false)
{
   std::string result;
   if (vulkan) result = "#version 450\n#define GPU_BRUSH_VULKAN\n";
   else if (!hlsl) result = "#version 330 core\n";
   if (pattern) result += "#define GPU_BRUSH_PATTERN\n";
   if (!fragment) return result + (hlsl ? vertex_hlsl : vertex_glsl);
   result += hlsl ? fragment_hlsl : fragment_glsl;
   result += fragment_common;
   result += hlsl ? "\nfloat4 main(PixelInput input) : SV_Target { return brushFillColor(input.brushPosition); }\n"
                  : "\nvoid main() { fragmentColor = brushFillColor(brushPosition); }\n";
   return result;
}
} // namespace gpu::brush_fill_source
