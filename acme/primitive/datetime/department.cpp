#include "framework.h" // from "base/apex/.h"
#include <time.h>
#include "acme/primitive/datetime/_string.h"
//#ifdef ANDROID
//#include <sys/time.h>
//#endif



namespace datetime
{


   ::datetime::time department::from_local(const ::text::context* pcontext, const ::string & str)
   {

      int iPathCount;

      return ::datetime::time(strtotime(pcontext, str, 0, iPathCount));

   }


   ::datetime::time department::from_gmt(const ::text::context* pcontext, const string& str)
   {

      int iPathCount;

      return ::datetime::time(gmt_strtotime(pcontext, str, 0, iPathCount));

   }


   department::department()
   {

      defer_create_mutex();

   }


   ::e_status department::initialize(::object * pobject)
   {
    
      auto estatus = ::acme::department::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }
         
      estatus = __construct_new(m_pinternational);

      if (!estatus)
      {

         return estatus;

      }

      estatus = __construct_new(m_pstr);

      if (!estatus)
      {

         return estatus;

      }

      m_pstr->m_pdatetime = this;

      return estatus;

   }


   ::e_status department::international::initialize(::object * pobject)
   {

      auto estatus = ::object::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status department::str::initialize(::object * pobject)
   {

      auto estatus = ::object::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status department::destroy()
   {

      m_pinternational.release();

      m_pstr.release();

      ::acme::department::destroy();

      return ::success;

   }


   /*class department::international & department::international()
   {

      return *m_pinternational;

   }


   class department::str & department::str()
   {
      return *m_str;
   }*/

   i32 department::get_month_day_count(i32 year, i32 month)
   {
      switch (month)
      {
      case 1:
         return 31;
      case 2:
         if ((year % 4) == 0)
            return 29;
         else
            return 28;
      case 3:
         return 31;
      case 4:
         return 30;
      case 5:
         return 31;
      case 6:
         return 30;
      case 7:
         return 31;
      case 8:
         return 31;
      case 9:
         return 30;
      case 10:
         return 31;
      case 11:
         return 30;
      case 12:
         return 31;
      }
      return -1;
   }

   // 0 is Sunday
   i32 department::get_weekday(i32 year, i32 month, i32 day)
   {
      ::datetime::time time(year, month, day, 0, 0, 0);
      return atoi(Format("%w", time));
   }

   i64 department::get_timestamp(i32 year, i32 month, i32 day)
   {
      string strInternationalDate;
      strInternationalDate.Format("%d-%02d-%02d", year, month, day);
      i32 i;
      return strtotime(nullptr, strInternationalDate, 0, i);
   }

   
   i64 department::strtotime(const ::text::context * pcontext, const char * psz, i32 iPath, i32 & iPathCount)
   {

      if (::is_null(psz) || string(psz).trimmed().is_empty())
      {

         return 0;

      }

      ::datetime::time time;
      ::datetime::result val = strtotime(pcontext, psz, iPath, iPathCount, false);
      if (val.m_bSpan)
         time = time.get_current_time() + val.GetSpan();
      else
         time = val.get_time();
      return time.get_time();
   }

   i64 department::strtotime(const ::text::context * pcontext, const char * psz, time_t timeParam, i32 iPath, i32 & iPathCount)
   {

      if (::is_null(psz) || string(psz).trimmed().is_empty())
      {

         return 0;

      }

      __UNREFERENCED_PARAMETER(iPath);
      ::datetime::time time(timeParam);
      iPathCount = 1;
      ::datetime::result val = ::datetime::result(time) +
                              span_strtotime( pcontext, psz);
      return val.get_time().get_time();
   }

   i64 department::gmt_strtotime(const ::text::context * pcontext, const char * psz, i32 iPath, i32 & iPathCount)
   {

      if (::is_null(psz) || string(psz).trimmed().is_empty())
      {

         return 0;

      }

      ::datetime::time time;
      ::datetime::result val = strtotime(pcontext, psz, iPath, iPathCount, true);
      if (val.m_bSpan)
         time = time.get_current_time() + val.GetSpan();
      else
         time = val.get_time();
      return time.get_time();
   }


   department::international::international()
   {


   }


   void department::international::parse_str(const char * psz, property_set & set)
   {
      string src(psz);
      src.trim();
      string str;
      if (src.get_length() >= 4)
      {
         str = src.Mid(0, 4);
         str.trim_left('0');
         set["year"] = str;
      }
      else
      {
         set["year"] = 0;
      }
      if (src.get_length() >= 7)
      {
         str = src.Mid(5, 2);
         str.trim_left('0');
         set["month"] = str;
      }
      else
      {
         set["month"] = 0;
      }
      if (src.get_length() >= 10)
      {
         str = src.Mid(8, 2);
         str.trim_left('0');
         set["day"] = str;
      }
      else
      {
         set["day"] = 0;
      }
      if (src.get_length() >= 13)
      {
         str = src.Mid(11, 2);
         str.trim_left('0');
         set["hour"] = str;
      }
      else
      {
         set["hour"] = 0;
      }
      if (src.get_length() >= 16)
      {
         str = src.Mid(14, 2);
         str.trim_left('0');
         set["minute"] = str;
      }
      else
      {
         set["minute"] = 0;
      }
      if (src.get_length() >= 19)
      {
         str = src.Mid(17, 2);
         str.trim_left('0');
         set["second"] = str;
      }
      else
      {
         set["second"] = 0;
      }
   }


   string department::international::get_gmt_date_time(const ::datetime::time & time, string strFormat)
   {
      string str;
      str = FormatGmt(strFormat, time);
      return str;
   }

   string department::international::get_gmt_date_time(string strFormat)
   {
      ::datetime::time time;
      time = time.get_current_time();
      return get_gmt_date_time(time, strFormat);
   }


   string department::international::get_gmt_date_time_for_file()
   {

      return get_gmt_date_time(INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE);

   }


   string department::international::get_local_date_time(const ::datetime::time & time, string strFormat)
   {
      string str;
      str = Format(strFormat, time);
      return str;
   }

   string department::international::get_local_date_time(string strFormat)
   {
      ::datetime::time time;
      time = time.get_current_time();
      return get_local_date_time(time, strFormat);
   }


   string department::international::get_local_date_time_for_file()
   {

      return get_local_date_time(INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE);

   }


   string department::international::get_gmt_date_time_for_file_with_no_spaces()
   {

      string str = get_gmt_date_time_for_file();

      str.replace(" ", "_");

      return str;

   }


   string department::international::get_local_date_time_for_file_with_no_spaces()
   {

      string str = get_local_date_time_for_file();

      str.replace(" ", "_");

      return str;

   }


   department::str::str()
   {
      
      m_pdatetime = nullptr;

   }


   string department::str::get_gmt_date_time()
   {
      return m_pdatetime->international().get_gmt_date_time(::datetime::time::get_current_time());
   }


   time_t department::s_local_mktime(i32 iHour, i32 iMinute, i32 iSecond, i32 iMonth, i32 iDay, i32 iYear)
   {

      struct ::tm tm;

      __zero(tm);
      tm.tm_hour = iHour;
      tm.tm_min = iMinute;
      tm.tm_sec = iSecond;
      tm.tm_mon = iMonth - 1;
      tm.tm_mday = iDay;
      tm.tm_year = iYear - 1900;
#ifdef WINDOWS
      return _mktime64(&tm);
#else
      return ::mktime(&tm);
#endif
   }


   time_t department::s_gmt_mktime(i32 iHour, i32 iMinute, i32 iSecond, i32 iMonth, i32 iDay, i32 iYear)
   {

      struct ::tm tm;

      __zero(tm);
      tm.tm_hour = iHour;
      tm.tm_min = iMinute;
      tm.tm_sec = iSecond;
      tm.tm_mon = iMonth - 1;
      tm.tm_mday = iDay;
      tm.tm_year = iYear - 1900;

#ifdef WINDOWS

      return _mkgmtime64(&tm);

#else

      return ::timegm(&tm);

#endif

   }



   string department::get_week_day_str(const ::text::context * pcontext, i32 iWeekDay) // 1 - domingo
   {
      
      auto psystem = m_psystem;

      return psystem->texttable()->get(pcontext, "datetimestr_weekday_long[" + __string(iWeekDay - 1) + "]");

   }


   string department::get_tiny_week_day_str(const ::text::context * pcontext, i32 iWeekDay) // 1 - domingo
   {

      auto psystem = m_psystem;

      return psystem->texttable()->get(pcontext, "datetimestr_weekday_tiny[" + __string(iWeekDay - 1) + "]");

   }


   string department::get_month_str(const ::text::context * pcontext, i32 iMonth)
   {
   
      auto psystem = m_psystem;

      return psystem->texttable()->get(pcontext, "datetimestr_month[" + __string(iMonth - 1) + "]");

   }


   string department::get_short_month_str(const ::text::context * pcontext, i32 iMonth)
   {

      auto psystem = m_psystem;

      return psystem->texttable()->get(pcontext, "datetimestr_month_short[" + __string(iMonth - 1) + "]");

   }


   ::datetime::time department::from_gmt_date_time(i32 iYear, i32 iMonth, i32 iDay, i32 iHour, i32 iMinute, i32 iSecond)
   {

      ::datetime::time timeLocalNow = ::datetime::time::get_current_time();

      struct ::tm tmLocalNow;

      timeLocalNow.GetGmtTm(&tmLocalNow);

      ::datetime::time timeUTCNow(tmLocalNow.tm_year + 1900, tmLocalNow.tm_mon + 1, tmLocalNow.tm_mday, tmLocalNow.tm_hour, tmLocalNow.tm_min, tmLocalNow.tm_sec);

      ::datetime::time timeUTC(tmLocalNow.tm_year + 1900, tmLocalNow.tm_mon + 1, tmLocalNow.tm_mday, tmLocalNow.tm_hour, tmLocalNow.tm_min, tmLocalNow.tm_sec);

      return timeUTC + (timeUTCNow - timeLocalNow);

   }



   /*
   and ML ("Month Length") is defined as:

   ML( y, 1 ) = 31
   ML( y, 2 ) = 28 + LEAP( y )
   ML( y, 3 ) = 31
   ML( y, 4 ) = 30
   ML( y, 5 ) = 31
   ML( y, 6 ) = 30
   ML( y, 7 ) = 31
   ML( y, 8 ) = 31
   ML( y, 9 ) = 30
   ML( y, 10 ) = 31
   ML( y, 11 ) = 30
   ML( y, 12 ) = 31

   and LEAP( y ) is defined as:

   LEAP( y ) = ( y % 4 == 0 ) && ( ( y % 100 != 0 ) || ( y % 400 == 0 ) ) */

   // simple week number
   //The simple week number we define such that
   //    week 1 starts on January 1st of a given year,
   //    week n+1 starts 7 days after week n
   i32 department::SWN(i32 y, i32 m, i32 d)
   {
      return 1 + (DP(y, m) + d - 1) / 7;
   }

   //where DP ("Days Passed") is given by:
   //   DP( y, 1 ) = 0
   //  DP( y, m+1 ) = DP( y, m ) + ML( y, m )
   i32 department::DP(i32 y, i32 m)
   {
      if (m == 1)
         return 0;
      else
         return DP(y, m - 1) + ML(y, m - 1);
   }

   i32 department::ML(i32 y, i32 m)
   {
      switch (m)
      {
      case 1:
         return 31;
      case 2:
         return 28 + LEAP(y);
      case 3:
         return 31;
      case 4:
         return 30;
      case 5:
         return 31;
      case 6:
         return 30;
      case 7:
         return 31;
      case 8:
         return 31;
      case 9:
         return 30;
      case 10:
         return 31;
      case 11:
         return 30;
      case 12:
         return 30;
      }
      
      throw ::exception(error_invalid_argument);


   }

   i32 department::LEAP(i32 y)
   {
      if ((y % 4 == 0) && ((y % 100 != 0) || (y % 400 == 0)))
         return 1;
      else
         return 0;
   }


   // Use this elegant code by Tomohiko Sakamoto:

   i32 department::dayofweek(i32 y, i32 m, i32 d)	/* 0 = Sunday */
   {
      static i32 t[] = { 0,3,2,5,0,3,5,1,4,6,2,4 };
      y -= m < 3;
      return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
   }

   i32 department::SDOW(i32 y, i32 m, i32 d) // ( 0 = Monday, ..., 6 = Sunday )
   {
      return (DP(y, m) + d - 1) % 7;
   }


   i32 department::DOW(i32 y, i32 m, i32 d)
   {
      //return SDOW(y, m, d);
      return getDayOfWeek(m, d, y, 0);
   }


   i32 department::getDayOfWeek(i32 month, i32 day, i32 year, i32 CalendarSystem)
   {
      // CalendarSystem = 1 for Gregorian Calendar
      if (month < 3)
      {
         month = month + 12;
         year = year - 1;
      }
      return (
             day
             + (2 * month)
             + i32(6 * (month + 1) / 10)
             + year
             + i32(year / 4)
             - i32(year / 100)
             + i32(year / 400)
             + CalendarSystem
             ) % 7;
   }

   /*In [ISO8601], the week number is defined by:

   weeks start on a monday
   week 1 of a given year is the one that includes the first Thursday of that year. (or, equivalently, week 1 is the week that includes 4 January.)

   This means that the days before week 1 in a given year are attributed to the last week of the previous year. Also the days that come after the last week of a given year are attributed to the first week of the next year.

   If we adapt approximation SWN5 for the simple week number to reflect the differences between the definitions of both week numbers, we arrive at the final solution, adopted for the week number wristapp:
   */
   /*i32 ISO_WN(i32  y, i32 m, i32 d, i32 dow, i32 dow0101 )
   {
   dow     = DOW( y, m, d );
   dow0101 = DOW( y, 1, 1 );

   if      ( m == 1  &&  3 < dow0101 < 7 - (d-1) )
   {
   // days before week 1 of the current year have the same week number as
   // the last day of the last week of the previous year

   dow     = dow0101 - 1;
   dow0101 = DOW( y-1, 1, 1 );
   m       = 12;
   d       = 31;
   }
   else if ( m == 12  &&  30 - (d-1) < DOW( y+1, 1, 1 ) < 4 )
   {
   // days after the last week of the current year have the same week number as
   // the first day of the next year, (i.e. 1)

   return 1;
   }

   return  ( DOW( y, 1, 1 ) < 4 ) + 4 * (m-1) + ( 2 * (m-1) + (d-1) + dow0101 - dow + 6 ) * 36 / 256;

   }*/


   i32 department::ISO_WN(i32  y, i32 m, i32 d)
   {
      i32 dow = DOW(y, m, d);
      i32 dow0101 = DOW(y, 1, 1);

      if (m == 1 && 3 < dow0101 && dow0101 < (7 - (d - 1)))
      {
         // days before week 1 of the current year have the same week number as
         // the last day of the last week of the previous year

         dow = dow0101 - 1;
         dow0101 = DOW(y - 1, 1, 1);
         m = 12;
         d = 31;
      }
      else if (m == 12 && (30 - (d - 1)) < DOW(y + 1, 1, 1) && DOW(y + 1, 1, 1) < 4)
      {
         // days after the last week of the current year have the same week number as
         // the first day of the next year, (i.e. 1)

         return 1;
      }

      return (dow0101 < 4) + 4 * (m - 1) + (2 * (m - 1) + (d - 1) + dow0101 - dow + 6) * 36 / 256;

   }


   string department::strftime(const char * psz, time_t timeParam)
   {
      string strFormat(psz);
      string str;
      ::datetime::time time(timeParam);
      strsize iFind = strFormat.find("%V");
      if (iFind >= 0)
      {
         string strV;
         strV.Format("%02d", ISO_WN(time.GetYear(), time.GetMonth(), time.GetDay()));
         strFormat.replace("%V", strV);
      }
      str = FormatGmt(strFormat, time);
      return str;
   }

   string department::strftime(const char * psz)
   {
      string str;
      ::datetime::time time;
      time = ::datetime::time::get_current_time();
      str = FormatGmt(psz, time);
      return str;
   }

   string department::friend_time(const ::text::context * pcontext, ::datetime::time timeNow, ::datetime::time time)
   {
      bool bDiff = false;
      bool bSolved = false;
      string strTime;
      string str;
      i64 iSecDiff = (timeNow - time).GetTotalSeconds();
      i64 iMinDiff = (timeNow - time).GetTotalMinutes();
      i64 iHouDiff = (timeNow - time).GetTotalHours();
      if (iSecDiff <= 59)
      {
         bSolved = true;
         strTime.Format("about %d seconds ago", (timeNow - time).GetTotalSeconds());
      }
      else if (iMinDiff <= 59)
      {
         bSolved = true;
         if (iMinDiff <= 1)
         {
            strTime = pcontext->get("about 1 minute and %SECONDS% seconds ago");
            strTime.replace("%SECONDS%", __string((timeNow - time).GetSeconds()));
         }
         else if (iMinDiff <= 2)
         {
            strTime = pcontext->get("about 2 minutes and %SECONDS% seconds ago");
            strTime.replace("%SECONDS%", __string((timeNow - time).GetSeconds()));
         }
         else
         {
            strTime = pcontext->get("about %MINUTES% minutes ago");
            strTime.replace("%MINUTES%", __string(iMinDiff));
         }
      }
      else if (iHouDiff <= 24)
      {
         bSolved = true;
         if (iHouDiff <= 1)
         {
            strTime.Format("about 1 hour and %d minutes ago", (timeNow - time).GetMinutes());
         }
         else if (iHouDiff <= 2)
         {
            strTime.Format("about 2 hours and %d minutes ago", (timeNow - time).GetMinutes());
         }
         else
         {
            strTime = pcontext->get("about %HOURS% hours ago");
            strTime.replace("%HOURS%", __string(iHouDiff));
         }
      }
      else
      {
         if (!bSolved && timeNow.GetGmtYear() != time.GetGmtYear())
         {
            bDiff = true;
            str.Format("%04d", time.GetGmtYear());
            strTime = str;
         }
         if (!bSolved && (bDiff || timeNow.GetGmtMonth() != time.GetGmtMonth()))
         {
            str = get_month_str(pcontext, time.GetGmtMonth());
            if (bDiff)
            {
               strTime += "-";
            }
            else
            {
               bDiff = true;
            }
            strTime += str;
         }
         if (!bSolved && (bDiff || timeNow.GetGmtDay() != time.GetGmtDay()))
         {
            str.Format("%02d", time.GetGmtDay());
            if (bDiff)
            {
               strTime += "-";
            }
            else
            {
               bDiff = true;
            }
            strTime += str;
         }
         if (!bSolved && (bDiff || timeNow.GetGmtHour() != time.GetGmtHour()))
         {
            str.Format("%02d", time.GetGmtHour());
            if (bDiff)
            {
               strTime += " ";
            }
            else
            {
               bDiff = true;
            }
            strTime += str;
         }
         if (!bSolved && (bDiff || timeNow.GetGmtMinute() != time.GetGmtMinute()))
         {
            if (bDiff)
            {
               str.Format("%02d", time.GetGmtMinute());
               strTime += ":";
               strTime += str;
            }
            else
            {
               bSolved = true;
               bDiff = true;
            }
         }
         if (!bDiff || !bSolved)
         {
            if (bDiff)
            {
               str.Format("%02d", time.GetGmtSecond());
               strTime += ":" + str;
            }
            else
            {
            }
         }
      }
      return strTime;

   }









   string department::_001FriendTime(const ::text::context* pcontext, const ::datetime::time& timeNow, const ::datetime::time& time)
   {

      bool bDiff = false;
      bool bSolved = false;
      string strTime;
      string str;
      ::i64 iSecDiff = (timeNow - time).GetTotalSeconds();
      ::i64 iMinDiff = (timeNow - time).GetTotalMinutes();
      ::i64 iHouDiff = (timeNow - time).GetTotalHours();
      if (iSecDiff <= 59)
      {
         bSolved = true;
         //strTime.Format("about %d seconds ago", (timeNow - time).GetTotalSeconds());
         strTime.Format("%ds", (timeNow - time).GetTotalSeconds());
      }
      else if (iMinDiff <= 59)
      {
         bSolved = true;
         if (iMinDiff <= 1)
         {
            //strTime = pscript->pstr("about 1 minute and %SECONDS% seconds ago");
            //strTime = pscript->pstr("1m %SECONDS%s seconds ago");
            strTime.Format("1m %ds", (timeNow - time).GetSeconds());
         }
         else if (iMinDiff <= 2)
         {
            //strTime = pscript->pstr("about 2 minutes and %SECONDS% seconds ago");
            //strTime = pscript->pstr("2 minutes and %SECONDS% seconds ago");
            strTime.Format("2m %ds", (timeNow - time).GetSeconds());
         }
         else
         {
            //strTime = pscript->pstr("about %MINUTES% minutes ago");
            //strTime = pscript->pstr("%MINUTES% minutes ago");
            strTime.Format("%dm", iMinDiff);
         }
      }
      else if (iHouDiff <= 24)
      {
         bSolved = true;
         if (iHouDiff <= 1)
         {
            //strTime.Format("about 1 hour and %d minutes ago", (timeNow - time).GetMinutes());
            strTime.Format("1h %dm", (timeNow - time).GetMinutes());

         }
         else if (iHouDiff <= 2)
         {
            //strTime.Format("about 2 hours and %d minutes ago", (timeNow - time).GetMinutes());
            strTime.Format("2h %dm", (timeNow - time).GetMinutes());
         }
         else
         {
            //strTime = pscript->pstr("about %HOURS% hours ago");
            //strTime = pscript->pstr("%HOURS% hours ago");
            strTime.Format("%dh", iHouDiff);
         }
      }
      else
      {
         if (!bSolved && timeNow.GetGmtYear() != time.GetGmtYear())
         {
            bDiff = true;
            str.Format("%04d", time.GetGmtYear());
            strTime = str;
         }
         if (!bSolved && (bDiff || timeNow.GetGmtMonth() != time.GetGmtMonth()))
         {
            str = get_month_str(pcontext, time.GetGmtMonth());
            if (bDiff)
            {
               strTime += "-";
            }
            else
            {
               bDiff = true;
            }
            strTime += str;
         }
         if (!bSolved && (bDiff || iHouDiff >= 24))
         {
            if (iHouDiff >= 24 && iHouDiff < 48)
            {
               str = "Yesterday";
            }
            else if (iHouDiff >= 48 && iHouDiff < 24 * 6)
            {

               string_array straWeekDay;

               straWeekDay.add("Sun");
               straWeekDay.add("Mon");
               straWeekDay.add("Tue");
               straWeekDay.add("Wed");
               straWeekDay.add("Thu");
               straWeekDay.add("Fri");
               straWeekDay.add("Sat");

               //str = Sys(pscript->get_application()).datetime().get_tiny_week_day_str(pscript->textcontext(), time.GetGmtDayOfWeek());
               str = straWeekDay[time.GetGmtDayOfWeek() % 7];

            }
            else
            {
               str.Format("%dd, time.GetGmtDay()");

            }
            if (bDiff)
            {
               strTime += "-";
            }
            else
            {
               bDiff = true;
            }
            strTime += str;
         }
         if (!bSolved && (bDiff || timeNow.GetGmtHour() != time.GetGmtHour()))
         {
            str.Format("%02d", time.GetGmtHour());
            if (bDiff)
            {
               strTime += "&nbsp;";
            }
            else
            {
               bDiff = true;
            }
            strTime += str;
         }
         if (!bSolved && (bDiff || timeNow.GetGmtMinute() != time.GetGmtMinute()))
         {
            if (bDiff)
            {
               str.Format("%02d", time.GetGmtMinute());
               strTime += ":";
               strTime += str;
            }
            else
            {
               bSolved = true;
               bDiff = true;
            }
         }
         if (!bDiff || !bSolved)
         {
            if (bDiff)
            {
               str.Format("%02d", time.GetGmtSecond());
               strTime += ":" + str;
            }
            else
            {
            }
         }
      }
      return strTime;
   }



} // namespace datetime





//
//CLASS_DECL_ACME stream & operator >> (stream & s, string_map < class ::datetime::department::time_zone > & m)
//{
//
//   s.stream_map(m);
//
//   return s;
//
//}
//
//
//CLASS_DECL_ACME stream & operator << (stream & s, string_map < class ::datetime::department::time_zone > & m)
//{
//
//   s.stream_map(m);
//
//   return s;
//
//}
//
//
//CLASS_DECL_ACME stream & operator >> (stream & s, int_ptr_map < class ::datetime::department::time_zone > & m)
//{
//
//   s.stream_map(m);
//
//   return s;
//
//}
//
//
//CLASS_DECL_ACME stream &operator << (stream & s, int_ptr_map < class ::datetime::department::time_zone > & m)
//{
//
//   s.stream_map(m);
//
//   return s;
//
//}
//




#include "framework.h"
#include <time.h>

#ifndef WINDOWS

#include <sys/time.h>

#endif



namespace datetime
{


   result department::span_strtotime(const ::text::context* pcontext, const char* pszSpanExpression)
   {

      static id idCalendarDay("calendar:day");
      static id idCalendarDays("calendar:days");
      static id idCalendarWeek("calendar:week");
      static id idCalendarWeeks("calendar:weeks");
      static id idCalendarYear("calendar:year");
      static id idCalendarYears("calendar:years");
      static id idCalendarHour("calendar:hour");
      static id idCalendarHours("calendar:hours");
      static id idCalendarNow("calendar:now");

      result time;
      time.m_bSpan = true;
      string str(pszSpanExpression);
      str.trim();
      str += " ";
      property_set set;
      bool bAdd = false;
      bool bMinus = false;
      const char* psz = str;
      string strNumber;
      string strText1;
      for (i32 i = 0; *psz; psz = ::str::utf8_inc(psz))
      {
         string strChar = ::str::get_utf8_char(psz);
         if (::str::ch::is_whitespace(psz))
         {
            i++;
            //if(strNumber.has_char() && strText.has_char())
            //{
            //}
            if ((bAdd || bMinus) && strNumber.has_char() && strText1.has_char())
            {
               result span;
               span.m_bSpan = true;
               if (strText1 == "day" || strText1 == "days" || strText1 == "dia" || strText1 == "dias"
                  || (pcontext != nullptr && pcontext->matches(idCalendarDay, strText1))
                  || (pcontext != nullptr && pcontext->matches(idCalendarDays, strText1)))
               {
                  span.m_iDay = atoi(strNumber);
               }
               else if (strText1 == "week" || strText1 == "weeks"
                  || (pcontext != nullptr && pcontext->matches(idCalendarWeek, strText1))
                  || (pcontext != nullptr && pcontext->matches(idCalendarWeeks, strText1)))
               {
                  span.m_iDay = atoi(strNumber) * 7;
               }
               else if (strText1 == "hour" || strText1 == "hours" || strText1 == "hora" || strText1 == "horas"
                  || (pcontext != nullptr && pcontext->matches(idCalendarHour, strText1))
                  || (pcontext != nullptr && pcontext->matches(idCalendarHour, strText1)))
               {
                  span.m_iHour = atoi(strNumber);
               }
               else if (strText1 == "year" || strText1 == "years"
                  || (pcontext != nullptr && pcontext->matches(idCalendarYear, strText1))
                  || (pcontext != nullptr && pcontext->matches(idCalendarYears, strText1)))
               {
                  span.m_iYear = atoi(strNumber);
               }
               else if (strText1 == "now"
                  || (pcontext != nullptr && pcontext->matches(idCalendarNow, strText1)))
               {
                  
                  __throw(error_invalid_argument, "now cannot be span");

               }
               else if (strText1.compare_ci("UTC") == 0)
               {

               }
               else
               {
                  __throw(error_not_implemented);
               }
               strNumber.Empty();
               strText1.Empty();
               if (bAdd)
               {
                  time = time + span;
                  bAdd = false;
               }
               else
               {
                  time = time - span;
                  bMinus = false;
               }
            }
            continue;
         }
         else if (strChar == "+")
         {

#ifdef __DEBUG

            if (bAdd)
            {
               info() << "strtotime: invalid char +";
            }
            else if (bMinus)
            {
               info() << "strtotime: invalid char + on Minus state";
            }

#endif

            bAdd = true;
            bMinus = false;
            strNumber.Empty();
         }
         else if (strChar == "-")
         {

#ifdef __DEBUG

            if (bAdd)
            {
               
               info() << "strtotime: invalid char - on add state";

            }
            else if (bMinus)
            {
               
               info() << "strtotime: invalid char - on Minus state";

            }

#endif

            bAdd = false;
            bMinus = true;
            strNumber.Empty();
         }
         else if (::str::ch::is_digit(psz))
         {
            strNumber += strChar;
         }
         else if (::str::ch::is_letter(psz))
         {
            strText1 += strChar;
         }
      }
      return time;
   }
   void parse_br_str(const char* psz, property_set& set)
   {
      string src(psz);
      src.trim();
      string str;
      if (src.get_length() >= 2)
      {
         str = src.Mid(0, 2);
         str.trim_left('0');
         set["day"] = str;
      }
      else
      {
         set["day"] = 0;
      }
      if (src.get_length() >= 5)
      {
         str = src.Mid(3, 2);
         str.trim_left('0');
         set["month"] = str;
      }
      else
      {
         set["month"] = 0;
      }
      if (src.get_length() >= 10)
      {
         str = src.Mid(6, 4);
         str.trim_left('0');
         set["year"] = str;
      }
      else
      {
         set["year"] = 0;
      }
      if (src.get_length() >= 13)
      {
         str = src.Mid(11, 2);
         str.trim_left('0');
         set["hour"] = str;
      }
      else
      {
         set["hour"] = 0;
      }
      if (src.get_length() >= 16)
      {
         str = src.Mid(14, 2);
         str.trim_left('0');
         set["minute"] = str;
      }
      else
      {
         set["minute"] = 0;
      }
      if (src.get_length() >= 19)
      {
         str = src.Mid(17, 2);
         str.trim_left('0');
         set["second"] = str;
      }
      else
      {
         set["second"] = 0;
      }
   }


   result department::strtotime(const ::text::context* pcontext, const char* psz, i32& iPath, i32& iPathCount, bool bUTC)
   {
      ::datetime::time time;
      string str(psz);
      str.trim();
      str += " ";
      property_set set;
      bool bBaseTime = false;
      i32 iStart = 0;

      // if is international date time 2009-04-31 21:45:59
      // or
      // if is international date time 2009-04-31 21:45
      if (str.get_length() >= 16)
      {
         if (((str.Mid(4, 1) == "-") || (str.Mid(4, 1) == ":"))
            && ((str.Mid(7, 1) == "-") || (str.Mid(7, 1) == ":"))
            && str.Mid(10, 1) == " "
            && str.Mid(13, 1) == ":")
         {
            bBaseTime = true;
            
            auto psystem = m_psystem;

            auto pdatetime = m_psystem->datetime();

            pdatetime->international().parse_str(str, set);

            string strWord = str.Mid(19);
            strWord.trim_left();
            strWord = ::str::get_word(strWord, " ");
            if (strWord.compare_ci("UTC") == 0
               || strWord.compare_ci("GMT") == 0
               || bUTC)
            {
               struct tm atm;
               atm.tm_sec = set["second"].i32();
               atm.tm_min = set["minute"].i32();
               atm.tm_hour = set["hour"].i32();
               atm.tm_mday = set["day"].i32();
               atm.tm_mon = set["month"].i32() - 1;        // tm_mon is 0 based
               atm.tm_year = set["year"].i32() - 1900;     // tm_year is 1900 based
               atm.tm_isdst = -1;
               /*time_t now = _time64(nullptr);
               time_t nowUtc = mktime(gmtime(&now));
               time_t tDiff = difftime(nowUtc, now);*/
#ifdef WINDOWS
               time = ::datetime::time(_mkgmtime64(&atm));
#else
               time = ::datetime::time(timegm(&atm));
#endif
            }
            else
            {
               time = ::datetime::time(
                  set["year"].i32(),
                  set["month"].i32(),
                  set["day"].i32(),
                  set["hour"].i32(),
                  set["minute"].i32(),
                  set["second"].i32());
            }
            iStart = 20;
         }
      }
      // if is international date time 2009-04-31
      if (!bBaseTime && str.get_length() >= 10)
      {
         if (str.Mid(4, 1) == "-"
            && str.Mid(7, 1) == "-")
         {
            bBaseTime = true;

            auto psystem = m_psystem;

            auto pdatetime = m_psystem->datetime();

            pdatetime->international().parse_str(str, set);

            time = ::datetime::time(
               set["year"].i32(),
               set["month"].i32(),
               set["day"].i32(),
               set["hour"].i32(),
               set["minute"].i32(),
               set["second"].i32());
            iStart = 11;
         }
      }
      // if is international date time 31/04/2011
      if (!bBaseTime && str.get_length() >= 10)
      {
         if (str.Mid(2, 1) == "/"
            && str.Mid(5, 1) == "/")
         {
            bBaseTime = true;
            parse_br_str(str, set);

            time = ::datetime::time(
               set["year"].i32(),
               set["month"].i32(),
               set["day"].i32(),
               set["hour"].i32(),
               set["minute"].i32(),
               set["second"].i32());
            iStart = 11;
         }
      }
      if (!bBaseTime && (
         ::str::begins_eat(str, "today") ||
         (pcontext != nullptr && pcontext->begins_eat(str, "calendar:today"))))
      {
         time = ::datetime::time::get_current_time();
         time = ::datetime::time(time.GetYear(), time.GetMonth(), time.GetDay(), 0, 0, 0);
         bBaseTime = true;
      }
      if (!bBaseTime && (
         ::str::begins_eat(str, "tomorrow") ||
         (pcontext != nullptr && pcontext->begins_eat(str, "calendar:tomorrow"))))
      {
         time = ::datetime::time::get_current_time();
         time = ::datetime::time(time.GetYear(), time.GetMonth(), time.GetDay(), 0, 0, 0);
         time += ::datetime::time_span(1, 0, 0, 0);
         bBaseTime = true;
      }
      if (!bBaseTime && (
         ::str::begins_eat(str, "yesterday") ||
         (pcontext != nullptr && pcontext->begins_eat(str, "calendar:yesterday"))))
      {
         time = ::datetime::time::get_current_time();
         time = ::datetime::time(time.GetYear(), time.GetMonth(), time.GetDay(), 0, 0, 0);
         time -= ::datetime::time_span(1, 0, 0, 0);
         bBaseTime = true;
      }
      if (!bBaseTime && (
         ::str::begins_eat(str, "now") ||
         (pcontext != nullptr && pcontext->begins_eat(str, "calendar:now"))))
      {

         time = ::datetime::time::get_current_time();

         bBaseTime = true;

      }

      string_array stra;

      auto psystem = m_psystem;

      auto pdatetime = m_psystem->datetime();

      auto pcre1 = psystem->create_pcre("^\\s*((\\d+)\\s*/\\s*(\\d+))((\\d|$)?!)");

      auto ptopic = pcre1->create_topic(str);

      if (!bBaseTime && ptopic && ptopic->get_count() >= 5)
      {
         time = ::datetime::time::get_current_time();
         i32 i1 = atoi(ptopic->get_match(2));
         i32 i2 = atoi(ptopic->get_match(3));
         i32 iCount = 0;
         bool bFirst = false;
         if (i1 != i2
            && i1 >= 1 && i1 <= 12
            && i2 >= 1 && i2 <=
            pdatetime->get_month_day_count(time.GetYear(), i1))
         {
            bFirst = true;
            iCount++;
         }
         if (i2 >= 1 && i2 <= 12
            && i1 >= 1 && i1 <=
            pdatetime->get_month_day_count(time.GetYear(), i2))
         {
            iCount++;
         }
         if (iCount > 0)
         {
            if ((iCount == 1 && bFirst) || (iCount == 2 && (iPath % iCount) == 0))
            {
               i32 iDay = i2;
               i32 iMonth = i1;
               time = ::datetime::time(time.GetYear(), iMonth, iDay,
                  time.GetHour(), time.GetMinute(), time.GetSecond());
               time = ::datetime::time(time.GetYear(), time.GetMonth(), time.GetDay(), 0, 0, 0);
            }
            else if ((iCount == 1 && !bFirst) || (iCount == 2 && (iPath % iCount) == 1))
            {
               i32 iDay = i1;
               i32 iMonth = i2;
               time = ::datetime::time(time.GetYear(), iMonth, iDay,
                  time.GetHour(), time.GetMinute(), time.GetSecond());
               time = ::datetime::time(time.GetYear(), time.GetMonth(), time.GetDay(), 0, 0, 0);
            }
            iPath = iPath / iCount;
            iPathCount = iPathCount * iCount;
            bBaseTime = true;
         }
      }
      if (bBaseTime)
      {
         if (str.Mid(iStart).trimmed().get_length() == 0)
         {

            return result(time);

         }

         return result(time) + span_strtotime(pcontext, str.Mid(iStart));

      }
      else
      {

         return span_strtotime(pcontext, str.Mid(iStart));

      }

   }


   string department::to_string(const ::text::context* pcontext, const ::datetime::result& result)
   {

      string str;

      if (result.m_bSpan)
      {
         string_array stra;
         string strItem;
         if (result.m_iYear != 0)
         {
            if (abs(result.m_iYear) == 1)
            {
               strItem.Format("%d year", result.m_iYear);
            }
            else
            {
               strItem.Format("%d years", result.m_iYear);
            }
            stra.add(strItem);
         }
         if (result.m_iMonth != 0)
         {
            if (abs(result.m_iMonth) == 1)
            {
               strItem.Format("%d month", result.m_iMonth);
            }
            else
            {
               strItem.Format("%d months", result.m_iMonth);
            }
            stra.add(strItem);
         }
         if (result.m_iDay != 0)
         {
            if (abs(result.m_iDay) == 1)
            {
               strItem.Format("%d day", result.m_iDay);
            }
            else
            {
               strItem.Format("%d days", result.m_iDay);
            }
            stra.add(strItem);
         }
         if (result.m_iHour != 0)
         {
            if (abs(result.m_iHour) == 1)
            {
               strItem.Format("%d hour", result.m_iHour);
            }
            else
            {
               strItem.Format("%d hours", result.m_iHour);
            }
            stra.add(strItem);
         }
         if (result.m_iMinute != 0)
         {
            if (abs(result.m_iMinute) == 1)
            {
               strItem.Format("%d minute", result.m_iMinute);
            }
            else
            {
               strItem.Format("%d minutes", result.m_iMinute);
            }
            stra.add(strItem);
         }
         if (result.m_iSecond != 0)
         {
            if (abs(result.m_iSecond) == 1)
            {
               strItem.Format("%d second", result.m_iSecond);
            }
            else
            {
               strItem.Format("%d seconds", result.m_iSecond);
            }
            stra.add(strItem);
         }
         if (stra.get_count() >= 2)
         {
            str = stra.implode(", ", 0, stra.get_count() - 1) + " and " + stra.last();
         }
         else if (stra.get_count() == 1)
         {
            str = stra[0];
         }
      }
      else
      {
         ::datetime::time time = result.get_time();
         if (time.GetSecond() == 0)
         {
            if (time.GetHour() == 0 && time.GetMinute() == 0)
            {

               str = Format("%Y-", time);

               get_month_str(pcontext, time.GetMonth());

               str += Format("-%d", time);

            }
            else
            {

               str = Format("%Y-", time);

               str += get_month_str(pcontext, time.GetMonth());

               str += Format("-%d %H:%M", time);

            }
         }
         else
         {

            str = Format("%Y-", time);

            str += get_month_str(pcontext, time.GetMonth());

            str += Format("-%d %H:%M:%S", time);

         }

      }

      return str;

   }


} // namespace datetime





//
//i64 g_iFirstNano;
//
//
////extern "C"
//CLASS_DECL_APEX i64 first_nano()
//{
//
//   return g_iFirstNano;
//
//}
//



//
//
////extern "C"
//CLASS_DECL_APEX ::u32 get_fast_tick_count()
//{
//
//#ifdef WINDOWS
//
//   return GetTickCount();
//
//#else
//
//   struct timeval tv;
//
//   if (gettimeofday(&tv, nullptr) != 0)
//   {
//
//      return 0;
//
//   }
//
//   return (::u32)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
//
//#endif
//
//}


//
//
//// http://stackoverflow.com/questions/32424125/c-code-to-get-local-time-offset-in-minutes-relative-to-utc
//// http://stackoverflow.com/questions/32424125/c-code-to-get-local-time-offset-in-minutes-relative-to-utc/32433950#32433950
//// http://stackoverflow.com/users/619295/trenki
//extern "C"
//CLASS_DECL_APEX int c_localtime_offset()
//{
//
//   time_t rawtime = time(nullptr);
//
//   struct tm *ptm = gmtime(&rawtime);
//
//   // Request that mktime() looksup dst in timezone database
//
//   ptm->tm_isdst = -1;
//
//   time_t gmt = mktime(ptm);
//
//   return (int)(rawtime - gmt);
//
//}
