#pragma once


#define make64_from32(l, h) ((::u64) (l)) | (((::u64) (h)) << 32)
#define first_u16(u) ((u) & 0xffff)
#define second_u16(u) (((u) >> 16) & 0xffff)
#define first_i16(u) ((::i16)(((::i32)(u)) & 0xffff)) // signed first_u16 or at least should be designed to be signed
#define second_i16(u) ((::i16)((((::i32)(u)) >> 16) & 0xffff)) // signed second_u16 or at least should be designed to be signed
#define x_i16(u) first_i16(u)
#define y_i16(u) second_i16(u)
#define lower32_from64(u) ((u) & 0xffffffff)
#define upper32_from64(u) ((u >> 32) & 0xffffffff)


class CLASS_DECL_ACME file_time
{
public:


   file_time_t           m_file_time;


   file_time() noexcept { m_file_time = 0; }
   file_time(file_time_t file_time) noexcept { m_file_time = file_time; }

   static file_time get_current_time() noexcept;

//#ifdef WINDOWS
//
//   file_time & operator=(const FILETIME & file_time) noexcept { m_file_time = make64_from32(file_time.dwLowDateTime, file_time.dwHighDateTime); return *this; }
//   inline FILETIME get_FILETIME() const noexcept { return {lower32_from64(m_file_time), upper32_from64(m_file_time)}; }
//
//   operator FILETIME * ()  { return (FILETIME *)&m_file_time; }
//   operator const FILETIME * () const { return (const FILETIME *)&m_file_time; }
//
//#endif

   explicit operator file_time_t &() { return m_file_time; }
   explicit operator file_time_t () const { return m_file_time; }


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


   file_time       m_file_timeCreation;
   file_time       m_file_timeModified;
   file_time       m_file_timeAccess; // Not used at Windows?


   file_time_set()
   {

      __zero(this);

   }


   bool operator == (const file_time_set & file_timeset) const
   {
      return
         &file_timeset == this ||
         (
         m_file_timeCreation == file_timeset.m_file_timeCreation
      && m_file_timeModified == file_timeset.m_file_timeModified
	   && m_file_timeAccess == file_timeset.m_file_timeAccess
            );
   }



   bool modified_timeout(const file_time & current, int iSeconds) const
   {

      if (current - m_file_timeModified > (iSeconds * 10'000'000))
      {

         return true;

      }

      return false;

   }


   bool modified_timeout(int iSeconds) const;

};


namespace datetime
{

   class time;

} // namespace datetime


CLASS_DECL_ACME bool file_modified_timeout(const char * path, int iSeconds);


CLASS_DECL_ACME bool get_file_time_set(const char * psz, file_time_set & time);

CLASS_DECL_ACME bool get_file_time_set(const char * psz, file_time & creation, file_time & modified);

CLASS_DECL_ACME bool set_modified_file_time(const char* psz, const ::datetime::time & time);

CLASS_DECL_ACME bool set_modified_file_time(const char* psz, const file_time & modified);

inline file_time_set get_file_time_set(const char * psz)
{

   file_time_set file_timeset;

   if (!get_file_time_set(psz, file_timeset))
   {

      file_time_set timeNull = {};

      return timeNull;

   }

   return file_timeset;

}


//CLASS_DECL_ACME file_time __file_time(const ::datetime::time & time);


//time_t __time(const file_time & file_time);



