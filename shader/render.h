#pragma once


namespace app_shader
{


   class CLASS_DECL_APP_SHADER render :
      virtual public __application_consumer
   {
   public:


      string                              m_strShaderPrefix;
      bool                                m_bUpdateShader;
      string                              m_strProjection;
      string                              m_strFragment;
      __pointer(::gpu::context)      m_pcontext;
      __pointer(::gpu::program)      m_pprogram;
      rectangle_i32                                m_rectangle;
      ::user::interaction *               m_pinteraction;
      string                              m_strFont1;
      string_map < ::image_pointer >      m_pimagemap;
      ::image_pointer                     m_pimage1;
      ::image_pointer                     m_pimage2;
      ::color::hls                               m_hlsText;
      ::millis                              m_millisStart;
      ::gpu::enum_shader_source           m_eshadersource;

      render();
      virtual ~render();


      virtual ::e_status initialize(::context_object * pcontextobject) override;

#ifdef DEBUG
      virtual int64_t add_ref(OBJ_REF_DBG_PARAMS) override;
      virtual int64_t dec_ref(OBJ_REF_DBG_PARAMS) override;
#endif

      virtual ::e_status update_shader();
      virtual void defer_update_shader();
      virtual ::e_status _update_shader();

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnDraw1Through3(::draw2d::graphics_pointer & pgraphics);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      virtual void defer_load_fragment(const char* pszPath);


   };


} // namespace app_shader



