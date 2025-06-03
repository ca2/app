// From gpu_vulkan::context by
// camilo on 2025-05-27 05:03 <3ThomasBorregaardSorensen!!
#pragma once


////#include "acme/exception/exception.h"
#include "acme/constant/gpu.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/prototype/prototype/memory.h"
#include "aura/graphics/draw3d/matrix.h"
#include "apex/parallelization/thread.h"
#include "aura/graphics/gpu/shader.h"
#include "acme/graphics/image/image32.h"


namespace gpu
{


   class CLASS_DECL_AURA device :
      virtual public ::particle
   {
   public:


      itask									         m_itaskCurrentGpuContext;


      ::pointer < ::gpu::approach >          m_pgpuapproach;
      ::pointer < ::windowing::window >      m_pwindow;
      ::pointer < ::gpu::context >           m_pgpucontextCurrent4;
      //::int_size                             m_sizeNew;
      //::int_size                             m_size;
      //float                                  m_z;
      //int_point                              m_pointTranslate;
      //::pointer<::gpu::cpu_buffer>           m_pcpubuffer;
      //::pointer<::gpu::shader>               m_pshader;
      bool                                   m_bCreated;
      //::draw3d::matrix                       m_matrixProjection;
      //::draw3d::matrix                       m_matrixImpact;
      //::pointer < ::gpu::renderer >          m_prenderer;
      //::pointer < ::graphics3d::engine >     m_pengine;
      //::pointer_array < ::gpu::render >      m_rendera;

      //::image32_callback                     m_callbackImage32CpuBuffer;

      //::pointer < ::mutex >                  m_pmutexOffscreen;
      //::int_size                             m_sizeOffscreen;
      //int                                    m_iScanOffscreen;
      //::memory                               m_memoryOffscreen;


      device();
      ~device() override;



      virtual ::gpu::context* current_context();
      //virtual void start_gpu_context(const start_context_t& startcontext);

      //virtual void initialize_gpu_context(const start_context_t& startcontext);

      //virtual void on_create_context(const start_context_t& startcontext);

      //bool task_iteration() override;

      virtual void lock_context();
      virtual void unlock_context();


      virtual void initialize_gpu_device(::gpu::approach * papproach, ::windowing::window * pwindow, const ::int_rectangle & rectanglePlacement, bool bAddSwapChainSupport);


      virtual ::pointer < ::gpu::context > allocate_context(::particle* pparticle);

      virtual ::pointer < ::gpu::context > start_gpu_output_context(::particle* pparticle, const ::gpu::enum_output & eoutput, const ::int_rectangle& rectanglePlacement);

      virtual ::pointer < ::gpu::context > start_cpu_buffer_context(::particle* pparticle, const ::function< void(::image::target* ptarget) >& callbackOnImagePixels, const ::int_rectangle& rectanglePlacement);

      virtual ::pointer < ::gpu::context > start_swap_chain_context(::particle* pparticle, ::windowing::window* pwindow);

      virtual ::pointer < ::gpu::context > start_gpu_context(const start_context_t& startcontext);


      virtual bool make_current(::gpu::context* pgpucontext);

      virtual void release_current(::gpu::context* pgpucontext);

      virtual void on_make_current();

      virtual void on_release_current();

      //virtual ::gpu::renderer* get_renderer();

      //virtual ::int_size size();


      //virtual string _001GetIntroProjection();
      //virtual string _001GetIntroFragment();

      virtual bool is_mesa();

      //inline const ::draw3d::matrix& view_matrix() const { return m_matrixImpact; }
      //inline ::draw3d::matrix& view_matrix() { return m_matrixImpact; }
      //inline const ::draw3d::matrix& projection_matrix() const { return m_matrixProjection; }
      //inline ::draw3d::matrix& projection_matrix() { return m_matrixProjection; }

      //virtual void start_drawing();
      //virtual void global_transform();
      //virtual void draw();
      //virtual void render();


//      virtual void set_bitmap_1(::image::image* pimage);

      //virtual void swap_buffers();


      //virtual void create_window_buffer(void* pHwnd);
      //virtual void _create_window_buffer(void* pHwnd);
      //virtual void create_offscreen_buffer(const ::int_size& size);
      //virtual void _create_offscreen_buffer(const ::int_size& size);

      //virtual void defer_create_window_context(::windowing::window* pwindow);
      //virtual void _defer_create_window_context(::windowing::window* pwindow);

      //virtual void resize_offscreen_buffer(const ::int_size& size);
      //virtual void destroy_offscreen_buffer();

      //virtual void prepare_for_gpu_read();

      virtual void translate_shader(string& str);

      virtual void _translate_shader(string_array& stra);

      //virtual void make_current();

      virtual string load_fragment(const ::string& pszPath, enum_shader_source& eshadersource);

      virtual string get_shader_version_text();

      //virtual void set_matrix_uniform(const ::gpu::payload& payloadMatrix);


      //virtual class image_data image24(const ::payload& payloadFile);
      //virtual class image_data image32(const ::payload& payloadFile);


      //virtual void clear(const ::color::color& color);
    
      virtual void on_top_end_frame();

      virtual int get_type_size(::gpu::enum_type etype);

      virtual void set_mat4(void* p, const ::glm::mat4& mat4);


   };


} // namespace gpu




