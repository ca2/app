#pragma once


#define INTERNATIONAL_DATE_HOUR_FORMAT_FOR_FILE "%Y-%m-%d %H"
#define INTERNATIONAL_DATE_HOUR_FORMAT "%Y-%m-%d %H"

#define INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE "%Y-%m-%d %H-%M-%S"
#define INTERNATIONAL_DATE_TIME_FORMAT "%Y-%m-%d %H:%M:%S"

CLASS_DECL_ACME i32 SWN(i32 y,i32 m,i32 d);
//where DP ("Days Passed") is given by:
//   DP( y, 1 ) = 0
//  DP( y, m+1 ) = DP( y, m ) + ML( y, m )
CLASS_DECL_ACME i32 DP(i32 y,i32 m);
CLASS_DECL_ACME i32 ML(i32 y,i32 m);
CLASS_DECL_ACME i32 LEAP(i32 y);
CLASS_DECL_ACME i32 dayofweek(i32 y,i32 m,i32 d);	/* 0 = Sunday */
CLASS_DECL_ACME i32 SDOW(i32 y,i32 m,i32 d); // ( 0 = Monday, ..., 6 = Sunday )
CLASS_DECL_ACME i32 DOW(i32 y,i32 m,i32 d);
CLASS_DECL_ACME i32 getDayOfWeek(i32 month,i32 day,i32 year,i32 CalendarSystem);


namespace datetime
{


   class CLASS_DECL_ACME department:
      virtual public ::acme::department
   {
   public:


      class CLASS_DECL_ACME international:
         virtual public ::object
      {
      public:

         
         international();


         virtual ::e_status initialize(::object * pobject) override;


         void parse_str(const string & str, property_set & set);


         string get_date_time(const ::datetime::time & time, string strFormat = INTERNATIONAL_DATE_TIME_FORMAT, const ::time_shift& timeshift = ::time_shift::none());
         string get_date_time(string strFormat = INTERNATIONAL_DATE_TIME_FORMAT, const ::time_shift& timeshift = ::time_shift::none());
         string get_date_time_for_file(const ::time_shift& timeshift = ::time_shift::none());
         

         //string local_get_date_time(const ::datetime::time & time, string strFormat = INTERNATIONAL_DATE_TIME_FORMAT);
         //string local_get_date_time(string strFormat = INTERNATIONAL_DATE_TIME_FORMAT);
         //string local_get_date_time_for_file();


         string get_date_time_for_file_with_no_spaces(const ::time_shift& timeshift = ::time_shift::none());
         //string local_get_date_time_for_file_with_no_spaces();


         inline string get_string(string strFormat = INTERNATIONAL_DATE_TIME_FORMAT, const ::time_shift& timeshift = ::time_shift::none()) { return get_date_time(strFormat, timeshift);  }
         inline string get_string(const ::datetime::time & time, string strFormat = INTERNATIONAL_DATE_TIME_FORMAT, const ::time_shift& timeshift = ::time_shift::none()) { return get_date_time(time, strFormat, timeshift); }
         
         //inline string local_get(string strFormat = INTERNATIONAL_DATE_TIME_FORMAT) { return local_get_date_time(strFormat); }
         //inline string local_get(const ::datetime::time & time, string strFormat = INTERNATIONAL_DATE_TIME_FORMAT) { return local_get_date_time(time, strFormat); }


         //inline string utc() { return utc_get(); }
         //inline string utc(const ::datetime::time & time) { return utc_get(time); }
         //inline string local() { return local_get(); }
         //inline string local(const ::datetime::time & time) { return local_get(time); }


      };


      class CLASS_DECL_ACME str:
         virtual public ::object
      {
      public:


         department* m_pdatetime;
         
         
         str();

         virtual ::e_status initialize(::object * pobject) override;
         
         string get_date_time(const ::time_shift& timeshift = ::time_shift::none());


      };

      class CLASS_DECL_ACME time_zone
      {
      public:

         string            m_strZone;
         double            m_dZone;
         ::datetime::time  m_time; /// time when this time zone record was last updated

      };




      __pointer(::datetime::department::international)   m_pinternational;
      __pointer(::datetime::department::str)             m_pstr;




      department();


      virtual ::e_status initialize(::object * pobject) override;
      ::e_status destroy() override;


      i64 get_timestamp(i32 year, i32 month, i32 day);

      
      i32 get_month_day_count(i32 year, i32 month);


      i32 get_weekday(i32 year, i32 month, i32 day);


      i64 strtotime(const ::text::context * pcontext, const ::string & str, time_t time,i32 iPath,i32 & iPathCount, const time_shift& timezone = ::time_shift::none());
      i64 strtotime(const ::text::context * pcontext, const ::string & str, i32 iPath,i32 & iPathCount, const time_shift& timezone = ::time_shift::none());

      
      ::datetime::time from_string(const ::text::context* pcontext, const ::string & str, const time_shift& timezone = ::time_shift::none());


      // 1 - domingo
      string get_week_day_str(const ::text::context * pcontext,i32 iWeekDay);
      // 1 - domingo
      string get_tiny_week_day_str(const ::text::context * pcontext,i32 iWeekDay);
      string get_month_str(const ::text::context * pcontext,i32 iMonth);
      string get_short_month_str(const ::text::context * pcontext,i32 iMonth);

      static time_t s_mktime(i32 iHour,i32 iMinute,i32 iSecond,i32 iMonth,i32 iDay,i32 iYear, const time_shift& timezone = ::time_shift::none());

      inline class  international& international() { return *m_pinternational; }
      inline class str& str() { return* m_pstr; }

      string strftime(const string & str, const ::datetime::time & time, const time_shift& timezone = ::time_shift::none());
      string strftime(const string & str, const time_shift& timezone = ::time_shift::none());

      i32 SWN(i32 y,i32 m,i32 d);
      i32 DP(i32 y,i32 m);
      i32 ML(i32 y,i32 m);
      i32 LEAP(i32 y);
      i32 dayofweek(i32 y,i32 m,i32 d);	/* 0 = Sunday */
      i32 SDOW(i32 y,i32 m,i32 d);
      i32 DOW(i32 y,i32 m,i32 d);
      i32 getDayOfWeek(i32 month,i32 day,i32 year,i32 CalendarSystem);
      i32 ISO_WN(i32  y,i32 m,i32 d);

      virtual string to_string(const ::text::context* pcontext, const ::datetime::result& result, const time_shift& timeshift = ::time_shift::none());

      virtual result span_parse_time(const ::text::context* pcontext, const string & str, const time_shift& timeshift = ::time_shift::none());

      virtual result parse_time(const ::text::context* pcontext, const string & str, i32& iPath, i32& iPathCount, const time_shift& timeshift = ::time_shift::none());

      string friend_time(const ::text::context * pcontext,::datetime::time timeNow,::datetime::time time, const time_shift& timeshift = ::time_shift::none());

      virtual string _001FriendTime(const ::text::context* pcontext, const ::datetime::time& timeNow, const ::datetime::time& time, const time_shift& timeshift = ::time_shift::none());


   };




} // namespace apex








inline void __exchange(::stream & stream, class ::datetime::department::time_zone & t)
{

   __TYPE_EXCHANGE(strZone);
   __TYPE_EXCHANGE(dZone);
   __TYPE_EXCHANGE(time);

}






