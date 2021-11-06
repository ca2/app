#pragma once


namespace windows
{


   namespace filetime
   {


      bool DosTimeToFileTime(::u32 dosTime, FILETIME & fileTime);
      bool FileTimeToDosTime(const FILETIME & fileTime, ::u32 & dosTime);
      void UnixTimeToFileTime(::u32 unixTime, FILETIME & fileTime);
      bool FileTimeToUnixTime(const FILETIME & fileTime, ::u32 & unixTime);
      bool GetSecondsSince1601(::u32 year, ::u32 month, ::u32 day, ::u32 hour, ::u32 minimum, ::u32 sec, uint64_t &resSeconds);

#if defined(WINDOWS)

      void GetCurUtcFileTime(FILETIME & ft);

#endif



   } // namespace filetime


} // namespace windows



