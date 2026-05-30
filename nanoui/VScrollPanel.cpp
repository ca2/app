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
#include "acme/constant/user_key.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/application.h"
#include "acme/platform/session.h"
#include "aura/user/user/interaction.h"
#include "acme/user/user/keyboard_state.h"
#include "aura/windowing/windowing.h"
#include "nano2d/context.h"


namespace nanoui
{


   VScrollPanel::VScrollPanel(Widget* parent)
      : Widget(parent), m_fTotalHeight(0.f),
      m_fScroll(0.f), m_update_layout(false)
   {

   }


   ::f32 VScrollPanel::y_coordinate_vertical_scroll(::i32 y)
   {

      ::f32 fTrackBarHeight = get_track_bar_height();

      ::f32 yMin = fTrackBarHeight / 2.f;

      ::f32 yMax = m_size.cy - fTrackBarHeight / 2.f;

      ::f32 yRange = yMax - yMin;

      ::f32 clippedY = ::minimum_maximum((::f32)y, yMin, yMax);

      ::f32 fScroll = (clippedY - yMin) / yRange;

      return fScroll;


   }


   void VScrollPanel::perform_layout(::nano2d::context * pcontext, bool bRecalcTextSize)
   {

      ///Widget::perform_layout(pcontext);

      if (m_children.empty())
      {

         return;

      }

      if (m_children.size() > 1)
      {

         throw ::exception(error_failed, "VScrollPanel should have one pwidgetChild.");

      }

      Widget* pwidgetPanel = m_children[0];

      auto sizePanel = pwidgetPanel->fixed_size();

      sizePanel = sizePanel.prefer_self_coordinate_if_positive(pwidgetPanel->m_size);

      auto size = pwidgetPanel->preferred_size(pcontext, bRecalcTextSize);

      m_fTotalHeight = (::f32)size.cy;


      pwidgetPanel->m_size.cy = size.cy;

      pwidgetPanel->m_size.cx = size.cx;

      if (sizePanel.cx + 12 > m_size.cx)
      {

         pwidgetPanel->m_size.cx = m_size.cx - 12;
      }

      // if (m_fTotalHeight > pwidgetPanel->m_size.cy)
      //{

      //   m_fScroll = ::minimum_maximum(m_fScroll, 0.f, ;

      //}

      pwidgetPanel->perform_layout(pcontext, bRecalcTextSize);

   }


   i32_size VScrollPanel::preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize)
   {

      if (m_children.empty())
      {

         return { 0, 0 };

      }

      return m_children[0]->preferred_size(pcontext, bRecalcTextSize) + i32_size(12, 0);

   }


   bool VScrollPanel::mouse_motion_event(const i32_point &point)
   {

      m_pointCurrentLocalCursor = point;

      if (!m_children.empty()
         && m_fTotalHeight > m_size.cy && is_left_button_pressed()
         && m_bDrag)
      {

         ::f32 fScroll = y_coordinate_vertical_scroll(point.y);

         information("drag:point=" + ::as_string(point.y) + ",rate=" + ::as_string(fScroll) + "\n");

         if (is_different(fScroll, m_fScroll, 0.00001))
         {

            m_fScroll = fScroll;

            m_update_layout = true;

            set_need_redraw();

            post_redraw();

         }

         return true;

      }

      return Widget::mouse_motion_event(point);

   }


   bool VScrollPanel::mouse_button_event(const i32_point & point, ::user::e_key euserkeyMouseButton, bool bDown, bool bDoubleClick)
   {

      m_pointCurrentLocalCursor = point;

      if (m_bEnabled && euserkeyMouseButton == ::user::e_key_left_button)
      {

         if (bDown && !m_children.empty() && m_fTotalHeight > m_size.cy && point.x > m_pos.x + m_size.cx - 13 &&
             point.x < m_pos.x + m_size.cx - 4)
         {

            m_bDrag = true;

            m_keystatePress = session();

            screen()->m_puserinteraction->set_mouse_capture();

            synchronous_lock lock(screen()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

            ::f32 fScroll = y_coordinate_vertical_scroll(point.y);

            if (is_different(fScroll, m_fScroll, 0.00001))
            {

               m_fScroll = fScroll;

               m_update_layout = true;

               lock.unlock();

               set_need_redraw();

               post_redraw();
            }

            return true;
         }
         else if (m_bDrag && !bDown)
         {

            m_keystatePress = session();

            m_bDrag = false;

            screen()->m_puserinteraction->defer_release_mouse_capture();

         }

      }

      return Widget::mouse_button_event(point, euserkeyMouseButton, bDown, bDoubleClick);

   }


   bool VScrollPanel::scroll_event(const i32_point & point, const ::f32_size& rel)
   {

      m_pointCurrentLocalCursor = point;

      if (!m_children.empty() && m_fTotalHeight > m_size.cy)
      {

         auto pagePercent = (::f64)m_size.cy / m_fTotalHeight;

         auto wheelScrollUnit = -1.0;

         auto wheelScrollPercent = 0.06;

         auto y = rel.cy;

         auto addPercent = pagePercent * wheelScrollPercent * y / wheelScrollUnit;

         screen()->application()->fork([this, point, addPercent]()
               {

                  auto addUp = addPercent;

                  auto timeDelay = 40_ms;

                  for (::i32 i = 0; i < 4; i++)
                  {

                     {

                        synchronous_lock lock(screen()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

                        auto fScroll = minimum_maximum(m_fScroll + addUp, 0., 1.);

                        ::i32 iRel = (::i32)((fScroll - m_fScroll) * (m_fTotalHeight - m_size.cy));

                        if (iRel == 0)
                        {

                           break;

                        }

                        m_fScroll = (::f32) fScroll;

                        addUp /= 2.0;

                        m_update_layout = true;

                        mouse_motion_event(m_pointCurrentLocalCursor);

                        set_need_redraw();

                        post_redraw();

                     }

                     preempt(timeDelay);

                     timeDelay *= 1.25;

                  }

               });


            //auto pwidgetChild = m_children[0];

            //auto old_pos = pwidgetChild->position();

            //auto offsetScroll = get_scroll_offset();

            //pwidgetChild->set_position(offsetScroll);

            //auto new_pos = pwidgetChild->position();

            //m_update_layout = true;

            //set_need_redraw();

            //post_redraw();

            //pwidgetChild->mouse_motion_event(p - m_pos, old_pos - new_pos, true, ::user::e_key_none);

         //}

         return true;

      }
      else
      {

         return Widget::scroll_event(point, rel);

      }

   }


   ::f32 VScrollPanel::get_track_bar_height() const
   {

      ::f32 fTrackBarHeight = height() * ::minimum(1.f, height() / (::f32)m_fTotalHeight);

      return fTrackBarHeight;

   }


   i32_size VScrollPanel::get_scroll_offset() const
   {

      ::i32 yOffset;

      if (m_fTotalHeight <= m_size.cy)
      {

         yOffset = 0;

      }
      else
      {

         yOffset = (::i32) (- m_fScroll * (m_fTotalHeight - m_size.cy));

      }

      return { 0, yOffset };

   }


   void VScrollPanel::draw(::nano2d::context * pcontext)
   {

      if (m_children.empty())
         return;

      Widget* pwidgetPanel = m_children[0];
      //m_child_preferred_height = pwidgetChild->preferred_size(pcontext).y;
      ::f32 fTrackBarHeight = get_track_bar_height();
      //::i32 yoffset = 0;
      //if (m_child_preferred_height > m_size.cy)
        // yoffset = (::i32)get_y_offset(m_scroll);
      //pwidgetChild->set_position(i32_sequence2(0, yoffset));

      if (m_update_layout)
      {

         m_update_layout = false;

         //pwidgetChild->m_iHoverCandidateChildStart = -1;
         //pwidgetChild->m_iHoverCandidateChildEnd = -1;

         auto size = pwidgetPanel->preferred_size(pcontext, false);

         m_fTotalHeight = (::f32)size.cy;

         pwidgetPanel->perform_layout(pcontext, false);

      }


      {
         ::nano2d::guard guard(pcontext);
         //pcontext->save();

//         ::f32 y = (::f32)m_pos.y;

         auto offsetScroll = get_scroll_offset();

         pcontext->translate((::f32)offsetScroll.cx, (::f32)offsetScroll.cy);

         pcontext->intersect_scissor((::f32)-offsetScroll.cx, (::f32)-offsetScroll.cy, (::f32)m_size.cx, (::f32)m_size.cy);

         //pcontext->intersect_scissor(0.f, 0.f, (::f32)m_size.cx, (::f32)m_size.cy);

         if (pwidgetPanel->visible())
         {

            pwidgetPanel->draw(pcontext);

         }

         //  pcontext->restore();

      }



      if (m_fTotalHeight <= m_size.cy)
      {

         return;

      }

      ::nano2d::paint paint = pcontext->box_gradient(
         (::f32)m_pos.x + m_size.cx - 12 + 1, (::f32)m_pos.y + 4 + 1, 8,
         (::f32)m_size.cy - 8, 3.f, 4.f, ::color::color(0, 32), ::color::color(0, 92));
      pcontext->begin_path();
      pcontext->rounded_rectangle(m_pos.x + m_size.cx - 12.f, m_pos.y + 4.f, 8.f,
         m_size.cy - 8.f, 3.f);
      pcontext->fill_paint(paint);
      pcontext->fill();

      paint = pcontext->box_gradient(
         m_pos.x + m_size.cx - 12.f - 1.f,
         m_pos.y + 4.f + (m_size.cy - 8.f - fTrackBarHeight) * m_fScroll - 1.f, 8.f, (::f32)fTrackBarHeight,
         3.f, 4.f, ::color::color(220, 100), ::color::color(128, 100));

      pcontext->begin_path();

      pcontext->rounded_rectangle(m_pos.x + m_size.cx - 12.f + 1.f,
         m_pos.y + 4.f + 1.f + (m_size.cy - 8.f - fTrackBarHeight) * m_fScroll, 8.f - 2.f,
         fTrackBarHeight - 2.f, 2.f);

      pcontext->fill_paint(paint);

      pcontext->fill();



   }


} // namespace nanoui



