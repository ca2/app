#include "framework.h"
#include "frame_array.h"


namespace image
{

#define pixel(x, y) (ba[(pointer->m_rectangle.height() - (y) - 1) * iScan + (x)])

//#define trans(color, alpha, un) (color * color * alpha * un / (255.0 * 255.0))
#define trans(color, alpha, un) (color * alpha /  255.0)

bool draw2d_gif_antialias_8bit(::image::image & imageCompose, image_frame_array * pimagepointera, ::image::image_pointer * pointer, ::i32 uFrameIndex, ::u8 * ba, ::i32 iScan, color_array & colora, ::i32 transparentIndex)
{

   return true;

//   ::color32_t color32;
//
//   ::color::color crBack = imagea.m_colorTransparent;
//
//   ::f64 dA1 = color32_byte_opacity(crBack);
//
//   ::f64 dR1 = color32_byte_red(crBack);
//
//   ::f64 dG1 = color32_byte_green(crBack);
//
//   ::f64 dB1 = color32_byte_blue(crBack);
//
//   bool bUnequal = true;
//
//   ::f64 dUnequal = 10.0;
//
//   ::f64 dUnequalScaleDown = 1.00;
//
//   ::f64 dUnequalRate = 10.0;
//
//   ::f64 dUnequalAddUp = 0.00;
//
//   ::f64 dUnequalDarken = 0.5;
//
//   ::f64 dTransparent = 4.0;
//
//   ::i32 w = pointer->m_pimage->m_iScan / sizeof(::color32_t);
//
//   ::i32 i = 0;
//
//   index x;
//
//   index y;
//
//   bool bTransparent;
//   //      goto skip1;
//
//
//   for (::collection::index iPass = 0; iPass < 1; iPass++)
//   {
//
//      for (y = 0; y < pointer->m_pimage->height(); y++)
//      {
//
//         bTransparent = false;
//
//         for (x = 0; x < pointer->m_pimage->width(); x++)
//         {
//
//            index iPixel = y * w + x;
//
//            color32 = pointer->m_pimage->m_pcolorref[iPixel];
//
//            ::f64 dA = color32_byte_opacity(color32);
//
//            ::f64 dR = color32_byte_red(color32);
//
//            ::f64 dG = color32_byte_green(color32);
//
//            ::f64 dB = color32_byte_blue(color32);
//
//            if (dA <= dTransparent)
//            {
//
//               bTransparent = true;
//
//               continue;
//
//            }
//
//            if (bUnequal && bTransparent)
//            {
//
//               if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
//               {
//
//                  ::f64 dA2;
//
//                  if (dR1 < 127)
//                  {
//
//                     dA2 = maximum(dR, maximum(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - minimum(dR, minimum(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = argb(
//                     (::u8)dA,
//                     (::u8)(trans(dR, dA, dUnequalDarken)),
//                     (::u8)(trans(dG, dA, dUnequalDarken)),
//                     (::u8)(trans(dB, dA, dUnequalDarken)));
//
//                  continue;
//
//               }
//               else
//               {
//
//                  bTransparent = false;
//
//               }
//
//            }
//            else
//            {
//
//               bTransparent = false;
//
//            }
//
//            //pointer->m_pimage->m_pcolorref[iPixel] = argb((::u8)255, (::u8)dR, (::u8)dG, (::u8)dB);
//
//         }
//
//
//
//         x--;
//
//         for (; x >= 0; x--)
//         {
//
//            index iPixel = y * w + x;
//
//            color32 = pointer->m_pimage->m_pcolorref[iPixel];
//
//            ::f64 dA = color32_byte_opacity(color32);
//
//            ::f64 dR = color32_byte_red(color32);
//
//            ::f64 dG = color32_byte_green(color32);
//
//            ::f64 dB = color32_byte_blue(color32);
//
//            if (dA <= dTransparent)
//            {
//
//               bTransparent = true;
//
//               continue;
//
//            }
//
//            if (bUnequal && bTransparent)
//            {
//
//               if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
//               {
//
//                  ::f64 dA2;
//
//                  if (dR1 < 127)
//                  {
//
//                     dA2 = maximum(dR, maximum(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - minimum(dR, minimum(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = argb(
//                     (::u8)dA,
//                     (::u8)(trans(dR, dA, dUnequalDarken)),
//                     (::u8)(trans(dG, dA, dUnequalDarken)),
//                     (::u8)(trans(dB, dA, dUnequalDarken)));
//
//                  continue;
//
//               }
//               else
//               {
//
//                  bTransparent = false;
//
//               }
//
//            }
//            else
//            {
//
//               bTransparent = false;
//
//            }
//
//            //pointer->m_pimage->m_pcolorref[iPixel] = argb((::u8)255, (::u8)dR, (::u8)dG, (::u8)dB);
//
//         }
//
//      }
//
//
//      dUnequal *= dUnequalScaleDown;
//
//
//      for (x = 0; x < pointer->m_pimage->width(); x++)
//      {
//
//         for (y = 0; y < pointer->m_pimage->height(); y++)
//         {
//
//            index iPixel = y * w + x;
//
//            color32 = pointer->m_pimage->m_pcolorref[iPixel];
//
//            ::f64 dA = color32_byte_opacity(color32);
//
//            ::f64 dR = color32_byte_red(color32);
//
//            ::f64 dG = color32_byte_green(color32);
//
//            ::f64 dB = color32_byte_blue(color32);
//
//            if (dA <= dTransparent)
//            {
//
//               bTransparent = true;
//
//               continue;
//
//            }
//
//            if (bUnequal && bTransparent)
//            {
//
//               if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
//               {
//
//                  ::f64 dA2;
//
//                  if (dR1 < 127)
//                  {
//
//                     dA2 = maximum(dR, maximum(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - minimum(dR, minimum(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = argb(
//                     (::u8)dA,
//                     (::u8)(trans(dR, dA, dUnequalDarken)),
//                     (::u8)(trans(dG, dA, dUnequalDarken)),
//                     (::u8)(trans(dB, dA, dUnequalDarken)));
//
//                  continue;
//
//               }
//               else
//               {
//
//                  bTransparent = false;
//
//               }
//
//            }
//            else
//            {
//
//               bTransparent = false;
//
//            }
//
//            //pointer->m_pimage->m_pcolorref[iPixel] = argb((::u8)255, (::u8)dR, (::u8)dG, (::u8)dB);
//
//         }
//
//         bTransparent = pointer->m_rectangle.bottom == imagea.height(); // borders transparent?
//
//         y--;
//
//         for (; y >= 0; y--)
//         {
//
//            index iPixel = y * w + x;
//
//            color32 = pointer->m_pimage->m_pcolorref[iPixel];
//
//            ::f64 dA = color32_byte_opacity(color32);
//
//            ::f64 dR = color32_byte_red(color32);
//
//            ::f64 dG = color32_byte_green(color32);
//
//            ::f64 dB = color32_byte_blue(color32);
//
//            if (dA <= dTransparent)
//            {
//
//               bTransparent = true;
//
//               continue;
//
//            }
//
//            if (bUnequal && bTransparent)
//            {
//
//               if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
//               {
//
//                  ::f64 dA2;
//
//                  if (dR1 < 127)
//                  {
//
//                     dA2 = maximum(dR, maximum(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - minimum(dR, minimum(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = argb(
//                     (::u8)dA,
//                     (::u8)(trans(dR, dA, dUnequalDarken)),
//                     (::u8)(trans(dG, dA, dUnequalDarken)),
//                     (::u8)(trans(dB, dA, dUnequalDarken)));
//
//                  continue;
//
//               }
//               else
//               {
//
//                  bTransparent = false;
//
//               }
//
//            }
//            else
//            {
//
//               bTransparent = false;
//
//            }
//
//            //pointer->m_pimage->m_pcolorref[iPixel] = argb((::u8)255, (::u8)dR, (::u8)dG, (::u8)dB);
//
//         }
//
//      }
//
//
//
//      dUnequal *= dUnequalScaleDown;
//
//
//
//      for (y = 0; y < pointer->m_pimage->height(); y++)
//      {
//
//         bTransparent = pointer->m_rectangle.left == 0; // borders transparent?
//
//         for (x = 0; x < pointer->m_pimage->width() && y + x < pointer->m_pimage->height(); x++)
//         {
//
//            index iPixel = (y + x) * w + x;
//
//            color32 = pointer->m_pimage->m_pcolorref[iPixel];
//
//            ::f64 dA = color32_byte_opacity(color32);
//
//            ::f64 dR = color32_byte_red(color32);
//
//            ::f64 dG = color32_byte_green(color32);
//
//            ::f64 dB = color32_byte_blue(color32);
//
//            if (dA <= dTransparent)
//            {
//
//               bTransparent = true;
//
//               continue;
//
//            }
//
//            if (bUnequal && bTransparent)
//            {
//
//               if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
//               {
//
//                  ::f64 dA2;
//
//                  if (dR1 < 127)
//                  {
//
//                     dA2 = maximum(dR, maximum(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - minimum(dR, minimum(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = argb(
//                     (::u8)dA,
//                     (::u8)(trans(dR, dA, dUnequalDarken)),
//                     (::u8)(trans(dG, dA, dUnequalDarken)),
//                     (::u8)(trans(dB, dA, dUnequalDarken)));
//
//                  continue;
//
//               }
//               else
//               {
//
//                  bTransparent = false;
//
//               }
//
//            }
//            else
//            {
//
//               bTransparent = false;
//
//            }
//
//            //pointer->m_pimage->m_pcolorref[iPixel] = argb((::u8)255, (::u8)dR, (::u8)dG, (::u8)dB);
//
//         }
//
//         bTransparent = pointer->m_rectangle.right == imagea.width(); // borders transparent?
//
//         x--;
//
//         for (; x >= 0; x--)
//         {
//
//            index iPixel = (y + x) * w + x;
//
//            color32 = pointer->m_pimage->m_pcolorref[iPixel];
//
//            ::f64 dA = color32_byte_opacity(color32);
//
//            ::f64 dR = color32_byte_red(color32);
//
//            ::f64 dG = color32_byte_green(color32);
//
//            ::f64 dB = color32_byte_blue(color32);
//
//            if (dA <= dTransparent)
//            {
//
//               bTransparent = true;
//
//               continue;
//
//            }
//
//            if (bUnequal && bTransparent)
//            {
//
//               if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
//               {
//
//                  ::f64 dA2;
//
//                  if (dR1 < 127)
//                  {
//
//                     dA2 = maximum(dR, maximum(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - minimum(dR, minimum(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = argb(
//                     (::u8)dA,
//                     (::u8)(trans(dR, dA, dUnequalDarken)),
//                     (::u8)(trans(dG, dA, dUnequalDarken)),
//                     (::u8)(trans(dB, dA, dUnequalDarken)));
//
//                  continue;
//
//               }
//               else
//               {
//
//                  bTransparent = false;
//
//               }
//
//            }
//            else
//            {
//
//               bTransparent = false;
//
//            }
//
//            //               // pointer->m_pimage->m_pcolorref[iPixel] = argb((::u8)dA, (::u8)dR, (::u8)dG, (::u8)dB);
//
//         }
//
//      }
//
//
//
//      dUnequal *= dUnequalScaleDown;
//
//
//      for (y = 0; y < pointer->m_pimage->height(); y++)
//      {
//
//         bTransparent = pointer->m_rectangle.left == 0; // borders transparent?
//
//         for (x = 0; x < pointer->m_pimage->width() && y - x >= 0; x++)
//         {
//
//            index iPixel = (y - x) * w + x;
//
//            color32 = pointer->m_pimage->m_pcolorref[iPixel];
//
//            ::f64 dA = color32_byte_opacity(color32);
//
//            ::f64 dR = color32_byte_red(color32);
//
//            ::f64 dG = color32_byte_green(color32);
//
//            ::f64 dB = color32_byte_blue(color32);
//
//            if (dA <= dTransparent)
//            {
//
//               bTransparent = true;
//
//               continue;
//
//            }
//
//            if (bUnequal && bTransparent)
//            {
//
//               if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
//               {
//
//                  ::f64 dA2;
//
//                  if (dR1 < 127)
//                  {
//
//                     dA2 = maximum(dR, maximum(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - minimum(dR, minimum(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = argb(
//                     (::u8)dA,
//                     (::u8)(trans(dR, dA, dUnequalDarken)),
//                     (::u8)(trans(dG, dA, dUnequalDarken)),
//                     (::u8)(trans(dB, dA, dUnequalDarken)));
//
//                  continue;
//
//               }
//               else
//               {
//
//                  bTransparent = false;
//
//               }
//
//            }
//            else
//            {
//
//               bTransparent = false;
//
//            }
//
//            //             // pointer->m_pimage->m_pcolorref[iPixel] = argb((::u8)dA, (::u8)dR, (::u8)dG, (::u8)dB);
//
//         }
//
//         bTransparent = pointer->m_rectangle.right == imagea.width(); // borders transparent?
//
//         x--;
//
//         for (; x >= 0; x--)
//         {
//
//            index iPixel = (y - x) * w + x;
//
//            color32 = pointer->m_pimage->m_pcolorref[iPixel];
//
//            ::f64 dA = color32_byte_opacity(color32);
//
//            ::f64 dR = color32_byte_red(color32);
//
//            ::f64 dG = color32_byte_green(color32);
//
//            ::f64 dB = color32_byte_blue(color32);
//
//            if (dA <= dTransparent)
//            {
//
//               bTransparent = true;
//
//               continue;
//
//            }
//
//            if (bUnequal && bTransparent)
//            {
//
//               if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
//               {
//
//                  ::f64 dA2;
//
//                  if (dR1 < 127)
//                  {
//
//                     dA2 = maximum(dR, maximum(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - minimum(dR, minimum(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = argb(
//                     (::u8)dA,
//                     (::u8)(trans(dR, dA, dUnequalDarken)),
//                     (::u8)(trans(dG, dA, dUnequalDarken)),
//                     (::u8)(trans(dB, dA, dUnequalDarken)));
//
//                  continue;
//
//               }
//               else
//               {
//
//                  bTransparent = false;
//
//               }
//
//            }
//            else
//            {
//
//               bTransparent = false;
//
//            }
//
//            // pointer->m_pimage->m_pcolorref[iPixel] = argb((::u8)dA, (::u8)dR, (::u8)dG, (::u8)dB);
//
//         }
//
//      }
//
//
//
//      dUnequal *= dUnequalScaleDown;
//
//
//
//      for (x = 0; x < pointer->m_pimage->width(); x++)
//      {
//
//         bTransparent = pointer->m_rectangle.top == 0; // borders transparent?
//
//         for (y = pointer->m_pimage->height() - 1; y >= 0 && x + (y - pointer->m_pimage->height() + 1) < pointer->m_pimage->width(); y--)
//         {
//
//            index iPixel = y * w + x + (y - pointer->m_pimage->height() + 1);
//
//            color32 = pointer->m_pimage->m_pcolorref[iPixel];
//
//            ::f64 dA = color32_byte_opacity(color32);
//
//            ::f64 dR = color32_byte_red(color32);
//
//            ::f64 dG = color32_byte_green(color32);
//
//            ::f64 dB = color32_byte_blue(color32);
//
//            if (dA <= dTransparent)
//            {
//
//               bTransparent = true;
//
//               continue;
//
//            }
//
//            if (bUnequal && bTransparent)
//            {
//
//               if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
//               {
//
//                  ::f64 dA2;
//
//                  if (dR1 < 127)
//                  {
//
//                     dA2 = maximum(dR, maximum(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - minimum(dR, minimum(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = argb(
//                     (::u8)dA,
//                     (::u8)(trans(dR, dA, dUnequalDarken)),
//                     (::u8)(trans(dG, dA, dUnequalDarken)),
//                     (::u8)(trans(dB, dA, dUnequalDarken)));
//
//                  continue;
//
//               }
//               else
//               {
//
//                  bTransparent = false;
//
//               }
//
//            }
//            else
//            {
//
//               bTransparent = false;
//
//            }
//
//            // pointer->m_pimage->m_pcolorref[iPixel] = argb((::u8)dA, (::u8)dR, (::u8)dG, (::u8)dB);
//
//         }
//
//         bTransparent = false;
//
//         y++;
//
//         for (; y < pointer->m_pimage->height(); y++)
//         {
//
//            index iPixel = y * w + x + (y - pointer->m_pimage->height() + 1);
//
//            color32 = pointer->m_pimage->m_pcolorref[iPixel];
//
//            ::f64 dA = color32_byte_opacity(color32);
//
//            ::f64 dR = color32_byte_red(color32);
//
//            ::f64 dG = color32_byte_green(color32);
//
//            ::f64 dB = color32_byte_blue(color32);
//
//            if (dA <= dTransparent)
//            {
//
//               bTransparent = true;
//
//               continue;
//
//            }
//
//            if (bUnequal && bTransparent)
//            {
//
//               if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
//               {
//
//                  ::f64 dA2;
//
//                  if (dR1 < 127)
//                  {
//
//                     dA2 = maximum(dR, maximum(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - minimum(dR, minimum(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = argb(
//                     (::u8)dA,
//                     (::u8)(trans(dR, dA, dUnequalDarken)),
//                     (::u8)(trans(dG, dA, dUnequalDarken)),
//                     (::u8)(trans(dB, dA, dUnequalDarken)));
//
//                  continue;
//
//               }
//               else
//               {
//
//                  bTransparent = false;
//
//               }
//
//            }
//            else
//            {
//
//               bTransparent = false;
//
//            }
//
//            // pointer->m_pimage->m_pcolorref[iPixel] = argb((::u8)dA, (::u8)dR, (::u8)dG, (::u8)dB);
//
//         }
//
//      }
//
//      dUnequal *= dUnequalScaleDown;
//
//
//
//      for (x = 0; x < pointer->m_pimage->width(); x++)
//      {
//
//         bTransparent = false;
//
//         for (y = 0; y < pointer->m_pimage->height() && x + y < pointer->m_pimage->width(); y++)
//         {
//
//            index iPixel = y * w + x + y;
//
//            color32 = pointer->m_pimage->m_pcolorref[iPixel];
//
//            ::f64 dA = color32_byte_opacity(color32);
//
//            ::f64 dR = color32_byte_red(color32);
//
//            ::f64 dG = color32_byte_green(color32);
//
//            ::f64 dB = color32_byte_blue(color32);
//
//            if (dA <= dTransparent)
//            {
//
//               bTransparent = true;
//
//               continue;
//
//            }
//
//            if (bUnequal && bTransparent)
//            {
//
//               if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
//               {
//
//                  ::f64 dA2;
//
//                  if (dR1 < 127)
//                  {
//
//                     dA2 = maximum(dR, maximum(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - minimum(dR, minimum(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = argb(
//                     (::u8)dA,
//                     (::u8)(trans(dR, dA, dUnequalDarken)),
//                     (::u8)(trans(dG, dA, dUnequalDarken)),
//                     (::u8)(trans(dB, dA, dUnequalDarken)));
//
//                  continue;
//
//               }
//               else
//               {
//
//                  bTransparent = false;
//
//               }
//
//            }
//            else
//            {
//
//               bTransparent = false;
//
//            }
//
//            // pointer->m_pimage->m_pcolorref[iPixel] = argb((::u8)dA, (::u8)dR, (::u8)dG, (::u8)dB);
//
//         }
//
//         bTransparent = false;
//
//         y--;
//
//         for (; y >= 0; y--)
//         {
//
//            index iPixel = y * w + x + y;
//
//            color32 = pointer->m_pimage->m_pcolorref[iPixel];
//
//            ::f64 dA = color32_byte_opacity(color32);
//
//            ::f64 dR = color32_byte_red(color32);
//
//            ::f64 dG = color32_byte_green(color32);
//
//            ::f64 dB = color32_byte_blue(color32);
//
//            if (dA <= dTransparent)
//            {
//
//               bTransparent = true;
//
//               continue;
//
//            }
//
//            if (bUnequal && bTransparent)
//            {
//
//               if (unequal(dR, dR1, dUnequal) && unequal(dG, dG1, dUnequal) && unequal(dB, dB1, dUnequal))
//               {
//
//                  ::f64 dA2;
//
//                  if (dR1 < 127)
//                  {
//
//                     dA2 = maximum(dR, maximum(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - minimum(dR, minimum(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = argb(
//                     (::u8)dA,
//                     (::u8)(trans(dR, dA, dUnequalDarken)),
//                     (::u8)(trans(dG, dA, dUnequalDarken)),
//                     (::u8)(trans(dB, dA, dUnequalDarken)));
//
//                  continue;
//
//               }
//               else
//               {
//
//                  bTransparent = false;
//
//               }
//
//            }
//            else
//            {
//
//               bTransparent = false;
//
//            }
//
//            // pointer->m_pimage->m_pcolorref[iPixel] = argb((::u8)dA, (::u8)dR, (::u8)dG, (::u8)dB);
//
//         }
//
//      }
//   }
//
//
//   return true;

}


} // namespace image



