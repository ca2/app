#pragma once


#include "aura/graphics/gpu/approach.h"


namespace opengl
{


   class CLASS_DECL_GPU_OPENGL opengl :
      virtual public ::gpu::approach
   {
   public:

      
      //__creatable_from_base(opengl, ::gpu::approach);


#ifdef WINDOWS_DESKTOP

      ATOM                          m_atomClass;

#endif
      bool                          m_bGpuLibraryInit;


      //HGLRC                         m_hrc;
      //HDC                           m_hdc;
      //HWND                          m_hwnd;
      //::size_i32                        m_sizeNew;
      //::size_i32                        m_size;
      //HDC                           m_hdcGraphics;
      //float                         m_z;
      //point_i32                         m_pointTranslate;
      //::pointer<::opengl::buffer>  m_pbuffer;
      //::pointer<::opengl::program> m_pprogram;
      //unsigned int                  VAO;
      //unsigned int                  VBO;

      opengl();
      virtual ~opengl();


      virtual void initialize(::particle * pparticle) override;


      ::pointer < ::gpu::context > create_context(::particle * pparticle) override;


      int fread(void * data, int c, int s ,::file::file* pfile);

      virtual void defer_init_gpu_library() override;

      //virtual void draw();
      //virtual void start();
      //virtual void render();

      //virtual bool create_offscreen_buffer(const ::size_i32& size);
      //virtual bool destroy_offscreen_buffer();


      //virtual void make_current();


      ::gpu::uniform load_dds(const ::string & strImagePath) override;


   };


} // namespace opengl



