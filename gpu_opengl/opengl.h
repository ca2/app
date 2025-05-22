#pragma once


#include "aura/graphics/gpu/approach.h"


namespace gpu_opengl
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
      //::int_size                        m_sizeNew;
      //::int_size                        m_size;
      //HDC                           m_hdcGraphics;
      //float                         m_z;
      //int_point                         m_pointTranslate;
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

      //virtual bool create_offscreen_buffer(const ::int_size& size);
      //virtual bool destroy_offscreen_buffer();


      //virtual void make_current();


      ::gpu::payload load_dds(const ::scoped_string & scopedstrImagePath) override;


   };


} // namespace gpu_opengl



