#include "framework.h"
#include "clock.h"
////#include "acme/prototype/datetime/earth_time.h"


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


      void clock::GetRect(::int_rectangle * lprect, enum_element eelement)
      {
         __UNREFERENCED_PARAMETER(lprect);
         __UNREFERENCED_PARAMETER(eelement);
      }


      void clock::set_time(const ::earth::time & time)
      {
         m_timespan = time - ::earth::time::now();
      }

      void clock::get_time(::earth::time & time)
      {
         time = ::earth::time::now() + m_timespan;
      }




      void clock::previous_minute()
      {
         m_timespan -= ::earth::time_span(0, 0, 1, 0);
      }
      void clock::next_minute()
      {
         m_timespan += ::earth::time_span(0, 0, 1, 0);
      }

      void clock::next_hour()
      {
         m_timespan += ::earth::time_span(0, 1, 0, 0);
      }

      void clock::previous_hour()
      {
         m_timespan -= ::earth::time_span(0, 1, 0, 0);
      }


      enum_element clock::hit_test(const int_point & point, ::user::e_zorder ezorder)
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


      bool clock::hit_test(enum_element eelement, const int_point& pt)
      {

         ::int_rectangle rectangle;

         GetRect(&rectangle, eelement);

         return rectangle.contains(pt) != false;

      }


   } // namespace clock


} // namespace datetime



