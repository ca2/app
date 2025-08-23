//
// From V0idsEmbrace.graphics3d by camilo on 2025-08-21 18:32 <3ThomasBorregaardSorensen
//
#pragma once


#include "bred/gpu/properties.h"
#include "bred/graphics3d/scene_object.h"



BEGIN_GPU_PROPERTIES(::gpu::point_light)
GPU_PROPERTY("position", ::gpu::e_type_seq4)
GPU_PROPERTY("color", ::gpu::e_type_seq4)
END_GPU_PROPERTIES()


namespace graphics3d
{


   class point_light :
      virtual public scene_object
   {
   public:

      float m_fLightIntensity = 1.0f;

   };


} // namespace graphics3d



