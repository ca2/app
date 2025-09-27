// From github:/tristancalderbank/OpenGL-PBR-Renderer/FullscreenQuad.h by
// camilo on 2025-09-26 22:46 <3ThomasBorregaardSorensen!!
#pragma once

///#include <vector>

#include "shader.h"


namespace gpu
{


   const unsigned int QUAD_NUM_TRIANGLES = 6;

   /**
    * A unit square that covers the whole screen.
    *
    * Includes texture coordinates.
    */
   class FullscreenQuad :
      virtual public ::graphics3d::renderable
   {
   public:


      float_array_base m_vertexa;


      FullscreenQuad();


      void Draw();


      //private:
      void loadVertexData();


      //private:
      //  unsigned int mVAO;
      //unsigned int mVBO;

   };


} // namespace gpu
