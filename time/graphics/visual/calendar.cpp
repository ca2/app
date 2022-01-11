#include "framework.h"
#include "acme/primitive/mathematics/mathematics.h"
#include "aura/graphics/draw2d/graphics.h"


namespace datetime
{


   namespace calendar
   {


      graphics::graphics()
      {

      }



      graphics::~graphics()
      {

      }


      ::e_status graphics::initialize(::object * pobject)
      {

         return ::success;

      }


      void graphics::_001OnDraw(::draw2d::graphics * pgraphics)
      {

         pgraphics->set(m_pfont);

         ::datetime::time timeNow = ::datetime::time::now();
         int32_t iMonth = m_iMonth;
         int32_t iYear = m_iYear;
         ::datetime::time time(iYear,iMonth,1,0,0,0);
         ::datetime::time_span timespan(1,0,0,0);
         color32_t crBorder;
         rectangle_i32 rectangleDay;
         int32_t iDay;
         for(iDay = 1; iDay <= 7; iDay++)
         {
            GetRectDay(iDay,0,rectangleDay);
            //crBorder = rgb(184, 184, 177);
            //pgraphics->Draw3dRect(rectangleDay, crBorder, crBorder);
            rectangleDay.deflate(m_iColWidth / 10,m_iLineHeight / 10);
            string strDay;
            strDay.format("%s",GetTinyWeekDay(pgraphics->textcontext(),iDay));
            pgraphics->draw_text(strDay,rectangleDay,e_align_bottom_right);
         }
         for(iDay = 1; iDay <= 33; iDay++)
         {
            if((timeNow.day() == iDay &&
                  timeNow.month() == iMonth &&
                  timeNow.year() == iYear)
                  ||
                  (iDay == m_time.day() &&
                   iMonth == m_time.month() &&
                   iYear == m_time.year()))
            {
               time += timespan;
               if(time.month() != iMonth)
                  break;
               continue;
            }
            GetRectDay(time,rectangleDay);
            crBorder = rgb(189,189,177);
            pgraphics->draw_inset_rectangle(rectangleDay,crBorder);
            rectangleDay.deflate(m_iColWidth / 5,m_iLineHeight / 5);
            string strDay;
            strDay.format("%d",iDay);
            pgraphics->draw_text(strDay,rectangleDay,e_align_bottom_right);
            time += timespan;
            if(time.month() != iMonth)
               break;
         }
         if(timeNow.month() == iMonth
               && timeNow.year() == iYear)
         {
            crBorder = rgb(90, 90, 80);
            GetRectDay(timeNow,rectangleDay);
            rectangleDay.inflate(m_iColWidth / 10,m_iColWidth / 10);
            pgraphics->fill_rectangle(rectangleDay,rgb(220,220,210));
            pgraphics->draw_inset_rectangle(rectangleDay,crBorder);
            rectangleDay.deflate(1,1);
            pgraphics->draw_inset_rectangle(rectangleDay,crBorder);
            rectangleDay.deflate(m_iColWidth / 5,m_iLineHeight / 5);
            string strDay;
            strDay.format("%d",timeNow.day());
            pgraphics->draw_text(strDay,rectangleDay,e_align_bottom_right);
         }
         ::datetime::time timeEmp = m_time;
         for(int32_t iDay = timeEmp.day(); time.year() == iYear
               && time.month() == iMonth &&
               (m_time.day() == iDay || (
                m_bRange && time <= m_timeEnd)); time += timespan)
         {
            crBorder = rgb(240,120,52);
            GetRectDay(m_time,rectangleDay);
            rectangleDay.inflate(m_iColWidth / 10,m_iColWidth / 10);
            pgraphics->draw_inset_rectangle(rectangleDay,crBorder);
            rectangleDay.deflate(1,1);
            pgraphics->draw_inset_rectangle(rectangleDay,crBorder);
            rectangleDay.deflate(m_iColWidth / 5,m_iLineHeight / 5);
            string strDay;
            strDay.format("%d",timeEmp.day());
            pgraphics->draw_text(strDay,rectangleDay,e_align_bottom_right);
         }

         pgraphics->set(m_pfontYear);
         ::rectangle_i32 rectangle;
         GetRect(rectangle,e_element_year_title);
         string strYear;
         strYear.format("%d",iYear);
         pgraphics->draw_text(strYear,rectangle,e_align_center);

         pgraphics->set(m_pfontMonth);
         GetRect(rectangle,e_element_month_title);
         string strMonth;
         strMonth = GetMonth(pgraphics->textcontext(),iMonth);
         pgraphics->draw_text(strMonth,rectangle,e_align_center);

         pgraphics->set(m_pfontSpin);
         GetRect(rectangle,e_element_previous_year);
         pgraphics->draw_text("<<",rectangle,e_align_center);
         GetRect(rectangle,e_element_next_year);
         pgraphics->draw_text(">>",rectangle,e_align_center);
         GetRect(rectangle,e_element_previous_month);
         pgraphics->draw_text("<",rectangle,e_align_center);
         GetRect(rectangle,e_element_next_month);
         pgraphics->draw_text(">",rectangle,e_align_center);
      }


      void graphics::GetRectDay(::datetime::time & time,RECTANGLE_I32 * lprect)
      {
         int32_t iWeekDay = time.day_of_week();
         ::datetime::time timeMonth(m_iYear,m_iMonth,1,0,0,0);
         int32_t iWeek = get_week_of_month(time);
         GetRectDay(iWeekDay,iWeek + 1,lprect);
      }

      void graphics::GetRectDay(int32_t iWeekDay,int32_t iLine,RECTANGLE_I32 * lprect)
      {
         lprect->left = m_point.x + m_iColWidth * (iWeekDay - 1);
         lprect->right = lprect->left + m_iColWidth + 1;
         lprect->top = m_point.y + m_iLineHeight * iLine;
         lprect->bottom = lprect->top + m_iLineHeight + 1;
      }

      void graphics::GetRect(RECTANGLE_I32 * lprect,enum enum_element eelement)
      {
         if(eelement == e_element_month_title)
         {
            lprect->left = m_point.x + m_iColWidth * 1;
            lprect->right = lprect->left + m_iColWidth * 2 + 1;
            lprect->top = m_point.y + m_iLineHeight * 7;
            lprect->bottom = lprect->top + m_iLineHeight + 1;
         }
         else
         {
            switch(eelement)
            {
            case e_element_previous_year:
               GetRectDay(5,7,lprect);
               return;
            case e_element_previous_month:
               GetRectDay(1,7,lprect);
               return;
            case e_element_next_month:
               GetRectDay(4,7,lprect);
               return;
            case e_element_next_year:
               GetRectDay(7,7,lprect);
               return;
            case e_element_year_title:
               GetRectDay(6,7,lprect);
               return;
            default:
               __throw(error_not_supported);
            }
         }
      }



      void graphics::set_pos(point_i32 pt,size_i32 sz)
      {
         m_point = pt;
         m_size = sz;
         m_iColWidth = m_size.cx / 7;
         m_iLineHeight = m_size.cy / 8;
      }




      enum_element graphics::hit_test(const ::point_i32 & point)
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


      bool graphics::time_hit_test(::datetime::time & timeRet,const point_i32 & point)
      {
         int32_t iMonth = m_iMonth;
         int32_t iYear = m_iYear;
         ::datetime::time time(iYear,iMonth,1,0,0,0);
         ::datetime::time_span timespan(1,0,0,0);
         rectangle_i32 rectangleDay;
         int32_t iDay;
         for(iDay = 1; iDay <= 33; iDay++)
         {
            GetRectDay(time,rectangleDay);
            if(rectangleDay.contains(point))
            {
               timeRet = time;
               return true;
            }
            time += timespan;
            if(time.month() != iMonth)
               break;
         }
         return false;
      }

      bool graphics::hit_test(enum_element eelement, const point_i32 & pt)
      {

         ::rectangle_i32 rectangle;
         GetRect(rectangle,eelement);
         return rectangle.contains(pt) != false;

      }



   } // namespace calendar


} // namespace datetime



