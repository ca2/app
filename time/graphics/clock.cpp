#include "framework.h"
#include "clock.h"
#include "acme/platform/system.h"
#include "acme/prototype/mathematics/mathematics.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/pen.h"


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


      void graphics::initialize(::particle * pparticle)
      {

         //return ::success;

      }


      void graphics::_001OnDraw(::draw2d::graphics * pgraphics)
      {

         //auto pmathematics = this->mathematics();

         ::earth::time timeNow = ::earth::time::now() + m_timespan;

         i32_rectangle rectangle;
         GetRect(&rectangle, e_element_clock);
         auto ppen = createø < ::draw2d::pen >();

         ppen->create_solid(1, argb(255, 0, 0, 0));
         pgraphics->set(ppen);
         pgraphics->draw_ellipse(rectangle);

         i32_point pointCenter(rectangle.center());

         auto ppenHour = createø < ::draw2d::pen >();
         auto ppenMinute = createø < ::draw2d::pen >();

         ppenHour->create_solid(5, argb(255, 0, 0, 0));
         ppenMinute->create_solid(1, argb(255, 0, 0, 0));

         ::f64 dRIntH = rectangle.width() * 57 / 128;
         ::f64 dRIntM = rectangle.width() * 59 / 128;
         ::f64 dRExt = rectangle.width() * 60 / 128;

         for (int32_t i = 0; i < 60; i++)
         {
            ::f64 angle = π / 2.0 - i * π * 2.0 / (60.0);
            i32_point pointInt;
            i32_point pointExt((::i32)(cos(angle) * dRExt), (::i32)(-sin(angle) * dRExt));
            pointExt.offset(pointCenter);
            if (i % 5 == 0)
            {
               pointInt.x = (::i32)(cos(angle) * dRIntH);
               pointInt.y = (::i32)(-sin(angle) * dRIntH);
               pgraphics->set(ppenHour);
            }
            else
            {
               pointInt.x = (::i32)(cos(angle) * dRIntM);
               pointInt.y = (::i32)(-sin(angle) * dRIntM);
               pgraphics->set(ppenMinute);
            }
            pointInt.offset(pointCenter);
            pgraphics->line(pointInt, pointExt);
            //pgraphics->line_to(pointExt);
         }

         ::f64 dRHour = rectangle.width() * 11 / 32;
         ::f64 dRMinute = rectangle.width() * 15 / 32;
         ::f64 dRSecond = rectangle.width() * 16 / 32;

         auto ppenHM = createø < ::draw2d::pen >();
         ppenHM->create_solid(2, argb(255, 0, 0, 0));
         pgraphics->set(ppenHM);

         //pgraphics->set_current_point(pointCenter);
         {
            ::f64 angle = π / 2.0 - timeNow.hour() * π * 2.0 / (12.0);
            i32_point pointHour((::i32)(cos(angle) * dRHour), (::i32)(-sin(angle) * dRHour));
            pointHour.offset(pointCenter);
            pgraphics->line(pointCenter, pointHour);
         }
         //pgraphics->set_current_point(pointCenter);
         {
            ::f64 angle = π / 2.0 - timeNow.minute() * π * 2.0 / (60.0);
            i32_point pointMinute((::i32)(cos(angle) * dRMinute), (::i32)(-sin(angle) * dRMinute));
            pointMinute.offset(pointCenter);
            pgraphics->line(pointCenter, pointMinute);
         }
         auto ppenRed = createø < ::draw2d::pen >();
         ppenRed->create_solid(1, argb(255, 200, 0, 0));
         pgraphics->set(ppenRed);
         //pgraphics->set_current_point(pointCenter);
         {
            ::f64 angle = π / 2.0 - timeNow.second() * π * 2.0 / (60.0);
            i32_point pointSecond((::i32)(cos(angle) * dRSecond), (::i32)(-sin(angle) * dRSecond));
            pointSecond.offset(pointCenter);
            pgraphics->line(pointCenter, pointSecond);
         }



      }



      void graphics::GetRect(::i32_rectangle * lprect, enum const ::e_element & eelement)
      {
         if (eelement == e_element_clock)
         {
            lprect->left = m_point.x;
            lprect->right = lprect->left + m_size.cx;
            lprect->top = m_point.y;
            lprect->bottom = lprect->top + m_size.cy;
         }
      }



      void graphics::set_pos(i32_point point, i32_size sz)
      {
         m_point = point;
         m_size = sz;
      }


   } // namespace clock


} // namespace datetime



