// Created from graphics3d/impact3d/render by camilo on 2023-06-16 15:00 <3ThomasBorregaardSorensenJegElskerDig!! (ThomasLikesNumber5)
#pragma once


#include "acme/constant/gpu.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "bred/gpu/shader.h"
#include "acme/prototype/prototype/pool.h"


namespace gpu
{


   class CLASS_DECL_BRED renderer :
      virtual public ::particle,
      virtual public ::ongoing_particle_array_source
   {
   public:

      int m_iSentLayerCount = 0;
      //::pointer<::gpu::layer>                         m_pgpulayer;

      ::collection::count     m_iDefaultFrameCount;

      //::gpu::enum_output                    m_eoutput;
      //::gpu::enum_scene                     m_escene;
      //bool                                m_bPendingShaderUpdate;
      //string                              m_strProjection;
      //string                              m_strFragment;
      //::pointer<::gpu::context>             m_pgpucontextUpper;
      ::pointer<::gpu::context>             m_pgpucontext;
      ::pointer<::gpu::graphics>     m_pgraphics;
      //::pointer<::gpu::context>             m_pgpucontextOutput;
      bool                                  m_bDisableDepthStencil = false;
      ::int_size m_sizeRenderer;
      //::pointer<::gpu::approach>            m_papproach;
      //::image::image_pointer                m_pimageFromGpu;
      ///::pointer<::gpu::shader>              m_pshader;
      //int_rectangle                         m_rectangle;
      //int_size                              m_sizeHost;
      //string                              m_strFont1;
      //string_map < ::image::image_pointer >      m_pimagemap;
      //::image::image_pointer                     m_pimage1;
      //::image::image_pointer                     m_pimage2;
      //::color::hls                        m_hlsText;
      //class ::time                          m_timeStart;
      //::pointer<::gpu::object>            m_pobject;
      //string                              m_strMatrixUniform;
      //string                              m_strTextureUniform;
      //bool                                m_bPrepared;
      //::string                            m_strRender;

      bool isFrameStarted = false;
      bool m_bNeedToRecreateSwapChain = false;


      ::pointer_array<command_buffer>	         m_commandbuffera;


      ::pointer < render_target >   m_pgpurendertarget;
      ::pointer < swap_chain >      m_pswapchain;
      ::pointer < render_state >    m_prenderstate;

      renderer();
      ~renderer() override;


#ifdef _DEBUG
      long long increment_reference_count() override;
      long long decrement_reference_count() override;
#endif


      //virtual void set_no_frame();

      //virtual void set_single_frame();

      virtual void create_command_buffers();

      virtual void free_command_buffers();

      bool isFrameInProgress() const { return isFrameStarted; }


      virtual ::particle_array * current_frame_particle_array();
      ::particle_array* ongoing_particle_array() override;


      virtual ::gpu::texture* current_render_target_texture(::gpu::frame* pgpuframe);

      //virtual ::int_rectangle rectangle();
      //virtual int height();
      virtual ::gpu::command_buffer* getCurrentCommandBuffer2(::gpu::frame* pgpuframe);
      virtual ::gpu::command_buffer* getLoadAssetsCommandBuffer();
      virtual bool render_step();

      virtual void initialize_gpu_renderer(::gpu::context * pgpucontext);

      //virtual void initialize_render(::user::interaction * puserinteraction);
      ///// Initialization routines
      //virtual void set_vertex_source_code(const string & strVertexSourceCode);
      //virtual void set_fragment_source_code(const string & strFragmentSourceCode);
      //virtual void set_model_path(const ::payload & payloadFile);

      virtual ::pointer<::gpu::shader> create_shader(
         const ::file::path& pathVert,
         const ::file::path& pathFrag,
         const ::array<::gpu::shader::enum_descriptor_set_slot>& eslota = {},
         const ::particle_pointer& pLocalDescriptorSet = {},
         //const ::particle_pointer& pVertexInput = {},
         const ::gpu::property* ppropertiesPush = nullptr,
         ::gpu::input_layout * pinputlayout = nullptr,
         ::gpu::shader::enum_flag eflag = ::gpu::shader::e_flag_none);


      //string get_font();
      //::e_status set_font(const string & strFont);

      //virtual void set_update_shader();
      //virtual void defer_update_shader();
      //virtual ::e_status _update_shader();

      //virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      //virtual void _001OnDraw1Through3(::draw2d::graphics_pointer & pgraphics);

      //virtual void _001OnDrawArcs(::draw2d::graphics_pointer & pgraphics, bool bPath);

      //virtual void draw_arc(::draw2d::graphics_pointer & pgraphics, int_rectangle & r, double dStart, double dAngle, bool bPath);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      //virtual void defer_prepare();

      //virtual void _prepare();

      //virtual void draw();

      //virtual void set_placement(const ::int_rectangle & rectanglePlacement);

      virtual void on_context_resize();

      virtual void on_begin_render(frame* pframe);
      virtual void on_end_render(frame* pframe);

      virtual void _on_begin_render(frame* pframe);
      virtual void _on_end_render(frame* pframe);




      virtual bool is_starting_frame()const;

      //virtual void on_new_frame();

      virtual ::pointer < frame > beginFrame();

      virtual void on_begin_frame();

      virtual void endFrame();

      virtual void wait_swap_chain_command_buffer_ready();

      virtual void wait_command_buffer_ready();


      virtual void on_begin_draw();
      virtual void on_end_draw();

      virtual void defer_end_frame_layer_copy();

      virtual void draw();
      virtual void read_to_cpu_buffer();
      //virtual void to_draw2d_graphics(::draw2d::graphics_pointer & pgraphics);

      virtual void on_start_drawing();
      virtual void on_global_transform();
      virtual void on_draw();
      //virtual void render();
      //virtual int get_frame_index();
      //virtual int get_frame_count();
      //virtual int _get_frame_index();
      //virtual int _default_get_frame_index();
      //virtual int __default_get_frame_index();


      virtual void endDraw(::gpu::graphics* pgraphics, ::user::interaction* puserinteraction);


      virtual void defer_update_renderer();

      virtual ::pointer < render_target > on_create_render_target();
      virtual ::pointer < swap_chain > on_create_swap_chain();

      //virtual render_target* back_buffer_render_target();

      //virtual ::pointer < render_target > allocate_offscreen_render_target();

      //virtual void on_graphics_end_draw(::user::interaction * puserinteraction);

      virtual void blend(::gpu::renderer* prenderer);
      virtual void clear(::gpu::texture* ptexture);
      virtual void copy(::gpu::texture* pgputextureTarget, ::gpu::texture* pgputextureSource);
      virtual void blend(::gpu::texture* pgputextureTarget, ::gpu::texture* pgputextureSource);

      virtual void soft_restore_context();

      virtual void endDrawEndDraw();


      virtual void do_on_frame(bool bForDrawing, const ::function < void(::gpu::frame*) > & on_frame);
      virtual void frame_prefix();
      virtual void frame_suffix();

      //virtual void start_layer(const ::int_rectangle& rectangleTarget);
      virtual void start_layer();
      //virtual void take_snapshot(layer * player, const ::int_rectangle& rectangleTarget);
      virtual void end_layer();
      //virtual void merge_layers(::pointer_array < layer > * playera);


      virtual void on_start_layer(layer * player);
      virtual void on_end_layer(layer* player);


      virtual void start_frame();
      virtual void end_frame();


      virtual ::pointer < ::gpu::texture > create_image_texture(const ::int_size& size, bool bWithDepth);
      //virtual void take_snapshot(layer* player);
     

   };


} // namespace graphics3d_hello3d



