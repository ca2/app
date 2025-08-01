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
#include "TabWidget.h"
#include "in_place_edit.h"
#include "TextBox.h"
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
      m_bHoverCache = false;
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

//      for (auto pchild : m_children) 
//      {
//
//         if (pchild)
//         {
//         
//            pchild->dec_ref();
//
//         }
//
//      }

   }


   /// Return whether or not the pwidget is currently visible (assuming all parents are visible)
   bool Widget::visible() const
   {

      return m_bVisible;

   }


   bool Widget::is_child_visible() const
   {
      
      auto pParent = this->parent();
      
      if(pParent)
      {
         
         if(!pParent->is_child_visible())
         {
            
            return false;
            
         }
         
         ::cast < TabWidgetBase > pTabParent = this->parent();
         
         if(pTabParent)
         {
            
            if(!pTabParent->is_tab_selected(this))
            {
               
               return false;
               
            }
            
         }
         
      }

      return this->visible();

   }


   /// Set whether or not the pwidget is currently visible (assuming all parents are visible)
   void Widget::set_visible(bool bVisible)
   {

      m_bVisible = bVisible;

   }

   //::collection::count Widget::get_child_as_item_count()
   //{

   //   return m_children.size();

   //}


   //item_pointer Widget::get_child_as_item(::collection::index iIndex)
   //{

   //   return m_children[iIndex];

   //}


   item_pointer Widget::selected_item()
   {

      return nullptr;

   }


   item_pointer Widget::hover_item()
   {

      for (auto& pwidget : m_children)
      {

         if (pwidget->m_bMouseHover)
         {

            return pwidget;

         }

      }

      return nullptr;

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


   void Widget::set_theme(const ::pointer < Theme >& theme)
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


   void Widget::set_size(const int_size& size)
   {

      m_size = size;

   }


   void Widget::on_begin_draw(::nano2d::context * pcontext)
   {

      if (m_callbackLayout)
      {

         auto callbackLayout = m_callbackLayout;

         m_callbackLayout.clear();

         callbackLayout(pcontext);

      }

   }


   int_size Widget::preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize)
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

      m_callbackLayout = [this](::nano2d::context * pcontext)
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


   void Widget::perform_layout(::nano2d::context * pcontext, bool bRecalcTextSize)
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


   Widget* Widget::find_widget(const int_point& p)
   {

      //auto size = m_children.get_count();

      for (auto iIndex = m_children.get_upper_bound(); iIndex >= 0; iIndex--)
      {

         Widget* pchild = m_children[iIndex];

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


   bool Widget::has_ascendant(Widget* pwidgetAscendantCandidate) const
   {

      auto pwidgetAscendant = this->parent();

      while (pwidgetAscendant != nullptr)
      {

         if (pwidgetAscendantCandidate == pwidgetAscendant)
         {

            return true;

         }

         pwidgetAscendant = pwidgetAscendant->parent();

      }

      return false;

   }


   const Widget* Widget::find_widget(const int_point& p) const
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


   bool Widget::mouse_button_event(const int_point& p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key& ekeyModifiers)
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


   bool Widget::mouse_motion_event(const int_point& p, const int_size& rel, bool bDown, const ::user::e_key& ekeyModifiers)
   {

      bool bHandled = false;

      ::collection::count iCount = 0;

      ::collection::index iStart = 0;

      ::collection::index iEnd = (::collection::index)m_children.size() - 1;

      //if (m_iHoverCandidateChildStart >= 0 && m_iHoverCandidateChildEnd >= m_iHoverCandidateChildStart)
      //{

      //   iStart = m_iHoverCandidateChildStart;

      //   iEnd = m_iHoverCandidateChildEnd;

      //}

      auto& children = m_children;

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

         //         int pointY = pointChildClient[1];
         //
         //         int childTop = pchild->m_pos[1];
         //
         //         int childBottom = childTop + pchild->m_size[1];

         bool bHover = pchild->contains(pointChildClient) && this->m_bHoverCache;

         bool bHoverOld = pchild->m_bHoverCache;

         if (::is_different(bHover, bHoverOld))
         {

            pchild->m_bHoverCache = bHover;

            bHandled |= pchild->mouse_enter_event(pointChildClient, bHover, ekeyModifiers);

         }

         if (bHover || bHoverOld)
         {

            bHandled |= pchild->mouse_motion_event(pointChildClient, rel, bDown, ekeyModifiers);

         }

         iCount++;

      }

      return bHandled;

   }


   bool Widget::scroll_event(const int_point& p, const float_size& rel)
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


   //bool Widget::mouse_drag_event(const sequence2_int&, const sequence2_int&, const ::user::e_key&)
   //{

   //   return false;

   //}


   bool Widget::mouse_enter_event(const int_point&, bool bEnter, const ::user::e_key& ekeyModifiers)
   {

      m_bMouseHover = bEnter;

      m_bHoverCache = bEnter;

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


   bool Widget::keyboard_event(::user::enum_key, int, int, const ::user::e_key&, const ::scoped_string & scopedstrText)
   {

      return false;

   }


   bool Widget::keyboard_character_event(unsigned int)
   {

      return false;

   }


   void Widget::insert_child_at(::collection::index iIndex, Widget* pwidget)
   {

      if (::is_null(pwidget))
      {

         throw ::exception(error_bad_argument);

      }

      if (iIndex < 0)
      {

         throw ::exception(error_bad_argument);

      }

      _synchronous_lock lock(screen()->m_puserinteraction->synchronization());

      if (iIndex > child_count())
      {

         throw ::exception(error_bad_argument);

      }

      //m_iHoverCandidateChildStart = -1;

      //m_iHoverCandidateChildEnd = -1;

      //ASSERT(iIndex <= child_count());

      m_children.insert_at(iIndex, pwidget);

      //pwidget->inc_ref();

      pwidget->set_parent(this);

      pwidget->set_theme(m_ptheme);

   }


   void Widget::add_child(Widget* pwidget)
   {

      if (!pwidget->m_papplication)
      {

         pwidget->initialize(this);

      }

      insert_child_at(child_count(), pwidget);

   }


   void Widget::set_layout(const ::pointer < Layout>& layout)
   {

      m_playout = layout;

   }


   void Widget::erase_child(Widget* pwidget)
   {

      _synchronous_lock lock(screen()->m_puserinteraction->synchronization());

      pwidget->destroy_window();

      if (!m_children.erase(pwidget))
      {

         //throw ::exception(error_wrong_state, "Widget::erase_child(): pwidget not found!");

      }

   }


   void Widget::to_top()
   {

      _synchronous_lock lock(screen()->m_puserinteraction->synchronization());

      if (m_pwidgetParent->m_children.erase(this))
      {

         m_pwidgetParent->m_children.add(this);

      }

   }


   void Widget::erase_child_at(::collection::index iIndex)
   {

      if (iIndex < 0 || iIndex >= (int)m_children.size())
      {

         throw ::exception(error_index_out_of_bounds, "Widget::erase_child_at(): out of bounds!");

      }

      //Widget* pwidget = m_children[iIndex];

      m_children.erase_at(iIndex);

      //pwidget->dec_ref();

   }


   void Widget::destroy_window()
   {

      for (auto& pwidgetChild : m_children)
      {

         ::nanoui::defer_destroy_window(pwidgetChild);

      }

      on_destroy_window();

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

         if (pscreen->m_focus_path.contains(this))
         {

            pscreen->m_focus_path.clear();

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

      pscreen->on_child_set_focus(this);

   }


   void Widget::kill_focus()
   {

      auto pscreen = screen();

      if (::is_null(pscreen))
      {

         return;

      }

      pscreen->on_child_kill_focus(this);

   }


   bool Widget::need_to_draw(::nano2d::context * pcontext)
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

      //information() << "Need to draw pwidget!! " << typeid(*this).name();

      return true;

   }


   void Widget::call_draw(::nano2d::context * pcontext)
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


   void Widget::draw(::nano2d::context * pcontext)
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

            //::int_rectangle rectangleThis;

            //auto pscrollPanel = dynamic_cast <VScrollPanel*>(parent());

            ////float yOffset = 0.f;

            ////if (pscrollPanel)
            ////{

            ////   auto pparent = m_pwidgetParent;

            ////   yOffset = pscrollPanel->get_y_offset();

            ////   rectangleThis = ::int_rectangle_dimension(0, m_pos.y() - yOffset, m_size.cx(), m_size.cy());

            ////}
            ////else
            ////{

            //rectangleThis = ::int_rectangle_dimension(0, 0, m_size.cx(), m_size.cy());

            //}

            //::collection::index iStart = 0;

            //::collection::index iEnd = (::collection::index)m_children.size() - 1;

            //if (m_iHoverCandidateChildStart >= 0 && m_iHoverCandidateChildEnd >= m_iHoverCandidateChildStart)
            //{

            //   iStart = m_iHoverCandidateChildStart;

            //   iEnd = m_iHoverCandidateChildEnd;

            //}

      if (m_children.empty())
      {

         return;

      }

      ::int_rectangle rectangleThis;

      ::int_size offsetScroll;

      auto pparent = m_pwidgetParent;

      if (pparent)
      {

         offsetScroll = pparent->get_scroll_offset();

      }

      rectangleThis = ::int_rectangle_dimension(-offsetScroll.cx(), -offsetScroll.cy(), m_size.cx(), m_size.cy());

      pcontext->translate((float)m_pos.x(), (float)m_pos.y());

      for (::collection::index i = 0; i < m_children.size(); i++)
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

         auto rectangleChild = ::int_rectangle_dimension(childX, childY, childW, childH);

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

            //         informationf("optimized");

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


   int_point Widget::screen_position() const
   {

      auto absolutePosition = absolute_position();

      auto pointScreenMainWindow = screen()->m_puserinteraction->position();

      auto pointScreen = pointScreenMainWindow;

      pointScreen += absolutePosition;

      return pointScreen;

   }


   int_size Widget::get_scroll_offset() const
   {

      return {};

   }


   int_size Widget::get_accumulated_scroll_offset() const
   {

      auto offsetScroll = get_scroll_offset();

      if (m_pwidgetParent)
      {

         offsetScroll += m_pwidgetParent->get_accumulated_scroll_offset();

      }

      return offsetScroll;

   }


   ::int_rectangle Widget::interaction_rectangle() const
   {

      ::int_rectangle rectangle;

      auto absolutionPosition = absolute_position();

      rectangle.left() = absolutionPosition.x();
      rectangle.top() = absolutionPosition.y();
      rectangle.right() = rectangle.left() + m_size.cx();
      rectangle.bottom() = rectangle.top() + m_size.cy();

      return rectangle;

   }


   void Widget::set_need_redraw(const ::int_rectangle& rectangle, function < void() > function)
   {

      auto rectangleInteraction = rectangle;

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

         rectangleInteraction -= offsetScroll;

      }

      auto pscreen = screen();

      if (pscreen)
      {

         pscreen->m_bNeedRedraw = true;

         pscreen->m_puserinteraction->set_need_redraw({ rectangleInteraction }, nullptr, function);

      }

   }


   void Widget::post_redraw()
   {

      auto pscreen = screen();

      if (pscreen)
      {

         if (pscreen->m_bPreventRedraw)
         {

            return;

         }

         pscreen->m_bNeedRedraw = false;

         pscreen->m_puserinteraction->post_redraw();

      }

   }


   void Widget::fixed_placement(const ::int_rectangle& rectangle)
   {

      set_position(rectangle.top_left());

      set_fixed_size(rectangle.size());

   }


   void Widget::expose_fixed_size(const ::int_rectangle& rectangle, bool bRedraw)
   {

      auto positionOld = m_pos;

      auto rectangleOld = interaction_rectangle();

      auto positionNew = rectangle.top_left();

      set_position(positionNew);

      auto sizeNew = rectangle.size();

      set_fixed_size(sizeNew);

      set_need_layout();

      if (bRedraw)
      {

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


   bool Widget::contains(const int_point& p) const
   {

      ::pointer < Button > pbutton = this;

      if (pbutton)
      {

         informationf("Button contains");

      }

      //int iAddUp = 0;

      //auto pparent = parent();

      //if (pparent)
      //{

      //   auto pscrollPanel = dynamic_cast <VScrollPanel*>((Widget *) pparent->parent());

      //   if (pscrollPanel)
      //   {

      //      iAddUp = 12;

      //   }

      //}

      //sequence2_int d = p - m_pos;
      return p.x() >= 0 && p.y() >= 0 && p.x() < (m_size.cx()) && p.y() < m_size.cy();

   }


   ::pointer < TextBox > Widget::create_in_place_edit(const ::float_rectangle& rectangle, const ::scoped_string& scopedstr)
   {

      if (::is_null(m_pinplaceedit))
      {

         throw ::exception(error_wrong_state);

         return {};

      }

      if (m_pinplaceedit->m_pwidget)
      {

         m_pinplaceedit->m_pwidget->end_in_place_edit();

         m_pinplaceedit->m_pwidget.release();

      }

      auto ptextbox = ___new TextBox(this, scopedstr);

      ptextbox->m_bAutoDeleteOnFinishEditing = true;

      ptextbox->fixed_placement(rectangle);

      ptextbox->set_visible(true);

      ptextbox->set_editable(true);

      m_pinplaceedit->m_pwidget = ptextbox;

      return ptextbox;

   }


   bool Widget::end_in_place_edit()
   {

      auto pwidgetParent = m_pwidgetParent;

      if (!pwidgetParent)
      {

         return false;

      }

      if (pwidgetParent->m_pinplaceedit
         && pwidgetParent->m_pinplaceedit->m_pwidget == this)
      {

         pwidgetParent->m_pinplaceedit->m_pwidget.release();

      }

      pwidgetParent->erase_child(this);

      return true;

   }


   void Widget::end_all_in_place_edits()
   {


   }


   bool Widget::on_mouse_button_in_place_edit(in_place_edit* pinplaceedit, bool bDown, bool bDoubleClick)
   {

      if (::is_null(pinplaceedit))
      {

         end_all_in_place_edits();

         return false;

      }

      if (bDown)
      {
         
         pinplaceedit->m_iClickCount++;

         //information() << "LeftButtonDown on P connector : " << pconnector->m_iConnector;
         
         if(m_pinplaceedit
            && m_pinplaceedit == pinplaceedit
            && m_pinplaceedit->m_pwidget)
         {
            
            return false;
            
            //      {
            //
            //         if (m_pinplaceedit->m_pwidget)
            //         {
            //
            //            m_pinplaceedit->m_pwidget->end_in_place_edit();
            //
            //         }
            //
            //      }
            
         }
         else if (bDoubleClick || pinplaceedit->m_iClickCount == 2)
         {
            
            pinplaceedit->m_iClickCount = 0;

            auto rectangleEdit = pinplaceedit->get_edit_rectangle(this);

            if (rectangleEdit)
            {

               //r += layerp_pos;

//                        r += m_xyLayerViewerTranslate;

               auto strName = pinplaceedit->get_name_for_editing();

               auto pedit = create_in_place_edit(rectangleEdit, strName);

               on_before_in_place_edit(pinplaceedit);

               pedit->m_callback = [pinplaceedit](auto str)
                  {

                     pinplaceedit->set_edit_payload(str);

                     pinplaceedit->set_need_update();

                     pinplaceedit->m_pwidget->end_in_place_edit();

                     return true;

                  };

               //pedit->m_callbackEndEdit = [pproject]()
               //   {

               //      pproject->m_iPEdit = -1;
               //      pproject->m_iPClick = -1;
               //      pproject->m_iPClickCount = -1;

               //   };

               pedit->m_callbackOnEdit = [this]()
                  {

                     screen()->m_puserinteraction->set_need_redraw();

                     screen()->m_puserinteraction->post_redraw();

                  };

               pedit->start_in_place_edit();

            }

         }
         else if (pinplaceedit->m_iClickCount == 1 || pinplaceedit != m_pinplaceedit)
         {
            
            end_all_in_place_edits();

            m_pinplaceedit = pinplaceedit;
            
            pinplaceedit->m_iClickCount = 1;

            pinplaceedit->set_need_update();
            
         }
//         else if (pinplaceedit->m_iClickCount > 2)
//         {
//
//            end_all_in_place_edits();
//            
//            pinplaceedit->m_iClickCount = 0;
//
//         }

         return true;

      }
      else
      {

         return false;

      }

   }


   void Widget::on_before_in_place_edit(in_place_edit* pinplaceedit)
   {

   }


} // namespace nanoui



