#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA pen :
      virtual public ::draw2d::object
   {
   public:


      
      enum e_type
      {

         type_null,
         type_solid,
         type_dot,
         type_brush,
         type_dash

      };


      enum e_line_cap
      {

         line_cap_flat,
         line_cap_round,
         line_cap_square,

      };

      enum e_align
      {

         align_center,
         align_inset,

      };


      enum e_line_join
      {

         line_join_miter,
         line_join_bevel,
         line_join_round,
         line_join_miter_clipped

      };


      e_type                  m_etype;
      e_line_cap              m_elinecapBeg;
      e_line_cap              m_elinecapEnd;
      e_line_join             m_elinejoin;
      e_align                 m_ealign;
      double                  m_dWidth;
      ::color                 m_color;
      __pointer(brush)        m_pbrush;


      pen();
      virtual ~pen();


      virtual void dump(dump_context & dumpcontext) const;

      virtual bool create_null();
      virtual bool create_solid(double dWidth, COLORREF crColor);
      virtual bool create_brush(double dWidth, ::draw2d::brush * pbrush);

      virtual e_line_cap get_beg_cap();
      virtual bool set_beg_cap(e_line_cap ebegcap);

      virtual e_line_cap get_end_cap();
      virtual bool set_end_cap(e_line_cap eendcap);

      virtual e_line_join get_line_join();
      virtual bool set_line_join(e_line_join elinejoin);

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

   //   pen_pointer(const ::allocer & allocer, double dWidth, COLORREF crColor);
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





