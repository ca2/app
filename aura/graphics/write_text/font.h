#pragma once


#include "aura/graphics/draw2d/object.h"
#include "acme/primitive/geometry2d/size.h"
#include "_constant.h"
#include "text_metric.h"


//#include "acme/primitive/geometry2d/_geometry2d.h"



//#include "acme/constant/character_set.h"


//#include "acme/primitive/collection/comparable_eq_array.h"
//#include "acme/primitive/collection/comparable_array.h"


#include "acme/primitive/collection/string_map.h"


//#include "acme/filesystem/filesystem/path.h"


#include "font_descriptor.h"


namespace write_text
{


#define WRITE_TEXT_TEXT_METRIC_INDEX 7

   class CLASS_DECL_AURA font :
      virtual public ::draw2d::object
   {
   public:


      class text
      {
      public:

         size_f64          m_size;
         bool              m_bSize;
         wstring           m_wstr;
         void *            m_osdata[4];

         text()
         {

            m_bSize = false;

         }

      };


      string                        m_strFontFamilyName;
      ::file::path                  m_path;
      font_descriptor               m_fontdescriptor;
      double                        m_dFontSize;
      double                        m_dFontWidth;
      ::draw2d::enum_unit           m_eunitFontSize;
      i32                           m_iFontWeight;
      bool                          m_bItalic;
      bool                          m_bUnderline;
      bool                          m_bStrikeout;
      enum_character_set_array      m_echaracterseta;
      enum_character_set            m_echaracterset;
      ///enum_rendering                m_erendering;
      text_metric                   m_textmetric2;
      bool                          m_bCacheLayout;

      //bool                          m_bTextMetric;
      string_map < text >           m_mapFontText;


      font();
      font(const font & font);
      ~font() override;


      // void dump(dump_context & dumpcontext) const override;
      
      virtual void create_text_metrics(::draw2d::graphics * pgraphics);

      virtual bool create_pixel_font(
      const ::string & strFacename,
      double dSize,
      i32 iWeight = 400,
      bool bItalic = false,
      bool bUnderline = false,
      bool bStrikeOut = false,
      double dWidth = 1.0);

      virtual bool create_point_font(
      const ::string & strFacename,
      double dSize,
      i32 iWeight = 400,
      bool bItalic = false,
      bool bUnderline = false,
      bool bStrikeOut = false,
      double dWidth = 1.0);

      void destroy() override;

      font & operator = (const font & font);

      virtual void set_family_name(const ::string & pszFamilyName);
      virtual void set_size(double dSize, ::draw2d::enum_unit = ::draw2d::e_unit_point);
      virtual void set_bold(bool bBold = true);
      virtual void set_italic(bool bItalic = true);
      virtual void set_underline(bool bUnderline = true);
      virtual void set_strikeout(bool bStrikeout = true);

      virtual enum_character_set calculate_character_set(::draw2d::graphics * pgraphics);
      virtual enum_character_set get_character_set(::draw2d::graphics * pgraphics);
      virtual string get_sample_text(::draw2d::graphics * pgraphics);
      
      
      virtual string get_font_descriptor_face();


      //string get_sample_text(enum_character_set echarsset);

      virtual double get_pixel_font_height(::draw2d::graphics * pgraphics);

      virtual void get_text_metric(::draw2d::graphics * pgraphics, text_metric & tm);

      virtual void _get_text_metric(::draw2d::graphics * pgraphics, text_metric & tm);

      virtual double get_ascent(::draw2d::graphics * pgraphics);

      virtual double get_descent(::draw2d::graphics * pgraphics);

      virtual double get_leading(::draw2d::graphics * pgraphics);

      virtual double get_height(::draw2d::graphics * pgraphics);

      inline text_metric * get_text_metric_struct()  { return (text_metric*) m_osdata[WRITE_TEXT_TEXT_METRIC_INDEX]; }
      inline const text_metric * get_text_metric_struct() const { return (text_metric*) m_osdata[WRITE_TEXT_TEXT_METRIC_INDEX]; }
      inline bool has_text_metric() const { return m_baCalculated[WRITE_TEXT_TEXT_METRIC_INDEX];}
      inline void set_has_text_metric() { m_osdata[WRITE_TEXT_TEXT_METRIC_INDEX] = &m_textmetric2; m_baCalculated[WRITE_TEXT_TEXT_METRIC_INDEX] = true; }


   };


   typedef ::pointer<font>font_pointer;




} // namespace write_text



