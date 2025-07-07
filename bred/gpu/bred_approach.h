#pragma once


#include "apex/gpu/approach.h"


namespace gpu
{


   class CLASS_DECL_BRED bred_approach :
      virtual public ::gpu::approach
   {
   public:





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
//      //::int_size                        m_sizeNew;
//      //::int_size                        m_size;
//      //HDC                           m_hdcGraphics;
//      //float                         m_z;
//      //int_point                         m_pointTranslate;
//      //::pointer<::opengl::buffer>  m_pbuffer;
//      //::pointer<::opengl::program> m_pprogram;
//      //unsigned int                  VAO;
//      //unsigned int                  VBO;

      //enum_mode                              m_emode;


      //::pointer < device >       m_pgpudevice;

      //::int_rectangle            m_rectangleOffscreen;


      bred_approach();
      ~bred_approach() override;


      void initialize(::particle * pparticle) override;


      void initialize_gpu_approach() override;


      ::gpu::device* get_gpu_device() override;


      void engine_on_frame_context_initialization(::gpu::context* pgpucontext) override;


      void defer_init_gpu_library() override;
   

      void on_before_create_window(::windowing::window* pwindow) override;

      
      void on_create_window(::windowing::window* pwindow) override;

    
   };


} // namespace gpu




