#pragma once


#define INTERNATIONAL_DATE_HOUR_FORMAT_FOR_FILE "%Y-%m-%d %H"
#define INTERNATIONAL_DATE_HOUR_FORMAT "%Y-%m-%d %H"

#define INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE "%Y-%m-%d %H-%M-%S"
#define INTERNATIONAL_DATE_TIME_FORMAT "%Y-%m-%d %H:%M:%S"

CLASS_DECL_APEX i32 SWN(i32 y,i32 m,i32 d);
//where DP ("Days Passed") is given by:
//   DP( y, 1 ) = 0
//  DP( y, m+1 ) = DP( y, m ) + ML( y, m )
CLASS_DECL_APEX i32 DP(i32 y,i32 m);
CLASS_DECL_APEX i32 ML(i32 y,i32 m);
CLASS_DECL_APEX i32 LEAP(i32 y);
CLASS_DECL_APEX i32 dayofweek(i32 y,i32 m,i32 d);	/* 0 = Sunday */
CLASS_DECL_APEX i32 SDOW(i32 y,i32 m,i32 d); // ( 0 = Monday, ..., 6 = Sunday )
CLASS_DECL_APEX i32 DOW(i32 y,i32 m,i32 d);
CLASS_DECL_APEX i32 getDayOfWeek(i32 month,i32 day,i32 year,i32 CalendarSystem);


namespace datetime
{


   class CLASS_DECL_APEX department:
      virtual public ::apex::department
   {
   public:
      class CLASS_DECL_APEX international:
         virtual public ::object
      {
      public:

         
         international();


         virtual ::e_status initialize(::context_object * pcontextobject) override;


         void parse_str(const char * psz,property_set & set);


         string get_gmt_date_time(const ::datetime::time & time, string strFormat = INTERNATIONAL_DATE_TIME_FORMAT);
         string get_gmt_date_time(string strFormat = INTERNATIONAL_DATE_TIME_FORMAT);
         string get_gmt_date_time_for_file();
         string get_local_date_time(const ::datetime::time & time, string strFormat = INTERNATIONAL_DATE_TIME_FORMAT);
         string get_local_date_time(string strFormat = INTERNATIONAL_DATE_TIME_FORMAT);
         string get_local_date_time_for_file();

         string get_gmt_date_time_for_file_with_no_spaces();
         string get_local_date_time_for_file_with_no_spaces();


         inline string get_gmt(string strFormat = INTERNATIONAL_DATE_TIME_FORMAT) { return get_gmt_date_time(strFormat);  }
         inline string get_gmt(const ::datetime::time & time, string strFormat = INTERNATIONAL_DATE_TIME_FORMAT) { return get_gmt_date_time(time, strFormat); }
         inline string get_local(string strFormat = INTERNATIONAL_DATE_TIME_FORMAT) { return get_local_date_time(strFormat); }
         inline string get_local(const ::datetime::time & time, string strFormat = INTERNATIONAL_DATE_TIME_FORMAT) { return get_local_date_time(time, strFormat); }


         inline string gmt() { return get_gmt(); }
         inline string gmt(const ::datetime::time & time) { return get_gmt(time); }
         inline string local() { return get_local(); }
         inline string local(const ::datetime::time & time) { return get_local(time); }




      };

      class CLASS_DECL_APEX str:
         virtual public ::object
      {
      public:


         department* m_pdatetime;
         
         
         str();

         virtual ::e_status initialize(::context_object * pcontextobject) override;
         
         string get_gmt_date_time();


      };

      class CLASS_DECL_APEX time_zone
      {
      public:

         string            m_strZone;
         double            m_dZone;
         ::datetime::time  m_time; /// time when this time zone record was last updated

      };




      __pointer(::datetime::department::international)   m_pinternational;
      __pointer(::datetime::department::str)             m_pstr;




      department();


      virtual ::e_status initialize(::context_object * pcontextobject) override;
      virtual void finalize() override;

      i32 get_month_day_count(i32 year,i32 month);
      i32 get_weekday(i32 year,i32 month,i32 day);
      i64 get_timestamp(i32 year,i32 month,i32 day);
      i64 strtotime(const ::apex::str_context * pcontext,const char * psz,time_t time,i32 iPath,i32 & iPathCount);
      i64 strtotime(const ::apex::str_context * pcontext,const char * psz,i32 iPath,i32 & iPathCount);
      i64 gmt_strtotime(const ::apex::str_context * pcontext,const char * psz,i32 iPath,i32 & iPathCount);

      ::datetime::time from_local(const string & str);
      ::datetime::time from_gmt(const string& str);

      // 1 - domingo
      string get_week_day_str(const apex::str_context * pcontext,i32 iWeekDay);
      // 1 - domingo
      string get_tiny_week_day_str(const apex::str_context * pcontext,i32 iWeekDay);
      string get_month_str(const apex::str_context * pcontext,i32 iMonth);
      string get_short_month_str(const apex::str_context * pcontext,i32 iMonth);

      static time_t s_local_mktime(i32 iHour,i32 iMinute,i32 iSecond,i32 iMonth,i32 iDay,i32 iYear);
      static time_t s_gmt_mktime(i32 iHour, i32 iMinute, i32 iSecond, i32 iMonth, i32 iDay, i32 iYear);

      ::datetime::time from_gmt_date_time(i32 iYear,i32 iMonth,i32 iDay,i32 iHour,i32 iMinute,i32 iSecond);

      inline class  international& international() { return *m_pinternational; }
      inline class str& str() { return* m_pstr; }

      string strftime(const char * psz,time_t timeParam);
      string strftime(const char * psz);


      i32 SWN(i32 y,i32 m,i32 d);
      i32 DP(i32 y,i32 m);
      i32 ML(i32 y,i32 m);
      i32 LEAP(i32 y);
      i32 dayofweek(i32 y,i32 m,i32 d);	/* 0 = Sunday */
      i32 SDOW(i32 y,i32 m,i32 d);
      i32 DOW(i32 y,i32 m,i32 d);
      i32 getDayOfWeek(i32 month,i32 day,i32 year,i32 CalendarSystem);
      i32 ISO_WN(i32  y,i32 m,i32 d);

      virtual string to_string(const ::apex::str_context* pcontext, const ::datetime::result& payload);

      virtual result span_strtotime(const ::apex::str_context* pcontext, const char* psz);
      //CLASS_DECL_APEX result strtotime(::object* pobject, const ::apex::str_context* pcontext, const char* psz, i32& iPath, i32& iPathCount, bool bForceUTC = false);

      virtual result strtotime(const ::apex::str_context* pcontext, const char* psz, i32& iPath, i32& iPathCount, bool bUTC);

      string friend_time(const ::apex::str_context * pcontext,::datetime::time timeNow,::datetime::time time);



      virtual string _001FriendTime(const ::apex::str_context* pcontext, const ::datetime::time& timeNow, const ::datetime::time& time);


      //virtual string to_string(const ::apex::str_context* pcontext, const ::datetime::result& result);


   };




} // namespace apex








inline void __exchange(::stream & stream, class ::datetime::department::time_zone & t)
{

   __TYPE_EXCHANGE(strZone);
   __TYPE_EXCHANGE(dZone);
   __TYPE_EXCHANGE(time);

}






