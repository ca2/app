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
#include "bred/graphics3d/rotation.h"


//namespace graphics3d
//{
//
//   
//   class floating_rotation;
//
//
//} // namespace graphics3d


namespace gpu
{

   enum enum_api
   {
      e_api_none,
      e_api_opengl,
      e_api_vulkan,
      e_api_directx11,
      e_api_directx12,

   };


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

      ::collection::index                          m_iGpuContext=-1;

      ::gpu::enum_api                              m_eapi = e_api_none;
      //int                                        m_iTopicTexture = -1;
      //bool                                       m_bCullFace = false;
      ::gpu::enum_cull_mode                        m_ecullmode;
      //bool                                       m_bOffscreen = true;
      int                                          m_iOverrideFrame = -1;
      enum_type                                    m_etype;
      enum_output                                  m_eoutput;
      ::gpu::enum_scene                            m_escene;
      //enum_output                                m_eoutputContextDraw2d = e_output_gpu_buffer;
      //enum_output                                m_eoutputContextEngine = e_output_gpu_buffer;
      ::gpu::compositor *                          m_pgpucompositor;
      ::pointer<::gpu::device>                     m_pgpudevice;
      //::int_rectangle                            m_rectangleNew;
      ::int_rectangle                              m_rectangle;
      float                                        m_z;
      int_point                                    m_pointTranslate;
      ::pointer<::gpu::cpu_buffer>                 m_pcpubuffer;
      ::pointer<::gpu::shader>                     m_pshader;
      ::pointer<::gpu::shader>                     m_pshaderBound;
      ::pointer<::gpu::render_target>              m_prendertargetBound;
      ::pointer < ::gpu::model_buffer >            m_pmodelbufferDummy;
      ::pointer < ::gpu::shader >                  m_pshaderBlend3;
      ::pointer < ::acme::windowing::window >      m_pacmewindowingwindowWindowSurface;

      ::pointer<::gpu::shader>                     m_pgpushaderRgbaFromB_G;
      bool                                         m_bCreated;
      ::draw3d::matrix                             m_matrixProjection;
      ::draw3d::matrix                             m_matrixImpact;
      bool                                         m_bD3D11On12Shared = false;
      //::pointer < ::gpu::renderer >              m_pgpurenderer;
      //::pointer < ::gpu::renderer >              m_pgpurendererDraw2d;
      //::pointer < ::gpu::renderer >              m_pgpurendererEngine;
      ::pointer < ::gpu::renderer >                m_pgpurenderer;
      //::pointer < ::gpu::renderer >              m_pgpurendererBackBuffer;
      //::pointer < ::gpu::renderer >              m_pgpurendererSwap;
      ::pointer_array < ::gpu::renderer >          m_gpurendereraDraw2d;
      ::pointer < ::graphics3d::engine >           m_pengine;
      ::pointer_array < ::gpu::render >            m_rendera;
      ::pointer < ::gpu::command_buffer >          m_pcommandbufferUpload;
      ::pointer < ::gpu::model_buffer >            m_pmodelbufferFullscreenQuad;
      // size memory buffer
      ::int_map < ::pool <::gpu::memory_buffer > > m_mapPoolMemoryBuffer;
      //::image32_callback                         m_callbackImage32CpuBuffer;
      ::pointer_array < ::gpu::texture >           m_textureaAtlas;
      //::pointer < ::mutex >                      m_pmutexOffscreen;
      //::int_size                                 m_sizeOffscreen;
      //int                                        m_iScanOffscreen;
      //::memory                                   m_memoryOffscreen;
      ::pointer < ::gpu::swap_chain >              m_pgpuswapchain;
      ::pointer_array < ::gpu::shader >            m_shaderaRetire;

      ::string_map_base < ::pointer < ::gpu::texture > >    m_texturemap;
      ::string_map_base < ::pointer < ::gpu::texture > >    m_texturemapGeneric;

      ::pointer<::gpu::binding_set>                m_pbindingsetGlobalUbo1;
      ::pointer<::gpu::binding_set>                m_pbindingsetIbl1;
      ::pointer<::gpu::binding_set>                m_pbindingsetGltfPbr;
      ::pointer<::gpu::binding_set>                m_pbindingsetSceneGltfPbr;
      ::pointer<::gpu::command_buffer>             m_pcommandbufferMain;
      //::pointer<::gpu::block>                    m_pblockGlobalUbo;


      context();
      ~context() override;

      
      //virtual void gpu_debug_message(const ::scoped_string& scopedstr);

      virtual void manage_retired_objects();

      virtual ::pointer < ::gpu::pixmap > create_gpu_pixmap(const ::int_size& size);

      virtual ::gpu::swap_chain* get_swap_chain();

      virtual ::gpu::texture* current_target_texture(::gpu::frame* pgpuframe);

      void _send(const ::procedure& procedure) override;
      //void _post(const ::procedure& procedure) override;

      virtual void construct(::pointer < ::gpu::shader >& pgpushader);

      virtual void on_cube_map_face_image(::image::image *pimage);
      /// loads only image::image (A8R8G8B8)
      virtual ::gpu::texture* texture(const ::file::path& path);


      virtual ::pointer < ::gpu::texture > create_empty_texture();


      /// loads different types of image
      virtual ::gpu::texture* generic_texture(const ::file::path & path, bool bSrgb);
      virtual void load_generic_texture(::pointer < ::gpu::texture > & ptexture, const ::file::path & path, bool bSrgb);
      virtual void load_ktx_texture_from_file_path(::gpu::texture * ptexture, const ::file::path & pathImage);
      virtual void load_ktx_texture_from_memory(::gpu::texture * ptexture, const void * data, memsize size);

      virtual void start_debug_happening(::gpu::command_buffer *pgpucommandbuffer,
                                         const ::scoped_string &scopedstrDebugHappening);
      virtual void end_debug_happening(::gpu::command_buffer *pgpucommandbuffer);

      virtual void load_texture(::pointer < ::gpu::texture > & ptexture, const ::file::path& path, bool bIsSrgb);

      virtual void layout_input_layout_properties(::gpu::properties *pproperties);
      virtual void layout_global_ubo(::gpu::properties * pproperties);
      virtual void layout_push_constants(::gpu::properties & properties, bool bGlobalUbo);
      virtual void layout_properties_default(::gpu::properties &properties);
      virtual void _layout_std140_or_std430(::gpu::properties &properties, enum_layout elayout);
      virtual void _layout_hlsl(::gpu::properties &properties);
      //virtual void defer_make_current();

      virtual ::floating_matrix4 defer_transpose(const ::floating_matrix4 & m);
      virtual ::floating_matrix4 defer_clip_remap_projection(const ::floating_matrix4 &m);
      virtual ::floating_matrix4 defer_remap_impact_matrix(const ::floating_matrix4 &m);


      virtual ::pointer < ::gpu::command_buffer > beginSingleTimeCommands(::gpu::queue * pgpuqueue, ::gpu::enum_command_buffer ecommandbuffer = ::gpu::e_command_buffer_graphics);
      virtual void endSingleTimeCommands(::gpu::command_buffer * pcommandbuffer);

      virtual ::gpu::command_buffer* defer_get_upload_command_buffer();
      virtual void defer_end_upload_command_buffer();


      virtual void begin_render(::gpu::command_buffer *pgpucommandbuffer, ::gpu::texture * pgputexture = nullptr);
      virtual void end_render(::gpu::command_buffer *pgpucommandbuffer);


      virtual floating_sequence3 front(const ::graphics3d::floating_rotation &rotation);


      virtual ::gpu::binding_set *global_ubo1_binding_set();
      virtual ::gpu::binding_set *ibl1_binding_set();
      virtual ::gpu::binding_set *gltf_pbr_binding_set();
      virtual ::gpu::binding_set *scene_gltf_pbr_binding_set();


      virtual void _context_lock();
      virtual void _context_unlock();

      virtual bool defer_bind2(::gpu::command_buffer * pgpucommandbuffer, ::gpu::shader * pgpushader, ::gpu::texture * pgputexture);
      virtual bool defer_bind3(::gpu::command_buffer * pgpucommandbuffer, ::gpu::shader * pgpushader);
      virtual void defer_unbind(::gpu::shader* pgpushader);
      virtual void defer_unbind_shader();
      //virtual bool defer_construct_new(::pointer < ::gpu::memory_buffer >& pmemorybuffer, memsize size, memory_buffer::enum_type etype);
      //virtual bool defer_construct_new(::pointer < ::gpu::memory_buffer >& pmemorybuffer, const ::block& block, memory_buffer::enum_type etype);


      virtual void create_window_context(::gpu::device* pgpudevice, ::acme::windowing::window * pwindow);

      virtual void create_gpu_context(::gpu::device* pgpudevice, const ::gpu::enum_output& eoutput, const ::gpu::enum_scene & escene, const ::int_size& size);

      /// <summary>
      ///  a draw2d context is a offscreen context that is used for drawing 2d graphics
      /// </summary>
      /// <param name="pgpudevice"></param>
      /// <param name="eoutput"></param>
      /// <param name="size"></param>
      virtual void create_draw2d_context(::gpu::device* pgpudevice, const enum_output& eoutput, const ::int_size& size);

      virtual void initialize_gpu_context(::gpu::device* pgpudevice, const ::gpu::enum_output& eoutput, ::acme::windowing::window* pwindow, const ::int_size & size);

      virtual void on_create_context(::gpu::device * pgpudevice, const ::gpu::enum_output & eoutput, ::acme::windowing::window* pwindow, const ::int_size & size);

      virtual void engine_on_frame_context_initialization();


      virtual void on_before_initialize_scene();

      virtual void onBeforePreloadGlobalAssets();

      //bool task_iteration() override;

      virtual void lock_context();
      virtual void unlock_context();

      virtual ::gpu::enum_output get_eoutput();

      virtual ::pointer < ::gpu::input_layout > input_layout(const ::gpu::property * pproperty);

      template < typename VERTEX >
      ::pointer < ::gpu::input_layout > input_layout()
      {

         return this->input_layout(::gpu_properties < VERTEX>());

      }




      virtual ::gpu::cpu_buffer * get_cpu_buffer();


      //virtual void initialize(::particle * pparticle) override;

      virtual void assert_there_is_current_context();

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
      virtual void set_cull_face(::gpu::enum_cull_mode ecullmode);

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

      //virtual void start_drawing();
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


      virtual void defer_create_window_context(::acme::windowing::window * pwindow);
      virtual void _defer_create_window_context(::acme::windowing::window * pwindow);

      
      virtual void prepare_for_gpu_read();

      virtual void translate_shader(string & str);

      virtual void _translate_shader(string_array_base& stra);

      //virtual void make_current();
      //virtual void release_current();

      virtual string load_fragment(const ::scoped_string & scopedstrPath, enum_shader_source & eshadersource);

      virtual string get_shader_version_text();

      virtual void set_matrix_uniform(const ::gpu::payload & payloadMatrix);


      virtual class image_data image24(const ::payload & payloadFile);
      virtual class image_data image32(const ::payload & payloadFile);


      virtual void clear(::gpu::texture * ptexture, const ::color::color& color);


      virtual ::pointer < ::gpu::block > create_global_ubo1(const ::gpu::property * ppropertyProperties);
      virtual void update_global_ubo1(::gpu::block * pblockGlobalUbo1);
      virtual void update_current_scene();

      //virtual void copy(::gpu::texture* ptexture);
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


      //virtual void white_to_color_sampler_shader_setup(gpu::shader * pshader);
      virtual ::memory white_to_color_sampler_vert();
      virtual ::memory white_to_color_sampler_frag();


      //virtual bool is_global_ubo_ok();

      virtual void initialize_rectangle_shader(::gpu::shader* pshader);


      virtual ::gpu::model_buffer* sequence2_uv_fullscreen_quad_model_buffer(::gpu::frame* pgpuframe);
      virtual ::pointer < ::gpu::model_buffer> create_sequence2_uv_fullscreen_quad_model_buffer(::gpu::frame* pgpuframe);


      //::pointer<::graphics3d::renderable> load_model();
      virtual ::pointer<::graphics3d::renderable> load_model(const ::gpu::renderable_t & renderable);
      virtual ::pointer<::graphics3d::renderable> _load_model(const ::gpu::renderable_t & renderable);
      virtual ::pointer<::gpu::texture> load_cube_map(
         const ::scoped_string & scopedstrName,
         const ::file::path & path, 
         bool b32);
      virtual ::pointer<::gpu::texture> load_sandbox_texture(const ::scoped_string &scopedstrName,
                                                             const ::file::path &path,
                                                             const ::scoped_string &scopedstrImageFormat);

      virtual ::pointer<::gpu::texture> cubemap_from_hdr(const ::file::path & path);

      // // ::pointer<::graphics3d::renderable> loadGLTFmodel(
      // //    const ::scoped_string &name,
      // //    const ::scoped_string &filepath,
      // //    uint32_t gltfFlags,
      // //    float scale);
      //
      //
      // ::pointer<::graphics3d::renderable> loadObjModel(
      //      const ::scoped_string &name,
      //      const ::scoped_string &filepath,
      //      bool isSkybox
      //      );
      //
      //
      // ::pointer<::graphics3d::renderable> loadGLTFmodel(
      //    const ::scoped_string &name,
      //    const ::scoped_string &filepath,
      //    uint32_t gltfFlags,
      //    float scale
      //    );


      //virtual ::pointer<::graphics3d::renderable> load_wavefront_obj_renderable(const ::gpu::renderable_t & model);

      //virtual ::pointer<::graphics3d::renderable> _load_wavefront_obj_renderable(const ::gpu::renderable_t & model);

      //virtual ::pointer<::graphics3d::renderable> load_gltf_model(const ::gpu::renderable_t & model);

      //virtual ::pointer<::graphics3d::renderable> _load_gltf_model(const ::gpu::renderable_t & model);


      virtual void set_viewport(::gpu::command_buffer *pgpucommandbuffer, const ::int_rectangle &rectangle);
      virtual void set_scissor(::gpu::command_buffer *pgpucommandbuffer, const ::int_rectangle &rectangle);

//      /// @brief generatePrefilteredEnvMap
//      /// @param environmentCubeExisting 
//      /// @param prenderableSkybox 
//      /// @return 
//      virtual ::pointer<::gpu::texture> generatePrefilteredEnvMap(
//         ::gpu::texture *environmentCubeExisting,
//         ::graphics3d::renderable *prenderableSkybox);
//
//      /// generate irradianceCube
//      /// @return irradianceCube
//      virtual ::pointer < ::gpu::texture > generateIrradianceMap(
////         ::gpu::texture * irradianceCube,
//         ::gpu::texture * environmentCube,
//         ::graphics3d::renderable * prenderableSkybox);
//      // ::pointer<::gpu::texture> loadCubemap(
//      //    const ::scoped_string& name,
//      //    const ::scoped_string& ktxFilename,
//      //    VkFormat format,
//      //    VkImageUsageFlags usageFlags,
//      //    VkImageLayout initialLayout);
//      //    virtual void generateBRDFlut(
//      //     ::gpu::texture * lutBrdf);
//      /// generate lutBrdf
//      /// @return lutBrdf
//      virtual ::pointer < ::gpu::texture > generateBRDFlut();



      //::pointer < ::graphics3d::renderable> create_tinyobj_renderable(const ::file::path& path);

      //::pointer < ::graphics3d::renderable > create_tinyobj(const ::file::path& path);
      // scene_object * get_tinyobj(const ::file::path& path);
      //
      // inline scene_object & tinyobj(const ::file::path& path)
      // {
      //
      //    return *get_tinyobj(path);
      //
      // }
      // 
      // 
      
      virtual floating_matrix4 ortho(float left, float right, float bottom, float top, float zNear = -1.0f,
                                     float zFar = 1.0f);
     
      //virtual floating_matrix4 perspective(float fovyRadians, float aspect, float zNear, float zFar);

      //// 
      //// ------------------------------
      //// Rotation from camera axes
      //// ------------------------------
      //// Builds a matrix from right, up, forward vectors
      //virtual floating_matrix4 rotateFromAxes(const floating_sequence3 &right, const floating_sequence3 &up,
      //                                const floating_sequence3 &forward);  // OpenGL forward = -f

      //virtual floating_matrix4 lookAt(const float_sequence3 &eye, const float_sequence3 &center,
      //   
      // 
      //                            const float_sequence3 &up);
      // 
virtual void swap_buffers();

      //  quite a work arround;
      // use just the metallic;
      // oh, please try to create something like:
      // ptextureMetallicRoughness =
      // m_pgpucontext->rgb_from_b_g(ptextureMetallic, ptextureRoughness);
      virtual ::memory rgba_from_b_g_vert_memory();
      virtual ::memory rgba_from_b_g_frag_memory();
      virtual ::pointer<::gpu::texture> rgba_from_b_g(::gpu::texture *pgputextureMetallic,
                                                      ::gpu::texture *pgputextureRoughness);
   };


   inline void context::swap_buffers()
   {



   }


} // namespace gpu



