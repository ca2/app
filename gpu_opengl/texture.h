// Created by camilo on 2025-06-08 18:11 < 3ThomasBorregaardSørensen!!
#pragma once


#include "bred/gpu/texture.h"
//#include <d3d11.h>
//#include <d2d1_1.h>
#include "_gpu_opengl.h"

namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL texture :
      virtual public ::gpu::texture
   {
   public:
      

      GLuint            m_gluTextureID;
      GLuint            m_gluDepthStencilRBO;
      GLuint            m_gluFbo;
      GLenum            m_gluType;


      texture();
      ~texture() override;


      void initialize_hdr_texture_on_memory(::gpu::renderer *prenderer, const ::block & block) override;
      void initialize_with_image_data(::gpu::renderer *pgpurenderer, const ::int_rectangle &rectangleTarget,
                                      int numChannels, bool bSrgb, const void *pdata, enum_type etype) override;
      // void initialize_image_texture(::gpu::renderer* prenderer,
      //    const ::int_rectangle & rectangleTarget, bool bWithDepth,
      //    const ::pointer_array < ::image::image > *pimagea, enum_type etype) override;

      //void blend(::gpu::texture* ptexture, const ::int_rectangle& rectangleTarget) override;


      void create_texture(const ::pointer_array < ::image::image > *pimagea) override;


      void create_render_target() override;


      void create_depth_resources() override;


      void bind_render_target() override;


      void set_pixels(const ::int_rectangle& rectangle, const void* data) override;


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

      void set_cube_face(int iFace) override;

      void generate_mipmap() override;

   };


} // namespace gpu_opengl



