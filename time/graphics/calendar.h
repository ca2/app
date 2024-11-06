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
 /*        int                        m_iColWidth;
         int                        m_iLineHeight;
         int_point                      m_point;*/


         graphics();
         ~graphics() override;


         void initialize(::particle * pparticle) override;


         virtual void GetRectDay(::earth::time& time, ::int_rectangle * lprect);
         virtual void GetRectDay(int32_t iWeekDay, int32_t iLine, ::int_rectangle * lprect);
         virtual void GetRect(::int_rectangle * lprect, enum enum_element eelement);

         void _001OnDraw(::draw2d::graphics* pgraphics);

         void set_pos(int_point pt, int_size sz);

         virtual enum_element hit_test(const ::int_point & point, ::user::e_zorder ezorder);
         virtual bool hit_test(enum_element eelement, const ::int_point& point);
         virtual bool time_hit_test(::earth::time& time, const ::int_point& point);

      };


   } // namespace calendar


} // namespace datetime



