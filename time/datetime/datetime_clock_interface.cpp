#include "framework.h"

clock_interface::clock_interface(::object * pobject) :
   ::object(pobject)
{
}

void clock_interface::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
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


clock_interface::EElement clock_interface::on_hit_test(::user::item & item)
{
   if(hit_test(ElementNextMinute, item.m_pointHitTest))
      return ElementNextMinute;
   if(hit_test(ElementNextHour, item.m_pointHitTest))
      return ElementNextHour;
   if(hit_test(ElementPreviousMinute, item.m_pointHitTest))
      return ElementPreviousMinute;
   if(hit_test(ElementPreviousHour, item.m_pointHitTest))
      return ElementPreviousHour;
   return ElementNull;
}


bool clock_interface::hit_test(EElement eelement, const ::point & point)
{
   ::rect rect;
   GetRect(rect, eelement);
   return rect.contains(point) != FALSE;
}
