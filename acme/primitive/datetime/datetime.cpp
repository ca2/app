// From datetime to datetime by camilo on 2022-11-19 04:41 <3ThomasBorregaardSorensen!!
#include "framework.h" // from "base/apex/.h"
#include "datetime.h"
////#include "acme/exception/exception.h"
#include "acme/exception/not_implemented.h"
#include "acme/platform/system.h"
#include "acme/primitive/datetime/_string.h"
//#include "acme/primitive/primitive/payload.h"
#include "acme/primitive/string/str.h"
#include "acme/primitive/text/context.h"
#include "acme/regular_expression/regular_expression.h"
#include "acme/regular_expression/result.h"


#include <time.h>


namespace datetime
{


   datetime::datetime()
   {

      defer_create_synchronization();

   }


   datetime::~datetime()
   {

   }

   ::earth::time datetime::from_string(const ::text::context* pcontext, const ::string & str, const ::earth::time_shift & timeshift)
   {

      int iPathCount;

      return ::earth::time(strtotime(pcontext, str, 0, iPathCount, timeshift));

   }


   //::earth::time datetime::from_utc(const ::text::context* pcontext, const string& str)
   //{

   //   int iPathCount;

   //   return ::earth::time(utc_strtotime(pcontext, str, 0, iPathCount));

   //}


   //datetime::datetime()
   //{

   //}


   void datetime::initialize(::particle * pparticle)
   {
    
      /*auto estatus = */ ::acme::department::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}
         
      /*estatus = */ __construct_new(m_pinternational);

      //if (!estatus)
      //{

      //   return estatus;

      //}

//      /*estatus = */ __construct_new(m_pstr);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //m_pstr->m_pdatetime = this;

      //return estatus;

   }


   void datetime::international::initialize(::particle * pparticle)
   {

      /*auto estatus = */ ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


//   void datetime::str().initialize(::particle * pparticle)
//   {
//
//      /* auto estatus = */ ::object::initialize(pparticle);
//
//      //if (!estatus)
//      //{
//
//      //   return estatus;
//
//      //}
//
//      //return estatus;
//
//   }
//

   void datetime::destroy()
   {

      m_pinternational.release();

      //m_pstr.release();

      ::acme::department::destroy();

      //return ::success;

   }


   /*class datetime::international & datetime::international()
   {

      return *m_pinternational;

   }


   class datetime::str & datetime::str()
   {
      return *m_str;
   }*/

   i32 datetime::get_month_day_count(i32 year, i32 month)
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
   i32 datetime::get_weekday(i32 year, i32 month, i32 day)
   {

      ::earth::time time(year, month, day, 0, 0, 0);

      return time.day_of_week();

   }


   i64 datetime::get_timestamp(i32 year, i32 month, i32 day)
   {
      
      ::earth::time time(year, month, day, 0, 0, 0);

      return time.m_i;

   }


   i64 datetime::strtotime(const ::text::context * pcontext, const string & str, i32 iPath, i32 & iPathCount, const ::earth::time_shift & timeshift)
   {

      if (str.trimmed().is_empty())
      {

         return 0;

      }

      ::earth::time time;

      ::datetime::result val = parse_time(pcontext, str, iPath, iPathCount, timeshift);

      if (val.m_bSpan)
      {

         time = ::earth::time::now() + val.GetSpan();

      }
      else
      {

         time = val.get_time();

      }

      return time.get_time();

   }


   i64 datetime::strtotime(const ::text::context * pcontext, const string & str, time_t timeParam, i32 iPath, i32 & iPathCount, const ::earth::time_shift& timeshift)
   {

      if (str.trimmed().is_empty())
      {

         return 0;

      }

      __UNREFERENCED_PARAMETER(iPath);

      ::earth::time time(timeParam);

      iPathCount = 1;

      ::datetime::result val = ::datetime::result(time) + span_parse_time(pcontext, str);

      return val.get_time().get_time();

   }


   //i64 datetime::utc_strtotime(const ::text::context * pcontext, const ::scoped_string & scopedstr, i32 iPath, i32 & iPathCount)
   //{

   //   if (::is_null(psz) || string(psz).trimmed().is_empty())
   //   {

   //      return 0;

   //   }

   //   ::earth::time time;

   //   ::datetime::result val = strtotime(pcontext, psz, iPath, iPathCount, true);

   //   if (val.m_bSpan)
   //   {

   //      time = ::earth::time::now() + val.GetSpan();

   //   }
   //   else
   //   {

   //      time = val.get_time();

   //   }

   //   return time.get_time();

   //}


   datetime::international::international()
   {


   }


   void datetime::international::parse_str(const string & strSrc, property_set & set)
   {
      
      string src(strSrc);

      src.trim();

      string str;

      if (src.length() >= 4)
      {

         str = src.Mid(0, 4);

         str.trim_left('0');

         set["year"] = str;

      }
      else
      {
         
         set["year"] = 0;

      }
      
      if (src.length() >= 7)
      {

         str = src.Mid(5, 2);

         str.trim_left('0');

         set["month"] = str;

      }
      else
      {
         
         set["month"] = 0;

      }

      if (src.length() >= 10)
      {
      
         str = src.Mid(8, 2);

         str.trim_left('0');

         set["day"] = str;

      }
      else
      {
         
         set["day"] = 0;

      }

      if (src.length() >= 13)
      {
      
         str = src.Mid(11, 2);
         
         str.trim_left('0');
         
         set["hour"] = str;

      }
      else
      {
         
         set["hour"] = 0;

      }

      if (src.length() >= 16)
      {
      
         str = src.Mid(14, 2);
         
         str.trim_left('0');
         
         set["minute"] = str;

      }
      else
      {
         
         set["minute"] = 0;

      }

      if (src.length() >= 19)
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


   string datetime::international::get_date_time(const ::earth::time & time, string strFormat, const ::earth::time_shift& timeshift)
   {
      
      string str;
      
      str = ::earth::format(strFormat, time, timeshift);
      
      return str;

   }


   //string datetime::international::utc_get_date_time(string strFormat)
   //{

   //   ::earth::time time;

   //   time = ::earth::time::now();

   //   return utc_get_date_time(time, strFormat);

   //}


   string datetime::international::get_date_time_for_file(const ::earth::time_shift& timeshift, const ::earth::time & time)
   {

      return get_date_time(time, INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE, timeshift);

   }


   //string datetime::international::get_date_time(const ::earth::time & time, string strFormat, const ::earth::time_shift& timeshift)
   //{
   //   
   //   string str;
   //   
   //   str = ::datetime::local_format(strFormat, time);

   //   return str;

   //}


   string datetime::international::get_date_time(string strFormat, const ::earth::time_shift& timeshift)
   {

      ::earth::time time;

      time = ::earth::time::now();

      return get_date_time(time, strFormat, timeshift);

   }


   //string datetime::international::get_date_time_for_file(const ::earth::time_shift& timeshift)
   //{

   //   return get_date_time(INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE, timeshift);

   //}


   string datetime::international::get_date_time_for_file_with_no_spaces(const ::earth::time_shift& timeshift, const ::earth::time & time)
   {

      string str = get_date_time_for_file(timeshift, time);

      str.replace_with("_", " ");

      return str;

   }


   //string datetime::international::get_date_time_for_file_with_no_spaces(const ::earth::time_shift& timeshift)
   //{

   //   string str = get_date_time_for_file(timeshift);

   //   str.replace(" ", "_");

   //   return str;

   //}


//   datetime::str().str()
//   {
//      
//      m_pdatetime = nullptr;
//
//   }
//
//
//   string datetime::str().get_date_time(const ::earth::time_shift& timeshift)
//   {
//
//      return m_pdatetime->international().get_date_time(::earth::time::now(), timeshift);
//
//   }
//

   time_t datetime::s_mktime(i32 iHour, i32 iMinute, i32 iSecond, i32 iMonth, i32 iDay, i32 iYear, const ::earth::time_shift& timeshift)
   {

      struct ::tm tm {};

      tm.tm_hour = iHour;
      tm.tm_min = iMinute;
      tm.tm_sec = iSecond;
      tm.tm_mon = iMonth - 1;
      tm.tm_mday = iDay;
      tm.tm_year = iYear - 1900;

      auto time = make_utc_time(&tm);

      return (time_t) (time - (time_t) timeshift.m_d);

//#ifdef WINDOWS
//
//      return _mktime64(&tm);
//
//#else
//
//      return ::mktime(&tm);
//
//#endif

   }


   //time_t datetime::s_utc_mktime(i32 iHour, i32 iMinute, i32 iSecond, i32 iMonth, i32 iDay, i32 iYear)
   //{

   //   struct ::tm tm;

   //   zero(tm);
   //   
   //   tm.tm_hour = iHour;
   //   tm.tm_min = iMinute;
   //   tm.tm_sec = iSecond;
   //   tm.tm_mon = iMonth - 1;
   //   tm.tm_mday = iDay;
   //   tm.tm_year = iYear - 1900;

//      return make_utc_time(&tm);

   //}


   string datetime::get_week_day_str(const ::text::context * pcontext, i32 iWeekDay) // 1 - domingo
   {
      
      return acmesystem()->texttable()->get(pcontext, "datetimestr_weekday_long[" + ::as_string(iWeekDay - 1) + "]");

   }


   string datetime::get_tiny_week_day_str(const ::text::context * pcontext, i32 iWeekDay) // 1 - domingo
   {

      return acmesystem()->texttable()->get(pcontext, "datetimestr_weekday_tiny[" + ::as_string(iWeekDay - 1) + "]");

   }


   string datetime::get_month_str(const ::text::context * pcontext, i32 iMonth)
   {
   
      return acmesystem()->texttable()->get(pcontext, "datetimestr_month[" + ::as_string(iMonth - 1) + "]");

   }


   string datetime::get_short_month_str(const ::text::context * pcontext, i32 iMonth)
   {

      return acmesystem()->texttable()->get(pcontext, "datetimestr_month_short[" + ::as_string(iMonth - 1) + "]");

   }


   //::earth::time datetime::from_date_time(i32 iYear, i32 iMonth, i32 iDay, i32 iHour, i32 iMinute, i32 iSecond)
   //{

   //   return s_utc_mktime(iYear, iMonth, iDay, iHour, iMinute, iSecond);

   //}


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
   i32 datetime::SWN(i32 y, i32 m, i32 d)
   {
      return 1 + (DP(y, m) + d - 1) / 7;
   }

   //where DP ("Days Passed") is given by:
   //   DP( y, 1 ) = 0
   //  DP( y, m+1 ) = DP( y, m ) + ML( y, m )
   i32 datetime::DP(i32 y, i32 m)
   {
      if (m == 1)
         return 0;
      else
         return DP(y, m - 1) + ML(y, m - 1);
   }

   i32 datetime::ML(i32 y, i32 m)
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
      
      throw ::exception(error_bad_argument);


   }

   i32 datetime::LEAP(i32 y)
   {
      if ((y % 4 == 0) && ((y % 100 != 0) || (y % 400 == 0)))
         return 1;
      else
         return 0;
   }


   // Use this elegant code by Tomohiko Sakamoto:

   i32 datetime::dayofweek(i32 y, i32 m, i32 d)	/* 0 = Sunday */
   {
      static i32 t[] = { 0,3,2,5,0,3,5,1,4,6,2,4 };
      y -= m < 3;
      return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
   }

   i32 datetime::SDOW(i32 y, i32 m, i32 d) // ( 0 = Monday, ..., 6 = Sunday )
   {
      return (DP(y, m) + d - 1) % 7;
   }


   i32 datetime::DOW(i32 y, i32 m, i32 d)
   {
      //return SDOW(y, m, d);
      return getDayOfWeek(m, d, y, 0);
   }


   i32 datetime::getDayOfWeek(i32 month, i32 day, i32 year, i32 CalendarSystem)
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


   i32 datetime::ISO_WN(i32  y, i32 m, i32 d)
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


   string datetime::format(const string & strFormatParam, const ::earth::time & time, const ::earth::time_shift & timeshift)
   {

      string strFormat(strFormatParam);

      string str;

      auto pFind = strFormat.find("%V");

      if (::is_set(pFind))
      {

         string strV;

         strV.format("%02d", ISO_WN(time.year(timeshift), time.month(timeshift), time.day(timeshift)));

         strFormat.replace_with(strV, "%V");

      }

      str = ::earth::format(strFormat, time, timeshift);

      return str;

   }


   string datetime::format(const string & str, const ::earth::time_shift& timeshift)
   {

      return format(str, ::earth::time::now(), timeshift);

   }


   //string datetime::strftime(const ::scoped_string & scopedstr, const ::earth::time & time, const ::earth::time_shift& timeshift)
   //{

   //   string strFormat(psz);

   //   string str;

   //   auto pFind = strFormat.find("%V");

   //   if (::is_set(pFind))
   //   {

   //      string strV;
   //      
   //      strV.format("%02d", ISO_WN(time.utc_year(), time.utc_month(), time.utc_day()));

   //      strFormat.replace("%V", strV);

   //   }

   //   str = ::datetime::utc_format(strFormat, time);

   //   return str;

   //}


   //string datetime::utc_strftime(const ::scoped_string & scopedstr)
   //{
   //   
   //   return utc_strftime(psz, ::earth::time::now());
   //   
   //}


   string datetime::friend_time(const ::text::context * pcontext, ::earth::time timeNow, ::earth::time time, const ::earth::time_shift& timeshift)
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
         strTime.format("about %d seconds ago", (timeNow - time).GetTotalSeconds());
      }
      else if (iMinDiff <= 59)
      {
         bSolved = true;
         if (iMinDiff <= 1)
         {
            strTime = pcontext->get("about 1 minute and %SECONDS% seconds ago");
            strTime.replace_with(::as_string((timeNow - time).GetSeconds()), "%SECONDS%");
         }
         else if (iMinDiff <= 2)
         {
            strTime = pcontext->get("about 2 minutes and %SECONDS% seconds ago");
            strTime.replace_with(::as_string((timeNow - time).GetSeconds()), "%SECONDS%");
         }
         else
         {
            strTime = pcontext->get("about %MINUTES% minutes ago");
            strTime.replace_with(::as_string(iMinDiff), "%MINUTES%");
         }
      }
      else if (iHouDiff <= 24)
      {
         bSolved = true;
         if (iHouDiff <= 1)
         {
            strTime.format("about 1 hour and %d minutes ago", (timeNow - time).GetMinutes());
         }
         else if (iHouDiff <= 2)
         {
            strTime.format("about 2 hours and %d minutes ago", (timeNow - time).GetMinutes());
         }
         else
         {
            strTime = pcontext->get("about %HOURS% hours ago");
            strTime.replace_with(::as_string(iHouDiff), "%HOURS%");
         }
      }
      else
      {
         if (!bSolved && timeNow.year(timeshift) != time.year(timeshift))
         {
            bDiff = true;
            str.format("%04d", time.year(timeshift));
            strTime = str;
         }
         if (!bSolved && (bDiff || timeNow.month(timeshift) != time.month(timeshift)))
         {
            str = get_month_str(pcontext, time.month(timeshift));
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
         if (!bSolved && (bDiff || timeNow.day(timeshift) != time.day(timeshift)))
         {
            str.format("%02d", time.day());
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
         if (!bSolved && (bDiff || timeNow.hour(timeshift) != time.hour(timeshift)))
         {
            str.format("%02d", time.hour(timeshift));
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
         if (!bSolved && (bDiff || timeNow.minute(timeshift) != time.minute(timeshift)))
         {
            if (bDiff)
            {
               str.format("%02d", time.minute(timeshift));
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
               str.format("%02d", time.second(timeshift));
               strTime += ":" + str;
            }
            else
            {

            }

         }

      }

      return strTime;

   }









   string datetime::_001FriendTime(const ::text::context* pcontext, const ::earth::time& timeNow, const ::earth::time& time, const ::earth::time_shift& timeshift)
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
         //strTime.format("about %d seconds ago", (timeNow - time).GetTotalSeconds());
         strTime.format("%ds", (timeNow - time).GetTotalSeconds());
      }
      else if (iMinDiff <= 59)
      {
         bSolved = true;
         if (iMinDiff <= 1)
         {
            //strTime = pscript->pstr("about 1 minute and %SECONDS% seconds ago");
            //strTime = pscript->pstr("1m %SECONDS%s seconds ago");
            strTime.format("1m %ds", (timeNow - time).GetSeconds());
         }
         else if (iMinDiff <= 2)
         {
            //strTime = pscript->pstr("about 2 minutes and %SECONDS% seconds ago");
            //strTime = pscript->pstr("2 minutes and %SECONDS% seconds ago");
            strTime.format("2m %ds", (timeNow - time).GetSeconds());
         }
         else
         {
            //strTime = pscript->pstr("about %MINUTES% minutes ago");
            //strTime = pscript->pstr("%MINUTES% minutes ago");
            strTime.format("%dm", iMinDiff);
         }
      }
      else if (iHouDiff <= 24)
      {
         bSolved = true;
         if (iHouDiff <= 1)
         {
            //strTime.format("about 1 hour and %d minutes ago", (timeNow - time).GetMinutes());
            strTime.format("1h %dm", (timeNow - time).GetMinutes());

         }
         else if (iHouDiff <= 2)
         {
            //strTime.format("about 2 hours and %d minutes ago", (timeNow - time).GetMinutes());
            strTime.format("2h %dm", (timeNow - time).GetMinutes());
         }
         else
         {
            //strTime = pscript->pstr("about %HOURS% hours ago");
            //strTime = pscript->pstr("%HOURS% hours ago");
            strTime.format("%dh", iHouDiff);
         }
      }
      else
      {
         if (!bSolved && timeNow.year(timeshift) != time.year(timeshift))
         {
            bDiff = true;
            str.format("%04d", time.year(timeshift));
            strTime = str;
         }
         if (!bSolved && (bDiff || timeNow.month(timeshift) != time.month(timeshift)))
         {
            str = get_month_str(pcontext, time.month(timeshift));
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

               //str = Sys(pscript->get_app()).datetime().get_tiny_week_day_str(pscript->textcontext(), time.GetGmtDayOfWeek());
               str = straWeekDay[time.day_of_week(timeshift) % 7];

            }
            else
            {
               str.format("%dd, time.GetGmtDay()");

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
         if (!bSolved && (bDiff || timeNow.hour(timeshift) != time.hour(timeshift)))
         {
            str.format("%02d", time.hour(timeshift));
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
         if (!bSolved && (bDiff || timeNow.minute(timeshift) != time.minute(timeshift)))
         {
            if (bDiff)
            {
               
               str.format("%02d", time.minute(timeshift));
               
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
               
               str.format("%02d", time.second(timeshift));

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


#include "framework.h"
#include <time.h>

#ifndef WINDOWS

#include <sys/time.h>

#endif



namespace datetime
{


   result datetime::span_parse_time(const ::text::context* pcontext, const string & strSpanExpression, const ::earth::time_shift & timeshift)
   {

      static atom idCalendarDay("calendar:day");
      static atom idCalendarDays("calendar:days");
      static atom idCalendarWeek("calendar:week");
      static atom idCalendarWeeks("calendar:weeks");
      static atom idCalendarYear("calendar:year");
      static atom idCalendarYears("calendar:years");
      static atom idCalendarHour("calendar:hour");
      static atom idCalendarHours("calendar:hours");
      static atom idCalendarNow("calendar:now");

      result time;
      time.m_bSpan = true;
      string str(strSpanExpression);
      str.trim();
      str += " ";
      property_set set;
      bool bAdd = false;
      bool bMinus = false;
      const char * psz = str.c_str();
      string strNumber;
      string strText1;
      string strChar;
      for (i32 i = 0; *psz; psz += strChar.length())
      {
         strChar = get_utf8_char(psz);
         if (unicode_is_whitespace(psz))
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
                  span.m_iDay = atoi(strNumber.c_str());
               }
               else if (strText1 == "week" || strText1 == "weeks"
                  || (pcontext != nullptr && pcontext->matches(idCalendarWeek, strText1))
                  || (pcontext != nullptr && pcontext->matches(idCalendarWeeks, strText1)))
               {
                  span.m_iDay = atoi(strNumber.c_str()) * 7;
               }
               else if (strText1 == "hour" || strText1 == "hours" || strText1 == "hora" || strText1 == "horas"
                  || (pcontext != nullptr && pcontext->matches(idCalendarHour, strText1))
                  || (pcontext != nullptr && pcontext->matches(idCalendarHour, strText1)))
               {
                  span.m_iHour = atoi(strNumber.c_str());
               }
               else if (strText1 == "year" || strText1 == "years"
                  || (pcontext != nullptr && pcontext->matches(idCalendarYear, strText1))
                  || (pcontext != nullptr && pcontext->matches(idCalendarYears, strText1)))
               {
                  span.m_iYear = atoi(strNumber.c_str());
               }
               else if (strText1 == "now"
                  || (pcontext != nullptr && pcontext->matches(idCalendarNow, strText1)))
               {
                  
                  throw ::exception(error_bad_argument, "now cannot be span");

               }
               else if (strText1.case_insensitive_order("UTC") == 0)
               {

               }
               else
               {
                  throw ::not_implemented();
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
               INFORMATION("strtotime: invalid char +");
            }
            else if (bMinus)
            {
               INFORMATION("strtotime: invalid char + on Minus state");
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
               
               INFORMATION("strtotime: invalid char - on add state");

            }
            else if (bMinus)
            {
               
               INFORMATION("strtotime: invalid char - on Minus state");

            }

#endif

            bAdd = false;
            bMinus = true;
            strNumber.Empty();
         }
         else if (unicode_is_digit(psz))
         {
            strNumber += strChar;
         }
         else if (unicode_is_letter(psz))
         {
            strText1 += strChar;
         }
      }
      return time;
   }
   void parse_br_str(const ::scoped_string & scopedstr, property_set& set)
   {
      string src(scopedstr);
      src.trim();
      string str;
      if (src.length() >= 2)
      {
         str = src.Mid(0, 2);
         str.trim_left('0');
         set["day"] = str;
      }
      else
      {
         set["day"] = 0;
      }
      if (src.length() >= 5)
      {
         str = src.Mid(3, 2);
         str.trim_left('0');
         set["month"] = str;
      }
      else
      {
         set["month"] = 0;
      }
      if (src.length() >= 10)
      {
         str = src.Mid(6, 4);
         str.trim_left('0');
         set["year"] = str;
      }
      else
      {
         set["year"] = 0;
      }
      if (src.length() >= 13)
      {
         str = src.Mid(11, 2);
         str.trim_left('0');
         set["hour"] = str;
      }
      else
      {
         set["hour"] = 0;
      }
      if (src.length() >= 16)
      {
         str = src.Mid(14, 2);
         str.trim_left('0');
         set["minute"] = str;
      }
      else
      {
         set["minute"] = 0;
      }
      if (src.length() >= 19)
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


   result datetime::parse_time(const ::text::context* pcontext, const string & strParam, i32& iPath, i32& iPathCount, const ::earth::time_shift& timeshift)
   {
      ::earth::time time;
      string str(strParam);
      str.trim();
      str += " ";
      property_set set;
      bool bBaseTime = false;
      i32 iStart = 0;

      // if is international date time 2009-04-31 21:45:59
      // or
      // if is international date time 2009-04-31 21:45
      if (str.length() >= 16)
      {

         if (((str.Mid(4, 1) == "-") || (str.Mid(4, 1) == ":"))
            && ((str.Mid(7, 1) == "-") || (str.Mid(7, 1) == ":"))
            && str.Mid(10, 1) == " "
            && str.Mid(13, 1) == ":")
         {

            bBaseTime = true;
            
            //auto pdatetime = datetime();

            international().parse_str(str, set);

            string strWord = str.Mid(19);
            strWord.trim_left();
            strWord = ::str().get_word(strWord, " ");
            if (strWord.case_insensitive_order("UTC") == 0
               || strWord.case_insensitive_order("GMT") == 0)
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
               time = ::earth::time(make_utc_time(&atm));

            }
            else
            {

               time = ::earth::time(
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
      if (!bBaseTime && str.length() >= 10)
      {
         if (str.Mid(4, 1) == "-"
            && str.Mid(7, 1) == "-")
         {
            bBaseTime = true;

            international().parse_str(str, set);

            time = ::earth::time(
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
      if (!bBaseTime && str.length() >= 10)
      {
         if (str.Mid(2, 1) == "/"
            && str.Mid(5, 1) == "/")
         {
            bBaseTime = true;
            parse_br_str(str, set);

            time = ::earth::time(
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
         str.begins_eat("today") ||
         (pcontext != nullptr && pcontext->begins_eat(str, "calendar:today"))))
      {
         time = ::earth::time::now();
         time = ::earth::time(time.year(timeshift), time.month(timeshift), time.day(timeshift), 0, 0, 0);
         bBaseTime = true;
      }
      if (!bBaseTime && (
         str.begins_eat("tomorrow") ||
         (pcontext != nullptr && pcontext->begins_eat(str, "calendar:tomorrow"))))
      {
         time = ::earth::time::now();
         time = ::earth::time(time.year(timeshift), time.month(timeshift), time.day(timeshift), 0, 0, 0);
         time += ::earth::time_span(1, 0, 0, 0);
         bBaseTime = true;
      }
      if (!bBaseTime && (
         str.begins_eat("yesterday") ||
         (pcontext != nullptr && pcontext->begins_eat(str, "calendar:yesterday"))))
      {
         time = ::earth::time::now();
         time = ::earth::time(time.year(timeshift), time.month(timeshift), time.day(timeshift), 0, 0, 0);
         time -= ::earth::time_span(1, 0, 0, 0);
         bBaseTime = true;
      }
      if (!bBaseTime && (
         str.begins_eat("now") ||
         (pcontext != nullptr && pcontext->begins_eat(str, "calendar:now"))))
      {

         time = ::earth::time::now();

         bBaseTime = true;

      }

      string_array stra;

      auto pdatetime = datetime();

      auto pcre1 = acmesystem()->compile_pcre("^\\s*((\\d+)\\s*/\\s*(\\d+))((\\d|$)?!)");

      auto presult = pcre1->run(str);

      if (!bBaseTime && presult && presult->get_count() >= 5)
      {

         time = ::earth::time::now();

         i32 i1 = atoi(presult->get_match(2).c_str());

         i32 i2 = atoi(presult->get_match(3).c_str());

         i32 iCount = 0;

         bool bFirst = false;

         if (i1 != i2
            && i1 >= 1 && i1 <= 12
            && i2 >= 1 && i2 <=
            get_month_day_count(time.year(timeshift), i1))
         {
            bFirst = true;
            iCount++;
         }
         if (i2 >= 1 && i2 <= 12
            && i1 >= 1 && i1 <=
            get_month_day_count(time.year(timeshift), i2))
         {
            iCount++;
         }
         if (iCount > 0)
         {
            if ((iCount == 1 && bFirst) || (iCount == 2 && (iPath % iCount) == 0))
            {
               i32 iDay = i2;
               i32 iMonth = i1;
               time = ::earth::time(time.year(timeshift), iMonth, iDay,
                  time.hour(timeshift), time.minute(timeshift), time.second(timeshift));
               time = ::earth::time(time.year(timeshift), time.month(timeshift), time.day(timeshift), 0, 0, 0);
            }
            else if ((iCount == 1 && !bFirst) || (iCount == 2 && (iPath % iCount) == 1))
            {
               i32 iDay = i1;
               i32 iMonth = i2;
               time = ::earth::time(time.year(timeshift), iMonth, iDay,
                  time.hour(timeshift), time.minute(timeshift), time.second(timeshift));
               time = ::earth::time(time.year(timeshift), time.month(timeshift), time.day(timeshift), 0, 0, 0);
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

         return result(time) + span_parse_time(pcontext, str.Mid(iStart));

      }
      else
      {

         return span_parse_time(pcontext, str.Mid(iStart));

      }

   }


   string datetime::to_string(const ::text::context* pcontext, const ::datetime::result& result, const ::earth::time_shift& timeshift)
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

               strItem.format("%d year", result.m_iYear);

            }
            else
            {

               strItem.format("%d years", result.m_iYear);

            }

            stra.add(strItem);

         }

         if (result.m_iMonth != 0)
         {

            if (abs(result.m_iMonth) == 1)
            {

               strItem.format("%d month", result.m_iMonth);

            }
            else
            {

               strItem.format("%d months", result.m_iMonth);

            }

            stra.add(strItem);

         }

         if (result.m_iDay != 0)
         {

            if (abs(result.m_iDay) == 1)
            {

               strItem.format("%d day", result.m_iDay);

            }
            else
            {

               strItem.format("%d days", result.m_iDay);


            }
            stra.add(strItem);

         }

         if (result.m_iHour != 0)
         {

            if (abs(result.m_iHour) == 1)
            {

               strItem.format("%d hour", result.m_iHour);

            }
            else
            {

               strItem.format("%d hours", result.m_iHour);

            }

            stra.add(strItem);

         }

         if (result.m_iMinute != 0)
         {

            if (abs(result.m_iMinute) == 1)
            {

               strItem.format("%d minute", result.m_iMinute);

            }
            else
            {

               strItem.format("%d minutes", result.m_iMinute);

            }

            stra.add(strItem);

         }

         if (result.m_iSecond != 0)
         {

            if (abs(result.m_iSecond) == 1)
            {

               strItem.format("%d second", result.m_iSecond);

            }
            else
            {

               strItem.format("%d seconds", result.m_iSecond);

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

         ::earth::time time = result.get_time();

         if (time.second(timeshift) == 0)
         {

            if (time.hour(timeshift) == 0 && time.minute(timeshift) == 0)
            {

               str = ::earth::format("%Y-", time, timeshift);

               get_month_str(pcontext, time.month(timeshift));

               str += ::earth::format("-%d", time, timeshift);

            }
            else
            {

               str = ::earth::format("%Y-", time, timeshift);

               str += get_month_str(pcontext, time.month(timeshift));

               str += ::earth::format("-%d %H:%M", time, timeshift);

            }

         }
         else
         {

            str = ::earth::format("%Y-", time, timeshift);

            str += get_month_str(pcontext, time.month(timeshift));

            str += ::earth::format("-%d %H:%M:%S", time, timeshift);

         }

      }

      return str;

   }


} // namespace datetime



