#include "framework.h"
#include "lock.h"
#include "acme/graphics/draw2d/image32.h"
#include "acme/platform/application.h"
#include "aura/graphics/image/save_image.h"
#include "aura/graphics/image/array.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/imaging.h"
#include "aura/graphics/image/fastblur.h"
#include "aura/graphics/image/drawing.h"
#include "graphics.h"
#include "host.h"
#include "brush.h"
#include "draw2d.h"
#include "task_tool.h"

//
//
//namespace aura
//{
//
//
//   extern CLASS_DECL_AURA string_map < int_to_string > * g_pmapFontFaceName;
//
//
//   extern CLASS_DECL_AURA critical_section * g_pcsFont;
//
//
//} // namespace aura


namespace draw2d
{


   double draw2d::g_dEmboss = 2.0;


   draw2d::draw2d()
   {

      m_pimpl = nullptr;

   }


   draw2d::~draw2d()
   {

   }


   void draw2d::initialize(::particle * pparticle)
   {

      //auto estatus = 

      ::acme::department::initialize(pparticle);

      defer_create_synchronization();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      __construct_new(m_pimagea);

      //estatus = 

      __construct_new(m_papi);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //lock::__s_initialize();

      //return estatus;

   }


   void draw2d::add_object(::draw2d::object * pobject)
   {

      critical_section_lock criticalsectionlock(&m_criticalsectionObjectList);

      m_objecta.add(pobject);

   }


   void draw2d::erase_object(::draw2d::object * pobject)
   {
      
      if(::is_null(this))
      {
         
         return;
         
      }

      critical_section_lock criticalsectionlock(&m_criticalsectionObjectList);

      m_objecta.erase(pobject);

   }


   void draw2d::add_image(::image * pimage)
   {

      critical_section_lock criticalsectionlock(&m_criticalsectionObjectList);

      m_pimagea->add_image(pimage);

   }


   void draw2d::erase_image(::image * pimage)
   {

      critical_section_lock criticalsectionlock(&m_criticalsectionObjectList);

      m_pimagea->erase_image(pimage);

   }


   void draw2d::add_graphics(graphics * pgraphics)
   {

      critical_section_lock criticalsectionlock(&m_criticalsectionGraphicsContextList);

      m_graphicsa.add(pgraphics);

   }


   void draw2d::erase_graphics(graphics * pgraphics)
   {

      critical_section_lock criticalsectionlock(&m_criticalsectionGraphicsContextList);

      m_graphicsa.erase(pgraphics);

   }


   //::pointer< ::mutex > draw2d::get_object_list_mutex()
   //{

   //   return m_pmutexObjectList;

   //}


   //::pointer< ::mutex > draw2d::get_image_list_mutex()
   //{

   //   return m_pmutexImageList;

   //}


   //::pointer< ::mutex > draw2d::get_graphics_context_list_mutex()
   //{

   //   return m_pmutexGraphicsContextList;

   //}


   void draw2d::clear_all_objects_os_data()
   {

      clear_object_list_os_data();
      clear_image_list_os_data();
      clear_graphics_context_list_os_data();

   }


   void draw2d::clear_object_list_os_data()
   {

      critical_section_lock criticalsectionlock(&m_criticalsectionObjectList);

      for (auto & pparticle : m_objecta)
      {

         pparticle->destroy_os_data();

      }

   }


   void draw2d::clear_image_list_os_data()
   {

      critical_section_lock criticalsectionlock(&m_criticalsectionImageList);

      for (auto & pimage : m_pimagea->imagea())
      {

         pimage->destroy_os_data();

      }

   }


   void draw2d::clear_graphics_context_list_os_data()
   {

      critical_section_lock criticalsectionlock(&m_criticalsectionGraphicsContextList);

      for (auto & pgraphics : m_graphicsa)
      {

         pgraphics->destroy_os_data();

      }

   }


   api & draw2d::api()
   {

      return *m_papi;

   }


   void draw2d::init1()
   {

      //if (!
      ::acme::department::init1();

      //{

      //   return false;

      //}

      if (acmeapplication()->m_bWriteText)
      {

         initialize_write_text();

      }

      //return true;

   }


   void draw2d::process_init()
   {

      ::acme::department::process_init();

      //synchronous_lock synchronouslock(this->synchronization());

      //if (!m_papi->open())
      //{

      //   return false;

      //}

      //return true;

   }


   void draw2d::init()
   {

      //if (!)
      ::acme::department::init();
      //{

      //   return false;

      //}

      //return true;

   }


   enum_format draw2d::file_extension_to_format(const ::payload & payloadFile)
   {

      return text_to_format(payloadFile.as_file_path().final_extension());

   }


   enum_format draw2d::text_to_format(string strText)
   {

      strText.make_lower();

      if (strText == "png")
      {

         return ::draw2d::e_format_png;

      }
      else if (strText == "jpg" || strText == "jpeg")
      {

         return ::draw2d::e_format_jpeg;

      }
      else if (strText == "gif")
      {

         return ::draw2d::e_format_gif;

      }
      else if (strText == "bmp")
      {

         return ::draw2d::e_format_bmp;

      }
      else
      {

         return ::draw2d::e_format_none;

      }

   }


   void draw2d::term()
   {

      {

         synchronous_lock synchronouslock(this->synchronization());

         try
         {

            if (m_papi)
            {

               m_papi->destroy();

            }

         }
         catch (...)
         {

         }

         m_alpha_spread__24CC_filterMap.erase_all();

         m_alpha_spread__32CC_filterMap.erase_all();

      }

      {

         critical_section_lock criticalsectionlock(&m_criticalsectionObjectList);

         m_objecta.clear();

      }

      {

         critical_section_lock criticalsectionlock(&m_criticalsectionImageList);

         m_pimagea->m_imagea.clear();

      }

      {

         critical_section_lock criticalsectionlock(&m_criticalsectionGraphicsContextList);

            m_graphicsa.clear();

      }

   }


   void draw2d::destroy()
   {

      m_papi.release();

      //lock::__s_finalize();

      //auto estatus = 
      ::acme::department::destroy();

      //return estatus;

   }


   ::pointer<save_image>draw2d::new_save_image(const ::payload & payloadFile, const ::payload & varOptions)
   {

      auto psaveimage = __new(save_image);

      auto psystem = acmesystem()->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto eformat = pdraw2d->text_to_format(varOptions["format"]);

      if (eformat != ::draw2d::e_format_none)
      {

         ::pointer<::aura::system>psystem = acmesystem();

         eformat = pdraw2d->file_extension_to_format(payloadFile.as_file_path());

      }

      if (eformat == ::draw2d::e_format_none)
      {

         psaveimage->m_eformat = ::draw2d::e_format_png;

      }

      if (varOptions["quality"].get_type() == e_type_f64
         || varOptions["quality"].get_type() == e_type_f32)
      {

         psaveimage->m_iQuality = (int)(varOptions["quality"].as_f64() * 100.0);

      }
      else
      {

         psaveimage->m_iQuality = varOptions["quality"].as_i32();

      }

      if (psaveimage->m_iQuality == 0)
      {

         psaveimage->m_iQuality = 100;

      }

      psaveimage->m_iDpi = varOptions["dpi"].as_i32();

      if (psaveimage->m_iDpi == 0)
      {

         psaveimage->m_iDpi = 96;

      }

      return psaveimage;

   }


   ::draw2d::graphics_pointer draw2d::create_graphics(::draw2d::host * pdraw2dhost)
   {

      auto pgraphics = pdraw2dhost->__create< ::draw2d::graphics>();

      pgraphics->m_pdraw2dhost = pdraw2dhost;

      return ::transfer(pgraphics);

   }


   ::draw2d::graphics_pointer draw2d::create_memory_graphics(::draw2d::host * pdraw2dhost)
   {

      auto pgraphics = create_graphics(pdraw2dhost);

      pgraphics->create_memory_graphics();

      return pgraphics;

   }



   // should not call axis class implementation because draw2d::draw2d is inside a n-furcation of user::draw2d
   void draw2d::term_instance()
   {

      try
      {

         ::acme::department::term_instance();

      }
      catch (...)
      {

         output_error_message("except", "except", e_message_box_ok);

      }

      //return ::success;

   }


   void draw2d::embossed_text_out(
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
      const ::color_filter & colorfilter)
   {

      if (strText.is_empty())
      {

         throw ::exception(error_null_pointer);

      }

      auto pred = [&](::draw2d::graphics * pgraphics)
      {

         pgraphics->set(pfont);
         pgraphics->_DrawText(strText, rectangle, ealign, edrawtext);

      };

      emboss_predicate(
         pgraphics,
         rectangle,
         pred,
         blur,
         imageBlur,
         colorGlow,
         iSpreadRadius,
         iBlurRadius,
         iBlur,
         bUpdate,
         colorfilter);

      auto opacity = colorfilter.opacity();

      auto pbrushText = __create < ::draw2d::brush >();

      pbrushText->create_solid(colorText & opacity);

      pgraphics->set(pbrushText);
      pgraphics->set(pfont);
      pgraphics->_DrawText(strText, rectangle, ealign, edrawtext);

      //return true;


   }


void draw2d::emboss_predicate(
   ::draw2d::graphics_pointer & pgraphics,
   const ::rectangle_i32 & rectangle,
   const ::function < void(::draw2d::graphics *) > & functionDraw,
   ::draw2d::fastblur & blur,
   ::image_pointer & pimageBlur,
   ::color::color crGlow,
   int iSpreadRadius,
   int iBlurRadius,
   int iBlur,
   bool bUpdate,
   const ::color_filter & colorfilter)
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

      //pimageBlur->initialize(rectangleEmboss, iEffectiveBlurRadius);

      //pimageBlur->fill(0, 0, 0, 0);

      ::rectangle_i32 rectangleCache;

      rectangleCache.left = (::i32)(iR * g_dEmboss);
      rectangleCache.top = (::i32)(iR * g_dEmboss);
      rectangleCache.right = rectangleCache.left + rectangle.width();

      rectangleCache.bottom = rectangleCache.top + rectangle.height();

      ::image_pointer pimage;

      //auto estatus =

      __construct(pimage);

      //if (!estatus)
      //{

      //   return false;

      //}

      //estatus =

      pimage->create(size);

      //if (!estatus)
      //{

      //   return false;

      //}

      pimage->fill_byte(0);

      auto pbrushText = __create < ::draw2d::brush >();

      pbrushText->create_solid(argb(255, 255, 255, 255));
      pimage->get_graphics()->set(pbrushText);

      pimage->get_graphics()->offset_origin(rectangleCache.left - rectangle.left, rectangleCache.top - rectangle.top);

      functionDraw(pimage->get_graphics());

      pimage->get_graphics()->offset_origin(-rectangleCache.left + rectangle.left, -rectangleCache.top + rectangle.top);

      auto psystem = acmesystem()->m_paurasystem;

      psystem->imaging().channel_spread_set_color(pimageBlur->g(), {}, size, pimage->g(), {}, ::color::e_channel_opacity, iEffectiveSpreadRadius, argb(255, 255, 255, 255));

      for (iptr i = 0; i < iBlur; i++)
      {
         
         blur.initialize(pimageBlur->size(), iEffectiveBlurRadius);

         blur.blur(pimageBlur);

      }

      pimageBlur->clear(crGlow);

      pimageBlur->mult_alpha();

   }

   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   image_source imagesource(pimageBlur);

   image_drawing_options imagedrawingoptions(rectangleEmboss);

   imagedrawingoptions = colorfilter;

   image_drawing imagedrawing(imagedrawingoptions, imagesource);

   pgraphics->draw(imagedrawing);

   //return true;

}


   void draw2d::alpha_spread__24CC(
      ::u8 * lpbDst, i32 xDest, i32 yDest, i32 wDest, i32 cx, i32 cy,
      ::u8 * lpbSrc, i32 xSrc, i32 ySrc, i32 wSrc,
      ::u8 bMin, i32 iRadius)
   {
      UNREFERENCED_PARAMETER(xDest);
      UNREFERENCED_PARAMETER(yDest);
      UNREFERENCED_PARAMETER(xSrc);
      UNREFERENCED_PARAMETER(ySrc);
      i32 iFilterW = iRadius * 2 + 1;
      i32 iFilterH = iRadius * 2 + 1;
      i32 iFilterHalfW = iFilterW / 2;
      i32 iFilterHalfH = iFilterH / 2;
      i32 iFilterArea = iFilterW * iFilterH;
      //i32 divisor;
      ::u8 * lpbSource;
      ::u8 * lpbSource_1;
      ::u8 * lpbSource_2;
      ::u8 * lpwDestination;
      ::u8 * lpFilter;
      ::u8 * pFilter;


      i32 i;
      i32 x;
      i32 y;
      i32 x1;
      i32 y1;
      i32 x2;
      i32 y2;

      i32 iRadius2 = iRadius * iRadius;
      i32 r2;

      synchronous_lock synchronouslock(this->synchronization());

      auto & filter = m_alpha_spread__24CC_filterMap[iRadius];

      if (filter.is_set())
      {

         pFilter = filter->begin();

      }
      else
      {

         filter = __new(memory());

         filter->set_size(iFilterArea);

         pFilter = filter->begin();

         for (y = 0; y <= iFilterHalfH; y++)
         {

            for (x = 0; x <= iFilterHalfW; x++)
            {

               x1 = iFilterHalfW - x;

               y1 = iFilterHalfH - y;

               r2 = x1 * x1 + y1 * y1;

               if (r2 <= iRadius2)
               {

                  i = 1;

               }
               else
               {

                  i = 0;

               }

               pFilter[x + y * iFilterW] = (::u8)i;

               pFilter[iFilterW - 1 - x + y * iFilterW] = (::u8)i;

               pFilter[iFilterW - 1 - x + (iFilterH - 1 - y) * iFilterW] = (::u8)i;

               pFilter[x + (iFilterH - 1 - y) * iFilterW] = (::u8)i;

            }

         }

      }

      synchronouslock.unlock();

      i32 maxx1 = cx;
      i32 maxy1 = cy;
      i32 max3x1 = maxx1 * 3;


      u32 dwR;
      u32 dwG;
      u32 dwB;


      i32 iFilterXLowerBound;
      i32 iFilterXUpperBound;
      i32 iFilterYLowerBound;
      i32 iFilterYUpperBound;

      i32 yLowerBound[4];
      i32 yUpperBound[4];
      i32 xLowerBound[4];
      i32 xUpperBound[4];

      // top
      xLowerBound[0] = 0;
      xUpperBound[0] = cx - 1;
      yLowerBound[0] = 0;
      yUpperBound[0] = iFilterHalfH - 1;

      // left
      xLowerBound[1] = 0;
      xUpperBound[1] = iFilterHalfW - 1;
      yLowerBound[1] = iFilterHalfH;
      yUpperBound[1] = cy - iFilterHalfH - 1;

      // right
      xLowerBound[2] = cx - iFilterHalfW;
      xUpperBound[2] = cx - 1;
      yLowerBound[2] = iFilterHalfH;
      yUpperBound[2] = cy - iFilterHalfH - 1;

      // bottom
      xLowerBound[3] = 0;
      xUpperBound[3] = cx - 1;
      yLowerBound[3] = cy - iFilterHalfW;
      yUpperBound[3] = cy - 1;

      i32 xL;
      i32 xU;
      i32 yL;
      i32 yU;

      bool bSpread;
      u32 bMin3 = bMin * 3;


      for (i = 0; i < 4; i++)
      {
         xL = xLowerBound[i];
         xU = xUpperBound[i];
         yL = yLowerBound[i];
         yU = yUpperBound[i];

         y1 = yL;
         y2 = y1 - iFilterHalfH;
         for (; y1 <= yU;)
         {
            if (y1 < iFilterHalfH)
            {
               iFilterYLowerBound = iFilterHalfH - y1;
            }
            else
            {
               iFilterYLowerBound = 0;
            }
            if (y1 > (cy - iFilterHalfH))
            {
               iFilterYUpperBound = iFilterH - (y1 - (cy - iFilterHalfH)) - 1;
            }
            else
            {
               iFilterYUpperBound = iFilterH - 1;
            }

            lpbSource = lpbSrc + (wSrc * maximum(y2, 0));

            x1 = xL;
            x2 = (x1 - iFilterHalfW) * 3;
            lpwDestination = lpbDst + (wDest * y1) + x1 * 3;
            for (; x1 <= xU;)
            {
               if (x1 < iFilterHalfH)
               {
                  iFilterXLowerBound = iFilterHalfH - x1;
               }
               else
               {
                  iFilterXLowerBound = 0;
               }
               if (x1 > (cx - iFilterHalfH + 1))
               {
                  iFilterXUpperBound = iFilterH - (x1 - (cx - iFilterHalfH + 1));
               }
               else
               {
                  iFilterXUpperBound = iFilterH - 1;
               }

               lpbSource_1 = lpbSource + maximum(x2, 0);


               dwR = 0;
               dwG = 0;
               dwB = 0;
               bSpread = false;
               for (i32 yFilter = iFilterYLowerBound; yFilter < iFilterYUpperBound; yFilter++)
               {
                  lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
                  lpFilter = pFilter + yFilter * iFilterW + iFilterXLowerBound;
                  for (i32 xFilter = iFilterXLowerBound; xFilter < iFilterXUpperBound; xFilter++)
                  {
                     if (*lpFilter >= 1)
                     {
                        dwB = lpbSource_2[0];
                        dwG = lpbSource_2[1];
                        dwR = lpbSource_2[2];

                        if (dwR + dwG + dwB > bMin3)
                        {
                           *((u32 *)lpwDestination) |= 0x00ffffff;
                           goto breakFilter;
                        }
                     }
                     lpFilter++;
                     lpbSource_2 += 3;
                  }
               }
            breakFilter:
               lpwDestination += 3;
               x1++;
               x2 += 3;
            }
            y1++;
            y2++;
         }
      }

      iFilterYLowerBound = 0;
      iFilterYUpperBound = iFilterW - 1;
      iFilterXLowerBound = 0;
      iFilterXUpperBound = iFilterH - 1;

      i32 iFilterHalfWidth = iFilterW / 2;
      i32 iFilterHalfWidthBytes = iFilterHalfWidth * 3;

      yL = iFilterHalfWidth;
      yU = maxy1 - iFilterHalfWidth;
      xL = iFilterHalfWidthBytes;
      xU = max3x1 - iFilterHalfWidthBytes;

      y1 = yL;
      y2 = yL - iFilterHalfWidth;



      /// divisor = (iFilterYUpperBound - iFilterYLowerBound + 1) * (iFilterXUpperBound - iFilterXLowerBound + 1);


      for (; y1 < yU;)
      {
         lpbSource = lpbSrc + (wSrc * y2);

         x1 = xL;
         x2 = xL - iFilterHalfWidthBytes;
         lpwDestination = lpbDst + (wDest * y1) + x1;
         for (; x1 < xU;)
         {
            lpbSource_1 = lpbSource + x2;
            lpFilter = pFilter;

            dwR = 0;
            dwG = 0;
            dwB = 0;
            bSpread = false;
            for (i32 yFilter = iFilterYLowerBound; yFilter <= iFilterYUpperBound; yFilter++)
            {
               lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
               lpFilter = pFilter + yFilter * iFilterW + iFilterXLowerBound;
               for (i32 xFilter = iFilterXLowerBound; xFilter <= iFilterXUpperBound; xFilter++)
               {
                  if (*lpFilter >= 1)
                  {
                     dwB = lpbSource_2[0];
                     dwG = lpbSource_2[1];
                     dwR = lpbSource_2[2];

                     if (dwR + dwG + dwB > bMin3)
                     {
                        bSpread = true;
                        break;
                     }
                  }
                  lpFilter++;
                  lpbSource_2 += 3;
               }
            }

            if (bSpread)
            {
               *((u32 *)lpwDestination) |= 0x00ffffff;
               lpwDestination += 3;
            }
            else
            {
               lpwDestination += 3;
            }
            x1 += 3;
            x2 += 3;
         }
         y1++;
         y2++;
      }

   }


   bool draw2d::channel_spread__32CC(::image * pimageDst, ::image * pimageSrc, i32 iChannel, i32 iRadius, const ::color::color & colorSpreadSetColor)
   {

      pimageDst->map();

      pimageSrc->map();

      i32 iFilterW = iRadius * 2 + 1;
      i32 iFilterH = iRadius * 2 + 1;
      i32 iFilterHalfW = iRadius;
      i32 iFilterHalfH = iRadius;
      i32 iFilterArea = iFilterW * iFilterH;
      //i32 divisor = iFilterW * iFilterH;
      ::u8 * lpbSource;
      ::u8 * lpbSource_1;
      ::u8 * lpbSource_2;
      ::u8 * lpwDestination;
      ::u8 * lpFilter;
      ::u8 * pFilter;

      i32 i;
      i32 x;
      i32 y;
      i32 x1;
      i32 y1;
      i32 x2;
      i32 y2;

      i32 iRadiusSquare = iRadius * iRadius;
      i32 rSquare;


      image32_t u32SpreadSetColor(colorSpreadSetColor, pimageDst->m_colorindexes);


      synchronous_lock synchronouslock(this->synchronization());

      auto & filter = m_alpha_spread__32CC_filterMap[iRadius];

      if (filter.is_set())
      {
         pFilter = filter->begin();
      }
      else
      {
         filter = __new(memory());
         filter->set_size(iFilterArea);
         pFilter = filter->begin();
         for (y = 0; y < iFilterH; y++)
         {
            for (x = 0; x < iFilterW; x++)
            {
               x1 = iFilterHalfW - x;
               y1 = iFilterHalfH - y;
               rSquare = x1 * x1 + y1 * y1;
               if (rSquare <= iRadiusSquare)
                  i = 1;
               else
                  i = 0;
               pFilter[x + y * iFilterW] = (::u8)i;
            }
         }
      }

      synchronouslock.unlock();

      i32 cx = pimageDst->width();
      i32 cy = pimageDst->height();

      if (cx != pimageSrc->width() || cy != pimageSrc->height())
         return false;

      ::u8 * lpbDst = (::u8 *)pimageDst->data();
      ::u8 * lpbSrc = (::u8 *)pimageSrc->data();

      //i32 wSrc = cx * 4;
      //i32 wDst = cx * 4;
      i32 wSrc = pimageSrc->scan_size();
      i32 wDst = pimageDst->scan_size();

      i32 maxx1 = cx;
      i32 maxy1 = cy;
      //   i32 maxy2 = cy - iFilterW;
      //   i32 maxy3 = cy - iFilterW / 2;
      i32 max3x1 = maxx1 * 4;
      //   i32 max3x2 = (maxx1 - iFilterH) * 4;
      //   i32 max3x3 = (maxx1 - iFilterH / 2) * 4;
      //i32 w = cx * 4;

      ::copy_image32(pimageDst, pimageSrc);
      //::memory_copy(lpbDst,lpbSrc,cx * cy * 4);


      i32 iFilterXLowerBound;
      i32 iFilterXUpperBound;
      i32 iFilterYLowerBound;
      i32 iFilterYUpperBound;

      i32 yLowerBound[4];
      i32 yUpperBound[4];
      i32 xLowerBound[4];
      i32 xUpperBound[4];

      // top
      xLowerBound[0] = 0;
      xUpperBound[0] = cx - 1;
      yLowerBound[0] = 0;
      yUpperBound[0] = iFilterHalfH - 1;

      // left
      xLowerBound[1] = 0;
      xUpperBound[1] = iFilterHalfW - 1;
      yLowerBound[1] = iFilterHalfH;
      yUpperBound[1] = cy - iFilterHalfH - 1;

      // right
      xLowerBound[2] = cx - iFilterHalfW;
      xUpperBound[2] = cx - 1;
      yLowerBound[2] = iFilterHalfH;
      yUpperBound[2] = cy - iFilterHalfH - 1;

      // bottom
      xLowerBound[3] = 0;
      xUpperBound[3] = cx - 1;
      yLowerBound[3] = cy - iFilterHalfH;
      yUpperBound[3] = cy - 1;

      i32 xL;
      i32 xU;
      i32 yL;
      i32 yU;


      i32 xMax = cx - 1;
      i32 yMax = cy - 1;

      // limits due the filter
      i32 xMaxFilterBound = xMax - iFilterHalfW;
      i32 yMaxFilterBound = yMax - iFilterHalfH;

      i32 xFilterMax = iFilterW - 1;
      i32 yFilterMax = iFilterH - 1;

      for (i = 0; i < 4; i++)
      {
         xL = xLowerBound[i];
         xU = xUpperBound[i];
         yL = yLowerBound[i];
         yU = yUpperBound[i];

         y1 = yL;
         y2 = y1 - iFilterHalfH;
         for (; y1 <= yU;)
         {
            if (y1 < iFilterHalfH)
            {
               iFilterYLowerBound = iFilterHalfH - y1;
            }
            else
            {
               iFilterYLowerBound = 0;
            }
            if (y1 > yMaxFilterBound)
            {
               iFilterYUpperBound = yFilterMax - (y1 - yMaxFilterBound);
            }
            else
            {
               iFilterYUpperBound = yFilterMax;
            }

            lpbSource = lpbSrc + wSrc * y2;

            x1 = xL;
            x2 = (x1 - iFilterHalfW) * 4;
            lpwDestination = lpbDst + (wDst * y1) + x1 * 4;
            if (*((u32 *)lpwDestination) != 0xffffffff)
            {
               for (; x1 <= xU; x1++)
               {
                  if (x1 < iFilterHalfH)
                  {
                     iFilterXLowerBound = iFilterHalfH - x1;
                  }
                  else
                  {
                     iFilterXLowerBound = 0;
                  }
                  if (x1 > xMaxFilterBound)
                  {
                     iFilterXUpperBound = xFilterMax - (x1 - xMaxFilterBound);
                  }
                  else
                  {
                     iFilterXUpperBound = xFilterMax;
                  }

                  lpbSource_1 = lpbSource + maximum(x2, 0) + iChannel;


                  for (i32 yFilter = iFilterYLowerBound; yFilter < iFilterYUpperBound; yFilter++)
                  {
                     lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
                     lpFilter = pFilter + yFilter * iFilterW + iFilterXLowerBound;
                     for (i32 xFilter = iFilterXLowerBound; xFilter < iFilterXUpperBound; xFilter++)
                     {
                        if (*lpFilter >= 1)
                        {
                           if (lpbSource_2[0] > 0)
                           {
                              *((image32_t *)lpwDestination) = u32SpreadSetColor;
                              goto breakFilter;
                           }
                        }
                        lpFilter++;
                        lpbSource_2 += 4;
                     }
                  }
               breakFilter:
                  lpwDestination += 4;
                  x2 += 4;
               }
            }
            y1++;
            y2++;
         }
      }

      iFilterYLowerBound = 0;
      iFilterYUpperBound = iFilterW - 1;
      iFilterXLowerBound = 0;
      iFilterXUpperBound = iFilterH - 1;

      i32 iFilterHalfWidth = iFilterW / 2;
      i32 iFilterHalfWidthBytes = iFilterHalfWidth * 4;

      yL = iFilterHalfWidth;
      yU = maxy1 - iFilterHalfWidth;
      xL = iFilterHalfWidthBytes;
      xU = max3x1 - iFilterHalfWidthBytes;

      y1 = yL;
      y2 = yL - iFilterHalfWidth;



      //divisor = (iFilterYUpperBound - iFilterYLowerBound + 1) * (iFilterXUpperBound - iFilterXLowerBound + 1);


      for (; y1 < yU;)
      {
         lpbSource = lpbSrc + (wSrc * y2) + iChannel;

         x1 = xL;
         x2 = xL - iFilterHalfWidthBytes;
         lpwDestination = lpbDst + (wDst * y1) + x1;
         for (; x1 < xU;)
         {
            lpbSource_1 = lpbSource + x2;
            lpFilter = pFilter;

            if (*((u32 *)lpwDestination) != 0xffffffff)
            {
               for (i32 yFilter = iFilterYLowerBound; yFilter <= iFilterYUpperBound; yFilter++)
               {
                  lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
                  lpFilter = pFilter + yFilter * iFilterW + iFilterXLowerBound;
                  for (i32 xFilter = iFilterXLowerBound; xFilter <= iFilterXUpperBound; xFilter++)
                  {
                     if (*lpFilter >= 1)
                     {
                        if (lpbSource_2[0] > 0)
                        {
                           *((image32_t *)lpwDestination) = u32SpreadSetColor;
                           goto breakFilter2;
                        }
                     }
                     lpFilter++;
                     lpbSource_2 += 4;
                  }
               }
            }
         breakFilter2:
            lpwDestination += 4;
            x1 += 4;
            x2 += 4;
         }
         y1++;
         y2++;
      }

      return true;
   }


   void draw2d::initialize_write_text()
   {

      ::e_status estatus = ::success;

      try
      {

         auto & pfactoryWriteText = write_text_factory();

         if (pfactoryWriteText)
         {

            pfactoryWriteText->merge_to_global_factory();

         }
         else
         {

            output_error_message("Failed to initialize write_text library.");

            //pfactoryWriteText = (const ::extended::status &) error_failed;

         }

      }
      catch (...)
      {

         estatus = error_exception;

      }

      //if (!estatus)
      //{

      //   information() << "write_text factory_item exchange has failed.\n\nSome reasons:\n   - No write_text library present;\n   - Failure to open any suitable write_text library.";

      //   //return estatus;

      //}

      auto psystem = acmesystem();

      //estatus = 

      __construct(m_pwritetext);

      //if (!estatus)
      //{

      //   information() << "Couldn't construct memory_new write_text.";

      //   return estatus;

      //}

      //estatus =

      m_pwritetext->init1();

      //if (!estatus)
      //{

      //   information() << "Couldn't initialize write_text (init1).";

      //   return estatus;

      //}

      //if (::succeeded(estatus))
      //{

      factory()->add_factory_item < ::draw2d::task_tool_item >(::e_task_tool_draw2d);

      //}

      //return estatus;

   }


   ::pointer<::factory::factory>& draw2d::write_text_factory()
   {

      string strImplementationName;

      if (has_property("write_text"))
      {

         strImplementationName = payload("write_text");

         //strDraw2d.trim();

         //if (strDraw2d.has_char())
         //{

         //   strDraw2d.case_insensitive_begins_eat("draw2d_");

         //   strDraw2d.case_insensitive_begins_eat("draw2d");

         //   strLibrary = "draw2d_" + strDraw2d;

         //}

      }

      ::e_status estatus;

      if (strImplementationName.has_char())
      {

         ::pointer<::aura::system>psystem = acmesystem();

         auto & pfactoryWriteText = psystem->factory("write_text", strImplementationName);

         if (pfactoryWriteText)
         {

            return pfactoryWriteText;

         }

      }

      strImplementationName = write_text_get_default_implementation_name();

      if (strImplementationName.is_empty())
      {

#ifdef WINDOWS

         strImplementationName = acmesystem()->implementation_name("write_text", "gdiplus");

#else

         strImplementationName = acmesystem()->implementation_name("write_text", "pango");

#endif

      }

      auto psystem = acmesystem();

      auto & pfactoryWriteText = psystem->factory("write_text", strImplementationName);

      if (pfactoryWriteText)
      {

         return pfactoryWriteText;

      }


#ifdef WINDOWS_DESKTOP

      if (strImplementationName != acmesystem()->implementation_name("write_text", "gdiplus"))
      {

         ::pointer<::aura::system>psystem = acmesystem();

         auto & pfactoryWriteText = psystem->factory("write_text", "gdiplus");

         if (pfactoryWriteText)
         {

            return pfactoryWriteText;

         }

      }


      if (strImplementationName != acmesystem()->implementation_name("write_text", "direct2d"))
      {

         ::pointer<::aura::system>psystem = acmesystem();

         auto & pfactoryWriteText = psystem->factory("write_text", "direct2d");

         if (pfactoryWriteText)
         {

            return pfactoryWriteText;

         }

      }


#endif

      if (strImplementationName != acmesystem()->implementation_name("write_text", "pango"))
      {

         auto psystem = acmesystem();

         auto & pfactoryWriteText = psystem->factory("write_text", "pango");

         if (pfactoryWriteText)
         {

            return pfactoryWriteText;

         }

      }

      //infomration("No write_text pluging available!!.");
      if (pfactoryWriteText)
      {

         return pfactoryWriteText;

      }

      throw ::exception(error_resource, "No write_text pluging available!!");

      //destroy:

      //   PFN_factory ([a-z0-9_]+)_factory = plibrary->get < PFN_factory >("([a-z0-9_]+)_factory");

      //   if (([a-z0-9_]+)_factory == nullptr)
      //   {

      //      return false;

      //   }

      //   ([a-z0-9_]+)_factory(::factory::factory * pfactory);

      //   return true;

   //#endif

   }


   string draw2d::write_text_get_default_implementation_name()
   {

#ifdef LINUX

      return "pango";

#elif defined(ANDROID)

      return "android";

#elif defined(FREEBSD)

      return "pango";

#else

      return "write_text";

      //return PLATFORM_COMMON_STRING;

#endif

}


   void draw2d::lock_device()
   {

      //return ::success;

   }


   void draw2d::unlock_device()
   {

      //return ::success;

   }


} // namespace draw2d


enum_rotate_flip exif_orientation_rotate_flip(int orientation)
{


   switch (orientation)
   {
   case 1:
      return e_rotate_none_flip_none;
   case 2:
      return e_rotate_none_flip_x;
   case 3:
      return e_rotate_180_flip_none;
   case 4:
      return e_rotate_180_flip_x;
   case 5:
      return e_rotate_90_flip_x;
   case 6:
      return e_rotate_90_flip_none;
   case 7:
      return e_rotate_270_flip_x;
   case 8:
      return e_rotate_270_flip_none;
   default:
      return e_rotate_none_flip_none;
   }


}



