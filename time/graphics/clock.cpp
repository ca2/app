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

         int_rectangle rectangle;
         GetRect(&rectangle, e_element_clock);
         auto ppen = __create < ::draw2d::pen >();

         ppen->create_solid(1, argb(255, 0, 0, 0));
         pgraphics->set(ppen);
         pgraphics->draw_ellipse(rectangle);

         int_point pointCenter(rectangle.center());

         auto ppenHour = __create < ::draw2d::pen >();
         auto ppenMinute = __create < ::draw2d::pen >();

         ppenHour->create_solid(5, argb(255, 0, 0, 0));
         ppenMinute->create_solid(1, argb(255, 0, 0, 0));

         double dRIntH = rectangle.width() * 57 / 128;
         double dRIntM = rectangle.width() * 59 / 128;
         double dRExt = rectangle.width() * 60 / 128;

         for (int32_t i = 0; i < 60; i++)
         {
            double angle = π / 2.0 - i * π * 2.0 / (60.0);
            int_point pointInt;
            int_point pointExt((int)(cos(angle) * dRExt), (int)(-sin(angle) * dRExt));
            pointExt.offset(pointCenter);
            if (i % 5 == 0)
            {
               pointInt.x() = (int)(cos(angle) * dRIntH);
               pointInt.y() = (int)(-sin(angle) * dRIntH);
               pgraphics->set(ppenHour);
            }
            else
            {
               pointInt.x() = (int)(cos(angle) * dRIntM);
               pointInt.y() = (int)(-sin(angle) * dRIntM);
               pgraphics->set(ppenMinute);
            }
            pointInt.offset(pointCenter);
            pgraphics->set_current_point(pointInt);
            pgraphics->line_to(pointExt);
         }

         double dRHour = rectangle.width() * 11 / 32;
         double dRMinute = rectangle.width() * 15 / 32;
         double dRSecond = rectangle.width() * 16 / 32;

         auto ppenHM = __create < ::draw2d::pen >();
         ppenHM->create_solid(2, argb(255, 0, 0, 0));
         pgraphics->set(ppenHM);

         pgraphics->set_current_point(pointCenter);
         {
            double angle = π / 2.0 - timeNow.hour() * π * 2.0 / (12.0);
            int_point pointHour((int)(cos(angle) * dRHour), (int)(-sin(angle) * dRHour));
            pointHour.offset(pointCenter);
            pgraphics->line_to(pointHour);
         }
         pgraphics->set_current_point(pointCenter);
         {
            double angle = π / 2.0 - timeNow.minute() * π * 2.0 / (60.0);
            int_point pointMinute((int)(cos(angle) * dRMinute), (int)(-sin(angle) * dRMinute));
            pointMinute.offset(pointCenter);
            pgraphics->line_to(pointMinute);
         }
         auto ppenRed = __create < ::draw2d::pen >();
         ppenRed->create_solid(1, argb(255, 200, 0, 0));
         pgraphics->set(ppenRed);
         pgraphics->set_current_point(pointCenter);
         {
            double angle = π / 2.0 - timeNow.second() * π * 2.0 / (60.0);
            int_point pointSecond((int)(cos(angle) * dRSecond), (int)(-sin(angle) * dRSecond));
            pointSecond.offset(pointCenter);
            pgraphics->line_to(pointSecond);
         }



      }



      void graphics::GetRect(::int_rectangle * lprect, enum enum_element eelement)
      {
         if (eelement == e_element_clock)
         {
            lprect->left() = m_point.x();
            lprect->right() = lprect->left() + m_size.cx();
            lprect->top() = m_point.y();
            lprect->bottom() = lprect->top() + m_size.cy();
         }
      }



      void graphics::set_pos(int_point point, int_size sz)
      {
         m_point = point;
         m_size = sz;
      }


   } // namespace clock


} // namespace datetime



