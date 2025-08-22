//
// From V0idsEmbrace.graphics3d by camilo on 2025-08-21 18:32 <3ThomasBorregaardSorensen
//
#pragma once
#include "bred/graphics3d/scene_object.h"


namespace graphics3d
{


   class point_light :
   virtual public scene_object
   {
   public:

      inline static const int MAX_LIGHTS = 10;

      float m_fLightIntensity = 1.0f;

   };


} // namespace graphics3d



