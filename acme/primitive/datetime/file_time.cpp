#include "framework.h"


namespace datetime
{


   file_time::file_time() noexcept
   {
      dwLowDateTime = 0;
      dwHighDateTime = 0;
   }

   file_time::file_time(const FILETIME& ft) noexcept
   {
      dwLowDateTime = ft.dwLowDateTime;
      dwHighDateTime = ft.dwHighDateTime;
   }

   file_time::file_time(ULONGLONG nTime) noexcept
   {
      dwLowDateTime = u32(nTime);
      dwHighDateTime = u32(nTime >> 32);
   }

   file_time& file_time::operator=(const FILETIME& ft) noexcept
   {
      dwLowDateTime = ft.dwLowDateTime;
      dwHighDateTime = ft.dwHighDateTime;

      return *this;
   }

   file_time WINAPI file_time::get_current_time() noexcept
   {
      file_time ft;
      GetSystemTimeAsFileTime(&ft);
      return ft;
   }

   file_time& file_time::operator+=(file_time_span span) noexcept
   {
      SetTime(get_time() + span.GetTimeSpan());

      return *this;
   }

   file_time& file_time::operator-=(file_time_span span) noexcept
   {
      SetTime(get_time() - span.GetTimeSpan());

      return *this;
   }

   file_time file_time::operator+(file_time_span span) const noexcept
   {
      return(file_time(get_time() + span.GetTimeSpan()));
   }

   file_time file_time::operator-(file_time_span span) const noexcept
   {
      return(file_time(get_time() - span.GetTimeSpan()));
   }

   file_time_span file_time::operator-(file_time ft) const noexcept
   {
      return(file_time_span(get_time() - ft.get_time()));
   }

   bool file_time::operator==(file_time ft) const noexcept
   {
      return(get_time() == ft.get_time());
   }

   bool file_time::operator!=(file_time ft) const noexcept
   {
      return(get_time() != ft.get_time());
   }

   bool file_time::operator<(file_time ft) const noexcept
   {
      return(get_time() < ft.get_time());
   }

   bool file_time::operator>(file_time ft) const noexcept
   {
      return(get_time() > ft.get_time());
   }

   bool file_time::operator<=(file_time ft) const noexcept
   {
      return(get_time() <= ft.get_time());
   }

   bool file_time::operator>=(file_time ft) const noexcept
   {
      return(get_time() >= ft.get_time());
   }

   ULONGLONG file_time::get_time() const noexcept
   {
      return((ULONGLONG(dwHighDateTime) << 32) | dwLowDateTime);
   }

   void file_time::SetTime(ULONGLONG nTime) noexcept
   {
      dwLowDateTime = u32(nTime);
      dwHighDateTime = u32(nTime >> 32);
   }

   file_time file_time::UTCToLocal() const noexcept
   {
      file_time ftLocal;

      ::FileTimeToLocalFileTime(this,&ftLocal);

      return(ftLocal);
   }

   file_time file_time::LocalToUTC() const noexcept
   {

      file_time ftUTC;

      ::LocalFileTimeToFileTime(this,&ftUTC);

      return(ftUTC);

   }


   const ULONGLONG file_time::Millisecond = 10000;
   const ULONGLONG file_time::Second = Millisecond * static_cast<ULONGLONG>(1000);
   const ULONGLONG file_time::Minute = Second * static_cast<ULONGLONG>(60);
   const ULONGLONG file_time::Hour = Minute * static_cast<ULONGLONG>(60);
   const ULONGLONG file_time::Day = Hour * static_cast<ULONGLONG>(24);
   const ULONGLONG file_time::Week = Day * static_cast<ULONGLONG>(7);


}













CLASS_DECL_ACME bool file_modified_timeout(const char * path, int iSeconds)
{

   ::file_time filetime = ::get_file_time(path);

   if (filetime.modified_timeout(iSeconds))
   {

      return true;

   }

   return false;

}

FILETIME get_file_time_now()
{

   FILETIME t = {};

   GetSystemTimeAsFileTime(&t);

   return t;

}



bool get_file_time(const char * psz,file_time & time)
{

   return get_file_time(psz,time.creation,time.modified);

}


#ifdef WINDOWS_DESKTOP


bool get_file_time(const char * psz,FILETIME & creation,FILETIME & modified)
{

   HANDLE h = CreateFileW(wstring(psz),GENERIC_READ,FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,nullptr,OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS,nullptr);

   if (h == INVALID_HANDLE_VALUE)
   {

      return false;

   }
   bool bOk = true;
   try
   {
      xxf_zero(creation);
      xxf_zero(modified);
      ::GetFileTime(h,&creation,nullptr,&modified);
   }
   catch(...)
   {
      bOk = false;
   }

   ::CloseHandle(h);

   return bOk;

}

CLASS_DECL_ACME bool set_modified_file_time(const char* psz, const ::datetime::time& time)
{

   return set_modified_file_time(psz, (FILETIME &) time.to_file_time());

}

CLASS_DECL_ACME bool set_modified_file_time(const char* psz, const FILETIME& modified)
{

   bool bOk = false;

   HANDLE h = CreateFileW(wstring(psz), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, nullptr);

   try
   {

      bOk = ::SetFileTime(h, nullptr, nullptr, &modified) != FALSE;

   }
   catch (...)
   {
   }

   ::CloseHandle(h);

   return bOk;

}

#elif defined(_UWP)


bool get_file_time(const char * psz,FILETIME & creation,FILETIME & modified)
{

   hfile hfile = hfile_create(psz, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

   bool bOk = false;

   try
   {

      xxf_zero(creation);
      xxf_zero(modified);

      if (::GetFileTime(hfile, &creation, nullptr, &modified))
      {

         bOk = true;

      }

   }
   catch (...)
   {

   }

   ::CloseHandle(hfile);

   return bOk;

}


#else


#include <sys/types.h>
#include <sys/stat.h>
#undef USE_MISC




bool get_file_time(const char * psz,FILETIME & creation,FILETIME & modified)
{

   struct stat st;

   stat(psz, &st);

   creation.dwLowDateTime = LODWORD(st.st_ctime);
   creation.dwHighDateTime = HIDWORD(st.st_ctime);

   modified.dwLowDateTime = LODWORD(st.st_mtime);
   modified.dwHighDateTime = HIDWORD(st.st_mtime);

   return true;

}


#endif
