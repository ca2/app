#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA brush :
      virtual public ::draw2d::object
   {
   public:


      enum enum_type
      {

         e_type_null,
         type_solid,
         type_linear_gradient_point_color,
         type_radial_gradient_color,
         type_pattern,

      };


      ::color::color                m_color;
      enum_type               m_etype;
      point_f64               m_point1;
      point_f64               m_point2;
      ::color::color                m_color1;
      ::color::color                m_color2;
      point_f64               m_point;
      size_f64                m_size;
      ::image_pointer      m_pimage;


      brush();
      virtual ~brush();


      virtual void finalize() override;

      virtual void dump(dump_context & dumpcontext) const override;

      virtual bool create_null();
      virtual bool create_solid(::color::color color);
      virtual bool CreateHatchBrush(i32 nIndex, ::color::color color);
      //virtual bool CreateBrushIndirect(const LOGBRUSH* pLogBrush);

      virtual bool CreatePatternBrush(::image * pimage);
//#ifdef WINDOWS
//      virtual bool CreateDIBPatternBrush(HGLOBAL hPackedDIB, ::u32 nUsage);
//#endif
      virtual bool CreateDIBPatternBrush(const void * pPackedDIB, ::u32 nUsage);

      virtual bool CreateSysColorBrush(i32 nIndex);

      virtual bool CreateLinearGradientBrush(const point_i32 & point1, const point_i32 & point2, const ::color::color & color1, const ::color::color & color2);
      virtual bool CreateRadialGradientBrush(const ::point_i32 & point,size_i32 s,const ::color::color & color1,const ::color::color & color2);
      virtual bool CreateLinearGradientBrush(point_f64 point1,point_f64 point2,const ::color::color & color1,const ::color::color & color2);
      virtual bool CreateRadialGradientBrush(point_f64 point,size_f64 s,const ::color::color & color1,const ::color::color & color2);

      //virtual i32 GetLogBrush(LOGBRUSH* pLogBrush);

      brush & operator = (const ::draw2d::brush & brushSrc);

   };

   using brush_pointer = __pointer(brush);

   //class CLASS_DECL_AURA brush_pointer :
   //   public pointer < brush >
   //{
   //public:


   //   brush_pointer()
   //   {
   //   }

   //   brush_pointer(brush * pbrush) :
   //      pointer < brush > (pbrush)
   //   {
   //   }

   //   brush_pointer(const pointer < brush > & br) :
   //      pointer < brush > (br)
   //   {
   //   }

   //   brush_pointer(const ::allocer & allocer) :
   //      pointer < brush > (allocer)
   //   {
   //   }

   //   // create_solid
   //   brush_pointer(const ::allocer & allocer, color32_t crColor) :
   //      pointer < brush > (allocer)
   //   {
   //      m_p->create_solid(crColor);
   //   }

   //   /*
   //         // CreateHatchBrush
   //         brush_pointer(::object * pobject, i32 nIndex, color32_t crColor) :
   //            pointer < brush > (pobject)
   //         {
   //            m_p->construct(nIndex, crColor);
   //         }
   //         // CreatePatternBrush
   //         brush_pointer(::object * pobject, bitmap * pbitmap) :
   //            pointer < brush > (pobject)
   //         {
   //            m_p->construct(pbitmap);
   //         }
   //   */


   //   brush_pointer & operator = (::draw2d::brush * pbrush)
   //   {

   //      pointer < brush >::operator = (pbrush);

   //      return *this;

   //   }


   //};


} // namespace draw2d



