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


      void clock::GetRect(::i32_rectangle * lprect, const e_element & eelement)
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


      e_element clock::hit_test(const i32_point & point, ::user::e_zorder ezorder)
      {

         for (auto eelement = e_element_none + 1; eelement < e_element_count; eelement++)
         {

            if (hit_test(eelement, point))
            {

               return eelement;

            }

         }

         return e_element_none;

      }


      bool clock::hit_test(const e_element & eelement, const i32_point& pt)
      {

         ::i32_rectangle rectangle;

         GetRect(&rectangle, eelement);

         return rectangle.contains(pt) != false;

      }


   } // namespace clock


} // namespace datetime



