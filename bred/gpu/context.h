#pragma once


////#include "acme/exception/exception.h"
#include "acme/constant/gpu.h"
#include "acme/prototype/collection/int_map.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/prototype/prototype/memory.h"
#include "acme/prototype/prototype/pool.h"
#include "aura/graphics/draw3d/matrix.h"
#include "apex/parallelization/thread.h"
#include "bred/gpu/memory_buffer.h"
#include "bred/gpu/shader.h"
#include "acme/graphics/image/image32.h"


namespace gpu
{


   class renderer;

   class image_data
   {
   public:


      ::memory       m_memory;

      int m_iWidth;
      int m_iHeight;

      int width() const { return m_iWidth; }
      int height() const { return m_iHeight; }
      const void * data() const { return m_memory.data(); }
      void * data() { return m_memory.data(); }

      image_data() :m_iWidth(0), m_iHeight(0) {}
      image_data(const image_data & imagedata) :
         m_iWidth(imagedata.m_iWidth),
         m_iHeight(imagedata.m_iHeight),
         m_memory(imagedata.m_memory)
      {


      }
      image_data(image_data && imagedata) :
         m_iWidth(imagedata.m_iWidth),
         m_iHeight(imagedata.m_iHeight),
         m_memory(::transfer(imagedata.m_memory))
      {


      }

   };


   class CLASS_DECL_BRED context :
      virtual public ::thread
   {

   protected:

   public:

      using thread::send;
      using thread::post;
      using thread::_send;
      using thread::_post;

      enum enum_type
      {
         e_type_undefined,
         e_type_none,
         e_type_generic,
         e_type_draw2d,
         e_type_graphics3d,
         e_type_window,
      };


      //int                                    m_iTopicTexture = -1;
      bool                                   m_bCullFace = false;
      //bool m_bOffscreen = true;
      int                                    m_iOverrideFrame = -1;
      enum_type                              m_etype;
      enum_output                            m_eoutput;
      ::gpu::enum_scene                      m_escene;
      //enum_output m_eoutputContextDraw2d = e_output_gpu_buffer;
      //enum_output m_eoutputContextEngine = e_output_gpu_buffer;
      ::gpu::compositor *                    m_pgpucompositor;
      ::pointer<::gpu::device>               m_pgpudevice;
      //::int_rectangle                        m_rectangleNew;
      ::int_rectangle                        m_rectangle;
      float                                  m_z;
      int_point                              m_pointTranslate;
      ::pointer<::gpu::cpu_buffer>           m_pcpubuffer;
      ::pointer<::gpu::shader>               m_pshader;
      ::pointer<::gpu::shader>               m_pshaderBound;
      ::pointer<::gpu::render_target>        m_prendertargetBound;
      bool                                   m_bCreated;
      ::draw3d::matrix                       m_matrixProjection;
      ::draw3d::matrix                       m_matrixImpact;
      bool  m_bD3D11On12Shared = false;
      //::pointer < ::gpu::renderer >          m_pgpurenderer;
      //::pointer < ::gpu::renderer >          m_pgpurendererDraw2d;
      //::pointer < ::gpu::renderer >          m_pgpurendererEngine;
      ::pointer < ::gpu::renderer >          m_pgpurenderer;
      //::pointer < ::gpu::renderer >          m_pgpurendererBackBuffer;
      //::pointer < ::gpu::renderer >          m_pgpurendererSwap;
      ::pointer_array < ::gpu::renderer >    m_gpurendereraDraw2d;
      ::pointer < ::graphics3d::engine >     m_pengine;
      ::pointer_array < ::gpu::render >      m_rendera;
      ::pointer < ::gpu::command_buffer >    m_pcommandbufferUpload;
      ::pointer < ::gpu::model_buffer >      m_pmodelbufferFullscreenQuad;
      // size memory buffer
      ::int_map < ::pool <::gpu::memory_buffer > > m_mapPoolMemoryBuffer;
      //::image32_callback                     m_callbackImage32CpuBuffer;
      ::pointer_array < ::gpu::texture >        m_textureaAtlas;
      //::pointer < ::mutex >                  m_pmutexOffscreen;
      //::int_size                             m_sizeOffscreen;
      //int                                    m_iScanOffscreen;
      //::memory                               m_memoryOffscreen;
      ::pointer < ::gpu::swap_chain >          m_pgpuswapchain;
      ::string_map < ::pointer < ::gpu::texture > > m_texturemap;
      ::pointer_array < ::gpu::shader >         m_shaderaRetire;


      context();
      ~context() override;

      
      //virtual void gpu_debug_message(const ::scoped_string& scopedstr);

      virtual void manage_retired_objects();

      virtual ::pointer < ::gpu::pixmap > create_gpu_pixmap(const ::int_size& size);

      virtual ::gpu::swap_chain* get_swap_chain();

      virtual ::gpu::texture* current_target_texture(::gpu::frame* pgpuframe);

      void _send(const ::procedure& procedure) override;
      //void _post(const ::procedure& procedure) override;

      virtual void øconstruct(::pointer < ::gpu::shader >& pgpushader);

      virtual ::gpu::texture* texture(const ::file::path& path);


      virtual void start_debug_happening(const ::scoped_string& scopedstrDebugHappening);
      virtual void end_debug_happening();

      virtual void load_texture(::pointer < ::gpu::texture > & ptexture, const ::file::path& path);



      virtual void defer_make_current();

      virtual ::pointer < ::gpu::command_buffer > beginSingleTimeCommands(::gpu::enum_command_buffer ecommandbuffer = ::gpu::e_command_buffer_graphics);
      virtual void endSingleTimeCommands(::gpu::command_buffer * pcommandbuffer);

      virtual ::gpu::command_buffer* defer_get_upload_command_buffer();
      virtual void defer_end_upload_command_buffer();


      virtual void _context_lock();
      virtual void _context_unlock();

      virtual void defer_bind(::gpu::shader* pgpushader);
      virtual void defer_unbind(::gpu::shader* pgpushader);
      virtual void defer_unbind_shader();
      //virtual bool defer_construct_new(::pointer < ::gpu::memory_buffer >& pmemorybuffer, memsize size, memory_buffer::enum_type etype);
      //virtual bool defer_construct_new(::pointer < ::gpu::memory_buffer >& pmemorybuffer, const ::block& block, memory_buffer::enum_type etype);


      virtual void create_window_context(::gpu::device* pgpudevice, ::windowing::window * pwindow);

      virtual void create_gpu_context(::gpu::device* pgpudevice, const ::gpu::enum_output& eoutput, const ::gpu::enum_scene & escene, const ::int_size& size);

      /// <summary>
      ///  a draw2d context is a offscreen context that is used for drawing 2d graphics
      /// </summary>
      /// <param name="pgpudevice"></param>
      /// <param name="eoutput"></param>
      /// <param name="size"></param>
      virtual void create_draw2d_context(::gpu::device* pgpudevice, const enum_output& eoutput, const ::int_size& size);

      virtual void initialize_gpu_context(::gpu::device* pgpudevice, const ::gpu::enum_output& eoutput, ::windowing::window* pwindow, const ::int_size & size);

      virtual void on_create_context(::gpu::device * pgpudevice, const ::gpu::enum_output & eoutput, ::windowing::window* pwindow, const ::int_size & size);

      virtual void engine_on_frame_context_initialization();

      //bool task_iteration() override;

      virtual void lock_context();
      virtual void unlock_context();

      virtual ::gpu::enum_output get_eoutput();

      virtual ::pointer < ::gpu::input_layout > input_layout(const ::gpu::properties & properties);

      template < typename VERTEX >
      ::pointer < ::gpu::input_layout > input_layout()
      {

         return this->input_layout(::gpu_properties < VERTEX>());

      }




      virtual ::gpu::cpu_buffer * get_cpu_buffer();


      //virtual void initialize(::particle * pparticle) override;

      virtual void do_on_context(const ::procedure & procedure);
      virtual void send_on_context(const ::procedure & procedure);
      virtual void top_send_on_context(::gpu::context * pcontextInnerStart, bool bForDrawing, const ::procedure& procedure);
      
      virtual bool create_offscreen_graphics_for_swap_chain_blitting(::gpu::graphics * pgraphics, const ::int_size& size = {});


      virtual ::gpu::renderer* get_gpu_renderer();
      //virtual ::gpu::renderer* back_buffer_gpu_renderer();
      ///virtual ::gpu::renderer* draw2d_renderer();
      //virtual ::gpu::renderer* graphics3d_renderer();

      //virtual ::gpu::renderer* new_draw2d_renderer();
      //virtual void set_topic_texture(int iIndex);
      virtual void set_cull_face(bool bSet = true);

      virtual ::int_rectangle rectangle();
      virtual void set_placement(const ::int_rectangle & rectanglePlacement);
      virtual void on_resize(const ::int_size& size);

      virtual string _001GetIntroProjection();
      virtual string _001GetIntroFragment();

      virtual bool is_mesa();

      inline const ::draw3d::matrix & view_matrix() const { return m_matrixImpact; }
      inline ::draw3d::matrix & view_matrix() { return m_matrixImpact; }
      inline const ::draw3d::matrix & projection_matrix() const { return m_matrixProjection; }
      inline ::draw3d::matrix & projection_matrix() { return m_matrixProjection; }

      virtual void start_drawing();
      virtual void global_transform();
      virtual void draw();
      virtual void render();


      virtual void set_bitmap_1(::image::image *pimage);

      //virtual void swap_buffers();


      virtual void create_window_buffer(::windowing::window * pwindow);
      virtual void _create_window_buffer(::windowing::window* pwindow);


      virtual void create_cpu_buffer(const ::int_size& size);
      virtual void _create_cpu_buffer(const ::int_size& size);
      virtual void resize_cpu_buffer(const ::int_size& size);
      virtual void destroy_cpu_buffer();


      virtual void defer_create_window_context(::windowing::window * pwindow);
      virtual void _defer_create_window_context(::windowing::window * pwindow);

      
      virtual void prepare_for_gpu_read();

      virtual void translate_shader(string & str);

      virtual void _translate_shader(string_array& stra);

      //virtual void make_current();
      //virtual void release_current();

      virtual string load_fragment(const ::string & pszPath, enum_shader_source & eshadersource);

      virtual string get_shader_version_text();

      virtual void set_matrix_uniform(const ::gpu::payload & payloadMatrix);


      virtual class image_data image24(const ::payload & payloadFile);
      virtual class image_data image32(const ::payload & payloadFile);


      virtual void clear(const ::color::color& color);


      virtual void create_global_ubo(int iSize, int iFrameCount);
      virtual void update_global_ubo(const ::block& block);

      virtual void copy(::gpu::texture* ptexture);
      virtual void copy(::gpu::texture* ptextureTarget, ::gpu::texture* ptextureSource);
      virtual void merge_layers(::gpu::texture* ptextureTarget, ::pointer_array < ::gpu::layer >* playera);

      virtual void on_start_layer(::gpu::layer* player);
      virtual void on_end_layer(::gpu::layer* player);



      virtual void on_create_texture(::gpu::texture * ptexture);
      //virtual void on_take_snapshot(layer * player);

      virtual void frame_prefix();
      virtual void frame_suffix();

      //virtual void on_begin_draw_attach(::gpu::graphics* pgpugraphics, const ::int_rectangle& rectangle);
      //virtual void draw2d_on_begin_draw(::gpu::graphics* pgpugraphics, const ::int_rectangle & rectangle);
      virtual void on_begin_draw_attach(::gpu::graphics* pgpugraphics);
      virtual void draw2d_on_begin_draw(::gpu::graphics* pgpugraphics);


      virtual void on_end_draw_detach(::gpu::graphics* pgpugraphics);
      virtual void draw2d_on_end_draw(::gpu::graphics* pgpugraphics);
      //virtual void start_layer();
      //virtual void end_layer();

      //virtual render_target* draw2d_render_target();
      //virtual render_target* graphics3d_render_target();

      virtual void __bind_draw2d_compositor(::gpu::compositor * pgpucompositor, ::gpu::layer * player);
      virtual void __defer_soft_unbind_draw2d_compositor(::gpu::compositor* pgpucompositor, ::gpu::layer * player);


      virtual ::memory rectangle_shader_vert();
      virtual ::memory rectangle_shader_frag();


      virtual void white_to_color_sampler_shader_setup(gpu::shader * pshader);
      virtual ::memory white_to_color_sampler_vert();
      virtual ::memory white_to_color_sampler_frag();




      virtual void initialize_rectangle_shader(::gpu::shader* pshader);


      virtual ::gpu::model_buffer* sequence2_uv_fullscreen_quad_model_buffer(::gpu::frame* pgpuframe);


   };






} // namespace gpu




