#include "framework.h"


namespace visual
{


   calendar::calendar(::object * pobject):
      ::object(pobject),
      calendar_interface(pobject),
      ::calendar(pobject),
      m_font(e_create),
      m_fontYear(e_create),
      m_fontMonth(e_create),
      m_fontSpin(e_create)
   {

   }


   void calendar::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {



      pgraphics->SelectObject(m_font);
      ::datetime::time timeNow = ::datetime::time::get_current_time();
      i32 iMonth = m_iMonth;
      i32 iYear = m_iYear;
      ::datetime::time time(iYear,iMonth,1,0,0,0);
      ::datetime::time_span timespan(1,0,0,0);
      COLORREF crBorder;
      ::rect rectDay;
      i32 iDay;
      for(iDay = 1; iDay <= 7; iDay++)
      {
         GetRectDay(iDay,0,rectDay);
         //crBorder = RGB(184, 184, 177);
         //pgraphics->Draw3dRect(rectDay, crBorder, crBorder);
         rectDay.deflate(m_iColWidth / 10,m_iLineHeight / 10);
         string strDay;
         strDay.Format("%s",GetTinyWeekDay(pgraphics->str_context(),iDay));
         pgraphics->draw_text(strDay,rectDay,DT_BOTTOM | DT_RIGHT);
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
         pgraphics->draw3d_rect(rectDay,crBorder,crBorder);
         rectDay.deflate(m_iColWidth / 5,m_iLineHeight / 5);
         string strDay;
         strDay.Format("%d",iDay);
         pgraphics->draw_text(strDay,rectDay,DT_BOTTOM | DT_RIGHT);
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
         pgraphics->fill_solid_rect(rectDay,RGB(220,220,210));
         pgraphics->draw3d_rect(rectDay,crBorder);
         rectDay.deflate(1,1);
         pgraphics->draw3d_rect(rectDay,crBorder);
         rectDay.deflate(m_iColWidth / 5,m_iLineHeight / 5);
         string strDay;
         strDay.Format("%d",timeNow.GetDay());
         pgraphics->draw_text(strDay,rectDay,DT_BOTTOM | DT_RIGHT);
      }
      ::datetime::time timeEmp = m_time;
      for(i32 iDay = timeEmp.GetDay(); time.GetYear() == iYear
            && time.GetMonth() == iMonth &&
            (m_time.GetDay() == iDay || (
             m_bRange && time <= m_timeEnd)); time += timespan)
      {
         crBorder = RGB(240,120,52);
         GetRectDay(m_time,rectDay);
         rectDay.inflate(m_iColWidth / 10,m_iColWidth / 10);
         pgraphics->draw3d_rect(rectDay,crBorder);
         rectDay.deflate(1,1);
         pgraphics->draw3d_rect(rectDay,crBorder);
         rectDay.deflate(m_iColWidth / 5,m_iLineHeight / 5);
         string strDay;
         strDay.Format("%d",timeEmp.GetDay());
         pgraphics->draw_text(strDay,rectDay,DT_BOTTOM | DT_RIGHT);
      }

      pgraphics->SelectObject(m_fontYear);
      ::rect rect;
      GetRect(rect,ElementYearTitle);
      string strYear;
      strYear.Format("%d",iYear);
      pgraphics->draw_text(strYear,rect,DT_CENTER | DT_VCENTER);

      pgraphics->SelectObject(m_fontMonth);
      GetRect(rect,ElementMonthTitle);
      string strMonth;
      strMonth = GetMonth(pgraphics->str_context(),iMonth);
      pgraphics->draw_text(strMonth,rect,DT_CENTER | DT_VCENTER);

      pgraphics->SelectObject(m_fontSpin);
      GetRect(rect,ElementPreviousYear);
      pgraphics->draw_text("<<",rect,DT_CENTER | DT_VCENTER);
      GetRect(rect,ElementNextYear);
      pgraphics->draw_text(">>",rect,DT_CENTER | DT_VCENTER);
      GetRect(rect,ElementPreviousMonth);
      pgraphics->draw_text("<",rect,DT_CENTER | DT_VCENTER);
      GetRect(rect,ElementNextMonth);
      pgraphics->draw_text(">",rect,DT_CENTER | DT_VCENTER);
   }


   void calendar::GetRectDay(::datetime::time & time,LPRECT lprect)
   {
      i32 iWeekDay = time.GetDayOfWeek();
      ::datetime::time timeMonth(m_iYear,m_iMonth,1,0,0,0);
      i32 iWeek = get_week_of_month(time);
      GetRectDay(iWeekDay,iWeek + 1,lprect);
   }

   void calendar::GetRectDay(i32 iWeekDay,i32 iLine,LPRECT lprect)
   {
      lprect->left = m_point.x + m_iColWidth * (iWeekDay - 1);
      lprect->right = lprect->left + m_iColWidth + 1;
      lprect->top = m_point.y + m_iLineHeight * iLine;
      lprect->bottom = lprect->top + m_iLineHeight + 1;
   }

   void calendar::GetRect(LPRECT lprect,enum EElement eelement)
   {
      if(eelement == ElementMonthTitle)
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
         case ElementPreviousYear:
            GetRectDay(5,7,lprect);
            return;
         case ElementPreviousMonth:
            GetRectDay(1,7,lprect);
            return;
         case ElementNextMonth:
            GetRectDay(4,7,lprect);
            return;
         case ElementNextYear:
            GetRectDay(7,7,lprect);
            return;
         case ElementYearTitle:
            GetRectDay(6,7,lprect);
            return;
         default:
            __throw(not_supported_exception());
         }
      }
   }



   void calendar::set_pos(const ::point & point,size sz)
   {
      m_point = point;
      m_size = sz;
      m_iColWidth = m_size.cx / 7;
      m_iLineHeight = m_size.cy / 8;
   }




   calendar::EElement calendar::on_hit_test(::user::item & item)
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

   bool calendar::time_hit_test(::datetime::time & timeRet, const ::point & point)
   {
      i32 iMonth = m_iMonth;
      i32 iYear = m_iYear;
      ::datetime::time time(iYear,iMonth,1,0,0,0);
      ::datetime::time_span timespan(1,0,0,0);
      ::rect rectDay;
      i32 iDay;
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

   bool calendar::hit_test(EElement eelement, const ::point & point)
   {

      ::rect rect;
      GetRect(rect,eelement);
      return rect.contains(point) != FALSE;

   }


} // namespace visual



