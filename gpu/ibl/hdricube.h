// From github:/tristancalderbank/OpenGL-PBR-Renderer/HDRICube.h by
// camilo on 2025-09-26 19:54 <3ThomasBorregaardSorensen!!
#pragma once

// #include <vector>
// #include <string>
// #include <iostream>
//
// //#include "stb_image/stb_image.h"
//
// #include "gpu/cube.h"
// #include "gpu/hdrtexture.h"
// #include "bred/gpu/shader.h"
//

namespace gpu
{


   namespace ibl
   {

      /**
       * A unit cube model textured with an equirectangular HDR image.
       */
      class HDRICube
         :
         virtual public ::particle
      {
      public:


         ::pointer<::gpu::cube> m_pcube;
         ::pointer < ::gpu::HDRTexture >  m_phdrtexture;


         HDRICube();


         ~HDRICube() override;


         virtual void Draw(Shader &shader);


         virtual void initialize_HDRICube(const ::string &hdriPath);

      };


   } // namespace ibl


} // namespace gpu
