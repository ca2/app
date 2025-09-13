#include "framework.h"
#include "line_layout.h"
#include "acme/constant/user_message.h"
#include "acme/platform/node.h"
#include "aura/graphics/write_text/font.h"
#include "aura/user/user/interaction_array.h"
#include "aura/user/user/style.h"
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


   void line_layout::create_line_layout(::user::interaction* puserinteractionParent, enum_orientation eorientation)
   {

      m_eorientation = eorientation;

      create_child(puserinteractionParent);

      display();

      set_need_layout();

   }




   void line_layout::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &line_layout::on_message_create);
      USER_MESSAGE_LINK(::user::e_message_destroy, pchannel, this, &line_layout::on_message_destroy);
      USER_MESSAGE_LINK(::user::e_message_show_window, pchannel, this, &line_layout::on_message_show_window);

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

         information() << "Hide callstack : " << node()->get_call_stack_trace();

      }

   }



   void line_layout::on_message_create(::message::message * pmessage)
   {


   }


   void line_layout::on_message_destroy(::message::message * pmessage)
   {

   }


   void line_layout::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      ::user::interaction::handle(ptopic, phandlercontext);

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

      // if (m_bExtendOnParent || get_parent()->is_frame_window() || get_parent()->is_impact())
      // {
      //
      //    _extend_on_parent(pgraphics);
      //
      // }

   }


   bool line_layout::on_perform_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if (id() == "RedDotLogicsInternal_license_manager::user_form::line_layout")
      {

         information() << "RedDotLogicsInternal_license_manager::user_form::line_layout";

      }

      {

         //synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         //auto children = synchronized_get_children();

         
         //if (m_puserinteractionpointeraChild && m_puserinteractionpointeraChild->has_interaction())
         {

            if (id() == "RedDotLogicsInternal_license_manager::user_form::line_layout")
            {

               information() << "RedDotLogicsInternal_license_manager::user_form::line_layout";

            }

            ::int_point point;

            int iMaximumNormal = 0;

            bool bChanged = false;

            double dMaximumAscent = 0.;

            auto pstyle = get_style(pgraphics);

            for_user_interaction_children(puserinteraction, this)
            {

               if(!puserinteraction->is_this_visible(e_layout_sketch))
               {

                  continue;

               }

               auto sizeItem = puserinteraction->size(e_layout_sketch);

               iMaximumNormal = ::maximum(iMaximumNormal, sizeItem.get_normal_dimension(m_eorientation));

               auto dAscent = pstyle->get_font(puserinteraction, puserinteraction->m_eelementMain)->get_ascent(pgraphics);

               dMaximumAscent = ::maximum(dMaximumAscent, dAscent);

            }

            for_user_interaction_children(puserinteraction, this)
            {

               if(!puserinteraction->is_this_visible(e_layout_sketch))
               {

                  continue;

               }

               auto strType = ::type(puserinteraction).as_string();
               auto pszWndTxt = puserinteraction->get_window_text().c_str();

               auto sizeItem = puserinteraction->size(e_layout_sketch);

               if (m_ealignrelativeOrthogonal == e_align_relative_base_bottom_line)
               {

                  auto dAscent = puserinteraction->get_font(pstyle)->get_ascent(pgraphics);


                  point.set_orthogonal_dimension(m_eorientation,
                     (int) (dMaximumAscent - dAscent));

               }
               else if (m_ealignrelativeOrthogonal == e_align_relative_far)
               {
                
                  point.set_orthogonal_dimension(m_eorientation,
                     iMaximumNormal - sizeItem.get_normal_dimension(m_eorientation));

               }

               if (puserinteraction->set_position(point, e_layout_layout, pgraphics))
               {

                  bChanged = true;

               }
               
               point.set_dimension(m_eorientation,
                  point.get_dimension(m_eorientation) +
                  sizeItem.get_dimension(m_eorientation)
                  + m_iPadding);

               //synchronouslock.lock();

            }

            ::int_size size;

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



