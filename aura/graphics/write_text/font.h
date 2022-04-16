#pragma once


#include "acme/constant/character_set.h"


#include "aura/graphics/draw2d/object.h"


#include "text_metric.h"


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

typedef comparable_array < enum_character_set > enum_character_set_array;


namespace write_text
{


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
      text_metric                   m_textmetric;
      bool                          m_bTextMetric;
      string_map < text >           m_mapText;


      font();
      font(const font & font);
      ~font() override;


      void dump(dump_context & dumpcontext) const override;


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


      static string get_sample_text(enum_character_set echarsset);

      virtual double get_pixel_font_height(::draw2d::graphics * pgraphics);

      virtual void get_text_metric(::draw2d::graphics * pgraphics, text_metric & tm);

      virtual void _get_text_metric(::draw2d::graphics * pgraphics, text_metric & tm);

      virtual double get_ascent(::draw2d::graphics * pgraphics);

      virtual double get_descent(::draw2d::graphics * pgraphics);

      virtual double get_leading(::draw2d::graphics * pgraphics);

      virtual double get_height(::draw2d::graphics * pgraphics);


   };


   typedef ___pointer < font > font_pointer;




} // namespace write_text



