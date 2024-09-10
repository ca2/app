// Super Fast Blur v1.1
// by Mario Klingemann <http://incubator.quasimondo.com>
//
// Tip: Multiple invovations of this filter with a small
// radius will approximate a gaussian blur quite well.
//
#pragma once


#include "acme/primitive/geometry2d/size.h"


//#include "acme/primitive/collection/numeric_array.h"
////#include "acme/primitive/primitive/object.h"
//#include "acme/primitive/geometry2d/_geometry2d.h"


namespace image
{


   class CLASS_DECL_AURA fastblur :
      virtual public ::particle
   {
   public:


      //::image::image_pointer  m_pimage;


#if VECTOR3_SSE

      // temporary output space for first pass.
      vector4 * timage;
      vector4 * tsurface;

      // lookup table for clamping pixel offsets
      // as the kernel passes the right (or lower) edge
      // of the input data
      int * vxmin;
      int * vymin;


      vector4 * m_stack;

      void stackblur(vector4* colorbuffer,const int w,const int h,const int radius, int wj);

#endif // VECTOR3_SSE

      ::size_i32           m_size;
      i32                  m_iRadius;
      byte_array           m_uchaR;
      byte_array           m_uchaG;
      byte_array           m_uchaB;
      byte_array           m_uchaA;
      byte_array           m_uchaDiv;
      ::array < rgba_t >   m_rgbaa;
      i64_array            m_iaVmin;
      i64_array            m_iaVmax;


      fastblur();
      ~fastblur();

      using ::particle::initialize;
      void initialize(i32 cx, i32 cy, i32 iRadius);
      void initialize(::size_i32 sz, i32 iRadius);


      virtual void blur(::image::image *pimage, const ::rectangle_i32 & rectangle);


      virtual void blur(::image::image *pimage);


      void do_fastblur(image32_t * pdata,i32 w,i32 h,u8 * rectangle,u8 * g,u8 * b,u8 * a,u8 * dv,i32 stride,i32 * vmin,i32 * vmax,int cx,int cy,int bottomup);
      void do_fastblur(image32_t * pdata,i32 w,i32 h,rgba_t * prgba,u8 * dv,i32 stride,int cx,int cy,int bottomup);
#if VECTOR3_SSE
      void do_boxblur(vector4 * pdata,i32 w,i32 h,u32 * prgba,u8 * dv,i32 stride,int cx,int cy,int bottomup);
      void do_stackblur(vector4 * pdata,i32 w,i32 h,u32 * prgba,u8 * dv,i32 stride,int cx,int cy,int bottomup);
#endif // VECTOR3_SSE


   };


} // namespace image



