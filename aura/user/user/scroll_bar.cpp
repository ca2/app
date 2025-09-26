#include "framework.h"
#include "scroll_bar.h"
#include "acme/constant/user_message.h"
#include "acme/handler/item.h"
#include "acme/user/user/content.h"
#include "aura/platform/draw_context2.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/message/user.h"


namespace user
{


   scroll_bar::scroll_bar()
   {

      //m_bParentScrollX = false;
      //m_bParentScrollY = false;

      //m_pscrolllayout->m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_dMinimum = 0.;
      //m_pscrolllayout->m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_dMaximum = 100.;
      //m_pscrolllayout->m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_dPage = 10.;
      //m_pscrolllayout->m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_dPosition = 0.;

      m_econtroltype = e_control_type_scroll_bar;

   }


   scroll_bar::~scroll_bar()
   {

   }



   ::double_point scroll_bar::get_parent_accumulated_scroll(enum_layout elayout)
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


   void scroll_bar::post_scroll_message(enum_scroll_command ecommand, double dPosition)
   {

      auto pscroll = øallocate ::message::scroll();

      pscroll->m_ecommand = ecommand;

      pscroll->m_dPosition = dPosition;

      //if(m_bTracking)
      //{

      //   pscroll->m_dPosition = m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_dTrackingPosition;

      //}
      //else
      //{

      //   pscroll->m_dPosition = m_pscrolllayout->m_scrollstatea[::user::e_layout_sketch].m_dPosition;

      //}

      if(m_eorientation == e_orientation_horizontal)
      {

         pscroll->m_eusermessage = ::user::e_message_scroll_x;

      }
      else
      {

         pscroll->m_eusermessage = ::user::e_message_scroll_y;

      }

      ::pointer<::user::interaction>puiParent = get_parent();

      puiParent->post_message(pscroll);

   }


   //bool scroll_bar::create_interaction(enum_orientation eorientation, ::user::interaction * puiParent)
   //{

   //   m_eorientation = eorientation;

   //   return create_interaction(puiParent);

   //}


   double_point scroll_bar::get_ascendant_context_offset()
   {

      if (::is_null(get_parent()))
      {

         return {};

      }

      return get_parent()->get_ascendant_context_offset();

   }


   double_point scroll_bar::get_parent_context_offset()
   {

      return {};

   }


   ::status < ::double_rectangle > scroll_bar::get_track_rectangle(::user::enum_layout elayout)
   {

      return error_interface_only;

   }


   ::color::color scroll_bar::scrollbar_color_strong(::user::style* pstyle, ::enum_element eelement)
   {

      if ((main_content().m_pitemCurrent && main_content().m_pitemCurrent->m_item.m_eelement == eelement) ||
         (m_pitemHover && m_pitemHover->m_item.m_eelement == eelement))
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

      if ((main_content().m_pitemCurrent && main_content().m_pitemCurrent->m_item.m_eelement == eelement) ||
         (m_pitemHover && m_pitemHover->m_item.m_eelement == eelement))
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

      if ((main_content().m_pitemCurrent && main_content().m_pitemCurrent->m_item.m_eelement == eelement) ||
         (m_pitemHover && m_pitemHover->m_item.m_eelement == eelement))
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

      if ((main_content().m_pitemCurrent && main_content().m_pitemCurrent->m_item.m_eelement == eelement) ||
         (m_pitemHover && m_pitemHover->m_item.m_eelement == eelement))
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

      if ((main_content().m_pitemCurrent && main_content().m_pitemCurrent->m_item.m_eelement == eelement) ||
         (m_pitemHover && m_pitemHover->m_item.m_eelement == eelement))
      {

         return argb(127, 90, 90, 90);

      }
      else
      {

         return argb(127, 65, 65, 65);

      }

   }


   double scroll_bar::scroll_bar_thickness(::user::enum_layout elayout)
   {

      return m_pscrolllayout->m_scrollstatea[elayout].m_dThickness;

   }


   void scroll_bar::_001OnClip(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001OnClip(pgraphics);

      //try
      //{

      //   ::user::interaction * pinteraction = this;

      //   if (!m_bClipRectangle)
      //   {

      //      ::int_rectangle rectangleX;

      //      ::collection::index i = 0;

      //      while (pinteraction != nullptr)
      //      {

      //         rectangleX = pinteraction->rectangle();

      //         pinteraction->client_to_host()(rectangleX);

      //         host_to_client()(rectangleX);

      //         if (i == 0)
      //         {

      //            m_rectangleClip = rectangleX;

      //         }
      //         else
      //         {

      //            m_rectangleClip.intersect(m_rectangleClip, rectangleX);

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



