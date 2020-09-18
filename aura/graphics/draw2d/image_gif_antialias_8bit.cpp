#include "framework.h"



#define pixel(x, y) (ba[(pointer->m_rect.height() - (y) - 1) * iScan + (x)])

//#define trans(color, alpha, un) (color * color * alpha * un / (255.0 * 255.0))
#define trans(color, alpha, un) (color * alpha /  255.0)

bool draw2d_gif_antialias_8bit(image & imageCompose, image_frame_array * pimagepointera, image_pointer * pointer, int uFrameIndex, u8 * ba, int iScan, colorref_array & cra, int transparentIndex)
{

   return true;

//   COLORREF cr;
//
//   COLORREF crBack = imagea.m_crTransparent;
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
//   int w = pointer->m_pimage->m_iScan / sizeof(COLORREF);
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
//            cr = pointer->m_pimage->m_pcolorref[iPixel];
//
//            double dA = colorref_get_a_value(cr);
//
//            double dR = colorref_get_r_value(cr);
//
//            double dG = colorref_get_g_value(cr);
//
//            double dB = colorref_get_b_value(cr);
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
//                     dA2 = max(dR, max(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - min(dR, min(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = ARGB(
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
//            //pointer->m_pimage->m_pcolorref[iPixel] = ARGB((byte)255, (byte)dR, (byte)dG, (byte)dB);
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
//            cr = pointer->m_pimage->m_pcolorref[iPixel];
//
//            double dA = colorref_get_a_value(cr);
//
//            double dR = colorref_get_r_value(cr);
//
//            double dG = colorref_get_g_value(cr);
//
//            double dB = colorref_get_b_value(cr);
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
//                     dA2 = max(dR, max(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - min(dR, min(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = ARGB(
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
//            //pointer->m_pimage->m_pcolorref[iPixel] = ARGB((byte)255, (byte)dR, (byte)dG, (byte)dB);
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
//            cr = pointer->m_pimage->m_pcolorref[iPixel];
//
//            double dA = colorref_get_a_value(cr);
//
//            double dR = colorref_get_r_value(cr);
//
//            double dG = colorref_get_g_value(cr);
//
//            double dB = colorref_get_b_value(cr);
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
//                     dA2 = max(dR, max(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - min(dR, min(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = ARGB(
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
//            //pointer->m_pimage->m_pcolorref[iPixel] = ARGB((byte)255, (byte)dR, (byte)dG, (byte)dB);
//
//         }
//
//         bTransparent = pointer->m_rect.bottom == imagea.height(); // borders transparent?
//
//         y--;
//
//         for (; y >= 0; y--)
//         {
//
//            index iPixel = y * w + x;
//
//            cr = pointer->m_pimage->m_pcolorref[iPixel];
//
//            double dA = colorref_get_a_value(cr);
//
//            double dR = colorref_get_r_value(cr);
//
//            double dG = colorref_get_g_value(cr);
//
//            double dB = colorref_get_b_value(cr);
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
//                     dA2 = max(dR, max(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - min(dR, min(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = ARGB(
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
//            //pointer->m_pimage->m_pcolorref[iPixel] = ARGB((byte)255, (byte)dR, (byte)dG, (byte)dB);
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
//         bTransparent = pointer->m_rect.left == 0; // borders transparent?
//
//         for (x = 0; x < pointer->m_pimage->width() && y + x < pointer->m_pimage->height(); x++)
//         {
//
//            index iPixel = (y + x) * w + x;
//
//            cr = pointer->m_pimage->m_pcolorref[iPixel];
//
//            double dA = colorref_get_a_value(cr);
//
//            double dR = colorref_get_r_value(cr);
//
//            double dG = colorref_get_g_value(cr);
//
//            double dB = colorref_get_b_value(cr);
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
//                     dA2 = max(dR, max(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - min(dR, min(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = ARGB(
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
//            //pointer->m_pimage->m_pcolorref[iPixel] = ARGB((byte)255, (byte)dR, (byte)dG, (byte)dB);
//
//         }
//
//         bTransparent = pointer->m_rect.right == imagea.width(); // borders transparent?
//
//         x--;
//
//         for (; x >= 0; x--)
//         {
//
//            index iPixel = (y + x) * w + x;
//
//            cr = pointer->m_pimage->m_pcolorref[iPixel];
//
//            double dA = colorref_get_a_value(cr);
//
//            double dR = colorref_get_r_value(cr);
//
//            double dG = colorref_get_g_value(cr);
//
//            double dB = colorref_get_b_value(cr);
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
//                     dA2 = max(dR, max(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - min(dR, min(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = ARGB(
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
//            //               // pointer->m_pimage->m_pcolorref[iPixel] = ARGB((byte)dA, (byte)dR, (byte)dG, (byte)dB);
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
//         bTransparent = pointer->m_rect.left == 0; // borders transparent?
//
//         for (x = 0; x < pointer->m_pimage->width() && y - x >= 0; x++)
//         {
//
//            index iPixel = (y - x) * w + x;
//
//            cr = pointer->m_pimage->m_pcolorref[iPixel];
//
//            double dA = colorref_get_a_value(cr);
//
//            double dR = colorref_get_r_value(cr);
//
//            double dG = colorref_get_g_value(cr);
//
//            double dB = colorref_get_b_value(cr);
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
//                     dA2 = max(dR, max(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - min(dR, min(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = ARGB(
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
//            //             // pointer->m_pimage->m_pcolorref[iPixel] = ARGB((byte)dA, (byte)dR, (byte)dG, (byte)dB);
//
//         }
//
//         bTransparent = pointer->m_rect.right == imagea.width(); // borders transparent?
//
//         x--;
//
//         for (; x >= 0; x--)
//         {
//
//            index iPixel = (y - x) * w + x;
//
//            cr = pointer->m_pimage->m_pcolorref[iPixel];
//
//            double dA = colorref_get_a_value(cr);
//
//            double dR = colorref_get_r_value(cr);
//
//            double dG = colorref_get_g_value(cr);
//
//            double dB = colorref_get_b_value(cr);
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
//                     dA2 = max(dR, max(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - min(dR, min(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = ARGB(
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
//            // pointer->m_pimage->m_pcolorref[iPixel] = ARGB((byte)dA, (byte)dR, (byte)dG, (byte)dB);
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
//         bTransparent = pointer->m_rect.top == 0; // borders transparent?
//
//         for (y = pointer->m_pimage->height() - 1; y >= 0 && x + (y - pointer->m_pimage->height() + 1) < pointer->m_pimage->width(); y--)
//         {
//
//            index iPixel = y * w + x + (y - pointer->m_pimage->height() + 1);
//
//            cr = pointer->m_pimage->m_pcolorref[iPixel];
//
//            double dA = colorref_get_a_value(cr);
//
//            double dR = colorref_get_r_value(cr);
//
//            double dG = colorref_get_g_value(cr);
//
//            double dB = colorref_get_b_value(cr);
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
//                     dA2 = max(dR, max(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - min(dR, min(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = ARGB(
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
//            // pointer->m_pimage->m_pcolorref[iPixel] = ARGB((byte)dA, (byte)dR, (byte)dG, (byte)dB);
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
//            cr = pointer->m_pimage->m_pcolorref[iPixel];
//
//            double dA = colorref_get_a_value(cr);
//
//            double dR = colorref_get_r_value(cr);
//
//            double dG = colorref_get_g_value(cr);
//
//            double dB = colorref_get_b_value(cr);
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
//                     dA2 = max(dR, max(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - min(dR, min(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = ARGB(
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
//            // pointer->m_pimage->m_pcolorref[iPixel] = ARGB((byte)dA, (byte)dR, (byte)dG, (byte)dB);
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
//            cr = pointer->m_pimage->m_pcolorref[iPixel];
//
//            double dA = colorref_get_a_value(cr);
//
//            double dR = colorref_get_r_value(cr);
//
//            double dG = colorref_get_g_value(cr);
//
//            double dB = colorref_get_b_value(cr);
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
//                     dA2 = max(dR, max(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - min(dR, min(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = ARGB(
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
//            // pointer->m_pimage->m_pcolorref[iPixel] = ARGB((byte)dA, (byte)dR, (byte)dG, (byte)dB);
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
//            cr = pointer->m_pimage->m_pcolorref[iPixel];
//
//            double dA = colorref_get_a_value(cr);
//
//            double dR = colorref_get_r_value(cr);
//
//            double dG = colorref_get_g_value(cr);
//
//            double dB = colorref_get_b_value(cr);
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
//                     dA2 = max(dR, max(dG, dB)) * dUnequalRate + dUnequalAddUp;
//
//                  }
//                  else
//                  {
//
//                     dA2 = (255.0 - min(dR, min(dG, dB))) * dUnequalRate + dUnequalAddUp;
//
//                  }
//
//                  dA = dA * dA2 / 255.0;
//
//                  pointer->m_pimage->m_pcolorref[iPixel] = ARGB(
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
//            // pointer->m_pimage->m_pcolorref[iPixel] = ARGB((byte)dA, (byte)dR, (byte)dG, (byte)dB);
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
