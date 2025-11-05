// Created by camilo on 2025-07-01 14:27 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{


   class CLASS_DECL_BRED pixmap :
      virtual public ::particle
   {
   public:


      ::int_rectangle      m_rectangle;
      ::gpu::texture *     m_pgputexture;


      pixmap();
      ~pixmap() override;


      virtual ::int_size size();


      virtual void initialize_gpu_pixmap(::gpu::texture * pgputexture, const ::int_rectangle& rectangle);
      virtual void on_initialize_gpu_pixmap();

      virtual void set_pixels(const void* data);

      virtual void bind_texture(::gpu::shader * pgpushader);
      virtual void unbind_texture(::gpu::shader* pgpushader);
      //virtual void merge_layers(::pointer_array < ::gpu::layer >* playera);
      //virtual void blend(::gpu::layer* player);
      //virtual void blend(::gpu::texture* ptexture);

   };


} // namespace gpu



