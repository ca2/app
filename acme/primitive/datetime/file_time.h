#pragma once


#include "file_time_span.h"


class CLASS_DECL_ACME file_time
{
public:


   file_time_t           m_filetime;


   file_time() noexcept { m_filetime = 0; }
   file_time(file_time_t file_time) noexcept { m_filetime = file_time; }

   static file_time get_current_time() noexcept;


   explicit operator file_time_t &() { return m_filetime; }
   explicit operator file_time_t () const { return m_filetime; }


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

   file_time_t get_time() const noexcept;
   void SetTime(file_time_t nTime) noexcept;


   //file_time UTCToLocal() const noexcept;
   //file_time LocalToUTC() const noexcept;

   static const file_time_t Millisecond;
   static const file_time_t Second;
   static const file_time_t Minute;
   static const file_time_t Hour;
   static const file_time_t Day;
   static const file_time_t Week;

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

      if (current - m_filetimeModified > (iSeconds * 10'000'000))
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
   class zonetime;

} // namespace earth


CLASS_DECL_ACME bool file_modified_timeout(const ::file::path & path, int iSeconds);


CLASS_DECL_ACME bool get_file_time_set(const ::file::path & path, file_time_set & time);

CLASS_DECL_ACME bool get_file_time_set(const ::file::path & path, file_time & creation, file_time & modified);

CLASS_DECL_ACME bool set_modified_file_time(const ::file::path & path, const ::earth::time & time);

CLASS_DECL_ACME bool set_modified_file_time(const ::file::path & path, const file_time & modified);

inline file_time_set get_file_time_set(const ::file::path & path)
{

   file_time_set file_timeset;

   if (!get_file_time_set(path, file_timeset))
   {

      file_time_set timeNull = {};

      return timeNull;

   }

   return file_timeset;

}


//CLASS_DECL_ACME file_time __file_time(const ::earth::time & time);


//time_t __time(const file_time & file_time);



