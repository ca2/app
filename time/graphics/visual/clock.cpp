#include "framework.h"



namespace datetime
{


   namespace clock
   {


   graphics::graphics()
   {
     
   }


   graphics::~graphics()
   {

   }

   ::e_status graphics::initialize(::layered * pobjectContext)
   {

      return ::success;

   }


   void graphics::_001OnDraw(::draw2d::graphics * pgraphics)
   {



      ::datetime::time timeNow = ::datetime::time::get_current_time() + m_timespan;

      rectangle_i32 rectangle;
      GetRect(&rectangle,e_element_clock);
      ::draw2d::pen_pointer pen(e_create);
      
      pen->create_solid(1, ARGB(255, 0, 0, 0));
      pgraphics->set(pen);
      pgraphics->draw_ellipse(rectangle);

      point_i32 pointCenter(rectangle.center());

      ::draw2d::pen_pointer penHour(e_create);
      ::draw2d::pen_pointer penMinute(e_create);

      penHour->create_solid(5, ARGB(255, 0, 0, 0));
      penMinute->create_solid(1, ARGB(255, 0, 0, 0));

      double dRIntH = rectangle.width() * 57 / 128;
      double dRIntM = rectangle.width() * 59 / 128;
      double dRExt = rectangle.width() * 60 / 128;

      for(int32_t i = 0; i < 60; i++)
      {
         double angle = System.math().GetPi() / 2.0 - i * System.math().GetPi() * 2.0 / (60.0);
         point_i32 pointInt;
         point_i32 pointExt((::i32)(cos(angle) * dRExt),(::i32)(-sin(angle) * dRExt));
         pointExt.offset(pointCenter);
         if(i % 5 == 0)
         {
            pointInt.x = (::i32)(cos(angle) * dRIntH);
            pointInt.y = (::i32)(-sin(angle) * dRIntH);
            pgraphics->set(penHour);
         }
         else
         {
            pointInt.x = (::i32)(cos(angle) * dRIntM);
            pointInt.y = (::i32)(-sin(angle) * dRIntM);
            pgraphics->set(penMinute);
         }
         pointInt.offset(pointCenter);
         pgraphics->move_to(pointInt);
         pgraphics->line_to(pointExt);
      }

      double dRHour = rectangle.width() * 11 / 32;
      double dRMinute = rectangle.width() * 15 / 32;
      double dRSecond = rectangle.width() * 16 / 32;

      ::draw2d::pen_pointer penHM(e_create);
      penHM->create_solid(2, ARGB(255, 0, 0, 0));
      pgraphics->set(penHM);

      pgraphics->move_to(pointCenter);
      {
         double angle = System.math().GetPi() / 2.0 - timeNow.GetHour() * System.math().GetPi() * 2.0 / (12.0);
         point_i32 pointHour((::i32)(cos(angle) * dRHour),(::i32)(-sin(angle) * dRHour));
         pointHour.offset(pointCenter);
         pgraphics->line_to(pointHour);
      }
      pgraphics->move_to(pointCenter);
      {
         double angle = System.math().GetPi() / 2.0 - timeNow.GetMinute() * System.math().GetPi() * 2.0 / (60.0);
         point_i32 pointMinute((::i32)(cos(angle) * dRMinute),(::i32)(-sin(angle) * dRMinute));
         pointMinute.offset(pointCenter);
         pgraphics->line_to(pointMinute);
      }
      ::draw2d::pen_pointer penRed(e_create);
      penRed->create_solid(1, ARGB(255, 200, 0, 0));
      pgraphics->set(penRed);
      pgraphics->move_to(pointCenter);
      {
         double angle = System.math().GetPi() / 2.0 - timeNow.GetSecond() * System.math().GetPi() * 2.0 / (60.0);
         point_i32 pointSecond((::i32)(cos(angle) * dRSecond),(::i32)(-sin(angle) * dRSecond));
         pointSecond.offset(pointCenter);
         pgraphics->line_to(pointSecond);
      }



   }



   void graphics::GetRect(LPRECT32 lprect,enum enum_element eelement)
   {
      if(eelement == e_element_clock)
      {
         lprect->left = m_point.x;
         lprect->right = lprect->left + m_size.cx;
         lprect->top = m_point.y;
         lprect->bottom = lprect->top + m_size.cy;
      }
   }



   void graphics::set_pos(point_i32 point_i32,size_i32 sz)
   {
      m_point = point_i32;
      m_size = sz;
   }



   } // namespace clock


} // namespace datetime



