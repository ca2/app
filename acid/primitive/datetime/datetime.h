// From department to datetime by camilo on 2022-11-19 04:41 <3ThomasBorregaardSorensen!!
#pragma once


////#include "acid/primitive/primitive/object.h"
#include "acid/platform/department.h"
#include "earth_time_shift.h"
#include "result.h"
////#include "acid/primitive/datetime/earth_time.h"


#define INTERNATIONAL_DATE_FORMAT_FOR_FILE "%Y-%m-%d"
#define INTERNATIONAL_DATE_FORMAT "%Y-%m-%d"

#define INTERNATIONAL_DATE_HOUR_FORMAT_FOR_FILE_WITH_NO_SPACES "%Y-%m-%d_%H"
#define INTERNATIONAL_DATE_HOUR_FORMAT_FOR_FILE "%Y-%m-%d %H"
#define INTERNATIONAL_DATE_HOUR_FORMAT "%Y-%m-%d %H"

#define INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE_WITH_NO_SPACES "%Y-%m-%d_%H-%M-%S"
#define INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE "%Y-%m-%d %H-%M-%S"
#define INTERNATIONAL_DATE_TIME_FORMAT "%Y-%m-%d %H:%M:%S"


CLASS_DECL_ACID i32 SWN(i32 y,i32 m,i32 d);
//where DP ("Days Passed") is given by:
//   DP( y, 1 ) = 0
//  DP( y, m+1 ) = DP( y, m ) + ML( y, m )
CLASS_DECL_ACID i32 DP(i32 y,i32 m);
CLASS_DECL_ACID i32 ML(i32 y,i32 m);
CLASS_DECL_ACID i32 LEAP(i32 y);
CLASS_DECL_ACID i32 dayofweek(i32 y,i32 m,i32 d);	/* 0 = Sunday */
CLASS_DECL_ACID i32 SDOW(i32 y,i32 m,i32 d); // ( 0 = Monday, ..., 6 = Sunday )
CLASS_DECL_ACID i32 DOW(i32 y,i32 m,i32 d);
CLASS_DECL_ACID i32 getDayOfWeek(i32 month,i32 day,i32 year,i32 CalendarSystem);


namespace datetime
{


   class CLASS_DECL_ACID datetime:
      virtual public ::acid::department
   {
   public:


      //class CLASS_DECL_ACID international:
      //   virtual public ::object
      //{
      //public:

      //   
      //   international();


      //   virtual void initialize(::particle * pparticle) override;


      //   ::posix_time parse(const string & str);

      //   void parse_str(const string & str, property_set & set);
      //   ::earth::time parse_str(const string & str);


      //   string date_time_text(const ::earth::time & time, string strFormat = INTERNATIONAL_DATE_TIME_FORMAT, const class ::time& timeshift = {});
      //   string date_time_text(string strFormat = INTERNATIONAL_DATE_TIME_FORMAT, const class ::time& timeshift = {});
      //   string date_time_text_for_file(const class ::time& timeshift = {}, const ::earth::time & time = ::earth::time::now());

      //   string date_text(const ::earth::time & time, string strFormat = INTERNATIONAL_DATE_FORMAT, const class ::time & timeshift = {});
      //   string date_text(string strFormat = INTERNATIONAL_DATE_FORMAT, const class ::time & timeshift = {});
      //   string date_text_for_file(const class ::time & timeshift = {}, const ::earth::time & time = ::earth::time::now());
      //   

      //   //string local_get_date_time(const ::earth::time & time, string strFormat = INTERNATIONAL_DATE_TIME_FORMAT);
      //   //string local_get_date_time(string strFormat = INTERNATIONAL_DATE_TIME_FORMAT);
      //   //string local_get_date_time_for_file();


      //   string get_date_time_for_file_with_no_spaces(const class ::time& timeshift = {}, const ::earth::time & time = ::earth::time::now());
      //   //string local_get_date_time_for_file_with_no_spaces();


      //   inline string format(const ::scoped_string & strFormat = INTERNATIONAL_DATE_TIME_FORMAT, const class ::time& timeshift = {}) { return date_time_text(strFormat, timeshift);  }
      //   inline string format(const ::earth::time & time, string strFormat = INTERNATIONAL_DATE_TIME_FORMAT, const class ::time& timeshift = {}) { return date_time_text(time, strFormat, timeshift); }
      //   
      //   //inline string local_get(string strFormat = INTERNATIONAL_DATE_TIME_FORMAT) { return local_get_date_time(strFormat); }
      //   //inline string local_get(const ::earth::time & time, string strFormat = INTERNATIONAL_DATE_TIME_FORMAT) { return local_get_date_time(time, strFormat); }


      //   //inline string utc() { return utc_get(); }
      //   //inline string utc(const ::earth::time & time) { return utc_get(time); }
      //   //inline string local() { return local_get(); }
      //   //inline string local(const ::earth::time & time) { return local_get(time); }


      //};


//      class CLASS_DECL_ACID str:
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
//         void initialize(::particle * pparticle) override;
//
//         string get_date_time(const class ::time& timeshift = {});
//
//
//      };





      //::pointer<::datetime::datetime::international>  m_pinternational;
      //::pointer<::datetime::datetime::str>            m_pstr;




      datetime();
      ~datetime() override;


      void initialize(::particle * pparticle) override;
      void destroy() override;


      i64 get_timestamp(i32 year, i32 month, i32 day);

      
      i32 get_month_day_count(i32 year, i32 month);


      i32 get_weekday(i32 year, i32 month, i32 day);


      posix_time strtotime(const ::text::context * pcontext, const ::string & str, posix_time time,i32 iPath,i32 & iPathCount, const class ::time& timezone = {});
      posix_time strtotime(const ::text::context * pcontext, const ::string & str, i32 iPath,i32 & iPathCount, const class ::time& timezone = {});

      
      ::earth::time from_string(const ::text::context* pcontext, const ::string & str, const class ::time& timezone = {});


      // 1 - domingo
      string get_week_day_str(const ::text::context * pcontext,i32 iWeekDay);
      // 1 - domingo
      string get_tiny_week_day_str(const ::text::context * pcontext,i32 iWeekDay);
      string get_month_str(const ::text::context * pcontext,i32 iMonth);
      string get_short_month_str(const ::text::context * pcontext,i32 iMonth);

      static posix_time s_mktime(i32 iHour,i32 iMinute,i32 iSecond,i32 iMonth,i32 iDay,i32 iYear, const class ::time& timezone = {});

      //inline class  international& international() { return *m_pinternational; }
      //inline class str& str() { return* m_pstr; }

      //string format(const string & str, const ::earth::time & time, const class ::time& timezone = {});
      //string format(const string & str, const class ::time& timezone = {});

      i32 SWN(i32 y,i32 m,i32 d);
      i32 DP(i32 y,i32 m);
      i32 ML(i32 y,i32 m);
      i32 LEAP(i32 y);
      i32 dayofweek(i32 y,i32 m,i32 d);	/* 0 = Sunday */
      i32 SDOW(i32 y,i32 m,i32 d);
      i32 DOW(i32 y,i32 m,i32 d);
      i32 getDayOfWeek(i32 month,i32 day,i32 year,i32 CalendarSystem);
      i32 ISO_WN(i32  y,i32 m,i32 d);

      virtual string to_string(const ::text::context* pcontext, const ::datetime::result& result, const class ::time& timeshift = {});

      virtual result span_parse_time(const ::text::context* pcontext, const string & str, const class ::time& timeshift = {});

      virtual result parse_time(const ::text::context* pcontext, const string & str, i32& iPath, i32& iPathCount, const class ::time& timeshift = {});

      string friend_time(const ::text::context * pcontext,::earth::time timeNow,::earth::time time, const class ::time& timeshift = {});

      virtual string _001FriendTime(const ::text::context* pcontext, const ::earth::time& timeNow, const ::earth::time& time, const class ::time& timeshift = {});


      ::posix_time parse(const string& str);

      void parse_text(const string& str, property_set& set);
      ::earth::time parse_text(const string& str);


      //string date_time_text(const ::earth::time& time, string strFormat = INTERNATIONAL_DATE_TIME_FORMAT, const class ::time& timeshift = {});
      //string date_time_text(string strFormat = INTERNATIONAL_DATE_TIME_FORMAT, const class ::time& timeshift = {});
      //string date_time_text_for_file(const class ::time& timeshift = {}, const ::earth::time& time = ::earth::time::now());



      //string local_get_date_time(const ::earth::time & time, string strFormat = INTERNATIONAL_DATE_TIME_FORMAT);
      //string local_get_date_time(string strFormat = INTERNATIONAL_DATE_TIME_FORMAT);
      //string local_get_date_time_for_file();


      string get_date_time_for_file_with_no_spaces(const class ::time& timeshift = {}, const ::earth::time& time = ::earth::time::now());
      //string local_get_date_time_for_file_with_no_spaces();


      virtual string format(const ::scoped_string& strFormat, const ::earth::time& time = ::time::now(), const class ::time& timeshift = {});
      //inline string format(const ::scoped_string& strFormat, const class ::time& timeshift = {}) { return format(::time::now(), strFormat, timeshift); }


      inline string date_time_text(const ::earth::time& time, const class ::time& timeshift = {}) { return format(INTERNATIONAL_DATE_TIME_FORMAT, time, timeshift); }
      inline string date_time_text(const class ::time & timeshift = {}) { return date_time_text(::time::now(), timeshift); }
      inline string date_time_text_for_file(const ::earth::time& time, const class ::time& timeshift = {}) { return format(INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE, time, timeshift); }
      inline string date_time_text_for_file(const class ::time& timeshift = {}) { return date_time_text_for_file(::time::now(), timeshift); }
      inline string date_time_text_for_file_with_no_spaces(const ::earth::time& time, const class ::time& timeshift = {}) { return format(INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE_WITH_NO_SPACES, time, timeshift); }
      inline string date_time_text_for_file_with_no_spaces(const class ::time& timeshift = {}) { return date_time_text_for_file_with_no_spaces(::time::now(), timeshift); }


      inline ::string date_text(const ::earth::time& time, string strFormat = INTERNATIONAL_DATE_FORMAT, const class ::time& timeshift = {}) { return format(strFormat, time, timeshift); }
      inline ::string date_text(string strFormat = INTERNATIONAL_DATE_FORMAT, const class ::time& timeshift = {}) { return format(strFormat, ::time::now(), timeshift); }
      inline ::string date_text_for_file(const class ::time& timeshift = {}, const ::earth::time& time = ::earth::time::now()) { return format(INTERNATIONAL_DATE_FORMAT_FOR_FILE, time, timeshift); }


      //inline string local_get(string strFormat = INTERNATIONAL_DATE_TIME_FORMAT) { return local_get_date_time(strFormat); }
      //inline string local_get(const ::earth::time & time, string strFormat = INTERNATIONAL_DATE_TIME_FORMAT) { return local_get_date_time(time, strFormat); }


      //inline string utc() { return utc_get(); }
      //inline string utc(const ::earth::time & time) { return utc_get(time); }
      //inline string local() { return local_get(); }
      //inline string local(const ::earth::time & time) { return local_get(time); }


virtual ::string elapsed_nanoseconds_text(::i64 iNanoseconds);


virtual ::string elapsed_time_text(const class ::time & time);


   };


} // namespace apex



CLASS_DECL_ACID ::earth::time earth_time_from_international_string(const ::scoped_string& scopedstrTime);
