// From gpu_opengl::context by
// camilo on 2025-05-27 06:10 <3ThomasBorregaardSorensen!!
#pragma once


#include "aura/graphics/gpu/device.h"
#include "acme/prototype/prototype/memory.h"


namespace gpu_opengl
{



   class CLASS_DECL_GPU_OPENGL device :
      virtual public ::gpu::device
   {
   public:


      ///itask									m_itaskGpu;

      //unsigned int                     m_VAO;
      //unsigned int                     m_VBO;

     /* GLint                            m_iMatrixUniform;

      GLuint                           m_gluTextureBitmap1;
      int                              m_iLastBitmap1Scan;
      ::int_size                       m_sizeBitmap1;

      memory                           m_memorySwap;*/

      device();
      ~device() override;



      //::pointer < ::gpu::context > allocate_context(::particle* pparticle) override;


      /// <summary>
      /// 
      /// </summary>
      /// <returns>true if changed to make current</returns>
      virtual bool make_current(::gpu::context * pgpucontext);
      virtual void release_current(::gpu::context* pgpucontext);
      virtual void _swap_buffers();
      //string _001GetIntroProjection() override;
      //string _001GetIntroFragment() override;

      //void draw() override;
      //void start_drawing() override;
      //void global_transform() override;
      //void render() override;

      //void set_bitmap_1(::image::image* pimage) override;

      //void swap_buffers() override;

      //virtual void create_offscreen_buffer(const ::int_size& size);
      //virtual void _create_offscreen_buffer(const ::int_size& size);

      //virtual void resize_offscreen_buffer(const ::int_size& size);
      //virtual void destroy_offscreen_buffer();

   /*   virtual void translate_shader(string & str);

      virtual void _translate_shader(string_array& stra);*/

      //virtual void make_current();

      // virtual string load_fragment(const ::string & pszPath, enum_shader_source& eshadersource);

      //virtual string get_shader_version_text();

      //void set_matrix_uniform(const ::gpu::payload& uniformMatrix) override;


      //void clear(const ::color::color& color) override;


   };


} // namespace gpu



