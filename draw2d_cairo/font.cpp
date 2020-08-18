#include "framework.h"


namespace draw2d_cairo
{


#ifdef WINDOWS


   class font_fam_c2
   {
   public:

      ENUMLOGFONTW lf;

   };

   int CALLBACK EnumFamCallBack(
   _In_ ENUMLOGFONTW   *lpelf,
   _In_ NEWTEXTMETRICW *lpntm,
   _In_ DWORD         FontType,
   _In_ LPARAM        lParam
   )
   {

      font_fam_c2 * pc2 = (font_fam_c2 *)lParam;

      pc2->lf = *lpelf;

      return TRUE;

   }


#endif


   font::font()
   {

      m_pthis = this;

#if defined(USE_PANGO)

      m_pdesc = nullptr;

#else

      m_bToyQuotedFontSelection = false;

      m_pfont = nullptr;
      m_ft = nullptr;
      m_pfontface = nullptr;
      xxf_zero(m_keyDone);

#endif

   }


   font::~font()
   {

      destroy();

   }


   void font::destroy()
   {

      sync_lock ml(cairo_mutex());
//      if(m_pdesc != nullptr)
//      {
// // the fonts are stored and managed by "font cache"
//         cairo_scaled_font_destroy(m_pdesc);
//
//         m_pdesc = nullptr;
//
//      }

//      if(m_pface != nullptr)
//      {
// // the fonts are stored and managed by "font cache"
//         cairo_font_face_destroy(m_pface);
//
//         m_pface = nullptr;
//
//      }

//      if(m_ft != nullptr)
      {

         //FT_Done_Face (m_ft);

         //       m_ft = nullptr;

      }

#if defined(USE_PANGO)

      if(m_pdesc == nullptr)
      {

         pango_font_description_free(m_pdesc);

      }

#else

      if (::is_set(m_pfontface))
      {

         cairo_font_face_destroy(m_pfontface);

      }

#endif

      //return true;

   }


   void font::dump(dump_context & dumpcontext) const
   {

      ::draw2d::font::dump(dumpcontext);

   }


   bool font::create(::draw2d::graphics * pgraphics, i8 iCreate)
   {

#if defined(USE_PANGO)

      m_pdesc = pango_font_description_new();

      pango_font_description_set_family(m_pdesc, m_strFontFamilyName);

      pango_font_description_set_style(m_pdesc, m_bItalic ? PANGO_STYLE_ITALIC : PANGO_STYLE_NORMAL);

      pango_font_description_set_weight(m_pdesc, (PangoWeight)m_iFontWeight);

      if (m_eunitFontSize == ::draw2d::unit_pixel)
      {

         pango_font_description_set_absolute_size(m_pdesc, m_dFontSize * PANGO_SCALE);

      }
      else
      {

         pango_font_description_set_size(m_pdesc, m_dFontSize * PANGO_SCALE);

      }

      m_osdata[0] = m_pdesc;

#elif TOY_FONT_SELECTION

      m_bToyQuotedFontSelection = true;

      toy_font_selection();

#else

      auto pcairographics = __graphics(pgraphics);

      FT_Face ftface = pcairographics->ftface(m_strFontFamilyName);

      if (!ftface)
      {

         toy_font_selection();

      }
      else
      {

         cairo_font_face_t * pfontface = cairo_ft_font_face_create_for_ft_face(ftface, 0);

         cairo_status_t status = cairo_font_face_status(pfontface);

         m_pfontface = pfontface;

         m_osdata[0] = m_pfontface;

      }

#endif

      return m_osdata[0];

   }


   void font::toy_font_selection()
   {

      cairo_font_slant_t slant = get_cairo_font_slant();

      cairo_font_weight_t weight = get_cairo_font_weight();

      cairo_font_face_t* pfontface = cairo_toy_font_face_create(m_strFontFamilyName, slant, weight);

      cairo_status_t status = cairo_font_face_status(pfontface);

      m_pfontface = pfontface;

      m_osdata[0] = m_pfontface;

      if (pfontface)
      {

         m_bToyQuotedFontSelection = true;

      }

   }


   cairo_font_slant_t font::get_cairo_font_slant()
   {

      if (m_bItalic)
      {

         return CAIRO_FONT_SLANT_ITALIC;

      }
      else
      {

         return CAIRO_FONT_SLANT_NORMAL;

      }

   }


   cairo_font_weight_t font::get_cairo_font_weight()
   {

      if (m_iFontWeight >= 700)
      {

         return CAIRO_FONT_WEIGHT_NORMAL;

      }
      else
      {

         return CAIRO_FONT_WEIGHT_BOLD;

      }

   }



   ::e_char_set font::calc_char_set(::draw2d::graphics * pgraphics)
   {

      return ::draw2d::font::calc_char_set(pgraphics);

   }


} // namespace draw2d_cairo



