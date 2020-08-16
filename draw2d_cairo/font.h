#pragma once


#if defined(USE_PANGO)

#include <pango/pangocairo.h>

#endif


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO font :
      virtual public ::draw2d::font
   {
   public:

#if defined(USE_PANGO)

      // this structure stores a description of the style of font you'd most like
      PangoFontDescription *        m_pdesc;

#else

      FT_Face                    m_ft;
      cairo_user_data_key_t      m_keyDone;
      cairo_scaled_font_t *      m_pfont;

#endif

      cairo_font_face_t *        m_pfontface;
      bool                       m_bToyQuotedFontSelection;


      font();
      virtual ~font();


      virtual bool create(::draw2d::graphics * pgraphics, ::index iCreate) override;
      virtual void destroy() override;


      virtual void dump(dump_context & dumpcontext) const override;

      virtual ::e_char_set calc_char_set(::draw2d::graphics * pgraphics) override;

      virtual cairo_font_slant_t get_cairo_font_slant();
      virtual cairo_font_weight_t get_cairo_font_weight();

      virtual void toy_font_selection();


   };


} // namespace draw2d_cairo



