#include "framework.h"
#include "acme/_operating_system.h"
#include <time.h>

#ifndef WINDOWS

#include <sys/time.h>

#endif



#if 0


extern "C" CLASS_DECL_ACME posix_time timegm(struct tm *tmp)
{

   static posix_time gmtime_offset;

   tmp->tm_isdst = 0;

   return __mktime_internal(tmp,gmtime_r,&gmtime_offset);

}


#endif




#ifdef ANDROID

posix_time timegm(tm * ptm)
{

   posix_time t1 = 60 * 60 * 24 * 2; // (sec * minimum * hours) * (safety 2 days); // 1970-01-03 00:00:00 +0000 (UTC).

   tm tm1;

   gmtime_r(&t1,&tm1);

   posix_time t2 = mktime(&tm1); // in reverse in Brazil (UTC -3) 1970-01-03 03:00:00 +0000

   posix_time t3 = mktime(ptm); // now (in Brazil) direct (UTC -3)

   return t3 - t2 + t1;

}

#endif


namespace datetime
{
//
//
//   value span_strtotime(::particle * pparticle, const ::text::context * pcontext, const ::scoped_string & scopedstrSpanExpression)
//   {
//
//      static auto idCalendarDay("calendar:day");
//      static auto idCalendarDays("calendar:days");
//      static auto idCalendarWeek("calendar:week");
//      static auto idCalendarWeeks("calendar:weeks");
//      static auto idCalendarYear("calendar:year");
//      static auto idCalendarYears("calendar:years");
//      static auto idCalendarHour("calendar:hour");
//      static auto idCalendarHours("calendar:hours");
//      static auto idCalendarNow("calendar:now");
//      __UNREFERENCED_PARAMETER(pparticle);
//      value time;
//      time.m_bSpan = true;
//      string str(pszSpanExpression);
//      str.trim();
//      str += " ";
//      property_set set;
//      bool bAdd = false;
//      bool bMinus = false;
//      const ::scoped_string & scopedstr = str;
//      string strNumber;
//      string strText1;
//      for(int i = 0; *psz; unicode_increment(psz))
//      {
//         string strChar = ::str::get_utf8_char(psz);
//         if(unicode_is_whitespace(psz))
//         {
//            i++;
//            //if(strNumber.has_character() && strText.has_character())
//            //{
//            //}
//            if((bAdd || bMinus) && strNumber.has_character() && strText1.has_character())
//            {
//               value span;
//               span.m_bSpan = true;
//               if(strText1 == "day" || strText1 == "days" || strText1 == "dia" || strText1 == "dias"
//                     || (pcontext != nullptr && pcontext->matches(idCalendarDay,strText1))
//                     || (pcontext != nullptr && pcontext->matches(idCalendarDays,strText1)))
//               {
//                  span.m_iDay = atoi(strNumber);
//               }
//               else if(strText1 == "week" || strText1 == "weeks"
//                       || (pcontext != nullptr && pcontext->matches(idCalendarWeek,strText1))
//                       || (pcontext != nullptr && pcontext->matches(idCalendarWeeks,strText1)))
//               {
//                  span.m_iDay = atoi(strNumber) * 7;
//               }
//               else if(strText1 == "hour" || strText1 == "hours" || strText1 == "hora" || strText1 == "horas"
//                       || (pcontext != nullptr && pcontext->matches(idCalendarHour,strText1))
//                       || (pcontext != nullptr && pcontext->matches(idCalendarHour,strText1)))
//               {
//                  span.m_iHour = atoi(strNumber);
//               }
//               else if(strText1 == "year" || strText1 == "years"
//                       || (pcontext != nullptr && pcontext->matches(idCalendarYear,strText1))
//                       || (pcontext != nullptr && pcontext->matches(idCalendarYears,strText1)))
//               {
//                  span.m_iYear = atoi(strNumber);
//               }
//               else if(strText1 == "now"
//                       || (pcontext != nullptr && pcontext->matches(idCalendarNow,strText1)))
//               {
//                  throw ::exception(::exception("now cannot be span"));
//               }
//               else if (strText1.case_insensitive_order("UTC") == 0)
//               {
//
//               }
//               else
//               {
//                  throw ::not_implemented();
//               }
//               strNumber.empty();
//               strText1.empty();
//               if(bAdd)
//               {
//                  time = time + span;
//                  bAdd = false;
//               }
//               else
//               {
//                  time = time - span;
//                  bMinus = false;
//               }
//            }
//            continue;
//         }
//         else if(strChar == "+")
//         {
//
//#ifdef _DEBUG
//
//            if(bAdd)
//            {
//               informationf("strtotime: invalid char +");
//            }
//            else if(bMinus)
//            {
//               informationf("strtotime: invalid char + on Minus state");
//            }
//
//#endif
//
//            bAdd = true;
//            bMinus = false;
//            strNumber.empty();
//         }
//         else if(strChar == "-")
//         {
//
//#ifdef _DEBUG
//
//            if(bAdd)
//            {
//               informationf("strtotime: invalid char - on add state");
//            }
//            else if(bMinus)
//            {
//               informationf("strtotime: invalid char - on Minus state");
//            }
//
//#endif
//
//            bAdd = false;
//            bMinus = true;
//            strNumber.empty();
//         }
//         else if(unicode_is_digit(psz))
//         {
//            strNumber += strChar;
//         }
//         else if(unicode_is_letter(psz))
//         {
//            strText1 += strChar;
//         }
//      }
//      return time;
//   }
//   void parse_br_str(const ::scoped_string & scopedstr,property_set & set)
//   {
//      string src(psz);
//      src.trim();
//      string str;
//      if(src.length() >= 2)
//      {
//         str = src.substr(0,2);
//         str.trim_left('0');
//         set["day"] = str;
//      }
//      else
//      {
//         set["day"]    = 0;
//      }
//      if(src.length() >= 5)
//      {
//         str = src.substr(3,2);
//         str.trim_left('0');
//         set["month"] = str;
//      }
//      else
//      {
//         set["month"] = 0;
//      }
//      if(src.length() >= 10)
//      {
//         str = src.substr(6,4);
//         str.trim_left('0');
//         set["year"] = str;
//      }
//      else
//      {
//         set["year"] = 0;
//      }
//      if(src.length() >= 13)
//      {
//         str = src.substr(11,2);
//         str.trim_left('0');
//         set["hour"] = str;
//      }
//      else
//      {
//         set["hour"] = 0;
//      }
//      if(src.length() >= 16)
//      {
//         str = src.substr(14,2);
//         str.trim_left('0');
//         set["minute"] = str;
//      }
//      else
//      {
//         set["minute"] = 0;
//      }
//      if(src.length() >= 19)
//      {
//         str = src.substr(17,2);
//         str.trim_left('0');
//         set["second"]  = str;
//      }
//      else
//      {
//         set["second"]   = 0;
//      }
//   }
//
//
//   value strtotime(::particle * pparticle, const ::text::context * pcontext,const ::scoped_string & scopedstr,int & iPath,int & iPathCount,bool bUTC)
//   {
//      ::earth::time time;
//      string str(psz);
//      str.trim();
//      str += " ";
//      property_set set;
//      bool bBaseTime = false;
//      int iStart = 0;
//
//      // if is international date time 2009-04-31 21:45:59
//      // or
//      // if is international date time 2009-04-31 21:45
//      if(str.length() >= 16)
//      {
//         if(((str.substr(4,1) == "-") || (str.substr(4, 1) == ":"))
//               && ((str.substr(7,1) == "-") || ( str.substr(7, 1) == ":"))
//               && str.substr(10,1) == " "
//               && str.substr(13,1) == ":")
//         {
//            bBaseTime = true;
//            Sys(pparticle).datetime().parse_text(str,set);
//            string strWord = str.substr(19);
//            strWord.trim_left();
//            strWord = ::str::get_word(strWord," ");
//            if(strWord.case_insensitive_order("UTC") == 0
//                  || strWord.case_insensitive_order("GMT") == 0
//                  || bUTC)
//            {
//               struct tm atm;
//               atm.tm_sec = set["second"];
//               atm.tm_min = set["minute"];
//               atm.tm_hour = set["hour"];
//               atm.tm_mday = set["day"].as_int();
//               atm.tm_mon = set["month"].as_int() - 1;        // tm_mon is 0 based
//               atm.tm_year = set["year"].as_int() - 1900;     // tm_year is 1900 based
//               atm.tm_isdst = -1;
//               /*posix_time now = _time64(nullptr);
//               posix_time nowUtc = mktime(gmtime(&now));
//               posix_time tDiff = difftime(nowUtc, now);*/
//#ifdef WINDOWS
//               time = ::earth::time(_mkgmtime64(&atm));
//#else
//               time = ::earth::time(timegm(&atm));
//#endif
//            }
//            else
//            {
//               time = ::earth::time(
//                      set["year"],
//                      set["month"],
//                      set["day"],
//                      set["hour"],
//                      set["minute"],
//                      set["second"]);
//            }
//            iStart = 20;
//         }
//      }
//      // if is international date time 2009-04-31
//      if(!bBaseTime && str.length() >= 10)
//      {
//         if(str.substr(4,1) == "-"
//               && str.substr(7,1) == "-")
//         {
//            bBaseTime = true;
//            Sys(pparticle).datetime().parse_text(str,set);
//            time = ::earth::time(
//                   set["year"],
//                   set["month"],
//                   set["day"],
//                   set["hour"],
//                   set["minute"],
//                   set["second"]);
//            iStart = 11;
//         }
//      }
//      // if is international date time 31/04/2011
//      if(!bBaseTime && str.length() >= 10)
//      {
//         if(str.substr(2,1) == "/"
//               && str.substr(5,1) == "/")
//         {
//            bBaseTime = true;
//            parse_br_str(str,set);
//
//            time = ::earth::time(
//                   set["year"],
//                   set["month"],
//                   set["day"],
//                   set["hour"],
//                   set["minute"],
//                   set["second"]);
//            iStart = 11;
//         }
//      }
//      if(!bBaseTime && (
//            str.begins_eat("today") ||
//            (pcontext != nullptr && pcontext->begins_eat(str,"calendar:today"))))
//      {
//         time = ::earth::time::now();
//         time = ::earth::time(time.GetYear(),time.GetMonth(),time.GetDay(),0,0,0);
//         bBaseTime = true;
//      }
//      if(!bBaseTime && (
//            str.begins_eat("tomorrow") ||
//            (pcontext != nullptr && pcontext->begins_eat(str,"calendar:tomorrow"))))
//      {
//         time = ::earth::time::now();
//         time = ::earth::time(time.GetYear(),time.GetMonth(),time.GetDay(),0,0,0);
//         time += ::earth::time_span(1,0,0,0);
//         bBaseTime = true;
//      }
//      if(!bBaseTime && (
//            str.begins_eat("yesterday") ||
//            (pcontext != nullptr && pcontext->begins_eat(str,"calendar:yesterday"))))
//      {
//         time = ::earth::time::now();
//         time = ::earth::time(time.GetYear(),time.GetMonth(),time.GetDay(),0,0,0);
//         time -= ::earth::time_span(1,0,0,0);
//         bBaseTime = true;
//      }
//      if(!bBaseTime && (
//            str.begins_eat("now") ||
//            (pcontext != nullptr && pcontext->begins_eat(str,"calendar:now"))))
//      {
//         
//         time = ::earth::time::now();
//         
//         bBaseTime = true;
//
//      }
//
//      string_array stra;
//
//      auto pcre1 = system()->create_regular_expression("pcre", "^\\s*((\\d+)\\s*/\\s*(\\d+))((\\d|$)?!)");
//
//      if(!bBaseTime && pcre1->matches(stra, str) >= 5)
//      {
//         time = ::earth::time::now();
//         int i1 = atoi(stra[2]);
//         int i2 = atoi(stra[3]);
//         int iCount = 0;
//         bool bFirst = false;
//         if(i1 != i2
//               && i1 >= 1 && i1 <= 12
//               && i2 >= 1 && i2 <=
//               Sys(pparticle).datetime().get_month_day_count(time.GetYear(),i1))
//         {
//            bFirst = true;
//            iCount++;
//         }
//         if(i2 >= 1 && i2 <= 12
//               && i1 >= 1 && i1 <=
//               Sys(pparticle).datetime().get_month_day_count(time.GetYear(),i2))
//         {
//            iCount++;
//         }
//         if(iCount > 0)
//         {
//            if((iCount == 1 && bFirst) || (iCount == 2 && (iPath % iCount) == 0))
//            {
//               int iDay = i2;
//               int iMonth = i1;
//               time = ::earth::time(time.GetYear(),iMonth,iDay,
//                                       time.GetHour(),time.GetMinute(),time.GetSecond());
//               time = ::earth::time(time.GetYear(),time.GetMonth(),time.GetDay(),0,0,0);
//            }
//            else if((iCount == 1 && !bFirst) || (iCount == 2 && (iPath % iCount) == 1))
//            {
//               int iDay = i1;
//               int iMonth = i2;
//               time = ::earth::time(time.GetYear(),iMonth,iDay,
//                                       time.GetHour(),time.GetMinute(),time.GetSecond());
//               time = ::earth::time(time.GetYear(),time.GetMonth(),time.GetDay(),0,0,0);
//            }
//            iPath = iPath / iCount;
//            iPathCount = iPathCount * iCount;
//            bBaseTime = true;
//         }
//      }
//      if(bBaseTime)
//      {
//         if (str.substr(iStart).trimmed().get_length() == 0)
//         {
//
//            return value(time);
//
//         }
//
//         return value(time) + span_strtotime(pparticle,pcontext,str.substr(iStart));
//
//      }
//      else
//      {
//
//         return span_strtotime(pparticle,pcontext,str.substr(iStart));
//
//      }
//
//   }
//
//
//   string to_string(::particle * pparticle, const ::text::context * pcontext,const ::datetime::result & value)
//   {
//      string str;
//      if(value.m_bSpan)
//      {
//         string_array stra;
//         string strItem;
//         if(value.m_iYear != 0)
//         {
//            if(abs(value.m_iYear) == 1)
//            {
//               strItem.formatf("%d year",value.m_iYear);
//            }
//            else
//            {
//               strItem.formatf("%d years",value.m_iYear);
//            }
//            stra.add(strItem);
//         }
//         if(value.m_iMonth != 0)
//         {
//            if(abs(value.m_iMonth) == 1)
//            {
//               strItem.formatf("%d month",value.m_iMonth);
//            }
//            else
//            {
//               strItem.formatf("%d months",value.m_iMonth);
//            }
//            stra.add(strItem);
//         }
//         if(value.m_iDay != 0)
//         {
//            if(abs(value.m_iDay) == 1)
//            {
//               strItem.formatf("%d day",value.m_iDay);
//            }
//            else
//            {
//               strItem.formatf("%d days",value.m_iDay);
//            }
//            stra.add(strItem);
//         }
//         if(value.m_iHour != 0)
//         {
//            if(abs(value.m_iHour) == 1)
//            {
//               strItem.formatf("%d hour",value.m_iHour);
//            }
//            else
//            {
//               strItem.formatf("%d hours",value.m_iHour);
//            }
//            stra.add(strItem);
//         }
//         if(value.m_iMinute != 0)
//         {
//            if(abs(value.m_iMinute) == 1)
//            {
//               strItem.formatf("%d minute",value.m_iMinute);
//            }
//            else
//            {
//               strItem.formatf("%d minutes",value.m_iMinute);
//            }
//            stra.add(strItem);
//         }
//         if(value.m_iSecond != 0)
//         {
//            if(abs(value.m_iSecond) == 1)
//            {
//               strItem.formatf("%d second",value.m_iSecond);
//            }
//            else
//            {
//               strItem.formatf("%d seconds",value.m_iSecond);
//            }
//            stra.add(strItem);
//         }
//         if(stra.get_count() >= 2)
//         {
//            str = stra.implode(", ",0,stra.get_count() - 1) + " and " + stra.last();
//         }
//         else if(stra.get_count() == 1)
//         {
//            str = stra[0];
//         }
//      }
//      else
//      {
//         ::earth::time time = value.get_time();
//         if(time.GetSecond() == 0)
//         {
//            if(time.GetHour() == 0 && time.GetMinute() == 0)
//            {
//               str = time.Format("%Y-");
//               Sys(pparticle).datetime().get_month_str(pcontext,time.GetMonth());
//               str += time.Format("-%d");
//            }
//            else
//            {
//               str = time.Format("%Y-");
//               str += Sys(pparticle).datetime().get_month_str(pcontext,time.GetMonth());
//               str += time.Format("-%d %H:%M");
//            }
//         }
//         else
//         {
//            str = time.Format("%Y-");
//            str += Sys(pparticle).datetime().get_month_str(pcontext,time.GetMonth());
//            str += time.Format("-%d %H:%M:%S");
//         }
//      }
//      return str;
//   }


} // namespace datetime


long long g_iNanosFirst;


CLASS_DECL_ACME long long _first_nano()
{

   return g_iNanosFirst;

}


CLASS_DECL_ACME unsigned int get_fast_tick_count()
{

#ifdef WINDOWS

   return ::GetTickCount();

#else

   struct timeval tv;

   if (gettimeofday(&tv, nullptr) != 0)
   {

      return 0;

   }

   return (unsigned int)(tv.tv_sec * 1000 + tv.tv_usec / 1000);

#endif

}




// http://stackoverflow.com/questions/32424125/c-code-to-get-local-time-offset-in-minutes-relative-to-utc
// http://stackoverflow.com/questions/32424125/c-code-to-get-local-time-offset-in-minutes-relative-to-utc/32433950#32433950
// http://stackoverflow.com/users/619295/trenki
extern "C"
CLASS_DECL_ACME int c_localtime_offset()
{

   time_t rawtime = time(nullptr);

   struct tm *ptm = gmtime(&rawtime);

   // Request that mktime() looksup dst in timezone database

   ptm->tm_isdst = -1;

   time_t gmt = mktime(ptm);

   return (int)(rawtime - gmt);

}
