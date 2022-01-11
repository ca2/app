#pragma once


namespace datetime
{


   namespace calendar
   {


 
      class CLASS_DECL_CA2_TIME calendar :
         virtual public ::object
      {
      public:


         int32_t      m_iMonth;
         int32_t      m_iYear;
         bool     m_bRange;
         ::datetime::time    m_time;
         ::datetime::time    m_timeEnd;


         calendar();
         virtual ~calendar();


         virtual void initialize(::object * pobject) override;

         virtual void GetRectDay(::datetime::time& time, RECTANGLE_I32 * lprect);
         virtual void GetRectDay(int32_t iWeekDay, int32_t iLine, RECTANGLE_I32 * lprect);
         virtual void GetRect(RECTANGLE_I32 * lprect, enum enum_element eelement);

         virtual void set_month(int32_t iYear, int32_t iMonth);
         virtual void set_time(const ::datetime::time& time);
         virtual void set_time_range(const ::datetime::time& time, const ::datetime::time& timeEnd);
         virtual void set_time_end(const ::datetime::time& timeEnd);
         virtual void get_time(::datetime::time& time);
         virtual int32_t get_month();
         virtual int32_t get_year();

         virtual int32_t get_week_of_month(::datetime::time& time);

         virtual void _001OnDraw(::draw2d::graphics* pgraphics);

         void set_pos(point_i32 pt, size_i32 sz);

         virtual void GetDateTime(const ::text::context* pcontext, string& strDateTime);

         virtual string GetTinyWeekDay(const ::text::context* pcontext, int32_t iWeekDay); // 1 - domingo
         virtual string GetWeekDay(const ::text::context* pcontext, int32_t iWeekDay); // 1 - domingo
         virtual string GetMonth(const ::text::context* pcontext, int32_t iMonth); // 1 - janeiro

         virtual void previous_month();
         virtual void next_month();
         virtual void next_year();
         virtual void previous_year();

         virtual enum_element hit_test(const ::point_i32 & point);
         virtual bool hit_test(enum_element eelement, const ::point_i32& point);
         virtual bool time_hit_test(::datetime::time& time, const ::point_i32& point);


      };

   
   } // namespace calendar


} // namespace datetime



