#pragma once


namespace windows
{


   namespace file_time
   {


      bool DosTimeToFileTime(unsigned int dosTime, FILETIME & fileTime);
      bool FileTimeToDosTime(const FILETIME & fileTime, unsigned int & dosTime);
      void UnixTimeToFileTime(unsigned int unixTime, FILETIME & fileTime);
      bool FileTimeToUnixTime(const FILETIME & fileTime, unsigned int & unixTime);
      bool GetSecondsSince1601(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int minimum, unsigned int sec, uint64_t &resSeconds);

#if defined(WINDOWS)

      void GetCurUtcFileTime(FILETIME & ft);

#endif



   } // namespace file_time


} // namespace windows



