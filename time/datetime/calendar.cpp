#include "framework.h"


namespace datetime
{


   namespace calendar
   {



      calendar::calendar()
      {

         ::datetime::time time = ::datetime::time::get_current_time();
         m_iYear = time.GetYear();
         m_iMonth = time.GetMonth();
         m_bRange = false;

      }


      calendar::~calendar()
      {


      }


      ::e_status calendar::initialize(::object * pobject)
      {

         auto estatus = ::object::initialize(pobject);

         if (!estatus)
         {

            return estatus;

         }

         return estatus;

      }


      void calendar::_001OnDraw(::draw2d::graphics* pgraphics)
      {

         __UNREFERENCED_PARAMETER(pgraphics);

      }


      void calendar::GetRectDay(::datetime::time& time, RECTANGLE_I32 * lprect)
      {

         int32_t iWeekDay = time.GetDayOfWeek();
         int32_t iWeek = get_week_of_month(time);
         GetRectDay(iWeekDay, iWeek + 1, lprect);

      }


      void calendar::GetRectDay(int32_t iWeekDay, int32_t iLine, RECTANGLE_I32 * lprect)
      {

         __UNREFERENCED_PARAMETER(iWeekDay);
         __UNREFERENCED_PARAMETER(iLine);
         __UNREFERENCED_PARAMETER(lprect);

      }


      void calendar::GetRect(RECTANGLE_I32 * lprect, enum enum_element eelement)
      {

         __UNREFERENCED_PARAMETER(lprect);
         __UNREFERENCED_PARAMETER(eelement);

      }


      void calendar::set_time(const ::datetime::time& time)
      {

         m_time = time;

      }


      void calendar::set_time_range(const ::datetime::time& time, const ::datetime::time& timeEnd)
      {

         m_time = time;
         m_timeEnd = timeEnd;
         m_bRange = true;

      }


      void calendar::set_time_end(const ::datetime::time& timeEnd)
      {

         m_timeEnd = timeEnd;
         m_bRange = true;

      }


      void calendar::get_time(::datetime::time& time)
      {

         time = m_time;

      }


      void calendar::set_pos(point_i32 point, size_i32 sz)
      {

         __UNREFERENCED_PARAMETER(point);
         __UNREFERENCED_PARAMETER(sz);

      }


      void calendar::GetDateTime(const ::text::context* pcontext, string& strDateTime)
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
         strDateTime.Format("%s %s, %s", strTime, strWeekDay, strDate);
      }


      string calendar::GetWeekDay(const ::text::context* pcontext, int32_t iWeekDay) // 1 - domingo
      {

         auto psystem = m_psystem;

         auto pdatetime = psystem->datetime();

         return pdatetime->get_week_day_str(pcontext, iWeekDay);

      }


      string calendar::GetTinyWeekDay(const ::text::context* pcontext, int32_t iWeekDay) // 1 - domingo
      {

         auto psystem = m_psystem;

         auto pdatetime = psystem->datetime();

         return pdatetime->get_tiny_week_day_str(pcontext, iWeekDay);

      }


      string calendar::GetMonth(const ::text::context* pcontext, int32_t iMonth)
      {

         auto psystem = m_psystem;

         auto pdatetime = psystem->datetime();

         return pdatetime->get_month_str(pcontext, iMonth);

      }


      void calendar::set_month(int32_t iYear, int32_t iMonth)
      {

         m_iYear = iYear;
         m_iMonth = iMonth;

      }


      void calendar::previous_month()
      {

         if (m_iMonth <= 1)
         {
            m_iMonth = 12;
            m_iYear--;
         }
         else
         {
            m_iMonth--;
         }

      }


      void calendar::next_month()
      {

         if (m_iMonth >= 12)
         {
            m_iMonth = 1;
            m_iYear++;
         }
         else
         {
            m_iMonth++;
         }

      }


      void calendar::next_year()
      {

         m_iYear++;

      }


      void calendar::previous_year()
      {

         m_iYear--;

      }


      enum_element calendar::hit_test(const point_i32 & point)
      {

         for (int iElement = e_element_none + 1; iElement < e_element_count; iElement++)
         {

            if (hit_test((enum_element)iElement, point))
            {

               return (enum_element)iElement;

            }

         }

         return e_element_none;

      }


      bool calendar::time_hit_test(::datetime::time& timeRet, const point_i32 & point)
      {
         int32_t iMonth = m_iMonth;
         int32_t iYear = m_iYear;
         ::datetime::time time(iYear, iMonth, 1, 0, 0, 0);
         ::datetime::time_span timespan(1, 0, 0, 0);
         rectangle_i32 rectDay;
         int32_t iDay;
         for (iDay = 1; iDay <= 33; iDay++)
         {
            GetRectDay(time, rectDay);
            if (rectDay.contains(point))
            {
               timeRet = time;
               return true;
            }
            time += timespan;
            if (time.GetMonth() != iMonth)
               break;
         }
         return false;
      }


      bool calendar::hit_test(enum_element eelement, const point_i32 & point)
      {

         ::rectangle_i32 rectangle;

         GetRect(rectangle, eelement);

         return rectangle.contains(point) != false;

      }


      int32_t calendar::get_week_of_month(::datetime::time& time)
      {
         
         ::datetime::time timeMonth(time.GetYear(), time.GetMonth(), 1, 0, 0, 0);
         
         return (time.GetDay() + timeMonth.GetDayOfWeek() - 2) / 7;

      }


      int32_t calendar::get_month()
      {
         
         return m_iMonth;

      }


      int32_t calendar::get_year()
      {

         return m_iYear;

      }


   } // namespace calendar


} // namespace datetime



