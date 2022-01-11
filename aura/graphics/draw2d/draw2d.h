#pragma once


#include "color_filter.h"


#include "api.h"


#include "aura/graphics/write_text/write_text.h"


#include "image_source.h"


#include "image_drawing.h"


#include "image.h"


#include "imaging.h"


#include "brush.h"


#include "graphics.h"


#include "fastblur.h"


class save_image;


namespace draw2d
{


   class fastblur;


   class CLASS_DECL_AURA draw2d  :
      virtual public ::acme::department
   {
   public:


      static double g_dEmboss;
      void* m_pimpl;

      i32_map < __pointer(memory) > m_alpha_spread__24CC_filterMap;
      i32_map < __pointer(memory) > m_alpha_spread__32CC_filterMap;


      __pointer(class ::draw2d::api)                           m_papi;

      //::mutex                                        m_pmutexFont;
//#ifdef WINDOWS
  //    __composite(::draw2d_direct2d::plugin)                     m_pplugin;
//#endif

      __pointer(::write_text::write_text)                      m_pwritetext;



      draw2d();
      ~draw2d() override;


      virtual void initialize(::object * pobject) override;

      virtual void process_init() override;

      virtual void init() override;
      virtual void init1() override;

      virtual void term() override;

      virtual void destroy() override;


      __pointer(save_image) new_save_image(const ::payload& payloadFile, const ::payload& varOptions);


      virtual graphics_pointer create_graphics();

      virtual graphics_pointer create_memory_graphics();

      virtual class api & api();

      inline class ::write_text::write_text * write_text() { return m_pwritetext; }

//#ifdef WINDOWS
  //    ::draw2d_direct2d::plugin * direct2d();
//#endif

      

      e_format file_extension_to_format(const ::payload & payloadFile);
      e_format text_to_format(string str);
      
      virtual void initialize_write_text();
      virtual __transport(::factory::factory) & write_text_factory();


      virtual void term_instance() override;


      virtual string write_text_get_default_library_name();

      virtual bool embossed_text_out(
      ::draw2d::graphics_pointer & pgraphics,
      const ::rectangle_i32 & rectangle,
      string strText,
      ::draw2d::fastblur & blur,
      ::image_pointer & imageBlur,
      ::write_text::font * pfont,
      const ::e_align & ealign,
      const ::e_draw_text & edrawtext,
      const ::color::color & colorText,
      const ::color::color & colorGlow,
      int iSpreadRadius,
      int iBlurRadius,
      int iBlur,
      bool bUpdate,
      const ::color_filter & colorfilter = nullptr);


      template < typename PRED >
      bool emboss_predicate(
         ::draw2d::graphics_pointer & pgraphics,
         const ::rectangle_i32 & rectangle,
         PRED pred,
         ::draw2d::fastblur & blur,
         ::image_pointer & pimageBlur,
         ::color::color crGlow,
         int iSpreadRadius,
         int iBlurRadius,
         int iBlur,
         bool bUpdate,
         const ::color_filter & colorfilter = nullptr)
      {

         int iR = iSpreadRadius + iBlurRadius + iBlur + 1;

         ::rectangle_i32 rectangleEmboss = rectangle;

         rectangleEmboss.left -= (::i32)(iR * g_dEmboss);
         rectangleEmboss.top -= (::i32)(iR * g_dEmboss);
         rectangleEmboss.right += (::i32)(iR * g_dEmboss);
         rectangleEmboss.bottom += (::i32)(iR * g_dEmboss);

         if (bUpdate || !pimageBlur->is_ok())
         {

            int iEffectiveSpreadRadius = iSpreadRadius;

            int iEffectiveBlurRadius = iBlurRadius;

            const ::size_i32 & size = rectangleEmboss.size();

            pimageBlur->create(rectangleEmboss);

            pimageBlur->fill(0, 0, 0, 0);

            ::rectangle_i32 rectangleCache;

            rectangleCache.left = (::i32)(iR * g_dEmboss);
            rectangleCache.top = (::i32)(iR * g_dEmboss);
            rectangleCache.right = rectangleCache.left + rectangle.width();

            rectangleCache.bottom = rectangleCache.top + rectangle.height();

            ::image_pointer pimage;

            auto estatus = __construct(pimage);

            if (!estatus)
            {

               return false;

            }

            estatus = pimage->create(size);

            if (!estatus)
            {

               return false;

            }

            pimage->fill(0, 0, 0, 0);

            auto pbrushText = __create < ::draw2d::brush > ();

            pbrushText->create_solid(argb(255, 255, 255, 255));
            pimage->get_graphics()->set(pbrushText);

            pimage->get_graphics()->OffsetViewportOrg(rectangleCache.left - rectangle.left, rectangleCache.top - rectangle.top);

            pred(pimage->get_graphics());

            pimage->get_graphics()->OffsetViewportOrg(-rectangleCache.left + rectangle.left, -rectangleCache.top + rectangle.top);

            __pointer(::aura::system) psystem = m_psystem;

            psystem->imaging().channel_spread_set_color(pimageBlur->g(), nullptr, size, pimage->g(), nullptr, ::color::e_channel_alpha, iEffectiveSpreadRadius, argb(255, 255, 255, 255));

            for (iptr i = 0; i < iBlur; i++)
            {

               blur.blur(pimageBlur, iEffectiveBlurRadius);

            }

            pimageBlur->set_rgb(crGlow);

            pimageBlur->mult_alpha();

         }

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         image_source imagesource(pimageBlur);

         image_drawing_options imagedrawingoptions(rectangleEmboss);

         imagedrawingoptions = colorfilter;

         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);

         return true;

      }


      virtual void alpha_spread__24CC(byte * pbDest, i32 xDest, i32 yDest, i32 wDest, i32 cx, i32 cy, byte * pbSrc, i32 ySrc, i32 xSrc, i32 wSrc, byte bMin, i32 iRadius);

      virtual bool channel_spread__32CC(::image * pimageDst, ::image * pimageSrc, i32 iChannel, i32 iRadius, ::color::color crSpreadSetColor);

      //virtual void enum_draw2d_fonts(::write_text::font_enumeration_item_array& itema);


      virtual void lock_device();
      virtual void unlock_device();



   };


} // namespace draw2d



