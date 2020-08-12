#include "framework.h"


namespace visual
{


   clock::clock(::object * pobject):
      ::object(pobject),
      ::clock_interface(pobject),
      ::datetime::clock(pobject)
   {
      //   ::datetime::time time = ::datetime::time::get_current_time();
   }


   void clock::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {



      ::datetime::time timeNow = ::datetime::time::get_current_time() + m_timespan;

      ::rect rect;
      GetRect(&rect,ElementClock);
      ::draw2d::pen_pointer pen(e_create);
      pen->create_solid(1, ARGB(255, 0, 0, 0));
      pgraphics->SelectObject(pen);
      pgraphics->draw_ellipse(rect);

      ::point pointCenter(rect.center());

      ::draw2d::pen_pointer penHour(e_create);
      penHour->create_solid(5, ARGB(255, 0, 0, 0));
      ::draw2d::pen_pointer penMinute(e_create);
      penMinute->create_solid(1, ARGB(255, 0, 0, 0));

      double dRIntH = rect.width() * 57 / 128;
      double dRIntM = rect.width() * 59 / 128;
      double dRExt = rect.width() * 60 / 128;

      for(i32 i = 0; i < 60; i++)
      {
         double angle = System.math().GetPi() / 2.0 - i * System.math().GetPi() * 2.0 / (60.0);
         ::point pointInt;
         ::point pointExt((LONG)(cos(angle) * dRExt),(LONG)(-sin(angle) * dRExt));
         pointExt.offset(pointCenter);
         if(i % 5 == 0)
         {
            pointInt.x = (LONG)(cos(angle) * dRIntH);
            pointInt.y = (LONG)(-sin(angle) * dRIntH);
            pgraphics->SelectObject(penHour);
         }
         else
         {
            pointInt.x = (LONG)(cos(angle) * dRIntM);
            pointInt.y = (LONG)(-sin(angle) * dRIntM);
            pgraphics->SelectObject(penMinute);
         }
         pointInt.offset(pointCenter);
         pgraphics->move_to(pointInt);
         pgraphics->line_to(pointExt);
      }

      double dRHour = rect.width() * 11 / 32;
      double dRMinute = rect.width() * 15 / 32;
      double dRSecond = rect.width() * 16 / 32;

      ::draw2d::pen_pointer penHM(e_create);
      penHM->create_solid(2, ARGB(255, 0, 0, 0));
      pgraphics->SelectObject(penHM);

      pgraphics->move_to(pointCenter);
      {
         double angle = System.math().GetPi() / 2.0 - timeNow.GetHour() * System.math().GetPi() * 2.0 / (12.0);
         ::point pointHour((LONG)(cos(angle) * dRHour),(LONG)(-sin(angle) * dRHour));
         pointHour.offset(pointCenter);
         pgraphics->line_to(pointHour);
      }
      pgraphics->move_to(pointCenter);
      {
         double angle = System.math().GetPi() / 2.0 - timeNow.GetMinute() * System.math().GetPi() * 2.0 / (60.0);
         ::point pointMinute((LONG)(cos(angle) * dRMinute),(LONG)(-sin(angle) * dRMinute));
         pointMinute.offset(pointCenter);
         pgraphics->line_to(pointMinute);
      }
      ::draw2d::pen_pointer penRed(e_create);
      penRed->create_solid(1, ARGB(255, 200, 0, 0));
      pgraphics->SelectObject(penRed);
      pgraphics->move_to(pointCenter);
      {
         double angle = System.math().GetPi() / 2.0 - timeNow.GetSecond() * System.math().GetPi() * 2.0 / (60.0);
         ::point pointSecond((LONG)(cos(angle) * dRSecond),(LONG)(-sin(angle) * dRSecond));
         pointSecond.offset(pointCenter);
         pgraphics->line_to(pointSecond);
      }



   }



   void clock::GetRect(LPRECT lprect,enum EElement eelement)
   {
      if(eelement == ElementClock)
      {
         lprect->left = m_point.x;
         lprect->right = lprect->left + m_size.cx;
         lprect->top = m_point.y;
         lprect->bottom = lprect->top + m_size.cy;
      }
   }


   void clock::set_pos(const ::point & point,size sz)
   {

      m_point = point;
      m_size = sz;

   }


} // namespace visual



