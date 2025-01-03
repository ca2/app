#include "framework.h"


namespace windows
{

   namespace file_time
   {


      static const unsigned int kNumTimeQuantumsInSecond = 10000000;
      static const unsigned int kFileTimeStartYear = 1601;
      static const unsigned int kDosTimeStartYear = 1980;
      static const unsigned int kUnixTimeStartYear = 1970;
      static const uint64_t kUnixTimeStartValue = ((uint64_t)kNumTimeQuantumsInSecond) *  60 * 60 * 24 * (89 + 365 * (kUnixTimeStartYear - kFileTimeStartYear));

      bool DosTimeToFileTime(unsigned int dosTime, FILETIME &ft)
      {

#if defined(_WIN32) && !defined(UNDER_CE) && !defined(METROWIN)
         return ::DosDateTimeToFileTime((::u3216_t)(dosTime >> 16), (::u3216_t)(dosTime & 0xFFFF), &ft) != false;
#else

         ft.dwLowDateTime = 0;
         ft.dwHighDateTime = 0;
         uint64_t res;
         if (!GetSecondsSince1601(kDosTimeStartYear + (dosTime >> 25), (dosTime >> 21) & 0xF, (dosTime >> 16) & 0x1F,
            (dosTime >> 11) & 0x1F, (dosTime >> 5) & 0x3F, (dosTime & 0x1F) * 2, res))
            return false;
         res *= kNumTimeQuantumsInSecond;
         ft.dwLowDateTime = (unsigned int)res;
         ft.dwHighDateTime = (unsigned int)(res >> 32);
         return true;
#endif
      }

      static const unsigned int kHighDosTime = 0xFF9FBF7D;
      static const unsigned int kLowDosTime = 0x210000;

#define PERIOD_4 (4 * 365 + 1)
#define PERIOD_100 (PERIOD_4 * 25 - 1)
#define PERIOD_400 (PERIOD_100 * 4 + 1)

      bool FileTimeToDosTime(const FILETIME &ft, unsigned int &dosTime)
      {
#if defined(_WIN32) && !defined(UNDER_CE) && !defined(METROWIN)

         unsigned short datePart, timePart;
         if (!::FileTimeToDosDateTime(&ft, &datePart, &timePart))
         {
            dosTime = (ft.dwHighDateTime >= 0x01C00000) ? kHighDosTime : kLowDosTime;
            return false;
         }
         dosTime = (((unsigned int)datePart) << 16) + timePart;

#else

         unsigned int year, mon, day, hour, minimum, sec;
         uint64_t v64 = ft.dwLowDateTime | ((uint64_t)ft.dwHighDateTime << 32);
         unsigned char ms[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
         unsigned int temp;
         unsigned int v;
         v64 += (kNumTimeQuantumsInSecond * 2 - 1);
         v64 /= kNumTimeQuantumsInSecond;
         sec = (unsigned int)(v64 % 60);
         v64 /= 60;
         minimum = (unsigned int)(v64 % 60);
         v64 /= 60;
         hour = (unsigned int)(v64 % 24);
         v64 /= 24;

         v = (unsigned int)v64;

         year = (unsigned int)(kFileTimeStartYear + v / PERIOD_400 * 400);
         v %= PERIOD_400;

         temp = (unsigned int)(v / PERIOD_100);
         if (temp == 4)
            temp = 3;
         year += temp * 100;
         v -= temp * PERIOD_100;

         temp = v / PERIOD_4;
         if (temp == 25)
            temp = 24;
         year += temp * 4;
         v -= temp * PERIOD_4;

         temp = v / 365;
         if (temp == 4)
            temp = 3;
         year += temp;
         v -= temp * 365;

         if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
            ms[1] = 29;
         for (mon = 1; mon <= 12; mon++)
         {
            unsigned int s = ms[mon - 1];
            if (v < s)
               break;
            v -= s;
         }
         day = (unsigned int)v + 1;

         dosTime = kLowDosTime;
         if (year < kDosTimeStartYear)
            return false;
         year -= kDosTimeStartYear;
         dosTime = kHighDosTime;
         if (year >= 128)
            return false;
         dosTime = (year << 25) | (mon << 21) | (day << 16) | (hour << 11) | (minimum << 5) | (sec >> 1);
#endif
         return true;
      }

      void UnixTimeToFileTime(unsigned int unixTime, FILETIME &ft)
      {
         uint64_t v = kUnixTimeStartValue + ((uint64_t)unixTime) * kNumTimeQuantumsInSecond;
         ft.dwLowDateTime = (unsigned int)v;
         ft.dwHighDateTime = (unsigned int)(v >> 32);
      }

      bool FileTimeToUnixTime(const FILETIME &ft, unsigned int &unixTime)
      {
         uint64_t winTime = (((uint64_t)ft.dwHighDateTime) << 32) + ft.dwLowDateTime;
         if (winTime < kUnixTimeStartValue)
         {
            unixTime = 0;
            return false;
         }
         winTime = (winTime - kUnixTimeStartValue) / kNumTimeQuantumsInSecond;
         if (winTime > 0xFFFFFFFF)
         {
            unixTime = 0xFFFFFFFF;
            return false;
         }
         unixTime = (unsigned int)winTime;
         return true;
      }

      bool GetSecondsSince1601(unsigned int year, unsigned int month, unsigned int day,
         unsigned int hour, unsigned int minimum, unsigned int sec, uint64_t &resSeconds)
      {
         resSeconds = 0;
         if (year < kFileTimeStartYear || year >= 10000 || month < 1 || month > 12 ||
            day < 1 || day > 31 || hour > 23 || minimum > 59 || sec > 59)
            return false;
         unsigned int numYears = year - kFileTimeStartYear;
         unsigned int numDays = numYears * 365 + numYears / 4 - numYears / 100 + numYears / 400;
         unsigned char ms[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
         if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
            ms[1] = 29;
         month--;
         for (unsigned int i = 0; i < month; i++)
            numDays += ms[i];
         numDays += day - 1;
         resSeconds = ((uint64_t)(numDays * 24 + hour) * 60 + minimum) * 60 + sec;
         return true;
      }





#if defined(WINDOWS)


      void GetCurUtcFileTime(FILETIME &ft)
      {

         SYSTEMTIME st;

         GetSystemTime(&st);

         SystemTimeToFileTime(&st, &ft);

      }


#endif





   } // namespace file_time


} // namespace windows


