#include "framework.h"
#include "water_routine.h"
#include "acme/graphics/image/image32.h"


namespace draw2d
{


   water_routine::water_routine()
   {

      m_iHeightField1 = nullptr;
      m_iHeightField2 = nullptr;

      m_iWidth = 0;
      m_iHeight = 0;

      m_bDrawWithLight = true;
      m_iLightModifier = 1;
      m_iHpage = 0;
      m_density = 5;

   }


   water_routine::~water_routine()
   {

      // Cleanup
      if(m_iHeightField1 != nullptr)
         delete [] m_iHeightField1;
      if(m_iHeightField2 != nullptr)
         delete [] m_iHeightField2;

      m_iHeightField1 = nullptr;
      m_iHeightField2 = nullptr;
      
   }


   void water_routine::create(int iWidth,int iHeight, struct color_indexes indexes)
   {

      m_colorindexes = indexes;

      if(m_iHeightField1 != nullptr)
         delete [] m_iHeightField1;
      if(m_iHeightField2 != nullptr)
         delete [] m_iHeightField2;

      // create our height fields
      m_iHeightField1 = __raw_new int[iWidth*iHeight];
      m_iHeightField2 = __raw_new int[iWidth*iHeight];

      // clear our height fields
      memory_set(m_iHeightField1,0,(iWidth*iHeight)*sizeof(int));
      memory_set(m_iHeightField2,0,(iWidth*iHeight)*sizeof(int));

      m_iWidth = iWidth;
      m_iHeight = iHeight;

      // set our page to 0
      m_iHpage = 0;

   }
   void water_routine::FlattenWater()
   {
      // clear our height fields
      memory_set(m_iHeightField1,0,(m_iWidth*m_iHeight)*sizeof(int));
      memory_set(m_iHeightField2,0,(m_iWidth*m_iHeight)*sizeof(int));
   }


   void water_routine::to(::image32_t * pSrcImage, ::image32_t * pTargetImage)
   {
      
      // Yes they have to be the same size...(for now)
      if(m_bDrawWithLight == false)
      {
         
         DrawWaterNoLight(m_iHpage,pSrcImage,pTargetImage);
         
      }
      else
      {
         
         DrawWaterWithLight(m_iHpage,m_iLightModifier,pSrcImage,pTargetImage);
         
      }
      
      CalcWater(m_iHpage,m_density);

      m_iHpage ^= 1;

   }


   void water_routine::CalcWater(int npage, int density)
   {
      
      int newh;
      int count = m_iWidth + 1;
      int *newptr;
      int *oldptr;

      // set up the pointers
      if(npage == 0)
      {
         
         newptr = &m_iHeightField1[0];
         oldptr = &m_iHeightField2[0];
         
      }
      else
      {
         
         newptr = &m_iHeightField2[0];
         oldptr = &m_iHeightField1[0];
         
      }

      int x, y;

      // Sorry, this function might not be as readable as I'd like, because
      // I optimized it somewhat.  (enough to make me feel satisfied with it)

      for (y = (m_iHeight-1)*m_iWidth; count < y; count += 2)
      {
         
         for (x = count+m_iWidth-2; count < x; count++)
         {

            // This does the eight-pixel method.  It looks much better.

            newh          = ((oldptr[count + m_iWidth]
                              + oldptr[count - m_iWidth]
                              + oldptr[count + 1]
                              + oldptr[count - 1]
                              + oldptr[count - m_iWidth - 1]
                              + oldptr[count - m_iWidth + 1]
                              + oldptr[count + m_iWidth - 1]
                              + oldptr[count + m_iWidth + 1]
                             ) >> 2 )
                            - newptr[count];

            newptr[count] =  newh - (newh >> density);
            /*
            // This is the "sludge" method...
                  newh = (oldptr[count]<<2)
                       +  oldptr[count-1-m_iWidth]
                       +  oldptr[count+1-m_iWidth]
                       +  oldptr[count-1+m_iWidth]
                       +  oldptr[count+1+m_iWidth]
                       + ((oldptr[count-1]
                       +   oldptr[count+1]
                       +   oldptr[count-m_iWidth]
                       +   oldptr[count+m_iWidth])<<1);

                  newptr[count] = (newh-(newh>>6)) >> density;
            */
            
         }
         
      }
      
   }


   void water_routine::SmoothWater(int npage)
   {
      
      int newh;
      int count = m_iWidth + 1;

      int *newptr;
      int *oldptr;

      // set up the pointers
      if(npage == 0)
      {
         
         newptr = &m_iHeightField1[0];
         oldptr = &m_iHeightField2[0];
         
      }
      else
      {
         
         newptr = &m_iHeightField2[0];
         oldptr = &m_iHeightField1[0];
         
      }

      int x, y;

      // Sorry, this function might not be as readable as I'd like, because
      // I optimized it somewhat.  (enough to make me feel satisfied with it)

      for(y=1; y<m_iHeight-1; y++)
      {
         
         for(x=1; x<m_iWidth-1; x++)
         {
            // This does the eight-pixel method.  It looks much better.

            newh          = ((oldptr[count + m_iWidth]
                              + oldptr[count - m_iWidth]
                              + oldptr[count + 1]
                              + oldptr[count - 1]
                              + oldptr[count - m_iWidth - 1]
                              + oldptr[count - m_iWidth + 1]
                              + oldptr[count + m_iWidth - 1]
                              + oldptr[count + m_iWidth + 1]
                             ) >> 3 )
                            + newptr[count];


            newptr[count] =  newh>>1;
            count++;
         }
         count += 2;
      }
   }

   void water_routine::CalcWaterBigFilter(int npage, int density)
   {
      int newh;
      int count = (2*m_iWidth) + 2;

      int *newptr;
      int *oldptr;

      // set up the pointers
      if(npage == 0)
      {
         newptr = &m_iHeightField1[0];
         oldptr = &m_iHeightField2[0];
      }
      else
      {
         newptr = &m_iHeightField2[0];
         oldptr = &m_iHeightField1[0];
      }

      int x, y;

      // Sorry, this function might not be as readable as I'd like, because
      // I optimized it somewhat.  (enough to make me feel satisfied with it)

      for(y=2; y<m_iHeight-2; y++)
      {
         for(x=2; x<m_iWidth-2; x++)
         {
            // This does the 25-pixel method.  It looks much okay.

            newh        = (
                          (
                          (
                          (oldptr[count + m_iWidth]
                           + oldptr[count - m_iWidth]
                           + oldptr[count + 1]
                           + oldptr[count - 1]
                          )<<1)
                          + ((oldptr[count - m_iWidth - 1]
                              + oldptr[count - m_iWidth + 1]
                              + oldptr[count + m_iWidth - 1]
                              + oldptr[count + m_iWidth + 1]))
                          + ( (
                              oldptr[count - (m_iWidth*2)]
                              + oldptr[count + (m_iWidth*2)]
                              + oldptr[count - 2]
                              + oldptr[count + 2]
                              ) >> 1 )
                          + ( (
                              oldptr[count - (m_iWidth*2) - 1]
                              + oldptr[count - (m_iWidth*2) + 1]
                              + oldptr[count + (m_iWidth*2) - 1]
                              + oldptr[count + (m_iWidth*2) + 1]
                              + oldptr[count - 2 - m_iWidth]
                              + oldptr[count - 2 + m_iWidth]
                              + oldptr[count + 2 - m_iWidth]
                              + oldptr[count + 2 + m_iWidth]
                              ) >> 2 )
                          )
                          >> 3)
                          - (newptr[count]);


            newptr[count] =  newh - (newh >> density);
            count++;
         }
         count += 4;
      }
   }

   void water_routine::HeightBlob(int x, int y, int radius, int height, int page)
   {
      int rquad;
      int cx, cy, cyq;
      int left, top, right, bottom;

      int *newptr;
      //int *oldptr;

      // set up the pointers
      if(page == 0)
      {
         newptr = &m_iHeightField1[0];
         //oldptr = &m_iHeightField2[0];
      }
      else
      {
         newptr = &m_iHeightField2[0];
         //oldptr = &m_iHeightField1[0];
      }

      rquad = radius * radius;

      // Make a randomly-placed blob...
      if(x<0) x = 1+radius+ rand()%(m_iWidth-2*radius-1);
      if(y<0) y = 1+radius+ rand()%(m_iHeight-2*radius-1);

      left=-radius; right = radius;
      top=-radius; bottom = radius;

      // Perform edge clipping...
      if(x - radius < 1) left -= (x-radius-1);
      if(y - radius < 1) top  -= (y-radius-1);
      if(x + radius > m_iWidth-1) right -= (x+radius-m_iWidth+1);
      if(y + radius > m_iHeight-1) bottom-= (y+radius-m_iHeight+1);


      for(cy = top; cy < bottom; cy++)
      {
         cyq = cy*cy;
         for(cx = left; cx < right; cx++)
         {
            if(cx*cx + cyq < rquad)
               newptr[m_iWidth*(cy+y) + (cx+x)] += height;
         }
      }

   }

   void water_routine::HeightBox (int x, int y, int radius, int height, int page)
   {
      int cx, cy;
      int left, top, right, bottom;
      int *newptr;
      //int *oldptr;

      // set up the pointers
      if(page == 0)
      {
         newptr = &m_iHeightField1[0];
       //  oldptr = &m_iHeightField2[0];
      }
      else
      {
         newptr = &m_iHeightField2[0];
         //oldptr = &m_iHeightField1[0];
      }

      if(x<0) x = 1+radius+ rand()%(m_iWidth-2*radius-1);
      if(y<0) y = 1+radius+ rand()%(m_iHeight-2*radius-1);

      left=-radius; right = radius;
      top=-radius; bottom = radius;

      // Perform edge clipping...
      if(x - radius < 1) left -= (x-radius-1);
      if(y - radius < 1) top  -= (y-radius-1);
      if(x + radius > m_iWidth-1) right -= (x+radius-m_iWidth+1);
      if(y + radius > m_iHeight-1) bottom-= (y+radius-m_iHeight+1);

      for(cy = top; cy < bottom; cy++)
      {
         for(cx = left; cx < right; cx++)
         {
            newptr[m_iWidth*(cy+y) + (cx+x)] = height;
         }
      }

   }


   void water_routine::WarpBlob(int x, int y, int radius, int height, int page)
   {
      int cx, cy;
      int left,top,right,bottom;
      int square;
      int radsquare = radius * radius;
      int *newptr;
      //int *oldptr;

      // set up the pointers
      if(page == 0)
      {
         newptr = &m_iHeightField1[0];
         //oldptr = &m_iHeightField2[0];
      }
      else
      {
         newptr = &m_iHeightField2[0];
         //oldptr = &m_iHeightField1[0];
      }
      //  radsquare = (radius*radius) << 8;
      radsquare = (radius*radius);

      height /= 64;

      left=-radius; right = radius;
      top=-radius; bottom = radius;

      // Perform edge clipping...
      if(x - radius < 1) left -= (x-radius-1);
      if(y - radius < 1) top  -= (y-radius-1);
      if(x + radius > m_iWidth-1) right -= (x+radius-m_iWidth+1);
      if(y + radius > m_iHeight-1) bottom-= (y+radius-m_iHeight+1);

      for(cy = top; cy < bottom; cy++)
      {
         for(cx = left; cx < right; cx++)
         {
            square = cy*cy + cx*cx;
            //      square <<= 8;
            if(square < radsquare)
            {
               //        height[page][WATERWID*(cy+y) + cx+x]
               //          += (sqrt(radsquare)-sqrt(square))*height;
               newptr[m_iWidth*(cy+y) + cx+x]
               += int((radius-sqrt((float)square))*(float)(height));
            }
         }
      }
   }

   void water_routine::SineBlob(int x, int y, int radius, int height, int page)
   {
      int cx, cy;
      int left,top,right,bottom;
      int square, dist;
      int radsquare = radius * radius;
      float length = float((1024.0/(float)radius)*(1024.0/(float)radius));
      int *newptr;
      //int *oldptr;

      // set up the pointers
      if(page == 0)
      {
         newptr = &m_iHeightField1[0];
         //oldptr = &m_iHeightField2[0];
      }
      else
      {
         newptr = &m_iHeightField2[0];
         //oldptr = &m_iHeightField1[0];
      }

      if(x<0) x = 1+radius+ rand()%(m_iWidth-2*radius-1);
      if(y<0) y = 1+radius+ rand()%(m_iHeight-2*radius-1);


      //  radsquare = (radius*radius) << 8;
      radsquare = (radius*radius);

      //  height /= 8;

      left=-radius; right = radius;
      top=-radius; bottom = radius;


      // Perform edge clipping...
      if(x - radius < 1) left -= (x-radius-1);
      if(y - radius < 1) top  -= (y-radius-1);
      if(x + radius > m_iWidth-1) right -= (x+radius-m_iWidth+1);
      if(y + radius > m_iHeight-1) bottom-= (y+radius-m_iHeight+1);

      for(cy = top; cy < bottom; cy++)
      {
         for(cx = left; cx < right; cx++)
         {
            square = cy*cy + cx*cx;
            if(square < radsquare)
            {
               dist = int(sqrt(square*length));
               newptr[m_iWidth*(cy+y) + cx+x]
               += (int)((cos((float) dist)+0xffff)*(height)) >> 19;
            }
         }
      }
   }

   void water_routine::DrawWaterNoLight(int page, ::image32_t * pSrcImage, ::image32_t * pTargetImage)
   {
      
      __UNREFERENCED_PARAMETER(page);
      //  int ox, oy;
      int Δx, Δy;
      int x, y;
      unsigned int ca;

      int offset=m_iWidth + 1;

      int *ptr = &m_iHeightField1[0];

      for (y = (m_iHeight-1)*m_iWidth; offset < y; offset += 2)
      {
         for (x = offset+m_iWidth-2; offset < x; offset++)
         {
            Δx = ptr[offset] - ptr[offset+1];
            Δy = ptr[offset] - ptr[offset+m_iWidth];

            //Shading = Δx;?
            // Water draw method?
            //      ca = BkGdImage[offset + WATERWID*(Δy>>3) + (Δx>>3)];
            ca = pSrcImage[offset + m_iWidth*(Δy>>3) + (Δx>>3)].m_u32;

            // If anyone knows a better/faster way to do this, please tell me...
            //      temp[offset] = (ca < 0) ? 0 : (ca > 255) ? 255 : ca;
            pTargetImage[offset].m_u32 = ca;

            offset++;
            Δx = ptr[offset] - ptr[offset+1];
            Δy = ptr[offset] - ptr[offset+m_iWidth];
            //    ca = BkGdImage[offset + m_iWidth*(Δy>>3) + (Δx>>3)];
            ca = pSrcImage[offset + m_iWidth*(Δy>>3) + (Δx>>3)].m_u32;
            pTargetImage[offset].m_u32 = ca;
            //      temp[offset] = (ca < 0) ? 0 : (ca > 255) ? 255 : ca;

         }
      }
   }

   void water_routine::DrawWaterWithLight(int page, int LightModifier,::image32_t * pSrcImage, ::image32_t * pTargetImage)
   {
      
      __UNREFERENCED_PARAMETER(page);
      __UNREFERENCED_PARAMETER(LightModifier);
      //  int ox, oy;
      int Δx, Δy;
      int x, y;
      image32_t ca;

      int offset=m_iWidth + 1;
      long lIndex;
      long lBreak = m_iWidth*m_iHeight;

      int *ptr = &m_iHeightField1[0];


      for (y = (m_iHeight-2)*m_iWidth; offset < y; )
      {
         for (x = offset+m_iWidth-2; offset < x; offset++)
         {
            Δx = ptr[offset] - ptr[offset+1];
            Δy = ptr[offset] - ptr[offset+m_iWidth];

            lIndex = offset + m_iWidth*(Δy>>3) + (Δx>>3);
            if(lIndex < lBreak && lIndex > 0)
            {
               ca = pSrcImage[lIndex];// - (Δx>>LightModifier);
               // Now we shift it by the Δx component...
               //
               ca = GetShiftedColor(ca, Δx);

               pTargetImage[offset] = ca;
            }

            offset++;
            Δx = ptr[offset] - ptr[offset+1];
            Δy = ptr[offset] - ptr[offset+m_iWidth];

            lIndex = offset + m_iWidth*(Δy>>3) + (Δx>>3);
            if(lIndex < lBreak && lIndex > 0)
            {
               ca = pSrcImage[lIndex];// - (Δx>>LightModifier);
               ca = GetShiftedColor(ca, Δx);
               //      temp[offset] = (ca < 0) ? 0 : (ca > 255) ? 255 : ca;
               pTargetImage[offset] = ca;
            }

         }
      }

   }


   inline ::image32_t water_routine::GetShiftedColor(::image32_t color,int shift)
   {
      
      long R;
      long G;
      long B;
      unsigned char ir;
      unsigned char ig;
      unsigned char ib;

      R = color.u8_red(color_indexes()) - shift;
      G = color.u8_green(color_indexes()) - shift;
      B = color.u8_blue(color_indexes()) - shift;

      ir = (unsigned char) ((R < 0) ? 0 : (R > 255) ? 255 : R);
      ig = (unsigned char) ((G < 0) ? 0 : (G > 255) ? 255 : G);
      ib = (unsigned char) ((B < 0) ? 0 : (B > 255) ? 255 : B);

      return { rgba(ir, ig, ib, 255), m_colorindexes };

   }

} // namespace draw2d
