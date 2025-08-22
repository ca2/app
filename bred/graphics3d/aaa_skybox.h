//
// From V0idsEmbrace.graphics3d by camilo on 2025-08-21 18:21 <3ThomasBorregaardSorensen!!
//

#pragma once
#include "bred/graphics3d/scene_object.h"


namespace graphics3d
{


   class skybox :
      virtual public scene_object
   {
   public:


      ::string          m_strCubemapTextureName;
      //long long m_llId;
      ///bool m_bIsSkybox = false;

   };

} // graphics3d
