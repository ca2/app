// Created from graphics3d/impact3d/render by camilo on 2023-06-16 15:00 <3ThomasBorregaardSorensenJegElskerDig!! (ThomasLikesNumber5)
#pragma once


#include "acme/constant/gpu.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "aura/graphics/gpu/shader.h"


namespace gpu
{


   class CLASS_DECL_AURA renderer :
      virtual public ::particle
   {
   public:

      enum enum_state
      {
         e_state_initial,
         e_state_new_frame,
         e_state_began_frame,
         e_state_began_render,
         e_state_ended_render,
         e_state_ended_frame,

      };


      enum enum_happening
      {
         
         e_happening_reset_frame_counter,
         e_happening_new_frame,
         e_happening_begin_frame,
         e_happening_begin_render,
         e_happening_end_render,
         e_happening_end_frame,

      };


      ::gpu::enum_output                    m_eoutput;
      ::gpu::enum_scene                     m_escene;
      //bool                                m_bPendingShaderUpdate;
      //string                              m_strProjection;
      //string                              m_strFragment;
      ::pointer<::gpu::context>             m_pgpucontext;
      //::pointer<::gpu::context>             m_pgpucontextOutput;

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

      ::pointer < frame > m_pframe;
      enum_state m_estate = e_state_initial;

      renderer();
      ~renderer() override;


#ifdef _DEBUG
      long long increment_reference_count() override;
      long long decrement_reference_count() override;
#endif

      virtual void on_happening(enum_happening ehappening);
      //virtual ::int_rectangle rectangle();
      //virtual int height();

      virtual bool render_step();

      virtual void initialize_renderer(::gpu::context * pgpucontext, ::gpu::enum_output eoutput, ::gpu::enum_scene escene);

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
         const ::particle_pointer& pVertexInput = {},
         const ::gpu::property* pproperties = nullptr,
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

      virtual void on_begin_draw();
      virtual void on_end_draw();

      virtual void draw();
      virtual void read_to_cpu_buffer();
      //virtual void to_draw2d_graphics(::draw2d::graphics_pointer & pgraphics);

      virtual void on_start_drawing();
      virtual void on_global_transform();
      virtual void on_draw();
      //virtual void render();
      virtual int get_frame_index() const;
      virtual int get_frame_count() const;


      virtual void on_new_frame();
      
      virtual ::pointer < frame > beginFrame();


      virtual void on_begin_render(frame* pframe);
      virtual void on_end_render(frame* pframe);

      virtual void endFrame();
      virtual void endDraw(::user::interaction * puserinteraction, ::gpu::renderer * prendererSrc);


      virtual void defer_update_render_pass();

      //virtual void on_graphics_end_draw(::user::interaction * puserinteraction);


   };


} // namespace graphics3d_hello3d



