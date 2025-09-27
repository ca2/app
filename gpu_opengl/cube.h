// From github:/tristancalderbank/OpenGL-PBR-Renderer/Cube.h by
// camilo on 2025-09-26 23:31 <3ThomasBorregaardSorensen!!
#pragma once


#include "gpu/cube.h"


namespace gpu_opengl
{
   /**
    * A unit cube mesh with only position coordinates.
    */
   class Cube :
   virtual public ::gpu::Cube
   {
   public:
      Cube();
      ~Cube() override;


      void Draw();

   //private:
      void loadVertexData();

   //private:
      unsigned int mVAO, mVBO;

     //  std::vector<float> mVertices = {
     //     // positions
     //     -1.0f,  1.0f, -1.0f,
     //     -1.0f, -1.0f, -1.0f,
     //      1.0f, -1.0f, -1.0f,
     //      1.0f, -1.0f, -1.0f,
     //      1.0f,  1.0f, -1.0f,
     //     -1.0f,  1.0f, -1.0f,
     //
     //     -1.0f, -1.0f,  1.0f,
     //     -1.0f, -1.0f, -1.0f,
     //     -1.0f,  1.0f, -1.0f,
     //     -1.0f,  1.0f, -1.0f,
     //     -1.0f,  1.0f,  1.0f,
     //     -1.0f, -1.0f,  1.0f,
     //
     //      1.0f, -1.0f, -1.0f,
     //      1.0f, -1.0f,  1.0f,
     //      1.0f,  1.0f,  1.0f,
     //      1.0f,  1.0f,  1.0f,
     //      1.0f,  1.0f, -1.0f,
     //      1.0f, -1.0f, -1.0f,
     //
     //     -1.0f, -1.0f,  1.0f,
     //     -1.0f,  1.0f,  1.0f,
     //      1.0f,  1.0f,  1.0f,
     //      1.0f,  1.0f,  1.0f,
     //      1.0f, -1.0f,  1.0f,
     //     -1.0f, -1.0f,  1.0f,
     //
     //     -1.0f,  1.0f, -1.0f,
     //      1.0f,  1.0f, -1.0f,
     //      1.0f,  1.0f,  1.0f,
     //      1.0f,  1.0f,  1.0f,
     //     -1.0f,  1.0f,  1.0f,
     //     -1.0f,  1.0f, -1.0f,
     //
     //     -1.0f, -1.0f, -1.0f,
     //     -1.0f, -1.0f,  1.0f,
     //      1.0f, -1.0f, -1.0f,
     //      1.0f, -1.0f, -1.0f,
     //     -1.0f, -1.0f,  1.0f,
     //      1.0f, -1.0f,  1.0f
     // };
   };


} // namespace gpu_opengl



