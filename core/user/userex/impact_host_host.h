//  Created from impact_host.h by camilo on 2026-07-08 16:14 <3ThomasBorregaardSørensen!!
//
//  userex_impact_container.hpp
//  app_veriwell_musical_player
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 14/07/18.
//  Copyright (c) 2018 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//  at macOS High Sierra 10.13.6
//
#pragma once


#include "berg/user/user/impact.h"



namespace userex
{


   class impact_host;


   class CLASS_DECL_CORE impact_host_host : virtual public ::user::impact
      //;
   //;
   //,
      //virtual public ::user::place_holder
   {
   public:


      bool m_bWfiUpDownTarget;
      ::pointer<::userex::impact_host> m_pimpacthost;
      ::f64_rectangle m_rectangleImpactHostRate;
      atom_array m_idaHandledImpacts;

      ::i32_rectangle m_rectangleDebugImpactHost;

      impact_host_host();
      ~impact_host_host() override;


      void install_message_routing(::channel *pchannel) override;


      virtual ::userex::impact_host *impact_host();

      virtual bool _001IsCompactMode();

      virtual void toggle_impact(const ::atom &atomImpactId);
      virtual void show_impact(const ::atom &atomImpactId);
      virtual void hide_impact(const ::atom &atomImpactId);


      bool wfi_is_up_down_target() override;


      virtual bool OnUpDownTargetAttach(::user::interaction *pinteraction);
      virtual bool OnUpDownTargetDetach(::user::interaction *pinteraction);


      virtual ::pointer<::user::impact> get_hosted_impact(const ::atom &atomImpactId);

      virtual void on_user_impact_created(const ::atom &atomImpactId);


      void route_command(::message::command *pcommand, bool bRouteToKeyDescendant) override;


      void _001OnDraw(::draw2d::graphics_pointer &pgraphics) override;


      void on_layout(::draw2d::graphics_pointer &pgraphics);

      void update_impact_host_placement();


      ::user::interaction *wfi_up_down_target_get_hosting_parent(const ::atom &atomImpactId) override;

   };


} // namespace userex


