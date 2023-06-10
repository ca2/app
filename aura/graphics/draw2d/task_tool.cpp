#include "framework.h"
#include "task_tool.h"
#include "acme/graphics/draw2d/_image32.h"


namespace draw2d
{


   void task_tool_item::run()
   {

      if (m_eop == op_blend)
      {

         if (m_bA == 0)
         {
         }
         else if (m_bA == 255)
         {
            int y = m_y;
            int yEnd = m_yEnd;
            int x = m_x;
            int xEnd = m_xEnd;
            int xEnd1 = m_xEnd - 7;
            int ySkip = m_ySkip;

            u8 * pdst = m_pdst2;
            u8 * psrc = m_psrc2;
            u8 * pdst2;
            u8 * psrc2;
            u8 * pdst3;
            u8 * psrc3;
            u8 * src_opacity; // xmetrix, xmxstudio contribution
            u8 * src_transparency; // unicorn, zjrosen contribution
            int w = m_w;
            u8 * psrcOpacity = m_psrcOpacity; // Currently living in Milky Way, but minding of a place I don't remember
            u8 * psrcTransparency = m_psrcTransparency; // Stacie, Dylan, Tectuma (Kevin) and Matt contribution
#define DIB_BLEND_ZERO_BLOCK_SIZE_EIGHTH 64
#define DIB_BLEND_ZERO_BLOCK_SIZE 256
            ::color::color craZero[DIB_BLEND_ZERO_BLOCK_SIZE];

            zero(craZero);

            int scanDst = m_scanDst;
            int scanSrc = m_scanSrc;

            if (psrcOpacity != nullptr && psrcTransparency != nullptr)
            {

               for (; y < yEnd; y += ySkip)
               {

                  pdst2 = &pdst[scanDst * y];

                  psrc2 = &psrc[scanSrc * y];

                  src_opacity = &psrcOpacity[w * y];

                  src_transparency = &psrcTransparency[w * y];

                  pdst3 = pdst2;

                  psrc3 = psrc2;
                  //int x2;
                  int x = 0;
                  int x1 = -1;
                  for (; x < xEnd; x++)
                  {

                     if (src_transparency[x])
                     {
                        if (x1 >= 0)
                        {
                           ::memory_copy(&((::color32_t *)pdst3)[x1], &((::color32_t *)psrc3)[x1], (x - x1) * sizeof(::color32_t));
                           x1 = -1;
                        }

                        x += src_transparency[x] - 1;
                        pdst2 = &pdst3[x << 2];
                        psrc2 = &psrc3[x << 2];

                     }
                     else if (src_opacity[x])
                     {

                        if (x1 < 0)
                        {
                           x1 = x;
                        }
                        x += src_opacity[x] - 1;
                        pdst2 = &pdst3[x << 2];
                        psrc2 = &psrc3[x << 2];
                        // dst <= src
                     }
                     else
                     {
                        if (pdst2[3] == 0)
                        {
                           if (x1 < 0)
                           {
                              x1 = x;
                           }
                           // dst <= src
                        }
                        else
                        {
                           if (x1 >= 0)
                           {
                              ::memory_copy(&((::color32_t *)pdst3)[x1], &((::color32_t *)psrc3)[x1], (x - x1) * sizeof(::color32_t));
                              x1 = -1;
                           }
                           ::u8 bA2 = (::u8)~(::u8)psrc2[3];
                           pdst2[0] = psrc2[0] + ((pdst2[0] * bA2) >> 8);
                           pdst2[1] = psrc2[1] + ((pdst2[1] * bA2) >> 8);
                           pdst2[2] = psrc2[2] + ((pdst2[2] * bA2) >> 8);
                           pdst2[3] = psrc2[3] + ((pdst2[3] * bA2) >> 8);

                        }

                     }

                     pdst2 += 4;

                     psrc2 += 4;

                  }
                  if (x1 >= 0)
                  {
                     ::memory_copy(&((::color32_t *)pdst3)[x1], &((::color32_t *)psrc3)[x1], (x - x1) * sizeof(::color32_t));
                     x1 = -1;
                  }
                  //pdst2 += xEnd;
                  //psrc2 += xEnd;

               }
            }
            else
            {

               //u8 * pBound1;
               //u8 * pBound8;
               //u8 * pBound;
               //u8 * pEnd8;
               for (; y < yEnd; y += ySkip)
               {

                  pdst2 = &pdst[scanDst * y];

                  psrc2 = &psrc[scanSrc * y];

                  pdst3 = pdst2;

                  psrc3 = psrc2;
                  //int x2;
                  int x = 0;
                  int x1 = -1;
                  //int xDistanceToBoundary1;
                  //int xDistanceToBoundary8;
                  int xEnd8;
                  for (; x < xEnd; x++)
                  {

restart:
                     ;

                     ::u8 bA2 = psrc2[3];
                     if (bA2 == 0)
                     {
                        if (x1 >= 0)
                        {
                           ::memory_copy(&((::color32_t *)pdst3)[x1], &((::color32_t *)psrc3)[x1], (x - x1) * sizeof(::color32_t));
                           x1 = -1;
                        }

#if 0
                        //if (0)
                        {

                           pBound = psrc3 + (xEnd << 2);
                           xDistanceToBoundary8 = (((iptr)psrc2) % (DIB_BLEND_ZERO_BLOCK_SIZE_EIGHTH * 4));
                           xDistanceToBoundary1 = (((iptr)psrc2) % (DIB_BLEND_ZERO_BLOCK_SIZE * 4));
                           pBound8 = minimum(pBound, psrc2 + DIB_BLEND_ZERO_BLOCK_SIZE_EIGHTH * 4 - xDistanceToBoundary8);
                           pBound1 = minimum(pBound, psrc2 + DIB_BLEND_ZERO_BLOCK_SIZE * 4 - xDistanceToBoundary1);

                           if (xDistanceToBoundary8 > 0)
                           {

                              while (psrc2 < pBound && psrc2[3] == 0)
                              {

                                 psrc2 += 4;

                              }

                              if (psrc2 >= pBound)
                              {
                                 break;
                              }

                              if (psrc2[3] != 0)
                              {

                                 x = (psrc2 - psrc3) >> 2;

                                 pdst2 = &pdst3[x << 2];

                                 goto restart;

                              }

                              // boundary is zero

                           }
                           else
                           {

                              pBound8 = psrc2;

                              // boundary is zero

                           }


                           if (psrc2 == pBound8 && psrc2 != pBound1)
                           {

                              pEnd8 = minimum(pBound, pBound1);
                              while (psrc2 + DIB_BLEND_ZERO_BLOCK_SIZE_EIGHTH * 4 <= pEnd8
                                     && __memcmp(psrc2, craZero, DIB_BLEND_ZERO_BLOCK_SIZE_EIGHTH * 4) == 0)
                              {

                                 psrc2 += DIB_BLEND_ZERO_BLOCK_SIZE_EIGHTH * 4;

                              }

                              if (psrc2 >= pBound)
                              {

                                 break;

                              }

                              if (psrc2[3] != 0)
                              {

                                 x = (psrc2 - psrc3) >> 2;

                                 pdst2 = &pdst3[x << 2];

                                 goto restart;

                              }

                              // boundary is zero

                           }
                           else
                           {

                              pBound1 = psrc2;

                           }

                           if (psrc2 == pBound1)
                           {

                              while (psrc2 + DIB_BLEND_ZERO_BLOCK_SIZE * 4 <= pBound
                                     && __memcmp(psrc2, craZero, DIB_BLEND_ZERO_BLOCK_SIZE * 4) == 0)
                              {

                                 psrc2 += DIB_BLEND_ZERO_BLOCK_SIZE * 4;

                              }

                              if (psrc2 >= pBound)
                              {
                                 break;
                              }

                              if (psrc2[3] != 0)
                              {

                                 x = (psrc2 - psrc3) >> 2;

                                 pdst2 = &pdst3[x << 2];

                                 goto restart;

                              }

                              // boundary is zero

                           }

                           while (psrc2 < pBound && psrc2[3] == 0)
                           {

                              psrc2 += 4;

                           }


                           if (psrc2 >= pBound)
                           {
                              break;
                           }

                           x = (psrc2 - psrc3) >> 2;

                           pdst2 = &pdst3[x << 2];

                           if (psrc2[3] != 0)
                           {

                              goto restart;

                           }

                        }
#else

                        //if (0)
                        {

                           int xDistanceToBoundary8 = (((iptr)psrc2) % (DIB_BLEND_ZERO_BLOCK_SIZE_EIGHTH * 4)) / 4;
                           int xDistanceToBoundary1 = (((iptr)psrc2) % (DIB_BLEND_ZERO_BLOCK_SIZE * 4)) / 4;
                           int xBoundary8 = minimum(xEnd, x + DIB_BLEND_ZERO_BLOCK_SIZE_EIGHTH - xDistanceToBoundary8);
                           int xBoundary1 = minimum(xEnd, x + DIB_BLEND_ZERO_BLOCK_SIZE - xDistanceToBoundary1);

                           if (xDistanceToBoundary8 > 0)
                           {

                              while (x < xBoundary8 && !(((::image32_t *)psrc3)[x]).u8_opacity())
                              {

                                 x++;

                              }

                              if (x >= xEnd)
                              {
                                 break;
                              }

                              if ((((::image32_t *)psrc3)[x]).u8_opacity())
                              {

                                 pdst2 = &pdst3[x << 2];

                                 psrc2 = &psrc3[x << 2];

                                 goto restart;

                              }

                              // boundary is zero

                           }
                           else
                           {

                              xBoundary8 = x;

                              // boundary is zero

                           }


                           if (x == xBoundary8 && x != xBoundary1)
                           {

                              xEnd8 = minimum(xEnd, xBoundary1);
                              while (x + DIB_BLEND_ZERO_BLOCK_SIZE_EIGHTH <= xEnd8
                                     && memory_order(&(((::color32_t *)psrc3)[x]), craZero, DIB_BLEND_ZERO_BLOCK_SIZE_EIGHTH * 4) == 0)
                              {

                                 x += DIB_BLEND_ZERO_BLOCK_SIZE_EIGHTH;

                              }

                              if (x >= xEnd)
                              {

                                 break;

                              }

                              if ((((::image32_t *)psrc3)[x]).u8_opacity())
                              {

                                 pdst2 = &pdst3[x << 2];

                                 psrc2 = &psrc3[x << 2];

                                 goto restart;

                              }

                              // boundary is zero

                           }
                           else
                           {

                              xBoundary1 = x;

                           }

                           if (x == xBoundary1)
                           {

                              while (x + DIB_BLEND_ZERO_BLOCK_SIZE <= xEnd
                                     && memory_order(&(((::color32_t *)psrc3)[x]), craZero, sizeof(craZero)) == 0)
                              {

                                 x += DIB_BLEND_ZERO_BLOCK_SIZE;

                              }

                              if (x >= xEnd)
                              {

                                 break;

                              }

                              if ((((::image32_t *)psrc3)[x]).u8_opacity())
                              {

                                 pdst2 = &pdst3[x << 2];

                                 psrc2 = &psrc3[x << 2];

                                 goto restart;

                              }

                              // boundary is zero

                           }

                           while (x < xEnd && !(((::image32_t *)psrc3)[x]).u8_opacity())
                           {

                              x++;

                           }

                           if (x >= xEnd)
                           {
                              break;
                           }

                           pdst2 = &pdst3[x << 2];

                           psrc2 = &psrc3[x << 2];

                           if ((((::image32_t *)psrc3)[x]).u8_opacity())
                           {

                              goto restart;

                           }

                        }

#endif

                     }
                     else if (bA2 == 255)
                     {

                        if (x1 < 0)
                        {
                           x1 = x;
                        }
                        // dst <= src
                     }
                     else
                     {
                        if (pdst2[3] == 0)
                        {
                           if (x1 < 0)
                           {
                              x1 = x;
                           }
                           // dst <= src
                        }
                        else
                        {
                           if (x1 >= 0)
                           {
                              ::memory_copy(&((::color32_t *)pdst3)[x1], &((::color32_t *)psrc3)[x1], (x - x1) * sizeof(::color32_t));
                              x1 = -1;
                           }
                           bA2 = (::u8)~bA2;
                           pdst2[0] = psrc2[0] + ((pdst2[0] * bA2) >> 8);
                           pdst2[1] = psrc2[1] + ((pdst2[1] * bA2) >> 8);
                           pdst2[2] = psrc2[2] + ((pdst2[2] * bA2) >> 8);
                           pdst2[3] = psrc2[3] + ((pdst2[3] * bA2) >> 8);

                        }

                     }

                     pdst2 += 4;

                     psrc2 += 4;

                  }
                  if (x1 >= 0)
                  {
                     ::memory_copy(&((::color32_t *)pdst3)[x1], &((::color32_t *)psrc3)[x1], (x - x1) * sizeof(::color32_t));
                     x1 = -1;
                  }
                  //pdst2 += xEnd;
                  //psrc2 += xEnd;

               }

            }
         }

         else
         {
            //return;
            ::u8 bA = m_bA;
            int y = m_y;
            int yEnd = m_yEnd;
            int x = m_x;
            int xEnd = m_xEnd;
            int xEnd1 = m_xEnd - 7;
            int ySkip = m_ySkip;
            //u8 * src_opacity; // xmetrix, xmxstudio contribution
            u8 * src_transparency; // unicorn, zjrosen contribution
            int w = m_w;
            u8 * psrcOpacity = m_psrcOpacity; // Currently living in Milky Way, but minding of a place I don't remember
            u8 * psrcTransparency = m_psrcTransparency; // Stacie, Dylan, Tectuma (Kevin) and Matt contribution

            u8 * pdst = m_pdst2;
            u8 * psrc = m_psrc2;
            u8 * pdst2;
            u8 * psrc2;
            u8 * pdst3;
            u8 * psrc3;

            int scanDst = m_scanDst;
            int scanSrc = m_scanSrc;

            if (psrcTransparency != nullptr)
            {

               for (; y < yEnd; y += ySkip)
               {

                  pdst2 = &pdst[scanDst * y];

                  psrc2 = &psrc[scanSrc * y];
                  //                  src_opacity = &psrcOpacity[w * y];

                  src_transparency = &psrcTransparency[w * y];

                  pdst3 = pdst2;

                  psrc3 = psrc2;

                  int x = 0;
                  for (; x < xEnd; x++)
                  {

                     ::u8 bA2 = psrc2[3];
                     if (src_transparency[x])
                     {
                        x += src_transparency[x] - 1;
                        pdst2 = &pdst3[x << 2];
                        psrc2 = &psrc3[x << 2];
                     }
                     else if (pdst2[3] == 0)
                     {
                        pdst2[0] = (psrc2[0] * bA) >> 8;
                        pdst2[1] = (psrc2[1] * bA) >> 8;
                        pdst2[2] = (psrc2[2] * bA) >> 8;
                        pdst2[3] = (psrc2[3] * bA) >> 8;
                     }
                     else
                     {

                        ::u8 bA3 = ((u16)~((u16)bA2 * (u16)bA)) >> 8;
                        pdst2[0] = (psrc2[0] * bA + pdst2[0] * bA3) >> 8;
                        pdst2[1] = (psrc2[1] * bA + pdst2[1] * bA3) >> 8;
                        pdst2[2] = (psrc2[2] * bA + pdst2[2] * bA3) >> 8;
                        pdst2[3] = (psrc2[3] * bA + pdst2[3] * bA3) >> 8;

                     }

                     pdst2 += 4;

                     psrc2 += 4;

                  }

               }

            }
            else
            {

               for (; y < yEnd; y += ySkip)
               {

                  pdst2 = &pdst[scanDst * y];

                  psrc2 = &psrc[scanSrc * y];

                  pdst3 = pdst2;

                  psrc3 = psrc2;

                  int x = 0;
                  for (; x < xEnd; x++)
                  {

                     ::u8 bA2 = psrc2[3];
                     if (bA2 == 0)
                     {
                     }
                     else if (pdst2[3] == 0)
                     {
                        pdst2[0] = (psrc2[0] * bA) >> 8;
                        pdst2[1] = (psrc2[1] * bA) >> 8;
                        pdst2[2] = (psrc2[2] * bA) >> 8;
                        pdst2[3] = (psrc2[3] * bA) >> 8;
                     }
                     else
                     {

                        ::u8 bA3 = ((u16)~((u16)bA2 * (u16)bA)) >> 8;
                        pdst2[0] = (psrc2[0] * bA + pdst2[0] * bA3) >> 8;
                        pdst2[1] = (psrc2[1] * bA + pdst2[1] * bA3) >> 8;
                        pdst2[2] = (psrc2[2] * bA + pdst2[2] * bA3) >> 8;
                        pdst2[3] = (psrc2[3] * bA + pdst2[3] * bA3) >> 8;

                     }

                     pdst2 += 4;

                     psrc2 += 4;

                  }

               }

            }

         }

      }

      //return ::success;

   }


} // namespace draw2d



