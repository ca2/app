#pragma once


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
      double                  m_dWidth;
      ::color                 m_color;
      __pointer(brush)        m_pbrush;


      pen();
      virtual ~pen();


      virtual void dump(dump_context & dumpcontext) const;

      virtual bool create_null();
      virtual bool create_solid(double dWidth, const ::color &color);
      virtual bool create_brush(double dWidth, ::draw2d::brush * pbrush);

      virtual enum_line_cap get_beg_cap();
      virtual bool set_beg_cap(enum_line_cap ebegcap);

      virtual enum_line_cap get_end_cap();
      virtual bool set_end_cap(enum_line_cap eendcap);

      virtual enum_line_join get_line_join();
      virtual bool set_line_join(enum_line_join elinejoin);

      pen & operator = (const pen & penSrc);



   };


   using pen_pointer = __pointer(pen);
   //class CLASS_DECL_AURA pen_pointer :
   //   public pointer < pen >
   //{
   //public:

   //   pen_pointer()
   //   {
   //   }

   //   pen_pointer(pen * ppen) :
   //      pointer < pen > (ppen)
   //   {
   //   }

   //   pen_pointer(const pointer < pen > & point) :
   //      pointer < pen > (point)
   //   {
   //   }

   //   pen_pointer(const ::allocer & allocer) :
   //      pointer < pen > (allocer)
   //   {
   //   }

   //   pen_pointer(const ::allocer & allocer, double dWidth, color32_t crColor);
   //   /*
   //         pen_pointer(::object * pobject, i32 nPenStyle, i32 nWidth, const LOGBRUSH* pLogBrush,
   //            i32 nStyleCount = 0, const u32* pStyle = nullptr) :

   //            pointer < pen > (pobject)
   //         {
   //            m_p->construct(nPenStyle, nWidth, pLogBrush, nStyleCount, pStyle);

   //         }
   //   */


   //   pen_pointer & operator = (::draw2d::pen * ppen)
   //   {

   //      pointer < pen >::operator = (ppen);

   //      return *this;

   //   }


   //};

   inline pen_pointer solid_pen(double dWidth, const ::color& color)
   {

      auto ppen = ::__create < pen >();

      ppen->create_solid(dWidth, color);

      return ppen;

   }


} // namespace draw2d





