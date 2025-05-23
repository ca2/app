#include "framework.h"
//#include "file_time.h"
//#include "acme/prototype/prototype/payload.h"
#include "acme/prototype/datetime/earth_gregorian_time.h"
#include "acme/prototype/datetime/system_time.h"
#include "acme/_operating_system.h"


file_time::file_time(now_t) :
   file_time(system_time(now_t{}))
{


      //system_time systemtime;

      ////auto estatus = get_system_time(&systemtime);

      //auto systemtime = now_as_system_time();

      ////if (!estatus)
      ////{

      ////   return estatus;

      ////}

      ///*estatus = */

      //return as_file_time(systemtime);

      ////if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;


}
//
//
//file_time::file_time(const system_time & systemtime) :
//   file_time(::earth::gregorian_time(systemtime))
//{
//
//
//}
//

file_time::file_time(const ::posix_time & time) :
   file_time(::earth::gregorian_time(time))
{

   //auto systemtime = as_system_time(time);

   //auto filetime = as_file_time(systemtime);

   //return filetime;

}


file_time::file_time(const class ::time & time)
{

   auto centimicroseconds = time.m_iSecond * 10'000'000 + time.m_iNanosecond / 100;

   centimicroseconds += (EPOCH_DIFFERENCE_NANOS/100);

   m_uFileTime = centimicroseconds;

}


file_time::file_time(const ::earth::gregorian_time & gregoriantime) :
   file_time(system_time(gregoriantime))
{

   //system_time systemtime;

   //get(&systemtime);

   //filetime = as_file_time(&systemtime);

}


file_time file_time::now() noexcept
{

   return now_t{};

//#ifdef WINDOWS_DESKTOP
//
//   FILETIME file_time;
//
//   GetSystemTimeAsFileTime(&file_time);
//
//   return *(const ::file_time *) &file_time;
//
//#else
//
//   ::file_time filetime(now_t{});
//
//   return filetime;
//
//#endif

}


file_time& file_time::operator +=(file_time_span span) noexcept
{

   set_file_time(get_file_time() + span.get_file_time_span());

   return *this;

}


file_time& file_time::operator-=(file_time_span span) noexcept
{
      
   set_file_time(get_file_time() - span.get_file_time_span());

   return *this;

}


file_time file_time::operator +(file_time_span span) const noexcept
{
   return{ file_time_t{}, get_file_time() + span.get_file_time_span() };
}

file_time file_time::operator-(file_time_span span) const noexcept
{
   return { file_time_t{}, get_file_time() - span.get_file_time_span() };
}


file_time_span file_time::operator-(file_time ft) const noexcept
{

   return{ file_time_span_t{}, (long long) get_file_time() -(long long) ft.get_file_time() };

}


bool file_time::operator==(file_time ft) const noexcept
{

   return get_file_time() == ft.get_file_time();

}


//bool file_time::operator!=(file_time ft) const noexcept
//{
//   return(get_file_time() != ft.get_file_time());
//}

::std::strong_ordering  file_time::operator<=>(file_time ft) const noexcept
{
   return get_file_time() <=> ft.get_file_time();
}

//bool file_time::operator>(file_time ft) const noexcept
//{
//   return(get_file_time() > ft.get_file_time());
//}
//
//bool file_time::operator<=(file_time ft) const noexcept
//{
//   return(get_file_time() <= ft.get_file_time());
//}
//
//bool file_time::operator>=(file_time ft) const noexcept
//{
//   return(get_file_time() >= ft.get_file_time());
//}


unsigned long long file_time::get_file_time() const noexcept
{

   return m_uFileTime;

}


void file_time::set_file_time(unsigned long long uFileTime) noexcept
{

   m_uFileTime = uFileTime;

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


//const file_time_t file_time::Millisecond = 10000;
//const file_time_t file_time::Second = Millisecond * static_cast<file_time_t>(1000);
//const file_time_t file_time::Minute = Second * static_cast<file_time_t>(60);
//const file_time_t file_time::Hour = Minute * static_cast<file_time_t>(60);
//const file_time_t file_time::Day = Hour * static_cast<file_time_t>(24);
//const file_time_t file_time::Week = Day * static_cast<file_time_t>(7);


CLASS_DECL_ACME bool file_modified_timeout(const ::file::path & path, int iSeconds)
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
//      auto pnode = system()->node();
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
//   void node::file_time_to_time(posix_time * ptime, const file_time_t * pfile_time, int nDST)
//   {
//
//      system_time systemtime;
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
//      estatus = system_time_to_earth_time(ptime, &systemtime);
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

void get_file_time_set(const ::file::path & path, file_time_set & file_timeset)
{

   return get_file_time_set(path, file_timeset.m_filetimeCreation, file_timeset.m_filetimeModified);

}


#ifdef WINDOWS


void get_file_time_set(const ::file::path & path, file_time & file_timeCreation, file_time & file_timeModified)
{

   ::windows::file_instance file;
   
   if (!file.safe_create_file(
      path,
      GENERIC_READ,
      FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
      nullptr,
      OPEN_EXISTING,
      FILE_FLAG_BACKUP_SEMANTICS,
      nullptr))
   {

      DWORD dwLastError = ::GetLastError();

      throw_last_error_exception(path, ::file::e_open_read, dwLastError, "get_file_time_set safe_create_file failed");

   }

   file.get_file_time((FILETIME*)&file_timeCreation,nullptr, (FILETIME *)&file_timeModified);

}


CLASS_DECL_ACME void set_modified_file_time(const ::file::path & path, const class ::time& time)
{

   //auto filetime = as_file_time(&time);

   //set_modified_file_time(path, file_time(time));
   set_modified_file_time(path, file_time(time));

}


CLASS_DECL_ACME void set_modified_file_time(const ::file::path & path, const file_time & filetimeModified)
{

   ::windows::file_instance file;
   
   if (!file.safe_create_file(path, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, nullptr))
   {

      DWORD dwLastError = ::GetLastError();

      throw_last_error_exception(path, ::file::e_open_write, dwLastError, "set_modified_file_time safe_create_file failed");

   }

   file.set_file_time(nullptr, nullptr, (FILETIME*)&filetimeModified);

}


#else


#include <sys/types.h>
#include <sys/stat.h>
#undef USE_MISC


void get_file_time_set(const ::file::path & path, file_time & creation, file_time & modified)
{

   struct stat st;

   stat(path, &st);

   creation = file_time({ posix_time_t{}, st.st_ctime });

   modified = file_time({ posix_time_t{}, st.st_mtime });

}


#endif



void copy(payload * ppayload, const file_time * pfiletime)
{

   ppayload->set_type(e_type_file_time, false);

   ppayload->m_filetime =*pfiletime;

}


bool file_time_set::modified_timeout(int iSeconds) const
{

   //auto filetimeNow = now_as_file_time();

   return modified_timeout(now_t{}, iSeconds);

}





CLASS_DECL_ACME file_time as_local_file_time(const ::file_time & filetime)
{


   return {};

}