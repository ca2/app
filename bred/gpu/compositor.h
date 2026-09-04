// Created by camilo on 2025-06-18 19:51 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{


   class CLASS_DECL_BRED compositor :
      virtual public ::particle
   {
   public:
      

      ::pointer <::gpu::context> m_pgpucontextOwned;

#ifdef WINDOWS

      bool m_bDraw2dNeedsD3D11onD12 = false;

#endif


      compositor();
      ~compositor() override;

      virtual ::gpu::texture_site * current_target_texture(::gpu::layer* pgpulayer);


      virtual void set_gpu_context(::gpu::context * pgpucontextCompositor);

      virtual void on_set_gpu_context();


      virtual void on_gpu_context_placement_change(
         const ::i32_point & pointInput,
         const ::i32_point & pointOutput,
         const ::i32_size & size,
         ::acme::windowing::window *pacmewindowingwindow,
         ::draw2d::graphics * pdraw2dgraphics);

      virtual bool renders_layer_externally(::gpu::layer * pgpulayer);
      virtual void on_start_layer_before_begin_render(::gpu::layer *pgpulayer);
      //virtual void on_gpu_context_placement_change(const ::i32_rectangle & rectanglePlacement);


      virtual ::gpu::context* gpu_context();

      //virtual void start_gpu_layer(::gpu::layer* pgpulayer);
      //virtual ::gpu::frame * end_gpu_layer(::gpu::layer* pgpulayer);


      //virtual void gpu_layer_on_after_begin_render();
      //virtual void gpu_layer_on_before_end_render();


      //virtual void just_after_new_frame();

      

      virtual void start_layer(bool bFirstLayer = false, ::user::interaction * puserinteraction = nullptr);
      virtual void end_layer(bool bClosingLayer = false);

      virtual void on_start_layer(::gpu::layer * pgpulayer);
      virtual void on_end_layer(::gpu::layer * pgpulayer);


   };

}
