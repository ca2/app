/*
    src/pwidget.cpp -- Base class of all widgets

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "Widget.h"
#include "Layout.h"
#include "Screen.h"
#include "Window.h"
#include "Button.h"
#include "VScrollPanel.h"
#include "acme/parallelization/synchronous_lock.h"
#include "nano2d/context.h"
#include "nano2d/draw2d_context.h"
#include "aura/user/user/interaction.h"


/* Uncomment the following definition to draw red bounding
   boxes around widgets (useful for debugging drawing code) */

   // #define NANOUI_SHOW_WIDGET_BOUNDS 1

namespace nanoui
{


   Widget::Widget(Widget* parent)
      : m_pwidgetParent(nullptr), m_ptheme(nullptr), m_playout(nullptr),
      m_bVisible(true), m_bEnabled(true),
      m_bMouseHover(false), m_tooltip(""), m_font_size(-1)
      , m_icon_extra_scale(1.f)/*, m_cursor(Cursor::Arrow)*/
   {
      m_bNeedLayout = false;
      //m_iHoverCandidateChildStart = -1;
      //m_iHoverCandidateChildEnd = -1;
      if (parent)
         parent->add_child(this);
   }


   Widget::~Widget() 
   {
      
      //   if (std::uncaught_exceptions() > 0) {
      //      /* If a pwidget constructor throws an exception, it is immediately
      //         dealloated but may still be referenced by a parent. Be conservative
      //         and don't decrease the reference count of children while dispatching
      //         exceptions. */
      //      return;
      //   }

      for (auto pchild : m_children) 
      {

         if (pchild)
         {
         
            pchild->dec_ref();

         }

      }

   }


   /// Return whether or not the pwidget is currently visible (assuming all parents are visible)
   bool Widget::visible() const
   { 
      
      return m_bVisible; 
   
   }


   /// Set whether or not the pwidget is currently visible (assuming all parents are visible)
   void Widget::set_visible(bool bVisible)
   {
      
      m_bVisible = bVisible; 
   
   }


   void Widget::toggle_visible()
   { 

      auto bVisible = this->visible();
      
      set_visible(!bVisible);

   }


   /// Return whether or not this pwidget is currently enabled
   bool Widget::enabled() const
   {
      
      return m_bEnabled; 
   
   }

   /// Set whether or not this pwidget is currently enabled
   void Widget::set_enabled(bool bEnabled) 
   {
      
      m_bEnabled = bEnabled; 
   
   }


   void Widget::set_theme(Theme* theme) 
   {

      if (m_ptheme.get() == theme)
      {
       
         return;

      }

      m_ptheme = theme;

      for (auto pchild : m_children)
      {

         pchild->set_theme(theme);

      }

   }


   float Widget::font_size() const
   {

      return (m_font_size < 0.f && m_ptheme) ? (float)m_ptheme->m_iStandardFontSize : (float)m_font_size;

   }


   void Widget::set_font_size(float font_size)
   {

      m_font_size = (int)font_size;

   }


   void Widget::set_size(const size_i32& size)
   {

      m_size = size;

   }


   void Widget::on_begin_draw(::nano2d::context* pcontext)
   {

      if (m_callbackLayout)
      {

         auto callbackLayout = m_callbackLayout;

         m_callbackLayout.clear();

         callbackLayout(pcontext);

      }

   }


   size_i32 Widget::preferred_size(::nano2d::context* pcontext, bool bRecalcTextSize)
   {

      if (m_playout)
      {
       
         return m_playout->preferred_size(pcontext, this, bRecalcTextSize);

      }
      else
      {

         return m_size;

      }

   }


   void Widget::set_need_layout()
   {

      m_bNeedLayout = true;

      m_callbackLayout = [this](::nano2d::context* pcontext)
      {

         parent()->perform_layout(pcontext);
         perform_layout(pcontext);

      };

      //auto pparent = m_pwidgetParent;

      //while (pparent)
      //{

      //   pparent->set_need_layout();

      //   ::pointer < Window > pwindow = pparent;

      //   if (pwindow)
      //   {

      //      break;

      //   }

      //   pparent = pparent->m_pwidgetParent;

      //}

   }


   void Widget::perform_layout(::nano2d::context* pcontext, bool bRecalcTextSize)
   {

      if (m_callbackLayout)
      {

         auto callbackLayout = m_callbackLayout;

         m_callbackLayout.clear();

         callbackLayout(pcontext);

      }

      if (m_playout)
      {

         m_playout->perform_layout(pcontext, this, bRecalcTextSize);

      }
      else
      {

         for (auto pchild : m_children)
         {

            auto pref = pchild->preferred_size(pcontext, bRecalcTextSize), fix = pchild->fixed_size();

            pchild->set_size({
               fix[0] ? fix[0] : pref[0],
               fix[1] ? fix[1] : pref[1]
            });

            pchild->perform_layout(pcontext);

         }

      }

   }


   Widget* Widget::find_widget(const point_i32& p)
   {

      for (auto it = m_children.get_upper_bound(); it >= 0; it--)
      {

         Widget* pchild = m_children[it];

         auto posChild = pchild->m_pos;

         auto offsetScroll = get_scroll_offset();

         auto pointChildClient = p - posChild - offsetScroll;

         if (pchild->visible() && pchild->contains(pointChildClient))
         {

            return pchild->find_widget(pointChildClient);

         }

      }

      return contains(p) ? this : nullptr;

   }


   const Widget* Widget::find_widget(const point_i32& p) const
   {

      for (auto it = m_children.get_upper_bound(); it >= 0; it--)
      {

         Widget* pchild = m_children[it];

         if (pchild->visible() && pchild->contains(p - m_pos))
         {

            return pchild->find_widget(p - m_pos);

         }

      }

      return contains(p) ? this : nullptr;

   }


   bool Widget::mouse_button_event(const point_i32& p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key& ekeyModifiers)
   {

      for (auto it = m_children.get_upper_bound(); it >= 0; it--)
      {

         Widget* pchild = m_children[it];

         if (pchild->visible())
         {

            auto posChild = pchild->m_pos;

            auto offsetScroll = get_scroll_offset();

            auto pointChildClient = p - posChild - offsetScroll;

            if (pchild->contains(pointChildClient))
            {

               if (pchild->mouse_button_event(pointChildClient, emouse, down, bDoubleClick, ekeyModifiers))
               {

                  bool bChildFocused = pchild->focused();

                  if (emouse == ::user::e_mouse_left_button && down && !bChildFocused)
                  {

                     pchild->request_focus();

                  }

                  return true;

               }

            }

         }

      }

      return false;

   }


   bool Widget::mouse_motion_event(const point_i32& p, const size_i32& rel, bool bDown, const ::user::e_key& ekeyModifiers)
   {

      bool bHandled = false;

      ::count iCount = 0;

      ::index iStart = 0;

      ::index iEnd = (::index)m_children.size() - 1;

      //if (m_iHoverCandidateChildStart >= 0 && m_iHoverCandidateChildEnd >= m_iHoverCandidateChildStart)
      //{

      //   iStart = m_iHoverCandidateChildStart;

      //   iEnd = m_iHoverCandidateChildEnd;

      //}

      auto children = m_children;

      for (auto i = iStart; i <= iEnd; i++)
      {

         Widget* pchild = children[i];

         if (!pchild->visible())
         {

            continue;

         }

         auto posChild = pchild->m_pos;

         auto offsetScroll = get_scroll_offset();

         auto pointChildClient = p - posChild - offsetScroll;

         bool contained = pchild->contains(pointChildClient);

         bool prev_contained = pchild->contains(pointChildClient - rel);

         if (contained != prev_contained)
         {

            bHandled |= pchild->mouse_enter_event(pointChildClient, contained, ekeyModifiers);

         }

         if (contained || prev_contained)
         {

            bHandled |= pchild->mouse_motion_event(pointChildClient, rel, bDown, ekeyModifiers);

         }

         iCount++;

      }

      return bHandled;

   }

   
   bool Widget::scroll_event(const point_i32& p, const size_f32& rel)
   {

      for (auto it = m_children.get_upper_bound(); it >= 0; it--)
      {

         Widget* pchild = m_children[it];

         if (!pchild->visible())
         {

            continue;

         }

         auto pointChildClient = p - pchild->m_pos;

         if (pchild->contains(pointChildClient) && pchild->scroll_event(pointChildClient, rel))
         {

            return true;

         }

      }

      return false;

   }


   //bool Widget::mouse_drag_event(const sequence2_i32&, const sequence2_i32&, const ::user::e_key&)
   //{

   //   return false;

   //}


   bool Widget::mouse_enter_event(const point_i32&, bool bEnter, const ::user::e_key& ekeyModifiers)
   {

      m_bMouseHover = bEnter;

      return false;

   }


   void Widget::set_mouse_capture()
   {

      screen()->set_mouse_capture(this);

   }

   
   void Widget::release_mouse_capture()
   {

      screen()->release_mouse_capture();

   }


   bool Widget::focus_event(bool focused)
   {

      //m_focused = focused;

      return false;

   }


   bool Widget::keyboard_event(::user::enum_key, int, int, const ::user::e_key&, const ::string& strText)
   {

      return false;

   }


   bool Widget::keyboard_character_event(unsigned int)
   {

      return false;

   }


   void Widget::add_child(::index iIndex, Widget* pwidget)
   {
      synchronous_lock lock(screen()->m_puserinteraction->synchronization());
      //m_iHoverCandidateChildStart = -1;
      //m_iHoverCandidateChildEnd = -1;
      ASSERT(iIndex <= child_count());
      m_children.insert_at(iIndex, pwidget);
      pwidget->inc_ref();
      pwidget->set_parent(this);
      pwidget->set_theme(m_ptheme);
   }

   void Widget::add_child(Widget* pwidget) {
      add_child(child_count(), pwidget);
   }


   void Widget:: set_layout(Layout* layout)
   {
      
      m_playout = layout; 
   
   }


   void Widget::erase_child(Widget* pwidget)
   {

      synchronous_lock lock(screen()->m_puserinteraction->synchronization());

      pwidget->destroy_window();

      if (!m_children.erase(pwidget))
      {

         throw ::exception(error_wrong_state, "Widget::erase_child(): pwidget not found!");

      }

   }


   void Widget::erase_child_at(::index iIndex) 
   {

      if (iIndex < 0 || iIndex >= (int)m_children.size())
      {
      
         throw ::exception(error_index_out_of_bounds, "Widget::erase_child_at(): out of bounds!");

      }

      Widget* pwidget = m_children[iIndex];

      m_children.erase_at(iIndex);

      pwidget->dec_ref();

   }


   void Widget::destroy_window()
   {

      on_destroy_window();
   
      for (auto pwidgetChild : m_children)
      {

         pwidgetChild->destroy_window();

      }

      m_children.clear();
   
   }


   void Widget::on_destroy_window()
   {

      auto pscreen = screen();

      if (pscreen)
      {

         if (pscreen->m_pwidgetDrag == this)
         {

            pscreen->m_pwidgetDrag.release();

         }

      }

      m_pwidgetParent.release();
      m_ptheme.release();
      m_playout.release();


   }


   Window* Widget::window() 
   {

      Widget* pwidget = this;

      while (true) 
      {

         if (!pwidget)
         {

            return nullptr;

         }

         Window* window = dynamic_cast<Window*>(pwidget);

         if (window)
         {

            return window;

         }

         pwidget = pwidget->parent();

      }

   }


   Screen* Widget::screen() 
   {

      Widget* pwidget = this;

      while (true) 
      {

         if (!pwidget)
         {

            return nullptr;

         }

         Screen* pscreen = dynamic_cast<Screen*>(pwidget);

         if (pscreen)
         {

            return pscreen;

         }

         pwidget = pwidget->parent();

      }

   }


   const Screen* Widget::screen() const 
   {
      
      return const_cast<Widget*>(this)->screen(); 
   
   }


   const Window* Widget::window() const 
   {
      
      return const_cast<Widget*>(this)->window(); 
   
   }


   bool Widget::focused() const
   { 

      auto pscreen = screen();

      if (::is_null(pscreen))
      {

         return false;

      }

      return pscreen->m_focus_path.contains(this); 
   
   }


   void Widget::request_focus()
   {

      auto pscreen = screen();

      if (::is_null(pscreen))
      {

         return;

      }

      pscreen->update_focus(this);

   }


   bool Widget::need_to_draw(::nano2d::context* pcontext)
   {

      ::pointer < ::nano2d::draw2d_context > pdraw2dcontext;

      pdraw2dcontext = pcontext;

      if (pdraw2dcontext)
      {

         auto interactionRectangle = interaction_rectangle();

         auto pparent = m_pwidgetParent;

         if (pparent)
         {

            interactionRectangle.offset(pparent->get_accumulated_scroll_offset());

         }

         if (!screen()->m_puserinteraction->needs_to_draw(pdraw2dcontext->m_pgraphics, interactionRectangle))
         {

//            information() << "Opting out from draw pwidget!! " << typeid(*this).name();

            return false;

         }

      }

      information() << "Need to draw pwidget!! " << typeid(*this).name();

      return true;

   }


   void Widget::call_draw(::nano2d::context* pcontext)
   {

      if (m_bNeedLayout)
      {

         m_bNeedLayout = false;

         perform_layout(pcontext);

      }

      if (!need_to_draw(pcontext))
      {

         return;

      }

      draw(pcontext);

   }


   void Widget::draw(::nano2d::context* pcontext)
   {

//#if defined(NANOUI_SHOW_WIDGET_BOUNDS)
//
//      pcontext->StrokeWidth(ctx, 1.0f);
//
//      pcontext->begin_path(ctx);
//
//      pcontext->rectangle(ctx, m_pos.x() - 0.5f, m_pos.y() - 0.5f, m_size.cx() + 1, m_size.cy() + 1);
//
//      pcontext->stroke_color(ctx, ::color::RGBA_color(255, 0, 0, 255));
//
//      pcontext->stroke(ctx);
//
//#endif

      //if (m_children.empty())
      //{

      //   return;

      //}

      //::rectangle_i32 rectangleThis;

      //auto pscrollPanel = dynamic_cast <VScrollPanel*>(parent());

      ////float yOffset = 0.f;

      ////if (pscrollPanel)
      ////{

      ////   auto pparent = m_pwidgetParent;

      ////   yOffset = pscrollPanel->get_y_offset();

      ////   rectangleThis = ::rectangle_i32_dimension(0, m_pos.y() - yOffset, m_size.cx(), m_size.cy());

      ////}
      ////else
      ////{

      //rectangleThis = ::rectangle_i32_dimension(0, 0, m_size.cx(), m_size.cy());

      //}

      //::index iStart = 0;

      //::index iEnd = (::index)m_children.size() - 1;

      //if (m_iHoverCandidateChildStart >= 0 && m_iHoverCandidateChildEnd >= m_iHoverCandidateChildStart)
      //{

      //   iStart = m_iHoverCandidateChildStart;

      //   iEnd = m_iHoverCandidateChildEnd;

      //}

      if (m_children.empty())
      {

         return;

      }

      ::rectangle_i32 rectangleThis;

      ::size_i32 offsetScroll;

      auto pparent = m_pwidgetParent;

      if (pparent)
      {

         offsetScroll = pparent->get_scroll_offset();

      }

      rectangleThis = ::rectangle_i32_dimension(-offsetScroll.cx(), -offsetScroll.cy(), m_size.cx(), m_size.cy());

      pcontext->translate((float)m_pos.x(), (float)m_pos.y());

      for (::index i = 0; i < m_children.size(); i++)
      {

         auto pchild = m_children[i];

         if (!pchild->visible())
         {

            continue;

         }

         pchild->on_begin_draw(pcontext);

         auto childX = pchild->m_pos.x();

         auto childY = pchild->m_pos.y();

         auto childW = pchild->m_size.cx();

         auto childH = pchild->m_size.cy();

         auto rectangleChild = ::rectangle_i32_dimension(childX, childY, childW, childH);

         if (rectangleChild.intersects(rectangleThis))
         {

            //if (pscrollPanel)
            //{

            //   if (i < m_iHoverCandidateChildStart || m_iHoverCandidateChildStart < 0)
            //   {

            //      m_iHoverCandidateChildStart = i;

            //   }

            //   if (i > m_iHoverCandidateChildEnd)
            //   {


            //      m_iHoverCandidateChildEnd = i;
            //   }

            //}

   //#if !defined(NANOUI_SHOW_WIDGET_BOUNDS)
   //         
   //         pcontext->save();
   //
   //         pcontext->intersect_scissor((float)pchild->m_pos.x(), (float)pchild->m_pos.y(),
   //            (float)pchild->m_size.cx(), (float)pchild->m_size.cy());
   //
   //#endif

            pchild->call_draw(pcontext);

            //#if !defined(NANOUI_SHOW_WIDGET_BOUNDS)
            //         
            //         pcontext->restore();
            //
            //#endif

         }
         else
         {

            //         output_debug_string("optimized");

         }

      }

      pcontext->translate((float)-m_pos.x(), (float)-m_pos.y());

   }


   //void Widget::_nanoui_to_user(::user::interaction * puserinteraction)
   //{
   //
   //   m_puserinteraction = puserinteraction;
   //
   //   if (::is_null(m_puserinteraction))
   //   {
   //
   //      m_puserinteraction->m_pappearance = this;
   //
   //   }
   //
   //   return;
   //
   ////   for (auto & pchild : m_children)
   ////   {
   ////
   ////      pchild->_nanoui_to_user(m_puserinteraction);
   ////
   ////   }
   //
   //}


   point_i32 Widget::screen_position() const
   {
   
      auto absolutePosition = absolute_position();

      auto pointScreenMainWindow = screen()->m_puserinteraction->position();

      auto pointScreen = pointScreenMainWindow;

      pointScreen += absolutePosition;

      return pointScreen;

   }


   size_i32 Widget::get_scroll_offset() const
   {

      return {};

   }


   size_i32 Widget::get_accumulated_scroll_offset() const
   {

      auto offsetScroll = get_scroll_offset();

      if (m_pwidgetParent)
      {

         offsetScroll += m_pwidgetParent->get_accumulated_scroll_offset();

      }

      return offsetScroll;

   }


   ::rectangle_i32 Widget::interaction_rectangle() const
   {

      ::rectangle_i32 rectangle;

      auto absolutionPosition = absolute_position();

      rectangle.left = absolutionPosition.x();
      rectangle.top = absolutionPosition.y();
      rectangle.right = rectangle.left + m_size.cx();
      rectangle.bottom = rectangle.top + m_size.cy();

      return rectangle;

   }


   void Widget::set_need_redraw(const ::rectangle_i32& rectangleParentCoordinates)
   {

      auto rectangleInteraction = rectangleParentCoordinates;

      if (rectangleInteraction.is_empty())
      {

         rectangleInteraction = interaction_rectangle();

      }
      else
      {

         auto absolutePosition = absolute_position();

         rectangleInteraction.offset(absolutePosition.x(), absolutePosition.y());

      }
      
      auto pparent = m_pwidgetParent;

      if (pparent)
      {

         auto offsetScroll = pparent->get_accumulated_scroll_offset();

         rectangleInteraction += offsetScroll;

      }


      screen()->m_puserinteraction->set_need_redraw(rectangleInteraction);

   }


   void Widget::post_redraw()
   {

      screen()->m_puserinteraction->post_redraw();

   }

   
   void Widget::fixed_placement(const ::rectangle_i32& rectangle)
   {

      set_position(rectangle.top_left());

      set_fixed_size(rectangle.size());

   }


   void Widget::expose_fixed_size(const ::rectangle_i32& rectangle)
   {

      auto positionOld = m_pos;

      auto rectangleOld = interaction_rectangle();

      auto positionNew = rectangle.top_left();

      set_position(positionNew);

      auto sizeNew = rectangle.size();

      set_fixed_size(sizeNew);

      auto rectangleNew = interaction_rectangle();

      if (positionOld != positionNew)
      {

         set_need_redraw(rectangleOld);

         set_need_redraw(rectangleNew);

      }
      else
      {

         auto rectangleRightDifference = rectangleOld.right_plus_difference(rectangleNew);

         auto rectangleBottomDifference = rectangleOld.bottom_difference(rectangleNew);

         rectangleRightDifference.normalize();

         rectangleBottomDifference.normalize();

         set_need_redraw(rectangleRightDifference);

         set_need_redraw(rectangleBottomDifference);

      }

      post_redraw();

   }


   bool Widget::is_mouse_down() const
   {

      return screen()->is_mouse_down(this);

   }


   void Widget::set_mouse_down(bool bMouseDown)
   {

      if (bMouseDown)
      {

         screen()->m_pwidgetMouseDown = this;

      }
      else
      {

         if (screen()->m_pwidgetMouseDown == this)
         {

            screen()->m_pwidgetMouseDown = nullptr;

         }

      }

   }


   bool Widget::contains(const point_i32& p) const 
   {

      ::pointer < Button > pbutton = this;

      if (pbutton)
      {

         output_debug_string("Button contains");

      }

      //sequence2_i32 d = p - m_pos;
      return p.x() >= 0 && p.y() >= 0 && p.x() < m_size.cx() && p.y() < m_size.cy();

   }


} // namespace nanoui



