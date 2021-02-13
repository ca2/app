#include "framework.h"


#define pixel(x, y) (ba[(pointer->m_rectangle.height() - (y) - 1) * iScan + (x)])


//bool draw2d_gif_detect_8bit_borders(image * imageCanvas, image_frame_array * pimagepointera, image_frame * pframe, int uFrameIndex, u8 * ba, int iScan, colorref_array & cra, int transparentIndex)
//{
//
//   return true;
//
////   color32_t cr;
////
////   color32_t crBack = 0;
////
////   ::count cTransparent = 0;
////
////   bool bTransparent;
////
////   ::count c = 0;
////
////   i64 iR = 0;
////
////   i64 iG = 0;
////
////   i64 iB = 0;
////
////   //int iLight = 0;
////
////   //int iDark = 0;
////
////   // Roughly detect colors on transparency borders...
////
////   // ... first, at horizontal orientation...
////
////   int h = pointer->m_pimpl->height();
////
////   int w = pointer->m_pimpl->width();
////
////   for (index y = 0; y < h; y++)
////   {
////
////      bTransparent = true;
////
////      for (index x = 0; x < w; x++)
////      {
////
////         index iIndex = pixel(x, y);
////
////         index iNextIndex = -1;
////
////         if (x < w - 1)
////         {
////
////            iNextIndex = pixel(x + 1, y);
////
////         }
////
////         if (iIndex >= cra.get_count())
////         {
////
////            continue;
////
////         }
////
////         if (bTransparent)
////         {
////
////            if (iIndex == transparentIndex)
////            {
////
////               cTransparent++;
////
////               continue;
////
////            }
////            else
////            {
////
////               cr = cra[iIndex];
////
////               bTransparent = false;
////
////            }
////
////         }
////         else
////         {
////
////            if (iNextIndex == transparentIndex)
////            {
////
////               cr = cra[iIndex];
////
////               bTransparent = true;
////
////            }
////            else
////            {
////
////               continue;
////
////            }
////
////         }
////
////         iR += colorref_get_r_value(cr);
////
////         iG += colorref_get_g_value(cr);
////
////         iB += colorref_get_b_value(cr);
////
////         c++;
////
////      }
////
////   }
////
////   // ... then, at vertical orientation...
////
////   for (index x = 0; x < w; x++)
////   {
////
////      bTransparent = true;
////
////      for (index y = 0; y < h; y++)
////      {
////
////         index iIndex = pixel(x, y);
////
////         index iNextIndex = -1;
////
////         if (y < h - 1)
////         {
////
////            iNextIndex = pixel(x, y + 1);
////
////         }
////
////         if (iIndex >= cra.get_count())
////         {
////
////            continue;
////
////         }
////
////         if (bTransparent)
////         {
////
////            if (iIndex == transparentIndex)
////            {
////
////               continue;
////
////            }
////            else
////            {
////
////               cr = cra[iIndex];
////
////               bTransparent = false;
////
////            }
////
////         }
////         else
////         {
////
////            if (iNextIndex == transparentIndex)
////            {
////
////               cr = cra[iIndex];
////
////               bTransparent = true;
////
////            }
////            else
////            {
////
////               continue;
////
////            }
////
////         }
////
////         iR += colorref_get_r_value(cr);
////
////         iG += colorref_get_g_value(cr);
////
////         iB += colorref_get_b_value(cr);
////
////         c++;
////
////      }
////
////   }
////
////   // and if detected transparency, roughly calculate if average border color is dark or light.
////
////   if (cTransparent <= 0)
////   {
////
////      crBack = argb(255, 127, 127, 127);
////
////      pimagepointera->m_bTransparent = false;
////
////   }
////   else
////   {
////
////      byte bAverage = (byte)((iR + iG + iB) / (3 * c));
////
////      double bLite = 127 + 63;
////
////      double bDark = 127 - 63;
////
////      if (bAverage > bLite) // Light
////      {
////
////         crBack = argb(255, 255, 255, 255);
////
////         pimagepointera->m_bTransparent = true;
////
////      }
////      else if (bAverage < bDark)
////      {
////
////         crBack = argb(255, 0, 0, 0);
////
////         pimagepointera->m_bTransparent = true;
////
////      }
////      else
////      {
////
////         crBack = argb(255, 127, 127, 127);
////
////         pimagepointera->m_bTransparent = false;
////
////      }
////
////
////   }
////
////   pimagepointera->m_colorTransparent = crBack;
////
////   return true;
//
//}
//
//
//
//
//
