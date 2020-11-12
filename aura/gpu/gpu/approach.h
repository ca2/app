#pragma once


namespace gpu
{


   class CLASS_DECL_AURA approach :
      virtual public ::object
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
//      //::size                        m_sizeNew;
//      //::size                        m_size;
//      //HDC                           m_hdcGraphics;
//      //float                         m_z;
//      //point                         m_pointTranslate;
//      //__pointer(::opengl::buffer)   m_pbuffer;
//      //__pointer(::opengl::program)  m_pprogram;
//      //unsigned int                  VAO;
//      //unsigned int                  VBO;

      approach();
      virtual ~approach();


      virtual ::estatus initialize(::layered * pobjectContext) override;


      virtual context * create_context();


      virtual ::estatus defer_init_glew();

      //virtual ::estatus draw();
      //virtual ::estatus start();
      //virtual ::estatus render();

      //virtual bool create_offscreen_buffer(const ::size& size);
      //virtual bool destroy_offscreen_buffer();


      //virtual ::estatus make_current();


   };


} // namespace gpu




