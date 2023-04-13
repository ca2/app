#include "framework.h"
//#include "earth_time.h"
//#include "file_time.h"
#include "date_span.h"
#include "earth_gregorian_time.h"
#include "acme/platform/definition.h"
#include "acme/primitive/datetime/_string.h"
//#include "acme/operating_system/time.h"
#include "acme/exception/not_implemented.h"
#include "acme/platform/debug.h"
#include "acme/primitive/string/str.h"


#include "acme/_operating_system.h"


#include <time.h>


void mkgmtime_from_filetime(time_t & time, const ::file_time_t & file_time);


namespace earth
{


   const char * const szInvalidDateTime = "Invalid DateTime";


   ::earth::time time::now() noexcept
   {

#ifdef WINDOWS

      return time( ::_time64( nullptr ) ) ;

#else

      return time( ::time( nullptr ) );

#endif

   }


   time::time(i32 nYear, i32 nMonth, i32 nDay, i32 nHour, i32 nMin, i32 nSec, const ::earth::time_shift & timeshift)
   {


#pragma warning (push)
#pragma warning (disable: 4127)  // conditional expression constant
#pragma warning (pop)


      struct tm atm;

      atm.tm_sec = nSec;
      atm.tm_min = nMin;
      atm.tm_hour = nHour;
      atm.tm_mday = nDay;
      atm.tm_mon = nMonth - 1;        // tm_mon is 0 based
      atm.tm_year = nYear - 1900;     // tm_year is 1900 based
      //atm.tm_isdst = nDST;


      m_time = make_utc_time(&atm) - (time_t) timeshift.m_d;


      /*
      Remember that:
      ENSURE( nYear >= 1900 );
      ENSURE( nMonth >= 1 && nMonth <= 12 );
      ENSURE( nDay >= 1 && nDay <= 31 );
      ENSURE( nHour >= 0 && nHour <= 23 );
      ENSURE( nMin >= 0 && nMin <= 59 );
      ENSURE( nSec >= 0 && nSec <= 59 );
      ASSUME(m_time != -1);   */    // indicates an illegal input time
      if(m_time == -1)
      {

         throw_exception(error_bad_argument);

      }

   }

   time::time(const ::earth::gregorian::time & gregoriantime, const time_shift & timeshift) :
      time(gregoriantime.m_iYear,
         gregoriantime.m_iMonth,
         gregoriantime.m_iDay,
         gregoriantime.m_iHour,
         gregoriantime.m_iMinute,
         gregoriantime.m_iSecond,
         timeshift
         )
   {


   }


#ifdef WINDOWS


   time::time(::u16 wDosDate, ::u16 wDosTime, i32 nDST)
   {

      struct tm atm;
      atm.tm_sec = (wDosTime & ~0xFFE0) << 1;
      atm.tm_min = (wDosTime & ~0xF800) >> 5;
      atm.tm_hour = wDosTime >> 11;

      atm.tm_mday = wDosDate & ~0xFFE0;
      atm.tm_mon = ((wDosDate & ~0xFE00) >> 5) - 1;
      atm.tm_year = (wDosDate >> 9) + 80;
      atm.tm_isdst = nDST;

#ifdef WINDOWS

      m_time = _mktime64(&atm);

#else

      m_time = mktime(&atm);

#endif

      ASSUME(m_time != -1);       // indicates an illegal input time

      if (m_time == -1)
      {

         throw ::exception(error_bad_argument);

      }

   }


#endif

   
   time::time(const file_time & file_time)
   {

      //auto pnode = acmesystem()->node();

      file_time_to_earth_time((time_t *)&m_time, &file_time.m_filetime);

   }


   struct tm* time::tm_struct(struct tm* ptm, const ::earth::time_shift & timeshift) const
   {

      time_t timeOffset = (time_t) timeshift.m_d;

      time_t time = m_time + timeOffset;

      if (ptm != nullptr)
      {

#ifdef WINDOWS

         struct tm tmTemp;

         errno_t err = _gmtime64_s(&tmTemp, &time);

         if (err != 0)
         {
            return nullptr;    // indicates that m_time was not initialized!
         }

         *ptm = tmTemp;

         return ptm;

#else

         struct tm * ptmTemp;

         ptmTemp = gmtime((time_t *)&time);

         // gmtime can return nullptr
         if(ptmTemp == nullptr)
            return nullptr;

         // but don't throw ::exception( exception or generate error...
         // (reason for commenting out below, fat to be erased...)
//         if(errno != 0)
         //          return nullptr;

         *ptm = *ptmTemp;

         return ptm;

#endif

      }
      else
      {

         return nullptr;

      }

   }


//   struct tm* time::GetLocalTm(struct tm* ptm) const
//   {
//
//      if (ptm != nullptr)
//      {
//
//
//#ifdef WINDOWS
//
//         //SYSTEMTIME st;
//
//         //::GetLocalTime(&st);
//
//         //ptm->tm_hour = st.wHour;
//         //ptm->tm_isdst = -1;
//         //ptm->tm_mday = st.wDay;
//         //ptm->tm_min = st.wMinute;
//         //ptm->tm_mon = st.wMonth;
//         //ptm->tm_sec = st.wSecond;
//         //ptm->tm_wday = st.wDayOfWeek;
//         //ptm->tm_yday = -1;
//         //ptm->tm_year = st.wYear;
//
//         struct tm tmTemp;
//
//         errno_t err = _localtime64_s(&tmTemp, &m_time);
//
//         if (err != 0)
//         {
//            return nullptr;    // indicates that m_time was not initialized!
//         }
//
//         *ptm = tmTemp;
//
//         return ptm;
//
//#else
//
//         return localtime_r((time_t *)&m_time, ptm);
//
//#endif
//
//      }
//      else
//      {
//
//         return nullptr;
//
//      }
//
//   }
//

   time_t time::get_time() const noexcept
   {

       return m_time;

   }


   i32 time::year(const ::earth::time_shift & timeshift) const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = tm_struct(&ttm, timeshift);

      return ptm ? (ptm->tm_year) + 1900 : 0 ;

   }


   i32 time::month(const ::earth::time_shift& timeshift) const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = tm_struct(&ttm, timeshift);

      return ptm ? ptm->tm_mon + 1 : 0;

   }


   i32 time::day(const ::earth::time_shift& timeshift) const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = tm_struct(&ttm, timeshift);

      return ptm ? ptm->tm_mday : 0 ;

   }


   i32 time::hour(const ::earth::time_shift& timeshift) const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = tm_struct(&ttm, timeshift);

      return ptm ? ptm->tm_hour : -1 ;

   }


   i32 time::minute(const ::earth::time_shift& timeshift) const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = tm_struct(&ttm, timeshift);

      return ptm ? ptm->tm_min : -1 ;

   }


   i32 time::second(const ::earth::time_shift& timeshift) const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = tm_struct(&ttm, timeshift);

      return ptm ? ptm->tm_sec : -1 ;

   }


   i32 time::day_of_week(const ::earth::time_shift & timeshift) const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = tm_struct(&ttm, timeshift);

      return ptm ? ptm->tm_wday + 1 : 0 ;

   }


   //i32 time::GetGmtYear() const noexcept
   //{

   //   struct tm ttm;

   //   struct tm * ptm;

   //   ptm = GetGmtTm(&ttm);

   //   return ptm ? (ptm->tm_year) + 1900 : 0 ;

   //}


   //i32 time::GetGmtMonth() const noexcept
   //{

   //   struct tm ttm;

   //   struct tm * ptm;

   //   ptm = GetGmtTm(&ttm);

   //   return ptm ? ptm->tm_mon + 1 : 0;

   //}


   //i32 time::GetGmtDay() const noexcept
   //{

   //   struct tm ttm;

   //   struct tm * ptm;

   //   ptm = GetGmtTm(&ttm);

   //   return ptm ? ptm->tm_mday : 0;

   //}


   //i32 time::GetGmtHour() const noexcept
   //{

   //   struct tm ttm;

   //   struct tm * ptm;

   //   ptm = GetGmtTm(&ttm);

   //   return ptm ? ptm->tm_hour : -1 ;

   //}


   //i32 time::GetGmtMinute() const noexcept
   //{

   //   struct tm ttm;

   //   struct tm * ptm;

   //   ptm = GetGmtTm(&ttm);

   //   return ptm ? ptm->tm_min : -1 ;

   //}


   //i32 time::GetGmtSecond() const noexcept
   //{

   //   struct tm ttm;

   //   struct tm * ptm;

   //   ptm = GetGmtTm(&ttm);

   //   return ptm ? ptm->tm_sec : -1;

   //}


   //i32 time::GetGmtDayOfWeek() const noexcept
   //{

   //   struct tm ttm;

   //   struct tm * ptm;

   //   ptm = GetGmtTm(&ttm);

   //   return ptm ? ptm->tm_wday + 1 : 0;

   //}


   time time::get_sunday(const time_shift& timeshift) const
   {

      time sunday(*this);

      sunday = time(sunday.year(timeshift),sunday.month(timeshift),sunday.day(timeshift),0,0,0);

      sunday -= time_span(sunday.day_of_week(timeshift) - 1,0,0,0);

      return sunday;

   }


   time_span time::elapsed() const
   {

      return ::earth::time::now() - *this;

   }


   time_span time::abs_diff(const class time & time) const
   {

      return abs(time.m_time - m_time);

   }


   time_t time::time_of_day(const time_shift& timeshift) const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = tm_struct(&ttm, timeshift);

      return ptm ? ((ptm->tm_hour * 3600) + (ptm->tm_min * 60) + ptm->tm_sec) : 0;

   }


   //time_t time::GetGmtTimeOfDay() const noexcept
   //{

   //   struct tm ttm;

   //   struct tm * ptm;

   //   ptm = GetGmtTm(&ttm);

   //   return ptm ? ((ptm->tm_hour * 3600) + (ptm->tm_min * 60) + ptm->tm_sec) : 0;

   //}


   i64 time::day_sig(const time_shift& timeshift) const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = tm_struct(&ttm, timeshift);

      return ptm ? ((ptm->tm_year * 500) + (ptm->tm_mon * 40) + ptm->tm_mday) : 0;

   }



   string format(const ::string & strFormat, const ::earth::time & time, const ::earth::time_shift& timeshift)
   {

      string str;

      auto timeUtc = time.m_time;

      timeUtc += (::i32)  (timeshift.m_d * 3600.0);

   #if defined(LINUX) || defined(ANDROID) || defined(SOLARIS)
      char * szBuffer = str.get_string_buffer(maxTimeBufferSize);
   #if OSBIT == 32
      const time_t timet = (const time_t) timeUtc;
      struct tm * ptmTemp = gmtime(&timet);
      #else
      struct tm * ptmTemp = gmtime(&timeUtc);
      #endif
      if (ptmTemp == nullptr || !strftime(szBuffer, maxTimeBufferSize, strFormat.c_str(), ptmTemp))
      {
         szBuffer[0] = '\0';
      }

      str.release_string_buffer();

      return str;

   #elif defined(__APPLE__)

   #if __WORDSIZE != 64
   #pragma error "error: long should 8-byte on __APPLE__"
   #endif

      char * szBuffer = str.get_string_buffer(maxTimeBufferSize);

      struct tm * ptmTemp = gmtime((time_t *)&time.m_time);

      if (ptmTemp == nullptr || !strftime(szBuffer, maxTimeBufferSize, strFormat, ptmTemp))
      {

         szBuffer[0] = '\0';

      }

      str.release_string_buffer();

      return str;

   #elif _SECURE_TEMPLATE

      char * szBuffer = str.get_string_buffer(maxTimeBufferSize);

      struct tm ptmTemp;

      errno_t err = _gmbtime64_s(&ptmTemp, &m_time);

      if (err != 0 || !_tcsftime(szBuffer, maxTimeBufferSize, strFormat, &ptmTemp))
      {

         szBuffer[0] = '\0';

      }


      str.ReleaseBuffer();

      return str;

      //#elif defined(ANDROID) || defined(SOLARIS)
      //
      //      struct tm* ptmTemp = localtime(&m_time);
      //
      //      if (ptmTemp == nullptr || !strftime(szBuffer, maxTimeBufferSize, strFormat, ptmTemp))
      //      {
      //
      //         szBuffer[0] = '\0';
      //
      //      }
      //
   #else

      str = strFormat;

      str.replace_with(as_string(time.year(timeshift)), "%Y");
      str.replace_with(::str::zero_padded(as_string(time.month(timeshift)), 2), "%m");
      str.replace_with(::str::zero_padded(as_string(time.day(timeshift)), 2), "%d");
      str.replace_with(::str::zero_padded(as_string(time.hour(timeshift)), 2), "%H");
      str.replace_with(::str::zero_padded(as_string(time.minute(timeshift)), 2), "%M");
      str.replace_with(::str::zero_padded(as_string(time.second(timeshift)), 2), "%S");

      return str;

   #endif

   }


   //string utc_format(const string & strFormat, const ::earth::time & time)
   //{

   //   string str;

   //   char szBuffer[maxTimeBufferSize];

   //#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

   //   struct tm * ptmTemp = gmtime((time_t *)&time.m_time);

   //   if (ptmTemp == nullptr || !strftime(szBuffer, maxTimeBufferSize, strFormat, ptmTemp))
   //   {

   //      szBuffer[0] = '\0';

   //   }

   //#elif _SECURE_TEMPLATE

   //   struct tm ptmTemp;

   //   errno_t err = _gmtime64_s(&ptmTemp, &m_time);

   //   if (err != 0 || !_tcsftime(szBuffer, maxTimeBufferSize, strFormat, &ptmTemp))
   //   {

   //      szBuffer[0] = '\0';

   //   }

   //#else

   //   struct tm * ptmTemp = _gmtime64(&time.m_time);

   //   if (ptmTemp == nullptr || !strftime(szBuffer, maxTimeBufferSize, strFormat, ptmTemp))
   //   {

   //      szBuffer[0] = '\0';

   //   }

   //#endif

   //   str = szBuffer;

   //   return szBuffer;

   //}


   ::earth::time & time::operator+=(date_span span)
   {

      __UNREFERENCED_PARAMETER(span);

      //throw ::not_implemented();

      return *this;

   }


   ::earth::time & time::operator-=(date_span span)
   {

      __UNREFERENCED_PARAMETER(span);

      //throw ::not_implemented();

      return *this;

   }


   ::earth::time time::operator-(date_span span) const
   {

      __UNREFERENCED_PARAMETER(span);

      //throw ::not_implemented();

      return 0;

   }


   ::earth::time time::operator+(date_span span) const
   {

      __UNREFERENCED_PARAMETER(span);

      //throw_();

      return 0;

   }


} // namespace earth








//#ifdef __DEBUG
//
//dump_context & operator <<(dump_context & dumpcontext, ::earth::time & time)
//{
////   char psz[32];
////   psz[0] = '\0';
////
//////   time_t tmp = time.get_time();
//////   errno_t err = _ctime64_s(psz, sizeof(psz), &tmp);
////
////   errno_t err = 0;
////
////   if ((err != 0) || (psz[0] == '\0') || (time.get_time() == 0))
////   {
////      dumpcontext << "::earth::time(invalid #" << (iptr) time.get_time() << ")";
////
////      return dumpcontext;
////   }
////
////   // format it
////   dumpcontext << "::earth::time(\"" << psz << "\")";
//
//   return dumpcontext;
//}
//
//#endif
//
////stream & operator <<(stream & os, ::earth::time & time)
////{
////
////   os.write((i64) time.m_time);
////
////   return os;
////
////}
////
////



//i64 time::GetGmtDaySig() const noexcept
//{

//   struct tm ttm;

//   struct tm * ptm;

//   ptm = GetGmtTm(&ttm);

//   return ptm ? ((ptm->tm_year * 500) + (ptm->tm_mon * 40) + ptm->tm_mday) : 0;

//}

//stream & operator >>(stream & is, ::earth::time & rtime)
//{
//
//   is.read((i64 &) rtime.m_time);
//
//   return is;
//
//}


#ifdef WINDOWS


CLASS_DECL_ACME SYSTEMTIME __SYSTEMTIME(const ::earth::time & time)
{

   SYSTEMTIME st = {};

   struct tm ttm;

   struct tm * ptm;

   ptm = time.tm_struct(&ttm);

   st.wDay = ptm->tm_mday;
   st.wDayOfWeek = ptm->tm_wday;
   st.wHour = ptm->tm_hour;
   st.wMilliseconds = 0;
   st.wMinute = ptm->tm_min;
   st.wMonth = ptm->tm_mon + 1;
   st.wSecond = ptm->tm_sec;
   st.wYear = 1900 + ptm->tm_year;

   return st;

}


//file_time __file_time(const ::earth::time & time)
//{
//
//   auto pnode = acmesystem()->node();
//
//   SYSTEMTIME systemtime;
//
//   pnode->system_time_to_earth_time(__systemtime();
//
//   file_time file_time = {};
//
//   if (!SystemTimeToFileTime(Systemtime, (FILETIME *) &file_time))
//   {
//
//#ifdef WINDOWS
//
//      DWORD dwLastError = ::GetLastError();
//
//#endif
//
//      //TRACELASTERROR();
//
//      zero(file_time);
//
//   }
//
//   return file_time;
//
//}


CLASS_DECL_ACME FILETIME & copy(FILETIME & filetime, const ::earth::time & time)
{

   SYSTEMTIME systemtime = __SYSTEMTIME(time);

   if (!SystemTimeToFileTime(&systemtime, &filetime))
   {

#ifdef WINDOWS

      DWORD dwLastError = ::GetLastError();

#endif

      //TRACELASTERROR();

      memset(&filetime, 0, sizeof(filetime));

   }

   return filetime;

}


#endif




//#define INTEL 1

//
//time_t __time(const file_time & file_time)
//{
//
//   auto time = __time(*(FILETIME *)&file_time);
//
//   auto estatus = mkgmtime_from_filetime(time.m_time, file_time.m_filetime);
//
//   if (!estatus)
//   {
//
//      throw ::exception(::exception(estatus));
//
//   }
//
//   return time;
//
//}



