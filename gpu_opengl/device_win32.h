// from context_win32 by
// camilo on 2025-05-30 03:36 <3ThomasBorregaardSorensen!!
#pragma once


#include "gpu_opengl/device.h"


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL device_win32 :
      virtual public ::gpu_opengl::device
   {
   public:


      bool                                m_bMesa;
      HGLRC                               m_hrc;
      HDC                                 m_hdc;
      HWND                                m_hwnd;
      HDC                                 m_hdcGraphics;
      ::pointer < ::windowing::window >   m_pwindow;
      bool                                m_bAddSwapChainSupport;
      ::int_rectangle                     m_rectangleWin32;
      


      device_win32();
      ~device_win32() override;

      void initialize_gpu_device(::gpu::approach* papproach, ::windowing::window* pwindow, const ::int_rectangle & rectanglePlacement, bool bAddSwapChainSupport) override;

      virtual void destroy_device();

      virtual ::pointer < ::gpu::context > allocate_context(::particle* pparticle);

      //virtual ::pointer < ::gpu::context > start_gpu_output_context(::particle* pparticle, const ::gpu::enum_output& eoutput, const ::int_rectangle& rectanglePlacement);

      //virtual ::pointer < ::gpu::context > start_cpu_buffer_context(::particle* pparticle, const ::image32_callback& callbackImage32CpuBuffer, const ::int_rectangle& rectanglePlacement);

      //virtual ::pointer < ::gpu::context > start_swap_chain_context(::particle* pparticle, ::windowing::window* pwindow);


      //void on_create_context(const ::gpu::start_context_t& startcontext) override;

      virtual void _defer_create_offscreen_window(const ::int_size& size);

      //void defer_create_window_context(::windowing::window* pwindow) override;
      //void _defer_create_window_context(::windowing::window* pwindow) override;
      //virtual void _create_window_context(::windowing::window* pwindow);

      virtual void _create_device(const ::int_size & size);
      //void _create_offscreen_buffer(const ::int_size& size) override;
      //void resize_offscreen_buffer(const ::int_size& size) override;
      //void destroy_offscreen_buffer() override;

      //bool make_current(::gpu::context* pgpucontext) override;

      //void release_current(::gpu::context* pgpucontext) override;

      void on_make_current() override;
      void on_release_current() override;


      void _swap_buffers() override;

      bool is_mesa() override;

      //void render();

      string get_shader_version_text() override;

      //void _translate_shader(string_array& straFragment) override;

      //void swap_buffers() override;


   };


} // namespace gpu_opengl



