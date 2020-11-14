#pragma once


#include "aura/const/charset.h"


enum enum_font_weight
{

   e_font_weight_dont_care =           0,
   e_font_weight_thin =                100,
   e_font_weight_extra_light =         200,
   e_font_weight_light =               300,
   e_font_weight_normal =              400,
   e_font_weight_medium =              500,
   e_font_weight_semibold =            600,
   e_font_weight_bold =                700,
   e_font_weight_extra_bold =          800,
   e_font_weight_heavy =               900,

};

typedef comparable_array < e_char_set > char_set_array;


namespace draw2d
{



   class CLASS_DECL_AURA text_metric
   {
   public:


      ::i32          tmHeight;
      ::i32          tmAscent;
      ::i32          tmDescent;
      ::i32          tmInternalLeading;
      ::i32          tmExternalLeading;
      ::i32          tmWeight;
      ::i32          tmOverhang;
      ::i32          tmDigitizedAspectX;
      ::i32          tmDigitizedAspectY;
      widechar       tmFirstChar;
      widechar       tmLastChar;
      widechar       tmDefaultChar;
      widechar       tmBreakChar;
      byte           tmItalic;
      byte           tmUnderlined;
      byte           tmStruckOut;
      byte           tmPitchAndFamily;
      byte           tmCharSet;

   };


   class CLASS_DECL_AURA font :
      virtual public ::draw2d::object
   {
   public:


      class text
      {
      public:

         sized       m_size;
         bool        m_bSize;
         wstring     m_wstr;
         void *      m_osdata[4];

         text()
         {

            m_bSize = false;

         }

      };


      string                  m_strFontFamilyName;
      double                  m_dFontSize;
      double                  m_dFontWidth;
      e_unit                  m_eunitFontSize;
      i32                     m_iFontWeight;
      bool                    m_bItalic;
      bool                    m_bUnderline;
      bool                    m_bStrikeout;
      char_set_array          m_echarseta;
      e_char_set              m_echarset;
      e_text_rendering_hint   m_etextrenderinghint;
      text_metric             m_textmetric;
      bool                    m_bTextMetric;
      string_map < text >     m_mapText;


      font();
      font(const font & font);
      virtual ~font();

      virtual void dump(dump_context & dumpcontext) const override;

      virtual bool create_pixel_font(
      const char * pszFacename,
      double dSize,
      i32 iWeight = 400,
      bool bItalic = false,
      bool bUnderline = false,
      bool bStrikeOut = false,
      double dWidth = 1.0);

      virtual bool create_point_font(
      const char * pszFacename,

      double dSize,
      i32 iWeight = 400,
      bool bItalic = false,
      bool bUnderline = false,
      bool bStrikeOut = false,
      double dWidth = 1.0);

      virtual void destroy() override;

      font & operator = (const font & font);

      virtual void set_family_name(const char * pszFamilyName);
      virtual void set_size(double dSize, e_unit = unit_point);
      virtual void set_bold(bool bBold = true);
      virtual void set_italic(bool bItalic = true);
      virtual void set_underline(bool bUnderline = true);
      virtual void set_strikeout(bool bStrikeout = true);

      virtual e_char_set calc_char_set(::draw2d::graphics * pgraphics);
      virtual e_char_set get_char_set(::draw2d::graphics * pgraphics);
      virtual string get_sample_text(::draw2d::graphics * pgraphics);

      static string get_sample_text(e_char_set echarsset);

      virtual double get_pixel_font_height(::draw2d::graphics * pgraphics);

      virtual bool get_text_metric(::draw2d::graphics * pgraphics, text_metric & tm);

      virtual bool _get_text_metric(::draw2d::graphics * pgraphics, text_metric & tm);

      virtual double get_ascent(::draw2d::graphics * pgraphics);

      virtual double get_descent(::draw2d::graphics * pgraphics);

      virtual double get_leading(::draw2d::graphics * pgraphics);

      virtual double get_height(::draw2d::graphics * pgraphics);

#ifdef WINDOWS

      virtual bool GetLogFont(LOGFONTW * pfontw);

#endif

   };


   typedef ___pointer < font > font_pointer;

#ifdef WINDOWS

   CLASS_DECL_AURA void wingdi_enum_fonts(::draw2d::font_enum_item_array & itema, bool bRaster, bool bTrueType, bool bOther);
   CLASS_DECL_AURA ::e_char_set wingdi_get_cs(int iCharSet);

#endif

   class CLASS_DECL_AURA font_enum_item :
      virtual public context_object
   {
   public:


      string                  m_strFile;
      string                  m_strName;
#ifdef WINDOWS
      wstring                 m_wstrName;
#endif
      char_set_array          m_echarseta;


      font_enum_item();
#ifdef WINDOWS
      font_enum_item(const widechar* pwideszName);
#endif
      font_enum_item(string strName);
      font_enum_item(string strFile, string strName);
      virtual ~font_enum_item();

      bool operator < (const font_enum_item& item) const
      {

         int iCompare = m_strName.compare(item.m_strName);

         if (iCompare < 0)
            return true;

         if (iCompare > 0)
            return false;

         //iCompare = ((int)m_echarset) - ((int) item.m_echarset);

         //if (iCompare < 0)
         // return true;

         //if (iCompare > 0)
         // return false;

         return m_strFile.compare(item.m_strFile);

      }

      bool operator == (const font_enum_item& item) const
      {

         return m_strFile == item.m_strFile
            && m_strName == item.m_strName;
         //                   && m_echarset == item.m_echarset;

      }

      bool operator != (const font_enum_item& item) const { return !this->operator==(item); }

   };


   using enum_item_array = __pointer_array(font_enum_item);


   inline font_pointer point_font(const char * pszFontName, double dFontSize, int iFontWeight = e_font_weight_normal)
   {

      auto pfont = ::__create < font >();

      pfont->create_point_font(pszFontName, dFontSize, iFontWeight);

      return pfont;

   }


} // namespace draw2d






