#pragma once


#include "acme/prototype/datetime/earth_time_span.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"



namespace datetime
{


   namespace clock
   {


      class CLASS_DECL_CA2_TIME clock :
         virtual public ::particle
      {
      protected:


         ::earth::time_span    m_timespan;


      public:


         clock();
         virtual ~clock();


         virtual void GetRect(::rectangle_i32 * lprect, enum_element eelement);


         virtual void set_time(const ::earth::time& time);
         virtual void get_time(::earth::time& time);

         virtual void _001OnDraw(::draw2d::graphics* pgraphics);


         virtual void previous_minute();
         virtual void next_minute();
         virtual void next_hour();
         virtual void previous_hour();

         virtual enum_element hit_test(const ::point_i32 & point, ::user::e_zorder ezorder);
         virtual bool hit_test(enum_element eelement, const ::point_i32& point);


      };

   
   } // namespace clock


} // namespace datetime


