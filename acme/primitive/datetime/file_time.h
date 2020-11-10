#pragma once


namespace datetime
{


   class CLASS_DECL_ACME file_time
   {
   public:

      filetime_t  m_filetime;


      file_time() noexcept;
      file_time(filetime_t nTime) noexcept;
#ifdef WINDOWS
      file_time(const FILETIME& ft) noexcept;
#endif

      static file_time get_current_time() noexcept;

#ifdef WINDOWS
      file_time& operator=(const FILETIME& ft) noexcept;
#endif

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

      filetime_t get_time() const noexcept;
      void SetTime(filetime_t nTime) noexcept;

      file_time UTCToLocal() const noexcept;
      file_time LocalToUTC() const noexcept;

      static const filetime_t Millisecond;
      static const filetime_t Second;
      static const filetime_t Minute;
      static const filetime_t Hour;
      static const filetime_t Day;
      static const filetime_t Week;
   };

   // Used only if these strings could not be found in resources.
   extern CLASS_DECL_ACME const char * const szInvalidDateTime;
   extern CLASS_DECL_ACME const char * const szInvalidDateTimeSpan;

   const i32 maxTimeBufferSize = 128;
   const long maxDaysInSpan  =   3615897L;




} // namesace datetime


CLASS_DECL_ACME filetime_t get_file_time_now();


struct CLASS_DECL_ACME file_time
{


//#ifdef WINDOWS
   filetime_t                         creation;
   filetime_t                         modified;
   filetime_t                         access; // Not used at Windows?
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


   bool modified_timeout(const filetime_t & current, int iSeconds)
   {

      if (current - modified > (natural(iSeconds) * 1000 * 1000 * 10))
      {

         return true;

      }

      return false;

   }


   bool modified_timeout(int iSeconds)
   {

      filetime_t current = get_file_time_now();

      return modified_timeout(current, iSeconds);

   }

};

CLASS_DECL_ACME bool file_modified_timeout(const char * path, int iSeconds);


CLASS_DECL_ACME bool get_file_time(const char * psz,file_time & time);

CLASS_DECL_ACME bool get_file_time(const char * psz, filetime_t & creation, filetime_t & modified);

CLASS_DECL_ACME bool set_modified_file_time(const char* psz, const ::datetime::time & time);

CLASS_DECL_ACME bool set_modified_file_time(const char* psz, const filetime_t & modified);

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









