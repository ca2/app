#include "framework.h"



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


      ::estatus graphics::initialize(::layered * pobjectContext)
      {

         return ::success;

      }


      void graphics::_001OnDraw(::draw2d::graphics * pgraphics)
      {

         pgraphics->set(m_pfont);

         ::datetime::time timeNow = ::datetime::time::get_current_time();
         int32_t iMonth = m_iMonth;
         int32_t iYear = m_iYear;
         ::datetime::time time(iYear,iMonth,1,0,0,0);
         ::datetime::time_span timespan(1,0,0,0);
         COLORREF crBorder;
         rect rectDay;
         int32_t iDay;
         for(iDay = 1; iDay <= 7; iDay++)
         {
            GetRectDay(iDay,0,rectDay);
            //crBorder = RGB(184, 184, 177);
            //pgraphics->Draw3dRect(rectDay, crBorder, crBorder);
            rectDay.deflate(m_iColWidth / 10,m_iLineHeight / 10);
            string strDay;
            strDay.Format("%s",GetTinyWeekDay(pgraphics->str_context(),iDay));
            pgraphics->draw_text(strDay,rectDay,e_align_bottom_right);
         }
         for(iDay = 1; iDay <= 33; iDay++)
         {
            if((timeNow.GetDay() == iDay &&
                  timeNow.GetMonth() == iMonth &&
                  timeNow.GetYear() == iYear)
                  ||
                  (iDay == m_time.GetDay() &&
                   iMonth == m_time.GetMonth() &&
                   iYear == m_time.GetYear()))
            {
               time += timespan;
               if(time.GetMonth() != iMonth)
                  break;
               continue;
            }
            GetRectDay(time,rectDay);
            crBorder = RGB(184,184,177);
            pgraphics->draw_rect(rectDay,crBorder);
            rectDay.deflate(m_iColWidth / 5,m_iLineHeight / 5);
            string strDay;
            strDay.Format("%d",iDay);
            pgraphics->draw_text(strDay,rectDay,e_align_bottom_right);
            time += timespan;
            if(time.GetMonth() != iMonth)
               break;
         }
         if(timeNow.GetMonth() == iMonth
               && timeNow.GetYear() == iYear)
         {
            crBorder = RGB(90, 90, 80);
            GetRectDay(timeNow,rectDay);
            rectDay.inflate(m_iColWidth / 10,m_iColWidth / 10);
            pgraphics->fill_rect(rectDay,RGB(220,220,210));
            pgraphics->draw_rect(rectDay,crBorder);
            rectDay.deflate(1,1);
            pgraphics->draw_rect(rectDay,crBorder);
            rectDay.deflate(m_iColWidth / 5,m_iLineHeight / 5);
            string strDay;
            strDay.Format("%d",timeNow.GetDay());
            pgraphics->draw_text(strDay,rectDay,e_align_bottom_right);
         }
         ::datetime::time timeEmp = m_time;
         for(int32_t iDay = timeEmp.GetDay(); time.GetYear() == iYear
               && time.GetMonth() == iMonth &&
               (m_time.GetDay() == iDay || (
                m_bRange && time <= m_timeEnd)); time += timespan)
         {
            crBorder = RGB(240,120,52);
            GetRectDay(m_time,rectDay);
            rectDay.inflate(m_iColWidth / 10,m_iColWidth / 10);
            pgraphics->draw_rect(rectDay,crBorder);
            rectDay.deflate(1,1);
            pgraphics->draw_rect(rectDay,crBorder);
            rectDay.deflate(m_iColWidth / 5,m_iLineHeight / 5);
            string strDay;
            strDay.Format("%d",timeEmp.GetDay());
            pgraphics->draw_text(strDay,rectDay,e_align_bottom_right);
         }

         pgraphics->set(m_pfontYear);
         ::rect rect;
         GetRect(rect,e_element_year_title);
         string strYear;
         strYear.Format("%d",iYear);
         pgraphics->draw_text(strYear,rect,e_align_center);

         pgraphics->set(m_pfontMonth);
         GetRect(rect,e_element_month_title);
         string strMonth;
         strMonth = GetMonth(pgraphics->str_context(),iMonth);
         pgraphics->draw_text(strMonth,rect,e_align_center);

         pgraphics->set(m_pfontSpin);
         GetRect(rect,e_element_previous_year);
         pgraphics->draw_text("<<",rect,e_align_center);
         GetRect(rect,e_element_next_year);
         pgraphics->draw_text(">>",rect,e_align_center);
         GetRect(rect,e_element_previous_month);
         pgraphics->draw_text("<",rect,e_align_center);
         GetRect(rect,e_element_next_month);
         pgraphics->draw_text(">",rect,e_align_center);
      }


      void graphics::GetRectDay(::datetime::time & time,LPRECT lprect)
      {
         int32_t iWeekDay = time.GetDayOfWeek();
         ::datetime::time timeMonth(m_iYear,m_iMonth,1,0,0,0);
         int32_t iWeek = get_week_of_month(time);
         GetRectDay(iWeekDay,iWeek + 1,lprect);
      }

      void graphics::GetRectDay(int32_t iWeekDay,int32_t iLine,LPRECT lprect)
      {
         lprect->left = m_point.x + m_iColWidth * (iWeekDay - 1);
         lprect->right = lprect->left + m_iColWidth + 1;
         lprect->top = m_point.y + m_iLineHeight * iLine;
         lprect->bottom = lprect->top + m_iLineHeight + 1;
      }

      void graphics::GetRect(LPRECT lprect,enum enum_element eelement)
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
               __throw(not_supported_exception());
            }
         }
      }



      void graphics::set_pos(point pt,size sz)
      {
         m_point = pt;
         m_size = sz;
         m_iColWidth = m_size.cx / 7;
         m_iLineHeight = m_size.cy / 8;
      }




      enum_element graphics::hit_test(const ::point & point)
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


      bool graphics::time_hit_test(::datetime::time & timeRet,const point & point)
      {
         int32_t iMonth = m_iMonth;
         int32_t iYear = m_iYear;
         ::datetime::time time(iYear,iMonth,1,0,0,0);
         ::datetime::time_span timespan(1,0,0,0);
         rect rectDay;
         int32_t iDay;
         for(iDay = 1; iDay <= 33; iDay++)
         {
            GetRectDay(time,rectDay);
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

      bool graphics::hit_test(enum_element eelement, const point & pt)
      {

         ::rect rect;
         GetRect(rect,eelement);
         return rect.contains(pt) != FALSE;

      }



   } // namespace calendar


} // namespace datetime



