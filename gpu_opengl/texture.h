// Created by camilo on 2025-06-08 18:11 < 3ThomasBorregaardSørensen!!
#pragma once


#include "bred/gpu/texture.h"
//#include <d3d11.h>
//#include <d2d1_1.h>
#include "_gpu_opengl.h"
#include "gpu_opengl/context_handle.h"


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL texture :
      virtual public ::gpu::texture,
      virtual public ::gpu_opengl::context_handle < GLuint, ::gpu_opengl::e_handle_fbo >
   {
   public:

      
      using base_context_handle = ::gpu_opengl::context_handle<GLuint, ::gpu_opengl::e_handle_fbo>;
      

      GLuint            m_gluTextureID;
      GLuint            m_gluDepthStencilRBO;
      //GLuint            m_gluFbo;
      GLenum            m_gluType;
      GLsync            m_glsyncGpuCommandsCompleteFence;


      texture();
      ~texture() override;


      void initialize_hdr_texture_on_memory(::gpu::context *pcontext, const ::block & block) override;
      void initialize_with_image_data(::gpu::context *pcontext, const ::int_rectangle &rectangleTarget,
                                      int numChannels, bool bSrgb, const void *pdata, ::gpu::enum_texture etexture) override;
      // void initialize_image_texture(::gpu::renderer* prenderer,
      //    const ::int_rectangle & rectangleTarget, bool bWithDepth,
      //    const ::pointer_array < ::image::image > *pimagea, enum_type etype) override;

      //void blend(::gpu::texture* ptexture, const ::int_rectangle& rectangleTarget) override;


      void _create_texture(const ::gpu::texture_data & texturedata = {}) override;


      //void create_render_target() override;
      
      virtual void _create_frame_buffer_object(base_context_handle::object & object);


      void create_depth_resources() override;


      void bind_render_target() override;


      void set_pixels(const ::int_rectangle& rectangle, const void* data) override;

      
      virtual GLuint frame_buffer_object();

      // // Loads a cubemap from a single KTX file
      // void texture::KtxLoadCubemapFromFile(
      //    const ::scoped_string &name,
      //    ::string filename,
      //    bool b32)
      //    // VkFormat format,
      //    // VkQueue copyQueue,
      //    // VkImageUsageFlags imageUsageFlags,
      //    // VkImageLayout imageLayout)

      virtual void KtxLoadCubemapFromFile(
         const ::scoped_string &name,
         ::string filename,
         bool b32);

            virtual void KtxLoadCubemapFrom_ktxTexture(const ::scoped_string &name, void *p_ktxTexture, bool b32);

      //void set_cube_face(int iFace, ::gpu::shader * pgpushader) override;

      void generate_mipmap(::gpu::command_buffer * pgpucommandbuffer) override;

      void set_current_mip(int level) override;


      virtual void set_cube_face(int iFace, ::gpu::shader *pgpushader);


      void defer_fence() override;
      void wait_fence() override;

      virtual void _defer_bind_to_render_target(base_context_handle::object & object);
   };


} // namespace gpu_opengl



