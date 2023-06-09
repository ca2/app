// Created by camilo on 2022-03-23 11:55 PM <3ThomasBorregaardSorensen!! (Thomas likes number 5!!)
#include "framework.h"
#include "render.h"
#include "application.h"
#include <math.h>
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/path.h"
#include "aura/graphics/draw2d/pen.h"


CLASS_DECL_ACME ::color::color dk_red(); // <3 tbs


namespace app_integration
{


   void render::_001OnDrawCirclePath(::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->text_out(100, 50, "Circle Path (300, 300) - (800, 800) r = 250");

      ::rectangle_f64 r(300, 300, 800, 800);

      double greekdeltax = m_rectangle.width() / 1000.0;

      double greekdeltay = m_rectangle.height() / 900.0;

      double d = minimum(greekdeltax, greekdeltay);

      r *= d;

      ::draw2d::path_pointer ppath;

      __construct(ppath);

      ppath->begin_figure();

      ppath->add_ellipse(r);

      ppath->close_figure();

      double radius = 100 * d;

      ::draw2d::pen_pointer ppen;

      __construct(ppen);

      auto & echeckSimple = get_app()->application_properties().m_echeckSimple;

      if (__bool(echeckSimple))
      {

         ppen->create_null();

      }
      else
      {

         ppen->create_solid(5.0, ::color::green);

      }

      ::draw2d::brush_pointer pbrush;

      __construct(pbrush);

      pbrush->CreateBoxGradientBrush(r.top_left(), r.size(), radius, ::dk_red(), ::color::transparent);

      pgraphics->fill(ppath, pbrush);

      pgraphics->draw(ppath, ppen);

      draw_text(pgraphics);

   }


} // namespace simple_drawing



