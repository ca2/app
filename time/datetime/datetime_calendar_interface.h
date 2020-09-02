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


   int32_t      m_iMonth;
   int32_t      m_iYear;
   bool     m_bRange;
   ::datetime::time    m_time;
   ::datetime::time    m_timeEnd;


   calendar_interface(::aura::application * papp);


   virtual void GetRectDay(::datetime::time & time, LPRECT lprect);
   virtual void GetRectDay(int32_t iWeekDay, int32_t iLine, LPRECT lprect);
   virtual void GetRect(LPRECT lprect, enum EElement eelement);

   virtual void set_month(int32_t iYear, int32_t iMonth);
   virtual void set_time(const ::datetime::time & time);
   virtual void set_time_range(const ::datetime::time & time, const ::datetime::time & timeEnd);
   virtual void set_time_end(const ::datetime::time & timeEnd);
   virtual void get_time(::datetime::time & time);
   virtual int32_t get_month();
   virtual int32_t get_year();

   virtual int32_t get_week_of_month(::datetime::time & time);

   virtual void _001OnDraw(::draw2d::graphics * pgraphics);

   void set_pos(point pt, size sz);

   virtual void GetDateTime(::aura::str_context * pcontext, string & strDateTime);

   virtual string GetTinyWeekDay(::aura::str_context * pcontext, int32_t iWeekDay); // 1 - domingo
   virtual string GetWeekDay(::aura::str_context * pcontext, int32_t iWeekDay); // 1 - domingo
   virtual string GetMonth(::aura::str_context * pcontext, int32_t iMonth); // 1 - janeiro

   virtual void previous_month();
   virtual void next_month();
   virtual void next_year();
   virtual void previous_year();

   virtual EElement hit_test(point pt);
   virtual bool hit_test(EElement eelement, point pt);
   virtual bool time_hit_test(::datetime::time & time, point pt);


};