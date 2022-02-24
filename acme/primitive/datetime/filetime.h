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


class CLASS_DECL_ACME filetime
{
public:


   filetime_t           m_filetime;


   filetime() noexcept { m_filetime = 0; }
   filetime(filetime_t filetime) noexcept { m_filetime = filetime; }

   static filetime get_current_time() noexcept;

//#ifdef WINDOWS
//
//   filetime & operator=(const FILETIME & filetime) noexcept { m_filetime = make64_from32(filetime.dwLowDateTime, filetime.dwHighDateTime); return *this; }
//   inline FILETIME get_FILETIME() const noexcept { return {lower32_from64(m_filetime), upper32_from64(m_filetime)}; }
//
//   operator FILETIME * ()  { return (FILETIME *)&m_filetime; }
//   operator const FILETIME * () const { return (const FILETIME *)&m_filetime; }
//
//#endif

   explicit operator filetime_t &() { return m_filetime; }
   explicit operator filetime_t () const { return m_filetime; }


   filetime& operator+=(filetime_span span) noexcept;
   filetime& operator-=(filetime_span span) noexcept;

   filetime operator+(filetime_span span) const noexcept;
   filetime operator-(filetime_span span) const noexcept;
   filetime_span operator-(filetime ft) const noexcept;

   bool operator==(filetime ft) const noexcept;
   bool operator!=(filetime ft) const noexcept;
   bool operator<(filetime ft) const noexcept;
   bool operator>(filetime ft) const noexcept;
   bool operator<=(filetime ft) const noexcept;
   bool operator>=(filetime ft) const noexcept;

   filetime_t get_time() const noexcept;
   void SetTime(filetime_t nTime) noexcept;


   //filetime UTCToLocal() const noexcept;
   //filetime LocalToUTC() const noexcept;

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


//CLASS_DECL_ACME filetime_t get_filetime_now();


struct CLASS_DECL_ACME filetime_set
{


   filetime       m_filetimeCreation;
   filetime       m_filetimeModified;
   filetime       m_filetimeAccess; // Not used at Windows?


   filetime_set()
   {

      __zero(this);

   }


   bool operator == (const filetime_set & filetimeset) const
   {
      return
         &filetimeset == this ||
         (
         m_filetimeCreation == filetimeset.m_filetimeCreation
      && m_filetimeModified == filetimeset.m_filetimeModified
	   && m_filetimeAccess == filetimeset.m_filetimeAccess
            );
   }



   bool modified_timeout(const filetime & current, int iSeconds) const
   {

      if (current - m_filetimeModified > (iSeconds * 10'000'000))
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


CLASS_DECL_ACME bool get_filetime_set(const char * psz, filetime_set & time);

CLASS_DECL_ACME bool get_filetime_set(const char * psz, filetime & creation, filetime & modified);

CLASS_DECL_ACME bool set_modified_filetime(const char* psz, const ::datetime::time & time);

CLASS_DECL_ACME bool set_modified_filetime(const char* psz, const filetime & modified);

inline filetime_set get_filetime_set(const char * psz)
{

   filetime_set filetimeset;

   if (!get_filetime_set(psz, filetimeset))
   {

      filetime_set timeNull = {};

      return timeNull;

   }

   return filetimeset;

}


//CLASS_DECL_ACME filetime __filetime(const ::datetime::time & time);


//time_t __time(const filetime & filetime);



