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


      texture();
      ~texture() override;


      void initialize_gpu_texture(::gpu::renderer* prenderer, const ::int_size & size);

      void blend(::gpu::texture* ptexture, const ::int_rectangle& rectangleTarget) override;


   };


} // namespace gpu_opengl



