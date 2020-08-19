#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA draw2d  :
      virtual public ::aura::department
   {
   public:


      static double g_dEmboss;

      bool           m_bSettingCursorMatter;

      map < i32, i32, __pointer(memory) > m_alpha_spread__24CC_filterMap;
      map < i32, i32, __pointer(memory) > m_alpha_spread__32CC_filterMap;


      __pointer(cursor_set)                                     m_pcursorset;
      __pointer(class ::draw2d::api)                            m_papi;
      __pointer(class font_department)                          m_pfontdepartment;



      draw2d();
      virtual ~draw2d();


      virtual void construct(::object * pobject);

      virtual ::estatus process_init() override;

      virtual ::estatus init() override;
      virtual ::estatus init1() override;

      virtual void term() override;


      virtual class api & api();

      virtual double font_similarity(const char * pszSystem, const char * pszUser);

      e_format file_extension_to_format(const ::var & varFile);
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
      int iDrawTextFlags,
      COLORREF crText,
      COLORREF crGlow,
      int iSpreadRadius,
      int iBlurRadius,
      int iBlur,
      bool bUpdate,
      double dAlpha = 1.0);


      template < typename PRED >
      bool emboss_pred(
      ::draw2d::graphics_pointer & pgraphics,
      const ::rect & rect,
      PRED pred,
      ::draw2d::fastblur & blur,
      ::image_pointer & imageBlur,
      COLORREF crGlow,
      int iSpreadRadius,
      int iBlurRadius,
      int iBlur,
      bool bUpdate,
      double dAlpha = 1.0);

      virtual void alpha_spread__24CC(byte * pbDest, i32 xDest, i32 yDest, i32 wDest, i32 cx, i32 cy, byte * pbSrc, i32 ySrc, i32 xSrc, i32 wSrc, BYTE bMin, i32 iRadius);

      virtual bool channel_spread__32CC(::image * pimageDst, ::image * pimageSrc, i32 iChannel, i32 iRadius, COLORREF crSpreadSetColor);

   };


} // namespace draw2d


