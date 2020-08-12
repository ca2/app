#pragma once

class CLASS_DECL_CA2_TIME calendar_interface :
   virtual public ::object
{
public:

   enum EElement
   {
      ElementNull,
      ElementPreviousYear,
      ElementPreviousMonth,
      ElementNextMonth,
      ElementNextYear,
      ElementMonthTitle,
      ElementYearTitle,
   };


   i32      m_iMonth;
   i32      m_iYear;
   bool     m_bRange;
   ::datetime::time    m_time;
   ::datetime::time    m_timeEnd;


   calendar_interface(::object * pobject);


   virtual void GetRectDay(::datetime::time & time, LPRECT lprect);
   virtual void GetRectDay(i32 iWeekDay, i32 iLine, LPRECT lprect);
   virtual void GetRect(LPRECT lprect, enum EElement eelement);

   virtual void set_month(i32 iYear, i32 iMonth);
   virtual void set_time(const ::datetime::time & time);
   virtual void set_time_range(const ::datetime::time & time, const ::datetime::time & timeEnd);
   virtual void set_time_end(const ::datetime::time & timeEnd);
   virtual void get_time(::datetime::time & time);
   virtual i32 get_month();
   virtual i32 get_year();

   virtual i32 get_week_of_month(::datetime::time & time);

   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

   void set_pos(const ::point & point, size sz);

   virtual void GetDateTime(::aura::str_context * pcontext, string & strDateTime);

   virtual string GetTinyWeekDay(const ::aura::str_context * pcontext, i32 iWeekDay); // 1 - domingo
   virtual string GetWeekDay(const ::aura::str_context * pcontext, i32 iWeekDay); // 1 - domingo
   virtual string GetMonth(const ::aura::str_context * pcontext, i32 iMonth); // 1 - janeiro

   virtual void previous_month();
   virtual void next_month();
   virtual void next_year();
   virtual void previous_year();

   virtual EElement on_hit_test(::user::item & item);
   virtual bool hit_test(EElement eelement, const ::point & point);
   virtual bool time_hit_test(::datetime::time & time, const ::point & point);


};