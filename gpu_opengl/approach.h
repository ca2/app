#pragma once


#include "aura/graphics/gpu/approach.h"


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL approach :
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


      approach();
      ~approach() override;


      void initialize(::particle * pparticle) override;


      ::file::path shader_path(const ::file::path& pathShader) override;



      //::pointer < ::gpu::context > _create_context(::particle * pparticle, ::gpu::enum_output eoutput, ::windowing::window* pwindow, const ::int_rectangle& rectanglePlacement) override;


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



