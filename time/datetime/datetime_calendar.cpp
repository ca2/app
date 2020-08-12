#include "framework.h"
#include "aura/filesystem/file/html_file.h"


calendar::calendar(::object * pobject) :
   ::object(pobject),
   calendar_interface(pobject)
{
   ::datetime::time time = ::datetime::time::get_current_time();
   m_iYear = time.GetYear();
   m_iMonth = time.GetMonth();
}


void calendar::_001GetHtml(__pointer(::html::file) pfile)
{


   try
   {

      // pszSchema can be ignored if the object has only one implemented schema
      ::datetime::time timeNow = ::datetime::time::get_current_time();
      i32 iMonth = m_iMonth;
      i32 iYear = m_iYear;
   
      if (iYear > (timeNow.GetYear() + 100))
         return;

      i32 iWeekDay;

      ::datetime::time time(iYear, iMonth, 1, 0, 0, 0);
      ::datetime::time_span timespan(1, 0, 0, 0);
      ::datetime::time timeLastDayOfMonth((iMonth == 12) ? (iYear + 1) : iYear, (iMonth == 12) ? 1 : (iMonth + 1), 1, 0, 0, 0);
      timeLastDayOfMonth -= ::datetime::time_span(1, 0, 0, 0);
      i32 iFirstDayOfWeek = time.GetDayOfWeek();

      if(pfile->m_strOptions.find("<monday-first>")>=0 && iFirstDayOfWeek == 1)
      {
         iFirstDayOfWeek = 8;
      }

//      i32 iFirstWeek;
      i32 iLastDayOfWeek = timeLastDayOfMonth.GetDayOfWeek();
      i32 iLastDayPreviousMonth = (time - ::datetime::time_span(1, 0, 0, 0)).GetDay();
      ::rect rectDay;
      i32 iDay;
      pfile->raw_print("<table cellpadding=\"0\" cellspacing=\"0\">");
      if(pfile->m_strOptions.find("<no-week-bar-title>") < 0)
      {
         pfile->raw_print("<tr>");
         if(pfile->m_strOptions.find("<left-week-of-the-year>") >= 0)
         {
            pfile->raw_print("<td>");
            pfile->raw_print("V");
            pfile->raw_print("</td>");
         }
         for(iWeekDay = 1; iWeekDay <= 7; iWeekDay++)
         {
            i32 iDayOfWeek = iWeekDay;
            if(pfile->m_strOptions.find("<monday-first>")>=0)
            {
               iDayOfWeek++;
               if(iDayOfWeek > 7)
                  iDayOfWeek = 1;
            }
            pfile->raw_print("<td>");
            pfile->printf("%s", GetTinyWeekDay(pfile->str_context(), iDayOfWeek).c_str());
            pfile->raw_print("</td>");
         }
         pfile->raw_print("</tr>");
      }


      i32 iDayCount = timeLastDayOfMonth.GetDay();
      i32 iLineCount = (iDayCount + iFirstDayOfWeek - 1) / 7;
      if(((iDayCount + iFirstDayOfWeek - 1) % 7) > 0)
         iLineCount++;

      iDay = 1;
      for(i32 iWeek = 1; iWeek <= iLineCount; iWeek++)
      {
         pfile->raw_print("<tr>");
         if(pfile->m_strOptions.find("<left-week-of-the-year>") >= 0)
         {
            time_t w ;       if(pfile->m_strOptions.find("<monday-first>")>=0)
      {
         w = atoi(System.datetime().strftime("%V", (time_t)::datetime::time(iYear, iMonth, iDay, 0, 0, 0).get_time()));
      }
      else
      {
         w = atoi( ::datetime::time(iYear, iMonth, iDay, 0, 0, 0).Format("%U"));
      }

            pfile->raw_print("<td>");
            pfile->raw_print(__str((i64) w));
            pfile->raw_print("</td>");
         }
         for(i32 iWeekDay = 1; iWeekDay <=7; iWeekDay++)
         {
            i32 iDayOfWeek = iWeekDay;
            if(pfile->m_strOptions.find("<monday-first>")>=0)
            {
               iDayOfWeek++;
            }

            pfile->raw_print("<td>");

            if((!m_bRange &&
               iMonth == m_time.GetMonth()
               && iYear == m_time.GetYear( )
               && iDay == m_time.GetDay()) ||
               (m_bRange &&
               ::datetime::time(iYear, iMonth, iDay, 23, 59, 59) >= m_time
               && ::datetime::time(iYear, iMonth, iDay, 0, 0, 0) <= m_timeEnd))
            {
               pfile->raw_print("<div class=\""+ pfile->m_strStyle + "calendar-sel\">");
            }
            else if((iWeek == 1 && iDayOfWeek < iFirstDayOfWeek) ||
               (iWeek == iLineCount && iDayOfWeek > iLastDayOfWeek))
            {
               pfile->raw_print("<div class=\""+ pfile->m_strStyle + "calendar-out-of-month-day\">");
            }
            else if((timeNow.GetDay() == iDay &&
               timeNow.GetMonth() == iMonth &&
               timeNow.GetYear() == iYear)
               ||
               (iDay == m_time.GetDay() &&
               iMonth == m_time.GetMonth() &&
               iYear == m_time.GetYear()))
            {
               pfile->raw_print("<div class=\""+ pfile->m_strStyle + "calendar-today\">");
            }
            else
            {
               if(iDayOfWeek == 1 || iDayOfWeek == 8)
               {
                  pfile->raw_print("<div class=\""+ pfile->m_strStyle + "calendar-sunday\">");
               }
               else
               {
                  pfile->raw_print("<div class=\""+ pfile->m_strStyle + "calendar-day\">");
               }
            }
            if(iWeek == 1 && iDayOfWeek < iFirstDayOfWeek)
            {
               pfile->printf("%d", iLastDayPreviousMonth + iDayOfWeek - iFirstDayOfWeek + 1);
               iDay = 1;
            }
            else if(iWeek == iLineCount && iDayOfWeek > iLastDayOfWeek)
            {
               pfile->printf("%d", iDayOfWeek - iLastDayOfWeek);
            }
            else
            {
               pfile->printf("%d", iDay);
               iDay++;
            }
            pfile->raw_print("</div></td>");
         }
         pfile->raw_print("</tr>");
      }
      pfile->raw_print("</table>");
   }
   catch(...)
   {
      //-----\/----- implement diagnostic print for html file;
      pfile->dprint("error calendar::_001GetHtml");
      // worst case: mal-formed calendar display
   }

}


