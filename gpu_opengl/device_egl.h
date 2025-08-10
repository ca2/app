#pragma once


#include "acme/_operating_system.h"
//#include "gpu_opengl/context.h"
#include "gpu_opengl/device.h"
//#include "aura/os/_os.h"
///#include "glad_egl.h"

#include <EGL/egl.h>
#include <EGL/eglext.h>


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL device_egl :
      virtual public ::gpu_opengl::device
   {
   public:


      EGLDisplay                       m_display;
      EGLConfig                        m_config;
      EGLContext                       m_context;
      EGLSurface                       m_surface;


      device_egl();
      ~device_egl() override;


      //void create_context() override;
      //void context::on_create_context(::gpu::device* pgpudevice, const ::gpu::enum_output& eoutput, ::windowing::window* pwindow, const ::int_size& size);
      void initialize_gpu_device_for_swap_chain(::gpu::approach* papproach, ::windowing::window* pwindow) override;
      void initialize_gpu_device_for_off_screen(::gpu::approach* papproach, const ::int_rectangle& rectanglePlacement) override;


      //void _create_offscreen_buffer(const ::int_size& size) override;
      //void resize_offscreen_buffer(const ::int_size& size) override;
      //void destroy_offscreen_buffer() override;

      //void make_current() override;

      //string get_shader_version_text() override;

      //void _translate_shader(string_array_base& stra) override;
      virtual void _create_device(const ::int_size & size);


   };


} // namespace gpu_opengl



