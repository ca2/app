//
//  stock_icon.cpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 20/06/26 09:18.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#include "framework.h"
#include "graphics.h"
#include "path.h"
#include "pen.h"
#include "stock_icon.h"
#include "acme/prototype/geometry2d/polygon.h"


namespace draw2d
{

   stock_icon::stock_icon()
   {
      m_estockiconNew = e_stock_icon_none;
      m_estockicon = e_stock_icon_none;
      
   }

   stock_icon::~stock_icon()
   {
      
      
   }

   void stock_icon::on_draw(::draw2d::graphics * pgraphics, const ::f64_rectangle & rectangleNew)
   {
      
      auto estockicon = m_estockiconNew;
      
      auto rectangle = rectangleNew;

      if (estockicon == e_stock_icon_close)
      {
         
         
         //         m_ppen->m_dWidth *= 2.0;
         //         m_ppen->set_modified();
         
         ::pointer<::draw2d::path> &ppath = m_ppath;
         
         if(m_rectangle != rectangle || m_estockicon != estockicon)
         {
            
            m_estockicon = estockicon;
            
            m_rectangle = rectangleNew;
            
            rectangle.deflate(rectangle.width() / 7.0, rectangle.height() / 7.0);
            
            
            constructø(ppath);
            
            ppath->begin_figure();
            ppath->add_line(rectangle.top_left(), rectangle.bottom_right());
            ppath->end_figure();
            ppath->begin_figure();
            ppath->add_line(rectangle.bottom_left(), rectangle.top_right());
            ppath->end_figure();
            
            
         }
         
         pgraphics->draw(ppath);
         
      }
      else if (estockicon == e_stock_icon_zoom)
      {
         
         rectangle.deflate(0, rectangle.height() / 7.0);
         
         pgraphics->draw_rectangle(rectangle);
         
         //m_ppen->m_elinecapBeg = ::draw2d::e_line_cap_flat;
         //m_ppen->m_elinecapEnd = ::draw2d::e_line_cap_flat;
         //set_current_point(rectangle.top_left() + ::i32_size(0,(::i32) (ppen->m_dWidth/2.0)));
         //line_to(rectangle.top_right() + ::i32_size(0,(::i32)(ppen->m_dWidth / 2.0)));
         //set_current_point(rectangle.top_left() + ::i32_size(0,(::i32)(ppen->m_dWidth)));
         //line_to(rectangle.top_right() + ::i32_size(0,(::i32)(ppen->m_dWidth)));
         //set_current_point(rectangle.top_left() + ::i32_size(0,(::i32)(ppen->m_dWidth *3.0 / 2.0)));
         //line_to(rectangle.top_right() + ::i32_size(0,(::i32)(ppen->m_dWidth *3.0 / 2.0)));
         //set_current_point(rectangle.top_left() + ::i32_size(0,(::i32)(ppen->m_dWidth*2.0)));
         //line_to(rectangle.top_right() + ::i32_size(0,(::i32)(ppen->m_dWidth*2.0)));
         
      }
      else if (estockicon == e_stock_icon_restore)
      {
         
         rectangle.deflate(0, rectangle.height() / 6.0);
         
         ::f64_rectangle rect1(rectangle);
         
         rect1.deflate(0, 0, ceil(rectangle.width() / 3.0), ceil(rectangle.height() / 3.0));
         
         ::f64_rectangle rect2(rect1);
         
         rect2.Align(e_align_bottom_right, rectangle);
         
         pgraphics->draw_rectangle(rect2);
         
         if(m_ppenBase != pgraphics->m_ppen || m_estockicon != estockicon)
         {
            
            m_ppenBase = pgraphics->m_ppen;
            
            constructø(m_ppen1);
            
            m_ppen1->copy_attributes(m_ppenBase);
            m_ppen1->m_elinecapBeg = ::draw2d::e_line_cap_square;
            m_ppen1->m_elinecapEnd = ::draw2d::e_line_cap_square;
            m_ppen1->set_modified();
            
            auto dPenWidth = m_ppen1->m_dWidth;
            
            pgraphics->set(m_ppen1);
            
            pgraphics->line(
                            rect2.top_left() + ::f64_size(0., (dPenWidth / 2.0)),
                            rect2.top_right() + ::f64_size(0., (dPenWidth / 2.0)));
            
            pgraphics->line(
                            rect2.top_left() + ::f64_size(0., (dPenWidth)),
                            rect2.top_right() + ::f64_size(0., (dPenWidth)));
            
            pgraphics->line(
                            rect2.top_left(),
                            rect2.top_right());
            
            pgraphics->line(
                            rect1.top_left() + ::f64_size(0., (dPenWidth / 2.0)),
                            rect1.top_right() + ::f64_size(0., (dPenWidth / 2.0)));
            
            pgraphics->line(
                            rect1.top_left() + ::f64_size(0., (dPenWidth)),
                            rect1.top_right() + ::f64_size(0., (dPenWidth)));
            
            pgraphics->line(
                            rect1.top_left(),
                            rect1.top_right());
            
            //   m_ppen->m_elinecapBeg = ::draw2d::e_line_cap_square;
            //   m_ppen->m_elinecapEnd = ::draw2d::e_line_cap_square;
            //   m_ppen->set_modified();
            
            pgraphics->line(
                            rect1.top_left(),
                            rect1.bottom_left());
            pgraphics->line(
                            rect1.top_right(),
                            { rect1.right, rect2.top });
            pgraphics->line(
                            rect1.bottom_left(),
                            { rect2.left, rect1.bottom });
            pgraphics->line(
                            rect2.top_left(),
                            rect2.bottom_left());
            pgraphics->line(
                            rect2.top_right(),
                            rect2.bottom_right());
            pgraphics->line(
                            rect2.bottom_left(),
                            rect2.bottom_right());
            
         }
         
      }
      else if (estockicon == e_stock_icon_iconify)
      {
         
         
         rectangle.deflate(0, rectangle.height() / 7.0);
         
         
         //set_current_point();
         pgraphics->line(rectangle.bottom_left(), rectangle.bottom_right());
         //set_current_point(rectangle.bottom_left() - ::i32_size(0,(::i32)(m_ppen->m_dWidth*2.0)));
         //line_to(rectangle.bottom_right() - ::i32_size(0,(::i32)(m_ppen->m_dWidth*2.0)));
         //set_current_point(rectangle.bottom_left() - ::i32_size(0,(::i32)(m_ppen->m_dWidth*3.0 / 2.0)));
         //line_to(rectangle.bottom_right() - ::i32_size(0,(::i32)(m_ppen->m_dWidth*3.0 / 2.0)));
         //set_current_point(rectangle.bottom_left() - ::i32_size(0,(::i32)(m_ppen->m_dWidth)));
         //line_to(rectangle.bottom_right() - ::i32_size(0,(::i32)(m_ppen->m_dWidth)));
         //set_current_point(rectangle.bottom_left() - ::i32_size(0,(::i32)(m_ppen->m_dWidth / 2.0)));
         //line_to(rectangle.bottom_right() - ::i32_size(0,(::i32)(m_ppen->m_dWidth / 2.0)));
         //set_current_point(rectangle.bottom_left());
         //line_to(rectangle.bottom_right());
         
      }
      else if (estockicon == e_stock_icon_transparent_frame)
      {
         
      }
      else if (estockicon == e_stock_icon_dock)
      {
         
         
         
         rectangle.deflate(rectangle.height() / 8.0, rectangle.height() / 8.0);
         
         pgraphics->draw_ellipse(rectangle);
         
         ::f64_rectangle rect1(rectangle);
         
         if (::is_set(pgraphics->m_ppen))
         {
            
            rect1.deflate((::i32)(pgraphics->m_ppen->m_dWidth / 2.0), (::i32)(pgraphics->m_ppen->m_dWidth / 2.0));
            
         }
         
         pgraphics->draw_ellipse(rect1);
         
         ::f64_rectangle rect2(rectangle);
         
         if (::is_set(pgraphics->m_ppen))
         {
            
            rect2.deflate((::i32)(pgraphics->m_ppen->m_dWidth), (::i32)(pgraphics->m_ppen->m_dWidth));
            
         }
         
         pgraphics->draw_ellipse(rect2);
         
         
      }
      else if (estockicon == e_stock_icon_notify)
      {
         
         rectangle.deflate(rectangle.height() / 2.0, rectangle.height() / 2.0);
         
         pgraphics->draw_ellipse(rectangle);
         
         ::f64_rectangle rect1(rectangle);
         
         rect1.deflate((::i32)(pgraphics->m_ppen->m_dWidth / 2.0), (::i32)(pgraphics->m_ppen->m_dWidth / 2.0));
         
         pgraphics->draw_ellipse(rect1);
         
         ::f64_rectangle rect2(rectangle);
         
         rect2.deflate((::i32)(pgraphics->m_ppen->m_dWidth), (::i32)(pgraphics->m_ppen->m_dWidth));
         
         pgraphics->draw_ellipse(rect2);
         
      }
      else if (estockicon == e_stock_icon_level_up)
      {
         
         rectangle.deflate(rectangle.height() / 3.0, rectangle.height() / 3.0);
         
         auto & pointa = m_pointa;
         
         if(m_rectangle != rectangle || m_estockicon != estockicon)
         {
            
            m_estockicon = estockicon;
            
            m_rectangle = rectangleNew;
            
            pointa.erase_all();
            
            pointa.add(rectangle.bottom_left());
            
            pointa.add(rectangle.bottom_right());
            
            pointa.add((rectangle.right + rectangle.left) / 2.0, rectangle.top);
            
         }
         
         pgraphics->polygon(pointa);
         
      }
      else if (estockicon == e_stock_icon_level_down)
      {
         
         rectangle.deflate(rectangle.height() / 3.0, rectangle.height() / 3.0);
         
         auto & pointa = m_pointa;
         
         if(m_rectangle != rectangle || m_estockicon != estockicon)
         {
            
            m_estockicon = estockicon;
            
            m_rectangle = rectangleNew;
            
            pointa.erase_all();
            
            pointa.add(rectangle.top_left());
            
            pointa.add(rectangle.top_right());
            
            pointa.add((rectangle.right + rectangle.left) / 2.0, rectangle.bottom);
            
         }
         
         pgraphics->polygon(pointa);
         
      }
      else
      {
         
         throw ::not_implemented();
         
      }
      
   }


} // namespace draw2d



