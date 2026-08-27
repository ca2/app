#pragma once


#include "object.h"


namespace draw2d
{


   class CLASS_DECL_AURA pen :
      virtual public ::draw2d::object
   {
   public:


      enum_pen                m_epen;
      enum_line_cap           m_elinecapBeg;
      enum_line_cap           m_elinecapEnd;
      enum_line_join          m_elinejoin;
      enum_pen_align          m_epenalign;
      ::f64                   m_dWidth;
      ::color::color          m_color;
      ::pointer<brush>        m_pdraw2dbrush;


      pen();
      ~pen() override;

      virtual bool is_similar_attributes(const pen * ppenSrc);
      virtual bool copy_attributes(const pen * ppenSrc);
      // void dump(dump_context & dumpcontext) const override;

      virtual bool create_null();
      virtual bool create_solid(::f64 dWidth, const ::color::color &color);
      virtual bool create_brush(::f64 dWidth, ::draw2d::brush * pdraw2dbrush);

      virtual enum_line_cap get_beg_cap();
      virtual bool set_beg_cap(enum_line_cap ebegcap);

      virtual enum_line_cap get_end_cap();
      virtual bool set_end_cap(enum_line_cap eendcap);

      virtual enum_line_join get_line_join();
      virtual bool set_line_join(enum_line_join elinejoin);

      pen & operator = (const pen & ppenSrc);



   };


   using pen_pointer = ::pointer<pen>;


   //class CLASS_DECL_AURA pen_pointer :
   //   public ::pointer<pen>
   //{
   //public:

   //   pen_pointer()
   //   {
   //   }

   //   pen_pointer(pen * pdraw2dpen) :
   //      ::pointer<pen>(pdraw2dpen)
   //   {
   //   }

   //   pen_pointer(const ::pointer<pen>& point) :
   //      ::pointer<pen>(point)
   //   {
   //   }

   //   pen_pointer(const ::allocer & allocer) :
   //      ::pointer<pen>(allocer)
   //   {
   //   }

   //   pen_pointer(const ::allocer & allocer, ::f64 dWidth, ::color::color crColor);
   //   /*
   //         pen_pointer(::particle * pparticle, ::i32 nPenStyle, ::i32 nWidth, const LOGBRUSH* pLogBrush,
   //            ::i32 nStyleCount = 0, const ::u32* pStyle = nullptr) :

   //            ::pointer<pen>(pparticle)
   //         {
   //            m_p->construct(nPenStyle, nWidth, pLogBrush, nStyleCount, pStyle);

   //         }
   //   */


   //   pen_pointer & operator = (::draw2d::pen * pdraw2dpen)
   //   {

   //      ::pointer<pen>:operator = (pdraw2dpen);

   //      return *this;

   //   }


   //};

   //inline pen_pointer solid_pen(::f64 dWidth, const ::color::color& color)
   //{

   //   auto pdraw2dpen = ::createø < pen >();

   //   pdraw2dpen->create_solid(dWidth, color);

   //   return pdraw2dpen;

   //}


} // namespace draw2d





