// From github:/tristancalderbank/OpenGL-PBR-Renderer/HDRICube.h by
// camilo on 2025-09-26 19:54 <3ThomasBorregaardSorensen!!
#pragma once

#include <vector>
#include <string>
#include <iostream>

//#include "stb_image/stb_image.h"

#include "gpu/cube.h"
#include "gpu/hdrtexture.h"
#include "bred/gpu/shader.h"
#include "gpu/ibl/hdricube.h"


namespace gpu_opengl
{


   namespace ibl
   {

      /**
       * A unit cube model textured with an equirectangular HDR image.
       */
      class HDRICube
         :
         virtual public ::gpu::ibl::HDRICube
      {
      public:


         ::pointer<cube> m_pcube;
         HDRTexture m_phdrtexture;


         HDRICube();


         ~HDRICube() override;


         void Draw(Shader &shader);


         void initialize_HDRICube(const ::string &hdriPath);

      };


   } // namespace ibl


} // namespace gpu_opengl
