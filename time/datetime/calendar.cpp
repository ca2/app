#include "framework.h"
#include "calendar.h"
#include "acme/platform/system.h"
#include "acme/primitive/datetime/datetime.h"
////#include "acme/primitive/primitive/object.h"


namespace datetime
{


   namespace calendar
   {



      calendar::calendar()
      {

         ::earth::time time = ::earth::time::now();
         m_iYear = time.year();
         m_iMonth = time.month();
         m_bRange = false;

      }


      calendar::~calendar()
      {


      }


      void calendar::initialize(::particle * pparticle)
      {

         //auto estatus = 
         
         ::particle::initialize(pparticle);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //return estatus;

      }


      void calendar::_001OnDraw(::draw2d::graphics* pgraphics)
      {

         UNREFERENCED_PARAMETER(pgraphics);

      }


      void calendar::GetRectDay(::earth::time& time, ::rectangle_i32 * lprect)
      {

         int32_t iWeekDay = time.day_of_week();
         int32_t iWeek = get_week_of_month(time);
         GetRectDay(iWeekDay, iWeek + 1, lprect);

      }


      void calendar::GetRectDay(int32_t iWeekDay, int32_t iLine, ::rectangle_i32 * lprect)
      {

         UNREFERENCED_PARAMETER(iWeekDay);
         UNREFERENCED_PARAMETER(iLine);
         UNREFERENCED_PARAMETER(lprect);

      }


      void calendar::GetRect(::rectangle_i32 * lprect, enum enum_element eelement)
      {

         UNREFERENCED_PARAMETER(lprect);
         UNREFERENCED_PARAMETER(eelement);

      }


      void calendar::set_time(const ::earth::time& time)
      {

         m_time = time;

      }


      void calendar::set_time_range(const ::earth::time& time, const ::earth::time& timeEnd)
      {

         m_time = time;
         m_timeEnd = timeEnd;
         m_bRange = true;

      }


      void calendar::set_time_end(const ::earth::time& timeEnd)
      {

         m_timeEnd = timeEnd;
         m_bRange = true;

      }


      void calendar::get_time(::earth::time& time)
      {

         time = m_time;

      }


      void calendar::set_pos(point_i32 point, size_i32 sz)
      {

         UNREFERENCED_PARAMETER(point);
         UNREFERENCED_PARAMETER(sz);

      }


      void calendar::GetDateTime(const ::text::context* pcontext, string& strDateTime)
      {

         ::earth::time time = ::earth::time::now();
         string strDate;
         string strWeekDay;
         string strTime;
         strDate.format(
            "%d de %s de %d",
            time.day(),
            GetMonth(pcontext, time.month()),
            time.year());
         strWeekDay = GetWeekDay(pcontext, time.day_of_week());
         strTime.format("%02d:%02d:%02d",
            time.hour(),
            time.minute(),
            time.second());
         strDateTime.format("%s %s, %s", strTime, strWeekDay, strDate);
      }


      string calendar::GetWeekDay(const ::text::context* pcontext, int32_t iWeekDay) // 1 - domingo
      {

         auto psystem = acmesystem();

         auto pdatetime = psystem->datetime();

         return pdatetime->get_week_day_str(pcontext, iWeekDay);

      }


      string calendar::GetTinyWeekDay(const ::text::context* pcontext, int32_t iWeekDay) // 1 - domingo
      {

         auto psystem = acmesystem();

         auto pdatetime = psystem->datetime();

         return pdatetime->get_tiny_week_day_str(pcontext, iWeekDay);

      }


      string calendar::GetMonth(const ::text::context* pcontext, int32_t iMonth)
      {

         auto psystem = acmesystem();

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


      bool calendar::time_hit_test(::earth::time& timeRet, const point_i32 & point)
      {
         int32_t iMonth = m_iMonth;
         int32_t iYear = m_iYear;
         ::earth::time time(iYear, iMonth, 1, 0, 0, 0);
         ::earth::time_span timespan(1, 0, 0, 0);
         rectangle_i32 rectangleDay;
         int32_t iDay;
         for (iDay = 1; iDay <= 33; iDay++)
         {
            GetRectDay(time, rectangleDay);
            if (rectangleDay.contains(point))
            {
               timeRet = time;
               return true;
            }
            time += timespan;
            if (time.month() != iMonth)
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


      int32_t calendar::get_week_of_month(::earth::time& time)
      {
         
         ::earth::time timeMonth(time.year(), time.month(), 1, 0, 0, 0);
         
         return (time.day() + timeMonth.day_of_week() - 2) / 7;

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



