#include "framework.h"
#include "simple_ui_draw.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"


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

      ::rectangle_i32 rectangleDraw;

      rectangleDraw = rectangle;

      rectangleDraw.deflate(0, 0, 1, 1);

      ::draw2d::brush_pointer b(e_create, this);

      b->create_solid(argb(255, 255, 255, 255));

      pgraphics->set(b);

      auto ppen = __create < ::draw2d::pen > ();

      ppen->create_solid(1.0, argb(255, 0, 0, 0));

      pgraphics->set(ppen);

      pgraphics->rectangle(rectangleDraw);

   }


   void draw::simple_ui_draw_fuzzy_color_spread(const ::rectangle_i32& rectangle, ::draw2d::graphics_pointer& pgraphics)
   {
      /*
      ::rectangle_i32 rectangleDraw;

      window_rectangle(rectangleDraw);

      int i = 0;
      int j = 0;
      int iCount = rectangleDraw.width();
      int jCount = rectangleDraw.height();

      unsigned char * point = (unsigned char *)m_pimage->get_data();

      for (i = 0; i < iCount; i++)
      {
      for (j = 0; j < jCount; j++)
      {
      double dPhase = fmod((((double) ::get_tick() * 360 * 0.5984 / 1000.0) + (i * 360.0 / (double)iCount) + (j * 360.0 / (double)jCount) + ((double)(sin(((double) ::get_tick() * 3.1415 * 2.0  *0.0484 / 1000.0) + i * 3.1415 * 2.0 * 2.0 / (double)(iCount)) * sin(((double) ::get_tick() * 3.1415 * 2.0  * 0.0484 / 1000.0) + j * 3.1415 * 2.0 * 2.0 / (double)(jCount)) * 360))), 360.0);
      int iR;
      int iG;
      int iB;
      double dRate = fmod(dPhase, 60.0) / 60.0;
      int iColor = (int)(dRate * 155.0);
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
      point += 4;

      }
      }
      */


   }


   void draw::simple_ui_draw_dark_glass(const ::rectangle_i32& rectangle, ::draw2d::graphics_pointer& pgraphics)
   {

      ::rectangle_i32 rectangleDraw;

      rectangleDraw = rectangle;

      pgraphics->fill_rectangle(rectangleDraw, argb(90, 127, 127, 127));

   }



   void draw::simple_ui_draw_pestana(const ::rectangle_i32& rectangle, ::draw2d::graphics_pointer& pgraphics)
   {

      ::rectangle_i32 rectangleDraw;

      rectangleDraw = rectangle;

      pgraphics->set_alpha_mode(draw2d::e_alpha_mode_blend);

      int iCount = rectangleDraw.height();
      auto ppen = __create < ::draw2d::pen > ();
      for (int i = 0; i < iCount; i += 2)
      {
         double dRate = (double)i / (double)iCount;
         dRate = 1.0 - dRate;
         unsigned char a1 = __byte_rate(1.0 - dRate, 23, 90);
         unsigned char r1 = __byte_rate(dRate, 23, 127);
         unsigned char g1 = __byte_rate(dRate, 23, 127);
         unsigned char b1 = __byte_rate(dRate, 23, 127);
         ppen->create_solid(1.0, argb(a1, r1, g1, b1));
         pgraphics->set(ppen);
         pgraphics->draw_line(rectangleDraw.left(), i, rectangleDraw.right(), i);

      }


   }



   void draw::simple_ui_draw_auth_box(const ::rectangle_i32& rectangle, ::draw2d::graphics_pointer& pgraphics)
   {

      ::rectangle_i32 rectangleDraw = rectangle;

      pgraphics->set_alpha_mode(draw2d::e_alpha_mode_blend);

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


      pa[0].x() = rectangle.left();
      pa[0].y() = rectangleDraw.top();
      pa[1].x() = rectangleDraw.right() - rectangleDraw.width() / 10;
      pa[1].y() = rectangleDraw.top() + rectangleDraw.height() / 10;
      pa[2].x() = rectangleDraw.right() - rectangleDraw.width() / 8;
      pa[2].y() = rectangleDraw.bottom() - rectangleDraw.height() / 10;
      pa[3].x() = rectangleDraw.left();
      pa[3].y() = rectangleDraw.bottom();


      pb[0].x() = rectangleDraw.left() + rectangleDraw.width() / 6;
      pb[0].y() = rectangleDraw.top() + rectangleDraw.height() / 6;
      pb[1].x() = rectangleDraw.right() - rectangleDraw.width() / 6;
      pb[1].y() = rectangleDraw.top() + rectangleDraw.height() / 6;
      pb[2].x() = rectangleDraw.right() - rectangleDraw.width() / 5;
      pb[2].y() = rectangleDraw.bottom() - rectangleDraw.height() / 4;
      pb[3].x() = rectangleDraw.left() + rectangleDraw.width() / 5;
      pb[3].y() = rectangleDraw.bottom() - rectangleDraw.height() / 4;

      {

         ::draw2d::brush_pointer b(e_create, this);

         b->create_solid(argb(192, 220, 220, 220));

         pgraphics->set(b);

         pgraphics->fill_polygon(pb, 4);

         auto ppen = __create < ::draw2d::pen > ();

         ppen->create_solid(1.0, argb(192, 192, 192, 192));

         pgraphics->set(ppen);

         pgraphics->draw_polygon(pb, 4);


      }













      // top
      ::memory_copy(pc, pa, sizeof(pb));
      pc[2].x() = pb[1].x();
      pc[2].y() = pb[1].y();
      pc[3].x() = pb[0].x();
      pc[3].y() = pb[0].y();

      {

         ::draw2d::brush_pointer b(e_create, this);

         b->create_solid(argb(180, 210, 210, 210));

         pgraphics->set(b);

         pgraphics->fill_polygon(pc, 4);

         auto ppen = __create < ::draw2d::pen > ();

         ppen->create_solid(1.0, argb(180, 180, 177, 177));

         pgraphics->set(ppen);

         pgraphics->draw_polygon(pc, 4);


      }
      // left
      ::memory_copy(pc, pa, sizeof(pb));
      pc[1].x() = pb[0].x();
      pc[1].y() = pb[0].y();
      pc[2].x() = pb[3].x();
      pc[2].y() = pb[3].y();
      {

         ::draw2d::brush_pointer b(e_create, this);

         b->create_solid(argb(123, 120, 120, 123));

         pgraphics->set(b);

         pgraphics->fill_polygon(pc, 4);

         auto ppen = __create < ::draw2d::pen > ();

         ppen->create_solid(1.0, argb(123, 90, 90, 90));

         pgraphics->set(ppen);

         pgraphics->draw_polygon(pc, 4);


      }
      // bottom
      ::memory_copy(pc, pa, sizeof(pb));
      pc[0].x() = pb[3].x();
      pc[0].y() = pb[3].y();
      pc[1].x() = pb[2].x();
      pc[1].y() = pb[2].y();
      {

         ::draw2d::brush_pointer b(e_create, this);

         b->create_solid(argb(149, 192, 192, 192));

         pgraphics->set(b);

         pgraphics->fill_polygon(pc, 4);

         auto ppen = __create < ::draw2d::pen > ();

         ppen->create_solid(1.0, argb(149, 176, 176, 176));

         pgraphics->set(ppen);

         pgraphics->draw_polygon(pc, 4);


      }
      // right
      ::memory_copy(pc, pa, sizeof(pb));
      pc[0].x() = pb[1].x();
      pc[0].y() = pb[1].y();
      pc[3].x() = pb[2].x();
      pc[3].y() = pb[2].y();
      {

         ::draw2d::brush_pointer b(e_create, this);

         b->create_solid(argb(90, 150, 149, 149));

         pgraphics->set(b);

         pgraphics->fill_polygon(pc, 4);

         auto ppen = __create < ::draw2d::pen > ();

         ppen->create_solid(1.0, argb(90, 120, 120, 123));

         pgraphics->set(ppen);

         pgraphics->draw_polygon(pc, 4);


      }





      {

         auto ppen = __create < ::draw2d::pen > ();

         ppen->create_solid(1.0, argb(190, 90, 90, 90));

         pgraphics->set(ppen);

         pgraphics->draw_polygon(pa, 4);

      }


   }

   void draw::simple_ui_draw_back_01_old(const ::rectangle_i32 & rectangle, ::draw2d::graphics_pointer& pgraphics)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::color::color crOut;

      ::color::color crIn;

      /*   if (eschema == ::hotplugin::plugin::schema_darker)
         {

         crOut = argb(0, 90, 90, 80);

         crIn = argb(133, 90, 90, 80);

         }
         else*/
      {

         crOut = argb(0, 255, 255, 233);

         crIn = argb(133, 255, 255, 233);

      }

      int iBorderH = minimum(rectangle.height() / 2, 49);

      auto pbrush = __create < ::draw2d::brush > ();

      pbrush->CreateLinearGradientBrush(rectangle.top_left(), point_i32(rectangle.left(), rectangle.top() + iBorderH), crOut, crIn);

      pgraphics->fill_rectangle(::rectangle_i32(rectangle.left(), rectangle.top(), (int)rectangle.width(), iBorderH), pbrush);

      pbrush->create_solid(crIn);

      pgraphics->fill_rectangle(::rectangle_i32(rectangle.left(), rectangle.top() + iBorderH, (int)rectangle.width(), (int)rectangle.height() - (iBorderH * 2)), pbrush);

      pbrush->CreateLinearGradientBrush(point_i32(rectangle.left(), rectangle.bottom() - iBorderH), rectangle.bottom_left(), crIn, crOut);

      pgraphics->fill_rectangle(::rectangle_i32(rectangle.left(), rectangle.bottom() - iBorderH, (int)rectangle.width(), iBorderH), pbrush);

   }


   void draw::simple_ui_draw_back_01_new(const ::rectangle_i32& rectangle, ::draw2d::graphics_pointer& pgraphics)
   {

      /*simple_solid_brush br(g, argb(255, 255, 255, 255));

      simple_pen pen;

      pen.create_solid(argb(255, 0, 0, 0));

      pgraphics->select(br);

      pgraphics->select(pen);

      m_rectangle.deflate(0, 0, 1, 1);

      pgraphics->rectangle(m_rectangle);*/

      //pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

      //pgraphics->fill_rectangle(rectangle,argb(0,0,0,0));

   }



} // namespace simple_ui



