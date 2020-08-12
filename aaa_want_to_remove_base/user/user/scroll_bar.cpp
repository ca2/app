#include "framework.h" 



namespace user
{


   scroll_bar::scroll_bar()
   {

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


   point scroll_bar::get_ascendant_viewport_offset()
   {

      if (GetParent() == nullptr)
      {

         return nullptr;

      }

      return GetParent()->get_ascendant_viewport_offset();

   }


   point scroll_bar::get_parent_viewport_offset()
   {

      return nullptr;

   }


   void scroll_bar::_001OnClip(::draw2d::graphics_pointer & pgraphics)
   {

      try
      {

         ::rect rectClip;

         ::aura::draw_context * pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();

         ::rect rectClient;

         bool bFirst = true;

         if (pdrawcontext != nullptr)
         {

            rectClient = pdrawcontext->m_rectWindow;

            _001ScreenToClient(rectClient);

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

               pinteraction->get_window_rect(rectClient);

               pinteraction->get_client_rect(rectFocus);

               rectFocus.offset(rectClient.top_left());

               _001ScreenToClient(rectFocus);

               rectFocus.bottom++;
               rectFocus.right++;

               pgraphics->IntersectClipRect(rectFocus);

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









