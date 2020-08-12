#pragma once


namespace visual
{


   class CLASS_DECL_CA2_TIME calendar:
      virtual public ::calendar
   {
   public:


      ::draw2d::font_pointer    m_font;
      ::draw2d::font_pointer    m_fontYear;
      ::draw2d::font_pointer    m_fontMonth;
      ::draw2d::font_pointer    m_fontSpin;


      calendar(::object * pobject);


      virtual void GetRectDay(::datetime::time & time,LPRECT lprect);
      virtual void GetRectDay(i32 iWeekDay,i32 iLine,LPRECT lprect);
      virtual void GetRect(LPRECT lprect,enum EElement eelement);

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      void set_pos(const ::point & point,size sz);

      virtual EElement on_hit_test(::user::item & item);
      virtual bool hit_test(EElement eelement, const ::point & point);
      virtual bool time_hit_test(::datetime::time & time, const ::point & point);

   };




} // namespace draw2d



