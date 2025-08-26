//
// From V0idsEmbrace.graphics3d by camilo on 2025-08-21 18:32 <3ThomasBorregaardSorensen
//
#pragma once


#include "bred/gpu/properties.h"
#include "bred/graphics3d/scene_object.h"


DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::point_light)
DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::gpu::point_light_push_constants)


namespace graphics3d
{


   class point_light :
      virtual public scene_object
   {
   public:

      float m_fLightIntensity = 1.0f;

   };


} // namespace graphics3d



