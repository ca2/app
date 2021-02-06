#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "axis/user/_user.h"
#endif
#include "simple_ui_draw.h"


namespace simple_ui
{


   draw::draw()
   {


   }


   draw::~draw()
   {


   }




   void draw::simple_ui_draw_frame_window_rect(const ::rectangle_i32& rectangle, ::draw2d::graphics_pointer& pgraphics)
   {

      ::rectangle_i32 rectDraw;

      rectDraw = rectangle;

      rectDraw.deflate(0, 0, 1, 1);

      ::draw2d::brush_pointer b(e_create);

      b->create_solid(ARGB(255, 255, 255, 255));

      pgraphics->set(b);

      ::draw2d::pen_pointer point_i32(e_create);

      point_i32->create_solid(1.0, ARGB(255, 0, 0, 0));

      pgraphics->set(point);

      pgraphics->rectangle(rectDraw);

   }


   void draw::simple_ui_draw_fuzzy_color_spread(const ::rectangle_i32& rectangle, ::draw2d::graphics_pointer& pgraphics)
   {
      /*
      ::rectangle_i32 rectDraw;

      get_window_rect(rectDraw);

      int i = 0;
      int j = 0;
      int iCount = rectDraw.width();
      int jCount = rectDraw.height();

      byte * point = (byte *)m_pimage->get_data();

      for (i = 0; i < iCount; i++)
      {
      for (j = 0; j < jCount; j++)
      {
      double dPhase = fmod((((double) ::get_tick() * 360 * 0.5984 / 1000.0) + (i * 360.0 / (double)iCount) + (j * 360.0 / (double)jCount) + ((double)(sin(((double) ::get_tick() * 3.1415 * 2.0  *0.0484 / 1000.0) + i * 3.1415 * 2.0 * 2.0 / (double)(iCount)) * sin(((double) ::get_tick() * 3.1415 * 2.0  * 0.0484 / 1000.0) + j * 3.1415 * 2.0 * 2.0 / (double)(jCount)) * 360))), 360.0);
      i32 iR;
      i32 iG;
      i32 iB;
      double dRate = fmod(dPhase, 60.0) / 60.0;
      i32 iColor = (i32)(dRate * 155.0);
      if (dPhase < 60)
      {
      // purple to blue
      iR = 255 - iColor;
      iG = 100;
      iB = 255;
      }
      else if (dPhase < (120))
      {
      // blue to cyan
      iR = 100;
      iG = 100 + iColor;
      iB = 255;
      }
      else if (dPhase < (180))
      {
      // cyan to green
      iR = 100;
      iG = 255;
      iB = 255 - iColor;
      }
      else if (dPhase < (240))
      {
      // green to yellow
      iR = 100 + iColor;
      iG = 255;
      iB = 100;
      }
      else if (dPhase < (300))
      {
      // yellow to red
      iR = 255;
      iG = 255 - iColor;
      iB = 100;
      }
      else
      {
      // red to purple
      iR = 255;
      iG = 100;
      iB = 100 + iColor;
      }

      point_i32[0] = iR;
      point_i32[1] = iG;
      point_i32[2] = iB;
      point_i32[3] = 84;
      point_i32 += 4;

      }
      }
      */


   }


   void draw::simple_ui_draw_dark_glass(const ::rectangle_i32& rectangle, ::draw2d::graphics_pointer& pgraphics)
   {

      ::rectangle_i32 rectDraw;

      rectDraw = rectangle;

      pgraphics->fill_rect(rectDraw, ARGB(90, 127, 127, 127));

   }



   void draw::simple_ui_draw_pestana(const ::rectangle_i32& rectangle, ::draw2d::graphics_pointer& pgraphics)
   {

      ::rectangle_i32 rectDraw;

      rectDraw = rectangle;

      pgraphics->set_alpha_mode(draw2d::alpha_mode_blend);

      int iCount = rectDraw.height();
      ::draw2d::pen_pointer point_i32(e_create);
      for (int i = 0; i < iCount; i += 2)
      {
         double dRate = (double)i / (double)iCount;
         dRate = 1.0 - dRate;
         byte a1 = __byte_rate(1.0 - dRate, 23, 90);
         byte r1 = __byte_rate(dRate, 23, 127);
         byte g1 = __byte_rate(dRate, 23, 127);
         byte b1 = __byte_rate(dRate, 23, 127);
         point_i32->create_solid(1.0, ARGB(a1, r1, g1, b1));
         pgraphics->set(point);
         pgraphics->draw_line(rectDraw.left, i, rectDraw.right, i);

      }


   }



   void draw::simple_ui_draw_auth_box(const ::rectangle_i32& rectangle, ::draw2d::graphics_pointer& pgraphics)
   {

      ::rectangle_i32 rectDraw = rectangle;

      pgraphics->set_alpha_mode(draw2d::alpha_mode_blend);

      // front
      point_f64 pa[4];
      //  0       1
      //
      //
      //  3       2

      // back
      point_f64 pb[4];


      // guards
      point_f64 pc[4];


      pa[0].x = rectangle.left;
      pa[0].y = rectDraw.top;
      pa[1].x = rectDraw.right - rectDraw.width() / 10;
      pa[1].y = rectDraw.top + rectDraw.height() / 10;
      pa[2].x = rectDraw.right - rectDraw.width() / 8;
      pa[2].y = rectDraw.bottom - rectDraw.height() / 10;
      pa[3].x = rectDraw.left;
      pa[3].y = rectDraw.bottom;


      pb[0].x = rectDraw.left + rectDraw.width() / 6;
      pb[0].y = rectDraw.top + rectDraw.height() / 6;
      pb[1].x = rectDraw.right - rectDraw.width() / 6;
      pb[1].y = rectDraw.top + rectDraw.height() / 6;
      pb[2].x = rectDraw.right - rectDraw.width() / 5;
      pb[2].y = rectDraw.bottom - rectDraw.height() / 4;
      pb[3].x = rectDraw.left + rectDraw.width() / 5;
      pb[3].y = rectDraw.bottom - rectDraw.height() / 4;

      {

         ::draw2d::brush_pointer b(e_create);

         b->create_solid(ARGB(192, 220, 220, 220));

         pgraphics->set(b);

         pgraphics->fill_polygon(pb, 4);

         ::draw2d::pen_pointer point_i32(e_create);

         point_i32->create_solid(1.0, ARGB(192, 192, 192, 192));

         pgraphics->set(point);

         pgraphics->draw_polygon(pb, 4);


      }













      // top
      ::memcpy_dup(pc, pa, sizeof(pb));
      pc[2].x = pb[1].x;
      pc[2].y = pb[1].y;
      pc[3].x = pb[0].x;
      pc[3].y = pb[0].y;

      {

         ::draw2d::brush_pointer b(e_create);

         b->create_solid(ARGB(180, 210, 210, 210));

         pgraphics->set(b);

         pgraphics->fill_polygon(pc, 4);

         ::draw2d::pen_pointer point_i32(e_create);

         point_i32->create_solid(1.0, ARGB(180, 180, 177, 177));

         pgraphics->set(point);

         pgraphics->draw_polygon(pc, 4);


      }
      // left
      ::memcpy_dup(pc, pa, sizeof(pb));
      pc[1].x = pb[0].x;
      pc[1].y = pb[0].y;
      pc[2].x = pb[3].x;
      pc[2].y = pb[3].y;
      {

         ::draw2d::brush_pointer b(e_create);

         b->create_solid(ARGB(123, 120, 120, 123));

         pgraphics->set(b);

         pgraphics->fill_polygon(pc, 4);

         ::draw2d::pen_pointer point_i32(e_create);

         point_i32->create_solid(1.0, ARGB(123, 90, 90, 90));

         pgraphics->set(point);

         pgraphics->draw_polygon(pc, 4);


      }
      // bottom
      ::memcpy_dup(pc, pa, sizeof(pb));
      pc[0].x = pb[3].x;
      pc[0].y = pb[3].y;
      pc[1].x = pb[2].x;
      pc[1].y = pb[2].y;
      {

         ::draw2d::brush_pointer b(e_create);

         b->create_solid(ARGB(149, 192, 192, 192));

         pgraphics->set(b);

         pgraphics->fill_polygon(pc, 4);

         ::draw2d::pen_pointer point_i32(e_create);

         point_i32->create_solid(1.0, ARGB(149, 176, 176, 176));

         pgraphics->set(point);

         pgraphics->draw_polygon(pc, 4);


      }
      // right
      ::memcpy_dup(pc, pa, sizeof(pb));
      pc[0].x = pb[1].x;
      pc[0].y = pb[1].y;
      pc[3].x = pb[2].x;
      pc[3].y = pb[2].y;
      {

         ::draw2d::brush_pointer b(e_create);

         b->create_solid(ARGB(90, 150, 149, 149));

         pgraphics->set(b);

         pgraphics->fill_polygon(pc, 4);

         ::draw2d::pen_pointer point_i32(e_create);

         point_i32->create_solid(1.0, ARGB(90, 120, 120, 123));

         pgraphics->set(point);

         pgraphics->draw_polygon(pc, 4);


      }





      {

         ::draw2d::pen_pointer point_i32(e_create);

         point_i32->create_solid(1.0, ARGB(190, 90, 90, 90));

         pgraphics->set(point);

         pgraphics->draw_polygon(pa, 4);

      }


   }

   void draw::simple_ui_draw_back_01_old(const ::rectangle_i32 & rectangle, ::draw2d::graphics_pointer& pgraphics)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      color32_t crOut;

      color32_t crIn;

      /*   if (eschema == ::hotplugin::plugin::schema_darker)
         {

         crOut = ARGB(0, 90, 90, 80);

         crIn = ARGB(133, 90, 90, 80);

         }
         else*/
      {

         crOut = ARGB(0, 255, 255, 233);

         crIn = ARGB(133, 255, 255, 233);

      }

      i32 iBorderH = min(rectangle.height() / 2, 49);

      ::draw2d::brush_pointer br(e_create);

      br->CreateLinearGradientBrush(rectangle.top_left(), point_i32(rectangle.left, rectangle.top + iBorderH), crOut, crIn);

      pgraphics->fill_rect(::rectangle_i32(rectangle.left, rectangle.top, (i32)rectangle.width(), iBorderH), br);

      br->create_solid(crIn);

      pgraphics->fill_rect(::rectangle_i32(rectangle.left, rectangle.top + iBorderH, (i32)rectangle.width(), (i32)rectangle.height() - (iBorderH * 2)), br);

      br->CreateLinearGradientBrush(point_i32(rectangle.left, rectangle.bottom - iBorderH), rectangle.bottom_left(), crIn, crOut);

      pgraphics->fill_rect(::rectangle_i32(rectangle.left, rectangle.bottom - iBorderH, (i32)rectangle.width(), iBorderH), br);

   }


   void draw::simple_ui_draw_back_01_new(const ::rectangle_i32& rectangle, ::draw2d::graphics_pointer& pgraphics)
   {

      /*simple_solid_brush br(g, ARGB(255, 255, 255, 255));

      simple_pen pen;

      pen.create_solid(ARGB(255, 0, 0, 0));

      pgraphics->select(br);

      pgraphics->select(pen);

      m_rectangle.deflate(0, 0, 1, 1);

      pgraphics->rectangle(m_rectangle);*/

      //pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);

      //pgraphics->fill_rect(rectangle,ARGB(0,0,0,0));

   }



} // namespace simple_ui



