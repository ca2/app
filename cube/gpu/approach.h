#pragma once


#include "acme/graphics/image/image32.h"


namespace gpu
{


   class CLASS_DECL_CUBE approach :
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
//      //::int_size                        m_sizeNew;
//      //::int_size                        m_size;
//      //HDC                           m_hdcGraphics;
//      //float                         m_z;
//      //int_point                         m_pointTranslate;
//      //::pointer<::opengl::buffer>  m_pbuffer;
//      //::pointer<::opengl::program> m_pprogram;
//      //unsigned int                  VAO;
//      //unsigned int                  VBO;

      enum_mode                              m_emode;


      ::pointer < device >       m_pgpudevice;


      approach();
      ~approach() override;


      virtual void initialize(::particle * pparticle) override;


      virtual void initialize_gpu_approach();


      virtual ::gpu::device* get_device(::windowing::window * pwindow, const ::int_rectangle & rectanglePlacement);


      virtual void engine_on_frame_context_initialization(::gpu::context* pgpucontext);


      virtual ::file::path shader_path(const ::file::path& pathShader);



      virtual void defer_init_gpu_library();

      //virtual void draw();
      //virtual void start();
      //virtual void render();

      //virtual bool create_offscreen_buffer(const ::int_size& size);
      //virtual bool destroy_offscreen_buffer();


      //virtual void make_current();


      virtual ::gpu::payload load_dds(const ::scoped_string & scopedstrImagePath);
    
   };


} // namespace gpu




