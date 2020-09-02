#include "framework.h"



namespace visual
{



   clock::clock(::aura::application * papp):
      ::object(papp),
      ::clock_interface(papp),
      ::datetime::clock(papp)
   {
      //   ::datetime::time time = ::datetime::time::get_current_time();
   }


   void clock::_001OnDraw(::draw2d::graphics * pgraphics)
   {



      ::datetime::time timeNow = ::datetime::time::get_current_time() + m_timespan;

      rect rect;
      GetRect(&rect,ElementClock);
      ::draw2d::pen_sp pen(allocer(),1,ARGB(255,0,0,0));
      pgraphics->SelectObject(pen);
      pgraphics->DrawEllipse(rect);

      point ptCenter(rect.center());

      ::draw2d::pen_sp penHour(allocer(),5,ARGB(255,0,0,0));
      ::draw2d::pen_sp penMinute(allocer(),1,ARGB(255,0,0,0));

      double dRIntH = rect.width() * 57 / 128;
      double dRIntM = rect.width() * 59 / 128;
      double dRExt = rect.width() * 60 / 128;

      for(int32_t i = 0; i < 60; i++)
      {
         double angle = System.math().GetPi() / 2.0 - i * System.math().GetPi() * 2.0 / (60.0);
         point ptInt;
         point ptExt((int64_t)(cos(angle) * dRExt),(int64_t)(-sin(angle) * dRExt));
         ptExt.offset(ptCenter);
         if(i % 5 == 0)
         {
            ptInt.x = (LONG)(cos(angle) * dRIntH);
            ptInt.y = (LONG)(-sin(angle) * dRIntH);
            pgraphics->SelectObject(penHour);
         }
         else
         {
            ptInt.x = (LONG)(cos(angle) * dRIntM);
            ptInt.y = (LONG)(-sin(angle) * dRIntM);
            pgraphics->SelectObject(penMinute);
         }
         ptInt.offset(ptCenter);
         pgraphics->move_to(ptInt);
         pgraphics->line_to(ptExt);
      }

      double dRHour = rect.width() * 11 / 32;
      double dRMinute = rect.width() * 15 / 32;
      double dRSecond = rect.width() * 16 / 32;

      ::draw2d::pen_sp penHM(allocer(),2,ARGB(255,0,0,0));
      pgraphics->SelectObject(penHM);

      pgraphics->move_to(ptCenter);
      {
         double angle = System.math().GetPi() / 2.0 - timeNow.GetHour() * System.math().GetPi() * 2.0 / (12.0);
         point ptHour((int64_t)(cos(angle) * dRHour),(int64_t)(-sin(angle) * dRHour));
         ptHour.offset(ptCenter);
         pgraphics->line_to(ptHour);
      }
      pgraphics->move_to(ptCenter);
      {
         double angle = System.math().GetPi() / 2.0 - timeNow.GetMinute() * System.math().GetPi() * 2.0 / (60.0);
         point ptMinute((int64_t)(cos(angle) * dRMinute),(int64_t)(-sin(angle) * dRMinute));
         ptMinute.offset(ptCenter);
         pgraphics->line_to(ptMinute);
      }
      ::draw2d::pen_sp penRed(allocer(),1,ARGB(255,200,0,0));
      pgraphics->SelectObject(penRed);
      pgraphics->move_to(ptCenter);
      {
         double angle = System.math().GetPi() / 2.0 - timeNow.GetSecond() * System.math().GetPi() * 2.0 / (60.0);
         point ptSecond((int64_t)(cos(angle) * dRSecond),(int64_t)(-sin(angle) * dRSecond));
         ptSecond.offset(ptCenter);
         pgraphics->line_to(ptSecond);
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



   void clock::set_pos(point pt,size sz)
   {
      m_point = pt;
      m_size = sz;
   }


} // namespace visual





















