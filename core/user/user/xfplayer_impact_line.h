#pragma once


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
   unsigned char *                                          m_lpBitmapData;
   ::pointer<::draw2d::graphics_extension>         m_pgraphicsextension;

   ::collection::index                                           m_iLinkHoverIndex;
   ::collection::index                                           m_iIndex;

   string                                          m_str;
   string                                          m_strPrefix;
   string                                          m_strRoot;
   ::int_array                                       m_iaPosition;

   ::int_rectangle                                 m_rectangle;

   int                              m_iIndent;
   bool                             m_bPendingLayoutUpdate;
   bool                             m_bVisible;
   bool                             m_bAutoSizeX;
   bool                             m_bAutoSizeY;
   int                              m_iAlign;
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
   ::int_rectangle                           m_rectangleX;
   double                           m_fRateX;
   //LOGFONTW                          m_logfont;


   // 09, Sept 2004 attributes with change inApril 2010 from dcMain/bmpMain to imageMain
   ::image::image_pointer                     m_pimageMain;
   bool                             m_bEnhancedEmboss;
   bool                             m_bCacheEmboss;
   string                           m_strCache;

   // Link
   //LOGFONTW                          m_logfontLink;
   string_array                          m_straLink;
   index_array                      m_iaLinkStart;
   index_array                      m_iaLinkEnd;


   double                           m_dXfplayerImpactLineBlend;
   int                              m_nFont;
   ::int_rectangle                           m_rectangleInvalidate;
   int                              m_iAnimateType;
   double                           m_dAnimateProgress;
   double                           m_dAnimateProgressIncrement;
   int                              m_iTextEffect;
   ::draw2d::pen *                      m_lpPenEmboss;
   ::color::color                         m_colorForeground;
   ::draw2d::pen *                      m_ppenLyricLeft;
   ::draw2d::pen *                      m_ppenLyricRight;
   ::int_size                             m_sizeLyricMargin;
   ::color::color                         m_colorLyricLeft;
   ::color::color                         m_colorLyricRight;

   xfplayer_impact_line(::user::interaction * puserinteraction);
   //xfplayer_impact_line(const xfplayer_impact_line & line);
   ~xfplayer_impact_line() override;

   virtual void initialize_xfplayer_impact_line(xfplayer_impact_linea * pContainer);

   void set_blend(double d);
   ::write_text::font * GetFont();
   bool CalcChar(const ::int_point & point, character_count &iChar);
   ::collection::index GetCharLink(character_count iChar);
   bool GetCharLink(string & str, character_count iChar);
   bool CharHasLink(character_count iChar);
   user::enum_line_hit get_link(string & strUrl, const ::int_point & point);
   ::collection::index GetLinkIndex(::collection::index iLine, character_count iChar);
   bool has_link();
   bool is_hover();
   void update_hover(int_point & pointCursor);
   void PrepareURLLinks();
   void SetFont(::write_text::font * pfont);

//#ifdef WINDOWS_DESKTOP
//   void GetLogFont(LOGFONTW & lf);
//#endif

   user::enum_line_hit hit_test(const int_point &pointCursorParam, character_count &iChar);

   void CalcCharsPositions(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle);


   void SetColors(::color32_t color32, ::color::color crOutline);

   void embossed_text_out(
   ::draw2d::graphics_pointer & pgraphics,
   const string & str,

   int left,
   int top,
   int ignore1,
   ::color32_t color32,
   ::color::color crOutline,
   character_count iLen,
   double dBlend);

   void embossed_text_out(
   ::draw2d::graphics_pointer & pgraphics,
   ::image::image *pimageCache,
   const ::scoped_string & scopedstr,
   int iLeft,
   int iTop,
   int iWidth,
   ::color32_t color32,
   ::color::color crOutline,
   character_count iLen,
   double dBlend);


   virtual void CacheEmboss(
   ::draw2d::graphics_pointer & pgraphics,
   const ::scoped_string & scopedstr,
   ::image::image_pointer & imageCache);

   bool IsVisible();
   void Validate(const ::int_rectangle & rectangle = {});
   void Invalidate(const ::int_rectangle & rectangle = {});
   //void AddVmsFont(::write_text::font * pfont);
   //int GetVmsFontCount();
   void SetPlacement(const ::int_rectangle & rectangle);
   int SetLyricColors(::color::color colorLeft, ::color::color colorRight);
   int SetLyricPens(::draw2d::pen * ppenLeft, ::draw2d::pen * ppenRight);
   void SetRenderCriticalSection(critical_section *pcs);
   void SetAnimateIncrement(double dIncrement);
   int MapToFontEffect(int iLineEffect);


   void SetForegroundColor(::color32_t color32);
   void SetEmbossPen(::draw2d::pen * pPen);

   void SetTextEffect(int iTextEffect);

   void SetAnimateType(int iAnimateType);

   void OnTimerAnimate(::draw2d::graphics_pointer & pgraphics, int_rectangle_array &   rectaModified);

   void Show(bool bShow = true);
   virtual xfplayer_impact_line & operator = (const xfplayer_impact_line & src);
   void GetPlacement(::int_rectangle * prectangle);

   void SetPlaement(const ::int_rectangle & rectangle);
   void SetAlign(int iAlign);
   static const int AlignLeft;
   static const int AlignRight;

   void SetAutoSize(bool bAutoSize);



   bool PrepareLine(::draw2d::graphics_pointer & pgraphics, string str, int flags, const ::int_rectangle & rectangle);


   void add_char(::wide_character wch, character_count &index);

   void add_char(::wide_character wch, character_count &index, ::write_text::font * pFont);

   bool _001OnDraw(::draw2d::graphics_pointer & pgraphics, bool bDraw, const ::int_rectangle & rectangle, int_rectangle_array & rectaModified, bool bRecalcLayout);

   bool _001OnDraw(::draw2d::graphics_pointer & pgraphics, bool bDraw, const ::int_rectangle & rectangle, int_rectangle_array & rectaModified, character_count * count, bool bRecalcLayout, ::color::color crColor, ::draw2d::pen_pointer sppen);


   DECLARE_MESSAGE_HANDLER(OnMouseMove);
   DECLARE_MESSAGE_HANDLER(OnLButtonDown);
   DECLARE_MESSAGE_HANDLER(OnLButtonUp);
   virtual void _001OnTimer(::timer * ptimer);
   DECLARE_MESSAGE_HANDLER(OnSetCursor);

   xfplayer_impact_line_selection::enum_state GetSelectionState();
   xfplayer_impact_line_selection & GetSelection();
   ::user::interaction * get_interaction();


};



