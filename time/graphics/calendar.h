#pragma once


#include "time/graphical/calendar.h"
//#include "acme/prototype/prototype/pointer.h"


namespace datetime
{


   namespace calendar
   {


      class CLASS_DECL_CA2_TIME graphics :
         virtual public ::datetime::calendar::graphical
      {
      public:


         ::write_text::font_pointer     m_pfont;
         ::write_text::font_pointer     m_pfontYear;
         ::write_text::font_pointer     m_pfontMonth;
         ::write_text::font_pointer     m_pfontSpin;
 /*        ::i32                        m_iColWidth;
         ::i32                        m_iLineHeight;
         i32_point                      m_point;*/


         graphics();
         ~graphics() override;


         void initialize(::particle * pparticle) override;


         virtual void GetRectDay(::earth::time& time, ::i32_rectangle * lprect);
         virtual void GetRectDay(int32_t iWeekDay, int32_t iLine, ::i32_rectangle * lprect);
         virtual void GetRect(::i32_rectangle * lprect, const e_element & eelement);

         void _001OnDraw(::draw2d::graphics* pgraphics);

         void set_pos(i32_point pt, i32_size sz);

         virtual e_element hit_test(const ::i32_point & point, ::user::e_zorder ezorder);
         virtual bool hit_test(const e_element & eelement, const ::i32_point& point);
         virtual bool time_hit_test(::earth::time& time, const ::i32_point& point);

      };


   } // namespace calendar


} // namespace datetime



