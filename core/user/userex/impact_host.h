//
//  userex_impact_container.hpp
//  app_veriwell_musical_player
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 14/07/18.
//  Copyright © 2018 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//  at macOS High Sierra 10.13.6
//
#pragma once


#include "base/user/user/impact.h"


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


   class CLASS_DECL_CORE impact_host :
      virtual public ::user::impact
   {
   public:


      ::size_i32                                    m_sizeTabbedFrame;
      string_map < ::pointer<::user::document >>      m_mapdoc;
      string_map < simple_frame_window * >      m_mapframe;
      atom_array                                  m_idaHandledImpacts;

      ::pointer<::user::single_document_template>     m_ptemplateTab;

      impact_host();
      ~impact_host() override;


      ::core::application* get_app();
      ::core::session* get_session();
      ::core::system* get_system();

      void install_message_routing(::channel * pchannel) override;

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      void handle(::topic * ptopic, ::context * pcontext) override;


      virtual ::pointer<::userex::pane_tab_impact>get_pane_tab_impact();

      virtual bool _001IsCompactMode();

      virtual void _001OnImpact(::atom idImpact);
      virtual void show_impact(::atom idImpact);
      virtual void hide_impact(::atom idImpact);
      virtual void toggle_impact(::atom idImpact);
      virtual void defer_show_impact(::atom idImpact);
      virtual ::pointer<::user::impact>_001GetImpact(::atom idImpact);
      virtual ::pointer<::simple_frame_window>_001GetFrame(::atom idImpact);
      virtual ::pointer<::user::impact>_001DetachImpact(::atom idImpact);
      virtual bool _001AttachImpact(::atom idImpact);
      virtual void _001DefaultLayoutImpact(::atom idImpact);
      virtual ::pointer<::user::impact>get_impact(::atom idImpact);
      virtual ::pointer<::user::document>get_doc(::atom idImpact);
      virtual bool defer_create_impact(::atom idImpact, ::request * prequest = nullptr);
      //virtual ::pointer<::user::document>detach_doc(::atom idImpact);
      //virtual bool attach(::pointer<::user::document>pdocument, ::atom idImpact);
      //virtual bool toggle(::pointer<::user::document>pdocument, ::atom idImpact);

      virtual bool OnUpDownTargetAttach(::user::interaction * pupdown) override;
      virtual bool OnUpDownTargetDetach(::user::interaction * pupdown) override;
      virtual bool tabfy(::user::interaction * pupdown);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);

      virtual void on_command(::message::command * pcommand) override;
      virtual void on_simple_command(::message::simple_command * psimplecommand) override;

   };


} // namespace userex


