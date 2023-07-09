#pragma once


#include "file_time_span.h"


struct file_time_t {};


class CLASS_DECL_ACME file_time
{
public:


   // Contains a 64-bit value representing the number
   // of 100-nanosecond intervals since January 1, 1601 (UTC).
   ::u64          m_uFileTime;


   file_time() noexcept { m_uFileTime = 0; }
   file_time(file_time_t, ::u64 uFileTime) noexcept { m_uFileTime = uFileTime; }
   explicit file_time(const system_time & systemtime);
   explicit file_time(const ::posix_time & time);
   explicit file_time(const class ::time & time);
   explicit file_time(const ::earth::gregorian_time & gregoriantime);
   // ystem_time_as_file_time();
   //file_time(local_const ::file_time & filetime);
   //file_time(const ::earth::time & time);
   file_time(now_t);

   static file_time get_current_time() noexcept;


   //explicit operator file_time_t &() { return m_filetime; }
   //explicit operator file_time_t () const { return m_filetime; }


   file_time& operator+=(file_time_span span) noexcept;
   file_time& operator-=(file_time_span span) noexcept;

   file_time operator+(file_time_span span) const noexcept;
   file_time operator-(file_time_span span) const noexcept;
   file_time_span operator-(file_time ft) const noexcept;

   bool operator==(file_time ft) const noexcept;
   std::strong_ordering operator<=>(file_time ft) const noexcept;
   //bool operator<(file_time ft) const noexcept;
   //bool operator>(file_time ft) const noexcept;
   //bool operator<=(file_time ft) const noexcept;
   //bool operator>=(file_time ft) const noexcept;

   ::u64 get_file_time() const noexcept;
   void set_file_time(::u64 nTime) noexcept;


   
   //file_time UTCToLocal() const noexcept;
   //file_time LocalToUTC() const noexcept;

   //static const file_time_t Millisecond;
   //static const file_time_t Second;
   //static const file_time_t Minute;
   //static const file_time_t Hour;
   //static const file_time_t Day;
   //static const file_time_t Week;

};


// Used only if these strings could not be found in resources.
extern CLASS_DECL_ACME const char * const szInvalidDateTime;
extern CLASS_DECL_ACME const char * const szInvalidDateTimeSpan;

const i32 maxTimeBufferSize = 128;
const long maxDaysInSpan  =   3615897L;


//CLASS_DECL_ACME file_time_t get_file_time_now();


struct CLASS_DECL_ACME file_time_set
{


   file_time       m_filetimeCreation;
   file_time       m_filetimeModified;
   file_time       m_filetimeAccess; // Not used at Windows?


   file_time_set() {}


   bool operator == (const file_time_set & file_timeset) const
   {
      return
         &file_timeset == this ||
         (
         m_filetimeCreation == file_timeset.m_filetimeCreation
      && m_filetimeModified == file_timeset.m_filetimeModified
	   && m_filetimeAccess == file_timeset.m_filetimeAccess
            );
   }



   bool modified_timeout(const file_time & current, int iSeconds) const
   {

      if ((current - m_filetimeModified).m_iFileTimeSpan > (iSeconds * 10'000'000))
      {

         return true;

      }

      return false;

   }


   bool modified_timeout(int iSeconds) const;

};


namespace earth
{

   class time;
   class zone_time;

} // namespace earth


CLASS_DECL_ACME bool file_modified_timeout(const ::file::path & path, int iSeconds);


CLASS_DECL_ACME void get_file_time_set(const ::file::path & path, file_time_set & time);

CLASS_DECL_ACME void get_file_time_set(const ::file::path & path, file_time & creation, file_time & modified);

CLASS_DECL_ACME void set_modified_file_time(const ::file::path & path, const class ::time & time);

CLASS_DECL_ACME void set_modified_file_time(const ::file::path & path, const file_time & modified);

inline file_time_set get_file_time_set(const ::file::path & path)
{

   file_time_set filetimeset;

   try
   {

      get_file_time_set(path, filetimeset);

   }
   catch (...)
   {

      return {};
      
   }

   return filetimeset;

}


//CLASS_DECL_ACME file_time __file_time(const ::earth::time & time);


//posix_time __time(const file_time & file_time);



CLASS_DECL_ACME file_time as_local_file_time(const ::file_time & filetime);



