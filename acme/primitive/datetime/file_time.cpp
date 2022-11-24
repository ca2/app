#include "framework.h"
//#include "file_time.h"
//#include "acme/primitive/primitive/payload.h"
#include "acme/operating_system/time.h"
#include "acme/_operating_system.h"


file_time file_time::get_current_time() noexcept
{

#ifdef WINDOWS_DESKTOP

   FILETIME file_time;

   GetSystemTimeAsFileTime(&file_time);

   return *(const ::file_time *) &file_time;

#else

   return 0;

#endif

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


file_time_t file_time::get_time() const noexcept
{

   return m_filetime;

}


void file_time::SetTime(file_time_t nTime) noexcept
{

   m_filetime = nTime;

}


//#ifdef WINDOWS
//
//
//   file_time file_time::UTCToLocal() const noexcept
//   {
//
//      FILETIME file_timeLocal;
//
//      auto file_timeThis = get_FILETIME();
//
//      ::FileTimeToLocalFileTime(&file_timeThis, &file_timeLocal);
//
//      return file_timeLocal;
//
//   }
//
//
//   file_time file_time::LocalToUTC() const noexcept
//   {
//
//      FILETIME file_timeUTC;
//
//      auto file_timeThis = get_FILETIME();
//
//      ::LocalFileTimeToFileTime(&file_timeThis, &file_timeUTC);
//
//      return file_timeUTC;
//
//   }
//
//#endif


const file_time_t file_time::Millisecond = 10000;
const file_time_t file_time::Second = Millisecond * static_cast<file_time_t>(1000);
const file_time_t file_time::Minute = Second * static_cast<file_time_t>(60);
const file_time_t file_time::Hour = Minute * static_cast<file_time_t>(60);
const file_time_t file_time::Day = Hour * static_cast<file_time_t>(24);
const file_time_t file_time::Week = Day * static_cast<file_time_t>(7);


CLASS_DECL_ACME bool file_modified_timeout(const char * path, int iSeconds)
{

   auto file_time = ::get_file_time_set(path);

   if (file_time.modified_timeout(iSeconds))
   {

      return true;

   }

   return false;

}


//namespace acme
//{
//
//
//   file_time node::get_file_time_now()
//   {
//
//      file_time file_time;
//
//      auto pnode = get_system()->node();
//
//      pnode->get_system_time_as_file_time(&file_time.m_filetime);
//
//      return file_time;
//
//      //return make64_from32(file_time.dwLowDateTime, file_time.dwHighDateTime);
//
//   }
//
//
//
//   void node::is_valid_file_time(const file_time_t * pfile_time)
//   {
//
//      ::file_time localtime;
//
//      auto estatus = file_time_to_local_file_time(&localtime.m_filetime, pfile_time);
//
//      if(!estatus)
//      {
//
//         return error_failed;
//
//      }
//
//      // then convert that time to system time
//      system_time systemtime;
//
//      estatus = file_time_to_system_time(&systemtime, &localtime.m_filetime);
//
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;
//
//   }
//
//
//   void node::file_time_to_time(time_t * ptime, const file_time_t * pfile_time, i32 nDST)
//   {
//
//      system_time_t systemtime;
//
//      auto estatus = file_time_to_system_time(&systemtime, pfile_time);
//
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      estatus = system_time_to_time(ptime, &systemtime);
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;
//
//   }
//
//
//} // namespace acme
//

bool get_file_time_set(const char * psz, file_time_set & file_timeset)
{

   return get_file_time_set(psz, file_timeset.m_filetimeCreation, file_timeset.m_filetimeModified);

}


#ifdef WINDOWS_DESKTOP


bool get_file_time_set(const char * psz, file_time & file_timeCreation, file_time & file_timeModified)
{

   HANDLE h = CreateFileW(wstring(psz),GENERIC_READ,FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,nullptr,OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS,nullptr);

   if (h == INVALID_HANDLE_VALUE)
   {

      return false;

   }
   
   bool bOk = true;

   try
   {
      
      //zero(creation);
      //zero(modified);
      ::GetFileTime(h,(FILETIME*)&file_timeCreation,nullptr, (FILETIME *)&file_timeModified);

   }
   catch(...)
   {
      bOk = false;
   }

   ::CloseHandle(h);

   return bOk;

}


CLASS_DECL_ACME bool set_modified_file_time(const char* psz, const ::earth::time& time)
{

   ::file_time file_time;

   time_to_file_time(&file_time.m_filetime, &time.m_i);

   return set_modified_file_time(psz, file_time);

}


CLASS_DECL_ACME bool set_modified_file_time(const char* psz, const file_time & file_timeModified)
{

   bool bOk = false;

   HANDLE h = CreateFileW(wstring(psz), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, nullptr);

   try
   {

      bOk = ::SetFileTime(h, nullptr, nullptr, (FILETIME*)&file_timeModified) != false;

   }
   catch (...)
   {
   }

   ::CloseHandle(h);

   return bOk;

}

#elif defined(_UWP)




#else


#include <sys/types.h>
#include <sys/stat.h>
#undef USE_MISC


bool get_file_time_set(const char * psz, file_time & creation, file_time & modified)
{

   struct stat st;

   stat(psz, &st);

   creation.m_filetime = st.st_ctime;

   modified.m_filetime = st.st_mtime;

   return true;

}


#endif



void copy(payload * ppayload, const file_time * pfile_time)
{

   ppayload->set_type(e_type_file_time, false);

   ppayload->m_filetime = pfile_time->m_filetime;

}


bool file_time_set::modified_timeout(int iSeconds) const
{

   auto file_timeNow = get_file_time_now();

   return modified_timeout(file_timeNow, iSeconds);

}



