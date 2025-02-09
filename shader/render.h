#pragma once


#include "acme/prototype/collection/string_map.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "apex/platform/app_consumer.h"
#include "aura/graphics/gpu/render.h"


namespace app_shader
{


   class CLASS_DECL_APP_SHADER render :
      virtual public app_consumer < application, ::gpu::render >
   {
   public:


      string                              m_strShaderPath;
      bool                                m_bUpdateShader;
      string                              m_strProjection;
      string                              m_strFragment;
      //::pointer<::gpu::context>           m_pgpucontext;
      //::pointer<::gpu::program>           m_pgpuprogram;
      ::image::image_pointer                     m_pimageFromGpu;
      //int_rectangle                       m_rectangle;
      string                              m_strFont1;
      string_map < ::image::image_pointer >      m_pimagemap;
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


      render();
      ~render() override;


      //virtual void initialize_render(::user::interaction * puserinteraction);

#ifdef _DEBUG
      virtual long long increment_reference_count() override;
      virtual long long decrement_reference_count() override;
#endif

      virtual void update_shader();
      virtual void defer_update_shader();
      virtual void _update_shader();

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnDrawLabel(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnDrawError(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnDraw1Through3(::draw2d::graphics_pointer & pgraphics);

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void defer_load_fragment(const ::string & pszPath);


   };


} // namespace app_shader



