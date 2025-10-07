#pragma once


#include "aura/graphics/draw2d/draw2d.h"


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO draw2d  :
      virtual public ::draw2d::draw2d
   {
   public:


      class private_font :
         virtual public ::particle
      {
      public:

         FT_Face  m_ftface;
         cairo_font_face_t  * m_pfontface;

      };

      string_map_base < ::pointer<private_font >>m_mapPrivateFont;

      ::pointer< ::mutex > m_pmutex;

      string_map_base < int_map < FT_Face > >  m_mapFontFace;

      string_to_int_base m_mapFontError;

      string_to_int_base m_pmapFontError2 ;

      string_map_base < cairo_font_face_t * > * m_mapCairoFontFace;


//extern CLASS_DECL_AURA array < matter * > * g_paAura;

#if defined(LINUX) || defined(FREEBSD) || defined(OPENBSD)

      ::pointer< ::mutex > m_pmutexFc;

      string_to_string_base     g_mapFontPath;

#endif

      draw2d();
      ~draw2d() override;


      virtual void initialize(::particle * pparticle) override;

      virtual void process_init() override;

      virtual void init() override;
      virtual void init1() override;

      virtual void term() override;

      virtual void destroy() override;





      cairo_font_face_t * private_ftface_from_memory(const ::block & block, const ::scoped_string & scopedstrName);
      cairo_font_face_t * private_ftface_from_file(::platform::context * pcontext, const ::payload & payloadFile);

#if defined(WINDOWS_DESKTOP)
      void adjust_composited_window_styles(unsigned int& nExStyle, unsigned int& nStyle);
#endif

   };

   
   CLASS_DECL_DRAW2D_CAIRO ::draw2d_cairo::draw2d * get();
   CLASS_DECL_DRAW2D_CAIRO ::particle * mutex();


} // namespace draw2d_cairo


