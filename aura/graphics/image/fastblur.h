// Super Fast Blur v1.1
// by Mario Klingemann <http://incubator.quasimondo.com>
//
// Tip: Multiple invovations of this filter with a small
// radius will approximate a gaussian blur quite well.
//
#pragma once


#include "acme/prototype/geometry2d/size.h"


//#include "acme/prototype/collection/numeric_array.h"
////#include "acme/prototype/prototype/object.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"


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

      // find table for clamping pixel offsets
      // as the kernel passes the right (or lower) edge
      // of the input data
      ::i32 * vxmin;
      ::i32 * vymin;


      vector4 * m_stack;

      void stackblur(vector4* colorbuffer,const ::i32 w,const ::i32 h,const ::i32 radius, ::i32 wj);

#endif // VECTOR3_SSE

      ::i32_size           m_size;
      ::i32                  m_iRadius;
      byte_array           m_u8aR;
      byte_array           m_u8aG;
      byte_array           m_u8aB;
      byte_array           m_u8aA;
      byte_array           m_u8aDiv;
      ::array < rgba_t >   m_rgbaa;
      i64_array_base            m_iaVmin;
      i64_array_base            m_iaVmax;


      fastblur();
      ~fastblur();

      using ::particle::initialize;
      void initialize(::i32 cx, ::i32 cy, ::i32 iRadius);
      void initialize(::i32_size sz, ::i32 iRadius);


      virtual void blur(::image::image *pimage, const ::i32_rectangle & rectangle);


      virtual void blur(::image::image *pimage);


      void do_fastblur(image32_t * pdata,::i32 w,::i32 h,::u8 * rectangle,::u8 * g,::u8 * b,::u8 * a,::u8 * dv,::i32 stride,::i32 * vmin,::i32 * vmax,::i32 cx,::i32 cy,::i32 bottomup);
      void do_fastblur(image32_t * pdata,::i32 w,::i32 h,rgba_t * prgba,::u8 * dv,::i32 stride,::i32 cx,::i32 cy,::i32 bottomup);
#if VECTOR3_SSE
      void do_boxblur(vector4 * pdata,::i32 w,::i32 h,::u32 * prgba,::u8 * dv,::i32 stride,::i32 cx,::i32 cy,::i32 bottomup);
      void do_stackblur(vector4 * pdata,::i32 w,::i32 h,::u32 * prgba,::u8 * dv,::i32 stride,::i32 cx,::i32 cy,::i32 bottomup);
#endif // VECTOR3_SSE


   };


} // namespace image



