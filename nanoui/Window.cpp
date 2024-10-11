/*
    src/window.cpp -- Top-level window pwidget

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "Window.h"
#include "Layout.h"
#include "PopupButton.h"
#include "Screen.h"
#include "acme/constant/user_key.h"
#include "nano2d/context.h"
#include "aura/user/user/interaction.h"


namespace nanoui
{


   Window::Window(Widget* parent, const ::scoped_string& title)
: Widget(parent), m_title(title), m_button_panel(nullptr), m_bModal(false),
m_bDrag(false)
   {

      m_bPendingCentering = false;

   }

void Window::on_destroy_window()
{
   
   ::nanoui::defer_destroy_window(m_button_panel);
   
   Widget::on_destroy_window();
   
}

   void Window::on_begin_draw(::nano2d::context* pcontext)
   {

      Widget::on_begin_draw(pcontext);

      if (m_bPendingCentering)
      {

         m_bPendingCentering = false;

         _center(pcontext);

      }

   }


   size_i32 Window::preferred_size(::nano2d::context* pcontext, bool bRecalcTextSize)
   {

      bool bButtonPanelWasVisible = true;

      if (m_button_panel)
      {

         bButtonPanelWasVisible = m_button_panel->m_bVisible;

         m_button_panel->set_visible(false);

      }

      auto sizeResult = Widget::preferred_size(pcontext, bRecalcTextSize);

      if (m_button_panel)
      {

         m_button_panel->set_visible(bButtonPanelWasVisible);

      }

      if (bRecalcTextSize)
      {

         pcontext->font_size(18.0f);
         pcontext->font_face("sans-bold");
         pcontext->text_bounds(0, 0, m_title, &m_boundsHeader);

      }

      return size_i32(
         ::maximum(sizeResult.cx(), (int)(m_boundsHeader.width() + 20)),
         ::maximum(sizeResult.cy(), (int)(m_boundsHeader.height()))
      );
   }


   Widget* Window::button_panel() 
   {
   
      if (!m_button_panel) 
      {
      
         m_button_panel = __allocate Widget(this);

         m_button_panel->set_layout(__allocate BoxLayout(e_orientation_horizontal, e_alignment_middle, 0, 4));

      }

      return m_button_panel;

   }


   void Window::perform_layout(::nano2d::context* pcontext, bool bRecalcTextSize) 
   {

      if (!m_button_panel) 
      {

         Widget::perform_layout(pcontext, bRecalcTextSize);

      }
      else 
      {

         m_button_panel->set_visible(false);

         Widget::perform_layout(pcontext, bRecalcTextSize);

         for (auto pwidgetChild : m_button_panel->children()) 
         {

            pwidgetChild->set_fixed_size({22, 22});

            pwidgetChild->set_font_size(15);

         }

         m_button_panel->set_visible(true);

         m_button_panel->set_size({width(), 22});

         m_button_panel->set_position({
            width() - (m_button_panel->preferred_size(pcontext, bRecalcTextSize).cx() + 5), 3 });

         m_button_panel->perform_layout(pcontext, bRecalcTextSize);

      }

   }


   void Window::draw(::nano2d::context* pcontext)
   {

      information() << "Draw Window!! " << typeid(*this).name();

//      if (m_offsetToApplyOnDraw.cx() != 0 || m_offsetToApplyOnDraw.cy() != 0)
//      {
//
//         m_pos += m_offsetToApplyOnDraw;
//
//         m_offsetToApplyOnDraw.cx() = 0;
//
//         m_offsetToApplyOnDraw.cy() = 0;
//
//      }

      if (!need_to_draw(pcontext))
      {

         return;

      }

      //int ds = m_ptheme->m_iWindowDropShadowSize;
      int cr = m_ptheme->m_iWindowCorderRadius;
      int hh = m_ptheme->m_iWindowHeaderHeight;

      /* Draw window */
      {
         ::nano2d::guard guard(pcontext);
         //pcontext->save();
         pcontext->begin_path();
         pcontext->rounded_rectangle((float)m_pos.x(), (float)m_pos.y(), (float)m_size.cx(), (float)m_size.cy(), (float)cr);

         pcontext->fill_color(m_bMouseHover ? m_ptheme->m_colorWindowFillFocused
            : m_ptheme->m_colorWindowFillUnfocused);
         pcontext->fill();


         ///* Draw a drop shadow */
         //::nano2d::paint shadow_paint = pcontext->box_gradient(
         //   ctx, m_pos.x(), m_pos.y(), m_size.cx(), m_size.cy(), cr * 2, ds * 2,
         //   m_ptheme->m_colorDropShadow, m_ptheme->m_colorTransparent);

         //pcontext->Save();
         //pcontext->reset_scissor();
         //pcontext->begin_path();
         //pcontext->rectangle(m_pos.x() - ds, m_pos.y() - ds, m_size.cx() + 2 * ds, m_size.cy() + 2 * ds);
         //pcontext->rounded_rectangle(m_pos.x(), m_pos.y(), m_size.cx(), m_size.cy(), cr);
         //pcontext->path_winding(::nano2d::e_solidity_hole);
         //pcontext->fill_paint(shadow_paint);
         //pcontext->fill();
         //pcontext->Restore();

         if (m_title.has_char()) {
            /* Draw header */
            ::nano2d::paint header_paint = pcontext->linear_gradient(
               (float)m_pos.x(), (float)m_pos.y(), (float)m_pos.x(),
               (float)m_pos.y() + (float)hh,
               m_ptheme->m_colorWindowHeaderGradientTop,
               m_ptheme->m_colorWindowHeaderGradientBottom);

            pcontext->begin_path();
            pcontext->rounded_rectangle((float)m_pos.x(), (float)m_pos.y(), (float)m_size.cx(), (float)hh, (float)cr);

            pcontext->fill_paint(header_paint);
            pcontext->fill();

            pcontext->begin_path();
            pcontext->rounded_rectangle((float)m_pos.x(), (float)m_pos.y(), (float)m_size.cx(), (float)hh, (float)cr);
            pcontext->stroke_color(m_ptheme->m_colorWindowHeaderSeparationTop);

            //pcontext->Save();
            //pcontext->intersect_scissor(m_pos.x(), m_pos.y(), m_size.cx(), 0.5f);
            //pcontext->stroke();
            //pcontext->Restore();

            pcontext->begin_path();
            pcontext->move_to(m_pos.x() + 0.5f, m_pos.y() + hh - 1.5f);
            pcontext->line_to(m_pos.x() + m_size.cx() - 0.5f, m_pos.y() + hh - 1.5f);
            pcontext->stroke_color(m_ptheme->m_colorWindowHeaderSeparationBottom);
            pcontext->stroke();

            pcontext->font_size(18.0f);
            pcontext->font_face("sans-bold");
            pcontext->text_align(::nano2d::e_align_center | ::nano2d::e_align_middle);

            //pcontext->font_blur(2);
            //pcontext->fill_color(m_ptheme->m_colorDropShadow);
            //pcontext->text(m_pos.x() + m_size.cx() / 2,
               // m_pos.y() + hh / 2, m_title.c_str(), nullptr);

            //pcontext->font_blur(0);
            pcontext->fill_color(focused() ? m_ptheme->m_colorWindowTitleFocused
               : m_ptheme->m_colorWindowTitleUnfocused);
            pcontext->text(m_pos.x() + m_size.cx() / 2.f, m_pos.y() + hh / 2.f - 1.f,
               m_title);
         }

       //  pcontext->restore();

      }

      Widget::draw(pcontext);

   }


   void Window::dispose() 
   {

      screen()->dispose_window(this);

   }


   void Window::_center(::nano2d::context* pcontext) 
   {

      screen()->center_window(this, pcontext);

   }


   bool Window::mouse_enter_event(const point_i32& pointCursor, bool enter, const ::user::e_key& ekeyModifiers)
   {

      Widget::mouse_enter_event(pointCursor, enter, ekeyModifiers);

      return true;

   }


#define __MOUSE_LEFT_BUTTON 0
#define __MOUSE_RIGHT_BUTTON 1


   bool Window::mouse_motion_event(const point_i32&pointCursor, const size_i32& rel, bool bDown, const ::user::e_key& ekeyModifiers)
   {

      if (m_bDrag && (ekeyModifiers & ::user::e_key_left_button) != 0 && bDown)
      {

         auto offset = screen()->m_pointLastCursor - m_pointDragStartCursor;
         
         auto posNew = m_pointDragStartPosition + offset;
         
         posNew = posNew.maximum(::point_i32(0, 0));
         
         posNew = posNew.minimum(parent()->size() - m_size);
         
         if(posNew != m_pointLastDragPosition)
         {
            
            ::point_i32 parentPosition;
            
            if(parent())
            {
             
               parentPosition = parent()->absolute_position();
               
            }
            
            ::rectangle_i32 rectangleOld(m_pointLastDragPosition, m_size);
            
            if(parent())
            {
               
               rectangleOld += parentPosition;
               
            }

            informationf("rectangleOld (%d, %d, %d, %d)",
                        rectangleOld.left(),
                        rectangleOld.top(),
                        rectangleOld.right(),
                        rectangleOld.bottom());
            
            ::rectangle_i32_array rectanglea;
            
            rectanglea.add(rectangleOld);

            for (auto ppopupbutton : m_popupbuttona)
            {

               auto ppopup = ppopupbutton->popup();

               ::rectangle_i32 rectangleOld(ppopup->m_pointLastDragPosition, ppopup->m_size);

               if (ppopup->parent())
               {

                  rectangleOld += ppopup->parent()->absolute_position();

               }

               if (ppopup->side() == Popup::Left)
               {

                  rectangleOld.right() += ppopup->anchor_size();

               }
               else
               {

                  rectangleOld.left() -= ppopup->anchor_size();

               }

               informationf("extra Popup Button : rectangleOld (%d, %d, %d, %d)",
                  rectangleOld.left(),
                  rectangleOld.top(),
                  rectangleOld.right(),
                  rectangleOld.bottom());

               rectanglea.add(rectangleOld);

            }

            ::rectangle_i32 rectangleNew(posNew, m_size);

            if(parent())
            {
               
               rectangleNew += parentPosition;
               
            }
            
            informationf("rectangleNew (%d, %d, %d, %d)",
                        rectangleNew.left(),
                        rectangleNew.top(),
                        rectangleNew.right(),
                        rectangleNew.bottom());

            rectanglea.add(rectangleNew);

            auto offset = posNew - m_pointLastDragPosition;

            for (auto ppopupbutton : m_popupbuttona)
            {

               auto ppopup = ppopupbutton->popup();

               ::rectangle_i32 rectangleNew(ppopup->m_pointLastDragPosition, ppopup->m_size);

               rectangleNew += offset;

               if (ppopup->parent())
               {

                  rectangleNew += ppopup->parent()->absolute_position();

               }

               if (ppopup->side() == Popup::Left)
               {

                  rectangleNew.right() += ppopup->anchor_size();

               }
               else
               {

                  rectangleNew.left() -= ppopup->anchor_size();

               }

               informationf("extra Popup Button : rectangleNew (%d, %d, %d, %d)",
                  rectangleNew.left(),
                  rectangleNew.top(),
                  rectangleNew.right(),
                  rectangleNew.bottom());

               rectanglea.add(rectangleNew);

            }
            
            auto function = [this, posNew]()
            {

               auto offset = posNew - m_pos;
               
               m_pos += offset;

               for (auto ppopupbutton : m_popupbuttona)
               {

                  auto ppopup = ppopupbutton->popup();

                  ppopup->m_pos += offset;

               }

            };
            
            screen()->m_puserinteraction->set_need_redraw(rectanglea, nullptr, function);
            
            post_redraw();
            
            m_pointLastDragPosition = posNew;
            
         }
         
         return true;

      }

      return Widget::mouse_motion_event(pointCursor, rel, bDown, ekeyModifiers);

   }


   bool Window::mouse_button_event(const point_i32& pointCursor, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key& ekeyModifiers)
   {

      if (Widget::mouse_button_event(pointCursor, emouse, down, bDoubleClick, ekeyModifiers))
      {

         return true;

      }

      if (emouse == ::user::e_mouse_left_button)
      {

         if (down)
         {

            auto bDrag = down && (pointCursor.y() - m_pos.y()) < m_ptheme->m_iWindowHeaderHeight;

            m_bDrag = bDrag;

            if (bDrag)
            {

               set_mouse_capture();
               
               m_pointDragStartCursor = screen()->m_pointLastCursor;
               
               m_pointDragStartPosition = m_pos;
               
               m_pointLastDragPosition = m_pos;

               return true;

            }

         }
         else
         {

            if (m_bDrag)
            {

               release_mouse_capture();

               if (m_functionOnMoved)
               {

                  m_functionOnMoved();

               }

               m_bDrag = false;

               return true;

            }

         }

      }

      return false;

   }


   bool Window::scroll_event(const point_i32& pointCursor, const size_f32& rel)
   {

      Widget::scroll_event(pointCursor, rel);

      return true;

   }


   void Window::refresh_relative_placement() {
      /* Overridden in \::pointer Popup */
   }

   //void Window::_nanoui_to_user(::user::interaction * puserinteraction)
   //{
   //
   //   //puserinteraction->__construct(m_pbox);
   //
   //   //m_pbox->create_control(puserinteraction, (iptr)(void*) this);
   //
   //   //m_pbox->display();
   //
   //   //m_pbox->place({ 10, 10, 99, 99 });
   //
   //   //m_pbox->set_need_layout();
   //
   //   //m_pbox->set_need_redraw();
   //
   //   //m_pbox->post_redraw();
   //
   //   //Widget::_nanoui_to_user(m_pbox);
   //
   //}



} // namespace nanoui


