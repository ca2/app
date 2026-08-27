// Created by camilo on 2026-07-27 14:16 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "aura/graphics/draw2d/bitmap.h"


namespace gpu 
{


   class CLASS_DECL_BRED bitmap :
      virtual public ::draw2d::bitmap
   {
   public:


      ::pointer<::gpu::texture> m_pgputexture;


      bitmap();
      ~bitmap();


      void destroy() override;


      virtual void update_bitmap_as_backed_by_gpu_texture(::gpu::texture * pgputexture, ::draw2d::graphics * pdraw2graphics);
      virtual void _create_gpu_bitmap(const ::i32_size & size, ::draw2d::graphics * pdraw2graphics, pixmap_t * ppixmap = nullptr);
      void create_bitmap(::draw2d::graphics *pdraw2dgraphics, const ::i32_size &size, ::pixmap * ppixmapOwned) override;
      
      virtual ::gpu::texture *gpu_texture() const;
      
      virtual void initialize_gpu_bitmap(::gpu::context *pgpucontext, const ::i32_size &size,
                                        const ::gpu::texture_data &texturedata);
      virtual ::gpu::texture *get_gpu_texture();

   };

} // namespace gpu 



