#include "framework.h"
#include "line_layout.h"
#include "acme/constant/message.h"
#include "aura/user/user/interaction_array.h"
#include "aura/message/user.h"


namespace user
{


   line_layout::line_layout()
   {

      m_bOnDraw = false;

      m_flagNonClient.erase(e_non_client_background);

      m_flagNonClient.erase(e_non_client_focus_rect);

   }


   line_layout::~line_layout()
   {

   }


   void line_layout::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &line_layout::on_message_create);
      MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &line_layout::on_message_destroy);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &line_layout::on_message_show_window);

   }


   void line_layout::on_message_show_window(::message::message * pmessage)
   {

      ::pointer<::message::show_window>pshowwindow(pmessage);

      if (pshowwindow->m_bShow)
      {

         information("Show\n");

      }
      else
      {

         information("Hide\n");

      }

   }



   void line_layout::on_message_create(::message::message * pmessage)
   {


   }


   void line_layout::on_message_destroy(::message::message * pmessage)
   {

   }


   void line_layout::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::interaction::handle(ptopic, pcontext);

   }


   void line_layout::_001OnNcClip(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void line_layout::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void line_layout::_001OnClip(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void line_layout::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void line_layout::on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_bExtendOnParent || get_parent()->is_frame_window() || get_parent()->is_impact())
      {

         extend_on_parent(pgraphics);

      }

   }


   bool line_layout::on_perform_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_puserinteractionpointeraChild && m_puserinteractionpointeraChild->has_interaction())
      {

         auto point = const_layout().sketch().origin();

         int iMaximumNormal = 0;

         for (auto & puserinteraction : m_puserinteractionpointeraChild->interactiona())
         {

            puserinteraction->set_position(point);

            iMaximumNormal = ::maximum(iMaximumNormal, puserinteraction->size(e_layout_sketch).get_normal_dimension(m_eorientation));

            point.set_dimension(m_eorientation,
               point.get_dimension(m_eorientation) +
               puserinteraction->size(e_layout_sketch).get_dimension(m_eorientation)
               + m_iPadding);

         }

         ::size_i32 size;

         size.set_orthogonal_dimension(m_eorientation, iMaximumNormal);

         size.set_dimension(m_eorientation, point.get_dimension(m_eorientation));

         set_size(size, ::user::e_layout_layout, pgraphics);

         return true;

      }

      return false;

   }


} // namespace user



