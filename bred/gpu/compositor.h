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

#ifdef WINDOWS
      bool m_bDraw2dNeedsD3D11onD12 = false;
#endif


      compositor();
      ~compositor() override;

      //virtual ::gpu::frame* gpu_frame();
      //virtual void set_gpu_frame(::gpu::frame*);
      virtual ::gpu::texture* current_target_texture(::gpu::frame* pgpuframe);


      virtual void set_gpu_context(::gpu::context * pgpucontextCompositor);

      virtual void on_set_gpu_context();


      virtual void on_gpu_context_placement_change(const ::int_rectangle& rectanglePlacement, ::acme::windowing::window *pacmewindowingwindow);


      //virtual void on_gpu_context_placement_change(const ::int_rectangle & rectanglePlacement);


      ::gpu::context* gpu_context();

      virtual void start_gpu_layer(::gpu::frame* pgpuframe);
      virtual ::gpu::frame * end_gpu_layer(::gpu::frame* pgpuframe);


      virtual void gpu_layer_on_after_begin_render();
      virtual void gpu_layer_on_before_end_render();


      virtual void just_after_new_frame();

      
      virtual void on_start_layer(::gpu::layer * pgpulayer);
      virtual void on_end_layer(::gpu::layer* pgpulayer);


   };

}
