// Created by camilo on 2023-06-30 18:50 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "redraw.h"
#include "aura/graphics/draw2d/clip.h"
#include "aura/graphics/draw2d/graphics.h"


namespace user
{


   void redraw::clear()
   {

      m_rectangleaNeedRedraw.clear();

   }


   void redraw::initialize_and_transfer(pointer_array < ::user::redraw_item > && redrawitema)
   {

      m_rectangleaNeedRedraw.clear();

      for (auto & predrawitem : redrawitema)
      {

         m_rectangleaNeedRedraw.append(predrawitem->m_rectanglea);

         if (predrawitem->m_functiona.has_element())
         {

            for (auto & function : predrawitem->m_functiona)
            {

               if (function)
               {

                  function();

               }

            }

         }

      }

      for (auto & r : m_rectangleaNeedRedraw)
      {

         if (r.area() > 500 * 500)
         {

            information() << "rNeedRedraw.area() has area > 500 * 500";

         }
         if (r.area() < 50 * 50)
         {

            information() << "rNeedRedraw.area() has area < 50 * 50";

         }

      }

   }


   void redraw::set_need_redraw(const ::rectangle_i32 & rectangle)
   {

      if (m_rectangleaNeedRedraw.has_element())
      {

         m_rectangleaNeedRedraw.add_if_none_contains(rectangle);

      }

   }


   void redraw::set_need_redraw(const ::rectangle_i32_array & rectanglea)
   {

      if (m_rectangleaNeedRedraw.has_element())
      {

         m_rectangleaNeedRedraw.append_if_none_contains(rectanglea);

      }

   }


   bool redraw::needs_to_draw(const ::rectangle_i32 & rectangle)
   {

      bool bNeedsToDraw = false;

      if (m_rectangleaNeedRedraw.is_empty())
      {

         return true;

      }

      for (auto & r : m_rectangleaNeedRedraw)
      {

         if (r.intersects(rectangle))
         {

            bNeedsToDraw = true;

            break;

         }

      }

      if (!bNeedsToDraw)
      {

         //information() << "Opting out from draw!! " << typeid(*this).name() << " " << m_atom.as_string();

      }

      return bNeedsToDraw;

   }


   void redraw::apply_clip(shift_i32 ΔHostToClient)
   {

      m_pgraphics->reset_clip();

      if (m_rectangleaNeedRedraw.has_element())
      {

         ::draw2d::clip_group clipgroup;

         for (auto rectangleHostNeedRedraw : m_rectangleaNeedRedraw)
         {

            auto rectangleNeedRedraw = rectangleHostNeedRedraw;

            ΔHostToClient(rectangleNeedRedraw);

            auto prectangle = __new(::draw2d::clip_rectangle);

            prectangle->m_item = rectangleNeedRedraw;

            clipgroup.add(prectangle);

         }

         m_pgraphics->intersect_clip(clipgroup);

      }

   }


} // namespace user


