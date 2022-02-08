#include "framework.h"
#include "acme/operating_system.h"
#include <time.h>
#include "acme/primitive/datetime/_string.h"
#include "acme/operating_system/time.h"


void mkgmtime_from_filetime(time_t & time, const ::filetime_t & filetime);


namespace datetime
{


   const char * const szInvalidDateTime = "Invalid DateTime";


   ::datetime::time time::now() noexcept
   {

#ifdef WINDOWS

      return time( ::_time64( nullptr ) ) ;

#else

      return time( ::time( nullptr ) );

#endif

   }


   time::time(i32 nYear, i32 nMonth, i32 nDay, i32 nHour, i32 nMin, i32 nSec, const ::time_shift & timeshift)
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


      m_i = make_utc_time(&atm) - (time_t) timeshift.m_d;


      /*
      Remember that:
      ENSURE( nYear >= 1900 );
      ENSURE( nMonth >= 1 && nMonth <= 12 );
      ENSURE( nDay >= 1 && nDay <= 31 );
      ENSURE( nHour >= 0 && nHour <= 23 );
      ENSURE( nMin >= 0 && nMin <= 59 );
      ENSURE( nSec >= 0 && nSec <= 59 );
      ASSUME(m_time != -1);   */    // indicates an illegal input time
      if(m_i == -1)
      {

         throw ::exception(error_bad_argument);

      }

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

      m_i = _mktime64(&atm);

#else

      m_i = mktime(&atm);

#endif

      ASSUME(m_i != -1);       // indicates an illegal input time

      if (m_i == -1)
      {

         throw ::exception(error_bad_argument);

      }

   }


#endif

   
   time::time(const filetime & filetime)
   {

      //auto pnode = get_system()->node();

      file_time_to_time((time_t *)&m_i, &filetime.m_filetime);

   }


   ::datetime::time & time::operator=(const time & time) noexcept
   {

      m_i = time.m_i;

      return *this;

   }

   
   ::datetime::time & time::operator+=( time_span span ) noexcept
   {

      m_i += span.GetTimeSpan();

      return *this;

   }


   ::datetime::time & time::operator-=( time_span span ) noexcept
   {

      m_i -= span.GetTimeSpan();

      return *this;
      
   }


   ::datetime::time & time::operator+=( date_span span )
   {

      __UNREFERENCED_PARAMETER(span);

      throw ::not_implemented();

      return *this;

   }


   ::datetime::time& time::operator-=( date_span span )
   {

       __UNREFERENCED_PARAMETER(span);

      throw ::not_implemented();

      return *this;

   }


   ::datetime::time time::operator-( date_span span ) const
   {

       __UNREFERENCED_PARAMETER(span);

      throw ::not_implemented();

      return 0;

   }


   ::datetime::time time::operator+( date_span span ) const
   {

       __UNREFERENCED_PARAMETER(span);

      throw ::not_implemented();

      return 0;

   }


   struct tm* time::tm_struct(struct tm* ptm, const ::time_shift & timeshift) const
   {

      time_t time = m_i + (time_t) timeshift.m_d;

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
//         errno_t err = _localtime64_s(&tmTemp, &m_i);
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
//         return localtime_r((time_t *)&m_i, ptm);
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

       return m_i;

   }


   i32 time::year(const ::time_shift & timeshift) const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = tm_struct(&ttm, timeshift);

      return ptm ? (ptm->tm_year) + 1900 : 0 ;

   }


   i32 time::month(const ::time_shift& timeshift) const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = tm_struct(&ttm, timeshift);

      return ptm ? ptm->tm_mon + 1 : 0;

   }


   i32 time::day(const ::time_shift& timeshift) const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = tm_struct(&ttm, timeshift);

      return ptm ? ptm->tm_mday : 0 ;

   }


   i32 time::hour(const ::time_shift& timeshift) const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = tm_struct(&ttm, timeshift);

      return ptm ? ptm->tm_hour : -1 ;

   }


   i32 time::minute(const ::time_shift& timeshift) const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = tm_struct(&ttm, timeshift);

      return ptm ? ptm->tm_min : -1 ;

   }


   i32 time::second(const ::time_shift& timeshift) const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = tm_struct(&ttm, timeshift);

      return ptm ? ptm->tm_sec : -1 ;

   }


   i32 time::day_of_week(const ::time_shift & timeshift) const noexcept
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

      return ::datetime::time::now() - *this;

   }


   time_span time::abs_diff(const time & time) const
   {

      return INTEGRAL_SECOND(abs(time.m_i - m_i));

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


   //i64 time::GetGmtDaySig() const noexcept
   //{

   //   struct tm ttm;

   //   struct tm * ptm;

   //   ptm = GetGmtTm(&ttm);

   //   return ptm ? ((ptm->tm_year * 500) + (ptm->tm_mon * 40) + ptm->tm_mday) : 0;

   //}


} // namespace datetime



#ifdef __DEBUG

dump_context & operator <<(dump_context & dumpcontext, ::datetime::time & time)
{
   char psz[32];
   psz[0] = '\0';

//   time_t tmp = time.get_time();
//   errno_t err = _ctime64_s(psz, sizeof(psz), &tmp);

   errno_t err = 0;

   if ((err != 0) || (psz[0] == '\0') || (time.get_time() == 0))
   {
      dumpcontext << "::datetime::time(invalid #" << (iptr) time.get_time() << ")";

      return dumpcontext;
   }

   // format it
   dumpcontext << "::datetime::time(\"" << psz << "\")";

   return dumpcontext;
}

#endif

stream & operator <<(stream & os, ::datetime::time & time)
{

   os.write((i64) time.m_i);

   return os;

}

//stream & operator >>(stream & is, ::datetime::time & rtime)
//{
//
//   is.read((i64 &) rtime.m_time);
//
//   return is;
//
//}


#ifdef WINDOWS


CLASS_DECL_ACME SYSTEMTIME __SYSTEMTIME(const ::datetime::time & time)
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


//filetime __filetime(const ::datetime::time & time)
//{
//
//   auto pnode = get_system()->node();
//
//   SYSTEMTIME systemtime;
//
//   pnode->system_time_to_time(__systemtime();
//
//   filetime filetime = {};
//
//   if (!SystemTimeToFileTime(Systemtime, (FILETIME *) &filetime))
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
//      __zero(filetime);
//
//   }
//
//   return filetime;
//
//}


CLASS_DECL_ACME FILETIME __FILETIME(const ::datetime::time & time)
{

   SYSTEMTIME systemtime = __SYSTEMTIME(time);

   FILETIME filetime = {};

   if (!SystemTimeToFileTime(&systemtime, &filetime))
   {

#ifdef WINDOWS

      DWORD dwLastError = ::GetLastError();

#endif

      //TRACELASTERROR();

      __zero(filetime);

   }

   return filetime;

}


#endif




//#define INTEL 1

//
//time_t __time(const filetime & filetime)
//{
//
//   auto time = __time(*(FILETIME *)&filetime);
//
//   auto estatus = mkgmtime_from_filetime(time.m_time, filetime.m_filetime);
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


namespace datetime
{


   string format(const ::string & strFormat, const ::datetime::time & time, const ::time_shift& timeshift)
   {

      string str;

   #if defined(LINUX) || defined(ANDROID) || defined(SOLARIS)
      char * szBuffer = str.get_string_buffer(maxTimeBufferSize);
      struct tm * ptmTemp = localtime(&time.m_i);
      if (ptmTemp == nullptr || !strftime(szBuffer, maxTimeBufferSize, strFormat, ptmTemp))
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

      struct tm * ptmTemp = localtime((time_t *)&time.m_i);

      if (ptmTemp == nullptr || !strftime(szBuffer, maxTimeBufferSize, strFormat, ptmTemp))
      {

         szBuffer[0] = '\0';

      }

      str.release_string_buffer();

      return str;

   #elif _SECURE_TEMPLATE

      char * szBuffer = str.get_string_buffer(maxTimeBufferSize);

      struct tm ptmTemp;

      errno_t err = _localtime64_s(&ptmTemp, &m_time);

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

      str.replace_with(__string(time.year(timeshift)), "%Y");
      str.replace_with(::str::zero_padded(__string(time.month(timeshift)), 2), "%m");
      str.replace_with(::str::zero_padded(__string(time.day(timeshift)), 2), "%d");
      str.replace_with(::str::zero_padded(__string(time.hour(timeshift)), 2), "%H");
      str.replace_with(::str::zero_padded(__string(time.minute(timeshift)), 2), "%M");
      str.replace_with(::str::zero_padded(__string(time.second(timeshift)), 2), "%S");

      return str;

   #endif



   }


   //string utc_format(const string & strFormat, const ::datetime::time & time)
   //{

   //   string str;

   //   char szBuffer[maxTimeBufferSize];

   //#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

   //   struct tm * ptmTemp = gmtime((time_t *)&time.m_i);

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

   //   struct tm * ptmTemp = _gmtime64(&time.m_i);

   //   if (ptmTemp == nullptr || !strftime(szBuffer, maxTimeBufferSize, strFormat, ptmTemp))
   //   {

   //      szBuffer[0] = '\0';

   //   }

   //#endif

   //   str = szBuffer;

   //   return szBuffer;

   //}


} // namespace datetime



