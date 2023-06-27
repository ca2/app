#include "framework.h"
#include "path.h"
#include "path_simple_optimization.h"
#include "aura/graphics/draw2d/graphics.h"
//#include "acme/primitive/geometry2d/_enhanced.h"
#include "acme/primitive/geometry2d/item.h"
//#include "acme/primitive/geometry2d/_collection_enhanced.h"
//#include "aura/graphics/write_text/_shape.h"
//#include "acme/primitive/geometry2d/_defer_shape.h"
#include "acme/primitive/geometry2d/_defer_item.h"


namespace draw2d
{


   path_simple_optimization::path_simple_optimization(::draw2d::path * ppath)
   {
      
      m_iTopic = 0;
      m_iTopicLines = 0;
      m_iClose = 0;


      for (auto & pitem : ppath->m_itema)
      {

         auto eitem = pitem->type();

         switch (eitem)
         {
         case e_item_arc:
            m_iTopic++;
            m_pitemTopic = pitem;
            break;
         case e_item_line:
            m_iTopic += 2; // to quit optimization
         //
         //
         //         {
         //            if(m_iTopic == 0)
         //            {
         //            m_iTopicLines++;
         //            auto & line = pitem->shape < line_f64 >();
         //            if(m_pointa.is_empty())
         //            {
         //
         //               m_pointa.add(line.m_p1);
         //
         //            }
         //            else if(is_different(m_pointa.last(), line.m_p1, 0.001))
         //            {
         //
         //               m_iTopic++;
         //
         //            }
         //            if(is_different(m_pointa.last(), line.m_p2, 0.001))
         //            {
         //
         //               m_pointa.add(line.m_p2);
         //
         //            }
         //
         //            }
         //      }
            break;
         case e_item_lines:
            m_iTopic++;
            m_pitemTopic = pitem;
            break;
         case e_item_rectangle:
            m_iTopic++;
            m_pitemTopic = pitem;
            break;
         case e_item_ellipse:
            m_iTopic++;
            m_pitemTopic = pitem;
            break;
         case e_item_polygon:
            m_iTopic++;
            m_pitemTopic = pitem;
            break;
         case e_item_draw_text:
            m_iTopic++;
            m_pitemTopic = pitem;
            break;
         case e_item_text_out:
            m_iTopic++;
            m_pitemTopic = pitem;
            break;
         case e_item_close_figure:
            m_iClose++;
            break;
         default:
            break;
         }

      }

   }

   bool path_simple_optimization::draw(::draw2d::graphics * pgraphics, ::draw2d::pen * ppen)
   {

   if (m_iTopic == 1 && m_iTopicLines == 0 && ::is_set(m_pitemTopic))
   {

      auto eshape = m_pitemTopic->type();

      switch (eshape)
      {
      case e_item_arc:
         break;
      case e_item_line:
         break;
      case e_item_lines:
         break;
      case e_item_rectangle:
         if (::is_set(ppen))
         {
            pgraphics->set(ppen);
         }
         pgraphics->draw_rectangle(m_pitemTopic->cast < ::geometry2d::rectangle_item>()->m_item);
         return true;
      case e_item_ellipse:
         if (::is_set(ppen))
         {
            pgraphics->set(ppen);
         }
         pgraphics->draw_ellipse(m_pitemTopic->cast < ::geometry2d::ellipse_item>()->m_item);
         return true;
      case e_item_polygon:
         break;
      case e_item_draw_text:
         break;
      case e_item_text_out:
         break;
      default:
         break;
      }


   //   else if(m_iTopic <= 0 && m_iTopicLines > 0)
   //   {
   //
   //      if(m_iClose == 1 && m_pointa.size() >= 3)
   //      {
   //         if(::is_set(ppen))
   //         {
   //            pgraphics->set(ppen);
   //         }
   //
   //         pgraphics->draw_polygon(m_pointa.get_data(), m_pointa.get_size());
   //
   //         return true;
   //
   //      }
   //      else if(m_iClose <= 1)
   //      {
   //
   //         if(m_pointa.size() >= 2)
   //         {
   //            if(::is_set(ppen))
   //            {
   //               pgraphics->set(ppen);
   //            }
   //
   //            pgraphics->set_current_point(m_pointa.first());
   //
   //            for(::index i = 1; i < m_pointa.get_size(); i++)
   //            {
   //
   //               pgraphics->line_to(m_pointa[i]);
   //
   //            }
   //
   //         }
   //
   //         return true;
   //
   //      }
   //
   }

   return false;

   }


   bool path_simple_optimization::fill(::draw2d::graphics * pgraphics, ::draw2d::brush * pbrush)
   {

   if (m_iTopic == 1 && m_iTopicLines == 0 && ::is_set(m_pitemTopic))
   {

      auto eitem = m_pitemTopic->type();

      switch (eitem)
      {
      case e_item_arc:
         break;
      case e_item_line:
         break;
      case e_item_lines:
         break;
      case e_item_rectangle:
         if (::is_set(pbrush))
         {
            pgraphics->set(pbrush);
         }
         pgraphics->fill_rectangle(m_pitemTopic->cast < ::geometry2d::rectangle_item>()->m_item);
         return true;
      case e_item_ellipse:
         if (::is_set(pbrush))
         {
            pgraphics->set(pbrush);
         }
         pgraphics->fill_ellipse(m_pitemTopic->cast < ::geometry2d::ellipse_item>()->m_item);
         return true;
      case e_item_polygon:
         break;
      case e_item_draw_text:
         break;
      case e_item_text_out:
         break;
      default:
         break;
      }

   }
   //   else if(m_iTopic <= 0 && m_iTopicLines > 0)
   //   {
   //
   //      if(m_iClose == 1 && m_pointa.size() >= 3)
   //      {
   //
   //         if(::is_set(pbrush))
   //         {
   //            pgraphics->set(pbrush);
   //         }
   //
   //         pgraphics->fill_polygon(m_pointa.get_data(), m_pointa.get_size());
   //
   //         return true;
   //
   //      }
   //      else if(m_iClose <= 1)
   //      {
   //
   //         information("filling opened path?");
   //
   ////         if(m_pointa.size() >= 2)
   ////         {
   ////            if(::is_set(ppen))
   ////            {
   ////               pgraphics->set(ppen);
   ////            }
   ////
   ////            pgraphics->set_current_point(m_pointa.first());
   ////
   ////            for(::index i = 1; i < pointa.get_size(); i++)
   ////            {
   ////
   ////               pgraphics->line_to(m_pointa[i]);
   ////
   ////            }
   ////
   ////         }
   //
   //         return true;
   //
   //      }
   //
   //   }

   return false;

   }



   ::pointer<::draw2d::path_optimization>create_path_simple_optimization(::draw2d::path * ppath)
   {

   return __new(path_simple_optimization(ppath));

   }


} //namespace draw2d



