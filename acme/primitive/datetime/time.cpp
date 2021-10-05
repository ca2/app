#include "framework.h"
#include "acme/operating_system.h"
#include <time.h>
#include "acme/primitive/datetime/_string.h"


::e_status mkgmtime_from_filetime(time_t & time, const ::filetime_t & filetime);


namespace datetime
{


   const char * const szInvalidDateTime = "Invalid DateTime";


   ::datetime::time time::get_current_time() noexcept
   {

#ifdef WINDOWS

      return time( ::_time64( nullptr ) ) ;

#else

      return time( ::time( nullptr ) );

#endif

   }




   time::time(i32 nYear, i32 nMonth, i32 nDay, i32 nHour, i32 nMin, i32 nSec, i32 nDST)
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
      atm.tm_isdst = nDST;

#ifdef WINDOWS

      m_time = _mktime64(&atm);

#else

      m_time = mktime(&atm);

#endif

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

         __throw(error_invalid_argument);

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

      m_time = _mktime64(&atm);

#else

      m_time = mktime(&atm);

#endif

      ASSUME(m_time != -1);       // indicates an illegal input time

      if(m_time == -1)
         __throw(error_invalid_argument);

   }




#endif

   
   time::time(const filetime & filetime)
   {

      //auto pnode = get_system()->node();

      file_time_to_time(&m_time, &filetime.m_filetime);

   }


   ::datetime::time & time::operator=(const time & time) noexcept
   {

      m_time = time.m_time;

      return *this;

   }

   
   ::datetime::time & time::operator+=( time_span span ) noexcept
   {

      m_time += span.GetTimeSpan();

      return *this;

   }


   ::datetime::time & time::operator-=( time_span span ) noexcept
   {
      m_time -= span.GetTimeSpan();

      return *this;
   }

   ::datetime::time & time::operator+=(const  duration & duration ) noexcept
   {
      m_time += duration.GetTimeSpan();

      return *this;
   }

   ::datetime::time & time::operator-=(const  duration & duration ) noexcept
   {
      m_time -= duration.GetTimeSpan();

      return *this;
   }

   ::datetime::time & time::operator+=( date_span span )
   {
      __UNREFERENCED_PARAMETER(span);
      __throw(error_not_implemented);

      return *this;
   }


   ::datetime::time& time::operator-=( date_span span )
   {

       __UNREFERENCED_PARAMETER(span);

      __throw(error_not_implemented);

      return *this;

   }


   ::datetime::time time::operator-( date_span span ) const
   {

       __UNREFERENCED_PARAMETER(span);

      __throw(error_not_implemented);

      return 0;

   }


   ::datetime::time time::operator+( date_span span ) const
   {

       __UNREFERENCED_PARAMETER(span);

      __throw(error_not_implemented);

      return 0;

   }


   struct tm* time::GetGmtTm(struct tm* ptm) const
   {

      if (ptm != nullptr)
      {

#ifdef WINDOWS

         struct tm tmTemp;

         errno_t err = _gmtime64_s(&tmTemp, &m_time);

         if (err != 0)
         {
            return nullptr;    // indicates that m_time was not initialized!
         }

         *ptm = tmTemp;

         return ptm;

#else

         struct tm * ptmTemp;

         ptmTemp = gmtime(&m_time);

         // gmtime can return nullptr
         if(ptmTemp == nullptr)
            return nullptr;

         // but don't __throw( exception or generate error...
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


   struct tm* time::GetLocalTm(struct tm* ptm) const
   {

      if (ptm != nullptr)
      {


#ifdef WINDOWS

         //SYSTEMTIME st;

         //::GetLocalTime(&st);

         //ptm->tm_hour = st.wHour;
         //ptm->tm_isdst = -1;
         //ptm->tm_mday = st.wDay;
         //ptm->tm_min = st.wMinute;
         //ptm->tm_mon = st.wMonth;
         //ptm->tm_sec = st.wSecond;
         //ptm->tm_wday = st.wDayOfWeek;
         //ptm->tm_yday = -1;
         //ptm->tm_year = st.wYear;

         struct tm tmTemp;

         errno_t err = _localtime64_s(&tmTemp, &m_time);

         if (err != 0)
         {
            return nullptr;    // indicates that m_time was not initialized!
         }

         *ptm = tmTemp;

         return ptm;

#else

         return localtime_r(&m_time, ptm);

#endif

      }
      else
      {

         return nullptr;

      }

   }





   time_t time::get_time() const noexcept
   {

       return( m_time );

   }


   i32 time::GetYear() const noexcept
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetLocalTm(&ttm);
      return ptm ? (ptm->tm_year) + 1900 : 0 ;
   }

   i32 time::GetMonth() const noexcept
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetLocalTm(&ttm);
      return ptm ? ptm->tm_mon + 1 : 0;
   }

   i32 time::GetDay() const noexcept
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetLocalTm(&ttm);
      return ptm ? ptm->tm_mday : 0 ;
   }

   i32 time::GetHour() const noexcept
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetLocalTm(&ttm);
      return ptm ? ptm->tm_hour : -1 ;
   }

   i32 time::GetMinute() const noexcept
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetLocalTm(&ttm);
      return ptm ? ptm->tm_min : -1 ;
   }

   i32 time::GetSecond() const noexcept
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetLocalTm(&ttm);
      return ptm ? ptm->tm_sec : -1 ;
   }

   i32 time::GetDayOfWeek() const noexcept
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetLocalTm(&ttm);
      return ptm ? ptm->tm_wday + 1 : 0 ;
   }

   i32 time::GetGmtYear() const noexcept
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetGmtTm(&ttm);
      return ptm ? (ptm->tm_year) + 1900 : 0 ;
   }

   i32 time::GetGmtMonth() const noexcept
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetGmtTm(&ttm);
      return ptm ? ptm->tm_mon + 1 : 0;
   }

   i32 time::GetGmtDay() const noexcept
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetGmtTm(&ttm);
      return ptm ? ptm->tm_mday : 0 ;
   }

   i32 time::GetGmtHour() const noexcept
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetGmtTm(&ttm);
      return ptm ? ptm->tm_hour : -1 ;
   }

   i32 time::GetGmtMinute() const noexcept
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetGmtTm(&ttm);
      return ptm ? ptm->tm_min : -1 ;
   }

   i32 time::GetGmtSecond() const noexcept
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetGmtTm(&ttm);
      return ptm ? ptm->tm_sec : -1 ;
   }

   i32 time::GetGmtDayOfWeek() const noexcept
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetGmtTm(&ttm);
      return ptm ? ptm->tm_wday + 1 : 0 ;
   }


   time time::get_sunday() const
   {

      time sunday(*this);

      sunday = time(sunday.GetYear(),sunday.GetMonth(),sunday.GetDay(),0,0,0);

      sunday -= time_span(sunday.GetDayOfWeek() - 1,0,0,0);

      return sunday;

   }




   time_span time::elapsed() const
   {

      return ::datetime::time::get_current_time() - *this;

   }


   time_span time::abs_diff(const time & time) const
   {

      return abs(time.m_time - m_time);

   }


   time_t time::GetTimeOfDay() const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = GetLocalTm(&ttm);

      return ptm ? ((ptm->tm_hour * 3600) + (ptm->tm_min * 60) + ptm->tm_sec) : 0;

   }


   time_t time::GetGmtTimeOfDay() const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = GetGmtTm(&ttm);

      return ptm ? ((ptm->tm_hour * 3600) + (ptm->tm_min * 60) + ptm->tm_sec) : 0;

   }

   i64 time::GetDaySig() const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = GetLocalTm(&ttm);

      return ptm ? ((ptm->tm_year * 500) + (ptm->tm_mon * 40) + ptm->tm_mday) : 0;

   }


   i64 time::GetGmtDaySig() const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = GetGmtTm(&ttm);

      return ptm ? ((ptm->tm_year * 500) + (ptm->tm_mon * 40) + ptm->tm_mday) : 0;

   }

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

   os.write((i64) time.m_time);

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

   ptm = time.GetGmtTm(&ttm);

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
//      __throw(::exception(estatus));
//
//   }
//
//   return time;
//
//}



namespace datetime
{


} // namespace datetime






string Format(const ::string & strFormat, const ::datetime::time & time)
{

   string str;

#if defined(LINUX) || defined(ANDROID) || defined(SOLARIS)
   char * szBuffer = str.get_string_buffer(maxTimeBufferSize);
   struct tm * ptmTemp = localtime(&time.m_time);
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

   struct tm * ptmTemp = localtime(&time.m_time);

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

   str.replace("%Y", __string(time.GetYear()));
   str.replace("%m", ::str::zero_padded(__string(time.GetMonth()), 2));
   str.replace("%d", ::str::zero_padded(__string(time.GetDay()), 2));
   str.replace("%H", ::str::zero_padded(__string(time.GetHour()), 2));
   str.replace("%M", ::str::zero_padded(__string(time.GetMinute()), 2));
   str.replace("%S", ::str::zero_padded(__string(time.GetSecond()), 2));

   return str;

#endif



}


string FormatGmt(const string & strFormat, const ::datetime::time & time)
{

   string str;

   char szBuffer[maxTimeBufferSize];

#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

   struct tm * ptmTemp = gmtime(&time.m_time);

   if (ptmTemp == nullptr || !strftime(szBuffer, maxTimeBufferSize, strFormat, ptmTemp))
   {

      szBuffer[0] = '\0';

   }

#elif _SECURE_TEMPLATE

   struct tm ptmTemp;

   errno_t err = _gmtime64_s(&ptmTemp, &m_time);

   if (err != 0 || !_tcsftime(szBuffer, maxTimeBufferSize, strFormat, &ptmTemp))
   {

      szBuffer[0] = '\0';

   }

#else

   struct tm * ptmTemp = _gmtime64(&time.m_time);

   if (ptmTemp == nullptr || !strftime(szBuffer, maxTimeBufferSize, strFormat, ptmTemp))
   {

      szBuffer[0] = '\0';

   }

#endif

   str = szBuffer;

   return szBuffer;

}


//
//
//string Format(const ::string & strFormat, const ::datetime::time & time)
//{
//   string str;
//   str = Format(strFormat, time);
//   return str;
//}
//
//
//string FormatGmt(const ::string & strFormat, const ::datetime::time & time)
//{
//   string str;
//   str = FormatGmt(strFormat, time);
//   return str;
//}
