#include "framework.h"
#include "os/cross/windows/_windows.h"

//namespace datetime
//{
//




   //filetime& filetime::operator=(const FILETIME& filetime) noexcept
   //{

   //   m_u64 = make64_from32(filetime.dwLowDateTime, filetime.dwHighDateTime);

   //   return *this;

   //}


   filetime filetime::get_current_time() noexcept
   {

#ifdef WINDOWS_DESKTOP

      FILETIME filetime;

      GetSystemTimeAsFileTime(&filetime);

      return filetime;

#else

      return 0;

#endif

   }


   filetime& filetime::operator+=(filetime_span span) noexcept
   {

      SetTime(get_time() + span.GetTimeSpan());

      return *this;

   }


   filetime& filetime::operator-=(filetime_span span) noexcept
   {
      
      SetTime(get_time() - span.GetTimeSpan());

      return *this;

   }


   filetime filetime::operator+(filetime_span span) const noexcept
   {
      return(filetime(get_time() + span.GetTimeSpan()));
   }

   filetime filetime::operator-(filetime_span span) const noexcept
   {
      return(filetime(get_time() - span.GetTimeSpan()));
   }

   filetime_span filetime::operator-(filetime ft) const noexcept
   {
      return(filetime_span(get_time() - ft.get_time()));
   }

   bool filetime::operator==(filetime ft) const noexcept
   {
      return(get_time() == ft.get_time());
   }

   bool filetime::operator!=(filetime ft) const noexcept
   {
      return(get_time() != ft.get_time());
   }

   bool filetime::operator<(filetime ft) const noexcept
   {
      return(get_time() < ft.get_time());
   }

   bool filetime::operator>(filetime ft) const noexcept
   {
      return(get_time() > ft.get_time());
   }

   bool filetime::operator<=(filetime ft) const noexcept
   {
      return(get_time() <= ft.get_time());
   }

   bool filetime::operator>=(filetime ft) const noexcept
   {
      return(get_time() >= ft.get_time());
   }


   filetime_t filetime::get_time() const noexcept
   {

      return m_filetime;

   }


   void filetime::SetTime(filetime_t nTime) noexcept
   {

      m_filetime = nTime;

   }


#ifdef WINDOWS


   filetime filetime::UTCToLocal() const noexcept
   {

      FILETIME filetimeLocal;

      auto filetimeThis = get_FILETIME();

      ::FileTimeToLocalFileTime(&filetimeThis, &filetimeLocal);

      return filetimeLocal;

   }


   filetime filetime::LocalToUTC() const noexcept
   {

      FILETIME filetimeUTC;

      auto filetimeThis = get_FILETIME();

      ::LocalFileTimeToFileTime(&filetimeThis, &filetimeUTC);

      return filetimeUTC;

   }

#endif


   const filetime_t filetime::Millisecond = 10000;
   const filetime_t filetime::Second = Millisecond * static_cast<filetime_t>(1000);
   const filetime_t filetime::Minute = Second * static_cast<filetime_t>(60);
   const filetime_t filetime::Hour = Minute * static_cast<filetime_t>(60);
   const filetime_t filetime::Day = Hour * static_cast<filetime_t>(24);
   const filetime_t filetime::Week = Day * static_cast<filetime_t>(7);

//
//}
//
//


CLASS_DECL_ACME bool file_modified_timeout(const char * path, int iSeconds)
{

   auto filetime = ::get_filetime_set(path);

   if (filetime.modified_timeout(iSeconds))
   {

      return true;

   }

   return false;

}


filetime_t get_filetime_now()
{

   FILETIME filetime = {};

   GetSystemTimeAsFileTime(&filetime);

   return make64_from32(filetime.dwLowDateTime, filetime.dwHighDateTime);

}


bool get_filetime_set(const char * psz, filetime_set & filetimeset)
{

   return get_filetime_set(psz, filetimeset.m_filetimeCreation, filetimeset.m_filetimeModified);

}


#ifdef WINDOWS_DESKTOP


bool get_filetime_set(const char * psz,filetime & filetimeCreation, filetime & filetimeModified)
{

   HANDLE h = CreateFileW(wstring(psz),GENERIC_READ,FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,nullptr,OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS,nullptr);

   if (h == INVALID_HANDLE_VALUE)
   {

      return false;

   }
   bool bOk = true;
   try
   {
      //xxf_zero(creation);
      //xxf_zero(modified);
      ::GetFileTime(h,filetimeCreation,nullptr, filetimeModified);
   }
   catch(...)
   {
      bOk = false;
   }

   ::CloseHandle(h);

   return bOk;

}

CLASS_DECL_ACME bool set_modified_filetime(const char* psz, const ::datetime::time& time)
{

   return set_modified_filetime(psz, __filetime(time));

}

CLASS_DECL_ACME bool set_modified_filetime(const char* psz, const filetime & filetimeModified)
{

   bool bOk = false;

   HANDLE h = CreateFileW(wstring(psz), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, nullptr);

   try
   {

      bOk = ::SetFileTime(h, nullptr, nullptr, filetimeModified) != FALSE;

   }
   catch (...)
   {
   }

   ::CloseHandle(h);

   return bOk;

}

#elif defined(_UWP)


bool get_filetime_set(const char * psz,FILETIME & creation,FILETIME & modified)
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


bool get_filetime_set(const char * psz, filetime & creation, filetime & modified)
{

   struct stat st;

   stat(psz, &st);

   creation.m_filetime = st.st_ctime;

   modified.m_filetime = st.st_mtime;

   return true;

}


#endif
