#include "framework.h"
#include "lock.h"
#include "acme/graphics/image/image32.h"
#include "acme/platform/application.h"
#include "aura/graphics/image/encoding_options.h"
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


bool g_bDraw2dDisableReferencingDebugging = false;


//
//
//namespace aura
//{
//
//
//   extern CLASS_DECL_AURA string_map_base < int_to_string > * g_pmapFontFaceName;
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

      øconstruct_new(m_pimagea);

      //estatus = 

      øconstruct_new(m_papi);

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


   void draw2d::add_image(::image::image *pimage)
   {

      critical_section_lock criticalsectionlock(&m_criticalsectionObjectList);

      m_pimagea->add_image(pimage);

   }


   void draw2d::erase_image(::image::image *pimage)
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


   //void draw2d::on_before_create_window(::windowing::window* pwindow)
   //{


   //}


   //void draw2d::on_create_window(::windowing::window * pwindow)
   //{


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


   class ::write_text::write_text * draw2d::write_text()
   {

      if(!m_pwritetext)
      {

         if (application()->m_bWriteText)
         {

            initialize_write_text();

         }

      }

      return m_pwritetext;

   }


   void draw2d::init1()
   {

      //if (!
      ::acme::department::init1();

      //{

      //   return false;

      //}


      //return true;

   }


   void draw2d::process_init()
   {

      ::acme::department::process_init();

      //_synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

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


   bool draw2d::graphics_context_supports_single_buffer_mode()
   {

      return true;

   }


   bool draw2d::graphics_context_does_full_redraw()
   {

      return false;

   }


   void draw2d::term()
   {

      {

         _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

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


   ::draw2d::graphics_pointer draw2d::create_graphics(::draw2d::host * pdraw2dhost)
   {

      auto pgraphics = pdraw2dhost->øcreate< ::draw2d::graphics>();

      pgraphics->m_pdraw2dhost = pdraw2dhost;

      return ::transfer(pgraphics);

   }


   ::draw2d::graphics_pointer draw2d::create_memory_graphics(::draw2d::host * pdraw2dhost)
   {

      auto pgraphics = create_graphics(pdraw2dhost);

      pgraphics->create_memory_graphics();

      return pgraphics;

   }


   ::draw2d::brush_pointer draw2d::create_solid_brush(const ::color::color & color)
   {

      ::draw2d::brush_pointer pbrush;

      øconstruct(pbrush);

      pbrush->create_solid(color);

      return pbrush;

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

         output_error_message("except", "except", ::user::e_message_box_ok);

      }

      //return ::success;

   }


   void draw2d::embossed_text_out(
      ::draw2d::graphics_pointer & pgraphics,
      const ::int_rectangle & rectangle,
      const ::scoped_string & scopedstrText,
      ::image::fastblur & blur,
      ::image::image_pointer & imageBlur,
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

      if (scopedstrText.is_empty())
      {

         throw ::exception(error_null_pointer);

      }

      auto pred = [&](::draw2d::graphics * pgraphicsParam)
      {

            pgraphicsParam->set(pfont);
            pgraphicsParam->_DrawText(scopedstrText, rectangle, ealign, edrawtext);

      };

      ///bool bRaspiBilbo = scopedstrText.case_insensitive_begins("bilbo-raspi-");

      //if (!bRaspiBilbo)
      {

         emboss_predicate(pgraphics, rectangle, pred, blur, imageBlur, colorGlow, iSpreadRadius, iBlurRadius, iBlur,
                          bUpdate, colorfilter);
      }

      auto opacity = colorfilter.opacity();

      auto pbrushText = øcreate < ::draw2d::brush >();

      pbrushText->create_solid(colorText & opacity);

      pgraphics->set(pbrushText);
      pgraphics->set(pfont);
      pgraphics->_DrawText(scopedstrText, rectangle, ealign, edrawtext);

      //return true;


   }


void draw2d::emboss_predicate(
   ::draw2d::graphics_pointer & pgraphics,
   const ::int_rectangle & rectangle,
   const ::function < void(::draw2d::graphics *) > & functionDraw,
   ::image::fastblur & blur,
   ::image::image_pointer & pimageBlur,
   ::color::color crGlow,
   int iSpreadRadius,
   int iBlurRadius,
   int iBlur,
   bool bUpdate,
   const ::color_filter & colorfilter)
{

   int iR = iSpreadRadius + iBlurRadius + iBlur + 1;

   ::int_rectangle rectangleEmboss = rectangle;

   rectangleEmboss.left() -= (int)(iR * g_dEmboss);
   rectangleEmboss.top() -= (int)(iR * g_dEmboss);
   rectangleEmboss.right() += (int)(iR * g_dEmboss);
   rectangleEmboss.bottom() += (int)(iR * g_dEmboss);

   if (bUpdate || !pimageBlur->is_ok())
   {

      int iEffectiveSpreadRadius = iSpreadRadius;

      int iEffectiveBlurRadius = iBlurRadius;

      const ::int_size & size = rectangleEmboss.size();

      //pimageBlur->initialize(rectangleEmboss, iEffectiveBlurRadius);

      //pimageBlur->fill(0, 0, 0, 0);

      ::int_rectangle rectangleCache;

      rectangleCache.left() = (int)(iR * g_dEmboss);
      rectangleCache.top() = (int)(iR * g_dEmboss);
      rectangleCache.right() = rectangleCache.left() + rectangle.width();

      rectangleCache.bottom() = rectangleCache.top() + rectangle.height();

      ::image::image_pointer pimage;

      //auto estatus =

      øconstruct(pimage);

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

      auto pbrushText = øcreate < ::draw2d::brush >();

      pbrushText->create_solid(argb(255, 255, 255, 255));
      pimage->get_graphics()->set(pbrushText);

      auto shift = rectangleCache.top_left() - rectangle.top_left();

      auto extent = rectangleCache.size();

      pimage->get_graphics()->shift_impact_area(shift, extent);

      functionDraw(pimage->get_graphics());

      pimage->get_graphics()->shift_impact_area(-shift, extent);

      auto psystem = system();

      pimageBlur->create(size);

      blur.initialize(pimageBlur->size(), iEffectiveBlurRadius);

      imaging()->channel_spread_set_color(pimageBlur->g(), {}, size, pimage->g(), {}, ::color::e_channel_red, iEffectiveSpreadRadius, argb(255, 255, 255, 255));

      for (iptr i = 0; i < iBlur; i++)
      {
         
         blur.blur(pimageBlur);

      }

      pimageBlur->set_rgb(crGlow);

      pimageBlur->mult_alpha();

   }

   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   ::image::image_source imagesource(pimageBlur);

   ::image::image_drawing_options imagedrawingoptions(rectangleEmboss);

   imagedrawingoptions = colorfilter;

   ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

   pgraphics->draw(imagedrawing);

   //return true;

}


   void draw2d::alpha_spread__24CC(
      unsigned char * lpbDst, int xDest, int yDest, int wDest, int cx, int cy,
      unsigned char * lpbSrc, int xSrc, int ySrc, int wSrc,
      unsigned char bMin, int iRadius)
   {
      __UNREFERENCED_PARAMETER(xDest);
      __UNREFERENCED_PARAMETER(yDest);
      __UNREFERENCED_PARAMETER(xSrc);
      __UNREFERENCED_PARAMETER(ySrc);
      int iFilterW = iRadius * 2 + 1;
      int iFilterH = iRadius * 2 + 1;
      int iFilterHalfW = iFilterW / 2;
      int iFilterHalfH = iFilterH / 2;
      int iFilterArea = iFilterW * iFilterH;
      //int divisor;
      unsigned char * lpbSource;
      unsigned char * lpbSource_1;
      unsigned char * lpbSource_2;
      unsigned char * lpwDestination;
      unsigned char * lpFilter;
      unsigned char * pFilter;


      int i;
      int x;
      int y;
      int x1;
      int y1;
      int x2;
      int y2;

      int iRadius2 = iRadius * iRadius;
      int r2;

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto & filter = m_alpha_spread__24CC_filterMap[iRadius];

      if (filter.is_set())
      {

         pFilter = filter->begin();

      }
      else
      {

         filter = øallocate memory();

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

               pFilter[x + y * iFilterW] = (unsigned char)i;

               pFilter[iFilterW - 1 - x + y * iFilterW] = (unsigned char)i;

               pFilter[iFilterW - 1 - x + (iFilterH - 1 - y) * iFilterW] = (unsigned char)i;

               pFilter[x + (iFilterH - 1 - y) * iFilterW] = (unsigned char)i;

            }

         }

      }

      synchronouslock.unlock();

      int maxx1 = cx;
      int maxy1 = cy;
      int max3x1 = maxx1 * 3;


      unsigned int dwR;
      unsigned int dwG;
      unsigned int dwB;


      int iFilterXLowerBound;
      int iFilterXUpperBound;
      int iFilterYLowerBound;
      int iFilterYUpperBound;

      int yLowerBound[4];
      int yUpperBound[4];
      int xLowerBound[4];
      int xUpperBound[4];

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

      int xL;
      int xU;
      int yL;
      int yU;

      bool bSpread;
      unsigned int bMin3 = bMin * 3;


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
               for (int yFilter = iFilterYLowerBound; yFilter < iFilterYUpperBound; yFilter++)
               {
                  lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
                  lpFilter = pFilter + yFilter * iFilterW + iFilterXLowerBound;
                  for (int xFilter = iFilterXLowerBound; xFilter < iFilterXUpperBound; xFilter++)
                  {
                     if (*lpFilter >= 1)
                     {
                        dwB = lpbSource_2[0];
                        dwG = lpbSource_2[1];
                        dwR = lpbSource_2[2];

                        if (dwR + dwG + dwB > bMin3)
                        {
                           *((unsigned int *)lpwDestination) |= 0x00ffffff;
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

      int iFilterHalfWidth = iFilterW / 2;
      int iFilterHalfWidthBytes = iFilterHalfWidth * 3;

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
            for (int yFilter = iFilterYLowerBound; yFilter <= iFilterYUpperBound; yFilter++)
            {
               lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
               lpFilter = pFilter + yFilter * iFilterW + iFilterXLowerBound;
               for (int xFilter = iFilterXLowerBound; xFilter <= iFilterXUpperBound; xFilter++)
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
               *((unsigned int *)lpwDestination) |= 0x00ffffff;
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


   bool draw2d::channel_spread__32CC(::image::image *pimageDst, ::image::image *pimageSrc, int iChannel, int iRadius, const ::color::color & colorSpreadSetColor)
   {

      pimageDst->map();

      pimageSrc->map();

      int iFilterW = iRadius * 2 + 1;
      int iFilterH = iRadius * 2 + 1;
      int iFilterHalfW = iRadius;
      int iFilterHalfH = iRadius;
      int iFilterArea = iFilterW * iFilterH;
      //int divisor = iFilterW * iFilterH;
      unsigned char * lpbSource;
      unsigned char * lpbSource_1;
      unsigned char * lpbSource_2;
      unsigned char * lpwDestination;
      unsigned char * lpFilter;
      unsigned char * pFilter;

      int i;
      int x;
      int y;
      int x1;
      int y1;
      int x2;
      int y2;

      int iRadiusSquare = iRadius * iRadius;
      int rSquare;


      image32_t u32SpreadSetColor(colorSpreadSetColor, pimageDst->m_colorindexes);


      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto & filter = m_alpha_spread__32CC_filterMap[iRadius];

      if (filter.is_set())
      {
         pFilter = filter->begin();
      }
      else
      {
         filter = øallocate memory();
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
               pFilter[x + y * iFilterW] = (unsigned char)i;
            }
         }
      }

      synchronouslock.unlock();

      int cx = pimageDst->width();
      int cy = pimageDst->height();

      if (cx != pimageSrc->width() || cy != pimageSrc->height())
         return false;

      unsigned char * lpbDst = (unsigned char *)pimageDst->data();
      unsigned char * lpbSrc = (unsigned char *)pimageSrc->data();

      //int wSrc = cx * 4;
      //int wDst = cx * 4;
      int wSrc = pimageSrc->scan_size();
      int wDst = pimageDst->scan_size();

      int maxx1 = cx;
      int maxy1 = cy;
      //   int maxy2 = cy - iFilterW;
      //   int maxy3 = cy - iFilterW / 2;
      int max3x1 = maxx1 * 4;
      //   int max3x2 = (maxx1 - iFilterH) * 4;
      //   int max3x3 = (maxx1 - iFilterH / 2) * 4;
      //int w = cx * 4;

      pimageDst->copy(pimageSrc);
      //::memory_copy(lpbDst,lpbSrc,cx * cy * 4);


      int iFilterXLowerBound;
      int iFilterXUpperBound;
      int iFilterYLowerBound;
      int iFilterYUpperBound;

      int yLowerBound[4];
      int yUpperBound[4];
      int xLowerBound[4];
      int xUpperBound[4];

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

      int xL;
      int xU;
      int yL;
      int yU;


      int xMax = cx - 1;
      int yMax = cy - 1;

      // limits due the filter
      int xMaxFilterBound = xMax - iFilterHalfW;
      int yMaxFilterBound = yMax - iFilterHalfH;

      int xFilterMax = iFilterW - 1;
      int yFilterMax = iFilterH - 1;

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
            if (*((unsigned int *)lpwDestination) != 0xffffffff)
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


                  for (int yFilter = iFilterYLowerBound; yFilter < iFilterYUpperBound; yFilter++)
                  {
                     lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
                     lpFilter = pFilter + yFilter * iFilterW + iFilterXLowerBound;
                     for (int xFilter = iFilterXLowerBound; xFilter < iFilterXUpperBound; xFilter++)
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

      int iFilterHalfWidth = iFilterW / 2;
      int iFilterHalfWidthBytes = iFilterHalfWidth * 4;

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

            if (*((unsigned int *)lpwDestination) != 0xffffffff)
            {
               for (int yFilter = iFilterYLowerBound; yFilter <= iFilterYUpperBound; yFilter++)
               {
                  lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
                  lpFilter = pFilter + yFilter * iFilterW + iFilterXLowerBound;
                  for (int xFilter = iFilterXLowerBound; xFilter <= iFilterXUpperBound; xFilter++)
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

      if(m_pwritetext)
      {

         return;

      }

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

      auto psystem = system();

      //estatus = 

      øconstruct(m_pwritetext);

      //if (!estatus)
      //{

      //   information() << "Couldn't construct aaa_memory_new write_text.";

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

         //if (strDraw2d.has_character())
         //{

         //   strDraw2d.case_insensitive_begins_eat("draw2d_");

         //   strDraw2d.case_insensitive_begins_eat("draw2d");

         //   strLibrary = "draw2d_" + strDraw2d;

         //}

      }

      ::e_status estatus;

      if (strImplementationName.has_character())
      {

         ::pointer<::aura::system>psystem = system();

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

         strImplementationName = system()->implementation_name("write_text", "gdiplus");

#else

         strImplementationName = system()->implementation_name("write_text", "pango");

#endif

      }

      auto psystem = system();

      auto & pfactoryWriteText = psystem->factory("write_text", strImplementationName);

      if (pfactoryWriteText)
      {

         return pfactoryWriteText;

      }


#ifdef WINDOWS_DESKTOP

      if (strImplementationName != system()->implementation_name("write_text", "gdiplus"))
      {

         ::pointer<::aura::system>psystem = system();

         auto & pfactoryWriteText = psystem->factory("write_text", "gdiplus");

         if (pfactoryWriteText)
         {

            return pfactoryWriteText;

         }

      }


      if (strImplementationName != system()->implementation_name("write_text", "direct2d"))
      {

         ::pointer<::aura::system>psystem = system();

         auto & pfactoryWriteText = psystem->factory("write_text", "direct2d");

         if (pfactoryWriteText)
         {

            return pfactoryWriteText;

         }

      }


#endif

      if (strImplementationName != system()->implementation_name("write_text", "pango"))
      {

         auto psystem = system();

         auto & pfactoryWriteText = psystem->factory("write_text", "pango");

         if (pfactoryWriteText)
         {

            return pfactoryWriteText;

         }

      }

      //informationf("No write_text pluging available!!.");
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
#if defined(WINDOWS_DESKTOP)
      return "win32";
#elif defined(LINUX)

      return "pango";

#elif defined(__ANDROID__)

      return "android";

#elif defined(__BSD__)


      return "pango";

#else

      return "write_text";

      //return PLATFORM_COMMON_STRING;

#endif

}


   bool draw2d::lock_device()
   {

      return false;

   }


   void draw2d::unlock_device()
   {


   }


   void draw2d::adjust_composited_window_styles(unsigned int& nExStyle, unsigned int& nStyle)
   {

      ////if (!m_papplication->m_bUseSwapChainWindow)
      //{

      //   nExStyle |= WS_EX_LAYERED;

      //}
      //if (m_papplication->m_bUseSwapChainWindow)
      //{

      //   nExStyle |= WS_EX_NOREDIRECTIONBITMAP;
      //   //nExStyle |= WS_EX_TRANSPARENT;
      //}


   }


} // namespace draw2d


