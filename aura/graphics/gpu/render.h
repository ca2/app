// Created from graphics3d/impact3d/render by camilo on 2023-06-16 15:00 <3ThomasBorregaardSorensenJegElskerDig!! (ThomasLikesNumber5)
#pragma once


#include "acme/primitive/geometry2d/rectangle.h"


namespace gpu
{


   class CLASS_DECL_AURA render :
      virtual public ::particle
   {
   public:


      
      //bool                                m_bPendingShaderUpdate;
      //string                              m_strProjection;
      //string                              m_strFragment;
      ::pointer<::gpu::context>              m_pgpucontext;
      //::pointer<::gpu::program>           m_pprogram;
      rectangle_i32                          m_rectangle;
      //string                              m_strFont1;
      //string_map < ::image_pointer >      m_pimagemap;
      //::image_pointer                     m_pimage1;
      //::image_pointer                     m_pimage2;
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
      int64_t increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      int64_t decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif


      void initialize(::particle * pparticle) override;


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

      //virtual void draw_arc(::draw2d::graphics_pointer & pgraphics, rectangle_i32 & r, double dStart, double dAngle, bool bPath);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      //virtual void defer_prepare();

      //virtual void _prepare();

      //virtual void draw();

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void start_drawing(context * pgpucontext);
      virtual void global_transform(context * pgpucontext);
      virtual void draw(context * pgpucontext);
      //virtual void render();




   };


} // namespace graphics3d_hello3d



