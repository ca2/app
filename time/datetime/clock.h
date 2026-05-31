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
         ~clock() override;


         virtual void GetRect(::i32_rectangle * lprect, const ::datetime::clock::e_element & eelement);


         virtual void set_time(const ::earth::time& time);
         virtual void get_time(::earth::time& time);

         virtual void _001OnDraw(::draw2d::graphics* pgraphics);


         virtual void previous_minute();
         virtual void next_minute();
         virtual void next_hour();
         virtual void previous_hour();

         virtual e_element hit_test(const ::i32_point & point, ::user::e_zorder ezorder);
         virtual bool hit_test(const ::datetime::clock::e_element & eelement, const ::i32_point& point);


      };

   
   } // namespace clock


} // namespace datetime


