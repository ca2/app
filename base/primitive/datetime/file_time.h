#pragma once


namespace datetime
{


   class CLASS_DECL_AURA file_time:
      public FILETIME
   {
   public:


      file_time() noexcept;
      file_time(const FILETIME& ft) noexcept;
      file_time(ULONGLONG nTime) noexcept;

      static file_time WINAPI get_current_time() noexcept;

      file_time& operator=(const FILETIME& ft) noexcept;

      file_time& operator+=(file_time_span span) noexcept;
      file_time& operator-=(file_time_span span) noexcept;

      file_time operator+(file_time_span span) const noexcept;
      file_time operator-(file_time_span span) const noexcept;
      file_time_span operator-(file_time ft) const noexcept;

      bool operator==(file_time ft) const noexcept;
      bool operator!=(file_time ft) const noexcept;
      bool operator<(file_time ft) const noexcept;
      bool operator>(file_time ft) const noexcept;
      bool operator<=(file_time ft) const noexcept;
      bool operator>=(file_time ft) const noexcept;

      ULONGLONG get_time() const noexcept;
      void SetTime(ULONGLONG nTime) noexcept;

      file_time UTCToLocal() const noexcept;
      file_time LocalToUTC() const noexcept;

      static const ULONGLONG Millisecond;
      static const ULONGLONG Second;
      static const ULONGLONG Minute;
      static const ULONGLONG Hour;
      static const ULONGLONG Day;
      static const ULONGLONG Week;
   };

   // Used only if these strings could not be found in resources.
   extern CLASS_DECL_AURA const char * const szInvalidDateTime;
   extern CLASS_DECL_AURA const char * const szInvalidDateTimeSpan;

   const i32 maxTimeBufferSize = 128;
   const long maxDaysInSpan  =   3615897L;




} // namesace datetime


CLASS_DECL_AURA FILETIME get_file_time_now();


struct CLASS_DECL_AURA file_time
{


//#ifdef WINDOWS
   FILETIME                         creation;
   FILETIME                         modified;
   FILETIME                         access; // Not used at Windows?
//#else
  // __time_t                         creation;
//   __time_t                         access;
  // __time_t                         modified;
//#endif


   file_time()
   {

      xxf_zero(creation);
      xxf_zero(modified);
      xxf_zero(access);

   }


   bool operator == (const file_time & t) const
   {
      if(&t == this)
         return true;
      return
         !__memcmp(&creation ,  &t.creation ,sizeof(creation))
      && !__memcmp(&modified ,  &t.modified ,sizeof(modified))
	   && !__memcmp(&access   ,  &t.access   ,sizeof(access));
   }


   bool modified_timeout(const FILETIME & current, int iSeconds)
   {

      u64 mod = (u64)modified.dwLowDateTime | ((u64) modified.dwHighDateTime << 32);

      u64 now = (u64)current.dwLowDateTime | ((u64)current.dwHighDateTime << 32);

      if (now - mod > (natural(iSeconds) * 1000 * 1000 * 10))
      {

         return true;

      }

      return false;

   }


   bool modified_timeout( int iSeconds)
   {

      FILETIME current = get_file_time_now();

      return modified_timeout(current, iSeconds);

   }

};

CLASS_DECL_AURA bool file_modified_timeout(const char * path, int iSeconds);


CLASS_DECL_AURA bool get_file_time(const char * psz,file_time & time);

CLASS_DECL_AURA bool get_file_time(const char * psz,FILETIME & creation,FILETIME & modified);

CLASS_DECL_AURA bool set_modified_file_time(const char* psz, const ::datetime::time & time);

CLASS_DECL_AURA bool set_modified_file_time(const char* psz, const FILETIME& modified);

inline file_time get_file_time(const char * psz)
{

   file_time time ={};

   if (!get_file_time(psz, time))
   {

      file_time timeNull = {};

      return timeNull;

   }

   return time;

}









