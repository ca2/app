#include "framework.h"
#include "clock.h"
#include "acme/platform/system.h"
#include "acme/primitive/mathematics/mathematics.h"
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

         auto psystem = get_system()->m_papexsystem;

         auto pmathematics = ::mathematics::mathematics();

         ::earth::time timeNow = ::earth::time::now() + m_timespan;

         rectangle_i32 rectangle;
         GetRect(&rectangle, e_element_clock);
         auto ppen = ::__create < ::draw2d::pen >(this);

         ppen->create_solid(1, argb(255, 0, 0, 0));
         pgraphics->set(ppen);
         pgraphics->draw_ellipse(rectangle);

         point_i32 pointCenter(rectangle.center());

         auto ppenHour = ::__create < ::draw2d::pen >(this);
         auto ppenMinute = ::__create < ::draw2d::pen >(this);

         ppenHour->create_solid(5, argb(255, 0, 0, 0));
         ppenMinute->create_solid(1, argb(255, 0, 0, 0));

         double dRIntH = rectangle.width() * 57 / 128;
         double dRIntM = rectangle.width() * 59 / 128;
         double dRExt = rectangle.width() * 60 / 128;

         for (int32_t i = 0; i < 60; i++)
         {
            double angle = pmathematics->get_pi() / 2.0 - i * pmathematics->get_pi() * 2.0 / (60.0);
            point_i32 pointInt;
            point_i32 pointExt((::i32)(cos(angle) * dRExt), (::i32)(-sin(angle) * dRExt));
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
            pgraphics->set_current_point(pointInt);
            pgraphics->line_to(pointExt);
         }

         double dRHour = rectangle.width() * 11 / 32;
         double dRMinute = rectangle.width() * 15 / 32;
         double dRSecond = rectangle.width() * 16 / 32;

         auto ppenHM = ::__create < ::draw2d::pen >(this);
         ppenHM->create_solid(2, argb(255, 0, 0, 0));
         pgraphics->set(ppenHM);

         pgraphics->set_current_point(pointCenter);
         {
            double angle = pmathematics->get_pi() / 2.0 - timeNow.hour() * pmathematics->get_pi() * 2.0 / (12.0);
            point_i32 pointHour((::i32)(cos(angle) * dRHour), (::i32)(-sin(angle) * dRHour));
            pointHour.offset(pointCenter);
            pgraphics->line_to(pointHour);
         }
         pgraphics->set_current_point(pointCenter);
         {
            double angle = pmathematics->get_pi() / 2.0 - timeNow.minute() * pmathematics->get_pi() * 2.0 / (60.0);
            point_i32 pointMinute((::i32)(cos(angle) * dRMinute), (::i32)(-sin(angle) * dRMinute));
            pointMinute.offset(pointCenter);
            pgraphics->line_to(pointMinute);
         }
         auto ppenRed = ::__create < ::draw2d::pen >(this);
         ppenRed->create_solid(1, argb(255, 200, 0, 0));
         pgraphics->set(ppenRed);
         pgraphics->set_current_point(pointCenter);
         {
            double angle = pmathematics->get_pi() / 2.0 - timeNow.second() * pmathematics->get_pi() * 2.0 / (60.0);
            point_i32 pointSecond((::i32)(cos(angle) * dRSecond), (::i32)(-sin(angle) * dRSecond));
            pointSecond.offset(pointCenter);
            pgraphics->line_to(pointSecond);
         }



      }



      void graphics::GetRect(RECTANGLE_I32 * lprect, enum enum_element eelement)
      {
         if (eelement == e_element_clock)
         {
            lprect->left = m_point.x;
            lprect->right = lprect->left + m_size.cx;
            lprect->top = m_point.y;
            lprect->bottom = lprect->top + m_size.cy;
         }
      }



      void graphics::set_pos(point_i32 point, size_i32 sz)
      {
         m_point = point;
         m_size = sz;
      }


   } // namespace clock


} // namespace datetime



