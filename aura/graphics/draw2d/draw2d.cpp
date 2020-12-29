#include "framework.h"


namespace aura
{


   extern CLASS_DECL_AURA string_map < int_to_string > * g_pmapFontFaceName;


   extern CLASS_DECL_AURA critical_section * g_pcsFont;


} // namespace aura


namespace draw2d
{


   double draw2d::g_dEmboss = 2.0;


   draw2d::draw2d()
   {

      defer_create_mutex();

      //m_pmutexFont = __new(::mutex);

      create_factory < cursor_set >();

      m_bSettingCursorMatter = false;

   }


   draw2d::~draw2d()
   {


   }


   ::e_status draw2d::initialize(::layered * pobjectContext)
   {

      auto estatus = ::apex::department::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      estatus = __construct_new(m_papi);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   api & draw2d::api()
   {

      return *m_papi;

   }


   ::e_status draw2d::init1()
   {

      if (!::apex::department::init1())
      {

         return false;

      }

      return true;

   }


   ::e_status draw2d::process_init()
   {

      if (!::apex::department::process_init())
      {

         return false;

      }

      sync_lock sl(mutex());

      if (!m_papi->open())
      {

         return false;

      }

      return true;

   }


   ::e_status draw2d::init()
   {

      if (!::apex::department::init())
      {

         return false;

      }

      return true;

   }


   double draw2d::font_similarity(const char* pszSystem, const char* pszUser)
   {

      if (::is_null(pszSystem) || ::is_null(pszUser))
      {

         return 0.0;

      }

      if (!stricmp(pszSystem, pszUser))
      {

         return 1.0;

      }

      return 0.0;

   }

   e_format draw2d::file_extension_to_format(const ::payload & varFile)
   {

      return text_to_format(varFile.get_file_path().final_extension());

   }

   e_format draw2d::text_to_format(string strText)
   {

      strText.make_lower();

      if (strText == "png")
      {

         return ::draw2d::format_png;

      }
      else if (strText == "jpg" || strText == "jpeg")
      {

         return ::draw2d::format_jpeg;

      }
      else if (strText == "gif")
      {

         return ::draw2d::format_gif;

      }
      else if (strText == "bmp")
      {

         return ::draw2d::format_bmp;

      }
      else
      {

         return ::draw2d::format_none;

      }

   }


   void draw2d::term()
   {

      sync_lock sl(mutex());

      try
      {

         if (m_papi)
         {

            m_papi->close();

            m_papi->finalize();

         }

      }
      catch (...)
      {

      }

      try
      {

         if (m_pfontdepartment)
         {

            m_pfontdepartment->finalize();

         }

      }
      catch (...)
      {


      }

      m_alpha_spread__24CC_filterMap.remove_all();

      m_alpha_spread__32CC_filterMap.remove_all();

      if (m_pcursorset)
      {

         m_pcursorset->finalize();

      }

   }


   void draw2d::finalize()
   {

      m_papi.release();

      m_pfontdepartment.release();

      m_pcursorset.release();

      ::apex::department::finalize();

   }


   class font_department & draw2d::fonts()
   {
      
      sync_lock sl(mutex());

      if (m_pfontdepartment == nullptr)
      {

         auto estatus = __construct_new(m_pfontdepartment);

         if (estatus)
         {

            System.process_subject(id_font_enumeration);

         }

      }

      return *m_pfontdepartment;

   }


   __pointer(cursor) draw2d::get_cursor(e_cursor ecursor)
   {

      sync_lock sl(mutex());

      if (m_pcursorset.is_null())
      {

         auto estatus =  __construct_new(m_pcursorset);

         if (!estatus)
         {

            return nullptr;

         }

         m_pcursorset->set_cursor_set_system_default();

      }

      return m_pcursorset->get_cursor(ecursor);

   }


   bool draw2d::set_cursor_set_from_matter(const ::file::path& pathDir)
   {

      sync_lock sl(mutex());

      if (m_bSettingCursorMatter)
      {

         return false;

      }

      __keep(m_bSettingCursorMatter);

      sl.unlock();

      auto pcursorset = __create_new < cursor_set > ();

      if (!pcursorset->set_cursor_set_from_matter(pathDir))
      {

         return false;

      }

      m_pcursorset = pcursorset;

      return true;

   }


   // should not call axis class implementation because draw2d::draw2d is inside a n-furcation of user::draw2d
   void draw2d::term_instance()
   {

      try
      {

         ::apex::department::term_instance();

      }
      catch (...)
      {

         message_box("except", "except", e_message_box_ok);

      }

   }


   bool draw2d::embossed_text_out(
   ::draw2d::graphics_pointer & pgraphics,
   const ::rect & rect,
   string strText,
   ::draw2d::fastblur & blur,
   ::image_pointer & imageBlur,
   ::draw2d::font * pfont,
   const ::e_align & ealign,
   const ::e_draw_text & edrawtext,
   color32_t crText,
   color32_t crGlow,
   int iSpreadRadius,
   int iBlurRadius,
   int iBlur,
   bool bUpdate,
   double dAlpha)
   {

      if (strText.is_empty())
      {

         return false;

      }

      auto pred = [&](::draw2d::graphics * pgraphics)
      {

         pgraphics->set(pfont);
         pgraphics->_DrawText(strText, *rect, ealign, edrawtext);

      };

      emboss_pred(
      pgraphics,
      rect,
      pred,
      blur,
      imageBlur,
      crGlow,
      iSpreadRadius,
      iBlurRadius,
      iBlur,
      bUpdate,
      dAlpha);

      byte bA = (byte)(dAlpha * 255.0);
      ::draw2d::brush_pointer pbrushText(e_create);
      pbrushText->create_solid((crText & 0x00ffffffu) | (bA << 24));
      pgraphics->set(pbrushText);
      pgraphics->set(pfont);
      pgraphics->_DrawText(strText, *rect, ealign, edrawtext);

      return true;

   }

   void draw2d::alpha_spread__24CC(
   byte * lpbDst, i32 xDest, i32 yDest, i32 wDest, i32 cx, i32 cy,
   byte * lpbSrc, i32 xSrc, i32 ySrc, i32 wSrc,
   byte bMin, i32 iRadius)
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
      i32 divisor;
      byte *lpbSource;
      byte *lpbSource_1;
      byte *lpbSource_2;
      byte *lpwDestination;
      byte *lpFilter;
      byte *pFilter;


      i32 i;
      i32 x;
      i32 y;
      i32 x1;
      i32 y1;
      i32 x2;
      i32 y2;

      i32 iRadius2 = iRadius * iRadius;
      i32 r2;

      sync_lock sl(mutex());

      auto & filter = m_alpha_spread__24CC_filterMap[iRadius];

      if (filter.is_set())
      {

         pFilter = filter->get_data();

      }
      else
      {

         filter = __new(memory());

         filter->set_size(iFilterArea);

         pFilter = filter->get_data();

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

               pFilter[x + y * iFilterW] = (byte)i;

               pFilter[iFilterW - 1 - x + y * iFilterW] = (byte)i;

               pFilter[iFilterW - 1 - x + (iFilterH - 1 - y) * iFilterW] = (byte)i;

               pFilter[x + (iFilterH - 1 - y) * iFilterW] = (byte)i;

            }

         }

      }

      sl.unlock();

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

            lpbSource = lpbSrc + (wSrc * max(y2, 0));

            x1 = xL;
            x2 = (x1 - iFilterHalfW) * 3;
            lpwDestination = lpbDst + (wDest  * y1) + x1 * 3;
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

               lpbSource_1 = lpbSource + max(x2, 0);


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



      divisor = (iFilterYUpperBound - iFilterYLowerBound + 1) * (iFilterXUpperBound - iFilterXLowerBound + 1);


      for (; y1 < yU;)
      {
         lpbSource = lpbSrc + (wSrc * y2);

         x1 = xL;
         x2 = xL - iFilterHalfWidthBytes;
         lpwDestination = lpbDst + (wDest  * y1) + x1;
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


   bool draw2d::channel_spread__32CC(::image * pimageDst, ::image * pimageSrc, i32 iChannel, i32 iRadius, color32_t crSpreadSetColor)
   {

      pimageDst->map();

      pimageSrc->map();

      i32 iFilterW = iRadius * 2 + 1;
      i32 iFilterH = iRadius * 2 + 1;
      i32 iFilterHalfW = iRadius;
      i32 iFilterHalfH = iRadius;
      i32 iFilterArea = iFilterW * iFilterH;
      i32 divisor = iFilterW * iFilterH;
      byte *lpbSource;
      byte *lpbSource_1;
      byte *lpbSource_2;
      byte *lpwDestination;
      byte *lpFilter;
      byte * pFilter;

      i32 i;
      i32 x;
      i32 y;
      i32 x1;
      i32 y1;
      i32 x2;
      i32 y2;

      i32 iRadiusSquare = iRadius * iRadius;
      i32 rSquare;


      sync_lock sl(mutex());

      auto & filter = m_alpha_spread__32CC_filterMap[iRadius];

      if (filter.is_set())
      {
         pFilter = filter->get_data();
      }
      else
      {
         filter = __new(memory());
         filter->set_size(iFilterArea);
         pFilter = filter->get_data();
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
               pFilter[x + y * iFilterW] = (byte)i;
            }
         }
      }

      sl.unlock();

      i32 cx = pimageDst->width();
      i32 cy = pimageDst->height();

      if (cx != pimageSrc->width() || cy != pimageSrc->height())
         return false;

      byte * lpbDst = (byte *)pimageDst->get_data();
      byte * lpbSrc = (byte *)pimageSrc->get_data();

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

      ::copy_colorref(pimageDst, pimageSrc);
      //::memcpy_dup(lpbDst,lpbSrc,cx * cy * 4);


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
            lpwDestination = lpbDst + (wDst  * y1) + x1 * 4;
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

                  lpbSource_1 = lpbSource + max(x2, 0) + iChannel;


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
                              *((u32 *)lpwDestination) = crSpreadSetColor;
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



      divisor = (iFilterYUpperBound - iFilterYLowerBound + 1) * (iFilterXUpperBound - iFilterXLowerBound + 1);


      for (; y1 < yU;)
      {
         lpbSource = lpbSrc + (wSrc * y2) + iChannel;

         x1 = xL;
         x2 = xL - iFilterHalfWidthBytes;
         lpwDestination = lpbDst + (wDst  * y1) + x1;
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
                           *((u32 *)lpwDestination) = crSpreadSetColor;
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


//   void draw2d::enum_draw2d_fonts(::draw2d::font_enum_item_array& itema)
//   {
//
//      cslock sl(::aura::g_pcsFont);
//
//      __pointer(::draw2d::font_enum_item) pitem;
//
//      double dAndroid = 4.4;
//
//      string strSystemFonts = Context.file().as_string("/system/etc/system_fonts.xml");
//
//      auto pdoc = create_xml_document();
//
//      __pointer(ttf_util) putil;
//
//      ::e_status estatus = __construct_new(putil);
//
//      if (pdoc->load(strSystemFonts))
//      {
//
//         ::index iFamilyPos = 0;
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
//               ::index iNamesetPos = 0;
//
//               auto pnameset = pfamily->get_child("nameset", iNamesetPos);
//
//               ::index iFilesetPos = 0;
//
//               auto pfileset = pfamily->get_child("fileset", iFilesetPos);
//
//               if (pnameset && pfileset)
//               {
//
//                  if (pnameset->get_children_count() >= 1 && pfileset->get_children_count() >= 1)
//                  {
//
//                     ::index iNamePos = 0;
//
//                     auto pfirstname = pnameset->get_child("name", iNamePos);
//
//                     ::index iFilePos = 0;
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
//                        pitem = __new(::draw2d::font_enum_item);
//
//                        if (::file_exists(path))
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
//         ::file::patha patha;
//
//         ::dir::ls(patha, "/system/fonts");
//
//         if (estatus)
//         {
//
//            for (auto& path : patha)
//            {
//
//               pitem = __new(::draw2d::font_enum_item);
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
//#ifdef FONT_MONO
//
//         pitem = __new(::draw2d::font_enum_item);
//
//         pitem->m_strFile = FONT_MONO;
//
//         pitem->m_strName = FONT_MONO;
//
//         itema.add(pitem);
//
//#endif
//
//
//#ifdef FONT_SANS
//
//         pitem = __new(::draw2d::font_enum_item);
//
//         pitem->m_strFile = FONT_SANS;
//
//         pitem->m_strName = FONT_SANS;
//
//         itema.add(pitem);
//
//#endif
//
//
//#ifdef FONT_SERIF
//
//         pitem = __new(::draw2d::font_enum_item);
//
//         pitem->m_strFile = FONT_SERIF;
//
//         pitem->m_strName = FONT_SERIF;
//
//         itema.add(pitem);
//
//#endif
//
//
//#ifdef FONT_SANS_EX
//
//         pitem = __new(::draw2d::font_enum_item);
//
//         pitem->m_strFile = FONT_SANS_EX;
//
//         pitem->m_strName = FONT_SANS_EX;
//
//         itema.add(pitem);
//
//#endif
//
//
//#ifdef FONT_SERIF_EX
//
//         pitem = __new(::draw2d::font_enum_item);
//
//         pitem->m_strFile = FONT_SERIF_EX;
//
//         pitem->m_strName = FONT_SERIF_EX;
//
//         itema.add(pitem);
//
//#endif
//
//
//#ifdef FONT_SANS_FX
//
//         pitem = __new(::draw2d::font_enum_item);
//
//         pitem->m_strFile = FONT_SANS_FX;
//
//         pitem->m_strName = FONT_SANS_FX;
//
//         itema.add(pitem);
//
//#endif
//
//
//#ifdef FONT_SERIF_FX
//
//         pitem = __new(::draw2d::font_enum_item);
//
//         pitem->m_strFile = FONT_SERIF_FX;
//
//         pitem->m_strName = FONT_SERIF_FX;
//
//         itema.add(pitem);
//
//#endif
//
//
//#ifdef FONT_SANS_FX2
//
//         pitem = __new(::draw2d::font_enum_item);
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


} // namespace draw2d


e_rotate_flip exif_orientation_rotate_flip(int orientation)
{


   switch (orientation)
   {
   case 1:
      return rotate_none_flip_none;
   case 2:
      return rotate_none_flip_x;
   case 3:
      return rotate_180_flip_none;
   case 4:
      return rotate_180_flip_x;
   case 5:
      return rotate_90_flip_x;
   case 6:
      return rotate_90_flip_none;
   case 7:
      return rotate_270_flip_x;
   case 8:
      return rotate_270_flip_none;
   default:
      return rotate_none_flip_none;
   }
   

}



