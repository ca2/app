#include "framework.h"

clock_interface::clock_interface(::aura::application * papp) :
   ::object(papp)
{
}

void clock_interface::_001OnDraw(::draw2d::graphics * pgraphics)
{
   
   UNREFERENCED_PARAMETER(pgraphics);

}


void clock_interface::GetRect(LPRECT lprect, enum EElement eelement)
{
   UNREFERENCED_PARAMETER(lprect);
   UNREFERENCED_PARAMETER(eelement);
}


void clock_interface::set_time(const ::datetime::time & time)
{
   m_timespan = time - ::datetime::time::get_current_time();
}

void clock_interface::get_time(::datetime::time & time)
{
   time = ::datetime::time::get_current_time() + m_timespan;
}




void clock_interface::previous_minute()
{
   m_timespan -= ::datetime::time_span(0, 0, 1, 0);
}
void clock_interface::next_minute()
{
   m_timespan += ::datetime::time_span(0, 0, 1, 0);
}

void clock_interface::next_hour()
{
   m_timespan += ::datetime::time_span(0, 1, 0, 0);
}

void clock_interface::previous_hour()
{
   m_timespan -= ::datetime::time_span(0, 1, 0, 0);
}


clock_interface::EElement clock_interface::hit_test(point pt)
{
   if(hit_test(ElementNextMinute, pt))
      return ElementNextMinute;
   if(hit_test(ElementNextHour, pt))
      return ElementNextHour;
   if(hit_test(ElementPreviousMinute, pt))
      return ElementPreviousMinute;
   if(hit_test(ElementPreviousHour, pt))
      return ElementPreviousHour;
   return ElementNull;
}


bool clock_interface::hit_test(EElement eelement, point pt)
{
   class rect rect;
   GetRect(rect, eelement);
   return rect.contains(pt) != FALSE;
}
