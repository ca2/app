#pragma once


#include "_constant.h"
#include "text_metric.h"
#include "font_family.h"
#include "acme/graphics/write_text/font_size.h"
#include "acme/graphics/write_text/font_weight.h"
#include "acme/prototype/geometry2d/size.h"
#include "aura/graphics/draw2d/object.h"


//#include "acme/prototype/geometry2d/_geometry2d.h"



//#include "acme/constant/character_set.h"


//#include "acme/prototype/collection/comparable_eq_array.h"
//#include "acme/prototype/collection/comparable_array.h"


#include "acme/prototype/collection/string_map.h"


//#include "acme/filesystem/filesystem/path.h"


#include "font_descriptor.h"


namespace write_text
{

   

#define WRITE_TEXT_TEXT_METRIC_INDEX 7

   class CLASS_DECL_AURA font :
      virtual public ::draw2d::object
   {
   public:


      class CLASS_DECL_AURA text
      {
      public:


         enum enum_size
         {
            e_size_word_break,
            e_size_end_ellipsis,
            e_size_case_3,
            e_size_unbounded,
            e_size_backend_draw_text,
            e_size_count,

         };

         class CLASS_DECL_AURA item
         {
         protected:
            bool m_bHasSize = false;
            double_size m_size;
            wstring     m_wstr;
         public:

            bool has_size() const;

            ::double_size get_size() const;

            void set_size(const ::double_size &size);

            void set_text(const ::scoped_string & scopedstr);

            ::wstring get_text() const;

         };


      private:

         item m_itema[e_size_count];

      public:


         void *            m_osdata[4];

         text();

         item * get_item(enum_size esize);



      };

      static ::mutex *s_pmutexFontTextMap;

      //string                        m_strFontFamilyName;
      font_family_pointer           m_pfontfamily;
      ::file::path                  m_path;
      font_descriptor               m_fontdescriptor;
      //double                        m_dFontSize;
      double                        m_dFontWidth;
      font_size                     m_fontsize;
      font_weight                   m_fontweight;
      bool                          m_bItalic;
      bool                          m_bUnderline;
      bool                          m_bStrikeout;
      enum_character_set_array      m_echaracterseta;
      enum_character_set            m_echaracterset;
      ///enum_rendering                m_erendering;
      text_metric                   m_textmetric2;
      bool                          m_bCacheLayout;

      //bool                          m_bTextMetric;
      string_map_base < text >           m_mapFontText;


      font();
      font(const font & font);
      ~font() override;


      // void dump(dump_context & dumpcontext) const override;
      
      virtual void create_text_metrics(::draw2d::graphics * pgraphics);

      virtual bool create_font(
      const font_family_pointer & pfontfamily,
      const font_size & fontsize,
      const font_weight & fontweight = e_font_weight_normal,
      bool bItalic = false,
      bool bUnderline = false,
      bool bStrikeOut = false,
      double dWidth = 1.0);
      
      
      virtual ::string family_name();


      virtual bool defer_load_internal_font(::draw2d::graphics * pgraphics);

      virtual void on_create_internal_font(::draw2d::graphics * pgraphics, ::write_text::internal_font * pinternalfont);
      

      //virtual bool create_point_font(
      //const font_family_pointer & pfontfamily,
      //double dSize,
      //int iWeight = 400,
      //bool bItalic = false,
      //bool bUnderline = false,
      //bool bStrikeOut = false,
      //double dWidth = 1.0);

      void destroy() override;

      font & operator = (const font & font);

      virtual void set_family_name(const ::scoped_string & scopedstrFamilyName);
      virtual void set_size(const font_size & fontsize);
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



