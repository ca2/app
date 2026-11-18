// Created by camilo on 2026-11-01 20:22 <3ThomasBorregaardSorensen!! Mummi!! bilbo!!
#pragma once


#include "acme/prototype/collection/string_map.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "apex/platform/app_consumer.h"
#include "bred/gpu/render.h"
#include "bred/platform/application.h"


namespace user
{


   class CLASS_DECL_BRED gpu_shader_render :
      virtual public app_consumer < ::bred::application, ::gpu::render >
   {
   public:


      string                              m_strShaderPath;
      bool                                m_bUpdateShader;
      bool                                m_bLoggedReadback = false;
      string                              m_strProjection;
      string                              m_strFragment;
      ::pointer<::gpu::model_buffer>       m_pmodelbufferFullscreen;
      //i32_rectangle                       m_rectangle;
      string                              m_strFont1;
      string_map_base < ::image::image_pointer >      m_pimagemap;
      ::image::image_pointer                     m_pimage1;
      ::image::image_pointer                     m_pimage2;
      ::color::hls                        m_hlsText;
      class ::time                        m_timeStart;
      ::gpu::enum_shader_source           m_eshadersource;
      ::image::image_pointer                     m_pimageLabel;
      string                              m_strLastLabel;
      ::color::color                      m_colorLastLabelBackground;
      ::image::image_pointer                     m_pimageError;
      string                              m_strLastError;

      ::pointer<::user::interaction>     m_puserinteraction;


      gpu_shader_render();
      ~gpu_shader_render() override;


      virtual void initialize_user_gpu_shader_render(::user::gpu_interaction * pusergpuinteraction);

#ifdef _DEBUG
      virtual ::i64 increment_reference_count() override;
      virtual ::i64 decrement_reference_count() override;
#endif

      virtual void update_shader();
      virtual void defer_update_shader();
      virtual void _update_shader();

      virtual ::image::image * drawn_frame_image();

      virtual void on_gpu_draw(::gpu::context * pgpucontext);

      virtual void on_gpu_render(::gpu::context *pgpucontext);

      virtual void _001OnDrawLabel(::draw2d::graphics_pointer & pdraw2dgraphics);

      virtual void _001OnDrawError(::draw2d::graphics_pointer & pdraw2dgraphics);

      virtual void _001OnDraw1Through3(::draw2d::graphics_pointer & pdraw2dgraphics);

      void on_layout(::draw2d::graphics_pointer & pdraw2dgraphics) override;

      virtual void defer_load_fragment(const ::scoped_string & scopedstrPath);


   };


} // namespace app_shader



