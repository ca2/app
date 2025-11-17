// From github:/tristancalderbank/OpenGL-PBR-Renderer/FullscreenQuad.h by
// camilo on 2025-09-26 22:46 <3ThomasBorregaardSorensen!!
#pragma once

///#include <vector>

#include "bred/gpu/context_object.h"
#include "bred/graphics3d/renderable.h"
#include "bred/gpu/model_data.h"
#include "bred/gpu/types.h"


namespace gpu
{



   /**
    * A unit square that covers the whole screen.
    *
    * Includes texture coordinates.
    */
   class CLASS_DECL_GPU full_screen_quad :
   virtual public ::gpu::context_object,
      virtual public ::graphics3d::renderable
   {
   public:


      const unsigned int QUAD_NUM_TRIANGLES = 6;


      ::gpu::model_data < ::gpu::position2_uv > m_modeldata;
      ::pointer<::gpu::model_buffer> m_pmodelbuffer;


      full_screen_quad();
      ~full_screen_quad() override;


      virtual void initialize_full_screen_quad(::gpu::context * pgpucontext);


      void draw(::gpu::command_buffer *pcommandbuffer) override;


      //private:
      ///virtual void loadVertexData();


      //private:
      //  unsigned int mVAO;
      //unsigned int mVBO;

   };


} // namespace gpu
