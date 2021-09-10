#include "framework.h"


namespace datetime
{


   namespace clock
   {



      clock::clock()
      {
      }



      clock::~clock()
      {


      }



      void clock::_001OnDraw(::draw2d::graphics * pgraphics)
      {
   
         __UNREFERENCED_PARAMETER(pgraphics);

      }


      void clock::GetRect(RECTANGLE_I32 * lprect, enum_element eelement)
      {
         __UNREFERENCED_PARAMETER(lprect);
         __UNREFERENCED_PARAMETER(eelement);
      }


      void clock::set_time(const ::datetime::time & time)
      {
         m_timespan = time - ::datetime::time::get_current_time();
      }

      void clock::get_time(::datetime::time & time)
      {
         time = ::datetime::time::get_current_time() + m_timespan;
      }




      void clock::previous_minute()
      {
         m_timespan -= ::datetime::time_span(0, 0, 1, 0);
      }
      void clock::next_minute()
      {
         m_timespan += ::datetime::time_span(0, 0, 1, 0);
      }

      void clock::next_hour()
      {
         m_timespan += ::datetime::time_span(0, 1, 0, 0);
      }

      void clock::previous_hour()
      {
         m_timespan -= ::datetime::time_span(0, 1, 0, 0);
      }


      enum_element clock::hit_test(const point_i32 & point)
      {

         for (int iElement = e_element_none + 1; iElement < e_element_count; iElement++)
         {

            if (hit_test((enum_element) iElement, point))
            {

               return (enum_element)iElement;

            }

         }

         return e_element_none;

      }


      bool clock::hit_test(enum_element eelement, const point_i32& pt)
      {

         ::rectangle_i32 rectangle;

         GetRect(rectangle, eelement);

         return rectangle.contains(pt) != false;

      }


   } // namespace clock


} // namespace datetime


