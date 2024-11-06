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

      // lookup table for clamping pixel offsets
      // as the kernel passes the right (or lower) edge
      // of the input data
      int * vxmin;
      int * vymin;


      vector4 * m_stack;

      void stackblur(vector4* colorbuffer,const int w,const int h,const int radius, int wj);

#endif // VECTOR3_SSE

      ::size_i32           m_size;
      int                  m_iRadius;
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
      void initialize(int cx, int cy, int iRadius);
      void initialize(::size_i32 sz, int iRadius);


      virtual void blur(::image::image *pimage, const ::rectangle_i32 & rectangle);


      virtual void blur(::image::image *pimage);


      void do_fastblur(image32_t * pdata,int w,int h,unsigned char * rectangle,unsigned char * g,unsigned char * b,unsigned char * a,unsigned char * dv,int stride,int * vmin,int * vmax,int cx,int cy,int bottomup);
      void do_fastblur(image32_t * pdata,int w,int h,rgba_t * prgba,unsigned char * dv,int stride,int cx,int cy,int bottomup);
#if VECTOR3_SSE
      void do_boxblur(vector4 * pdata,int w,int h,unsigned int * prgba,unsigned char * dv,int stride,int cx,int cy,int bottomup);
      void do_stackblur(vector4 * pdata,int w,int h,unsigned int * prgba,unsigned char * dv,int stride,int cx,int cy,int bottomup);
#endif // VECTOR3_SSE


   };


} // namespace image



