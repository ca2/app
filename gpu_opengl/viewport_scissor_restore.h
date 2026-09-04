// From gpu_directx12/input_layout.h by
// camilo on 2025-06-29 08:34 <3ThomasBorregaardSørensen!!
// From gpu_directx11/input_layout.h by
// camilo on 2025-06-29 06:04 <3ThomasBorregaardSørensen!!
// From gpu_vulkan/input_layout.h by camilo on 2025-06-29 03:49 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/gpu/context.h"
#include "_gpu_opengl.h"


namespace gpu_opengl
{



   class CLASS_DECL_GPU_OPENGL viewport_scissor_restore :
      virtual public ::gpu::viewport_scissor_restore
   {
   public:

      GLint m_viewport[4]{};
      GLint m_scissor[4]{};
      GLboolean m_bScissorTestEnabled{ GL_FALSE };


      viewport_scissor_restore()
      {

         glGetIntegerv(GL_VIEWPORT, m_viewport);

         glGetIntegerv(GL_SCISSOR_BOX, m_scissor);

         m_bScissorTestEnabled =
            glIsEnabled(GL_SCISSOR_TEST);

      }


      ~viewport_scissor_restore()
      {

         glViewport(
            m_viewport[0],
            m_viewport[1],
            m_viewport[2],
            m_viewport[3]);

         glScissor(
            m_scissor[0],
            m_scissor[1],
            m_scissor[2],
            m_scissor[3]);

         if (m_bScissorTestEnabled)
         {

            glEnable(GL_SCISSOR_TEST);

         }
         else
         {

            glDisable(GL_SCISSOR_TEST);

         }

      }


      viewport_scissor_restore(
         const viewport_scissor_restore &) = delete;

      viewport_scissor_restore &
         operator = (
            const viewport_scissor_restore &) = delete;

   };


} // namespace gpu_opengl



