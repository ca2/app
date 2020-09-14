#pragma once


namespace datetime
{


   namespace calendar
   {


      class CLASS_DECL_CA2_TIME graphics :
         virtual public ::datetime::calendar::visual
      {
      public:


         ::draw2d::font_pointer     m_pfont;
         ::draw2d::font_pointer     m_pfontYear;
         ::draw2d::font_pointer     m_pfontMonth;
         ::draw2d::font_pointer     m_pfontSpin;
 /*        int                        m_iColWidth;
         int                        m_iLineHeight;
         point                      m_point;*/


         graphics();
         virtual ~graphics();


         virtual ::estatus initialize(::layered * pobjectContext) override;


         virtual void GetRectDay(::datetime::time& time, LPRECT lprect);
         virtual void GetRectDay(int32_t iWeekDay, int32_t iLine, LPRECT lprect);
         virtual void GetRect(LPRECT lprect, enum enum_element eelement);

         void _001OnDraw(::draw2d::graphics* pgraphics);

         void set_pos(point pt, size sz);

         virtual enum_element hit_test(const ::point& point);
         virtual bool hit_test(enum_element eelement, const ::point& point);
         virtual bool time_hit_test(::datetime::time& time, const ::point& point);

      };


   } // namespace calendar


} // namespace datetime



