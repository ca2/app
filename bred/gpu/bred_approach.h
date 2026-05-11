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
//      //::i32_size                        m_sizeNew;
//      //::i32_size                        m_size;
//      //HDC                           m_hdcGraphics;
//      //float                         m_z;
//      //i32_point                         m_pointTranslate;
//      //::pointer<::opengl::buffer>  m_pbuffer;
//      //::pointer<::opengl::program> m_pprogram;
//      //::u32                  VAO;
//      //::u32                  VBO;

      //enum_mode                              m_emode;


      //::pointer < device >       m_pgpudevice;

      //::i32_rectangle            m_rectangleOffscreen;
      ::map<::acme::windowing::window *, ::pointer<::gpu::device>> m_devicemap;

      bred_approach();
      ~bred_approach() override;


      void initialize(::particle * pparticle) override;


      void initialize_gpu_approach() override;


      ::gpu::device* get_gpu_device(::acme::windowing::window * pacmewindowingwindow) override;


      void engine_on_frame_context_initialization(::gpu::context* pgpucontext) override;


      void defer_init_gpu_library() override;
   

      void gpu_on_before_create_window(::acme::windowing::window* pwindow) override;

      
      void gpu_on_create_window(::acme::windowing::window* pwindow) override;
      virtual void _gpu_on_create_window(::acme::windowing::window *pwindow);

    
   };


} // namespace gpu




