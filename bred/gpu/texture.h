// Created by camilo on 2025-06-12 21:04 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{


   class CLASS_DECL_BRED texture :
      virtual public ::particle 
   {
   public:


      ::pointer < ::gpu::renderer > m_pgpurenderer;
      ::int_size m_size;


      texture();
      ~texture() override;

      
      virtual void initialize_gpu_texture(::gpu::renderer * pgpurenderer, const ::int_size& size);

      virtual void merge_layers(::pointer_array < ::gpu::layer >* playera);
      virtual void blend(::gpu::layer * player);
      virtual void blend(::gpu::texture * ptexture, const ::int_rectangle & rectangleTarget);

   };


} // namespace gpu



