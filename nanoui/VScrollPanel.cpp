/*
    src/vscrollpanel.cpp -- Adds a vertical scrollbar around a pwidget
    that is too big to fit into a certain area

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "VScrollPanel.h"
#include "Screen.h"
#include "aura/user/user/interaction.h"
#include "aura/windowing/windowing.h"
#include "nano2d/context.h"


namespace nanoui
{


   VScrollPanel::VScrollPanel(Widget* parent)
      : Widget(parent), m_fTotalHeight(0.f),
      m_fScroll(0.f), m_update_layout(false)
   {

   }


   float VScrollPanel::y_coordinate_vertical_scroll(int y)
   {

      float fTrackBarHeight = get_track_bar_height();

      float yMin = fTrackBarHeight / 2.f;

      float yMax = m_size.cy() - fTrackBarHeight / 2.f;

      float yRange = yMax - yMin;

      float clippedY = ::minimum_maximum((float)y, yMin, yMax);

      float fScroll = (clippedY - yMin) / yRange;

      return fScroll;


   }


   void VScrollPanel::perform_layout(::nano2d::context* pcontext, bool bRecalcTextSize)
   {

      ///Widget::perform_layout(pcontext);

      if (m_children.empty())
      {

         return;

      }

      if (m_children.size() > 1)
      {

         throw std::runtime_error("VScrollPanel should have one pwidgetChild.");

      }

      Widget* pwidgetPanel = m_children[0];

      if (m_size.cx() > 0)
      {

         pwidgetPanel->m_size.cx() = m_size.cx() - 12;

      }

      auto size = pwidgetPanel->preferred_size(pcontext, bRecalcTextSize);

      m_fTotalHeight = (float)size.cy();


      pwidgetPanel->m_size = size;

      //if (m_fTotalHeight > pwidgetPanel->m_size.cy())
      //{

      //   m_fScroll = ::minimum_maximum(m_fScroll, 0.f, ;

      //}

      pwidgetPanel->perform_layout(pcontext, bRecalcTextSize);

   }


   size_i32 VScrollPanel::preferred_size(::nano2d::context* pcontext, bool bRecalcTextSize)
   {

      if (m_children.empty())
      {

         return { 0, 0 };

      }

      return m_children[0]->preferred_size(pcontext, bRecalcTextSize) + size_i32(12, 0);

   }


   bool VScrollPanel::mouse_motion_event(const point_i32& p, const size_i32& rel, bool bDown, const ::user::e_key& ekeyModifiers)
   {

      if (!m_children.empty()
         && m_fTotalHeight > m_size.cy()
         && bDown
         && m_bDrag)
      {

         float fScroll = y_coordinate_vertical_scroll(p.y());

         information("drag:point=" + as_string(p.y()) + ",rate=" + as_string(fScroll) + "\n");

         if (is_different(fScroll, m_fScroll, 0.00001))
         {

            m_fScroll = fScroll;

            m_update_layout = true;

            set_need_redraw();

            post_redraw();

         }

         return true;

      }

      return Widget::mouse_motion_event(p, rel, bDown, ekeyModifiers);

   }


   bool VScrollPanel::mouse_button_event(const point_i32& p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key& ekeyModifiers)
   {

      if (Widget::mouse_button_event(p, emouse, down, bDoubleClick, ekeyModifiers))
      {

         return true;

      }

      if (down
         && emouse == ::user::e_mouse_left_button
         && !m_children.empty() 
         && m_fTotalHeight > m_size.cy() 
         && p.x() > m_pos.x() + m_size.cx() - 13 
         && p.x() < m_pos.x() + m_size.cx() - 4)
      {

         m_bDrag = true;

         screen()->m_puserinteraction->set_mouse_capture();

         float fScroll = y_coordinate_vertical_scroll(p.y());

         if (is_different(fScroll, m_fScroll, 0.00001))
         {

            m_fScroll = fScroll;

            m_update_layout = true;

            set_need_redraw();

         }

         return true;

      }
      else if (m_bDrag && !down)
      {

         m_bDrag = false;

         screen()->m_puserinteraction->windowing()->release_mouse_capture();

      }

      return false;

   }


   bool VScrollPanel::scroll_event(const point_i32& p, const size_f32& rel)
   {

      if (!m_children.empty() && m_fTotalHeight > m_size.cy())
      {

         float fScroll = y_coordinate_vertical_scroll(p.y());

         if (is_different(fScroll, m_fScroll, 0.00001))
         {

            m_fScroll = fScroll;

            auto pwidgetChild = m_children[0];

            auto old_pos = pwidgetChild->position();

            auto offsetScroll = get_scroll_offset();

            pwidgetChild->set_position(offsetScroll);

            auto new_pos = pwidgetChild->position();

            m_update_layout = true;

            set_need_redraw();

            post_redraw();

            pwidgetChild->mouse_motion_event(p - m_pos, old_pos - new_pos, true, ::user::e_key_none);

         }

         return true;

      }
      else
      {

         return Widget::scroll_event(p, rel);

      }

   }


   float VScrollPanel::get_track_bar_height() const
   {

      float fTrackBarHeight = height() * ::minimum(1.f, height() / (float)m_fTotalHeight);

      return fTrackBarHeight;

   }


   size_i32 VScrollPanel::get_scroll_offset() const
   {

      int yOffset;

      if (m_fTotalHeight <= m_size.cy())
      {

         yOffset = 0;

      }
      else
      {

         yOffset = (int) (- m_fScroll * (m_fTotalHeight - m_size.cy()));

      }

      return { 0, yOffset };

   }


   void VScrollPanel::draw(::nano2d::context* pcontext)
   {

      if (m_children.empty())
         return;

      Widget* pwidgetPanel = m_children[0];
      //m_child_preferred_height = pwidgetChild->preferred_size(pcontext).y();
      float fTrackBarHeight = get_track_bar_height();
      //int yoffset = 0;
      //if (m_child_preferred_height > m_size.cy())
        // yoffset = (int)get_y_offset(m_scroll);
      //pwidgetChild->set_position(sequence2_i32(0, yoffset));

      if (m_update_layout)
      {

         m_update_layout = false;

         //pwidgetChild->m_iHoverCandidateChildStart = -1;
         //pwidgetChild->m_iHoverCandidateChildEnd = -1;

         auto size = pwidgetPanel->preferred_size(pcontext, false);

         m_fTotalHeight = (float)size.cy();

         pwidgetPanel->perform_layout(pcontext, false);

      }


      {
         ::nano2d::guard guard(pcontext);
         //pcontext->save();

//         float y = (float)m_pos.y();

         auto offsetScroll = get_scroll_offset();

         pcontext->translate((float)offsetScroll.cx(), (float)offsetScroll.cy());

         pcontext->intersect_scissor((float)-offsetScroll.cx(), (float)-offsetScroll.cy(), (float)m_size.cx(), (float)m_size.cy());

         //pcontext->intersect_scissor(0.f, 0.f, (float)m_size.cx(), (float)m_size.cy());

         if (pwidgetPanel->visible())
         {

            pwidgetPanel->draw(pcontext);

         }

         //  pcontext->restore();

      }



      if (m_fTotalHeight <= m_size.cy())
      {

         return;

      }

      ::nano2d::paint paint = pcontext->box_gradient(
         (float)m_pos.x() + m_size.cx() - 12 + 1, (float)m_pos.y() + 4 + 1, 8,
         (float)m_size.cy() - 8, 3.f, 4.f, ::color::color(0, 32), ::color::color(0, 92));
      pcontext->begin_path();
      pcontext->rounded_rectangle(m_pos.x() + m_size.cx() - 12.f, m_pos.y() + 4.f, 8.f,
         m_size.cy() - 8.f, 3.f);
      pcontext->fill_paint(paint);
      pcontext->fill();

      paint = pcontext->box_gradient(
         m_pos.x() + m_size.cx() - 12.f - 1.f,
         m_pos.y() + 4.f + (m_size.cy() - 8.f - fTrackBarHeight) * m_fScroll - 1.f, 8.f, (float)fTrackBarHeight,
         3.f, 4.f, ::color::color(220, 100), ::color::color(128, 100));

      pcontext->begin_path();

      pcontext->rounded_rectangle(m_pos.x() + m_size.cx() - 12.f + 1.f,
         m_pos.y() + 4.f + 1.f + (m_size.cy() - 8.f - fTrackBarHeight) * m_fScroll, 8.f - 2.f,
         fTrackBarHeight - 2.f, 2.f);

      pcontext->fill_paint(paint);

      pcontext->fill();



   }


} // namespace nanoui



