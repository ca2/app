#include "framework.h"



//#include <math.h>


namespace hotplugin
{


   void plugin::on_bare_paint_veri_discreet(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectangle)

   {

      double dRate = get_progress_rate();

      if(dRate <= 0.0)
      {

         return;

      }

      ::rectangle_i32 rectangleWindow;
      window_rectangle(&rectangleWindow);
      //  i32 cx = rectangleWindow.right() - rectangleWindow.left();
      //i32 cy = rectangleWindow.bottom() - rectangleWindow.top();




      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
      int h = 33;
      int m = 49 * 2;

      int top;
      int bottom;
      int left;
      int right;

      if(::height(rectangle) < h)
      {
         top = rectangle.top();
         bottom = rectangle.bottom();
      }
      else
      {
         top = rectangle.top() + ::height(rectangle) / 2 - h / 2;
         bottom = rectangle.top() + ::height(rectangle) / 2 + h / 2;
      }

      if(::width(rectangle) < m)
      {
         left = rectangle.left();
         right = rectangle.right();
      }
      else
      {

         left = rectangle.left() + minimum(m / 2,::width(rectangle) / 2);
         right = rectangle.right() - minimum(m / 2,::width(rectangle) / 2);

      }

      ::rectangle_i32 rectangleBar(left,top,right,bottom);




      auto ppen = __create < ::draw2d::pen > ();

      ppen->create_null();

      auto pbrush = __create < ::draw2d::brush >();

      pbrush->create_solid(argb(190, 49, 50, 49));

      pgraphics->SelectObject(pen);

      pgraphics->SelectObject(brush);

      auto rectangleX = this->rectangle();


      ::rectangle_i32 rectangleProgress(rectangleBar);

      rectangleProgress.right() = (int) (rectangleProgress.left() + rectangleBar.width() * minimum(1.0, maximum(0.0, dRate)));

      ::rectangle_i32 rectangleProgressComplement(rectangleBar);

      rectangleProgressComplement.left() = rectangleProgress.right();

      pgraphics->rectangle(rectangleProgressComplement);

      {

         unsigned char uchR,uchG,uchB;
         auto pbrush = __create < ::draw2d::brush > ();
         get_progress_color(uchR,uchG,uchB,dRate,0);
         pbrush->create_solid(argb(184,uchR,uchG,uchB));
         pgraphics->fill_rectangle(rectangleProgress,br);

      }

      ppen->create_solid(1.0,argb(149, 150, 149, 142));

      pgraphics->draw_rectangle(rectangleBar, ppen);

      ::write_text::font_pointer f(e_create);

      f->create_pixel_font("Calibri",18);

      pgraphics->SelectObject(f);

      string strProgress;

      strProgress.formatf("%0.3f%%",dRate * 100.0);

      rectangleBar.left() +=4;

      rectangleBar.top() += 5;

      pgraphics->set_text_color(argb(255, 255, 255, 255));

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_clear_type_grid_fit);

      pgraphics->text_out(rectangleBar.left(), rectangleBar.top(), m_strStatus + " : " + strProgress + " : " + m_strStatus2);

   }


} // namespace hotplugin


