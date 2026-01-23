// Created by camilo on 2026-01-23 01:42 <3ThomasBorregaardSørensen!!
#pragma once


#include "gpu_opengl/device.h"




namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL device_cgl :
      virtual public ::gpu_opengl::device
   {
   public:

      
      CGLPixelFormatObj       m_cglpixelformat;
      CGLContextObj m_cglcontextShare;
//      EGLDisplay                       m_egldisplay;
//      //EGLConfig                        m_eglconfigPrimary;
//      //EGLConfig                        m_eglconfigSwapChainWindow;
//      EGLConfig                        m_eglconfigPBuffer;
//      EGLConfig                        m_eglconfigWindow;
//      //EGLConfig                        m_eglconfigPrimary;
//      EGLContext                       m_eglcontextPrimary;
//      long                             m_lX11NativeVisualId;
      // EGLSurface                       m_eglsurface;
      //itask                            m_itaskGpu;


      device_cgl();
      ~device_cgl() override;

      ::pointer < ::gpu::context > allocate_context() override;
      //void create_context() override;
      //void context::on_create_context(::gpu::device* pgpudevice, const ::gpu::enum_output& eoutput, ::windowing::window* pwindow, const ::int_size& size);
      void initialize_gpu_device_for_swap_chain(::gpu::approach* papproach, ::windowing::window* pwindow) override;
      void initialize_gpu_device_for_off_screen(::gpu::approach* papproach, const ::int_rectangle& rectanglePlacement) override;
      virtual void _destroy_cgl_device();

      //void _create_offscreen_buffer(const ::int_size& size) override;
      virtual void _defer_create_offscreen_window(const ::int_size& size);
      //void resize_offscreen_buffer(const ::int_size& size) override;
      //void destroy_offscreen_buffer() override;

      //void make_current() override;

      //string get_shader_version_text() override;

      //void _translate_shader(string_array_base& stra) override;
      virtual void _create_device(const ::int_size & size);
      //virtual void _opengl_lock();
      //virtual void _opengl_unlock();

      //void _swap_buffers() override;

//      virtual bool _simplified_find_config_for_x11_window4(EGLConfig & eglconfig, long lX11VisualId, bool bOpaque);
//      virtual bool _simplified_find_config_for_x11_window2(EGLConfig & eglconfig, long lX11VisualId, bool bOpaque);
//      virtual bool _simplified_find_config_for_x11_window1(EGLConfig & eglconfig, long & lX11VisualId, bool bOpaque);
//      virtual bool _find_config_for_x11_window1(EGLConfig & eglconfig, long & lX11VisualId, bool bOpaque);
//      virtual bool _find_config_for_pbuffer(EGLConfig & eglconfig, bool bOpaque);
      virtual void __cgl_swap_buffers();

   };


} // namespace gpu_opengl



