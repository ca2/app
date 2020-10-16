#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


namespace user
{


   scroll_bar::scroll_bar()
   {

      m_bParentScroll = false;

      m_scrollinfo.nMin    = 0;
      m_scrollinfo.nMax    = 100;
      m_scrollinfo.nPage   = 10;
      m_scrollinfo.nPos    = 0;

   }


   scroll_bar::~scroll_bar()
   {

   }


   void scroll_bar::send_scroll_message(UINT nSBCode)
   {

      auto pscroll = __new(::message::scroll);

      pscroll->m_nSBCode = nSBCode;

      if(m_bTracking)
      {

         pscroll->m_nPos = m_scrollinfo.nTrackPos;

      }
      else
      {

         pscroll->m_nPos = m_scrollinfo.nPos;

      }

      if(m_eorientation == orientation_horizontal)
      {

         pscroll->m_id = WM_HSCROLL;

      }
      else
      {

         pscroll->m_id = WM_VSCROLL;

      }

      __pointer(::user::interaction) puiParent = GetParent();

      puiParent->send(pscroll);

   }


   bool scroll_bar::create_window(e_orientation eorientation, u32 uStyle, ::user::interaction * puiParent, ::id id)
   {

      m_eorientation = eorientation;

      return ::user::interaction::create_window(nullptr, nullptr, uStyle, puiParent, id);

   }


   point scroll_bar::get_ascendant_viewport_offset() const
   {

      if (GetParent() == nullptr)
      {

         return nullptr;

      }

      return GetParent()->get_ascendant_viewport_offset();

   }


   point scroll_bar::get_parent_viewport_offset() const
   {

      return nullptr;

   }


   bool scroll_bar::GetTrackRect(RECT* prect)
   {

      return false;

   }


   ::color scroll_bar::scrollbar_color_strong(::user::style* pstyle, ::user::e_element eelement)
   {

      if (*m_pitemCurrent == eelement || *m_pitemHover== eelement)
      {

         return ARGB(130, 190, 180, 250);

      }
      else
      {

         return ARGB(150, 150, 150, 150);

      }

   }


   ::color scroll_bar::scrollbar_color(::user::style * pstyle, ::user::e_element eelement)
   {

      if(*m_pitemCurrent == eelement || *m_pitemHover== eelement)
      {

         return ARGB(100, 190, 180, 250);

      }
      else
      {

         return ARGB(150, 150, 150, 150);

      }

   }


   ::color scroll_bar::scrollbar_border_color(::user::style* pstyle, ::user::e_element eelement)
   {

      if(*m_pitemCurrent == eelement || *m_pitemHover== eelement)
      {

         return ARGB(190, 180, 180, 180);

      }
      else
      {

         return ARGB(190, 160, 160, 160);

      }

   }


   ::color scroll_bar::scrollbar_lite_border_color(::user::style* pstyle, ::user::e_element eelement)
   {

      if(*m_pitemCurrent == eelement || *m_pitemHover== eelement)
      {

         return ARGB(190, 90, 110, 180);

      }
      else
      {

         return ARGB(190, 110, 110, 100);

      }

   }


   ::color scroll_bar::scrollbar_draw_color(::user::style* pstyle, ::user::e_element eelement)
   {

      if (*m_pitemCurrent == eelement || *m_pitemHover == eelement)
      {

         return ARGB(127, 90, 90, 90);

      }
      else
      {

         return ARGB(127, 65, 65, 65);

      }

   }


   void scroll_bar::_001OnClip(::draw2d::graphics_pointer & pgraphics)
   {

      try
      {
         return;
         ::rect rectClip;

         ::aura::draw_context * pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();

         ::rect rectClient;

         bool bFirst = true;

         if (pdrawcontext != nullptr)
         {

            rectClient = pdrawcontext->m_rectWindow;

            _001ScreenToClient(rectClient, layout_design);

            rectClient.bottom++;
            rectClient.right++;

            rectClip = rectClient;

            bFirst = false;

         }

         ::user::interaction * pinteraction = this;

         ::rect rectFocus;

         index i = 0;

         while (pinteraction != nullptr)
         {

            if (i != 1)
            {

               pinteraction->get_window_rect(rectClient, layout_design);

               pinteraction->get_client_rect(rectFocus);

               rectFocus.offset(rectClient.top_left());

               _001ScreenToClient(rectFocus, layout_design);

               rectFocus.bottom++;
               rectFocus.right++;

               pgraphics->intersect_clip(rectFocus);

            }

            i++;

            pinteraction = pinteraction->GetParent();

         }

      }
      catch (...)
      {

         __throw(::exception::exception("no more a window"));

      }

   }




} // namespace user









