#include "framework.h"
#include "calendar.h"
#include "acme/platform/system.h"
#include "acme/primitive/datetime/datetime.h"
#include "apex/filesystem/file/html_file.h"


namespace datetime
{


   namespace calendar
   {



   graphical::graphical()
   {

      ::earth::time time = ::earth::time::now();
      
      m_iYear = time.year();

      m_iMonth = time.month();

   }



   graphical::~graphical()
   {


   }



   void graphical::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::datetime::calendar::calendar::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void graphical::_001GetHtml(::html_file * pfile)
   {


      try
      {

         // pszSchema can be ignored if the object has only one implemented schema
         ::earth::time timeNow = ::earth::time::now();
         int32_t iMonth = m_iMonth;
         int32_t iYear = m_iYear;

         if (iYear > (timeNow.year() + 100))
            return;

         int32_t iWeekDay;

         ::earth::time time(iYear, iMonth, 1, 0, 0, 0);
         ::earth::time_span timespan(1, 0, 0, 0);
         ::earth::time timeLastDayOfMonth((iMonth == 12) ? (iYear + 1) : iYear, (iMonth == 12) ? 1 : (iMonth + 1), 1, 0, 0, 0);
         timeLastDayOfMonth -= ::earth::time_span(1, 0, 0, 0);
         int32_t iFirstDayOfWeek = time.day_of_week();

         if (pfile->m_strOptions.contains("<monday-first>")&& iFirstDayOfWeek == 1)
         {
            iFirstDayOfWeek = 8;
         }

         //      int32_t iFirstWeek;
         int32_t iLastDayOfWeek = timeLastDayOfMonth.day_of_week();
         int32_t iLastDayPreviousMonth = (time - ::earth::time_span(1, 0, 0, 0)).day();
         rectangle_i32 rectangleDay;
         int32_t iDay;
         pfile->raw_print("<table cellpadding=\"0\" cellspacing=\"0\">");
         if (!pfile->m_strOptions.contains("<no-week-bar-title>"))
         {
            pfile->raw_print("<tr>");
            if (pfile->m_strOptions.contains("<left-week-of-the-year>"))
            {
               pfile->raw_print("<td>");
               pfile->raw_print("V");
               pfile->raw_print("</td>");
            }
            for (iWeekDay = 1; iWeekDay <= 7; iWeekDay++)
            {
               int32_t iDayOfWeek = iWeekDay;
               if (pfile->m_strOptions.contains("<monday-first>"))
               {
                  iDayOfWeek++;
                  if (iDayOfWeek > 7)
                     iDayOfWeek = 1;
               }
               pfile->raw_print("<td>");
               pfile->printf("%s", GetTinyWeekDay(pfile->textcontext(), iDayOfWeek).c_str());
               pfile->raw_print("</td>");
            }
            pfile->raw_print("</tr>");
         }


         int32_t iDayCount = timeLastDayOfMonth.day();
         int32_t iLineCount = (iDayCount + iFirstDayOfWeek - 1) / 7;
         if (((iDayCount + iFirstDayOfWeek - 1) % 7) > 0)
            iLineCount++;

         auto psystem = acmesystem()->m_papexsystem;

         iDay = 1;
         for (int32_t iWeek = 1; iWeek <= iLineCount; iWeek++)
         {
            pfile->raw_print("<tr>");
            if (pfile->m_strOptions.contains("<left-week-of-the-year>"))
            {
               time_t w;   
               
               auto psystem = acmesystem();

               auto pdatetime = psystem->datetime();

               if (pfile->m_strOptions.contains("<monday-first>"))
               {
                  
                  w = atoi(pdatetime->format("%V",::earth::time(iYear, iMonth, iDay, 0, 0, 0)));

               }
               else
               {

                  w = atoi(pdatetime->format("%U", ::earth::time(iYear, iMonth, iDay, 0, 0, 0)));

               }

               pfile->raw_print("<td>");
               pfile->raw_print(as_string((int64_t)w));
               pfile->raw_print("</td>");
            }
            for (int32_t iWeekDay = 1; iWeekDay <= 7; iWeekDay++)
            {
               int32_t iDayOfWeek = iWeekDay;
               if (pfile->m_strOptions.contains("<monday-first>"))
               {
                  iDayOfWeek++;
               }

               pfile->raw_print("<td>");

               if ((!m_bRange &&
                  iMonth == m_time.month()
                  && iYear == m_time.year()
                  && iDay == m_time.day()) ||
                  (m_bRange &&
                     ::earth::time(iYear, iMonth, iDay, 23, 59, 59) >= m_time
                     && ::earth::time(iYear, iMonth, iDay, 0, 0, 0) <= m_timeEnd))
               {
                  pfile->raw_print("<div class=\"" + pfile->m_strStyle + "calendar-sel\">");
               }
               else if ((iWeek == 1 && iDayOfWeek < iFirstDayOfWeek) ||
                  (iWeek == iLineCount && iDayOfWeek > iLastDayOfWeek))
               {
                  pfile->raw_print("<div class=\"" + pfile->m_strStyle + "calendar-out-of-month-day\">");
               }
               else if ((timeNow.day() == iDay &&
                  timeNow.month() == iMonth &&
                  timeNow.year() == iYear)
                  ||
                  (iDay == m_time.day() &&
                     iMonth == m_time.month() &&
                     iYear == m_time.year()))
               {
                  pfile->raw_print("<div class=\"" + pfile->m_strStyle + "calendar-today\">");
               }
               else
               {
                  if (iDayOfWeek == 1 || iDayOfWeek == 8)
                  {
                     pfile->raw_print("<div class=\"" + pfile->m_strStyle + "calendar-sunday\">");
                  }
                  else
                  {
                     pfile->raw_print("<div class=\"" + pfile->m_strStyle + "calendar-day\">");
                  }
               }
               if (iWeek == 1 && iDayOfWeek < iFirstDayOfWeek)
               {
                  pfile->printf("%d", iLastDayPreviousMonth + iDayOfWeek - iFirstDayOfWeek + 1);
                  iDay = 1;
               }
               else if (iWeek == iLineCount && iDayOfWeek > iLastDayOfWeek)
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
      catch (...)
      {
         //-----\/----- implement diagnostic print for html file;
         pfile->dprint("error calendar::_001GetHtml");
         // worst case: mal-formed calendar display
      }

   }




   } // namespace calendar


} // namespace datetime



