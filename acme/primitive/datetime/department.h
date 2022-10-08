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


         virtual void initialize(::object * pobject) override;


         void parse_str(const string & str, property_set & set);


         string get_date_time(const ::earth::time & time, string strFormat = INTERNATIONAL_DATE_TIME_FORMAT, const ::earth::time_shift& timeshift = ::earth::time_shift::none());
         string get_date_time(string strFormat = INTERNATIONAL_DATE_TIME_FORMAT, const ::earth::time_shift& timeshift = ::earth::time_shift::none());
         string get_date_time_for_file(const ::earth::time_shift& timeshift = ::earth::time_shift::none(), const ::earth::time & time = ::earth::time::now());
         

         //string local_get_date_time(const ::earth::time & time, string strFormat = INTERNATIONAL_DATE_TIME_FORMAT);
         //string local_get_date_time(string strFormat = INTERNATIONAL_DATE_TIME_FORMAT);
         //string local_get_date_time_for_file();


         string get_date_time_for_file_with_no_spaces(const ::earth::time_shift& timeshift = ::earth::time_shift::none(), const ::earth::time & time = ::earth::time::now());
         //string local_get_date_time_for_file_with_no_spaces();


         inline string get_string(string strFormat = INTERNATIONAL_DATE_TIME_FORMAT, const ::earth::time_shift& timeshift = ::earth::time_shift::none()) { return get_date_time(strFormat, timeshift);  }
         inline string get_string(const ::earth::time & time, string strFormat = INTERNATIONAL_DATE_TIME_FORMAT, const ::earth::time_shift& timeshift = ::earth::time_shift::none()) { return get_date_time(time, strFormat, timeshift); }
         
         //inline string local_get(string strFormat = INTERNATIONAL_DATE_TIME_FORMAT) { return local_get_date_time(strFormat); }
         //inline string local_get(const ::earth::time & time, string strFormat = INTERNATIONAL_DATE_TIME_FORMAT) { return local_get_date_time(time, strFormat); }


         //inline string utc() { return utc_get(); }
         //inline string utc(const ::earth::time & time) { return utc_get(time); }
         //inline string local() { return local_get(); }
         //inline string local(const ::earth::time & time) { return local_get(time); }


      };


//      class CLASS_DECL_ACME str:
//         virtual public ::object
//      {
//      public:
//
//
//         department* m_pdatetime;
//
//
//         str();
//
//         void initialize(::object * pobject) override;
//
//         string get_date_time(const ::earth::time_shift& timeshift = ::earth::time_shift::none());
//
//
//      };





      __pointer(::datetime::department::international)   m_pinternational;
      //__pointer(::datetime::department::str)             m_pstr;




      department();


      virtual void initialize(::object * pobject) override;
      void destroy() override;


      i64 get_timestamp(i32 year, i32 month, i32 day);

      
      i32 get_month_day_count(i32 year, i32 month);


      i32 get_weekday(i32 year, i32 month, i32 day);


      i64 strtotime(const ::text::context * pcontext, const ::string & str, time_t time,i32 iPath,i32 & iPathCount, const ::earth::time_shift& timezone = ::earth::time_shift::none());
      i64 strtotime(const ::text::context * pcontext, const ::string & str, i32 iPath,i32 & iPathCount, const ::earth::time_shift& timezone = ::earth::time_shift::none());

      
      ::earth::time from_string(const ::text::context* pcontext, const ::string & str, const ::earth::time_shift& timezone = ::earth::time_shift::none());


      // 1 - domingo
      string get_week_day_str(const ::text::context * pcontext,i32 iWeekDay);
      // 1 - domingo
      string get_tiny_week_day_str(const ::text::context * pcontext,i32 iWeekDay);
      string get_month_str(const ::text::context * pcontext,i32 iMonth);
      string get_short_month_str(const ::text::context * pcontext,i32 iMonth);

      static time_t s_mktime(i32 iHour,i32 iMinute,i32 iSecond,i32 iMonth,i32 iDay,i32 iYear, const ::earth::time_shift& timezone = ::earth::time_shift::none());

      inline class  international& international() { return *m_pinternational; }
      //inline class str& str() { return* m_pstr; }

      string strftime(const string & str, const ::earth::time & time, const ::earth::time_shift& timezone = ::earth::time_shift::none());
      string strftime(const string & str, const ::earth::time_shift& timezone = ::earth::time_shift::none());

      i32 SWN(i32 y,i32 m,i32 d);
      i32 DP(i32 y,i32 m);
      i32 ML(i32 y,i32 m);
      i32 LEAP(i32 y);
      i32 dayofweek(i32 y,i32 m,i32 d);	/* 0 = Sunday */
      i32 SDOW(i32 y,i32 m,i32 d);
      i32 DOW(i32 y,i32 m,i32 d);
      i32 getDayOfWeek(i32 month,i32 day,i32 year,i32 CalendarSystem);
      i32 ISO_WN(i32  y,i32 m,i32 d);

      virtual string to_string(const ::text::context* pcontext, const ::datetime::result& result, const ::earth::time_shift& timeshift = ::earth::time_shift::none());

      virtual result span_parse_time(const ::text::context* pcontext, const string & str, const ::earth::time_shift& timeshift = ::earth::time_shift::none());

      virtual result parse_time(const ::text::context* pcontext, const string & str, i32& iPath, i32& iPathCount, const ::earth::time_shift& timeshift = ::earth::time_shift::none());

      string friend_time(const ::text::context * pcontext,::earth::time timeNow,::earth::time time, const ::earth::time_shift& timeshift = ::earth::time_shift::none());

      virtual string _001FriendTime(const ::text::context* pcontext, const ::earth::time& timeNow, const ::earth::time& time, const ::earth::time_shift& timeshift = ::earth::time_shift::none());


   };


} // namespace apex



