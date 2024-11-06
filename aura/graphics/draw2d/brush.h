#pragma once


#include "object.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/size.h"


namespace draw2d
{


   class CLASS_DECL_AURA brush :
      virtual public ::draw2d::object
   {
   public:



      enum_brush              m_ebrush;

      ::color::color          m_color;
      double_point               m_point1;
      double_point               m_point2;
      ::color::color          m_color1;
      ::color::color          m_color2;
      double_point               m_point;
      double_size                m_size;
      ::image::image_pointer         m_pimage;
      double                  m_dRadius;


      brush();
      ~brush() override;


      virtual void destroy() override;

      
      // void dump(dump_context & dumpcontext) const override;


      virtual bool create_null();
      virtual bool create_solid(::color::color color);
      virtual bool CreateHatchBrush(int nIndex, ::color::color color);
      //virtual bool CreateBrushIndirect(const LOGBRUSH* pLogBrush);

      virtual bool CreatePatternBrush(::image::image *pimage, const ::double_size & size = {});
//#ifdef WINDOWS
//      virtual bool CreateDIBPatternBrush(HGLOBAL hPackedDIB, unsigned int nUsage);
//#endif
      virtual bool CreateDIBPatternBrush(const void * pPackedDIB, unsigned int nUsage);

      virtual bool CreateSysColorBrush(int nIndex);

      virtual bool CreateLinearGradientBrush(const int_point & point1, const int_point & point2, const ::color::color & color1, const ::color::color & color2);
      virtual bool CreateRadialGradientBrush(const ::int_point & point,int_size s,const ::color::color & color1,const ::color::color & color2);
      virtual bool CreateLinearGradientBrush(double_point point1,double_point point2,const ::color::color & color1,const ::color::color & color2);
      virtual bool CreateRadialGradientBrush(double_point point,double_size s,const ::color::color & color1,const ::color::color & color2);
      virtual bool CreateBoxGradientBrush(double_point point, double_size s, double dRadius, const ::color::color & colorInner, const ::color::color & colorOuter);

      //virtual int GetLogBrush(LOGBRUSH* pLogBrush);

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
   //         brush_pointer(::particle * pparticle, int nIndex, ::color::color crColor) :
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



