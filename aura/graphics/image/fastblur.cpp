// Super Fast Blur v1.1
// by Mario Klingemann <http://incubator.quasimondo.com>
//
// Tip: Multiple invovations of this filter with a small
// radius will approximate a gaussian blur quite well.
//
#include "framework.h"
#include "fastblur.h"
#include "image.h"
#include "acme/graphics/image/pixmap_lock.h"
////#include "acme/exception/exception.h"


namespace image
{


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



#if defined(__arm__) && !defined(__ANDROID__) && !defined(RASPBERRYPIOS)

#include <arm_neon.h>

//namespace WebCore {


inline float32x4_t loadRGBA8AsFloat(unsigned int* source)
{

   ::u32x2_t temporary1 = {0, 0};

   temporary1 = vset_lane_unsigned_int(*source,temporary1,0);

   ::u3216x4_t temporary2 = vget_low_unsigned_short(vmovl_unsigned_char(vreinterpret_byte_unsigned_int(temporary1)));

   return vcvtq_float_unsigned_int(vmovl_unsigned_short(temporary2));

}

inline void storeFloatAsRGBA8(float32x4_t data,unsigned int* destination)
{

   ::u3216x4_t temporary1 = vmovn_unsigned_int(vcvtq_u32_float(data));

   ::u328x8_t temporary2 = vmovn_unsigned_short(vcombine_unsigned_short(temporary1,temporary1));

   *destination = vget_lane_unsigned_int(vreinterpret_u32_unsigned_char(temporary2),0);

}

//} // namespace WebCore

#endif // HAVE(ARM_NEON_INTRINSICS)

//#endif // NEONHelpers_h

   fastblur::fastblur()
   {

      m_iRadius = 0;
      m_size.cx() = 0;
      m_size.cy() = 0;

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


   void fastblur::initialize(int cx,int cy,int radius)
   {

      if (cx <= 0 || cy <= 0 || radius <= 0)
      {

         throw ::exception(error_bad_argument);

      }

      if (m_size == ::int_size(cx, cy) && m_iRadius == radius)
      {

         return;

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

      timage = ___new vector4[wh];
      // temporary output space for first pass.
      tsurface = ___new vector4[wh];

      m_stack = ___new vector4[div2];




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
      vxmin = ___new int[cx + 100 + div2];
      vymin = ___new int[cy + 100 + div2];

      const int r1 = radius + 1;
      
      int wm = cx - 1;
      
      int c = cx + div2;
      
      for(::collection::index x = 0; x < c; x++)
      {
         
         vxmin[x] = (int) minimum(x + r1,wm);

      }

      int hm = cy - 1;
      c = cy + div2;
      int s = cx;
      //if(s % 16 > 0)
      //{
      //   s = ((s / 16) * 16) + 16;
      //}
      for(::collection::index y = 0; y < c; y++)
      {
         vymin[y] = (int)(minimum(y + r1,hm)*s);
      }

#endif // VECTOR3_SSE


//      m_p->m_iHeight = cy;

      //      int h         = cy;
      //    int scan      = m_p->scan;
      int div       = radius + radius + 1;
      m_iRadius         = radius;
      m_uchaDiv.set_size(256 * div);
      unsigned char * dv         = m_uchaDiv.get_data();

      m_size.cx()         = cx;
      m_size.cy()         = cy;

      for(int i = 0; i < m_uchaDiv.get_count(); i++)
      {

         dv[i]= minimum(255,i / div);

      }

      m_rgbaa.set_size(m_size.area());



      //return true;

   }


   void fastblur::initialize(int_size sz,int iRadius)
   {

      return initialize(sz.cx(),sz.cy(),iRadius);

   }


   void fastblur::blur(::image::image *pimage, const ::int_rectangle & rectangle)
   {

      pixmap_lock lock(pimage, rectangle);

      return blur(pimage);

   }


   void fastblur::blur(::image::image *pimage)
   {

      int cx = pimage->width();

      int cy = pimage->height();

      int iRadius = m_iRadius;

      if (cx <= 0 || cy <= 0 || iRadius <= 0)
      {

         throw ::exception(error_wrong_state);

      }

      //if (!)
      initialize(cx, cy, iRadius);
      //{

      //   return false;

      //}

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

      unsigned int * pimage32 = (unsigned int *) m_p->get_data();

      unsigned char * int_point;
      vector4 * t = timage;

      int w = m_size.cx();
      int h = m_size.cy();

      int s = m_p->m_iScan / 4;

      {
auto tickA0 = ::time::now();

         for(::collection::index y = 0; y < h; y++)
         {
            for(::collection::index x = 0; x < w; x++)
            {
               p = (unsigned char *)&pimage32[y * s + x];
               t[y * w + x] = vector4(int_point[0],int_point[1],int_point[2],int_point[3]);
            }
         }
auto tickA1 = ::time::now();
         unsigned int dwA2 = dwA1 - dwA0;
         string str;

         str.formatf("%d",dwA2);

      }



      {
auto tick1 = ::time::now();

         try
         {

            b = do_boxblur(
                timage,
                w,
                h,
                m_iRadius,
                (unsigned int *)m_ucha.get_data(),
                m_uchaDiv.get_data(),
                w * 4,
                w,h,bottomup);

         }
         catch(...)
         {

         }
auto tick2 = ::time::now();
         unsigned int dw3 = dw2 - dw1;

         string str1;
         str1.format("| Parameters: w=%d h=%d rectangle=%d  \n",w,h,m_iRadius);
         string str2;
         str2.format("| time for calculating box blur : %d\b",dw3);

         informationf("/-----------------------------------------\n");
         informationf("| \n");
         information(str1);
         information(str2);
         informationf("| \n");

         ::aura::application * papp = m_p->get_app();
         informationf("/--------------------------------");
         informationf("| fastblur::blur");
         informationf("| ");
         informationf("| do_fastblur = %d ms",dw3);
      }

      {
auto tickC0 = ::time::now();

         for(::collection::index y = 0; y < h; y++)
         {
            for(::collection::index x = 0; x < w; x++)
            {
               p = (unsigned char *)&pimage32[y * s + x];
               t = &timage[y * w + x];
               int_point[0] = (unsigned char)t->w;
               int_point[1] = (unsigned char)t->x;
               int_point[2] = (unsigned char)t->y;
               int_point[3] = (unsigned char)t->z;
            }
         }
auto tickC1 = ::time::now();
         unsigned int dwC2 = dwC1 - dwC0;
         string str;

         str.formatf("%d",dwC2);
      }
#else
      unsigned int * pimage32 = (unsigned int *)pimage->image32();

      vector4 * t = timage;

      int w = m_size.cx();
      int h = m_size.cy();
      int wj = w; // w job
      int hj = h; // h job

      //if(wj % 16 > 0)
      //{
      //   wj = ((wj / 16) * 16) + 16;
      //}

      int s = pimage->scan_size() / 4;

      unsigned char * p;

      {
         
         auto tickA0 = ::time::now();

         for(::collection::index y = 0; y < hj; y++)
         {

            for(::collection::index x = 0; x < wj; x++)
            {

               p = (unsigned char *)&pimage32[y * s + x];

               t[y * wj + x] = vector4(p[0],p[1],p[2],p[3]);

            }

         }
         
         auto tickA1 = ::time::now();

         auto tickA2 = tickA1 - tickA0;

         string str;

         str = as_string(tickA2.integral_millisecond());

      }


      {

         auto tick1 = ::time::now();

         try
         {

            do_stackblur(
                timage,
                w,
                h,
                m_iRadius,
                (unsigned int *)m_rgbaa.get_data(),
                m_uchaDiv.get_data(),
                wj,
                w,h,bottomup);

         }
         catch(...)
         {

         }
         
         auto tick2 = ::time::now();

         auto tick3 = tick2 - tick1;

         if(0)
         {

            string str1;
            str1.format("| Parameters: w=%d h=%d rectangle=%d  \n",wj,hj,m_iRadius);
            string str2;
            str2.format("| time for calculating stack blur : %" PRId64 "ms\b",tick3.integral_millisecond());

            informationf("/-----------------------------------------\n");
            informationf("| \n");
            information(str1);
            information(str2);
            informationf("| \n");

            //::aura::application * papp = pimage->get_app();
            information() << "/--------------------------------";
            information() << "| fastblur::blur";
            information() << "| ";
            information() << "| do_fastblur = %" PRId64 "ms", tick3.integral_millisecond();

         }

      }

      {

         auto tickC0 = ::time::now();

         for(::collection::index y = 0; y < h; y++)
         {

            for(::collection::index x = 0; x < w; x++)
            {

               p = (unsigned char *)&pimage32[y * s + x];
               t = &timage[y * wj + x];
               p[0] = (unsigned char)t->w;
               p[1] = (unsigned char)t->x;
               p[2] = (unsigned char)t->y;
               p[3] = (unsigned char)t->z;

            }

         }
         
         auto tickC1 = ::time::now();
         
         auto tickC2 = tickC1 - tickC0;

         string str;

         str = as_string(tickC2.integral_millisecond());

      }

#endif

#else


      //unsigned int dw1= ::time::now();

#ifdef __arm__

#else

//      ::collection::count cCount = maximum(2,m_iRadius / 8);

      ::collection::count cCount = 2;

      for(::collection::index i = 0; i < cCount; i++)
#endif
      {
         //try
         //{

            do_fastblur(
                pimage->image32(),
                m_size.cx(),
                m_size.cy(),
                m_rgbaa.data(),
                m_uchaDiv.get_data(),
                pimage->scan_size(),
                cx,cy,bottomup);

         //}
         //catch(...)
         //{

         //}

      }

      /*
auto tick2 = ::time::now();
      unsigned int dw3 = dw2 - dw1;
      string str1;
      str1.format("| Parameters: w=%d h=%d rectangle=%d  \n",m_size.cx(),m_size.cy(),m_iRadius);
      string str2;
      str2.format("| time for calculating fast blur : %d\b",dw3);

      informationf("/-----------------------------------------\n");
      informationf("| \n");
      information(str1);
      information(str2);
      informationf("| \n");

      ::aura::application * papp = m_p->get_app();
      informationf("/--------------------------------");
      informationf("| fastblur::blur");
      informationf("| ");
      informationf("| do_fastblur = %d ms",dw3);
      */
#endif

#if defined(__ANDROID__)

      pimage->mult_alpha();

#endif

      //return b;

   }

#if defined(__arm__) && !defined(__ANDROID__) && !defined(RASPBERRYPIOS)


   inline void boxBlurNEON(unsigned int* sourcePixel,unsigned int* destinationPixel,
                           unsigned Δx,int dxLeft,int dxRight,int stride,int strideLine,int effectWidth,int effectHeight)
   {

      float32x4_t deltaX = vdupq_n_float(1.0 / Δx);

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

            float32x4_t sum = vdupq_n_float(0);

            // Fill the kernel
            int maxKernelSize = minimum(dxRight,effectWidth);

            for(int i = 0; i < maxKernelSize; ++i)
            {

               float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + line + i * pixelStride);

               sum = vaddq_float(sum,sourcePixelAsFloat);

            }

            // Blurring

            for(x = 0; x < effectWidth; x++)
            {

               pixelOffset = line + x * pixelStride;

               float32x4_t result = vmulq_float(sum,deltaX);

               storeFloatAsRGBA8(result,destinationPixel + pixelOffset);

               if(x >= dxLeft)
               {

                  float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + pixelOffset - strideLeft);

                  sum = vsubq_float(sum,sourcePixelAsFloat);

               }

               if(x <= dxW)
               {

                  float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + pixelOffset + strideRight);

                  sum = vaddq_float(sum,sourcePixelAsFloat);

               }

            }

         }

      }
      else
      {

         for(int y = 0; y < effectHeight; ++y)
         {

            int line = y * pixelLine;

            float32x4_t sum = vdupq_n_float(0);

            // Fill the kernel
            int maxKernelSize = minimum(dxRight,effectWidth);

            for(int i = 0; i < maxKernelSize; ++i)
            {

               float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + line + i * pixelStride);

               sum = vaddq_float(sum,sourcePixelAsFloat);

            }

            // Blurring
            x = 0;

            pixelOffset = line;

            for(; x < dxLeft; x++)
            {

               float32x4_t result = vmulq_float(sum,deltaX);

               storeFloatAsRGBA8(result,destinationPixel + pixelOffset);

               {

                  float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + pixelOffset + strideRight);

                  sum = vaddq_float(sum,sourcePixelAsFloat);

               }

               pixelOffset += pixelStride;

            }

            for(; x <= dxW; x++)
            {

               float32x4_t result = vmulq_float(sum,deltaX);

               storeFloatAsRGBA8(result,destinationPixel + pixelOffset);

               {

                  float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + pixelOffset - strideLeft);

                  sum = vsubq_float(sum,sourcePixelAsFloat);

               }

               {

                  float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + pixelOffset + strideRight);

                  sum = vaddq_float(sum,sourcePixelAsFloat);

               }

               pixelOffset += pixelStride;

            }


            for(; x < effectWidth; x++)
            {

               float32x4_t result = vmulq_float(sum,deltaX);

               storeFloatAsRGBA8(result,destinationPixel + pixelOffset);

               {

                  float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + pixelOffset - strideLeft);

                  sum = vsubq_float(sum,sourcePixelAsFloat);

               }

               pixelOffset += pixelStride;

            }

         }

      }

   }


   void fastblur::do_fastblur(unsigned int * pimage32,int w,int h,int radius,unsigned int * prgba,unsigned char * dv,int stride,int cx,int cy,int bottomup)
   {

      //int stride = 4 * cx;
      int dxLeft = 0;
      int dxRight = 0;
      int dyLeft = 0;
      int dyRight = 0;
      unsigned int* src = pimage32;
      unsigned int* dst = m_pimage->m_pcolorref;
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
      if(dst != pimage32)
      {

         ::memory_copy(pimage32,dst,m_p->m_iScan * m_p.height());

      }

   }

#else

#if VECTOR3_SSE

   inline void boxBlurSSE(vector4* sourcePixel,vector4* destinationPixel,
                          unsigned Δx,int dxLeft,int dxRight,int stride,int strideLine,int effectWidth,int effectHeight)
   {

      vector4 deltaX = vector4(1.0f / Δx,1.0f / Δx,1.0f / Δx,1.0f / Δx);

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
            int maxKernelSize = minimum(dxRight,effectWidth);

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
            int maxKernelSize = minimum(dxRight,effectWidth);

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
   * this version is vectorized for float32 rectangle/g/b/a using sse
   *
   * vector4() is just a class wrapping _mm_zzz_ps() family of SSE intrinsics
   * ( if you need one, start here:
   *  - http://fastcpp.blogspot.com/2011/12/simple-vector3-class-with-sse-support.html )
   *
   * radius is in (whole) pixels
   *
   */

   void fastblur::stackblur(vector4* pimage32,const int w,const int h,const int radius, int wj)
   {

      if(radius < 1) return;	// nothing to do

      // some values for convenience
      //const int w = pimage->width;
      //const int h = pimage->height;
      const int wm = w - 1;
      const int hm = h - 1;
      const int r1 = radius + 1;

      // number of divisions in the kernel
      // D(-rectangle), D(-rectangle+1), ... D(0), ... D(rectangle-1), D(rectangle)
      const int div = (radius * 2) + 1;

      // temporary output space for first pass.
      //vector4* tsurface = ___new vector4[wh];

      // lookup table for clamping pixel offsets
      // as the kernel passes the right (or lower) edge
      // of the input data
      //int* const vmin = __allocate< int[maximum >(w,h)];

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
         // samples of [0] (maximum()).  minimum() handles
         // images which are smaller than the kernel.
         for(int i=-radius; i <= radius; i++)
         {

            // calcualte address of source pixel
            const vector4& p = pimage32[yi + minimum(wm,maximum(i,0))];

            // put pixel in the stack
            vector4& sir = stack[i + radius];
            sir = p;

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
            // minimum() will cause the last pixel to repeat.
            //if(y == 0) vmin[x] = minimum(x + radius + 1,wm);
            //vector4& p = pimage32[yw + vmin[x]];
            vector4& p = pimage32[yw + vxmin[x]];


            // erase "past" pixels from the sum
            sum -= outsum;


            // erase "left" side of stack from outsum
            stackstart = stackpointer - radius + div;
            vector4& sir = stack[stackstart % div];
            outsum -= sir;

            // now this (same) stack entry is the "right" side
            // add ___new pixel to the stack, and update accumulators
            sir = p;
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

            yi = maximum(0,yp) + x;
            const vector4& p = tsurface[yi];

            sir = p;

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

            pimage32[yi] = sum * divsum;

            stackstart = stackpointer - radius + div;
            vector4& sir = stack[stackstart % div];
            sum -= outsum;
            outsum -= sir;

            //if(x == 0) vmin[y] = minimum(y + r1,hm)*w;
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


   void fastblur::do_boxblur(vector4 * pimage,int w,int h,int radius,unsigned int * prgba,unsigned char * dv,int stride,int cx,int cy,int bottomup)
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

         ::memory_copy(pimage,dst,stride * h);

      }


      //return true;

   }


   void fastblur::do_stackblur(vector4 * pimage,int w,int h,int radius,unsigned int * prgba,unsigned char * dv,int stride,int cx,int cy,int bottomup)
   {

      stackblur(pimage,w,h,radius, stride);

      ///return true;

   }


#endif // VECTOR3_SSE



   void fastblur::do_fastblur(image32_t * pimage32,int w,int h,rgba_t * prgba,unsigned char * dv,int stride,int cx,int cy,int bottomup)
   {

      int radius = m_iRadius;

      if(radius <= 0)
      {

         throw ::exception(error_wrong_state);

      }

      int rsum,gsum,bsum,asum;
      int x;
      int y;
      int i;
      int yp;
      int yw;
      unsigned char * pbyte_1;
      unsigned char * pbyte_2;
      int wm = w - 1;
      //      int hm = h - 1;
      int wr = minimum(w,cx) - 1 - radius;
      int hr = minimum(h,cy) - 1 - radius;
      //   int div        = radius + radius + 1;
      unsigned char * p;

      yw = 0;

      h = minimum(h,cy);

      w = minimum(w,cx);

      if(bottomup)
      {

         pimage32 = (image32_t *)(((unsigned char *)pimage32) + (stride * (cy - h)));

         prgba = (rgba_t *)(((unsigned char *)prgba) + (stride * (cy - h)));

      }

//      int dir;

      //if(bottomup)
      //{

      //   dir = -1;

      //}
      //else
      //{

      //   dir = 1;

      //}

      int workstride = w * sizeof(unsigned int);

      //int * pimage32 = (int *)pimage32;
      unsigned char * pb = (unsigned char *)pimage32;
      unsigned char * pwork = (unsigned char *)prgba;
      unsigned char * pwk = (unsigned char *)prgba;

      for(y = 0; y < h; y++)
      {

         pwork = &pwk[workstride * y];

         asum = 0;
         rsum = 0;
         gsum = 0;
         bsum = 0;

         for(i = -radius; i <= radius; i++)
         {

            p = &pb[yw + (minimum(wm,maximum(i,0)) * 4)];
            rsum += p[0];
            gsum += p[1];
            bsum += p[2];
            asum += p[3];

         }

         pbyte_1 = &pb[yw + (radius + 1) * 4];
         pbyte_2 = &pb[yw];

         for(x = 0; x < radius; x++)
         {

            pwork[0] = dv[rsum];
            pwork[1] = dv[gsum];
            pwork[2] = dv[bsum];
            pwork[3] = dv[asum];

            rsum += pbyte_1[0] - pbyte_2[0];
            gsum += pbyte_1[1] - pbyte_2[1];
            bsum += pbyte_1[2] - pbyte_2[2];
            asum += pbyte_1[3] - pbyte_2[3];

            pwork += 4;
            pbyte_1 += 4;

         }

         for(; x < wr; x++)
         {

            pwork[0] = dv[rsum];
            pwork[1] = dv[gsum];
            pwork[2] = dv[bsum];
            pwork[3] = dv[asum];


            rsum += pbyte_1[0] - pbyte_2[0];
            gsum += pbyte_1[1] - pbyte_2[1];
            bsum += pbyte_1[2] - pbyte_2[2];
            asum += pbyte_1[3] - pbyte_2[3];

            pbyte_1 += 4;
            pbyte_2 += 4;
            pwork += 4;

         }

         pbyte_1 -= 4;

         for(; x < w; x++)
         {

            pwork[0] = dv[rsum];
            pwork[1] = dv[gsum];
            pwork[2] = dv[bsum];
            pwork[3] = dv[asum];


            rsum += pbyte_1[0] - pbyte_2[0];
            gsum += pbyte_1[1] - pbyte_2[1];
            bsum += pbyte_1[2] - pbyte_2[2];
            asum += pbyte_1[3] - pbyte_2[3];

            pbyte_2 += 4;
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
            p = &pwk[maximum(0,yp) + x * 4];
            rsum += p[0];
            gsum += p[1];
            bsum += p[2];
            asum += p[3];
            yp += stride;
         }

         unsigned char * r1 = &pwk[(x * 4) + (radius + 1) * workstride];
         unsigned char * r2 = &pwk[(x * 4)];

         pbyte_1 = (unsigned char *)&pimage32[x];

         for(y = 0; y < radius; y++)
         {

            pbyte_1[0] = dv[rsum];
            pbyte_1[1] = dv[gsum];
            pbyte_1[2] = dv[bsum];
            pbyte_1[3] = dv[asum];

            rsum += r1[0] - r2[0];
            gsum += r1[1] - r2[1];
            bsum += r1[2] - r2[2];
            asum += r1[3] - r2[3];

            pbyte_1 += stride;
            r1 += workstride;

         }

         for(; y < hr; y++)
         {

            pbyte_1[0] = dv[rsum];
            pbyte_1[1] = dv[gsum];
            pbyte_1[2] = dv[bsum];
            pbyte_1[3] = dv[asum];

            rsum += r1[0] - r2[0];
            gsum += r1[1] - r2[1];
            bsum += r1[2] - r2[2];
            asum += r1[3] - r2[3];

            pbyte_1 += stride;
            r1 += workstride;
            r2 += workstride;

         }

         pbyte_1 -= stride;
         r1 -= workstride;

         for(; y < h; y++)
         {

            pbyte_1[0] = dv[rsum];
            pbyte_1[1] = dv[gsum];
            pbyte_1[2] = dv[bsum];
            pbyte_1[3] = dv[asum];

            rsum += r1[0] - r2[0];
            gsum += r1[1] - r2[1];
            bsum += r1[2] - r2[2];
            asum += r1[3] - r2[3];

            pbyte_1 += stride;
            r2 += workstride;

         }

      }

      //return true;

   }

#endif // VECTOR3_SSE

   void fastblur::do_fastblur(image32_t * pimage32,int w,int h,unsigned char * rectangle,unsigned char * g,unsigned char * b,unsigned char * a,unsigned char * dv,int stride,int * vmin,int * vmax,int cx,int cy,int bottomup)
   {

      throw ::exception(error_wrong_state);

      /*

            if (radius <= 0)
            {

               return false;

            }

            int asum, rsum, gsum, bsum, x, y, i, yp, yi, yw;
            int s = stride / sizeof(::color32_t);
            int wm = w - 1;
            int hm = h - 1;
            int div = radius + radius + 1;
            int int_point;
            int pbyte_1;
            int pbyte_2;

            yw = yi = 0;

            for (x = 0; x < w; x++)
            {
               vmin[x] = minimum(x + radius + 1, wm);
               vmax[x] = maximum(x - radius, 0);
            }

            for (y = 0; y < h; y++)
            {
               asum = rsum = gsum = bsum = 0;
               yi = y * s;
               for (i = -radius; i <= radius; i++)
               {
                  p = pimage32[yi + minimum(wm, maximum(i, 0))];
                  asum += ((int_point & 0xff000000) >> 24);
                  rsum += ((int_point & 0xff0000) >> 16);
                  gsum += ((int_point & 0x00ff00) >> 8);
                  bsum += (int_point & 0x0000ff);
               }
               for (x = 0; x < w; x++)
               {
                  a[yi] = dv[asum];
                  rectangle[yi] = dv[rsum];
                  g[yi] = dv[gsum];
                  b[yi] = dv[bsum];

                  pbyte_1 = pimage32[yw + vmin[x]];
                  pbyte_2 = pimage32[yw + vmax[x]];

                  asum += ((pbyte_1 >> 24) & 0xff) - ((pbyte_2 >> 24) & 0xff);
                  rsum += ((pbyte_1 & 0x00ff0000) - (pbyte_2 & 0x00ff0000)) >> 16;
                  gsum += ((pbyte_1 & 0x0000ff00) - (pbyte_2 & 0x0000ff00)) >> 8;
                  bsum += ((pbyte_1 & 0x000000ff) - (pbyte_2 & 0x000000ff));
                  yi++;
               }
               yw += s;
            }
            for (y = 0; y < h; y++)
            {
               vmin[y] = minimum(y + radius + 1, hm) * s;
               vmax[y] = maximum(y - radius, 0) * s;
            }

            for (x = 0; x < w; x++)
            {
               asum = rsum = gsum = bsum = 0;
               yp = -radius*s;
               for (i = -radius; i <= radius; i++)
               {
                  yi = maximum(0, yp) + x;
                  rsum += rectangle[yi];
                  gsum += g[yi];
                  bsum += b[yi];
                  asum += a[yi];
                  yp += s;
               }
               yi = x;
               for (y = 0; y < h; y++)
               {
                  pimage32[yi] = (dv[asum] << 24) | (dv[rsum] << 16) | (dv[gsum] << 8) | dv[bsum];

                  pbyte_1 = x + vmin[y];
                  pbyte_2 = x + vmax[y];

                  rsum += rectangle[pbyte_1] - rectangle[pbyte_2];
                  gsum += g[pbyte_1] - g[pbyte_2];
                  bsum += b[pbyte_1] - b[pbyte_2];
                  asum += a[pbyte_1] - a[pbyte_2];

                  yi += s;

               }

            }

            return true;

      */

   }




} // namespace image


