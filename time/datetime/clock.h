#pragma once


namespace datetime
{


   namespace clock
   {


      class CLASS_DECL_CA2_TIME clock :
         virtual public ::object
      {
      protected:


         ::datetime::time_span    m_timespan;


      public:


         clock();
         virtual ~clock();


         virtual void GetRect(LPRECT32 lprect, enum_element eelement);


         virtual void set_time(const ::datetime::time& time);
         virtual void get_time(::datetime::time& time);

         virtual void _001OnDraw(::draw2d::graphics* pgraphics);


         virtual void previous_minute();
         virtual void next_minute();
         virtual void next_hour();
         virtual void previous_hour();

         virtual enum_element hit_test(const ::point& point);
         virtual bool hit_test(enum_element eelement, const ::point& point);


      };

   
   } // namespace clock


} // namespace datetime


