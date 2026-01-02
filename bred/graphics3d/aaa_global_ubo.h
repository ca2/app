#pragma once

#include "bred/gpu/properties.h"
#include "bred/gpu/_types.h"
#include "bred/graphics3d/point_light.h"

namespace graphics3d
{

   struct global_ubo
   {
      inline static const int MAX_LIGHTS{10};
      floating_matrix4 projection{1.f};
      floating_matrix4 view{1.f};
      floating_sequence4 ambientLightColor{1.f, 1.f, 1.f, .02f};
      floating_sequence4 viewPos;
      gpu::point_light pointLights[MAX_LIGHTS];
      int numLights;
   };

} // namespace graphics3d


DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::graphics3d::global_ubo);
