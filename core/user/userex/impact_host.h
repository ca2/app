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
#include "berg/user/user/place_holder.h"


namespace userex
{


//   class CLASS_DECL_CORE ::update :
//      public ::user::update
//   {
//   public:
//
//
//      enum enum_type
//      {
//
//         type_none,
////         type_attach_impact,
////         type_detach_impact,
////         type_attach_toggle_impact,
//
//      };
//
//
//      string         m_strImpact;
//      enum_type         m_etype;
//
//
//      ::update();
//      virtual ~::update();
//
//   };


   class impact_host_host;



   class CLASS_DECL_CORE impact_host :
      virtual public ::user::impact,
      virtual public ::user::place_holder
   {
   public:


      ::i32_size                                    m_sizeTabbedFrame;
      string_map_base < ::pointer<::user::document >>      m_mapdoc;
      string_map_base < simple_frame_window * >      m_mapframe;
      ::pointer<::userex::impact_host_host> m_pimpacthosthost;
      //::pointer<::user::single_document_template>     m_ptemplateTab;

      impact_host();
      ~impact_host() override;


      // ::core::application* get_app();
      // ::core::session* get_session();
      // ::core::system* get_system();

      void install_message_routing(::channel * pchannel) override;

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


      virtual ::pointer<::userex::pane_tab_impact>get_pane_tab_impact();

      virtual bool _001IsCompactMode();

      void _001OnDraw(::draw2d::graphics_pointer &pgraphics) override;

      virtual void _001OnImpact(const ::atom & atomImpactId);
      virtual void show_impact(const ::atom & atomImpactId);
      virtual void hide_impact(const ::atom & atomImpactId);
      virtual void toggle_impact(const ::atom & atomImpactId);
      virtual void defer_show_impact(const ::atom & atomImpactId);
      virtual ::pointer<::user::impact>_001GetImpact(const ::atom & atomImpactId);
      virtual ::pointer<::simple_frame_window>_001GetFrame(const ::atom & atomImpactId);
      virtual ::pointer<::user::impact>_001DetachImpact(const ::atom & atomImpactId);
      virtual bool _001AttachImpact(const ::atom & atomImpactId);
      virtual void _001DefaultLayoutImpact(const ::atom & atomImpactId);
      virtual ::pointer<::user::impact>get_hosted_impact(const ::atom & atomImpactId);
      virtual ::pointer<::user::document>get_doc(const ::atom & atomImpactId);
      virtual bool defer_create_impact(const ::atom & atomImpactId, ::request * prequest = nullptr);
      //virtual ::pointer<::user::document>detach_doc(const ::atom & atomImpactId);
      //virtual bool attach(::pointer<::user::document>pdocument, ::atom atomImpactId);
      //virtual bool toggle(::pointer<::user::document>pdocument, ::atom atomImpactId);

      virtual bool OnUpDownTargetAttach(::user::interaction * pupdown) override;
      virtual bool OnUpDownTargetDetach(::user::interaction * pupdown) override;
      virtual bool tabfy(::user::interaction * pupdown);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);

      void on_command(::message::command * pcommand) override;
      void on_simple_command(::message::simple_command * psimplecommand) override;
      void route_command(::message::command *pcommand, bool bRouteToKeyDescendant) override;

      ::user::interaction * wfi_up_down_target_get_hosting_parent(const ::atom &atomImpactId) override;

   };


} // namespace userex


