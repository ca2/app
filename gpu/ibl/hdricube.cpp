// From github:/tristancalderbank/OpenGL-PBR-Renderer/HDRICube.cpp by
// camilo on 2025-09-26 19:54 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "hdricube.h"



namespace gpu
{


   namespace ibl
   {

      HDRICube::HDRICube()
      {


      }


      HDRICube::~HDRICube()
      {

      }


      void HDRICube::initialize_HDRICube(const ::scoped_string &hdriPath)
      {

         øconstruct_new(m_phdrtexture);

         m_pcube = std::make_unique<Cube>();

      }


      void HDRICube::Draw(Shader &shader)
      {
         shader.setInt("hdri", 0);

         // draw mesh
         glBindTexture(GL_TEXTURE_2D, hdrTexture.getId());
         cube->Draw();
      };


   } // namespace ibl


} // namespace gpu
