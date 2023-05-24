/*
    nanoui/tabwidget.cpp -- Widget for organizing multiple
    sub-widgets into tabs

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "Layout.h"
#include "TabWidget.h"
#include "Screen.h"
#include "Popup.h"
#include "Button.h"
#include "acme/constant/_font_awesome.h"
#include "acme/handler/item.h"
#include "aura/user/user/interaction.h"
#include "nano2d/context.h"


namespace nanoui
{


   TabWidgetBase::TabWidgetBase(Widget* parent, const ::scoped_string& scopedstrFont)
      : Widget(parent), m_font(scopedstrFont), m_colorBackground(::color::color(0.f, 0.f)) 
   {

      m_iaTabOffsets.add(0);

   }


   void TabWidgetBase::erase_tab(::index iId) 
   {

      auto iIndex = tab_index(iId);

      bool close_active = iIndex == m_iActiveTab;

      m_straTabCaptions.erase_at(iIndex);

      m_iaTabIds.erase_at(iIndex);

      if (iIndex <= m_iActiveTab)
      {

         m_iActiveTab = ::maximum(0, m_iActiveTab - 1);

      }

      m_callbackLayout = [this](::nano2d::context* pcontext)
      {

         perform_layout(pcontext);

      };

      if (m_closecallback)
      {

         m_closecallback(iId);

      }

      if (close_active && m_callback) 
      {

         m_callback(selected_id());

         update_visibility();

      }

      //screen()->m_puserinteraction->set_need_layout();

      set_need_redraw();

      post_redraw();

   }


   ::index TabWidgetBase::insert_tab(::index iIndex, const ::scoped_string& scopedstrCaption) 
   {

      ::index iId = m_iTabCounter++;

      m_straTabCaptions.insert_at(iIndex, scopedstrCaption);

      m_iaTabIds.insert_at(iIndex, iId);

      //TabWidgetBase::perform_layout(screen()->::nano2d::_context());

      m_callbackLayout = [this](::nano2d::context* pcontext)
      {
         
         perform_layout(pcontext);

      };

      if (iIndex < m_iActiveTab)
      {
       
         m_iActiveTab++;

      }
      
      if (m_iaTabIds.size() == 1 && m_callback) 
      {

         m_iActiveTab = 0;

         m_callback(iId);

         update_visibility();

      }

      //screen()->m_puserinteraction->set_need_layout();

      set_need_redraw();

      post_redraw();

      return iId;

   }


   ::index TabWidgetBase::append_tab(const ::scoped_string& caption) 
   {

      return insert_tab(m_straTabCaptions.size(), caption);

   }


   ::index TabWidgetBase::tab_index(::index iId) const
   {

      for (::index i = 0; i < m_iaTabIds.size(); ++i) 
      {

         if (m_iaTabIds[i] == iId)
         {

            return i;

         }

      }

      throw ::exception(error_not_found, "TabWidgetBase::tab_index(): not found!");

   }


   void TabWidgetBase::update_visibility()
   {
      
      /* No-op */ 
   
   }


   void TabWidgetBase::perform_layout(::nano2d::context* pcontext, bool bRecalcTextSize) 
   {

      m_iaTabOffsets.clear();
      pcontext->font_face(m_font.c_str());
      pcontext->font_size(font_size());
      pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_top);

      m_iaTabOffsets.clear();
      int width = 0;
      float unused[4];
      for (const ::scoped_string& label : m_straTabCaptions) 
      {

         int label_width = (int)pcontext->text_bounds(0.f, 0.f, label.c_str(), unused);
         m_iaTabOffsets.add(width);
         width += label_width + 2 * m_ptheme->m_iHorizontalPaddingTabButton;
         if (m_bTabsCloseable)
            width += m_iCloseButtonWidth;
      }
      m_iaTabOffsets.add(width);

      pcontext->font_face("icons");
      m_iCloseButtonWidth = (int)
         pcontext->text_bounds(0.f, 0.f, get_utf8_character(e_font_awesome_times_circle).data(), unused);
   }

   vector2_i32 TabWidgetBase::preferred_size(::nano2d::context* pcontext, bool bRecalcTextSize)
   {
      pcontext->font_face(m_font.c_str());
      pcontext->font_size(font_size());
      pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_top);

      int width = 0;
      for (const ::scoped_string& label : m_straTabCaptions) {
         float unused[4];
         int label_width = (int)pcontext->text_bounds(0, 0, label.c_str(), unused);
         width += label_width + 2 * m_ptheme->m_iHorizontalPaddingTabButton;
         if (m_bTabsCloseable)
            width += m_iCloseButtonWidth;
      }

      return vector2_i32(width + 1,
         (int)(font_size() + 2.f * m_ptheme->m_iVerticalPaddingTabButton + 2.f * m_iPadding));
   }

   void TabWidgetBase::draw(::nano2d::context* pcontext) {
      if (m_callbackLayout)
      {
         m_callbackLayout(pcontext);

         m_callbackLayout = nullptr;
         //m_bPendingLayout = false;
         //TabWidgetBase::perform_layout(pcontext);


      }
      if (m_iaTabOffsets.size() != m_straTabCaptions.size() + 1)
         throw std::runtime_error("Must run TabWidget::perform_layout() after adding/removing tabs!");

      int tab_height = (int)(font_size() + 2.f * m_ptheme->m_iVerticalPaddingTabButton);

      if (m_colorBackground.fa() != 0.f) {
         pcontext->fill_color(m_colorBackground);
         pcontext->begin_path();
         pcontext->rounded_rectangle(m_pos.x()() + .5f, m_pos.y()() + .5f + tab_height, (float)m_size.x()(),
            m_size.y()() - tab_height - 2.f, (float)m_ptheme->m_iButtonCornerRadius);
         pcontext->fill();
      }

      Widget::draw(pcontext);

      ::nano2d::paint tab_background_color = pcontext->linear_gradient(
         (float)m_pos.x()(), m_pos.y()() + 1.f, (float)m_pos.x()(), (float)m_pos.y()() + tab_height,
         m_ptheme->m_colorButtonGradientTopPushed, m_ptheme->m_colorButtonGradientBottomPushed);

      pcontext->save();
      pcontext->intersect_scissor((float)m_pos.x()(), (float)m_pos.y()(), (float)m_size.x()(), (float)tab_height);
      pcontext->font_size(font_size());
      pcontext->text_align(::nano2d::e_align_left | ::nano2d::e_align_top);
      for (::index i = 0; i < m_straTabCaptions.size(); ++i) {
         int x_pos = m_pos.x()() + m_iaTabOffsets[i],
            y_pos = m_pos.y()(),
            width = m_iaTabOffsets[i + 1] - m_iaTabOffsets[i];

         if (i == (::index)m_iActiveTab) {
            pcontext->begin_path();
            pcontext->rounded_rectangle(x_pos + 0.5f, y_pos + 1.5f, (float)width,
               tab_height + 4.f, (float)m_ptheme->m_iButtonCornerRadius);
            pcontext->stroke_color(m_ptheme->m_colorBorderLight);
            pcontext->stroke();

            pcontext->begin_path();
            pcontext->rounded_rectangle(x_pos + 0.5f, y_pos + 0.5f, (float)width,
               tab_height + 4.f, (float)m_ptheme->m_iButtonCornerRadius);
            pcontext->stroke_color(m_ptheme->m_colorBorderDark);
            pcontext->stroke();
         }
         else {
            pcontext->begin_path();
            pcontext->rounded_rectangle(x_pos + 0.5f, y_pos + 1.5f, (float)width,
               tab_height + 4.f, (float)m_ptheme->m_iButtonCornerRadius);

            pcontext->fill_paint(tab_background_color);
            pcontext->fill();

            pcontext->stroke_color(m_ptheme->m_colorBorderDark);
            pcontext->stroke();
         }
         x_pos += m_ptheme->m_iHorizontalPaddingTabButton;
         y_pos += m_ptheme->m_iVerticalPaddingTabButton + 1;
         pcontext->fill_color(m_ptheme->m_colorText);
         pcontext->font_face(m_font.c_str());

         pcontext->text((float)x_pos, (float)y_pos, m_straTabCaptions[i]);

         if (m_bTabsCloseable) {
            x_pos = m_pos.x()() + m_iaTabOffsets[i + 1] -
               m_ptheme->m_iHorizontalPaddingTabButton - m_iCloseButtonWidth + 5;
            pcontext->font_face("icons");
            pcontext->fill_color(i == (size_t)m_iCloseIndexPushed ? m_ptheme->m_colorTextShadow
               : m_ptheme->m_colorText);
            bool highlight = m_iCloseIndex == (int)i;
            auto icon = highlight ? e_font_awesome_times_circle : e_font_awesome_times;
            float sizeFixed = font_size() * (highlight ? 1.f : .70f),
               offset_x = highlight ? 0.f : (sizeFixed * .40f),
               offset_y = highlight ? 0.f : (sizeFixed * .21f);
            pcontext->font_size(sizeFixed);
            pcontext->text(x_pos + offset_x, y_pos + offset_y + .5f, get_utf8_character(icon).data());
            pcontext->font_size(font_size());
         }

      }

      if (m_iTabDragIndex != -1 && m_iTabDragStart != m_iTabDragEnd)
      {

         auto x_pos = m_pos.x()() + m_iTabDragMinimum + m_iTabDragEnd - m_iTabDragStart;

         pcontext->begin_path();

         pcontext->rounded_rectangle(x_pos + 0.5f, m_pos.y()() + 1.5f, (float)(m_iTabDragMaximum - m_iTabDragMinimum),
            tab_height + 4.f, (float)m_ptheme->m_iButtonCornerRadius);

         pcontext->fill_color(::color::color(255, 255, 255, 30));

         pcontext->fill();

      }

      pcontext->restore();

      auto x0 = m_iaTabOffsets[m_iActiveTab];

      auto x1 = m_iaTabOffsets[m_iaTabOffsets.size() > 1 ? m_iActiveTab + 1 : 0];

      for (int i = 1; i >= 0; --i)
      {

         /* Top border */

         pcontext->begin_path();
         pcontext->move_to(m_pos.x()() + .5f, m_pos.y()() + tab_height + i + .5f);
         pcontext->line_to(m_pos.x()() + x0 + 1.0f, m_pos.y()() + tab_height + i + .5f);
         pcontext->move_to((float)(m_pos.x()() + x1), m_pos.y()() + tab_height + i + .5f);
         pcontext->line_to(m_pos.x()() + m_size.x()() + .5f, m_pos.y()() + tab_height + i + .5f);
         pcontext->stroke_width(1.0f);
         pcontext->stroke_color((i == 0) ? m_ptheme->m_colorBorderDark : m_ptheme->m_colorBorderLight);
         pcontext->stroke();

         /* Bottom + side borders */
         pcontext->save();
         pcontext->intersect_scissor((float)m_pos.x()(), (float)(m_pos.y()() + tab_height), (float)m_size.x()(), (float)m_size.y()());
         pcontext->begin_path();
         pcontext->rounded_rectangle(m_pos.x()() + .5f, m_pos.y()() + i + .5f, m_size.x()() - 1.f,
            m_size.y()() - 2.f, (float)m_ptheme->m_iButtonCornerRadius);
         pcontext->stroke();
         pcontext->restore();

      }

   }


   ::item_pointer TabWidgetBase::hit_test(const vector2_i32& p, bool test_vertical) const 
   {

      auto pitem = __new(::item);

      int tab_height = (int)font_size() + 2 * m_ptheme->m_iVerticalPaddingTabButton;

      if (test_vertical && (p.y()() <= m_pos.y()() || p.y()() > m_pos.y()() + tab_height))
      {

         pitem->m_eelement = e_element_none;

         return pitem;

      }

      int x = p.x()() - m_pos.x()();

      for (::index i = 0; i < m_iaTabOffsets.size() - 1; ++i) 
      {

         if (x >= m_iaTabOffsets[i] && x < m_iaTabOffsets[i + 1]) 
         {

            int r = m_iaTabOffsets[i + 1] - x;

            pitem->m_iItem = i;

            if (m_bTabsCloseable &&
               r < m_ptheme->m_iHorizontalPaddingTabButton + m_iCloseButtonWidth - 4 &&
               r > m_ptheme->m_iHorizontalPaddingTabButton - 4 &&
               p.y()() - m_pos.y()() > m_ptheme->m_iVerticalPaddingTabButton &&
               p.y()() - m_pos.y()() <= tab_height - m_ptheme->m_iVerticalPaddingTabButton)
            {

               pitem->m_eelement = e_element_close_button;
             
            }
            else
            {

               pitem->m_eelement = e_element_tab;

            }
            
            return pitem;

         }

      }

      pitem->m_eelement = e_element_none;

      return pitem;

   }


   bool TabWidgetBase::mouse_button_event(const vector2_i32& p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key& ekeyModifiers)
   {
      
      auto pitem = hit_test(p);

      bool bHandled = false;

      Screen* pscreen = screen();

      if (m_ppopup) 
      {

         m_ppopup->mouse_button_event(
            p - m_pos + absolute_position() - m_ppopup->absolute_position() + m_ppopup->position(), emouse, down, bDoubleClick, ekeyModifiers);

         pscreen->update_focus(this);

         pscreen->erase_child(m_ppopup);

         m_ppopup = nullptr;

         bHandled = true;

      }

      bool iDragInProgressIndex = m_iTabDragIndex != -1 && m_iTabDragStart != m_iTabDragEnd;

      if (m_popupcallback && emouse == ::user::e_mouse_right_button && down 
         && ::is_item_set_and_non_negative(pitem) &&
         !iDragInProgressIndex) 
      {

         m_ppopup = m_popupcallback(tab_id(pitem->m_iItem), pscreen);
         m_ppopup->set_position(p + vector2_i32(8, -6));
         m_ppopup->set_anchor_offset(8);
         m_ppopup->set_anchor_size(8);
         
         if (m_ppopup->layout() == nullptr)
            m_ppopup->set_layout(memory_new GroupLayout(5, 3));

         for (Widget* pwidgetChild : m_ppopup->children()) 
         {

            Button* b = dynamic_cast<Button*>(pwidgetChild);
            
            if (!b)
            {

               continue;

            }

            b->set_icon_position(Button::IconPosition::Right);

            b->set_flags(Button::ContextMenuButton);

         }

         m_ppopup->m_callbackLayout =
            [this](::nano2d::context* pcontext)
         {
            
            m_ppopup->set_size(m_ppopup->preferred_size(pcontext) + vector2_i32(40, 0));
            
            m_ppopup->perform_layout(pcontext);

         };

         set_need_layout();

         set_need_redraw();

         post_redraw();

         //m_bPendingSizing = true;
         //m_bPendingLayout = true;
         bHandled = true;

      }

      if (emouse == ::user::e_mouse_left_button && m_ppopup == nullptr)
      {

         if (::is_item_set_and_non_negative(pitem)) 
         {

            if (pitem->m_eelement == e_element_close_button && m_iTabDragIndex == -1) 
            {

               if (down) 
               {

                  m_iCloseIndexPushed = pitem->m_iItem;

               }
               else if (m_iCloseIndex == m_iCloseIndexPushed) 
               {

                  erase_tab(tab_id(pitem->m_iItem));

                  mouse_motion_event(p, vector2_i32(0), false, ::user::e_key_none);

               }

            }
            else
            {

               if (down) 
               {

                  bool bTabChanged = m_iActiveTab != pitem->m_iItem;

                  m_iActiveTab = pitem->m_iItem;

                  m_iTabDragIndex = m_bTabsDraggable ? pitem->m_iItem : -1;

                  m_iTabDragStart = m_iTabDragEnd = p.x()();

                  m_iTabDragMinimum = m_iaTabOffsets[pitem->m_iItem];

                  m_iTabDragMaximum = m_iaTabOffsets[pitem->m_iItem + 1];

                  m_iCloseIndexPushed = -1;

                  if (bTabChanged && m_callback) 
                  {

                     m_callback(selected_id());

                     update_visibility();

                  }

               }
               else if (m_iTabDragIndex != -1) 
               {

                  m_iTabDragIndex = -1;

                  mouse_motion_event(p, vector2_i32(0), false, ::user::e_key_none);

               }

            }

            bHandled = true;

         }

         if (!down) 
         {

            bHandled = m_iCloseIndexPushed != -1 || m_iTabDragIndex != -1;

            m_iCloseIndexPushed = -1;

            m_iTabDragIndex = -1;

         }

         bHandled = true;

      }

      bHandled |= Widget::mouse_button_event(p, emouse, down, bDoubleClick, ekeyModifiers);

      return bHandled;

   }


   bool TabWidgetBase::mouse_enter_event(const vector2_i32&/* p */, bool /* enter */, const ::user::e_key&)
   {

      if (m_bTabsCloseable && m_iCloseIndex >= 0)
      {
         m_iCloseIndex = -1;
         m_iCloseIndexPushed = -1;
         return true;
      }
      return false;

   }


   bool TabWidgetBase::mouse_motion_event(const vector2_i32& p, const vector2_i32& rel, bool bDown, const ::user::e_key& ekeyModifiers)
   {

      auto pitem = hit_test(p, false);

      if (m_iTabDragIndex != -1) 
      {

         m_iTabDragEnd = p.x()();

         if (::is_item_set_and_non_negative(pitem) && m_iTabDragIndex != pitem->m_iItem) 
         {

            auto i0 = ::minimum(m_iTabDragIndex, pitem->m_iItem);

            auto i1 = ::maximum(m_iTabDragIndex, pitem->m_iItem);

            auto mid = (m_iaTabOffsets[i0] + m_iaTabOffsets[i1 + 1]) / 2;

            if ((m_iTabDragIndex < pitem->m_iItem && p.x()() - m_pos.y()() > mid) ||
               (m_iTabDragIndex > pitem->m_iItem && p.x()() - m_pos.y()() < mid)) 
            {
            
               ::swap(m_straTabCaptions[pitem->m_iItem], m_straTabCaptions[m_iTabDragIndex]);

               ::swap(m_iaTabIds[pitem->m_iItem], m_iaTabIds[m_iTabDragIndex]);

               //TabWidgetBase::perform_layout(screen()->::nano2d::_context());
               m_callbackLayout = [this](::nano2d::context* pcontext)
               {

                  TabWidgetBase::perform_layout(pcontext);

               };

               m_iTabDragIndex = pitem->m_iItem;

               m_iActiveTab = pitem->m_iItem;

               set_need_layout();

               set_need_redraw();

               post_redraw();

            }

         }

         return true;

      }

      if (pitem->m_eelement != e_element_close_button)
      {

         pitem = nullptr;

      }

      if (pitem->m_iItem != m_iCloseIndex)
      {

         m_iCloseIndex = pitem->m_iItem;

         m_iCloseIndexPushed = -1;

         return true;

      }

      return Widget::mouse_motion_event(p, rel, bDown, ekeyModifiers);

   }


   TabWidget::TabWidget(Widget* parent, const ::scoped_string& font)
      : TabWidgetBase(parent, font) 
   { 
   

   }


   void TabWidget::perform_layout(::nano2d::context* pcontext, bool bRecalcTextSize) 
   {

      TabWidgetBase::perform_layout(pcontext, bRecalcTextSize);

      int tab_height = (int)font_size() + 2 * m_ptheme->m_iVerticalPaddingTabButton;

      for (Widget* pwidgetChild : m_children) 
      {

         pwidgetChild->set_position(vector2_i32(m_iPadding, m_iPadding + tab_height + 1));

         pwidgetChild->set_size(m_size - vector2_i32(2 * m_iPadding, 2 * m_iPadding + tab_height + 1));

         pwidgetChild->perform_layout(pcontext, bRecalcTextSize);

      }

   }

   void TabWidget::update_visibility() 
   {

      if (tab_count() == 0)
      {

         return;

      }

      for (Widget* pwidgetChild : m_children)
      {

         pwidgetChild->set_visible(false);

      }

      auto p = m_widgets.plookup(selected_id());

      if (::is_set(p))
      {

         p->m_element2->set_visible(true);

      }

   }

   vector2_i32 TabWidget::preferred_size(::nano2d::context* pcontext, bool bRecalcTextSize) 
   {

      auto sizeBase = TabWidgetBase::preferred_size(pcontext, bRecalcTextSize);

      vector2_i32 sizeContent;
         
      for (Widget* pwidgetChild : m_children)
      {

         sizeContent = sizeContent.maximum(pwidgetChild->preferred_size(pcontext, bRecalcTextSize));

      }

      return vector2_i32(
         ::maximum(sizeBase.x()(), sizeContent.x()() + 2 * m_iPadding),
         sizeBase.y()() + sizeContent.y()() + 2 * m_iPadding
      );

   }


   ::index TabWidget::insert_tab(::index iIndex, const ::scoped_string& caption, Widget* pwidget) 
   {

      auto iId = TabWidgetBase::insert_tab(iIndex, caption);

      m_widgets[iId] = pwidget;

      update_visibility();

      return iId;

   }


   ::index TabWidget::append_tab(const ::scoped_string& caption, Widget* pwidget) 
   {

      pwidget->set_visible(false);

      auto iId = TabWidgetBase::append_tab(caption);

      m_widgets[iId] = pwidget;

      update_visibility();

      return iId;

   }


   void TabWidget::erase_tab(::index iId) 
   {

      TabWidgetBase::erase_tab(iId);

      Widget* pwidget = m_widgets[iId];

      m_widgets.erase_item(iId);

      if (m_bEraseChildren)
      {

         erase_child(pwidget);

      }

   }


} // namespace nanoui



