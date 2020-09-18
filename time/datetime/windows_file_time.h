#pragma once


namespace windows
{


   namespace file_time
   {


      bool DosTimeToFileTime(uint32_t dosTime, FILETIME & fileTime);
      bool FileTimeToDosTime(const FILETIME & fileTime, uint32_t & dosTime);
      void UnixTimeToFileTime(uint32_t unixTime, FILETIME & fileTime);
      bool FileTimeToUnixTime(const FILETIME & fileTime, uint32_t & unixTime);
      bool GetSecondsSince1601(uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t min, uint32_t sec, uint64_t &resSeconds);

#if defined(WINDOWS)

      void GetCurUtcFileTime(FILETIME & ft);

#endif



   } // namespace file_time


} // namespace windows



