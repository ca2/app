#pragma once


#if defined(ANDROID) || defined(__APPLE__)

struct tm;

#endif



enum _CTIMESPANFORMATSTEP
{
   _CTFS_NONE = 0,
   _CTFS_FORMAT = 1,
   _CTFS_NZ = 2
};
#define _CTIMESPANFORMATS 3


namespace earth
{



   class time_shift
   {
   public:


      double      m_d; // in seconds;


      time_shift(double d = 0.0) : m_d(d){}


      static inline time_shift none() // UTC
      {

         return { 0.0 };

      }

      static inline time_shift local()
      {

         time_t zero = 0;

         const tm* lt = localtime(&zero);

         int unaligned = lt->tm_sec + (lt->tm_min + (lt->tm_hour * 60)) * 60;

         return { (double)(lt->tm_mon ? unaligned - 24 * 60 * 60 : unaligned) };

      }


      operator double & () { return m_d; }
      operator double () const {return m_d; }

   };


   namespace gregorian
   {


      class CLASS_DECL_ACME time
      {
      public:


         int      m_iDayOfWeek;


         ::i64    m_iNanoSecond;
         int      m_iSecond;        /* Seconds.	[0-60] (1 leap second) */
         int      m_iMinute;        /* Minutes.	[0-59] */
         int      m_iHour;          /* Hours.	[0-23] */
         int      m_iDay;           /* Day.		[1-31] */
         int      m_iMonth;         /* Month.	[0-11] */
         int      m_iYear;


         inline time()
         {


         }


         inline time(const ::earth::time & time, ::i64 iNanosecond, const time_shift & timeshift = time_shift::none());

         inline time(const ::duration & duration,  const time_shift & timeshift = time_shift::none());

         inline void set(const struct ::tm * ptm, ::i64 iNanosecond = 0)
         {

            m_iNanoSecond = iNanosecond;
            m_iSecond = ptm->tm_sec;
            m_iMinute = ptm->tm_min;
            m_iHour = ptm->tm_hour;
            m_iDay = ptm->tm_mday;
            m_iMonth = ptm->tm_mon;
            m_iYear = ptm->tm_year + 1900;

         }


         inline void set(const ::earth::time & time, ::i64 iNanosecond, const time_shift & timeshift);

         inline void set(const ::duration & time, const time_shift & timeshift);

         ::time_t get_time_t();


         inline void get(struct ::tm * ptm)
         {

            ptm->tm_sec = m_iSecond;
            ptm->tm_min = m_iMinute;
            ptm->tm_hour = m_iHour;
            ptm->tm_mday = m_iDay;
            ptm->tm_mon = m_iMonth;
            ptm->tm_year = m_iYear - 1900;

         }


         void get(system_time_t * psystemtime);
         void set(const system_time_t * psystemtime);

         void get(file_time_t * pfiletime);
         void set(const file_time_t * pfiletime);


         void Now(const time_shift & timeshift = time_shift::none());


      };


   }


   // it is in UTC by default?
   class CLASS_DECL_ACME time :
      public integral_second
   {
   public:


      using integral_second::integral_second;


      time() noexcept;
      inline time(enum_now) noexcept { m_i = now().m_i; }
      time(const time & time);
      time(time_t time) noexcept;
      time(i32 nYear, i32 nMonth, i32 nDay, i32 nHour, i32 nMin, i32 nSec, const time_shift& timeshift = time_shift::none());
      time(const file_time & ft);
#ifdef WINDOWS
      time(::u16 wDosDate, ::u16 wDosTime, i32 nDST = -1);
#endif


      static time now() noexcept;


      time& operator=(const time & time) noexcept;


      time& operator+=( date_span span );
      time& operator-=( date_span span );

      time& operator+=( time_span span ) noexcept;
      time& operator-=( time_span span ) noexcept;

      //time& operator+=( const duration & span ) noexcept;
      //time& operator-=( const duration & span ) noexcept;

      time_span operator-( time time ) const noexcept;
      time operator-( time_span span ) const noexcept;
      time operator+( time_span span ) const noexcept;

      time operator-( date_span span ) const;
      time operator+( date_span span ) const;

      //time operator-(const duration & duration) const;
      //time operator+(const duration & duration) const;

      bool operator==( time time ) const noexcept;
      bool operator!=( time time ) const noexcept;
      bool operator<( time time ) const noexcept;
      bool operator>( time time ) const noexcept;
      bool operator<=( time time ) const noexcept;
      bool operator>=( time time ) const noexcept;

      struct ::tm* tm_struct( struct ::tm* ptm, const ::earth::time_shift& timeshift = time_shift::none()) const;

      time_t get_time() const noexcept;

      i32 year(const time_shift & timeshift = time_shift::none()) const noexcept;
      i32 month(const time_shift& timeshift = time_shift::none()) const noexcept;
      i32 day(const time_shift& timeshift = time_shift::none()) const noexcept;
      i32 hour(const time_shift& timeshift = time_shift::none()) const noexcept;
      i32 minute(const time_shift& timeshift = time_shift::none()) const noexcept;
      i32 second(const time_shift& timeshift = time_shift::none()) const noexcept;
      i32 day_of_week(const time_shift& timeshift = time_shift::none()) const noexcept; // 1 = Sunday, 7 = Saturday


      time get_sunday(const time_shift& timeshift = time_shift::none()) const;

      time_t time_of_day(const time_shift& timeshift = time_shift::none()) const noexcept;
      
      i64 day_sig(const time_shift& timeshift = time_shift::none()) const noexcept;
      
      
      time_span elapsed() const;
      time_span abs_diff(const ::earth::time & time) const;


   };


   inline bool time::operator==(time time) const noexcept
   {
      return m_i == time.m_i;

   }


   inline bool time::operator!=(time time) const noexcept
   {

      return m_i != time.m_i;

   }


   inline bool time::operator<(time time) const noexcept
   {

      return m_i < time.m_i;

   }


   inline bool time::operator>(time time) const noexcept
   {

      return m_i > time.m_i;

   }


   inline bool time::operator<=(time time) const noexcept
   {

      return m_i <= time.m_i;

   }


   inline bool time::operator>=(time time) const noexcept
   {

      return m_i >= time.m_i;

   }


   inline time_span time::operator-(time time) const noexcept
   {

      return INTEGRAL_SECOND(m_i - time.m_i);

   }


   inline ::earth::time time::operator-(time_span span) const noexcept
   {

      return INTEGRAL_SECOND(m_i - span.m_i);

   }


   inline ::earth::time time::operator+(time_span span) const noexcept
   {

      return m_i + span.m_i;

   }


   inline time::time() noexcept :
      integral_second(INTEGRAL_SECOND(0))
   {

   }


   inline time::time(const time & time) :
      integral_second(INTEGRAL_SECOND(time))
   {

   }


   inline time::time(time_t time)  noexcept :
      integral_second(INTEGRAL_SECOND(time))
   {

   }


   namespace gregorian
   {


      inline time::time(const ::earth::time & time, ::i64 iNanosecond, const time_shift & timeshift)
      {

         set(time, iNanosecond, timeshift);

      }


      inline void time::set(const ::earth::time & time, ::i64 iNanosecond, const time_shift & timeshift)
      {

         struct tm tm;

         time.tm_struct(&tm, timeshift);

         set(&tm, iNanosecond);

      }


      inline time::time(const ::duration & duration, const time_shift & timeshift)
      {

         set(duration, timeshift);

      }


      inline void time::set(const ::duration & duration, const time_shift & timeshift)
      {

         set({(time_t) duration.m_iSecond }, duration.m_iNanosecond, timeshift);

      }


   } // namespace gregorian


} // namespace earth


COMPARISON_WITH_DURATION(::earth::time)



