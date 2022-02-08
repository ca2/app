//
//  userex_view_container.hpp
//  app_veriwell_musical_player
//
//  Created by Camilo Sasuke Tsumanuma on 14/07/18.
//  Copyright © 2018 Camilo Sasuke Tsumanuma. All rights reserved.
//  at macOS High Sierra 10.13.6
//
#pragma once


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
////         type_attach_view,
////         type_detach_view,
////         type_attach_toggle_view,
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
      string_map < __pointer(::user::document) >       m_mapdoc;
      string_map < simple_frame_window * >      m_mapframe;
      id_array                                  m_idaHandledImpacts;

      __pointer(::user::single_document_template)      m_ptemplateTab;

      impact_host();
      virtual ~impact_host();


      inline ::core::application* get_application() const { return m_pcontext ? m_pcontext->m_pcoreapplication : nullptr; }
      inline ::core::session* get_session() const { return m_pcontext ? m_pcontext->m_pcoresession : nullptr; }
      inline ::core::system* get_system() const { return m_psystem ? m_psystem->m_pcoresystem : nullptr; }

      void install_message_routing(::channel * pchannel) override;

      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;

      virtual void handle(::topic * ptopic, ::context * pcontext) override;


      virtual __pointer(::userex::pane_tab_view) get_pane_tab_view();

      virtual bool _001IsCompactMode();

      virtual void _001OnImpact(::atom idImpact);
      virtual void show_view(::atom idImpact);
      virtual void hide_view(::atom idImpact);
      virtual void toggle_view(::atom idImpact);
      virtual void defer_show_view(::atom idImpact);
      virtual __pointer(::user::impact) _001GetImpact(::atom idImpact);
      virtual __pointer(::simple_frame_window) _001GetFrame(::atom idImpact);
      virtual __pointer(::user::impact) _001DetachImpact(::atom idImpact);
      virtual bool _001AttachImpact(::atom idImpact);
      virtual void _001DefaultLayoutImpact(::atom idImpact);
      virtual __pointer(::user::impact) get_view(::atom idImpact);
      virtual __pointer(::user::document) get_doc(::atom idImpact);
      virtual bool defer_create_view(::atom idImpact, ::create * pcreate = nullptr);
      //virtual __pointer(::user::document) detach_doc(::atom idImpact);
      //virtual bool attach(__pointer(::user::document) pdocument, ::atom idImpact);
      //virtual bool toggle(__pointer(::user::document) pdocument, ::atom idImpact);

      virtual bool OnUpDownTargetAttach(::user::interaction * pupdown) override;
      virtual bool OnUpDownTargetDetach(::user::interaction * pupdown) override;
      virtual bool tabfy(::user::interaction * pupdown);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);

      virtual void on_command(::message::command * pcommand) override;
      virtual void on_simple_command(::message::simple_command * psimplecommand) override;

   };


} // namespace userex


