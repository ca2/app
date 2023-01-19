#include "framework.h"
#include "render.h"
#include <math.h>
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/brush.h"
#include "application.h"


CLASS_DECL_ACME ::color::color dk_red(); // <3 tbs


namespace app_integration
{


   void render::_001OnDrawBoxGradient(::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->text_out(100, 50, "Round Rectangle (100, 100) - (900, 500) r = 100");

      ::rectangle_f64 r(100, 100, 900, 500);

      double Δx = m_rectangle.width() / 1000.0;

      double Δy = m_rectangle.height() / 600.0;

      double d = minimum(Δx, Δy);

      r *= d;

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

      pgraphics->fill_round_rectangle(r, pbrush, radius);

      pgraphics->::draw2d::graphics::draw_round_rectangle(r, ppen, radius);

      draw_text(pgraphics);

   }


} // namespace simple_drawing



