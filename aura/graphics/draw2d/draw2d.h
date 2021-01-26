#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA draw2d  :
      virtual public ::apex::department
   {
   public:


      static double g_dEmboss;

      bool           m_bSettingCursorMatter;

      i32_map < __pointer(memory) > m_alpha_spread__24CC_filterMap;
      i32_map < __pointer(memory) > m_alpha_spread__32CC_filterMap;


      __pointer(cursor_set)                                    m_pcursorset;
      __pointer(class ::draw2d::api)                           m_papi;
      __pointer(class font_department)                         m_pfontdepartment;

      //__pointer(::mutex)                                        m_pmutexFont;
#ifdef WINDOWS
      __composite(::draw2d_direct2d::plugin)                     m_pplugin;
#endif

      draw2d();
      virtual ~draw2d();


      virtual ::e_status initialize(::layered * pobjectContext) override;

      virtual ::e_status process_init() override;

      virtual ::e_status init() override;
      virtual ::e_status init1() override;

      virtual void term() override;

      virtual void finalize() override;

      virtual class api & api();


#ifdef WINDOWS
      ::draw2d_direct2d::plugin * direct2d();
#endif

      virtual double font_similarity(const char * pszSystem, const char * pszUser);

      e_format file_extension_to_format(const ::payload & varFile);
      e_format text_to_format(string str);
      

      class font_department & fonts();


      __pointer(cursor) get_cursor(e_cursor ecursor);
      virtual bool set_cursor_set_from_matter(const ::file::path& pathDir);


      virtual void term_instance() override;

      virtual bool embossed_text_out(
      ::draw2d::graphics_pointer & pgraphics,
      const ::rect & rect,
      string strText,
      ::draw2d::fastblur & blur,
      ::image_pointer & imageBlur,
      ::draw2d::font * pfont,
      const ::e_align & ealign,
      const ::e_draw_text & edrawtext,
      color32_t crText,
      color32_t crGlow,
      int iSpreadRadius,
      int iBlurRadius,
      int iBlur,
      bool bUpdate,
      const ::color_filter & colorfilter = nullptr);


      template < typename PRED >
      bool emboss_pred(
      ::draw2d::graphics_pointer & pgraphics,
      const ::rect & rect,
      PRED pred,
      ::draw2d::fastblur & blur,
      ::image_pointer & imageBlur,
      color32_t crGlow,
      int iSpreadRadius,
      int iBlurRadius,
      int iBlur,
      bool bUpdate,
      const color_filter & colorfilter = nullptr);

      virtual void alpha_spread__24CC(byte * pbDest, i32 xDest, i32 yDest, i32 wDest, i32 cx, i32 cy, byte * pbSrc, i32 ySrc, i32 xSrc, i32 wSrc, byte bMin, i32 iRadius);

      virtual bool channel_spread__32CC(::image * pimageDst, ::image * pimageSrc, i32 iChannel, i32 iRadius, color32_t crSpreadSetColor);

      virtual void enum_draw2d_fonts(::draw2d::font_enum_item_array& itema);


   };


} // namespace draw2d


