//  Created from impact_host.cpp by camilo on 2026-07-08 16:14 <3ThomasBorregaardSørensen!!
//
//  userex_impact_container.cpp
//  app_veriwell_musical_player
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 14/07/18.
//  Copyright (c) 2018 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#include "framework.h"
#include "impact_host.h"
#include "impact_host_host.h"
#include "pane_tab_impact.h"
#include "font_impact.h"
#include "acme/constant/user_message.h"
#include "acme/constant/simple_command.h"
#include "acme/platform/keep.h"
#include "acme/platform/system.h"
#include "acme/prototype/prototype/atom.h"
#include "apex/database/_binary_stream.h"
#include "apex/message/simple_command.h"
#include "acme/handler/request.h"
#include "berg/user/user/tab_pane.h"
#include "berg/user/user/document.h"
#include "berg/user/user/single_document_template.h"
#include "berg/user/simple/child_frame.h"
#include "core/user/user/user.h"
#include "core/platform/application.h"
#include "core/platform/session.h"


namespace userex
{


   impact_host_host::impact_host_host()
   {

      m_bWfiUpDownTarget = false;

      m_rectangleImpactHostRate.left = 0.1;
      m_rectangleImpactHostRate.top = 0.1;
      m_rectangleImpactHostRate.right = 0.8;
      m_rectangleImpactHostRate.bottom = 0.6;

   }


   impact_host_host ::~impact_host_host()
   {



   }


   bool impact_host_host::wfi_is_up_down_target()
   {

      return m_bWfiUpDownTarget;

   }


   void impact_host_host::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      //::user::place_holder::install_message_routing(pchannel);

   }


   ::userex::impact_host *impact_host_host::impact_host()
   {

      if (!m_pimpacthost)
      {

         m_pimpacthost = create_impact<::userex::impact_host>(this, "impact_host");
          
         update_impact_host_placement();

      }

      return m_pimpacthost;
   }


   bool impact_host_host::_001IsCompactMode()
   {

      return false;

   }


   void impact_host_host::toggle_impact(const ::atom & atomImpactId)
   {

      auto pimpacthost = impact_host();

      if (!pimpacthost)
      {

         throw ::exception(error_wrong_state);

      }

      pimpacthost->toggle_impact(atomImpactId);

   }


   void impact_host_host::show_impact(const ::atom &atomImpactId)
   {

      auto pimpacthost = impact_host();

      if (!pimpacthost)
      {

         throw ::exception(error_wrong_state);
      }

      pimpacthost->show_impact(atomImpactId);

   }


   void impact_host_host::hide_impact(const ::atom &atomImpactId)
   {

      auto pimpacthost = impact_host();

      if (!pimpacthost)
      {

         throw ::exception(error_wrong_state);
      }

      pimpacthost->hide_impact(atomImpactId);

   }


   bool impact_host_host::OnUpDownTargetAttach(::user::interaction *pupdown)
   {

      return false;

   }


   bool impact_host_host::OnUpDownTargetDetach(::user::interaction *pupdown)
   {
      
      return false; 
   
   }


   ::pointer<::user::impact> impact_host_host::get_hosted_impact(const ::atom & atomImpactId)
   {

      if (!m_pimpacthost)
      {

         return nullptr;

      }


      return m_pimpacthost->get_hosted_impact(atomImpactId);

   }


   void impact_host_host::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      return ::user::impact::route_command(pcommand, bRouteToKeyDescendant);

      // if (pcommand->m_bRet)
      //   return;

      //// then pump through parent
      //::pointer<::user::interaction> puiParent = get_parent();

      //if (puiParent != nullptr)
      //{

      //   puiParent->route_command(pcommand);

      //   if (pcommand->m_bRet)
      //   {

      //      return;
      //   }
      //}

   }

   void impact_host_host::on_user_impact_created(const ::atom & atomImpactId)
   {


   }


   void impact_host_host::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::impact::_001OnDraw(pgraphics);

   }


   void impact_host_host::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      update_impact_host_placement();

   }


   void impact_host_host::update_impact_host_placement()
   {

      if (m_pimpacthost.is_null())
      {

         return;

      }

      ::i32_rectangle rectangle = client2_rectangle();

      if (rectangle.is_empty())
      {

         return;

      }

      rectangle.left = (::i32)(rectangle.width() * m_rectangleImpactHostRate.left);
      rectangle.top = (::i32)(rectangle.height() * m_rectangleImpactHostRate.top);
      rectangle.right = (::i32)(rectangle.width() * m_rectangleImpactHostRate.right);
      rectangle.bottom = (::i32)(rectangle.height() * m_rectangleImpactHostRate.bottom);

      m_rectangleDebugImpactHost = rectangle;

      auto r = m_pimpacthost->client2_rectangle();

      m_pimpacthost->client_to_host()(r);

      host_to_client()(r);

      if (rectangle != r)
      {

         m_pimpacthost->place(rectangle);

         m_pimpacthost->set_need_perform_layout();

         m_pimpacthost->set_need_layout();

      }

   }


   ::user::interaction *impact_host_host::wfi_up_down_target_get_hosting_parent(const ::atom &atomImpactId)
   {

      if (!wfi_is_up_down_target())
      {

         throw ::exception(error_wrong_state);

      }

      return m_pimpacthost;

   }

   
} // namespace userex



