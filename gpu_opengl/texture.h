// Created by camilo on 2025-06-08 18:11 < 3ThomasBorregaardSørensen!!
#pragma once


#include "bred/gpu/texture.h"
#include <d3d11.h>
#include <d2d1_1.h>


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


      void initialize_image_texture(::gpu::renderer* prenderer, const ::int_rectangle & rectangleTarget, bool bWithDepth, const ::pointer_array < ::image::image >& imagea, enum_type etype) override;

      //void blend(::gpu::texture* ptexture, const ::int_rectangle& rectangleTarget) override;


      void create_render_target() override;


      void create_depth_resources() override;


      void bind_render_target() override;


      void set_pixels(const ::int_rectangle& rectangle, const void* data) override;


   };


} // namespace gpu_opengl



