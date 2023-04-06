#pragma once


/*#ifdef UNIVERSAL_WINDOWS

struct timeval
{
   //__int32    tv_sec;         // seconds
   //__int32    tv_usec;        // microseconds
//};
*/

//#endif

#ifndef UNIVERSAL_WINDOWS

CLASS_DECL_AURA int_bool WINAPI LocalFileTimeToFileTime(const FILETIME *localft, LPFILETIME utcft);
CLASS_DECL_AURA int_bool WINAPI FileTimeToLocalFileTime(const FILETIME *utcft, LPFILETIME localft);
CLASS_DECL_AURA int_bool FileTimeToSystemTime(const FILETIME *ft, LPSYSTEMTIME syst);
CLASS_DECL_AURA int_bool SystemTimeToFileTime(const SYSTEMTIME *syst, LPFILETIME ft);

void GetSystemTimeAsFileTime(LPFILETIME time); // [out] Destination for the current utc time
void GetSystemTime(LPSYSTEMTIME systime);

#endif


