#include "framework.h"


calendar_interface::calendar_interface(::object * pobject) :
   ::object(pobject)
{

   ::datetime::time time = ::datetime::time::get_current_time();
   m_iYear = time.GetYear();
   m_iMonth = time.GetMonth();
   m_bRange = false;

}


void calendar_interface::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{
   
   UNREFERENCED_PARAMETER(pgraphics);

}


void calendar_interface::GetRectDay(::datetime::time & time, LPRECT lprect)
{

   i32 iWeekDay = time.GetDayOfWeek();
   i32 iWeek = get_week_of_month(time);
   GetRectDay(iWeekDay, iWeek + 1, lprect);
}

void calendar_interface::GetRectDay(i32 iWeekDay, i32 iLine, LPRECT lprect)
{
   UNREFERENCED_PARAMETER(iWeekDay);
   UNREFERENCED_PARAMETER(iLine);
   UNREFERENCED_PARAMETER(lprect);
}

void calendar_interface::GetRect(LPRECT lprect, enum EElement eelement)
{
   UNREFERENCED_PARAMETER(lprect);
   UNREFERENCED_PARAMETER(eelement);
}


void calendar_interface::set_time(const ::datetime::time & time)
{
   m_time = time;
}

void calendar_interface::set_time_range(const ::datetime::time & time, const ::datetime::time & timeEnd)
{
   m_time = time;
   m_timeEnd = timeEnd;
   m_bRange = true;
}

void calendar_interface::set_time_end(const ::datetime::time & timeEnd)
{
   m_timeEnd = timeEnd;
   m_bRange = true;
}

void calendar_interface::get_time(::datetime::time & time)
{
   time = m_time;
}

void calendar_interface::set_pos(const ::point & point, size sz)
{
   UNREFERENCED_PARAMETER(point);
   UNREFERENCED_PARAMETER(sz);
}


void calendar_interface::GetDateTime(::aura::str_context * pcontext, string & strDateTime)
{
   ::datetime::time time = ::datetime::time::get_current_time();
   string strDate;
   string strWeekDay;
   string strTime;
   strDate.Format(
      "%d de %s de %d",
      time.GetDay(),
      GetMonth(pcontext, time.GetMonth()),
      time.GetYear());
   strWeekDay = GetWeekDay(pcontext, time.GetDayOfWeek());
   strTime.Format("%02d:%02d:%02d",
      time.GetHour(),
      time.GetMinute(),
      time.GetSecond());
   strDateTime.Format("%s %s, %s", strTime,  strWeekDay, strDate);
}


string calendar_interface::GetWeekDay(const ::aura::str_context * pcontext, i32 iWeekDay) // 1 - domingo
{
   return System.datetime().get_week_day_str(pcontext, iWeekDay);
}


string calendar_interface::GetTinyWeekDay(const ::aura::str_context * pcontext, i32 iWeekDay) // 1 - domingo
{
   return System.datetime().get_tiny_week_day_str(pcontext, iWeekDay);
}

string calendar_interface::GetMonth(const ::aura::str_context * pcontext, i32 iMonth)
{
   return System.datetime().get_month_str(pcontext, iMonth);
}


void calendar_interface::set_month(i32 iYear, i32 iMonth)
{
   m_iYear = iYear;
   m_iMonth = iMonth;
}


void calendar_interface::previous_month()
{
   if(m_iMonth <= 1)
   {
      m_iMonth = 12;
      m_iYear--;
   }
   else
   {
      m_iMonth--;
   }
}
void calendar_interface::next_month()
{
   if(m_iMonth >= 12)
   {
      m_iMonth = 1;
      m_iYear++;
   }
   else
   {
      m_iMonth++;
   }
}
void calendar_interface::next_year()
{
   m_iYear++;
}
void calendar_interface::previous_year()
{
   m_iYear--;
}


calendar_interface::EElement calendar_interface::on_hit_test(::user::item & item)
{
   if(hit_test(ElementNextMonth, item.m_pointHitTest))
      return ElementNextMonth;
   if(hit_test(ElementNextYear, item.m_pointHitTest))
      return ElementNextYear;
   if(hit_test(ElementPreviousMonth, item.m_pointHitTest))
      return ElementPreviousMonth;
   if(hit_test(ElementPreviousYear, item.m_pointHitTest))
      return ElementPreviousYear;
   return ElementNull;
}

bool calendar_interface::time_hit_test(::datetime::time & timeRet, const ::point & point)
{
   i32 iMonth = m_iMonth;
   i32 iYear = m_iYear;
   ::datetime::time time(iYear, iMonth, 1, 0, 0, 0);
   ::datetime::time_span timespan(1, 0, 0, 0);
   ::rect rectDay;
   i32 iDay;
   for(iDay = 1; iDay <= 33; iDay++)
   {
      GetRectDay(time, rectDay);
      if(rectDay.contains(point))
      {
         timeRet = time;
         return true;
      }
      time += timespan;
      if(time.GetMonth() != iMonth)
         break;
   }
   return false;
}

bool calendar_interface::hit_test(EElement eelement, const ::point & point)
{
   ::rect rect;
   GetRect(rect, eelement);
   return rect.contains(point) != FALSE;
}


i32 calendar_interface::get_week_of_month(::datetime::time & time)
{
   ::datetime::time timeMonth(time.GetYear(), time.GetMonth(), 1, 0, 0, 0);
   return (time.GetDay() + timeMonth.GetDayOfWeek() - 2) / 7;
}

i32 calendar_interface::get_month()
{
   return m_iMonth;
}

i32 calendar_interface::get_year()
{
   return m_iYear;
}
