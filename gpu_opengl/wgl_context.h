//
// Created by camilo on 2026-02-22 14:29 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "acme/_operating_system.h"
#include "gpu_opengl/_gpu_opengl.h"
#include "windowing_win32/window.h"


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL wgl_context :
      virtual public ::particle
   {
   public:


      HWND m_hwnd;
      HDC m_hdc;
      HGLRC m_hglrc;

      bool m_bDummy;
      bool m_bOwnWindow;

      bool m_bContextSelected = false;
      task_index m_taskindex = 0;
      itask m_itask;
      htask m_htask;


      wgl_context();
      ~wgl_context();


      void create_window_wgl_context(::windowing_win32::window *pwin32windowingwindow);

      void create_offscreen_wgl_context();

      void create_dummy_wgl_context();

      void _create_wgl_context(int * contextAttribs);

      void select();
      void unselect();


      void destroy();


   };




   //class CLASS_DECL_GPU_OPENGL dummy_wgl_context : public wgl_context
   //{
   //public:


   //   dummy_wgl_context();
   //   ~dummy_wgl_context();
   //};


   class CLASS_DECL_GPU_OPENGL scoped_dummy_wgl_context
   {
   public:

      
      ::particle *m_pparticle;

      
      scoped_dummy_wgl_context(::particle * pparticle);
      ~scoped_dummy_wgl_context();


   };


   CLASS_DECL_GPU_OPENGL HWND create_hidden_gl_window();


   CLASS_DECL_GPU_OPENGL void defer_load_wgl_extensions(::particle * pparticle);


} // namespace gpu_opengl



