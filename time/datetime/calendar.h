#pragma once


////#include "acme/primitive/datetime/earth_time.h"
#include "acme/primitive/geometry2d/_geometry2d.h"
#include "acme/primitive/primitive/particle.h"


namespace datetime
{


   namespace calendar
   {


 
      class CLASS_DECL_CA2_TIME calendar :
         virtual public ::particle
      {
      public:


         int32_t      m_iMonth;
         int32_t      m_iYear;
         bool     m_bRange;
         ::earth::time    m_time;
         ::earth::time    m_timeEnd;


         calendar();
         ~calendar() override;


         virtual void initialize(::particle * pparticle) override;

         virtual void GetRectDay(::earth::time& time, RECTANGLE_I32 * lprect);
         virtual void GetRectDay(int32_t iWeekDay, int32_t iLine, RECTANGLE_I32 * lprect);
         virtual void GetRect(RECTANGLE_I32 * lprect, enum enum_element eelement);

         virtual void set_month(int32_t iYear, int32_t iMonth);
         virtual void set_time(const ::earth::time& time);
         virtual void set_time_range(const ::earth::time& time, const ::earth::time& timeEnd);
         virtual void set_time_end(const ::earth::time& timeEnd);
         virtual void get_time(::earth::time& time);
         virtual int32_t get_month();
         virtual int32_t get_year();

         virtual int32_t get_week_of_month(::earth::time& time);

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

         virtual enum_element hit_test(const ::point_i32 & point, ::user::e_zorder ezorder);
         virtual bool hit_test(enum_element eelement, const ::point_i32& point);
         virtual bool time_hit_test(::earth::time& time, const ::point_i32& point);


      };

   
   } // namespace calendar


} // namespace datetime



