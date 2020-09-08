
#include "framework.h" // from "base/apex/.h"
#include <time.h>
//#ifdef ANDROID
//#include <sys/time.h>
//#endif



namespace datetime
{


   ::datetime::time department::from_local(const string & str)
   {

      int iPathCount;

      return ::datetime::time(strtotime(Session.str_context(), str, 0, iPathCount));

   }


   ::datetime::time department::from_gmt(const string& str)
   {

      int iPathCount;

      return ::datetime::time(gmt_strtotime(Session.str_context(), str, 0, iPathCount));

   }


   department::department() :
      m_international(this),
      m_str(this)
   {

      defer_create_mutex();

      m_str.m_pdatetime = this;

      
   }


   class department::international & department::international()
   {

      return m_international;

   }


   class department::str & department::str()
   {
      return m_str;
   }

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
      return atoi(time.Format("%w"));
   }

   i64 department::get_timestamp(i32 year, i32 month, i32 day)
   {
      string strInternationalDate;
      strInternationalDate.Format("%d-%02d-%02d", year, month, day);
      i32 i;
      return strtotime(nullptr, strInternationalDate, 0, i);
   }

   i64 department::strtotime(const ::apex::str_context * pcontext, const char * psz, i32 iPath, i32 & iPathCount)
   {

      if (::is_null(psz) || string(psz).trimmed().is_empty())
      {

         return 0;

      }

      ::datetime::time time;
      ::datetime::value val = ::datetime::strtotime(get_context_application(), pcontext, psz, iPath, iPathCount, false);
      if (val.m_bSpan)
         time = time.get_current_time() + val.GetSpan();
      else
         time = val.get_time();
      return time.get_time();
   }

   i64 department::strtotime(const ::apex::str_context * pcontext, const char * psz, time_t timeParam, i32 iPath, i32 & iPathCount)
   {

      if (::is_null(psz) || string(psz).trimmed().is_empty())
      {

         return 0;

      }

      UNREFERENCED_PARAMETER(iPath);
      ::datetime::time time(timeParam);
      iPathCount = 1;
      ::datetime::value val = ::datetime::value(time) +
                              ::datetime::span_strtotime(get_context_application(), pcontext, psz);
      return val.get_time().get_time();
   }

   i64 department::gmt_strtotime(const ::apex::str_context * pcontext, const char * psz, i32 iPath, i32 & iPathCount)
   {

      if (::is_null(psz) || string(psz).trimmed().is_empty())
      {

         return 0;

      }

      ::datetime::time time;
      ::datetime::value val = ::datetime::strtotime(get_context_application(), pcontext, psz, iPath, iPathCount, true);
      if (val.m_bSpan)
         time = time.get_current_time() + val.GetSpan();
      else
         time = val.get_time();
      return time.get_time();
   }

   department::international::international(::object * pobject) :
      ::object(pobject)
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
      time.FormatGmt(str, strFormat);
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
      time.Format(str, strFormat);
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


   department::str::str(::object * pobject)
   {
      UNREFERENCED_PARAMETER(pobject);
      m_pdatetime = nullptr;
   }

   string department::str::get_gmt_date_time()
   {
      return m_pdatetime->international().get_gmt_date_time(::datetime::time::get_current_time());
   }


   time_t department::s_local_mktime(i32 iHour, i32 iMinute, i32 iSecond, i32 iMonth, i32 iDay, i32 iYear)
   {

      struct ::tm tm;

      xxf_zero(tm);
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

      xxf_zero(tm);
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



   string department::get_week_day_str(const apex::str_context * pcontext, i32 iWeekDay) // 1 - domingo
   {
      return System.str().get(pcontext, "datetimestr_weekday_long[" + __str(iWeekDay - 1) + "]");
   }

   string department::get_tiny_week_day_str(const apex::str_context * pcontext, i32 iWeekDay) // 1 - domingo
   {
      return System.str().get(pcontext, "datetimestr_weekday_tiny[" + __str(iWeekDay - 1) + "]");
   }

   string department::get_month_str(const apex::str_context * pcontext, i32 iMonth)
   {
      return System.str().get(pcontext, "datetimestr_month[" + __str(iMonth - 1) + "]");
   }

   string department::get_short_month_str(const apex::str_context * pcontext, i32 iMonth)
   {
      return System.str().get(pcontext, "datetimestr_month_short[" + __str(iMonth - 1) + "]");
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
      __throw(invalid_argument_exception());
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
      time.FormatGmt(str, strFormat);
      return str;
   }

   string department::strftime(const char * psz)
   {
      string str;
      ::datetime::time time;
      time = ::datetime::time::get_current_time();
      time.FormatGmt(str, psz);
      return str;
   }

   string department::friend_time(const apex::str_context * pcontext, ::datetime::time timeNow, ::datetime::time time)
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
            strTime.replace("%SECONDS%", __str((timeNow - time).GetSeconds()));
         }
         else if (iMinDiff <= 2)
         {
            strTime = pcontext->get("about 2 minutes and %SECONDS% seconds ago");
            strTime.replace("%SECONDS%", __str((timeNow - time).GetSeconds()));
         }
         else
         {
            strTime = pcontext->get("about %MINUTES% minutes ago");
            strTime.replace("%MINUTES%", __str(iMinDiff));
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
            strTime.replace("%HOURS%", __str(iHouDiff));
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









   string department::_001FriendTime(const ::apex::str_context* pcontext, const ::datetime::time& timeNow, const ::datetime::time& time)
   {

      bool bDiff = false;
      bool bSolved = false;
      string strTime;
      string str;
      __int64 iSecDiff = (timeNow - time).GetTotalSeconds();
      __int64 iMinDiff = (timeNow - time).GetTotalMinutes();
      __int64 iHouDiff = (timeNow - time).GetTotalHours();
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

               //str = Sys(pscript->get_context_application()).datetime().get_tiny_week_day_str(pscript->str_context(), time.GetGmtDayOfWeek());
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
//CLASS_DECL_APEX stream & operator >> (stream & s, string_map < class ::datetime::department::time_zone > & m)
//{
//
//   s.stream_map(m);
//
//   return s;
//
//}
//
//
//CLASS_DECL_APEX stream & operator << (stream & s, string_map < class ::datetime::department::time_zone > & m)
//{
//
//   s.stream_map(m);
//
//   return s;
//
//}
//
//
//CLASS_DECL_APEX stream & operator >> (stream & s, int_ptr_map < class ::datetime::department::time_zone > & m)
//{
//
//   s.stream_map(m);
//
//   return s;
//
//}
//
//
//CLASS_DECL_APEX stream &operator << (stream & s, int_ptr_map < class ::datetime::department::time_zone > & m)
//{
//
//   s.stream_map(m);
//
//   return s;
//
//}
//
