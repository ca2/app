#include "framework.h"


calendar_interface::calendar_interface(::aura::application * papp) :
   ::object(papp)
{

   ::datetime::time time = ::datetime::time::get_current_time();
   m_iYear = time.GetYear();
   m_iMonth = time.GetMonth();
   m_bRange = false;

}


void calendar_interface::_001OnDraw(::draw2d::graphics * pgraphics)
{
   
   UNREFERENCED_PARAMETER(pgraphics);

}


void calendar_interface::GetRectDay(::datetime::time & time, LPRECT lprect)
{

   int32_t iWeekDay = time.GetDayOfWeek();
   int32_t iWeek = get_week_of_month(time);
   GetRectDay(iWeekDay, iWeek + 1, lprect);
}

void calendar_interface::GetRectDay(int32_t iWeekDay, int32_t iLine, LPRECT lprect)
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

void calendar_interface::set_pos(point pt, size sz)
{
   UNREFERENCED_PARAMETER(pt);
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


string calendar_interface::GetWeekDay(::aura::str_context * pcontext, int32_t iWeekDay) // 1 - domingo
{
   return System.datetime().get_week_day_str(pcontext, iWeekDay);
}


string calendar_interface::GetTinyWeekDay(::aura::str_context * pcontext, int32_t iWeekDay) // 1 - domingo
{
   return System.datetime().get_tiny_week_day_str(pcontext, iWeekDay);
}

string calendar_interface::GetMonth(::aura::str_context * pcontext, int32_t iMonth)
{
   return System.datetime().get_month_str(pcontext, iMonth);
}


void calendar_interface::set_month(int32_t iYear, int32_t iMonth)
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


calendar_interface::EElement calendar_interface::hit_test(point pt)
{
   if(hit_test(ElementNextMonth, pt))
      return ElementNextMonth;
   if(hit_test(ElementNextYear, pt))
      return ElementNextYear;
   if(hit_test(ElementPreviousMonth, pt))
      return ElementPreviousMonth;
   if(hit_test(ElementPreviousYear, pt))
      return ElementPreviousYear;
   return ElementNull;
}

bool calendar_interface::time_hit_test(::datetime::time & timeRet, point pt)
{
   int32_t iMonth = m_iMonth;
   int32_t iYear = m_iYear;
   ::datetime::time time(iYear, iMonth, 1, 0, 0, 0);
   ::datetime::time_span timespan(1, 0, 0, 0);
   rect rectDay;
   int32_t iDay;
   for(iDay = 1; iDay <= 33; iDay++)
   {
      GetRectDay(time, rectDay);
      if(rectDay.contains(pt))
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

bool calendar_interface::hit_test(EElement eelement, point pt)
{
   class rect rect;
   GetRect(rect, eelement);
   return rect.contains(pt) != FALSE;
}


int32_t calendar_interface::get_week_of_month(::datetime::time & time)
{
   ::datetime::time timeMonth(time.GetYear(), time.GetMonth(), 1, 0, 0, 0);
   return (time.GetDay() + timeMonth.GetDayOfWeek() - 2) / 7;
}

int32_t calendar_interface::get_month()
{
   return m_iMonth;
}

int32_t calendar_interface::get_year()
{
   return m_iYear;
}
