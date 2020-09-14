#pragma once


namespace opengl
{


   class CLASS_DECL_GPU_OPENGL opengl :
      virtual public ::gpu::approach
   {
   public:


#ifdef WINDOWS_DESKTOP

      ATOM                          m_atomClass;

#endif
      bool                          m_bGlewInit;


      //HGLRC                         m_hrc;
      //HDC                           m_hdc;
      //HWND                          m_hwnd;
      //::size                        m_sizeNew;
      //::size                        m_size;
      //HDC                           m_hdcGraphics;
      //float                         m_z;
      //point                         m_pointTranslate;
      //__pointer(::opengl::buffer)   m_pbuffer;
      //__pointer(::opengl::program)  m_pprogram;
      //unsigned int                  VAO;
      //unsigned int                  VBO;

      opengl();
      virtual ~opengl();


      virtual ::estatus initialize(::layered * pobjectContext) override;


      virtual ::gpu::context* create_context() override;


      virtual ::estatus defer_init_glew() override;

      //virtual ::estatus draw();
      //virtual ::estatus start();
      //virtual ::estatus render();

      //virtual bool create_offscreen_buffer(const ::size& size);
      //virtual bool destroy_offscreen_buffer();


      //virtual ::estatus make_current();


   };


} // namespace opengl



