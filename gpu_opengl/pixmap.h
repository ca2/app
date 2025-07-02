// From bred/gpu/pixmap.h by
//  camilo on 2025-07-01 14:36 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/gpu/pixmap.h"


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL pixmap :
      virtual public ::gpu::pixmap
   {
   public:


      GLuint       m_gluTexture;


      pixmap();
      ~pixmap() override;


      // virtual ::int_size size();


      void initialize_gpu_pixmap(::gpu::renderer* pgpurenderer, const ::int_size & size) override;


      void set_pixels(const void* data, int w, int h) override;
      //virtual void merge_layers(::pointer_array < ::gpu::layer >* playera);
      //virtual void blend(::gpu::layer* player);
      //virtual void blend(::gpu::texture* ptexture);


      void bind_texture() override;

   };


} // namespace gpu




