#include "framework.h"
#include "scroll_bar.h"
#include "acme/handler/item.h"
#include "acme/constant/message.h"
#include "aura/platform/draw_context2.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/message/user.h"


namespace user
{


   scroll_bar::scroll_bar()
   {

      //m_bParentScrollX = false;
      //m_bParentScrollY = false;

      m_scrollinfo.nMin    = 0;
      m_scrollinfo.nMax    = 100;
      m_scrollinfo.nPage   = 10;
      m_scrollinfo.nPos    = 0;

      m_econtroltype = e_control_type_scroll_bar;

   }


   scroll_bar::~scroll_bar()
   {

   }



   ::point_i32 scroll_bar::get_parent_accumulated_scroll(enum_layout elayout)
   {

      //auto pparent = get_parent();

      //if (::is_null(pparent))
      //{

         return ::user::interaction::get_parent_accumulated_scroll(elayout);

      //}

      //auto pparentParent = pparent->get_parent();

      //if (::is_null(pparentParent))
      //{

      //   return pparent->get_parent_accumulated_scroll(elayout);

      //}

      //return pparentParent->get_parent_accumulated_scroll(elayout);

   }



   void scroll_bar::post_scroll_message(enum_scroll_command ecommand)
   {

      auto pscroll = __new(::message::scroll);

      pscroll->m_ecommand = ecommand;

      if(m_bTracking)
      {

         pscroll->m_nPos = m_scrollinfo.nTrackPos;

      }
      else
      {

         pscroll->m_nPos = m_scrollinfo.nPos;

      }

      if(m_eorientation == e_orientation_horizontal)
      {

         pscroll->m_atom = e_message_hscroll;

      }
      else
      {

         pscroll->m_atom = e_message_vscroll;

      }

      ::pointer<::user::interaction>puiParent = get_parent();

      puiParent->post(pscroll);

   }


   //bool scroll_bar::create_interaction(enum_orientation eorientation, ::user::interaction * puiParent)
   //{

   //   m_eorientation = eorientation;

   //   return create_interaction(puiParent);

   //}


   point_i32 scroll_bar::get_ascendant_context_offset()
   {

      if (::is_null(get_parent()))
      {

         return {};

      }

      return get_parent()->get_ascendant_context_offset();

   }


   point_i32 scroll_bar::get_parent_context_offset()
   {

      return {};

   }


   ::status < ::rectangle_i32 > scroll_bar::get_track_rectangle(::draw2d::graphics_pointer & pgraphics)
   {

      return error_interface_only;

   }


   ::color::color scroll_bar::scrollbar_color_strong(::user::style* pstyle, ::enum_element eelement)
   {

      if ((m_pitemCurrent && m_pitemCurrent->m_eelement == eelement) || 
         (m_pitemHover && m_pitemHover->m_eelement == eelement))
      {

         return argb(130, 190, 180, 250);

      }
      else
      {

         return argb(150, 150, 150, 150);

      }

   }


   ::color::color scroll_bar::scrollbar_color(::user::style * pstyle, ::enum_element eelement)
   {

      if ((m_pitemCurrent && m_pitemCurrent->m_eelement == eelement) ||
         (m_pitemHover && m_pitemHover->m_eelement == eelement))
      {

         return argb(100, 190, 180, 250);

      }
      else
      {

         return argb(150, 150, 150, 150);

      }

   }


   ::color::color scroll_bar::scrollbar_border_color(::user::style* pstyle, ::enum_element eelement)
   {

      if ((m_pitemCurrent && m_pitemCurrent->m_eelement == eelement) ||
         (m_pitemHover && m_pitemHover->m_eelement == eelement))
      {

         return argb(190, 180, 180, 180);

      }
      else
      {

         return argb(190, 160, 160, 160);

      }

   }


   ::color::color scroll_bar::scrollbar_lite_border_color(::user::style* pstyle, ::enum_element eelement)
   {

      if ((m_pitemCurrent && m_pitemCurrent->m_eelement == eelement) ||
         (m_pitemHover && m_pitemHover->m_eelement == eelement))
      {

         return argb(190, 90, 110, 180);

      }
      else
      {

         return argb(190, 110, 110, 100);

      }

   }


   ::color::color scroll_bar::scrollbar_draw_color(::user::style* pstyle, ::enum_element eelement)
   {

      if ((m_pitemCurrent && m_pitemCurrent->m_eelement == eelement) ||
         (m_pitemHover && m_pitemHover->m_eelement == eelement))
      {

         return argb(127, 90, 90, 90);

      }
      else
      {

         return argb(127, 65, 65, 65);

      }

   }


   void scroll_bar::_001OnClip(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001OnClip(pgraphics);

      //try
      //{

      //   ::user::interaction * pinteraction = this;

      //   if (!m_bClipRectangle)
      //   {

      //      ::rectangle_i32 rectangleClient;

      //      ::index i = 0;

      //      while (pinteraction != nullptr)
      //      {

      //         rectangleClient = pinteraction->client_rectangle();

      //         pinteraction->client_to_host()(rectangleClient);

      //         host_to_client()(rectangleClient);

      //         if (i == 0)
      //         {

      //            m_rectangleClip = rectangleClient;

      //         }
      //         else
      //         {

      //            m_rectangleClip.intersect(m_rectangleClip, rectangleClient);

      //         }

      //         pinteraction = pinteraction->get_parent();

      //         i++;

      //      }

      //      m_bClipRectangle = true;

      //   }

      //   pgraphics->intersect_clip(m_rectangleClip);

      //}
      //catch (...)
      //{

      //   throw ::exception(error_exception, "no more a window");

      //}

   }



} // namespace user



