#include "framework.h"


namespace windows
{

   namespace file_time
   {


      static const u32 kNumTimeQuantumsInSecond = 10000000;
      static const u32 kFileTimeStartYear = 1601;
      static const u32 kDosTimeStartYear = 1980;
      static const u32 kUnixTimeStartYear = 1970;
      static const u64 kUnixTimeStartValue = ((u64)kNumTimeQuantumsInSecond) *  60 * 60 * 24 * (89 + 365 * (kUnixTimeStartYear - kFileTimeStartYear));

      bool DosTimeToFileTime(u32 dosTime, FILETIME &ft)
      {

#if defined(_WIN32) && !defined(UNDER_CE) && !defined(_UWP)
         return ::DosDateTimeToFileTime((u16)(dosTime >> 16), (u16)(dosTime & 0xFFFF), &ft) != FALSE;
#else

         ft.dwLowDateTime = 0;
         ft.dwHighDateTime = 0;
         u64 res;
         if (!GetSecondsSince1601(kDosTimeStartYear + (dosTime >> 25), (dosTime >> 21) & 0xF, (dosTime >> 16) & 0x1F,
            (dosTime >> 11) & 0x1F, (dosTime >> 5) & 0x3F, (dosTime & 0x1F) * 2, res))
            return false;
         res *= kNumTimeQuantumsInSecond;
         ft.dwLowDateTime = (u32)res;
         ft.dwHighDateTime = (u32)(res >> 32);
         return true;
#endif
      }

      static const u32 kHighDosTime = 0xFF9FBF7D;
      static const u32 kLowDosTime = 0x210000;

#define PERIOD_4 (4 * 365 + 1)
#define PERIOD_100 (PERIOD_4 * 25 - 1)
#define PERIOD_400 (PERIOD_100 * 4 + 1)

      bool FileTimeToDosTime(const FILETIME &ft, u32 &dosTime)
      {
#if defined(_WIN32) && !defined(UNDER_CE) && !defined(_UWP)

         WORD datePart, timePart;
         if (!::FileTimeToDosDateTime(&ft, &datePart, &timePart))
         {
            dosTime = (ft.dwHighDateTime >= 0x01C00000) ? kHighDosTime : kLowDosTime;
            return false;
         }
         dosTime = (((u32)datePart) << 16) + timePart;

#else

         u32 year, mon, day, hour, MIN, sec;
         u64 v64 = ft.dwLowDateTime | ((u64)ft.dwHighDateTime << 32);
         byte ms[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
         u32 temp;
         u32 v;
         v64 += (kNumTimeQuantumsInSecond * 2 - 1);
         v64 /= kNumTimeQuantumsInSecond;
         sec = (u32)(v64 % 60);
         v64 /= 60;
         MIN = (u32)(v64 % 60);
         v64 /= 60;
         hour = (u32)(v64 % 24);
         v64 /= 24;

         v = (u32)v64;

         year = (u32)(kFileTimeStartYear + v / PERIOD_400 * 400);
         v %= PERIOD_400;

         temp = (u32)(v / PERIOD_100);
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
            u32 s = ms[mon - 1];
            if (v < s)
               break;
            v -= s;
         }
         day = (u32)v + 1;

         dosTime = kLowDosTime;
         if (year < kDosTimeStartYear)
            return false;
         year -= kDosTimeStartYear;
         dosTime = kHighDosTime;
         if (year >= 128)
            return false;
         dosTime = (year << 25) | (mon << 21) | (day << 16) | (hour << 11) | (MIN << 5) | (sec >> 1);
#endif
         return true;
      }

      void UnixTimeToFileTime(u32 unixTime, FILETIME &ft)
      {
         u64 v = kUnixTimeStartValue + ((u64)unixTime) * kNumTimeQuantumsInSecond;
         ft.dwLowDateTime = (u32)v;
         ft.dwHighDateTime = (u32)(v >> 32);
      }

      bool FileTimeToUnixTime(const FILETIME &ft, u32 &unixTime)
      {
         u64 winTime = (((u64)ft.dwHighDateTime) << 32) + ft.dwLowDateTime;
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
         unixTime = (u32)winTime;
         return true;
      }

      bool GetSecondsSince1601(u32 year, u32 month, u32 day,
         u32 hour, u32 MIN, u32 sec, u64 &resSeconds)
      {
         resSeconds = 0;
         if (year < kFileTimeStartYear || year >= 10000 || month < 1 || month > 12 ||
            day < 1 || day > 31 || hour > 23 || MIN > 59 || sec > 59)
            return false;
         u32 numYears = year - kFileTimeStartYear;
         u32 numDays = numYears * 365 + numYears / 4 - numYears / 100 + numYears / 400;
         byte ms[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
         if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
            ms[1] = 29;
         month--;
         for (u32 i = 0; i < month; i++)
            numDays += ms[i];
         numDays += day - 1;
         resSeconds = ((u64)(numDays * 24 + hour) * 60 + MIN) * 60 + sec;
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


