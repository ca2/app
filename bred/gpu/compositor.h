// Created by camilo on 2025-06-18 19:51 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{



   class CLASS_DECL_BRED compositor :
      virtual public ::particle
   {
   public:
      //bool m_bInLayer = false;

      ::pointer <::gpu::context> m_pgpucontextCompositor2;


      compositor();
      ~compositor() override;


      virtual void set_gpu_context(::gpu::context * pgpucontextCompositor);

      virtual void on_set_gpu_context();


      virtual void defer_yield_gpu_context(const ::int_rectangle & rectanglePlacement);


      ::gpu::context* gpu_context();

      virtual void start_gpu_layer(::gpu::frame* pgpuframe);
      virtual ::gpu::frame * end_gpu_layer();


      virtual void gpu_layer_on_after_begin_render();
      virtual void gpu_layer_on_before_end_render();


      virtual void just_after_new_frame();

      virtual void on_start_layer();
      virtual void on_end_layer();

   };

}
