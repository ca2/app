#include "framework.h"
#include "line_layout.h"
#include "acme/constant/message.h"
#include "acme/platform/node.h"
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

         information() << "Show";

      }
      else
      {

         information() << "Hide callstack : " << acmenode()->get_call_stack_trace();

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

         _extend_on_parent(pgraphics);

      }

   }


   bool line_layout::on_perform_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_atom == "RedDotLogicsInternal_license_manager::user_form::line_layout")
      {

         information() << "RedDotLogicsInternal_license_manager::user_form::line_layout";

      }

      {

         //synchronous_lock synchronouslock(this->synchronization());

         auto children = synchronized_get_children();

         //if (m_puserinteractionpointeraChild && m_puserinteractionpointeraChild->has_interaction())
         {

            if (m_atom == "RedDotLogicsInternal_license_manager::user_form::line_layout")
            {

               information() << "RedDotLogicsInternal_license_manager::user_form::line_layout";

            }

            ::point_i32 point;

            int iMaximumNormal = 0;

            bool bChanged = false;

            for (auto & puserinteraction : children)
            {

               //synchronouslock.unlock();

               if (puserinteraction->set_position(point, e_layout_layout, pgraphics))
               {

                  bChanged = true;

               }
               
               auto sizeItem = puserinteraction->size(e_layout_sketch);

               iMaximumNormal = ::maximum(iMaximumNormal, sizeItem.get_normal_dimension(m_eorientation));

               point.set_dimension(m_eorientation,
                  point.get_dimension(m_eorientation) +
                  sizeItem.get_dimension(m_eorientation)
                  + m_iPadding);

               //synchronouslock.lock();

            }

            ::size_i32 size;

            size.set_orthogonal_dimension(m_eorientation, iMaximumNormal);

            size.set_dimension(m_eorientation, point.get_dimension(m_eorientation));

            if (set_size(size, ::user::e_layout_layout, pgraphics))
            {

               bChanged = true;

            }

            return bChanged;

         }

      }

      return false;

   }


} // namespace user



