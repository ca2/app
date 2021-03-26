#pragma once


namespace datetime
{


   namespace calendar
   {


      class CLASS_DECL_CA2_TIME graphics :
         virtual public ::datetime::calendar::visual
      {
      public:


         ::write_text::font_pointer     m_pfont;
         ::write_text::font_pointer     m_pfontYear;
         ::write_text::font_pointer     m_pfontMonth;
         ::write_text::font_pointer     m_pfontSpin;
 /*        int                        m_iColWidth;
         int                        m_iLineHeight;
         point_i32                      m_point;*/


         graphics();
         virtual ~graphics();


         virtual ::e_status initialize(::object * pobject) override;


         virtual void GetRectDay(::datetime::time& time, RECTANGLE_I32 * lprect);
         virtual void GetRectDay(int32_t iWeekDay, int32_t iLine, RECTANGLE_I32 * lprect);
         virtual void GetRect(RECTANGLE_I32 * lprect, enum enum_element eelement);

         void _001OnDraw(::draw2d::graphics* pgraphics);

         void set_pos(point_i32 pt, size_i32 sz);

         virtual enum_element hit_test(const ::point_i32& point);
         virtual bool hit_test(enum_element eelement, const ::point_i32& point);
         virtual bool time_hit_test(::datetime::time& time, const ::point_i32& point);

      };


   } // namespace calendar


} // namespace datetime



