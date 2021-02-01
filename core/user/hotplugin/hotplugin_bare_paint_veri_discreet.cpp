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

      ::rectangle_i32 rectWindow;
      get_window_rect(&rectWindow);
      //  i32 cx = rectWindow.right - rectWindow.left;
      //i32 cy = rectWindow.bottom - rectWindow.top;




      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
      int h = 33;
      int m = 49 * 2;

      int top;
      int bottom;
      int left;
      int right;

      if(::height(rectangle) < h)
      {
         top = rectangle.top;
         bottom = rectangle.bottom;
      }
      else
      {
         top = rectangle.top + ::height(rectangle) / 2 - h / 2;
         bottom = rectangle.top + ::height(rectangle) / 2 + h / 2;
      }

      if(::width(rectangle) < m)
      {
         left = rectangle.left;
         right = rectangle.right;
      }
      else
      {

         left = rectangle.left + min(m / 2,::width(rectangle) / 2);
         right = rectangle.right - min(m / 2,::width(rectangle) / 2);

      }

      ::rectangle_i32 rectBar(left,top,right,bottom);




      ::draw2d::pen_pointer pen(e_create);

      pen->create_null();

      ::draw2d::brush_pointer brush(e_create);

      brush->create_solid(ARGB(190, 49, 50, 49));

      pgraphics->SelectObject(pen);

      pgraphics->SelectObject(brush);

      ::rectangle_i32 rectClient;

      get_client_rect(rectClient);


      ::rectangle_i32 rectProgress(rectBar);

      rectProgress.right = (::i32) (rectProgress.left + rectBar.width() * min(1.0, max(0.0, dRate)));

      ::rectangle_i32 rectProgressComplement(rectBar);

      rectProgressComplement.left = rectProgress.right;

      pgraphics->rectangle_i32(rectProgressComplement);

      {

         byte uchR,uchG,uchB;
         ::draw2d::brush_pointer br(e_create);
         get_progress_color(uchR,uchG,uchB,dRate,0);
         br->create_solid(ARGB(184,uchR,uchG,uchB));
         pgraphics->fill_rect(rectProgress,br);

      }

      pen->create_solid(1.0,ARGB(149, 150, 149, 142));

      pgraphics->draw_rect(rectBar, pen);

      ::draw2d::font_pointer f(e_create);

      f->create_pixel_font("Calibri",18);

      pgraphics->SelectObject(f);

      string strProgress;

      strProgress.Format("%0.3f%%",dRate * 100.0);

      rectBar.left +=4;

      rectBar.top += 5;

      pgraphics->set_text_color(ARGB(255, 255, 255, 255));

      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_clear_type_grid_fit);

      pgraphics->text_out(rectBar.left, rectBar.top, m_strStatus + " : " + strProgress + " : " + m_strStatus2);

   }


} // namespace hotplugin


