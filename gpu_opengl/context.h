#pragma once


#include "aura/graphics/gpu/context.h"
#include "acme/prototype/prototype/memory.h"


namespace gpu_opengl
{



   class CLASS_DECL_GPU_OPENGL context :
      virtual public ::gpu::context
   {
   public:


      //GLuint m_fboID;
      //GLuint m_texID;
      //::int_size m_sizeTex;

      bool     m_bDepthBuffer = true;

      ::pointer < ::gpu_opengl::frame_buffer >   m_pframebuffer;

      ::int_size                    m_sizeHost;
      //bool m_bMesa;

      GLuint m_globalUBO;


      unsigned int                     m_VAO;
      unsigned int                     m_VBO;

      GLint                            m_iMatrixUniform;

      GLuint                           m_gluTextureBitmap1;
      int                              m_iLastBitmap1Scan;
      ::int_size                       m_sizeBitmap1;

      memory                           m_memorySwap;

      context();
      ~context() override;


      string _001GetIntroProjection() override;
      string _001GetIntroFragment() override;

      void draw() override;
      void start_drawing() override;
      void global_transform() override;
      void render() override;

      void set_bitmap_1(::image::image *pimage) override;

      void swap_buffers() override;


      virtual void update_framebuffer(const ::int_size& size);

      //virtual void create_offscreen_buffer(const ::int_size& size);
      //virtual void _create_offscreen_buffer(const ::int_size& size);

      //virtual void resize_offscreen_buffer(const ::int_size& size);
      //virtual void destroy_offscreen_buffer();

   /*   virtual void translate_shader(string & str);

      virtual void _translate_shader(string_array& stra);*/

      //virtual void make_current();

      // virtual string load_fragment(const ::string & pszPath, enum_shader_source& eshadersource);

      //virtual string get_shader_version_text();

      virtual void _create_offscreen_window(const ::int_size & size);

      void on_create_context(const ::gpu::start_context_t& startcontext) override;

      void defer_create_window_context(::windowing::window * pwindow) override;
      void _defer_create_window_context(::windowing::window * pwindow) override;
      virtual void _create_window_context(::windowing::window * pwindow);

      virtual void _create_window_buffer();
      void _create_cpu_buffer(const ::int_size& size) override;
      void resize_cpu_buffer(const ::int_size& size) override;
      void destroy_cpu_buffer() override;

      
      void set_matrix_uniform(const ::gpu::payload & uniformMatrix) override;


      void clear(const ::color::color& color) override;
      void create_global_ubo(int iSize, int iFrameCount) override;
      void update_global_ubo(const ::block& block) override;


      
      void make_current() override;


      void release_current() override;

      //bool is_mesa() override;

      //void render();

      string get_shader_version_text() override;

      void _translate_shader(string_array & straFragment) override;

      //void swap_buffers() override;


   };



} // namespace gpu



