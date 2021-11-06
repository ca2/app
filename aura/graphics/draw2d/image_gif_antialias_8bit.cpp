#include "framework.h"



#define pixel(x, y) (ba[(pointer->m_rectangle.height() - (y) - 1) * iScan + (x)])

//#define trans(color, alpha, un) (color * color * alpha * un / (255.0 * 255.0))
#define trans(color, alpha, un) (color * alpha /  255.0)

bool draw2d_gif_antialias_8bit(image & imageCompose, image_frame_array * pimagepointera, image_pointer * pointer, int uFrameIndex, u8 * ba, int iScan, colorref_array & cra, int transparentIndex)
{

   return true;

//   ::color32_t color32;
//
//   ::color::color crBack = imagea.m_colorTransparent;
//
//   double dA1 = colorref_get_a_value(crBack);
//
//   double dR1 = colorref_get_r_value(crBack);
//
//   double dG1 = colorref_get_g_value(crBack);
//
//   double dB1 = colorref_get_b_value(crBack);
//
//   bool bUnequal = true;
//
//   double dUnequal = 10.0;
//
//   double dUnequalScaleDown = 1.00;
//
//   double dUnequalRate = 10.0;
//
//   double dUnequalAddUp = 0.00;
//
//   double dUnequalDarken = 0.5;
//
//   double dTransparent = 4.0;
//
//   int w = pointer->m_pimage->m_iScan / sizeof(::color32_t);
//
//   int i = 0;
//
//   index x;
//
//   index y;
//
//   bool bTransparent;
//   //      goto skip1;
//
//
//   for (index iPass = 0; iPass < 1; iPass++)
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
//            double dA = colorref_get_a_value(color32);
//
//            double dR = colorref_get_r_value(color32);
//
//            double dG = colorref_get_g_value(color32);
//
//            double dB = colorref_get_b_value(color32);
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
//                  double dA2;
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
//                     (byte)dA,
//                     (byte)(trans(dR, dA, dUnequalDarken)),
//                     (byte)(trans(dG, dA, dUnequalDarken)),
//                     (byte)(trans(dB, dA, dUnequalDarken)));
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
//            //pointer->m_pimage->m_pcolorref[iPixel] = argb((byte)255, (byte)dR, (byte)dG, (byte)dB);
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
//            double dA = colorref_get_a_value(color32);
//
//            double dR = colorref_get_r_value(color32);
//
//            double dG = colorref_get_g_value(color32);
//
//            double dB = colorref_get_b_value(color32);
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
//                  double dA2;
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
//                     (byte)dA,
//                     (byte)(trans(dR, dA, dUnequalDarken)),
//                     (byte)(trans(dG, dA, dUnequalDarken)),
//                     (byte)(trans(dB, dA, dUnequalDarken)));
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
//            //pointer->m_pimage->m_pcolorref[iPixel] = argb((byte)255, (byte)dR, (byte)dG, (byte)dB);
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
//            double dA = colorref_get_a_value(color32);
//
//            double dR = colorref_get_r_value(color32);
//
//            double dG = colorref_get_g_value(color32);
//
//            double dB = colorref_get_b_value(color32);
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
//                  double dA2;
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
//                     (byte)dA,
//                     (byte)(trans(dR, dA, dUnequalDarken)),
//                     (byte)(trans(dG, dA, dUnequalDarken)),
//                     (byte)(trans(dB, dA, dUnequalDarken)));
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
//            //pointer->m_pimage->m_pcolorref[iPixel] = argb((byte)255, (byte)dR, (byte)dG, (byte)dB);
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
//            double dA = colorref_get_a_value(color32);
//
//            double dR = colorref_get_r_value(color32);
//
//            double dG = colorref_get_g_value(color32);
//
//            double dB = colorref_get_b_value(color32);
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
//                  double dA2;
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
//                     (byte)dA,
//                     (byte)(trans(dR, dA, dUnequalDarken)),
//                     (byte)(trans(dG, dA, dUnequalDarken)),
//                     (byte)(trans(dB, dA, dUnequalDarken)));
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
//            //pointer->m_pimage->m_pcolorref[iPixel] = argb((byte)255, (byte)dR, (byte)dG, (byte)dB);
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
//            double dA = colorref_get_a_value(color32);
//
//            double dR = colorref_get_r_value(color32);
//
//            double dG = colorref_get_g_value(color32);
//
//            double dB = colorref_get_b_value(color32);
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
//                  double dA2;
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
//                     (byte)dA,
//                     (byte)(trans(dR, dA, dUnequalDarken)),
//                     (byte)(trans(dG, dA, dUnequalDarken)),
//                     (byte)(trans(dB, dA, dUnequalDarken)));
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
//            //pointer->m_pimage->m_pcolorref[iPixel] = argb((byte)255, (byte)dR, (byte)dG, (byte)dB);
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
//            double dA = colorref_get_a_value(color32);
//
//            double dR = colorref_get_r_value(color32);
//
//            double dG = colorref_get_g_value(color32);
//
//            double dB = colorref_get_b_value(color32);
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
//                  double dA2;
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
//                     (byte)dA,
//                     (byte)(trans(dR, dA, dUnequalDarken)),
//                     (byte)(trans(dG, dA, dUnequalDarken)),
//                     (byte)(trans(dB, dA, dUnequalDarken)));
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
//            //               // pointer->m_pimage->m_pcolorref[iPixel] = argb((byte)dA, (byte)dR, (byte)dG, (byte)dB);
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
//            double dA = colorref_get_a_value(color32);
//
//            double dR = colorref_get_r_value(color32);
//
//            double dG = colorref_get_g_value(color32);
//
//            double dB = colorref_get_b_value(color32);
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
//                  double dA2;
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
//                     (byte)dA,
//                     (byte)(trans(dR, dA, dUnequalDarken)),
//                     (byte)(trans(dG, dA, dUnequalDarken)),
//                     (byte)(trans(dB, dA, dUnequalDarken)));
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
//            //             // pointer->m_pimage->m_pcolorref[iPixel] = argb((byte)dA, (byte)dR, (byte)dG, (byte)dB);
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
//            double dA = colorref_get_a_value(color32);
//
//            double dR = colorref_get_r_value(color32);
//
//            double dG = colorref_get_g_value(color32);
//
//            double dB = colorref_get_b_value(color32);
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
//                  double dA2;
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
//                     (byte)dA,
//                     (byte)(trans(dR, dA, dUnequalDarken)),
//                     (byte)(trans(dG, dA, dUnequalDarken)),
//                     (byte)(trans(dB, dA, dUnequalDarken)));
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
//            // pointer->m_pimage->m_pcolorref[iPixel] = argb((byte)dA, (byte)dR, (byte)dG, (byte)dB);
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
//            double dA = colorref_get_a_value(color32);
//
//            double dR = colorref_get_r_value(color32);
//
//            double dG = colorref_get_g_value(color32);
//
//            double dB = colorref_get_b_value(color32);
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
//                  double dA2;
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
//                     (byte)dA,
//                     (byte)(trans(dR, dA, dUnequalDarken)),
//                     (byte)(trans(dG, dA, dUnequalDarken)),
//                     (byte)(trans(dB, dA, dUnequalDarken)));
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
//            // pointer->m_pimage->m_pcolorref[iPixel] = argb((byte)dA, (byte)dR, (byte)dG, (byte)dB);
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
//            double dA = colorref_get_a_value(color32);
//
//            double dR = colorref_get_r_value(color32);
//
//            double dG = colorref_get_g_value(color32);
//
//            double dB = colorref_get_b_value(color32);
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
//                  double dA2;
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
//                     (byte)dA,
//                     (byte)(trans(dR, dA, dUnequalDarken)),
//                     (byte)(trans(dG, dA, dUnequalDarken)),
//                     (byte)(trans(dB, dA, dUnequalDarken)));
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
//            // pointer->m_pimage->m_pcolorref[iPixel] = argb((byte)dA, (byte)dR, (byte)dG, (byte)dB);
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
//            double dA = colorref_get_a_value(color32);
//
//            double dR = colorref_get_r_value(color32);
//
//            double dG = colorref_get_g_value(color32);
//
//            double dB = colorref_get_b_value(color32);
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
//                  double dA2;
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
//                     (byte)dA,
//                     (byte)(trans(dR, dA, dUnequalDarken)),
//                     (byte)(trans(dG, dA, dUnequalDarken)),
//                     (byte)(trans(dB, dA, dUnequalDarken)));
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
//            // pointer->m_pimage->m_pcolorref[iPixel] = argb((byte)dA, (byte)dR, (byte)dG, (byte)dB);
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
//            double dA = colorref_get_a_value(color32);
//
//            double dR = colorref_get_r_value(color32);
//
//            double dG = colorref_get_g_value(color32);
//
//            double dB = colorref_get_b_value(color32);
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
//                  double dA2;
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
//                     (byte)dA,
//                     (byte)(trans(dR, dA, dUnequalDarken)),
//                     (byte)(trans(dG, dA, dUnequalDarken)),
//                     (byte)(trans(dB, dA, dUnequalDarken)));
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
//            // pointer->m_pimage->m_pcolorref[iPixel] = argb((byte)dA, (byte)dR, (byte)dG, (byte)dB);
//
//         }
//
//      }
//
//
//
//
//   }
//
//
//   return true;

}
