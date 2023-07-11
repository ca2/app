// From acme/operating_system/ansi/windows_time.cpp by camilo on 2023-07-09 14:33 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/operating_system/time.h"


system_time::system_time(const file_time & filetime) :
   system_time(as_system_time(as_SYSTEMTIME(as_FILETIME(filetime))))
{

   //auto FILETIME = ;

   //return SystemTimeToFileTime((const SYSTEMTIME *) psystemtime, (LPFILETIME) pfile_time);

}


file_time::file_time(const system_time & systemtime) :
   file_time(as_file_time(as_FILETIME(as_SYSTEMTIME(systemtime))))
{

   //auto FILETIME = ;

   //return SystemTimeToFileTime((const SYSTEMTIME *) psystemtime, (LPFILETIME) pfile_time);

}



