#include "platform.h"
#include "font.h"
#include "draw2d.h"
#include "graphics.h"
#include "acme/parallelization/synchronous_lock.h"
//#include "aura/graphics/draw2d/host.h"
#include "acme/platform/application.h"



namespace draw2d_cairo
{


#ifdef WINDOWS


   class font_fam_c2
   {
   public:

      ENUMLOGFONTW lf;

   };

   ::i32 CALLBACK EnumFamCallBack(
   _In_ ENUMLOGFONTW   *lpelf,
   _In_ NEWTEXTMETRICW *lpntm,
   _In_ ::u32         FontType,
   _In_ LPARAM        lParam
   )
   {

      font_fam_c2 * pc2 = (font_fam_c2 *)lParam;

      pc2->lf = *lpelf;

      return true;

   }


#endif


   font::font()
   {

      //m_pthis = this;

#if defined(USE_PANGO)

      m_ppangofontdescription = nullptr;

#else

      m_bToyQuotedFontSelection = false;

      m_pcairoscaledfont = nullptr;
      m_ftface = nullptr;
      m_pcairofontface = nullptr;
      zero(m_cairouserdatakeyDone);

#endif

   }


   font::~font()
   {

      destroy();

   }


   void font::destroy()
   {

//#if defined(USE_PANGO)
//
//      // this structure stores a description of the style of font you'd most like
//      PangoFontDescription* m_ppangofontdescription;
//
//#else
//
//      FT_Face                    m_ftface;
//      cairo_user_data_key_t      m_cairouserdatakeyDone;
//      cairo_scaled_font_t* m_pcairoscaledfont;
//
//#endif
//
//      cairo_font_face_t* m_pcairofontface;
//      bool                       m_bToyQuotedFontSelection;

#if defined(USE_PANGO)

      if (m_ppangofontdescription == nullptr)
      {

         pango_font_description_free(m_ppangofontdescription);

      }

#else

      if (::is_set(m_pcairofontface))
      {

         cairo_font_face_destroy(m_pcairofontface);

      }

#endif

      //return ::success;

   }

//
//   void font::destroy()
//   {
//
//      _synchronous_lock ml(::draw2d_cairo::mutex(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
////      if(m_ppangofontdescription != nullptr)
////      {
//// // the fonts are stored and managed by "font cache"
////         cairo_scaled_font_destroy(m_ppangofontdescription);
////
////         m_ppangofontdescription = nullptr;
////
////      }
//
////      if(m_pface != nullptr)
////      {
//// // the fonts are stored and managed by "font cache"
////         cairo_font_face_destroy(m_pface);
////
////         m_pface = nullptr;
////
////      }
//
////      if(m_ftface != nullptr)
//      {
//
//         //FT_Done_Face (m_ftface);
//
//         //       m_ftface = nullptr;
//
//      }
//
//      destroy_os_data();
//
//      ::write_text::font::destroy();
//
//      //return ::success;
//
//   }


//   void font::dump(dump_context & dumpcontext) const
//   {
//
//      ::write_text::font::dump(dumpcontext);
//
//   }


   void font::update(::draw2d::graphics * pdraw2dgraphics)
   {

      bool bFont = false;

      if (m_pathFontFile.has_character())
      {

         ::pointer<::draw2d_cairo::draw2d>pdraw2d = system()->draw2d();

         auto pfontface = pdraw2d->private_ftface_from_file(pdraw2dgraphics->m_papplication, m_pathFontFile);

         m_pcairofontface = pfontface;

         //m_osdata[1] = m_pcairofontface;

         //m_osdata[0] = nullptr;

         return ;

      }

#if defined(USE_PANGO)

      ::i32 iPangoSize = (::i32) (m_fontsize.as_f64() * PANGO_SCALE);

      if(iPangoSize <= 0)
      {

         warning() <<"Invalid size for font: pango_font_description_set_size: assertion 'size >= 0' failed";

         //return false;

         throw ::exception(error_wrong_state);

      }

      m_mapPangoLayout.erase_all();

      m_ppangofontdescription = pango_font_description_new();

      ::f64 dFontScaler = 1.0;

      if(::is_set(pdraw2dgraphics->m_pdraw2dhost))
      {

         dFontScaler = pdraw2dgraphics->m_pdraw2dhost->font_scaler();

      }
      else
      {

         informationf("Warning: No ::user::interaction font scaler!\n");

      }

      pango_font_description_set_family(m_ppangofontdescription, family_name());

      pango_font_description_set_style(m_ppangofontdescription, m_bItalic ? PANGO_STYLE_ITALIC : PANGO_STYLE_NORMAL);

      pango_font_description_set_weight(m_ppangofontdescription, (PangoWeight)m_fontweight.as_i32());

      if (m_fontsize.eunit() == ::e_unit_pixel)
      {

         pango_font_description_set_absolute_size(m_ppangofontdescription, m_fontsize.as_f64() * PANGO_SCALE);

      }
      else
      {

         pango_font_description_set_size(m_ppangofontdescription, m_fontsize.as_f64() * PANGO_SCALE);

      }

      m_osdata[0] = m_ppangofontdescription;

#elif TOY_FONT_SELECTION

      m_bToyQuotedFontSelection = true;

      toy_font_selection();

#else

      auto pcairographics = __graphics(pdraw2dgraphics);

      FT_Face ftface = pcairographics->ftface(
         m_pfontfamily->family_name(pdraw2dgraphics),
         m_fontweight.as_i32(), m_bItalic);

      if (!ftface)
      {

         toy_font_selection();

      }
      else
      {

         cairo_font_face_t * pfontface = cairo_ft_font_face_create_for_ft_face(ftface, 0);

         cairo_status_t status = cairo_font_face_status(pfontface);

         m_pcairofontface = pfontface;

         //m_osdata[1] = m_pcairofontface;

      }

#endif


      //return m_osdata[0];

   }


   void font::toy_font_selection()
   {

      cairo_font_slant_t slant = get_cairo_font_slant();

      cairo_font_weight_t weight = get_cairo_font_weight();

      cairo_font_face_t* pfontface = cairo_toy_font_face_create(
         m_pfontfamily->family_name(this),
         slant, 
         weight);

      cairo_status_t status = cairo_font_face_status(pfontface);

      m_pcairofontface = pfontface;

      //m_osdata[1] = m_pcairofontface;

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

      if (m_fontweight.as_i32() >= 700)
      {

         return CAIRO_FONT_WEIGHT_BOLD;

      }
      else
      {

         return CAIRO_FONT_WEIGHT_NORMAL;

      }

   }



   ::enum_character_set font::calculate_character_set(::draw2d::graphics * pdraw2dgraphics)
   {

      return ::write_text::font::calculate_character_set(pdraw2dgraphics);

   }


} // namespace draw2d_cairo



