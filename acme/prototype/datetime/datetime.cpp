// From datetime to datetime by camilo on 2022-11-19 04:41 <3ThomasBorregaardSorensen!!
#include "framework.h" // from "base/apex/.h"
#include "datetime.h"
////#include "acme/exception/exception.h"
#include "acme/exception/not_implemented.h"
#include "acme/exception/parsing.h"
#include "acme/platform/system.h"
#include "acme/prototype/datetime/_string.h"
#include "acme/prototype/datetime/earth_gregorian_time.h"
//#include "acme/prototype/prototype/payload.h"
#include "acme/prototype/string/str.h"
#include "acme/prototype/text/context.h"
#include "acme/regular_expression/regular_expression.h"
#include "acme/regular_expression/result.h"


#include <time.h>


namespace datetime
{


   datetime::datetime()
   {

   }


   datetime::~datetime()
   {

   }

   ::earth::time datetime::from_string(const ::text::context* pcontext, const ::scoped_string & scopedstr, const class ::time & timeshift)
   {

      int iPathCount;

      return ::earth::time(strtotime(pcontext, scopedstr, 0, iPathCount, timeshift));

   }


   //::earth::time datetime::from_utc(const ::text::context* pcontext, const ::scoped_string & scopedstr)
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

      defer_create_synchronization();

      //if (!estatus)
      //{

      //   return estatus;

      //}
         
      ///*estatus = */ øconstruct_new(m_pinternational);

      //if (!estatus)
      //{

      //   return estatus;

      //}

//      /*estatus = */ øconstruct_new(m_pstr);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //m_pstr->m_pdatetime = this;

      //return estatus;

   }


   //void datetime::international::initialize(::particle * pparticle)
   //{

   //   /*auto estatus = */ ::object::initialize(pparticle);

   //   //if (!estatus)
   //   //{

   //   //   return estatus;

   //   //}

   //   //return estatus;

   //}


//   void datetime::str::initialize(::particle * pparticle)
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

      //m_pinternational.release();

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

   int datetime::get_month_day_count(int year, int month)
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
   int datetime::get_weekday(int year, int month, int day)
   {

      ::earth::time time(year, month, day, 0, 0, 0);

      return time.day_of_week();

   }


   long long datetime::get_timestamp(int year, int month, int day)
   {
      
      ::earth::time time(year, month, day, 0, 0, 0);

      return time.m_iSecond;

   }


   posix_time datetime::strtotime(const ::text::context * pcontext, const ::scoped_string & scopedstr, int iPath, int & iPathCount, const class ::time & timeshift)
   {

      if (scopedstr.trimmed().is_empty())
      {

         return {};

      }

      ::earth::time time;

      ::datetime::result val = parse_time(pcontext, scopedstr, iPath, iPathCount, timeshift);

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


   posix_time datetime::strtotime(const ::text::context * pcontext, const ::scoped_string & scopedstr, posix_time timeParam, int iPath, int & iPathCount, const class ::time& timeshift)
   {

      if (scopedstr.trimmed().is_empty())
      {

         return {};

      }

      __UNREFERENCED_PARAMETER(iPath);

      ::earth::time time(timeParam);

      iPathCount = 1;

      ::datetime::result val = ::datetime::result(time) + span_parse_time(pcontext, scopedstr);

      return val.get_time().get_time();

   }


   //long long datetime::utc_strtotime(const ::text::context * pcontext, const ::scoped_string & scopedstr, int iPath, int & iPathCount)
   //{

   //   if (::is_null(scopedstr) || string(scopedstr).trimmed().is_empty())
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


   //datetime::international::international()
   //{


   //}


   void datetime::parse_text(const ::scoped_string & scopedstrSrc, ::property_set & set)
   {
      
      string src(scopedstrSrc);

      src.trim();

      string str;

      if (src.length() >= 4)
      {

         str = src.substr(0, 4);

         str.trim_left('0');

         set["year"] = str;

      }
      else
      {
         
         set["year"] = 0;

      }
      
      if (src.length() >= 7)
      {

         str = src.substr(5, 2);

         str.trim_left('0');

         set["month"] = str;

      }
      else
      {
         
         set["month"] = 0;

      }

      if (src.length() >= 10)
      {
      
         str = src.substr(8, 2);

         str.trim_left('0');

         set["day"] = str;

      }
      else
      {
         
         set["day"] = 0;

      }

      if (src.length() >= 13)
      {
      
         str = src.substr(11, 2);
         
         str.trim_left('0');
         
         set["hour"] = str;

      }
      else
      {
         
         set["hour"] = 0;

      }

      if (src.length() >= 16)
      {
      
         str = src.substr(14, 2);
         
         str.trim_left('0');
         
         set["minute"] = str;

      }
      else
      {
         
         set["minute"] = 0;

      }

      if (src.length() >= 19)
      {
        
         str = src.substr(17, 2);

         str.trim_left('0');

         set["second"] = str;

      }
      else
      {
         
         set["second"] = 0;

      }

   }


   ::earth::time datetime::parse_text(const ::scoped_string & scopedstr)
   {

      ::property_set set;

      parse_text(scopedstr, set);

      auto year = set["year"].as_int();
      auto month = set["month"].as_int();
      auto day = set["day"].as_int();
      auto hour = set["hour"].as_int();
      auto minute = set["minute"].as_int();
      auto second = set["second"].as_int();

      if (year <= 0
         && month <= 0
         && day <= 0
         && hour <= 0
         && minute <= 0
         && second <= 0
         )
      {

         return {};

      }




      return { year, month, day, hour, minute, second };

   }


   ::posix_time datetime::parse(const ::scoped_string & scopedstrParam)
   {

      ::string str(scopedstrParam);

      str.trim();

      ::earth::gregorian_time gregoriantime{};

      if(character_isdigit(scopedstrParam[0])
         && character_isdigit(scopedstrParam[1])
         && character_isdigit(scopedstrParam[2])
         && character_isdigit(scopedstrParam[3])
         && character_isdigit(scopedstrParam[5])
         && character_isdigit(scopedstrParam[6])
         && character_isdigit(scopedstrParam[8])
         && character_isdigit(scopedstrParam[9]))
      {
         if (character_isdigit(scopedstrParam[11])
            && character_isdigit(scopedstrParam[12])
            && character_isdigit(scopedstrParam[14])
            && character_isdigit(scopedstrParam[15])
            && character_isdigit(scopedstrParam[17])
            && character_isdigit(scopedstrParam[18]))
         {
            gregoriantime.m_iSecond = atoi(scopedstrParam(17, 2));
            gregoriantime.m_iMinute = atoi(scopedstrParam(14, 2));
            gregoriantime.m_iHour = atoi(scopedstrParam(11, 2));

         }

         gregoriantime.m_iDay = atoi(scopedstrParam(8, 2));
         gregoriantime.m_iMonth = atoi(scopedstrParam(5, 2));
         gregoriantime.m_iYear = atoi(scopedstrParam(0, 4));
      }
      else
      {

         throw ::parsing_exception("not international date");

      }

      return gregoriantime.make_utc_time();

   }


   string datetime::format(const ::scoped_string& scopedstrFormat, const ::earth::time & time, const class ::time& timeshift)
   {
      
      string str;
      
      str = ::earth::format(scopedstrFormat, time, timeshift);
      
      return str;

   }


   //string datetime::international::date_time_text(const ::scoped_string & scopedstrFormat, const class ::time & timeshift)
   //{

   //   ::earth::time time;

   //   time = ::earth::time::now();

   //   return date_time_text(time, strFormat, timeshift);

   //}


   //string datetime::international::date_time_text_for_file(const class ::time & timeshift, const ::earth::time & time)
   //{

   //   return date_time_text(time, INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE, timeshift);

   //}


   //string datetime::international::date_text(const ::earth::time & time, const ::scoped_string & scopedstrFormat, const class ::time & timeshift)
   //{

   //   string str;

   //   str = ::earth::format(strFormat, time, timeshift);

   //   return str;

   //}


   //string datetime::international::date_text(const ::scoped_string & scopedstrFormat, const class ::time & timeshift)
   //{

   //   ::earth::time time;

   //   time = ::earth::time::now();

   //   return date_text(time, strFormat, timeshift);

   //}


   //string datetime::international::date_text_for_file(const class ::time & timeshift, const ::earth::time & time)
   //{

   //   return date_text(time, INTERNATIONAL_DATE_FORMAT_FOR_FILE, timeshift);

   //}






   //string datetime::international::utc_get_date_time(const ::scoped_string & scopedstrFormat)
   //{

   //   ::earth::time time;

   //   time = ::earth::time::now();

   //   return utc_get_date_time(time, strFormat);

   //}




   //string datetime::international::get_date_time(const ::earth::time & time, const ::scoped_string & scopedstrFormat, const class ::time& timeshift)
   //{
   //   
   //   string str;
   //   
   //   str = ::datetime::local_format(strFormat, time);

   //   return str;

   //}


   //string datetime::international::get_date_time_for_file(const class ::time& timeshift)
   //{

   //   return get_date_time(INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE, timeshift);

   //}


   //string datetime::international::get_date_time_for_file_with_no_spaces(const class ::time& timeshift, const ::earth::time & time)
   //{

   //   string str = date_time_text_for_file(timeshift, time);

   //   str.replace_with("_", " ");

   //   return str;

   //}


   //string datetime::international::get_date_time_for_file_with_no_spaces(const class ::time& timeshift)
   //{

   //   string str = get_date_time_for_file(timeshift);

   //   str.replace(" ", "_");

   //   return str;

   //}


//   datetime::str::str()
//   {
//      
//      m_pdatetime = nullptr;
//
//   }
//
//
//   string datetime::str::get_date_time(const class ::time& timeshift)
//   {
//
//      return m_pdatetime->date_time_text(::earth::time::now(), timeshift);
//
//   }
//

   posix_time datetime::s_mktime(int iHour, int iMinute, int iSecond, int iMonth, int iDay, int iYear, const class ::time& timeshift)
   {

       earth::gregorian_time time;

       time.m_iHour = iHour;
       time.m_iMinute = iMinute;
       time.m_iSecond = iSecond;
       time.m_iMonth = iMonth -1;
       time.m_iDay = iDay;
       time.m_iYear = iYear;

      auto posixtime = time.make_utc_time();

      return posixtime - timeshift;

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


   //posix_time datetime::s_utc_mktime(int iHour, int iMinute, int iSecond, int iMonth, int iDay, int iYear)
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


   string datetime::get_week_day_str(const ::text::context * pcontext, int iWeekDay) // 1 - domingo
   {
      
      return system()->texttable()->get(pcontext, "datetimestr_weekday_long[" + ::as_string(iWeekDay - 1) + "]");

   }


   string datetime::get_tiny_week_day_str(const ::text::context * pcontext, int iWeekDay) // 1 - domingo
   {

      ::string str;

      if(system()->texttable()->_get(str,  pcontext, "datetimestr_weekday_tiny[" + ::as_string(iWeekDay - 1) + "]"))
      {
      
         return str;
      
      }

      switch (iWeekDay)
      {
      case 1:
         return "M";
      case 2:
         return "T";
      case 3:
         return "W";
      case 4:
         return "T";
      case 5:
         return "F";
      case 6:
         return "S";
      case 7:
         return "S";
      default:
         return "";
      }

   }


   string datetime::get_month_str(const ::text::context * pcontext, int iMonth)
   {

      ::string str;
   
      if (system()->texttable()->_get(str, pcontext, "datetimestr_month[" + ::as_string(iMonth - 1) + "]"))
      {

         return str;

      }

      switch (iMonth)
      {
      case 1:
         return "January";
      case 2:
         return "February";
      case 3:
         return "March";
      case 4:
         return "April";
      case 5:
         return "May";
      case 6:
         return "June";
      case 7:
         return "July";
      case 8:
         return "August";
      case 9:
         return "September";
      case 10:
         return "October";
      case 11:
         return "November";
      case 12:
         return "December";
      default:
         return "";
      }

   }


   string datetime::get_short_month_str(const ::text::context * pcontext, int iMonth)
   {

      return system()->texttable()->get(pcontext, "datetimestr_month_short[" + ::as_string(iMonth - 1) + "]");

   }


   //::earth::time datetime::from_date_time(int iYear, int iMonth, int iDay, int iHour, int iMinute, int iSecond)
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
   int datetime::SWN(int y, int m, int d)
   {
      return 1 + (DP(y, m) + d - 1) / 7;
   }

   //where DP ("Days Passed") is given by:
   //   DP( y, 1 ) = 0
   //  DP( y, m+1 ) = DP( y, m ) + ML( y, m )
   int datetime::DP(int y, int m)
   {
      if (m == 1)
         return 0;
      else
         return DP(y, m - 1) + ML(y, m - 1);
   }

   int datetime::ML(int y, int m)
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

   int datetime::LEAP(int y)
   {
      if ((y % 4 == 0) && ((y % 100 != 0) || (y % 400 == 0)))
         return 1;
      else
         return 0;
   }


   // Use this elegant code by Tomohiko Sakamoto:

   int datetime::dayofweek(int y, int m, int d)	/* 0 = Sunday */
   {
      static int t[] = { 0,3,2,5,0,3,5,1,4,6,2,4 };
      y -= m < 3;
      return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
   }

   int datetime::SDOW(int y, int m, int d) // ( 0 = Monday, ..., 6 = Sunday )
   {
      return (DP(y, m) + d - 1) % 7;
   }


   int datetime::DOW(int y, int m, int d)
   {
      //return SDOW(y, m, d);
      return getDayOfWeek(m, d, y, 0);
   }


   int datetime::getDayOfWeek(int month, int day, int year, int CalendarSystem)
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
             + int(6 * (month + 1) / 10)
             + year
             + int(year / 4)
             - int(year / 100)
             + int(year / 400)
             + CalendarSystem
             ) % 7;
   }

   /*In [ISO8601], the week number is defined by:

   weeks start on a monday
   week 1 of a given year is the one that includes the first Thursday of that year. (or, equivalently, week 1 is the week that includes 4 January.)

   This means that the days before week 1 in a given year are attributed to the last week of the previous year. Also the days that come after the last week of a given year are attributed to the first week of the next year.

   If we adapt approximation SWN5 for the simple week number to reflect the differences between the definitions of both week numbers, we arrive at the final solution, adopted for the week number wristapp:
   */
   /*int ISO_WN(int  y, int m, int d, int dow, int dow0101 )
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


   int datetime::ISO_WN(int  y, int m, int d)
   {
      int dow = DOW(y, m, d);
      int dow0101 = DOW(y, 1, 1);

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


   //string datetime::format(const ::scoped_string & scopedstrFormatParam, const ::earth::time & time, const class ::time & timeshift)
   //{

   //   string strFormat(strFormatParam);

   //   string str;

   //   auto pFind = strFormat.find("%V");

   //   if (::is_set(pFind))
   //   {

   //      string strV;

   //      strV.formatf("%02d", ISO_WN(time.year(timeshift), time.month(timeshift), time.day(timeshift)));

   //      strFormat.replace_with(strV, "%V");

   //   }

   //   str = ::earth::format(strFormat, time, timeshift);

   //   return str;

   //}


   //string datetime::format(const ::scoped_string & scopedstr, const class ::time& timeshift)
   //{

   //   return format(str, ::earth::time::now(), timeshift);

   //}


   //string datetime::strftime(const ::scoped_string & scopedstr, const ::earth::time & time, const class ::time& timeshift)
   //{

   //   string strFormat(scopedstr);

   //   string str;

   //   auto pFind = strFormat.find("%V");

   //   if (::is_set(pFind))
   //   {

   //      string strV;
   //      
   //      strV.formatf("%02d", ISO_WN(time.utc_year(), time.utc_month(), time.utc_day()));

   //      strFormat.replace("%V", strV);

   //   }

   //   str = ::datetime::utc_format(strFormat, time);

   //   return str;

   //}


   //string datetime::utc_strftime(const ::scoped_string & scopedstr)
   //{
   //   
   //   return utc_strftime(scopedstr, ::earth::time::now());
   //   
   //}


   string datetime::friend_time(const ::text::context * pcontext, ::earth::time timeNow, ::earth::time time, const class ::time& timeshift)
   {
      bool bDiff = false;
      bool bSolved = false;
      string strTime;
      string str;
      long long iSecDiff = (timeNow - time).seconds();
      long long iMinDiff = (timeNow - time).minutes();
      long long iHouDiff = (timeNow - time).hours();
      if (iSecDiff <= 59)
      {
         bSolved = true;
         strTime.formatf("about %d seconds ago", (timeNow - time).seconds());
      }
      else if (iMinDiff <= 59)
      {
         bSolved = true;
         if (iMinDiff <= 1)
         {
            strTime = pcontext->get("about 1 minute and %SECONDS% seconds ago");
            strTime.replace_with(::as_string((timeNow - time).second()), "%SECONDS%");
         }
         else if (iMinDiff <= 2)
         {
            strTime = pcontext->get("about 2 minutes and %SECONDS% seconds ago");
            strTime.replace_with(::as_string((timeNow - time).second()), "%SECONDS%");
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
            strTime.formatf("about 1 hour and %d minutes ago", (timeNow - time).minute());
         }
         else if (iHouDiff <= 2)
         {
            strTime.formatf("about 2 hours and %d minutes ago", (timeNow - time).minute());
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
            str.formatf("%04d", time.year(timeshift));
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
            str.formatf("%02d", time.day());
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
            str.formatf("%02d", time.hour(timeshift));
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
               str.formatf("%02d", time.minute(timeshift));
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
               str.formatf("%02d", time.second(timeshift));
               strTime += ":" + str;
            }
            else
            {

            }

         }

      }

      return strTime;

   }









   string datetime::_001FriendTime(const ::text::context* pcontext, const ::earth::time& timeNow, const ::earth::time& time, const class ::time& timeshift)
   {

      bool bDiff = false;
      bool bSolved = false;
      string strTime;
      string str;
      long long iSecDiff = (timeNow - time).seconds();
      long long iMinDiff = (timeNow - time).minutes();
      long long iHouDiff = (timeNow - time).hours();
      if (iSecDiff <= 59)
      {
         bSolved = true;
         //strTime.formatf("about %d seconds ago", (timeNow - time).GetTotalSeconds());
         strTime.formatf("%ds", (timeNow - time).seconds());
      }
      else if (iMinDiff <= 59)
      {
         bSolved = true;
         if (iMinDiff <= 1)
         {
            //strTime = pscript->pstr("about 1 minute and %SECONDS% seconds ago");
            //strTime = pscript->pstr("1m %SECONDS%s seconds ago");
            strTime.formatf("1m %ds", (timeNow - time).second());
         }
         else if (iMinDiff <= 2)
         {
            //strTime = pscript->pstr("about 2 minutes and %SECONDS% seconds ago");
            //strTime = pscript->pstr("2 minutes and %SECONDS% seconds ago");
            strTime.formatf("2m %ds", (timeNow - time).second());
         }
         else
         {
            //strTime = pscript->pstr("about %MINUTES% minutes ago");
            //strTime = pscript->pstr("%MINUTES% minutes ago");
            strTime.formatf("%dm", iMinDiff);
         }
      }
      else if (iHouDiff <= 24)
      {
         bSolved = true;
         if (iHouDiff <= 1)
         {
            //strTime.formatf("about 1 hour and %d minutes ago", (timeNow - time).GetMinutes());
            strTime.formatf("1h %dm", (timeNow - time).minute());

         }
         else if (iHouDiff <= 2)
         {
            //strTime.formatf("about 2 hours and %d minutes ago", (timeNow - time).GetMinutes());
            strTime.formatf("2h %dm", (timeNow - time).minute());
         }
         else
         {
            //strTime = pscript->pstr("about %HOURS% hours ago");
            //strTime = pscript->pstr("%HOURS% hours ago");
            strTime.formatf("%dh", iHouDiff);
         }
      }
      else
      {
         if (!bSolved && timeNow.year(timeshift) != time.year(timeshift))
         {
            bDiff = true;
            str.formatf("%04d", time.year(timeshift));
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

               string_array_base straWeekDay;

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
               str.formatf("%dd, time.GetGmtDay()");

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
            str.formatf("%02d", time.hour(timeshift));
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
               
               str.formatf("%02d", time.minute(timeshift));
               
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
               
               str.formatf("%02d", time.second(timeshift));

               strTime += ":" + str;

            }
            else
            {

            }

         }

      }

      return strTime;

   }


   ::string datetime::friendly_elapsed(const class ::time& time)
   {

      ::string str;

      auto iSeconds = time.integral_second();

      if (iSeconds < 60)
      {

         str.formatf("%llds", iSeconds);

      }
      else
      {

         auto secs = iSeconds % 60;

         auto iMinutes = iSeconds / 60;

         if (iMinutes < 60)
         {

            str.formatf("%lld minutes %llds", iMinutes, secs);

         }
         else
         {

            auto mins = iMinutes % 60;

            auto iHours = iMinutes / 60;

            if (iHours < 24)
            {

               str.formatf("%lld hours %lld minutes %llds", iHours, mins, secs);

            }
            else
            {
               
               auto hours = iHours % 24;

               auto iDays = iHours / 24;

               str.formatf("%lld days %lld hours %lld minutes %llds", iDays, hours, mins, secs);

            }

         }

      }

      return str;

   }



} // namespace datetime


#include "framework.h"
#include <time.h>

#ifndef WINDOWS

#include <sys/time.h>

#endif



namespace datetime
{


   result datetime::span_parse_time(const ::text::context* pcontext, const ::scoped_string & scopedstrSpanExpression, const class ::time & timeshift)
   {

      static auto idCalendarDay("calendar:day");
      static auto idCalendarDays("calendar:days");
      static auto idCalendarWeek("calendar:week");
      static auto idCalendarWeeks("calendar:weeks");
      static auto idCalendarYear("calendar:year");
      static auto idCalendarYears("calendar:years");
      static auto idCalendarHour("calendar:hour");
      static auto idCalendarHours("calendar:hours");
      static auto idCalendarNow("calendar:now");

      result time;
      time.m_bSpan = true;
      string str(scopedstrSpanExpression);
      str.trim();
      str += " ";
      ::property_set set;
      bool bAdd = false;
      bool bMinus = false;
      const_char_pointer psz = str.c_str();
      string strNumber;
      string strText1;
      string strChar;
      for (int i = 0; *psz; psz += strChar.length())
      {
         strChar = get_utf8_char(psz);
         if (unicode_is_whitespace(psz))
         {
            i++;
            //if(strNumber.has_character() && strText.has_character())
            //{
            //}
            if ((bAdd || bMinus) && strNumber.has_character() && strText1.has_character())
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
               strNumber.empty();
               strText1.empty();
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

#ifdef _DEBUG

            if (bAdd)
            {
               information() << "strtotime: invalid char +";
            }
            else if (bMinus)
            {
               information() << "strtotime: invalid char + on Minus state";
            }

#endif

            bAdd = true;
            bMinus = false;
            strNumber.empty();
         }
         else if (strChar == "-")
         {

#ifdef _DEBUG

            if (bAdd)
            {
               
               information() << "strtotime: invalid char - on add state";

            }
            else if (bMinus)
            {
               
               information() << "strtotime: invalid char - on Minus state";

            }

#endif

            bAdd = false;
            bMinus = true;
            strNumber.empty();
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
   void parse_br_str(const ::scoped_string & scopedstr, ::property_set & set)
   {
      string src(scopedstr);
      src.trim();
      string str;
      if (src.length() >= 2)
      {
         str = src.substr(0, 2);
         str.trim_left('0');
         set["day"] = str;
      }
      else
      {
         set["day"] = 0;
      }
      if (src.length() >= 5)
      {
         str = src.substr(3, 2);
         str.trim_left('0');
         set["month"] = str;
      }
      else
      {
         set["month"] = 0;
      }
      if (src.length() >= 10)
      {
         str = src.substr(6, 4);
         str.trim_left('0');
         set["year"] = str;
      }
      else
      {
         set["year"] = 0;
      }
      if (src.length() >= 13)
      {
         str = src.substr(11, 2);
         str.trim_left('0');
         set["hour"] = str;
      }
      else
      {
         set["hour"] = 0;
      }
      if (src.length() >= 16)
      {
         str = src.substr(14, 2);
         str.trim_left('0');
         set["minute"] = str;
      }
      else
      {
         set["minute"] = 0;
      }
      if (src.length() >= 19)
      {
         str = src.substr(17, 2);
         str.trim_left('0');
         set["second"] = str;
      }
      else
      {
         set["second"] = 0;
      }
   }


   result datetime::parse_time(const ::text::context* pcontext, const ::scoped_string & scopedstrParam, int& iPath, int& iPathCount, const class ::time& timeshift)
   {
      ::earth::time time;
      string str(scopedstrParam);
      str.trim();
      str += " ";
      ::property_set set;
      bool bBaseTime = false;
      int iStart = 0;

      // if is international date time 2009-04-31 21:45:59
      // or
      // if is international date time 2009-04-31 21:45
      if (str.length() >= 16)
      {

         if (((str.substr(4, 1) == "-") || (str.substr(4, 1) == ":"))
            && ((str.substr(7, 1) == "-") || (str.substr(7, 1) == ":"))
            && str.substr(10, 1) == " "
            && str.substr(13, 1) == ":")
         {

            bBaseTime = true;
            
            //auto pdatetime = datetime();

            parse_text(str, set);

            string strWord = str.substr(19);
            strWord.trim_left();
            strWord = ::str::get_word(strWord, " ");
            if (strWord.case_insensitive_order("UTC") == 0
               || strWord.case_insensitive_order("GMT") == 0)
            {

//               struct tm atm;
//
//               atm.tm_sec = set["second"].as_int();
//               atm.tm_min = set["minute"].as_int();
//               atm.tm_hour = set["hour"].as_int();
//               atm.tm_mday = set["day"].as_int();
//               atm.tm_mon = set["month"].as_int() - 1;        // tm_mon is 0 based
//               atm.tm_year = set["year"].as_int() - 1900;     // tm_year is 1900 based
//               atm.tm_isdst = -1;
//               /*posix_time now = _time64(nullptr);
//               posix_time nowUtc = mktime(gmtime(&now));
//               posix_time tDiff = difftime(nowUtc, now);*/
//               time = ::earth::time(::earth::make_utc_time(&atm));
                time = ::earth::time(
                        set["year"].as_int(),
                        set["month"].as_int(),
                        set["day"].as_int(),
                        set["hour"].as_int(),
                        set["minute"].as_int(),
                        set["second"].as_int());

            }
            else
            {

               time = ::earth::time(
                  set["year"].as_int(),
                  set["month"].as_int(),
                  set["day"].as_int(),
                  set["hour"].as_int(),
                  set["minute"].as_int(),
                  set["second"].as_int(), ::time::local());

            }

            iStart = 20;

         }
      }
      // if is international date time 2009-04-31
      if (!bBaseTime && str.length() >= 10)
      {
         if (str.substr(4, 1) == "-"
            && str.substr(7, 1) == "-")
         {
            bBaseTime = true;

            parse_text(str, set);

            time = ::earth::time(
               set["year"].as_int(),
               set["month"].as_int(),
               set["day"].as_int(),
               set["hour"].as_int(),
               set["minute"].as_int(),
               set["second"].as_int());
            iStart = 11;
         }
      }
      // if is international date time 31/04/2011
      if (!bBaseTime && str.length() >= 10)
      {
         if (str.substr(2, 1) == "/"
            && str.substr(5, 1) == "/")
         {
            bBaseTime = true;
            parse_br_str(str, set);

            time = ::earth::time(
               set["year"].as_int(),
               set["month"].as_int(),
               set["day"].as_int(),
               set["hour"].as_int(),
               set["minute"].as_int(),
               set["second"].as_int());
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

      string_array_base stra;

      auto pdatetime = datetime();

      auto pcre1 = system()->compile_pcre("^\\s*((\\d+)\\s*/\\s*(\\d+))((\\d|$)?!)");

      auto presult = pcre1->run(str);

      if (!bBaseTime && presult && presult->get_count() >= 5)
      {

         time = ::earth::time::now();

         int i1 = atoi(presult->get_match(2).c_str());

         int i2 = atoi(presult->get_match(3).c_str());

         int iCount = 0;

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
               int iDay = i2;
               int iMonth = i1;
               time = ::earth::time(time.year(timeshift), iMonth, iDay,
                  time.hour(timeshift), time.minute(timeshift), time.second(timeshift));
               time = ::earth::time(time.year(timeshift), time.month(timeshift), time.day(timeshift), 0, 0, 0);
            }
            else if ((iCount == 1 && !bFirst) || (iCount == 2 && (iPath % iCount) == 1))
            {
               int iDay = i1;
               int iMonth = i2;
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

         if (str.substr(iStart).trimmed().size() == 0)
         {

            return result(time);

         }

         return result(time) + span_parse_time(pcontext, str.substr(iStart));

      }
      else
      {

         return span_parse_time(pcontext, str.substr(iStart));

      }

   }


   string datetime::to_string(const ::text::context* pcontext, const ::datetime::result& result, const class ::time& timeshift)
   {

      string str;

      if (result.m_bSpan)
      {

         string_array_base stra;

         string strItem;

         if (result.m_iYear != 0)
         {

            if (abs(result.m_iYear) == 1)
            {

               strItem.formatf("%d year", result.m_iYear);

            }
            else
            {

               strItem.formatf("%d years", result.m_iYear);

            }

            stra.add(strItem);

         }

         if (result.m_iMonth != 0)
         {

            if (abs(result.m_iMonth) == 1)
            {

               strItem.formatf("%d month", result.m_iMonth);

            }
            else
            {

               strItem.formatf("%d months", result.m_iMonth);

            }

            stra.add(strItem);

         }

         if (result.m_iDay != 0)
         {

            if (abs(result.m_iDay) == 1)
            {

               strItem.formatf("%d day", result.m_iDay);

            }
            else
            {

               strItem.formatf("%d days", result.m_iDay);


            }
            stra.add(strItem);

         }

         if (result.m_iHour != 0)
         {

            if (abs(result.m_iHour) == 1)
            {

               strItem.formatf("%d hour", result.m_iHour);

            }
            else
            {

               strItem.formatf("%d hours", result.m_iHour);

            }

            stra.add(strItem);

         }

         if (result.m_iMinute != 0)
         {

            if (abs(result.m_iMinute) == 1)
            {

               strItem.formatf("%d minute", result.m_iMinute);

            }
            else
            {

               strItem.formatf("%d minutes", result.m_iMinute);

            }

            stra.add(strItem);

         }

         if (result.m_iSecond != 0)
         {

            if (abs(result.m_iSecond) == 1)
            {

               strItem.formatf("%d second", result.m_iSecond);

            }
            else
            {

               strItem.formatf("%d seconds", result.m_iSecond);

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


::string datetime::elapsed_nanoseconds_text(long long iNanoseconds)
{

   ::string str;

   if(iNanoseconds > 1'000'000)
   {

      str.formatf("%0.6f ms", (double) iNanoseconds / 1'000'000.);

   }
   else if(iNanoseconds > 1'000)
   {

      str.formatf("%0.3d μs", (double) iNanoseconds / 1'000.);

   }
   else
   {

      str.formatf("%d ηs", (int) (iNanoseconds));

   }

   return str;

}


::string datetime::elapsed_time_text(const class ::time & time)
{


   auto iSeconds = time.m_iSecond;
   auto iSecond = iSeconds % 60;
   auto iMinutes = iSeconds / 60;
   auto iMinute = iMinutes % 60;
   auto iHours = iMinutes / 60;
   auto iHour = iHours % 24;
   auto iDays = iHours / 24;

   ::string_array_base stra;

   if(iDays > 0)
   {

      stra.append_formatf("%d day(s)", iDays);

   }

   if(iHour > 0)
   {

      stra.append_formatf("%d hour(s)", iHour);

   }

   if(iMinute > 0)
   {

      stra.append_formatf("%d minute(s)", iMinute);

   }

   if(iSecond > 0)
   {

      stra.append_formatf("%d second(s)", iSecond);

   }

   if(time.m_iNanosecond > 0)
   {

      stra.add(elapsed_nanoseconds_text(time.m_iNanosecond));

   }

   return stra._008Implode(", ", " and ");

}



} // namespace datetime


CLASS_DECL_ACME::earth::time earth_time_from_international_string(const ::scoped_string& scopedstrTime)
{

   auto range = scopedstrTime();

   range.trim();

   if (::character_isalnum(range[4])
      || ::character_isalnum(range[7])
      || ::character_isalnum(range[10])
      || ::character_isalnum(range[13])
      || ::character_isalnum(range[16]))
   {

      throw ::exception(error_bad_argument);

   }

   //       2007-12-03 17-23-24
   int iYear = atoi(range(0, 4));
   int iMonth = atoi(range(5, 2));
   int iDay = atoi(range(8, 2));

   int iHour = atoi(range(11, 2));
   int iMinute = atoi(range(14, 2));
   int iSecond = atoi(range(17, 2));

   return { iYear, iMonth, iDay, iHour, iMinute, iSecond, ::earth::time({posix_time_t{}, 0}) };

}



