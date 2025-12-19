// From gpu_opengl/context.h by camilo on 2025-09-28 11:54 <3ThomasBorregaardSorensen!!
#pragma once


#include "bred/gpu/context.h"
#include "acme/prototype/prototype/memory.h"


namespace gpu_gpu
{


   class CLASS_DECL_GPU context :
      virtual public ::gpu::context
   {
   public:
      float m_fGammaCorrectionFactor = 2.2f;
      float m_fBloomBrightnessCutoff = 1.0f; // fragments with brightness above this are blurred

//::pointer < ::graphics3d::renderable > m_prenderableSkybox;
      // bool     m_bDepthBuffer = true;
      // //GLuint m_vaoFullScreenQuad;
      // //GLuint m_vboFullScreenQuad;
      // ::pointer < ::gpu_opengl::frame_buffer >   m_pframebuffer;
      // ::pointer < ::gpu_opengl::shader >   m_pshaderCopy;
      // ::pointer < ::gpu_opengl::shader >   m_pshaderBlend3;
      // ::int_size                    m_sizeHost;
      // ::pointer < ::gpu::model_buffer >      m_pmodelbufferDummy;
      // //bool m_bMesa;
      //
      // GLuint m_globalUBO;
      //
      //
      // unsigned int                     m_VAO;
      // unsigned int                     m_VBO;
      //
      // GLint                            m_iMatrixUniform;
      //
      // GLuint                           m_gluTextureBitmap1;
      // int                              m_iLastBitmap1Scan;
      // ::int_size                       m_sizeBitmap1;
      //
      // memory                           m_memorySwap;
      //
      // GLuint                           m_gluLayerFrameBuffer;
      //

      context();
      ~context() override;


      ::pointer<::gpu::texture> cubemap_from_hdr(const ::file::path &pathHdr);
      ::pointer<::gpu::texture> cubemap_from_hdr_on_memory(const ::block & block);

//
//
//       string _001GetIntroProjection() override;
//       string _001GetIntroFragment() override;
//
//       void draw() override;
//       void start_drawing() override;
//       void global_transform() override;
//       void render() override;
//
//       void set_bitmap_1(::image::image *pimage) override;
//       //void set_topic_texture(int iIndex) override;
//       void set_cull_face(::gpu::enum_cull_mode ecullmode) override;
//       //void swap_buffers() override;
//
//       void _context_lock() override;
//       void _context_unlock() override;
//
//       virtual void update_framebuffer(const ::int_size& size);
//       //void gpu_debug_message(const ::scoped_string& scopedstrMessage) override;
//       void start_debug_happening(const ::scoped_string& scopedstrMessage) override;
//       ::memory rectangle_shader_vert() override;
//       ::memory rectangle_shader_frag() override;
//
//       ::memory white_to_color_sampler_vert() override;
//       ::memory white_to_color_sampler_frag() override;
//
//
//       void load_generic_texture(::pointer < ::gpu::texture > & ptexture, const file::path &path, int iAssimpTextureType) override;
//
//
//       //virtual void create_offscreen_buffer(const ::int_size& size);
//       //virtual void _create_offscreen_buffer(const ::int_size& size);
//
//       //virtual void resize_offscreen_buffer(const ::int_size& size);
//       //virtual void destroy_offscreen_buffer();
//
//    /*   virtual void translate_shader(string & str);
//
//       virtual void _translate_shader(string_array_base& stra);*/
//
//       //virtual void make_current();
//
//       // virtual string load_fragment(const ::scoped_string & scopedstrPath, enum_shader_source& eshadersource);
//
//       //virtual string get_shader_version_text();
//
//
//
//       virtual void _create_offscreen_window(const ::int_size & size);
//
//       void copy(::gpu::texture* ptextureTarget, ::gpu::texture* ptextureSource) override;
//
//       void on_create_context(::gpu::device* pgpudevice, const ::gpu::enum_output& eoutput, ::windowing::window* pwindow, const ::int_size& size) override;
//
//       void defer_create_window_context(::windowing::window * pwindow) override;
//       void _defer_create_window_context(::windowing::window * pwindow) override;
//       virtual void _create_window_context(::windowing::window * pwindow);
//
//       virtual void _create_window_buffer();
//       void _create_cpu_buffer(const ::int_size& size) override;
//       void resize_cpu_buffer(const ::int_size& size) override;
//       void destroy_cpu_buffer() override;
//
//
//       void set_matrix_uniform(const ::gpu::payload & uniformMatrix) override;
//
//
//       void clear(const ::color::color& color) override;
//       void create_global_ubo(int iSize, int iFrameCount) override;
//       void update_global_ubo(const ::block& block) override;
//
//
//       void copy(::gpu::texture* ptexture) override;
//       virtual void _copy_using_shader(::gpu::texture* ptexture);
//       virtual void _copy_using_blit(::gpu::texture* ptexture);
//       void merge_layers(::gpu::texture* ptextureTarget, ::pointer_array < ::gpu::layer >* playera) override;
//
//       void on_start_layer(::gpu::layer* player) override;
//
//       void on_end_layer(::gpu::layer* player) override;
//
//       //virtual void _ensure_layer_framebuffer();
//
//       //void make_current() override;
//
//
//       void defer_make_current() override;
//
//
//       //void release_current() override;
//
//       //bool is_mesa() override;
//
//       //void render();
//
//       string get_shader_version_text() override;
//
//       void _translate_shader(string_array_base & straFragment) override;
//
//       //void swap_buffers() override;
//
//       //void copy(::gpu::texture* pgputextureTarget, ::gpu::texture* pgputextureSource) override;
//
//       ::pointer<::graphics3d::renderable> _load_gltf_model(const ::gpu::renderable_t &model) override;

//      ::pointer < ::graphics3d::renderable > get_skybox_cube_model();
//
//      virtual ::gpu::ibl::equirectangular_cubemap *equirectangular_cubemap();
//      virtual ::gpu::ibl::specular_map *ibl_specular_map();
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

      
      ::pointer<::graphics3d::renderable> _load_gltf_model(const ::gpu::renderable_t &model) override;
      void load_generic_texture(::pointer<::gpu::texture> &ptexture, const ::file::path &path, int iAssimpTextureType) override;
      virtual void load_ktxTexture(::pointer<::gpu::texture> &ptexture, void *p_ktxTexture);
      virtual void load_ktxTexture_cube_map(::pointer<::gpu::texture> &ptexture, void *p_ktxTexture);
      ::pointer<::gpu::texture> load_cube_map(const ::scoped_string &scopedstrName, const ::file::path &path,
                                                      bool b32) override;

   };



} // namespace gpu_gpu



