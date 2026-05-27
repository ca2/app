// From github:/tristancalderbank/OpenGL-PBR-Renderer/FullscreenQuad.h by
// camilo on 2025-09-27 02:00 <3ThomasBorregaardSorensen!!
#pragma once
//
//
//#include "gpu/full_screen_quad.h"
//
//
//namespace gpu_opengl
//{
//
//
//   //const ::u32 QUAD_NUM_TRIANGLES = 6;
//
//   /**
//    * A unit square that covers the whole screen.
//    *
//    * Includes texture coordinates.
//    */
//   class full_screen_quad:
//   virtual public ::gpu::full_screen_quad
//   {
//   public:
//      
//      
//      //::u32 m_uVAO;
//      //::u32 m_uVBO;
//
//
//
//      full_screen_quad();
//      ~full_screen_quad() override;
//
//
//      void initialize_full_screen_quad(::gpu::context * pgpucontext) override;
//
//      
//      virtual void bind(::gpu::command_buffer *pcommandbuffer);
//      virtual void draw(::gpu::command_buffer *pcommandbuffer);
//      virtual void unbind(::gpu::command_buffer *pcommandbuffer);
//
//
//   // private:
//   //
//   //    std::vector<::f32> mVertices = {
//   //       // positions   // textureCoordinates
//   //       -1.0f,  1.0f,  0.0f, 1.0f,
//   //       -1.0f, -1.0f,  0.0f, 0.0f,
//   //        1.0f, -1.0f,  1.0f, 0.0f,
//   //
//   //       -1.0f,  1.0f,  0.0f, 1.0f,
//   //        1.0f, -1.0f,  1.0f, 0.0f,
//   //        1.0f,  1.0f,  1.0f, 1.0f
//   //     };
//   };
//
//
//} // namespace gpu_opengl
//
//
