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
//      string         m_strView;
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


      ::size                                    m_sizeTabbedFrame;
      string_map < __pointer(::user::document) >       m_mapdoc;
      string_map < simple_frame_window * >      m_mapframe;
      id_array                                  m_idaHandledViews;

      __pointer(::user::single_document_template)      m_ptemplateTab;

      impact_host();
      virtual ~impact_host();


      virtual void install_message_routing(::channel * pchannel) override;

      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;


      virtual __pointer(::userex::pane_tab_view) get_pane_tab_view();

      virtual bool _001IsCompactMode();

      virtual void _001OnView(::id idView);
      virtual void show_view(::id idView);
      virtual void hide_view(::id idView);
      virtual void toggle_view(::id idView);
      virtual void defer_show_view(::id idView);
      virtual __pointer(::user::impact) _001GetView(::id idView);
      virtual __pointer(::simple_frame_window) _001GetFrame(::id idView);
      virtual __pointer(::user::impact) _001DetachView(::id idView);
      virtual bool _001AttachView(::id idView);
      virtual void _001DefaultLayoutView(::id idView);
      virtual __pointer(::user::impact) get_view(::id idView);
      virtual __pointer(::user::document) get_doc(::id idView);
      virtual bool defer_create_view(::id idView, ::create * pcreate = nullptr);
      //virtual __pointer(::user::document) detach_doc(::id idView);
      //virtual bool attach(__pointer(::user::document) pdocument, ::id idView);
      //virtual bool toggle(__pointer(::user::document) pdocument, ::id idView);

      virtual bool OnUpDownTargetAttach(::user::interaction * pupdown) override;
      virtual bool OnUpDownTargetDetach(::user::interaction * pupdown) override;
      virtual bool tabfy(::user::interaction * pupdown);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      DECL_GEN_SIGNAL(_001OnCreate);

      virtual void on_command(::user::command * pcommand) override;
      virtual void on_simple_command(::message::simple_command * psimplecommand) override;

   };


} // namespace userex


