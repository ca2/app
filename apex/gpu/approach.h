#pragma once


#include "acme/graphics/image/image32.h"


namespace gpu
{


   class CLASS_DECL_APEX approach :
      virtual public ::object
   {
   public:



      enum enum_mode
      {


         e_mode_none,
         e_mode_system,
         e_mode_egl,
         e_mode_glx,
         e_mode_cgl,
         e_mode_fbo,


      };


//
//#ifdef WINDOWS_DESKTOP
//
//      ATOM                          m_atomClass;
//
//#endif
//      bool                          m_bGlewInit;
//
//
//      //HGLRC                         m_hrc;
//      //HDC                           m_hdc;
//      //HWND                          m_hwnd;
//      //::i32_size                        m_sizeNew;
//      //::i32_size                        m_size;
//      //HDC                           m_hdcGraphics;
//      //::f32                         m_z;
//      //i32_point                         m_pointTranslate;
//      //::pointer<::opengl::buffer>  m_pbuffer;
//      //::pointer<::opengl::program> m_pprogram;
//      //::u32                  VAO;
//      //::u32                  VBO;

      enum_mode                              m_emode;


      //::pointer < device >       m_pgpudevice;

      ::i32_rectangle            m_rectangleOffscreen;
      int m_iGraphicsModeStep = -1;
      int m_iGraphicsModeStepCount = -1;

      approach();
      ~approach() override;


      virtual void initialize(::particle * pparticle) override;


      virtual void initialize_gpu_approach();

      virtual ::pointer < ::apex::gpu::window_attachment > allocate_gpu_window_attachment(::acme::windowing::window * pacmewindowingwindow);

      virtual ::gpu::device* get_gpu_device(::acme::windowing::window * pacmewindowingwindow);


      virtual void engine_on_frame_context_initialization(::gpu::context* pgpucontext);

      virtual ::particle_pointer _allocate_draw2d_window_attachment_for_gpu(::acme::windowing::window * pacmewindowingwindow);

      virtual void defer_init_gpu_library();


      virtual int graphics3d_modes_step();
      virtual int graphics3d_modes_step_count();

   

      virtual void gpu_on_before_create_window(::acme::windowing::window* pwindow);
      virtual void gpu_on_create_window(::acme::windowing::window* pwindow);

    
   };


} // namespace gpu




