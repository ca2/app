// Super Fast Blur v1.1
// by Mario Klingemann <http://incubator.quasimondo.com>
//
// Tip: Multiple invovations of this filter with a small
// radius will approximate a gaussian blur quite well.
//
#include "framework.h"




inline void kernelPosition(int boxBlur,unsigned& std,int& dLeft,int& dRight)
{

   switch(boxBlur)
   {
   case 0:

      if(!(std % 2))
      {

         dLeft = std / 2 - 1;

         dRight = std - dLeft;

      }
      else
      {

         dLeft = std / 2;

         dRight = std - dLeft;

      }

      break;

   case 1:

      if(!(std % 2))
      {

         dLeft++;

         dRight--;

      }

      break;

   case 2:

      if(!(std % 2))
      {

         dRight++;

         std++;

      }

      break;

   }

}



#if defined(__arm__) && !defined(ANDROID) && !defined(RASPBIAN)

#include <arm_neon.h>

//namespace WebCore {


inline float32x4_t loadRGBA8AsFloat(u32* source)
{

   uint32x2_t temporary1 = {0, 0};

   temporary1 = vset_lane_u32(*source,temporary1,0);

   uint16x4_t temporary2 = vget_low_u16(vmovl_u8(vreinterpret_u8_u32(temporary1)));

   return vcvtq_f32_u32(vmovl_u16(temporary2));

}

inline void storeFloatAsRGBA8(float32x4_t data,u32* destination)
{

   uint16x4_t temporary1 = vmovn_u32(vcvtq_u32_f32(data));

   uint8x8_t temporary2 = vmovn_u16(vcombine_u16(temporary1,temporary1));

   *destination = vget_lane_u32(vreinterpret_u32_u8(temporary2),0);

}

//} // namespace WebCore

#endif // HAVE(ARM_NEON_INTRINSICS)

//#endif // NEONHelpers_h
namespace draw2d
{

   fastblur::fastblur()
   {

      m_iRadius = 0;
      m_size.cx = 0;
      m_size.cy = 0;

#if VECTOR3_SSE

      vxmin = nullptr;
      vymin = nullptr;

      m_stack = nullptr;
      tsurface = nullptr;
      timage = nullptr;

#endif // VECTOR3_SSE

   }



   fastblur::~fastblur()
   {

#if VECTOR3_SSE

      if (m_stack != nullptr)
      {
         delete[] m_stack;
         m_stack = nullptr;
      }
      if (tsurface != nullptr)
      {
         delete[] tsurface;
         tsurface = nullptr;
      }
      if (timage != nullptr)
      {
         delete[] timage;
         timage = nullptr;
      }

      if (vxmin != nullptr)
      {
         delete[] vxmin;
         vxmin = nullptr;
      }
      if (vymin != nullptr)
      {
         delete[] vymin;
         vymin = nullptr;
      }

#endif // VECTOR3_SSE

   }


   bool fastblur::initialize(i32 cx,i32 cy,i32 radius)
   {

      if (cx <= 0 || cy <= 0 || radius <= 0)
      {

         return false;

      }

      if (m_size == size(cx, cy) && m_iRadius == radius)
      {

         return true;

      }


#if VECTOR3_SSE

      int div2 = (radius * 2) + 1;

      if(m_stack != nullptr)
      {
         delete[] m_stack;
         m_stack = nullptr;
      }
      if(tsurface != nullptr)
      {
         delete[] tsurface;
         tsurface = nullptr;
      }
      if(timage != nullptr)
      {
         delete[] timage;
         timage = nullptr;
      }

      int wj = cx;

      //if(wj % 16 > 0)
      //{
      //   wj = ((wj / 16) * 16) + 16;
      //}

      const int wh = (wj)*(cy);
#undef new
      timage = new vector4[wh];
      // temporary output space for first pass.
      tsurface = new vector4[wh];

      m_stack = new vector4[div2];

#define new ACME_NEW


      if(vxmin != nullptr)
      {
         delete[] vxmin;
         vxmin = nullptr;
      }
      if(vymin != nullptr)
      {
         delete[] vymin;
         vymin = nullptr;
      }

      // lookup table for clamping pixel offsets
      // as the kernel passes the right (or lower) edge
      // of the input data
      vxmin = new int[cx + 100 + div2];
      vymin = new int[cy + 100 + div2];

      const int r1 = radius + 1;
      
      int wm = cx - 1;
      
      int c = cx + div2;
      
      for(index x = 0; x < c; x++)
      {
         
         vxmin[x] = (int) MIN(x + r1,wm);

      }

      int hm = cy - 1;
      c = cy + div2;
      int s = cx;
      //if(s % 16 > 0)
      //{
      //   s = ((s / 16) * 16) + 16;
      //}
      for(index y = 0; y < c; y++)
      {
         vymin[y] = (int)(MIN(y + r1,hm)*s);
      }

#endif // VECTOR3_SSE


//      m_p->m_iHeight = cy;

      //      i32 h         = cy;
      //    i32 scan      = m_p->scan;
      i32 div       = radius + radius + 1;
      m_iRadius         = radius;
      m_uchaDiv.allocate(256 * div);
      u8 * dv         = m_uchaDiv.get_data();

      m_size.cx         = cx;
      m_size.cy         = cy;

      for(i32 i = 0; i < m_uchaDiv.get_count(); i++)
      {

         dv[i]= MIN(255,i / div);

      }

      m_uia.set_size(m_size.area());



      return true;

   }


   bool fastblur::initialize(size sz,i32 iRadius)
   {

      return initialize(sz.cx,sz.cy,iRadius);

   }


   bool fastblur::blur(::image * pimage, i32 iRadius, const ::rect & rect)
   {

      pixmap_lock lock(pimage, rect);

      return blur(pimage, iRadius);

   }


   bool fastblur::blur(::image * pimage, int iRadius)
   {

      int cx = pimage->width();

      int cy = pimage->height();

      if (iRadius <= 0)
      {

         iRadius = m_iRadius;

      }

      if (cx <= 0 || cy <= 0 || iRadius <= 0)
      {

         return false;

      }

      if (!initialize(cx, cy, iRadius))
      {

         return false;

      }

      pimage->map();

      bool b = false;

      int bottomup;

#ifdef __APPLE__
      bottomup = 1;
#else
      bottomup = 0;
#endif


#if VECTOR3_SSE

#ifdef DO_BOX_BLUR

      u32 * pdata = (u32 *) m_p->get_data();

      u8 * point;
      vector4 * t = timage;

      int w = m_size.cx;
      int h = m_size.cy;

      int s = m_p->m_iScan / 4;

      {
auto tickA0 = ::tick::now();

         for(index y = 0; y < h; y++)
         {
            for(index x = 0; x < w; x++)
            {
               point = (u8 *)&pdata[y * s + x];
               t[y * w + x] = vector4(point[0],point[1],point[2],point[3]);
            }
         }
auto tickA1 = ::tick::now();
         DWORD dwA2 = dwA1 - dwA0;
         string str;

         str.Format("%d",dwA2);

      }



      {
auto tick1 = ::tick::now();

         try
         {

            b = do_boxblur(
                timage,
                w,
                h,
                m_iRadius,
                (u32 *)m_ucha.get_data(),
                m_uchaDiv.get_data(),
                w * 4,
                w,h,bottomup);

         }
         catch(...)
         {

         }
auto tick2 = ::tick::now();
         DWORD dw3 = dw2 - dw1;

         string str1;
         str1.Format("| Parameters: w=%d h=%d rect=%d  \n",w,h,m_iRadius);
         string str2;
         str2.Format("| time for calculating box blur : %d\b",dw3);

         output_debug_string("/-----------------------------------------\n");
         output_debug_string("| \n");
         output_debug_string(str1);
         output_debug_string(str2);
         output_debug_string("| \n");

         ::aura::application * papp = m_p->get_context_application();
         TRACE("/--------------------------------");
         TRACE("| fastblur::blur");
         TRACE("| ");
         TRACE("| do_fastblur = %d ms",dw3);
      }

      {
auto tickC0 = ::tick::now();

         for(index y = 0; y < h; y++)
         {
            for(index x = 0; x < w; x++)
            {
               point = (u8 *)&pdata[y * s + x];
               t = &timage[y * w + x];
               point[0] = (byte)t->w;
               point[1] = (byte)t->x;
               point[2] = (byte)t->y;
               point[3] = (byte)t->z;
            }
         }
auto tickC1 = ::tick::now();
         DWORD dwC2 = dwC1 - dwC0;
         string str;

         str.Format("%d",dwC2);
      }
#else
      u32 * pdata = (u32 *)pimage->colorref();

      u8 * point;
      vector4 * t = timage;

      int w = m_size.cx;
      int h = m_size.cy;
      int wj = w; // w job
      int hj = h; // h job

      //if(wj % 16 > 0)
      //{
      //   wj = ((wj / 16) * 16) + 16;
      //}

      int s = pimage->scan_size() / 4;

      {
auto tickA0 = ::tick::now();

         for(index y = 0; y < hj; y++)
         {
            for(index x = 0; x < wj; x++)
            {
               point = (u8 *)&pdata[y * s + x];
               t[y * wj + x] = vector4(point[0],point[1],point[2],point[3]);
            }
         }
         
         auto tickA1 = ::tick::now();

         auto tickA2 = tickA1 - tickA0;

         string str;

         str.Format(__prtick,tickA2.m_i);

      }


      {

         auto tick1 = ::tick::now();

         try
         {

            b = do_stackblur(
                timage,
                w,
                h,
                m_iRadius,
                (u32 *)m_uia.get_data(),
                m_uchaDiv.get_data(),
                wj,
                w,h,bottomup);

         }
         catch(...)
         {

         }
         
         auto tick2 = ::tick::now();

         auto tick3 = tick2 - tick1;

         if(0)
         {

            string str1;
            str1.Format("| Parameters: w=%d h=%d rect=%d  \n",wj,hj,m_iRadius);
            string str2;
            str2.Format("| time for calculating stack blur : " __prtick "\b",tick3.m_i);

            output_debug_string("/-----------------------------------------\n");
            output_debug_string("| \n");
            output_debug_string(str1);
            output_debug_string(str2);
            output_debug_string("| \n");

            //::aura::application * papp = pimage->get_context_application();
            TRACE("/--------------------------------");
            TRACE("| fastblur::blur");
            TRACE("| ");
            TRACE("| do_fastblur = " __prtick, tick3);

         }

      }

      {
auto tickC0 = ::tick::now();

         for(index y = 0; y < h; y++)
         {
            for(index x = 0; x < w; x++)
            {
               point = (u8 *)&pdata[y * s + x];
               t = &timage[y * wj + x];
               point[0] = (byte)t->w;
               point[1] = (byte)t->x;
               point[2] = (byte)t->y;
               point[3] = (byte)t->z;
            }
         }
         
         auto tickC1 = ::tick::now();
         
         auto tickC2 = tickC1 - tickC0;

         string str;

         str.Format(__prtick,tickC2.m_i);
      }

#endif

#else


      //DWORD dw1 = ::get_tick();

#ifdef __arm__

#else

//      ::count cCount = MAX(2,m_iRadius / 8);

      ::count cCount = 2;

      for(index i = 0; i < cCount; i++)
#endif
      {
         try
         {

            b = do_fastblur(
                (u32*)pimage->colorref(),
                m_size.cx,
                m_size.cy,
                m_iRadius,
                m_uia.get_data(),
                m_uchaDiv.get_data(),
                pimage->scan_size(),
                cx,cy,bottomup);

         }
         catch(...)
         {

         }

      }

      /*
auto tick2 = ::tick::now();
      DWORD dw3 = dw2 - dw1;
      string str1;
      str1.Format("| Parameters: w=%d h=%d rect=%d  \n",m_size.cx,m_size.cy,m_iRadius);
      string str2;
      str2.Format("| time for calculating fast blur : %d\b",dw3);

      output_debug_string("/-----------------------------------------\n");
      output_debug_string("| \n");
      output_debug_string(str1);
      output_debug_string(str2);
      output_debug_string("| \n");

      ::aura::application * papp = m_p->get_context_application();
      TRACE("/--------------------------------");
      TRACE("| fastblur::blur");
      TRACE("| ");
      TRACE("| do_fastblur = %d ms",dw3);
      */
#endif

#if defined(ANDROID)

      pimage->mult_alpha();

#endif

      return b;

   }

#if defined(__arm__) && !defined(ANDROID) && !defined(RASPBIAN)


   inline void boxBlurNEON(u32* sourcePixel,u32* destinationPixel,
                           unsigned dx,int dxLeft,int dxRight,int stride,int strideLine,int effectWidth,int effectHeight)
   {

      float32x4_t deltaX = vdupq_n_f32(1.0 / dx);

      int pixelLine = strideLine / 4;

      int pixelStride = stride / 4;

      int strideRight = dxRight * pixelStride;

      int strideLeft = dxLeft * pixelStride;

      int dxW = effectWidth - dxRight;

      int x;

      int pixelOffset;

      if(dxLeft > dxW)
      {

         for(int y = 0; y < effectHeight; ++y)
         {

            int line = y * pixelLine;

            float32x4_t sum = vdupq_n_f32(0);

            // Fill the kernel
            int maxKernelSize = MIN(dxRight,effectWidth);

            for(int i = 0; i < maxKernelSize; ++i)
            {

               float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + line + i * pixelStride);

               sum = vaddq_f32(sum,sourcePixelAsFloat);

            }

            // Blurring

            for(x = 0; x < effectWidth; x++)
            {

               pixelOffset = line + x * pixelStride;

               float32x4_t result = vmulq_f32(sum,deltaX);

               storeFloatAsRGBA8(result,destinationPixel + pixelOffset);

               if(x >= dxLeft)
               {

                  float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + pixelOffset - strideLeft);

                  sum = vsubq_f32(sum,sourcePixelAsFloat);

               }

               if(x <= dxW)
               {

                  float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + pixelOffset + strideRight);

                  sum = vaddq_f32(sum,sourcePixelAsFloat);

               }

            }

         }

      }
      else
      {

         for(int y = 0; y < effectHeight; ++y)
         {

            int line = y * pixelLine;

            float32x4_t sum = vdupq_n_f32(0);

            // Fill the kernel
            int maxKernelSize = MIN(dxRight,effectWidth);

            for(int i = 0; i < maxKernelSize; ++i)
            {

               float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + line + i * pixelStride);

               sum = vaddq_f32(sum,sourcePixelAsFloat);

            }

            // Blurring
            x = 0;

            pixelOffset = line;

            for(; x < dxLeft; x++)
            {

               float32x4_t result = vmulq_f32(sum,deltaX);

               storeFloatAsRGBA8(result,destinationPixel + pixelOffset);

               {

                  float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + pixelOffset + strideRight);

                  sum = vaddq_f32(sum,sourcePixelAsFloat);

               }

               pixelOffset += pixelStride;

            }

            for(; x <= dxW; x++)
            {

               float32x4_t result = vmulq_f32(sum,deltaX);

               storeFloatAsRGBA8(result,destinationPixel + pixelOffset);

               {

                  float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + pixelOffset - strideLeft);

                  sum = vsubq_f32(sum,sourcePixelAsFloat);

               }

               {

                  float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + pixelOffset + strideRight);

                  sum = vaddq_f32(sum,sourcePixelAsFloat);

               }

               pixelOffset += pixelStride;

            }


            for(; x < effectWidth; x++)
            {

               float32x4_t result = vmulq_f32(sum,deltaX);

               storeFloatAsRGBA8(result,destinationPixel + pixelOffset);

               {

                  float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + pixelOffset - strideLeft);

                  sum = vsubq_f32(sum,sourcePixelAsFloat);

               }

               pixelOffset += pixelStride;

            }

         }

      }

   }


   bool fastblur::do_fastblur(u32 * pdata,i32 w,i32 h,i32 radius,u32 * prgba,u8 * dv,i32 stride,int cx,int cy,int bottomup)
   {

      //int stride = 4 * cx;
      int dxLeft = 0;
      int dxRight = 0;
      int dyLeft = 0;
      int dyRight = 0;
      u32* src = pdata;
      u32* dst = m_pimage->m_pcolorref;
      unsigned int kernelSizeX = radius * 3 / 2 + 1;
      unsigned int kernelSizeY = radius * 3 / 2 + 1;

      for(int i = 0; i < 3; ++i)
      {

         if(kernelSizeX)
         {

            kernelPosition(i,kernelSizeX,dxLeft,dxRight);

            boxBlurNEON(src,dst,kernelSizeX,dxLeft,dxRight,4,stride,cx,cy);

            __swap(src,dst);

         }

         if(kernelSizeY)
         {

            kernelPosition(i,kernelSizeY,dyLeft,dyRight);

            boxBlurNEON(src,dst,kernelSizeY,dyLeft,dyRight,stride,4,cy,cx);

            __swap(src,dst);

         }

      }

      // The final result should be stored in srcPixelArray.
      if(dst != pdata)
      {

         ::memcpy_dup(pdata,dst,m_p->m_iScan * m_p.height());

      }

   }

#else

#if VECTOR3_SSE

   inline void boxBlurSSE(vector4* sourcePixel,vector4* destinationPixel,
                          unsigned dx,int dxLeft,int dxRight,int stride,int strideLine,int effectWidth,int effectHeight)
   {

      vector4 deltaX = vector4(1.0f / dx,1.0f / dx,1.0f / dx,1.0f / dx);

      int pixelLine = strideLine / 4;

      int pixelStride = stride / 4;

      int strideRight = dxRight * pixelStride;

      int strideLeft = dxLeft * pixelStride;

      int dxW = effectWidth - dxRight;

      int x;

      int pixelOffset;

      if(dxLeft > dxW)
      {

         for(int y = 0; y < effectHeight; ++y)
         {

            int line = y * pixelLine;

            vector4 sum = vector4();

            // Fill the kernel
            int maxKernelSize = MIN(dxRight,effectWidth);

            for(int i = 0; i < maxKernelSize; ++i)
            {

               sum += sourcePixel[line + i*pixelStride];

            }

            // Blurring

            for(x = 0; x < effectWidth; x++)
            {

               pixelOffset = line + x * pixelStride;

               destinationPixel[pixelOffset] = sum * deltaX;

               if(x >= dxLeft)
               {

                  sum -= sourcePixel[pixelOffset - strideLeft];

               }

               if(x <= dxW)
               {

                  sum += sourcePixel[pixelOffset + strideRight];

               }

            }

         }

      }
      else
      {

         for(int y = 0; y < effectHeight; ++y)
         {

            int line = y * pixelLine;

            vector4 sum = vector4();

            // Fill the kernel
            int maxKernelSize = MIN(dxRight,effectWidth);

            for(int i = 0; i < maxKernelSize; ++i)
            {

               sum += sourcePixel[line + i*pixelStride];

            }

            // Blurring
            x = 0;

            pixelOffset = line;

            for(; x < dxLeft; x++)
            {

               destinationPixel[pixelOffset] = sum * deltaX;

               {

                  sum += sourcePixel[pixelOffset + strideRight];

               }

               pixelOffset += pixelStride;

            }

            for(; x <= dxW; x++)
            {

               destinationPixel[pixelOffset] = sum * deltaX;

               {

                  sum -= sourcePixel[pixelOffset - strideLeft];

               }

               {

                  sum += sourcePixel[pixelOffset + strideRight];

               }

               pixelOffset += pixelStride;

            }


            for(; x < effectWidth; x++)
            {

               destinationPixel[pixelOffset] = sum * deltaX;

               {

                  sum -= sourcePixel[pixelOffset - strideLeft];

               }

               pixelOffset += pixelStride;

            }

         }

      }

   }

   // https://gist.github.com/benjamin9999/3809142

   /*
   * "stackblur"
   * originally, Mario Klingemann, mario@quasimondo.com
   * this implementation, Benjamin Yates (benjamin@rqdq.com)
   * http://incubator.quasimondo.com/processing/stackblur.pde
   *
   * this blur routine seems to be quite popular.
   *
   * unfortunately, mario didn't comment anything.
   * but, it's easy to see it's just a flavor of a two-pass
   * sliding box kernel.
   *
   * this version is vectorized for float32 rect/g/b/a using sse
   *
   * vector4() is just a class wrapping _mm_zzz_ps() family of SSE intrinsics
   * ( if you need one, start here:
   *  - http://fastcpp.blogspot.com/2011/12/simple-vector3-class-with-sse-support.html )
   *
   * radius is in (whole) pixels
   *
   */

   void fastblur::stackblur(vector4* pix,const int w,const int h,const int radius, int wj)
   {

      if(radius < 1) return;	// nothing to do

      // some values for convenience
      //const int w = pimage->width;
      //const int h = pimage->height;
      const int wm = w - 1;
      const int hm = h - 1;
      const int r1 = radius + 1;

      // number of divisions in the kernel
      // D(-rect), D(-rect+1), ... D(0), ... D(rect-1), D(rect)
      const int div = (radius * 2) + 1;

      // temporary output space for first pass.
      //vector4* tsurface = new vector4[wh];

      // lookup table for clamping pixel offsets
      // as the kernel passes the right (or lower) edge
      // of the input data
      //int* const vmin = new int[max(w,h)];

      // calculate divisor for pulling an output from the kernel
      //   the kernel is pyramid shaped.
      //   to understand this divisor, imagine a cross-section
      //   of the center of the pyramid.
      //   (or ask mario to document it better)
      //
      // I store the reciprocal in the vector to
      // mul_ps later instead of div_ps
      int divsumi = (div + 1) >> 1;
      divsumi *= divsumi;
      const vector4 divsum(1.0f / (float)divsumi);

      // kernel pixel data "stack"
      // which works more like a ring-buffer,
      // where the pointer is advanced each iteration, modulo #divisions
      vector4* stack = m_stack;
      int stackpointer;
      int stackstart;



      // input/output offsets.
      // they are discrete because the source can be non-square
      int yw = 0;	// current read offset in source
      int yi = 0; // current write offset in destination


      // blur horizontally, output to temporary buffer
      for(int y=0; y<h; y++)
      {

         vector4 insum(0.f);
         vector4 outsum(0.f);
         vector4 sum(0.f);

         // preload the kernel(stack)
         // pixels before the left edge of the image are
         // samples of [0] (max()).  min() handles
         // images which are smaller than the kernel.
         for(int i=-radius; i <= radius; i++)
         {

            // calcualte address of source pixel
            const vector4& point = pix[yi + MIN(wm,MAX(i,0))];

            // put pixel in the stack
            vector4& sir = stack[i + radius];
            sir = point;

            // rbs is a weight from (1)...(radius+1)...(1)
            const int rbs = r1 - abs(i);

            // add pixel to accumulators
            sum += sir * (float) rbs;
            if(i > 0)
            {
               insum  += sir;
            }
            else
            {
               outsum += sir;
            }
         }


         // now that the kernel is preloaded
         // stackpointer is the index of the center of the kernel
         stackpointer = radius;


         // now start outputing pixels
         for(int x=0; x<w; x++)
         {

            // output a pixel
            tsurface[yi] = sum * divsum;


            // calculate address of the next pixel
            // to add to the kernel
            //
            // on first pass, make a lut to handle access
            // past the right edge of the width pimage->
            // min() will cause the last pixel to repeat.
            //if(y == 0) vmin[x] = min(x + radius + 1,wm);
            //vector4& point = pix[yw + vmin[x]];
            vector4& point = pix[yw + vxmin[x]];


            // remove "past" pixels from the sum
            sum -= outsum;


            // remove "left" side of stack from outsum
            stackstart = stackpointer - radius + div;
            vector4& sir = stack[stackstart % div];
            outsum -= sir;

            // now this (same) stack entry is the "right" side
            // add new pixel to the stack, and update accumulators
            sir = point;
            insum += sir;
            sum += insum;


            // slide kernel one pixel ahead (right),
            // update accumulators again
            stackpointer = (stackpointer + 1) % div;
            const vector4& sirnext = stack[stackpointer];
            outsum += sirnext;
            insum -= sirnext;

            yi++;	// advance output offset to next pixel
         }
         yw += wj;	// advance input offset to next line
      }//y loop



      // now blur vertically from the temporary
      // buffer, using the original image buffer
      // as the output
      for(int x=0; x<w; x++)
      {

         vector4 insum(0);
         vector4 outsum(0);
         vector4 sum(0);

         //preload the stack
         int yp = -radius * wj;
         for(int i = -radius; i <= radius; i++)
         {

            vector4& sir = stack[i + radius];

            yi = MAX(0,yp) + x;
            const vector4& point = tsurface[yi];

            sir = point;

            const int rbs = r1 - abs(i);
            sum += sir * (float) rbs;
            if(i > 0)
            {
               insum  += sir;
            }
            else
            {
               outsum += sir;
            }

            // only advance to the next row if there
            // are still more rows of image left.
            // otherwise, we keep sampling the same row
            // as if the bottom line was duplicated
            if(i < hm) yp += wj;

         }//preload

         stackpointer = radius;

         // this loop is the same as the y-loop,
         // except the src/dest offsets are calcuated differently
         yi = x;	// set starting output offset by column
         for(int y=0; y<h; y++)
         {

            pix[yi] = sum * divsum;

            stackstart = stackpointer - radius + div;
            vector4& sir = stack[stackstart % div];
            sum -= outsum;
            outsum -= sir;

            //if(x == 0) vmin[y] = min(y + r1,hm)*w;
            //sir = tsurface[x + vmin[y]];
            sir = tsurface[x + vymin[y]];

            insum += sir;
            sum += insum;

            stackpointer = (stackpointer + 1) % div;
            const vector4& sirnext = stack[stackpointer];
            outsum += sirnext;
            insum -= sirnext;

            yi += wj; // advance output offset to next line
         }
      }//x loop
   }


   bool fastblur::do_boxblur(vector4 * pimage,i32 w,i32 h,i32 radius,u32 * prgba,u8 * dv,i32 stride,int cx,int cy,int bottomup)
   {

      int dxLeft = 0;
      int dxRight = 0;
      int dyLeft = 0;
      int dyRight = 0;
      vector4* src = pimage;
      vector4* dst = tsurface;
      unsigned int kernelSizeX = radius * 3 / 2 + 1;
      unsigned int kernelSizeY = radius * 3 / 2 + 1;

      for(int i = 0; i < 3; ++i)
      {

         if(kernelSizeX)
         {

            kernelPosition(i,kernelSizeX,dxLeft,dxRight);

            boxBlurSSE(src,dst,kernelSizeX,dxLeft,dxRight,4,stride,w,h);

            __swap(src,dst);

         }

         if(kernelSizeY)
         {

            kernelPosition(i,kernelSizeY,dyLeft,dyRight);

            boxBlurSSE(src,dst,kernelSizeY,dyLeft,dyRight,stride,4,h,w);

            __swap(src,dst);

         }

      }

      // The final result should be stored in srcPixelArray.
      if(dst != pimage)
      {

         ::memcpy_dup(pimage,dst,stride * h);

      }


      return true;

   }

   bool fastblur::do_stackblur(vector4 * pimage,i32 w,i32 h,i32 radius,u32 * prgba,u8 * dv,i32 stride,int cx,int cy,int bottomup)
   {

      stackblur(pimage,w,h,radius, stride);

      return true;

   }


#endif // VECTOR3_SSE



   bool fastblur::do_fastblur(u32 * pdata,i32 w,i32 h,i32 radius,u32 * prgba,u8 * dv,i32 stride,int cx,int cy,int bottomup)
   {

      if(radius <= 0)
      {

         return false;

      }

      i32 rsum,gsum,bsum,asum;
      i32 x;
      i32 y;
      i32 i;
      i32 yp;
      i32 yw;
      u8 * pu8_1;
      u8 * pu8_2;
      i32 wm = w - 1;
      //      i32 hm = h - 1;
      i32 wr = MIN(w,cx) - 1 - radius;
      i32 hr = MIN(h,cy) - 1 - radius;
      //   i32 div        = radius + radius + 1;
      u8 * point;

      yw = 0;

      h = MIN(h,cy);

      w = MIN(w,cx);

      if(bottomup)
      {

         pdata = (u32 *)(((u8 *)pdata) + (stride * (cy - h)));

         prgba = (u32 *)(((u8 *)prgba) + (stride * (cy - h)));

      }

      int dir;

      if(bottomup)
      {

         dir = -1;

      }
      else
      {

         dir = 1;

      }

      i32 * pix = (i32 *)pdata;
      u8 * pb = (u8 *)pdata;
      u8 * pwork = (u8 *)prgba;
      u8 * pwk = (u8 *)prgba;

      for(y = 0; y < h; y++)
      {

         pwork = &pwk[stride * y];

         asum = 0;
         rsum = 0;
         gsum = 0;
         bsum = 0;

         for(i = -radius; i <= radius; i++)
         {

            point = &pb[yw + (MIN(wm,MAX(i,0)) * 4)];
            rsum += point[0];
            gsum += point[1];
            bsum += point[2];
            asum += point[3];

         }

         pu8_1 = &pb[yw + (radius + 1) * 4];
         pu8_2 = &pb[yw];

         for(x = 0; x < radius; x++)
         {

            pwork[0] = dv[rsum];
            pwork[1] = dv[gsum];
            pwork[2] = dv[bsum];
            pwork[3] = dv[asum];

            rsum += pu8_1[0] - pu8_2[0];
            gsum += pu8_1[1] - pu8_2[1];
            bsum += pu8_1[2] - pu8_2[2];
            asum += pu8_1[3] - pu8_2[3];

            pwork += 4;
            pu8_1 += 4;

         }

         for(; x < wr; x++)
         {

            pwork[0] = dv[rsum];
            pwork[1] = dv[gsum];
            pwork[2] = dv[bsum];
            pwork[3] = dv[asum];


            rsum += pu8_1[0] - pu8_2[0];
            gsum += pu8_1[1] - pu8_2[1];
            bsum += pu8_1[2] - pu8_2[2];
            asum += pu8_1[3] - pu8_2[3];

            pu8_1 += 4;
            pu8_2 += 4;
            pwork += 4;

         }

         pu8_1 -= 4;

         for(; x < w; x++)
         {

            pwork[0] = dv[rsum];
            pwork[1] = dv[gsum];
            pwork[2] = dv[bsum];
            pwork[3] = dv[asum];


            rsum += pu8_1[0] - pu8_2[0];
            gsum += pu8_1[1] - pu8_2[1];
            bsum += pu8_1[2] - pu8_2[2];
            asum += pu8_1[3] - pu8_2[3];

            pu8_2 += 4;
            pwork += 4;

         }

         yw += stride;

      }

      for(x = 0; x < w; x++)
      {

         asum = 0;
         rsum = 0;
         gsum = 0;
         bsum = 0;

         yp = -radius * stride;

         for(i = -radius; i <= radius; i++)
         {
            point = &pwk[MAX(0,yp) + x * 4];
            rsum += point[0];
            gsum += point[1];
            bsum += point[2];
            asum += point[3];
            yp += stride;
         }

         u8 * r1 = &pwk[(x * 4) + (radius + 1) * stride];
         u8 * r2 = &pwk[(x * 4)];

         pu8_1 = (u8 *)&pix[x];

         for(y = 0; y < radius; y++)
         {

            pu8_1[0] = dv[rsum];
            pu8_1[1] = dv[gsum];
            pu8_1[2] = dv[bsum];
            pu8_1[3] = dv[asum];

            rsum += r1[0] - r2[0];
            gsum += r1[1] - r2[1];
            bsum += r1[2] - r2[2];
            asum += r1[3] - r2[3];

            pu8_1 += stride;
            r1 += stride;

         }

         for(; y < hr; y++)
         {

            pu8_1[0] = dv[rsum];
            pu8_1[1] = dv[gsum];
            pu8_1[2] = dv[bsum];
            pu8_1[3] = dv[asum];

            rsum += r1[0] - r2[0];
            gsum += r1[1] - r2[1];
            bsum += r1[2] - r2[2];
            asum += r1[3] - r2[3];

            pu8_1 += stride;
            r1 += stride;
            r2 += stride;

         }

         pu8_1 -= stride;
         r1 -= stride;

         for(; y < h; y++)
         {

            pu8_1[0] = dv[rsum];
            pu8_1[1] = dv[gsum];
            pu8_1[2] = dv[bsum];
            pu8_1[3] = dv[asum];

            rsum += r1[0] - r2[0];
            gsum += r1[1] - r2[1];
            bsum += r1[2] - r2[2];
            asum += r1[3] - r2[3];

            pu8_1 += stride;
            r2 += stride;

         }

      }

      return true;

   }

#endif // VECTOR3_SSE

   bool fastblur::do_fastblur(u32 * pix,i32 w,i32 h,i32 radius,u8 * rect,u8 * g,u8 * b,u8 * a,u8 * dv,i32 stride,i32 * vmin,i32 * vmax,int cx,int cy,int bottomup)
   {

      return false;

      /*

            if (radius <= 0)
            {

               return false;

            }

            i32 asum, rsum, gsum, bsum, x, y, i, yp, yi, yw;
            i32 s = stride / sizeof(COLORREF);
            i32 wm = w - 1;
            i32 hm = h - 1;
            i32 div = radius + radius + 1;
            i32 point;
            i32 pu8_1;
            i32 pu8_2;

            yw = yi = 0;

            for (x = 0; x < w; x++)
            {
               vmin[x] = MIN(x + radius + 1, wm);
               vmax[x] = MAX(x - radius, 0);
            }

            for (y = 0; y < h; y++)
            {
               asum = rsum = gsum = bsum = 0;
               yi = y * s;
               for (i = -radius; i <= radius; i++)
               {
                  point = pix[yi + MIN(wm, MAX(i, 0))];
                  asum += ((point & 0xff000000) >> 24);
                  rsum += ((point & 0xff0000) >> 16);
                  gsum += ((point & 0x00ff00) >> 8);
                  bsum += (point & 0x0000ff);
               }
               for (x = 0; x < w; x++)
               {
                  a[yi] = dv[asum];
                  rect[yi] = dv[rsum];
                  g[yi] = dv[gsum];
                  b[yi] = dv[bsum];

                  pu8_1 = pix[yw + vmin[x]];
                  pu8_2 = pix[yw + vmax[x]];

                  asum += ((pu8_1 >> 24) & 0xff) - ((pu8_2 >> 24) & 0xff);
                  rsum += ((pu8_1 & 0x00ff0000) - (pu8_2 & 0x00ff0000)) >> 16;
                  gsum += ((pu8_1 & 0x0000ff00) - (pu8_2 & 0x0000ff00)) >> 8;
                  bsum += ((pu8_1 & 0x000000ff) - (pu8_2 & 0x000000ff));
                  yi++;
               }
               yw += s;
            }
            for (y = 0; y < h; y++)
            {
               vmin[y] = MIN(y + radius + 1, hm) * s;
               vmax[y] = MAX(y - radius, 0) * s;
            }

            for (x = 0; x < w; x++)
            {
               asum = rsum = gsum = bsum = 0;
               yp = -radius*s;
               for (i = -radius; i <= radius; i++)
               {
                  yi = MAX(0, yp) + x;
                  rsum += rect[yi];
                  gsum += g[yi];
                  bsum += b[yi];
                  asum += a[yi];
                  yp += s;
               }
               yi = x;
               for (y = 0; y < h; y++)
               {
                  pix[yi] = (dv[asum] << 24) | (dv[rsum] << 16) | (dv[gsum] << 8) | dv[bsum];

                  pu8_1 = x + vmin[y];
                  pu8_2 = x + vmax[y];

                  rsum += rect[pu8_1] - rect[pu8_2];
                  gsum += g[pu8_1] - g[pu8_2];
                  bsum += b[pu8_1] - b[pu8_2];
                  asum += a[pu8_1] - a[pu8_2];

                  yi += s;

               }

            }

            return true;

      */

   }







} // namespace draw2d
