#pragma once


#include "core/user/user/_.h"
#include "xfplayer_impact_line_selection.h"
#include "acme/prototype/geometry2d/_collection.h"


class CLASS_DECL_CORE xfplayer_impact_line  :
   virtual public ::object
{
public:

   enum EAnimate
   {
      AnimateNoAnimate = 0,
      AnimateRHL = 1 // Rotates Horizontally Left
   };


   enum EEffect
   {
      EffectSimple = 0,
      EffectEmbossed = 1
   };


   bool                                            m_bColonPrefix;


   ::pointer<xfplayer_impact_line_selection>       m_pselection;
   ::u8 *                                          m_lpBitmapData;
   ::pointer<::draw2d::graphics_extension>         m_pgraphicsextension;

   ::collection::index                                           m_iLinkHoverIndex;
   ::collection::index                                           m_iIndex;

   string                                          m_str;
   string                                          m_strPrefix;
   string                                          m_strRoot;
   ::i32_array_base                                       m_iaPosition;

   ::i32_rectangle                                 m_rectangle;

   ::i32                              m_iIndent;
   bool                             m_bPendingLayoutUpdate;
   bool                             m_bVisible;
   bool                             m_bAutoSizeX;
   bool                             m_bAutoSizeY;
   ::i32                              m_iAlign;
   ::user::interaction *            m_puserinteraction;
   xfplayer_impact_linea *              m_pContainer;

   // 08, May 2004 attributes
   ::draw2d::graphics_pointer                m_dc1;
   ::draw2d::bitmap_pointer                  m_bmp1;
   ::write_text::font_pointer                    m_pfont;
   ::write_text::font_pointer                    m_pfontPrefix;
   ::write_text::font_pointer                    m_pfontLink;
   ::color::color                         m_cr;
   ::color::color                         m_colorOutline;
   ::i32_rectangle                           m_rectangleX;
   ::f64                           m_fRateX;
   //LOGFONTW                          m_logfont;


   // 09, Sept 2004 attributes with change inApril 2010 from dcMain/bmpMain to imageMain
   ::image::image_pointer                     m_pimageMain;
   bool                             m_bEnhancedEmboss;
   bool                             m_bCacheEmboss;
   string                           m_strCache;

   // Link
   //LOGFONTW                          m_logfontLink;
   string_array_base                          m_straLink;
   index_array                      m_iaLinkStart;
   index_array                      m_iaLinkEnd;


   ::f64                           m_dXfplayerImpactLineBlend;
   ::i32                              m_nFont;
   ::i32_rectangle                           m_rectangleInvalidate;
   ::i32                              m_iAnimateType;
   ::f64                           m_dAnimateProgress;
   ::f64                           m_dAnimateProgressIncrement;
   ::i32                              m_iTextEffect;
   ::draw2d::pen *                      m_lpPenEmboss;
   ::color::color                         m_colorForeground;
   ::draw2d::pen *                      m_ppenLyricLeft;
   ::draw2d::pen *                      m_ppenLyricRight;
   ::i32_size                             m_sizeLyricMargin;
   ::color::color                         m_colorLyricLeft;
   ::color::color                         m_colorLyricRight;

   xfplayer_impact_line(::user::interaction * puserinteraction);
   //xfplayer_impact_line(const xfplayer_impact_line & line);
   ~xfplayer_impact_line() override;

   virtual void initialize_xfplayer_impact_line(xfplayer_impact_linea * pContainer);

   void set_blend(::f64 d);
   ::write_text::font * GetFont();
   bool CalcChar(const ::i32_point & point, character_count &iChar);
   ::collection::index GetCharLink(character_count iChar);
   bool GetCharLink(string & str, character_count iChar);
   bool CharHasLink(character_count iChar);
   user::enum_line_hit get_link(string & strUrl, const ::i32_point & point);
   ::collection::index GetLinkIndex(::collection::index iLine, character_count iChar);
   bool has_link();
   bool is_hover();
   void update_hover(i32_point & pointCursor);
   void PrepareURLLinks();
   void SetFont(::write_text::font * pfont);

//#ifdef WINDOWS_DESKTOP
//   void GetLogFont(LOGFONTW & lf);
//#endif

   user::enum_line_hit hit_test(const i32_point &pointCursorParam, character_count &iChar);

   void CalcCharsPositions(::draw2d::graphics_pointer & pgraphics, const ::i32_rectangle & rectangle);


   void SetColors(::color32_t color32, ::color::color crOutline);

   void embossed_text_out(
   ::draw2d::graphics_pointer & pgraphics,
   const ::scoped_string & scopedstr,

   ::i32 left,
   ::i32 top,
   ::i32 ignore1,
   ::color32_t color32,
   ::color::color crOutline,
   character_count iLen,
   ::f64 dBlend);

   void embossed_text_out(
   ::draw2d::graphics_pointer & pgraphics,
   ::image::image *pimageCache,
   const ::scoped_string & scopedstr,
   ::i32 iLeft,
   ::i32 iTop,
   ::i32 iWidth,
   ::color32_t color32,
   ::color::color crOutline,
   character_count iLen,
   ::f64 dBlend);


   virtual void CacheEmboss(
   ::draw2d::graphics_pointer & pgraphics,
   const ::scoped_string & scopedstr,
   ::image::image_pointer & imageCache);

   bool IsVisible();
   void Validate(const ::i32_rectangle & rectangle = {});
   void Invalidate(const ::i32_rectangle & rectangle = {});
   //void AddVmsFont(::write_text::font * pfont);
   //::i32 GetVmsFontCount();
   void SetPlacement(const ::i32_rectangle & rectangle);
   ::i32 SetLyricColors(::color::color colorLeft, ::color::color colorRight);
   ::i32 SetLyricPens(::draw2d::pen * ppenLeft, ::draw2d::pen * ppenRight);
   void SetRenderCriticalSection(critical_section *pcs);
   void SetAnimateIncrement(::f64 dIncrement);
   ::i32 MapToFontEffect(::i32 iLineEffect);


   void SetForegroundColor(::color32_t color32);
   void SetEmbossPen(::draw2d::pen * pPen);

   void SetTextEffect(::i32 iTextEffect);

   void SetAnimateType(::i32 iAnimateType);

   void OnTimerAnimate(::draw2d::graphics_pointer & pgraphics, int_rectangle_array_base &   rectaModified);

   void Show(bool bShow = true);
   virtual xfplayer_impact_line & operator = (const xfplayer_impact_line & src);
   void GetPlacement(::i32_rectangle * prectangle);

   void SetPlaement(const ::i32_rectangle & rectangle);
   void SetAlign(::i32 iAlign);
   static const ::i32 AlignLeft;
   static const ::i32 AlignRight;

   void SetAutoSize(bool bAutoSize);



   bool PrepareLine(::draw2d::graphics_pointer & pgraphics, const ::scoped_string & scopedstr, ::i32 flags, const ::i32_rectangle & rectangle);


   void add_char(::wide_character wch, character_count &index);

   void add_char(::wide_character wch, character_count &index, ::write_text::font * pFont);

   bool _001OnDraw(::draw2d::graphics_pointer & pgraphics, bool bDraw, const ::i32_rectangle & rectangle, int_rectangle_array_base & rectaModified, bool bRecalcLayout);

   bool _001OnDraw(::draw2d::graphics_pointer & pgraphics, bool bDraw, const ::i32_rectangle & rectangle, int_rectangle_array_base & rectaModified, character_count * count, bool bRecalcLayout, ::color::color crColor, ::draw2d::pen_pointer sppen);


   DECLARE_MESSAGE_HANDLER(OnMouseMove);
   DECLARE_MESSAGE_HANDLER(OnLButtonDown);
   DECLARE_MESSAGE_HANDLER(OnLButtonUp);
   virtual void on_timer(::timer * ptimer);
   DECLARE_MESSAGE_HANDLER(OnSetCursor);

   xfplayer_impact_line_selection::enum_state GetSelectionState();
   xfplayer_impact_line_selection & GetSelection();
   ::user::interaction * get_interaction();


};



