#pragma once


#include "object.h"
#include "acme/primitive/geometry2d/size.h"


namespace draw2d
{


   class CLASS_DECL_AURA brush :
      virtual public ::draw2d::object
   {
   public:



      enum_brush              m_ebrush;

      ::color::color          m_color;
      point_f64               m_point1;
      point_f64               m_point2;
      ::color::color          m_color1;
      ::color::color          m_color2;
      point_f64               m_point;
      size_f64                m_size;
      ::image_pointer         m_pimage;
      double                  m_dRadius;


      brush();
      ~brush() override;


      virtual void destroy() override;

      
      // void dump(dump_context & dumpcontext) const override;


      virtual bool create_null();
      virtual bool create_solid(::color::color color);
      virtual bool CreateHatchBrush(i32 nIndex, ::color::color color);
      //virtual bool CreateBrushIndirect(const LOGBRUSH* pLogBrush);

      virtual bool CreatePatternBrush(::image * pimage, const ::size_f64 & size = nullptr);
//#ifdef WINDOWS
//      virtual bool CreateDIBPatternBrush(HGLOBAL hPackedDIB, ::u32 nUsage);
//#endif
      virtual bool CreateDIBPatternBrush(const void * pPackedDIB, ::u32 nUsage);

      virtual bool CreateSysColorBrush(i32 nIndex);

      virtual bool CreateLinearGradientBrush(const point_i32 & point1, const point_i32 & point2, const ::color::color & color1, const ::color::color & color2);
      virtual bool CreateRadialGradientBrush(const ::point_i32 & point,size_i32 s,const ::color::color & color1,const ::color::color & color2);
      virtual bool CreateLinearGradientBrush(point_f64 point1,point_f64 point2,const ::color::color & color1,const ::color::color & color2);
      virtual bool CreateRadialGradientBrush(point_f64 point,size_f64 s,const ::color::color & color1,const ::color::color & color2);
      virtual bool CreateBoxGradientBrush(point_f64 point, size_f64 s, double dRadius, const ::color::color & colorInner, const ::color::color & colorOuter);

      //virtual i32 GetLogBrush(LOGBRUSH* pLogBrush);

      brush & operator = (const ::draw2d::brush & pbrushSrc);

   };

   //class CLASS_DECL_AURA brush_pointer :
   //   public ::pointer<brush>
   //{
   //public:


   //   brush_pointer()
   //   {
   //   }

   //   brush_pointer(brush * pbrush) :
   //      ::pointer<brush>(pbrush)
   //   {
   //   }

   //   brush_pointer(const ::pointer<brush>& br) :
   //      ::pointer<brush>(br)
   //   {
   //   }

   //   brush_pointer(const ::allocer & allocer) :
   //      ::pointer<brush>(allocer)
   //   {
   //   }

   //   // create_solid
   //   brush_pointer(const ::allocer & allocer, ::color::color crColor) :
   //      ::pointer<brush>(allocer)
   //   {
   //      m_p->create_solid(crColor);
   //   }

   //   /*
   //         // CreateHatchBrush
   //         brush_pointer(::particle * pparticle, i32 nIndex, ::color::color crColor) :
   //            ::pointer<brush>(pparticle)
   //         {
   //            m_p->construct(nIndex, crColor);
   //         }
   //         // CreatePatternBrush
   //         brush_pointer(::particle * pparticle, bitmap * pbitmap) :
   //            ::pointer<brush>(pparticle)
   //         {
   //            m_p->construct(pbitmap);
   //         }
   //   */


   //   brush_pointer & operator = (::draw2d::brush * pbrush)
   //   {

   //      ::pointer<brush>:operator = (pbrush);

   //      return *this;

   //   }


   //};


} // namespace draw2d



