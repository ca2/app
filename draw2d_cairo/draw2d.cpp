#include "framework.h"
#include "draw2d.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/prototype/prototype/memory.h"


FT_Library __ftlibrary();




// namespace aura
// {


//    extern CLASS_DECL_AURA string_map < int_to_string > * g_pmapFontFaceName;


//    extern CLASS_DECL_AURA critical_section * g_pcsFont;


// } // namespace aura


namespace draw2d_cairo
{
::draw2d_cairo::draw2d * g_pdraw2dcairo = nullptr;

::draw2d_cairo::draw2d * get()
{
return g_pdraw2dcairo;

}


::particle * mutex()
{

   return get()->m_pmutex;

}
   //double draw2d::g_dEmboss = 2.0;


   draw2d::draw2d()
   {

      g_pdraw2dcairo = this;
      //defer_create_synchronization();

      //m_pmutexFont = __allocate ::pointer < ::mutex > ();

      //add_factory_item < e_cursor_set >();

   }


   draw2d::~draw2d()
   {


   }


   void draw2d::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::draw2d::draw2d::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

      m_pmutex = node()->create_mutex();
      //m_pmutexFc = node()->create_mutex();
      //m_pmutexFont= node()->create_mutex();

      //g_pparticleCairoSynchronization = m_pmutex;

   }


   void draw2d::init1()
   {

      ::draw2d::draw2d::init1();

      //if (!::draw2d::draw2d::init1())
      //{

      //   return false;

      //}

      //return true;

   }


   void draw2d::process_init()
   {

      ::draw2d::draw2d::process_init();

      //if (!::draw2d::draw2d::process_init())
      //{

      //   return false;

      //}

//      synchronous_lock synchronouslock(this->synchronization());
//
//      if (!m_papi->open())
//      {
//
//         return false;
//
//      }

      //return true;

   }


   void draw2d::init()
   {

      ::draw2d::draw2d::init();

      //if (!::draw2d::draw2d::init())
      //{

      //   return false;

      //}

      //return true;

   }


//
//   enum_format draw2d::file_extension_to_format(const ::payload & payloadFile)
//   {
//
//      return text_to_format(payloadFile.get_file_path().final_extension());
//
//   }
//
//   enum_format draw2d::text_to_format(const ::scoped_string & scopedstrText)
//   {
//
//      strText.make_lower();
//
//      if (strText == "png")
//      {
//
//         return ::draw2d::e_format_png;
//
//      }
//      else if (strText == "jpg" || strText == "jpeg")
//      {
//
//         return ::draw2d::e_format_jpeg;
//
//      }
//      else if (strText == "gif")
//      {
//
//         return ::draw2d::e_format_gif;
//
//      }
//      else if (strText == "bmp")
//      {
//
//         return ::draw2d::e_format_bmp;
//
//      }
//      else
//      {
//
//         return ::draw2d::e_format_none;
//
//      }
//
//   }
//

   void draw2d::term()
   {

      synchronous_lock synchronouslock(this->synchronization());

      try
      {

         if (m_papi)
         {

            //m_papi->close();

            m_papi->destroy();

         }

      }
      catch (...)
      {

      }

      m_alpha_spread__24CC_filterMap.erase_all();

      m_alpha_spread__32CC_filterMap.erase_all();

      //return ::success;

   }


   void draw2d::destroy()
   {

      m_papi.release();

      //auto estatus = 
      
      ::draw2d::draw2d::destroy();

      //return estatus;

   }






//
//   // should not call axis class implementation because draw2d::draw2d is inside a n-furcation of user::draw2d
//   void draw2d::term_instance()
//   {
//
//      try
//      {
//
//         ::draw2d::draw2d::term_instance();
//
//      }
//      catch (...)
//      {
//
//         output_error_message("except", "except", e_message_box_ok);
//
//      }
//
//   }
//
//
//   bool draw2d::embossed_text_out(
//   ::draw2d::graphics_pointer & pgraphics,
//   const ::int_rectangle & rectangle,
//   string strText,
//   ::image::fastblur & blur,
//   ::image::image_pointer & imageBlur,
//   ::write_text::font * pfont,
//   const ::e_align & ealign,
//   const ::e_draw_text & edrawtext,
//   color32_t crText,
//   color32_t crGlow,
//   int iSpreadRadius,
//   int iBlurRadius,
//   int iBlur,
//   bool bUpdate,
//   const ::color_filter & colorfilter)
//   {
//
//      if (strText.is_empty())
//      {
//
//         return false;
//
//      }
//
//      auto pred = [&](::draw2d::graphics * pgraphics)
//      {
//
//         pgraphics->set(pfont);
//         pgraphics->_DrawText(strText, *rectangle, ealign, edrawtext);
//
//      };
//
//      emboss_predicate(
//      pgraphics,
//      rectangle,
//      pred,
//      blur,
//      imageBlur,
//      crGlow,
//      iSpreadRadius,
//      iBlurRadius,
//      iBlur,
//      bUpdate,
//      colorfilter);
//
//      auto bA = colorfilter.opacity().get_alpha();
//
//      auto pbrushText = __øcreate < ::draw2d::brush > ();
//      pbrushText->create_solid((crText & 0x00ffffffu) | (bA << 24));
//      pgraphics->set(pbrushText);
//      pgraphics->set(pfont);
//      pgraphics->_DrawText(strText, *rectangle, ealign, edrawtext);
//
//      return true;
//
//   }
//
//   void draw2d::alpha_spread__24CC(
//   unsigned char * lpbDst, int xDest, int yDest, int wDest, int cx, int cy,
//   unsigned char * lpbSrc, int xSrc, int ySrc, int wSrc,
//   unsigned char bMin, int iRadius)
//   {
//      __UNREFERENCED_PARAMETER(xDest);
//      __UNREFERENCED_PARAMETER(yDest);
//      __UNREFERENCED_PARAMETER(xSrc);
//      __UNREFERENCED_PARAMETER(ySrc);
//      int iFilterW = iRadius * 2 + 1;
//      int iFilterH = iRadius * 2 + 1;
//      int iFilterHalfW = iFilterW / 2;
//      int iFilterHalfH = iFilterH / 2;
//      int iFilterArea = iFilterW * iFilterH;
//      int divisor;
//      unsigned char *lpbSource;
//      unsigned char *lpbSource_1;
//      unsigned char *lpbSource_2;
//      unsigned char *lpwDestination;
//      unsigned char *lpFilter;
//      unsigned char *pFilter;
//
//
//      int i;
//      int x;
//      int y;
//      int x1;
//      int y1;
//      int x2;
//      int y2;
//
//      int iRadius2 = iRadius * iRadius;
//      int r2;
//
//      synchronous_lock synchronouslock(this->synchronization());
//
//      auto & filter = m_alpha_spread__24CC_filterMap[iRadius];
//
//      if (filter.is_set())
//      {
//
//         pFilter = filter->get_data();
//
//      }
//      else
//      {
//
//         filter = __allocate memory();
//
//         filter->set_size(iFilterArea);
//
//         pFilter = filter->get_data();
//
//         for (y = 0; y <= iFilterHalfH; y++)
//         {
//
//            for (x = 0; x <= iFilterHalfW; x++)
//            {
//
//               x1 = iFilterHalfW - x;
//
//               y1 = iFilterHalfH - y;
//
//               r2 = x1 * x1 + y1 * y1;
//
//               if (r2 <= iRadius2)
//               {
//
//                  i = 1;
//
//               }
//               else
//               {
//
//                  i = 0;
//
//               }
//
//               pFilter[x + y * iFilterW] = (unsigned char)i;
//
//               pFilter[iFilterW - 1 - x + y * iFilterW] = (unsigned char)i;
//
//               pFilter[iFilterW - 1 - x + (iFilterH - 1 - y) * iFilterW] = (unsigned char)i;
//
//               pFilter[x + (iFilterH - 1 - y) * iFilterW] = (unsigned char)i;
//
//            }
//
//         }
//
//      }
//
//      synchronouslock.unlock();
//
//      int maxx1 = cx;
//      int maxy1 = cy;
//      int max3x1 = maxx1 * 3;
//
//
//      unsigned int dwR;
//      unsigned int dwG;
//      unsigned int dwB;
//
//
//      int iFilterXLowerBound;
//      int iFilterXUpperBound;
//      int iFilterYLowerBound;
//      int iFilterYUpperBound;
//
//      int yLowerBound[4];
//      int yUpperBound[4];
//      int xLowerBound[4];
//      int xUpperBound[4];
//
//      // top
//      xLowerBound[0] = 0;
//      xUpperBound[0] = cx - 1;
//      yLowerBound[0] = 0;
//      yUpperBound[0] = iFilterHalfH - 1;
//
//      // left
//      xLowerBound[1] = 0;
//      xUpperBound[1] = iFilterHalfW - 1;
//      yLowerBound[1] = iFilterHalfH;
//      yUpperBound[1] = cy - iFilterHalfH - 1;
//
//      // right
//      xLowerBound[2] = cx - iFilterHalfW;
//      xUpperBound[2] = cx - 1;
//      yLowerBound[2] = iFilterHalfH;
//      yUpperBound[2] = cy - iFilterHalfH - 1;
//
//      // bottom
//      xLowerBound[3] = 0;
//      xUpperBound[3] = cx - 1;
//      yLowerBound[3] = cy - iFilterHalfW;
//      yUpperBound[3] = cy - 1;
//
//      int xL;
//      int xU;
//      int yL;
//      int yU;
//
//      bool bSpread;
//      unsigned int bMin3 = bMin * 3;
//
//
//      for (i = 0; i < 4; i++)
//      {
//         xL = xLowerBound[i];
//         xU = xUpperBound[i];
//         yL = yLowerBound[i];
//         yU = yUpperBound[i];
//
//         y1 = yL;
//         y2 = y1 - iFilterHalfH;
//         for (; y1 <= yU;)
//         {
//            if (y1 < iFilterHalfH)
//            {
//               iFilterYLowerBound = iFilterHalfH - y1;
//            }
//            else
//            {
//               iFilterYLowerBound = 0;
//            }
//            if (y1 > (cy - iFilterHalfH))
//            {
//               iFilterYUpperBound = iFilterH - (y1 - (cy - iFilterHalfH)) - 1;
//            }
//            else
//            {
//               iFilterYUpperBound = iFilterH - 1;
//            }
//
//            lpbSource = lpbSrc + (wSrc * maximum(y2, 0));
//
//            x1 = xL;
//            x2 = (x1 - iFilterHalfW) * 3;
//            lpwDestination = lpbDst + (wDest  * y1) + x1 * 3;
//            for (; x1 <= xU;)
//            {
//               if (x1 < iFilterHalfH)
//               {
//                  iFilterXLowerBound = iFilterHalfH - x1;
//               }
//               else
//               {
//                  iFilterXLowerBound = 0;
//               }
//               if (x1 > (cx - iFilterHalfH + 1))
//               {
//                  iFilterXUpperBound = iFilterH - (x1 - (cx - iFilterHalfH + 1));
//               }
//               else
//               {
//                  iFilterXUpperBound = iFilterH - 1;
//               }
//
//               lpbSource_1 = lpbSource + maximum(x2, 0);
//
//
//               dwR = 0;
//               dwG = 0;
//               dwB = 0;
//               bSpread = false;
//               for (int yFilter = iFilterYLowerBound; yFilter < iFilterYUpperBound; yFilter++)
//               {
//                  lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
//                  lpFilter = pFilter + yFilter * iFilterW + iFilterXLowerBound;
//                  for (int xFilter = iFilterXLowerBound; xFilter < iFilterXUpperBound; xFilter++)
//                  {
//                     if (*lpFilter >= 1)
//                     {
//                        dwB = lpbSource_2[0];
//                        dwG = lpbSource_2[1];
//                        dwR = lpbSource_2[2];
//
//                        if (dwR + dwG + dwB > bMin3)
//                        {
//                           *((unsigned int *)lpwDestination) |= 0x00ffffff;
//                           goto breakFilter;
//                        }
//                     }
//                     lpFilter++;
//                     lpbSource_2 += 3;
//                  }
//               }
//breakFilter:
//               lpwDestination += 3;
//               x1++;
//               x2 += 3;
//            }
//            y1++;
//            y2++;
//         }
//      }
//
//      iFilterYLowerBound = 0;
//      iFilterYUpperBound = iFilterW - 1;
//      iFilterXLowerBound = 0;
//      iFilterXUpperBound = iFilterH - 1;
//
//      int iFilterHalfWidth = iFilterW / 2;
//      int iFilterHalfWidthBytes = iFilterHalfWidth * 3;
//
//      yL = iFilterHalfWidth;
//      yU = maxy1 - iFilterHalfWidth;
//      xL = iFilterHalfWidthBytes;
//      xU = max3x1 - iFilterHalfWidthBytes;
//
//      y1 = yL;
//      y2 = yL - iFilterHalfWidth;
//
//
//
//      divisor = (iFilterYUpperBound - iFilterYLowerBound + 1) * (iFilterXUpperBound - iFilterXLowerBound + 1);
//
//
//      for (; y1 < yU;)
//      {
//         lpbSource = lpbSrc + (wSrc * y2);
//
//         x1 = xL;
//         x2 = xL - iFilterHalfWidthBytes;
//         lpwDestination = lpbDst + (wDest  * y1) + x1;
//         for (; x1 < xU;)
//         {
//            lpbSource_1 = lpbSource + x2;
//            lpFilter = pFilter;
//
//            dwR = 0;
//            dwG = 0;
//            dwB = 0;
//            bSpread = false;
//            for (int yFilter = iFilterYLowerBound; yFilter <= iFilterYUpperBound; yFilter++)
//            {
//               lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
//               lpFilter = pFilter + yFilter * iFilterW + iFilterXLowerBound;
//               for (int xFilter = iFilterXLowerBound; xFilter <= iFilterXUpperBound; xFilter++)
//               {
//                  if (*lpFilter >= 1)
//                  {
//                     dwB = lpbSource_2[0];
//                     dwG = lpbSource_2[1];
//                     dwR = lpbSource_2[2];
//
//                     if (dwR + dwG + dwB > bMin3)
//                     {
//                        bSpread = true;
//                        break;
//                     }
//                  }
//                  lpFilter++;
//                  lpbSource_2 += 3;
//               }
//            }
//
//            if (bSpread)
//            {
//               *((unsigned int *)lpwDestination) |= 0x00ffffff;
//               lpwDestination += 3;
//            }
//            else
//            {
//               lpwDestination += 3;
//            }
//            x1 += 3;
//            x2 += 3;
//         }
//         y1++;
//         y2++;
//      }
//
//   }
//
//
//   bool draw2d::channel_spread__32CC(::image::image *pimageDst, ::image::image *pimageSrc, int iChannel, int iRadius, color32_t crSpreadSetColor)
//   {
//
//      pimageDst->map_base();
//
//      pimageSrc->map_base();
//
//      int iFilterW = iRadius * 2 + 1;
//      int iFilterH = iRadius * 2 + 1;
//      int iFilterHalfW = iRadius;
//      int iFilterHalfH = iRadius;
//      int iFilterArea = iFilterW * iFilterH;
//      int divisor = iFilterW * iFilterH;
//      unsigned char *lpbSource;
//      unsigned char *lpbSource_1;
//      unsigned char *lpbSource_2;
//      unsigned char *lpwDestination;
//      unsigned char *lpFilter;
//      unsigned char * pFilter;
//
//      int i;
//      int x;
//      int y;
//      int x1;
//      int y1;
//      int x2;
//      int y2;
//
//      int iRadiusSquare = iRadius * iRadius;
//      int rSquare;
//
//
//      synchronous_lock synchronouslock(this->synchronization());
//
//      auto & filter = m_alpha_spread__32CC_filterMap[iRadius];
//
//      if (filter.is_set())
//      {
//         pFilter = filter->get_data();
//      }
//      else
//      {
//         filter = __allocate memory();
//         filter->set_size(iFilterArea);
//         pFilter = filter->get_data();
//         for (y = 0; y < iFilterH; y++)
//         {
//            for (x = 0; x < iFilterW; x++)
//            {
//               x1 = iFilterHalfW - x;
//               y1 = iFilterHalfH - y;
//               rSquare = x1 * x1 + y1 * y1;
//               if (rSquare <= iRadiusSquare)
//                  i = 1;
//               else
//                  i = 0;
//               pFilter[x + y * iFilterW] = (unsigned char)i;
//            }
//         }
//      }
//
//      synchronouslock.unlock();
//
//      int cx = pimageDst->width();
//      int cy = pimageDst->height();
//
//      if (cx != pimageSrc->width() || cy != pimageSrc->height())
//         return false;
//
//      unsigned char * lpbDst = (unsigned char *)pimageDst->get_data();
//      unsigned char * lpbSrc = (unsigned char *)pimageSrc->get_data();
//
//      //int wSrc = cx * 4;
//      //int wDst = cx * 4;
//      int wSrc = pimageSrc->scan_size();
//      int wDst = pimageDst->scan_size();
//
//      int maxx1 = cx;
//      int maxy1 = cy;
//      //   int maxy2 = cy - iFilterW;
//      //   int maxy3 = cy - iFilterW / 2;
//      int max3x1 = maxx1 * 4;
//      //   int max3x2 = (maxx1 - iFilterH) * 4;
//      //   int max3x3 = (maxx1 - iFilterH / 2) * 4;
//      //int w = cx * 4;
//
//      ::copy_image32(pimageDst, pimageSrc);
//      //::memory_copy(lpbDst,lpbSrc,cx * cy * 4);
//
//
//      int iFilterXLowerBound;
//      int iFilterXUpperBound;
//      int iFilterYLowerBound;
//      int iFilterYUpperBound;
//
//      int yLowerBound[4];
//      int yUpperBound[4];
//      int xLowerBound[4];
//      int xUpperBound[4];
//
//      // top
//      xLowerBound[0] = 0;
//      xUpperBound[0] = cx - 1;
//      yLowerBound[0] = 0;
//      yUpperBound[0] = iFilterHalfH - 1;
//
//      // left
//      xLowerBound[1] = 0;
//      xUpperBound[1] = iFilterHalfW - 1;
//      yLowerBound[1] = iFilterHalfH;
//      yUpperBound[1] = cy - iFilterHalfH - 1;
//
//      // right
//      xLowerBound[2] = cx - iFilterHalfW;
//      xUpperBound[2] = cx - 1;
//      yLowerBound[2] = iFilterHalfH;
//      yUpperBound[2] = cy - iFilterHalfH - 1;
//
//      // bottom
//      xLowerBound[3] = 0;
//      xUpperBound[3] = cx - 1;
//      yLowerBound[3] = cy - iFilterHalfH;
//      yUpperBound[3] = cy - 1;
//
//      int xL;
//      int xU;
//      int yL;
//      int yU;
//
//
//      int xMax = cx - 1;
//      int yMax = cy - 1;
//
//      // limits due the filter
//      int xMaxFilterBound = xMax - iFilterHalfW;
//      int yMaxFilterBound = yMax - iFilterHalfH;
//
//      int xFilterMax = iFilterW - 1;
//      int yFilterMax = iFilterH - 1;
//
//      for (i = 0; i < 4; i++)
//      {
//         xL = xLowerBound[i];
//         xU = xUpperBound[i];
//         yL = yLowerBound[i];
//         yU = yUpperBound[i];
//
//         y1 = yL;
//         y2 = y1 - iFilterHalfH;
//         for (; y1 <= yU;)
//         {
//            if (y1 < iFilterHalfH)
//            {
//               iFilterYLowerBound = iFilterHalfH - y1;
//            }
//            else
//            {
//               iFilterYLowerBound = 0;
//            }
//            if (y1 > yMaxFilterBound)
//            {
//               iFilterYUpperBound = yFilterMax - (y1 - yMaxFilterBound);
//            }
//            else
//            {
//               iFilterYUpperBound = yFilterMax;
//            }
//
//            lpbSource = lpbSrc + wSrc * y2;
//
//            x1 = xL;
//            x2 = (x1 - iFilterHalfW) * 4;
//            lpwDestination = lpbDst + (wDst  * y1) + x1 * 4;
//            if (*((unsigned int *)lpwDestination) != 0xffffffff)
//            {
//               for (; x1 <= xU; x1++)
//               {
//                  if (x1 < iFilterHalfH)
//                  {
//                     iFilterXLowerBound = iFilterHalfH - x1;
//                  }
//                  else
//                  {
//                     iFilterXLowerBound = 0;
//                  }
//                  if (x1 > xMaxFilterBound)
//                  {
//                     iFilterXUpperBound = xFilterMax - (x1 - xMaxFilterBound);
//                  }
//                  else
//                  {
//                     iFilterXUpperBound = xFilterMax;
//                  }
//
//                  lpbSource_1 = lpbSource + maximum(x2, 0) + iChannel;
//
//
//                  for (int yFilter = iFilterYLowerBound; yFilter < iFilterYUpperBound; yFilter++)
//                  {
//                     lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
//                     lpFilter = pFilter + yFilter * iFilterW + iFilterXLowerBound;
//                     for (int xFilter = iFilterXLowerBound; xFilter < iFilterXUpperBound; xFilter++)
//                     {
//                        if (*lpFilter >= 1)
//                        {
//                           if (lpbSource_2[0] > 0)
//                           {
//                              *((unsigned int *)lpwDestination) = crSpreadSetColor;
//                              goto breakFilter;
//                           }
//                        }
//                        lpFilter++;
//                        lpbSource_2 += 4;
//                     }
//                  }
//breakFilter:
//                  lpwDestination += 4;
//                  x2 += 4;
//               }
//            }
//            y1++;
//            y2++;
//         }
//      }
//
//      iFilterYLowerBound = 0;
//      iFilterYUpperBound = iFilterW - 1;
//      iFilterXLowerBound = 0;
//      iFilterXUpperBound = iFilterH - 1;
//
//      int iFilterHalfWidth = iFilterW / 2;
//      int iFilterHalfWidthBytes = iFilterHalfWidth * 4;
//
//      yL = iFilterHalfWidth;
//      yU = maxy1 - iFilterHalfWidth;
//      xL = iFilterHalfWidthBytes;
//      xU = max3x1 - iFilterHalfWidthBytes;
//
//      y1 = yL;
//      y2 = yL - iFilterHalfWidth;
//
//
//
//      divisor = (iFilterYUpperBound - iFilterYLowerBound + 1) * (iFilterXUpperBound - iFilterXLowerBound + 1);
//
//
//      for (; y1 < yU;)
//      {
//         lpbSource = lpbSrc + (wSrc * y2) + iChannel;
//
//         x1 = xL;
//         x2 = xL - iFilterHalfWidthBytes;
//         lpwDestination = lpbDst + (wDst  * y1) + x1;
//         for (; x1 < xU;)
//         {
//            lpbSource_1 = lpbSource + x2;
//            lpFilter = pFilter;
//
//            if (*((unsigned int *)lpwDestination) != 0xffffffff)
//            {
//               for (int yFilter = iFilterYLowerBound; yFilter <= iFilterYUpperBound; yFilter++)
//               {
//                  lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
//                  lpFilter = pFilter + yFilter * iFilterW + iFilterXLowerBound;
//                  for (int xFilter = iFilterXLowerBound; xFilter <= iFilterXUpperBound; xFilter++)
//                  {
//                     if (*lpFilter >= 1)
//                     {
//                        if (lpbSource_2[0] > 0)
//                        {
//                           *((unsigned int *)lpwDestination) = crSpreadSetColor;
//                           goto breakFilter2;
//                        }
//                     }
//                     lpFilter++;
//                     lpbSource_2 += 4;
//                  }
//               }
//            }
//breakFilter2:
//            lpwDestination += 4;
//            x1 += 4;
//            x2 += 4;
//         }
//         y1++;
//         y2++;
//      }
//
//      return true;
//   }


//   void draw2d::enum_draw2d_fonts(::write_text::font_enumeration_item_array& itema)
//   {
//
//      critical_section_lock synchronouslock(::aura::g_pcsFont);
//
//      ::pointer<::write_text::font_enumeration_item>pitem;
//
//      double dAndroid = 4.4;
//
//      string strSystemFonts = file()->as_string("/system/etc/system_fonts.xml");
//
//            auto psystem = system();

      //auto pxml = psystem->xml();

      //auto pdoc = pxml->create_document();
//
//      ::pointer<ttf_util>putil;
//
//      ::e_status estatus = __construct_new(putil);
//
//      if (pdoc->load(strSystemFonts))
//      {
//
//         ::collection::index iFamilyPos = 0;
//
//         while (auto pfamily = pdoc->root()->get_child("family", iFamilyPos))
//         {
//
//            if (iFamilyPos < 0)
//            {
//
//               break;
//
//            }
//
//            iFamilyPos++;
//
//            if (pfamily->get_name() == "family")
//            {
//
//               ::collection::index iNamesetPos = 0;
//
//               auto pnameset = pfamily->get_child("nameset", iNamesetPos);
//
//               ::collection::index iFilesetPos = 0;
//
//               auto pfileset = pfamily->get_child("fileset", iFilesetPos);
//
//               if (pnameset && pfileset)
//               {
//
//                  if (pnameset->get_children_count() >= 1 && pfileset->get_children_count() >= 1)
//                  {
//
//                     ::collection::index iNamePos = 0;
//
//                     auto pfirstname = pnameset->get_child("name", iNamePos);
//
//                     ::collection::index iFilePos = 0;
//
//                     auto pfirstfile = pfileset->get_child("file", iFilePos);
//
//                     if (pfirstname && pfirstfile)
//                     {
//
//                        string strName = pfirstname->get_value();
//
//                        string strFile = pfirstfile->get_value();
//
//                        ::file::path path = "/system/fonts";
//
//                        path /= strFile;
//
//                        pitem = __allocate ::write_text::font_enumeration_item();
//
//                        if (::file_system()->exists(path))
//                        {
//
//                           pitem->m_strFile = path;
//
//                        }
//                        else
//                        {
//
//                           pitem->m_strFile = strFile;
//
//                        }
//
//                        pitem->m_strName = strName;
//
//                        itema.add(pitem);
//
//                        ::aura::g_pmapFontFaceName->set_at(strName, pitem->m_strFile);
//
//                     }
//
//                  }
//
//               }
//
//            }
//
//         }
//
//      }
//
//      if (dAndroid >= 8.0)
//      {
//
//         ::file::path_array_base patha;
//
//         ::dir::ls(patha, "/system/fonts");
//
//         if(estatus.succeeded())
//         {
//
//            for (auto& path : patha)
//            {
//
//               pitem = __allocate ::write_text::font_enumeration_item();
//
//               pitem->m_strFile = path;
//
//               string strName = putil->GetFontNameFromFile(path);
//
//               if (strName.is_empty())
//               {
//
//                  strName = path.title();
//
//               }
//
//               pitem->m_strName = strName;
//
//               itema.add(pitem);
//
//               ::aura::g_pmapFontFaceName->set_at(strName, path);
//
//            }
//
//         }
//
//      }
//
//      if (itema.isEmpty())
//      {
//
//
//#ifdef pnode->font_name(e_font_mono)
//
//         pitem = __allocate ::write_text::font_enumeration_item();
//
//         pitem->m_strFile = pnode->font_name(e_font_mono);
//
//         pitem->m_strName = pnode->font_name(e_font_mono);
//
//         itema.add(pitem);
//
//#endif
//
//
//#ifdef pnode->font_name(e_font_sans)
//
//         pitem = __allocate ::write_text::font_enumeration_item();
//
//         pitem->m_strFile = pnode->font_name(e_font_sans);
//
//         pitem->m_strName = pnode->font_name(e_font_sans);
//
//         itema.add(pitem);
//
//#endif
//
//
//#ifdef pnode->font_name(e_font_serif)
//
//         pitem = __allocate ::write_text::font_enumeration_item();
//
//         pitem->m_strFile = pnode->font_name(e_font_serif);
//
//         pitem->m_strName = pnode->font_name(e_font_serif);
//
//         itema.add(pitem);
//
//#endif
//
//
//#ifdef pnode->font_name(e_font_sans_ex)
//
//         pitem = __allocate ::write_text::font_enumeration_item();
//
//         pitem->m_strFile = pnode->font_name(e_font_sans_ex);
//
//         pitem->m_strName = pnode->font_name(e_font_sans_ex);
//
//         itema.add(pitem);
//
//#endif
//
//
//#ifdef pnode->font_name(e_font_serif_ex)
//
//         pitem = __allocate ::write_text::font_enumeration_item();
//
//         pitem->m_strFile = pnode->font_name(e_font_serif_ex);
//
//         pitem->m_strName = pnode->font_name(e_font_serif_ex);
//
//         itema.add(pitem);
//
//#endif
//
//
//#ifdef pnode->font_name(e_font_sans_fx)
//
//         pitem = __allocate ::write_text::font_enumeration_item();
//
//         pitem->m_strFile = pnode->font_name(e_font_sans_fx);
//
//         pitem->m_strName = pnode->font_name(e_font_sans_fx);
//
//         itema.add(pitem);
//
//#endif
//
//
//#ifdef pnode->font_name(e_font_serif_fx)
//
//         pitem = __allocate ::write_text::font_enumeration_item();
//
//         pitem->m_strFile = pnode->font_name(e_font_serif_fx);
//
//         pitem->m_strName = pnode->font_name(e_font_serif_fx);
//
//         itema.add(pitem);
//
//#endif
//
//
//#ifdef FONT_SANS_FX2
//
//         pitem = __allocate ::write_text::font_enumeration_item();
//
//         pitem->m_strFile = FONT_SANS_FX2;
//
//         pitem->m_strName = FONT_SANS_FX2;
//
//         itema.add(pitem);
//
//#endif
//
//
//      }
//
//   }


//   void draw2d::initialize_write_text()
//   {
//
//      ::e_status estatus = ::success;
//
//      try
//      {
//
//         if (!([a-z0-9_]+)_factory(::factory_item::get_factory()))
//         {
//
//            output_error_message("Failed to initialize draw2d library.");
//
//            estatus = error_failed;
//
//         }
//
//      }
//      catch (...)
//      {
//
//         estatus = error_exception;
//
//      }
//
//      if (!estatus)
//      {
//
//         informationf("([a-z0-9_]+)_factory has failed.\n\nSome reasons:\n   - No draw2d library present;\n   - Failure to open any suitable draw2d library.", e_message_box_ok);
//
//         return estatus;
//
//      }
//
//
//      synchronous_lock synchronouslock(psystem->m_pmutexLibrary);
//
//      estatus = __øconstruct(m_pwritetext);
//
//      if (!estatus)
//      {
//
//         informationf("Couldn't construct ___new draw2d.");
//
//         return false;
//
//      }
//
//      estatus = m_pwritetext->init1();
//
//      if (!estatus)
//      {
//
//         informationf("Couldn't initialize write_text (init1).");
//
//         return estatus;
//
//      }
//
//      if (::succeeded(estatus))
//      {
//
//         add_factory_item < ::draw2d::task_tool_item >(::e_task_tool_draw2d);
//
//      }
//
//      return estatus;
//
//   }


//   void draw2d::([a-z0-9_]+)_factory(::factory::factory * pfactory)
//   {
//
//      string strLibrary;
//
//      if (has_property("write_text"))
//      {
//
//         strLibrary = payload("write_text");
//
//         //strDraw2d.trim();
//
//         //if (strDraw2d.has_character())
//         //{
//
//         //   strDraw2d.case_insensitive_begins_eat("draw2d_");
//
//         //   strDraw2d.case_insensitive_begins_eat("draw2d");
//
//         //   strLibrary = "draw2d_" + strDraw2d;
//
//         //}
//
//      }
//
//      ::e_status estatus;
//
//      if (strLibrary.has_character())
//      {
//
//         estatus = psystem->([a-z0-9_]+)_factory("write_text", strLibrary);
//
//         if(estatus.succeeded())
//         {
//
//            return ::success;
//
//         }
//
//      }
//
//      strLibrary = write_text_get_default_implementation_name();
//
//      if (strLibrary.is_empty())
//      {
//
//#ifdef WINDOWS
//
//         strLibrary = "write_text_gdiplus";
//
//#else
//
//         strLibrary = "write_text_cairo";
//
//#endif
//
//      }
//
//      estatus = psystem->([a-z0-9_]+)_factory("write_text", strLibrary);
//
//      if(estatus.succeeded())
//      {
//
//         return ::success;
//
//      }
//
//
//#ifdef WINDOWS_DESKTOP
//
//
//      if (strLibrary != "write_text_gdiplus")
//      {
//
//         estatus = psystem->([a-z0-9_]+)_factory("write_text", "gdiplus");
//
//         if(estatus.succeeded())
//         {
//
//            return ::success;
//
//         }
//
//      }
//
//
//      if (strLibrary != "write_text_direct2d")
//      {
//
//         estatus = psystem->([a-z0-9_]+)_factory("write_text", "direct2d");
//
//         if(estatus.succeeded())
//         {
//
//            return ::success;
//
//         }
//
//      }
//
//
//#endif
//
//      if (strLibrary != "write_text_cairo")
//      {
//
//
//         estatus = psystem->([a-z0-9_]+)_factory("write_text", "cairo");
//
//         if(estatus.succeeded())
//         {
//
//            return ::success;
//
//         }
//
//      }
//
//      //informationf("No write_text pluging available!!.");
//      return error_failed;
//
//      //destroy:
//
//      //   PFN_factory ([a-z0-9_]+)_factory = plibrary->get < PFN_factory >("([a-z0-9_]+)_factory");
//
//      //   if (([a-z0-9_]+)_factory == nullptr)
//      //   {
//
//      //      return false;
//
//      //   }
//
//      //   ([a-z0-9_]+)_factory(::factory::factory * pfactory);
//
//      //   return true;
//
//   //#endif
//
//   }
//
//
//   string draw2d::write_text_get_default_implementation_name()
//   {
//
//#ifdef LINUX
//
//      return "linux";
//
//#else
//
//      return PLATFORM_COMMON_STRING;
//
//#endif
//
//   }


   cairo_font_face_t * draw2d::private_ftface_from_memory(const ::block & block, const ::scoped_string & scopedstrName)
   {

      auto & pprivatefont = m_mapPrivateFont[scopedstrName];

      if(::is_set(pprivatefont))
      {

         return pprivatefont->m_pfontface;

      }

      pprivatefont = __allocate private_font();

      FT_Face ftface{};

      FT_Error fterror = FT_New_Memory_Face(__ftlibrary(), (const FT_Byte *) block.data(), (FT_Long) block.size(), 0, &ftface);

      if(fterror != 0)
      {

         return nullptr;

      }

      cairo_font_face_t * pfontface = cairo_ft_font_face_create_for_ft_face(ftface, 0);

      if(::is_null(pfontface))
      {

         FT_Done_Face(ftface);

         return nullptr;

      }

      pprivatefont->m_ftface = ftface;

      pprivatefont->m_pfontface = pfontface;

      return pfontface;

   }


   cairo_font_face_t * draw2d::private_ftface_from_file(::platform::context * pcontext, const ::payload & payloadFile)
   {

      synchronous_lock synchronouslock(::draw2d_cairo::mutex());

      ::file::path pathFile = payloadFile.as_file_path();

      auto & pprivatefont = m_mapPrivateFont[pathFile];

      if(::is_set(pprivatefont))
      {

         return pprivatefont->m_pfontface;

      }

      ::file::path path = pcontext->defer_process_path(pathFile);

      auto pmemorypointer = system()->draw2d()->write_text()->get_file_memory(pcontext, path);

      return private_ftface_from_memory(*pmemorypointer, pathFile);

   }


} // namespace draw2d_cairo


//enum_rotate_flip exif_orientation_rotate_flip(int orientation)
//{
//
//
//   switch (orientation)
//   {
//   case 1:
//      return e_rotate_none_flip_none;
//   case 2:
//      return e_rotate_none_flip_x;
//   case 3:
//      return e_rotate_180_flip_none;
//   case 4:
//      return e_rotate_180_flip_x;
//   case 5:
//      return e_rotate_90_flip_x;
//   case 6:
//      return e_rotate_90_flip_none;
//   case 7:
//      return e_rotate_270_flip_x;
//   case 8:
//      return e_rotate_270_flip_none;
//   default:
//      return e_rotate_none_flip_none;
//   }
//
//
//}



