#pragma once


namespace datetime
{


   namespace calendar
   {


      enum enum_element
      {

         e_element_none,
         e_element_previous_year,
         e_element_previous_month,
         e_element_next_month,
         e_element_next_year,
         e_element_month_title,
         e_element_year_title,
         e_element_count,

      };


   }  // namespace calendar


   namespace clock
   {


      enum enum_element
      {

         e_element_none,
         e_element_previous_hour,
         e_element_previous_minute,
         e_element_next_minute,
         e_element_next_hour,
         e_element_hour_title,
         e_element_minute_title,
         e_element_clock,
         e_element_count,

      };


   } // namespace clock


} // namespace datetime



