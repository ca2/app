// Created from graphics3d/impact3d/render by camilo on 2023-06-16 15:00 <3ThomasBorregaardSorensenJegElskerDig!! (ThomasLikesNumber5)
#pragma once


#include "acme/prototype/geometry2d/rectangle.h"


namespace gpu
{


   class CLASS_DECL_CUBE render :
      virtual public ::particle
   {
   public:


      //bool                                m_bPendingShaderUpdate;
      //string                              m_strProjection;
      //string                              m_strFragment;
      ::pointer<::gpu::context>             m_pgpucontext;
      ::image::image_pointer                       m_pimageFromGpu;
      ::pointer<::gpu::shader>              m_pshader;
      int_rectangle                         m_rectangle;
      int_size                              m_sizeHost;
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


      render();
      ~render() override;


#ifdef _DEBUG
      long long increment_reference_count() override;
      long long decrement_reference_count() override;
#endif

      virtual bool render_step();

      void initialize(::particle * pparticle) override;

      //virtual void initialize_render(::user::interaction * puserinteraction);
      ///// Initialization routines
      //virtual void set_vertex_source_code(const string & strVertexSourceCode);
      //virtual void set_fragment_source_code(const string & strFragmentSourceCode);
      //virtual void set_model_path(const ::payload & payloadFile);


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

      virtual void draw();
      virtual void read_to_cpu_buffer();
      virtual void to_draw2d_graphics(::draw2d::graphics_pointer & pgraphics);

      virtual void on_start_drawing(::gpu::context * pgpucontext);
      virtual void on_global_transform(::gpu::context * pgpucontext);
      virtual void on_draw(::gpu::context * pgpucontext);
      //virtual void render();

      


   };


} // namespace graphics3d_hello3d



