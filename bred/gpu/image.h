#pragma once


#include "aura/graphics/image/image.h"


namespace gpu
{


   class context;
   class texture;


   class CLASS_DECL_BRED image :
      virtual public ::image::image
   {
   public:


      ::pointer < ::gpu::texture > m_pgputexture;


      image();
      ~image() override;


      ::draw2d::graphics * get_graphics() const override;

      virtual ::gpu::texture * gpu_texture() const;
      virtual void initialize_gpu_image(
         ::gpu::context * pgpucontext,
         const ::i32_size & size);

      void destroy() override;

      void map(bool bApplyAlphaTransform = true) const override;
      void unmap() const override;


   };


} // namespace gpu
