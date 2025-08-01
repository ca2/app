#pragma once


#include "impact_host.h"
#include "tab.h"
#include "tab_callback.h"
#include "aura/user/user/form_callback.h"


namespace user
{


   class CLASS_DECL_BASE tab_impact :
      virtual public ::user::impact_host,
      virtual public ::user::tab,
      virtual public ::user::tab_callback,
      virtual public ::user::form_callback
   {
   public:


      ::pointer<tab_drop_target_window>         m_pdroptargetwindow;
      ::user::impact_data *                     m_pimpactdata;
      ::user::impact_data *                     m_pimpactdataOld;
      ::user::impact_creator *                  m_pviewcreator;
      bool                                      m_bCloseDocumentIfNoTabs;
      ::pointer<::user::impact>                 m_pimpactTopic;
      atom_map < ::pointer<::form_document >>   m_mapformdocument;
      atom_map < ::pointer<::user::handler_impact >>  m_maphandlerimpact;
      // ::pointer < options_impact >              m_poptionsimpact;
      ::pointer < options_impact_handler >      m_poptionsimpacthandlerContext;


      tab_impact();
      ~tab_impact() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;
      void destroy() override;

      void install_message_routing(::channel * pchannel) override;


      DECLARE_MESSAGE_HANDLER(_001OnMenuMessage);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_set_focus);

      DECLARE_MESSAGE_HANDLER(on_command_display_about);

      virtual void show_about_tab_pane();


      virtual bool add_impact(const ::scoped_string & scopedstrName, const ::atom & idImpact = nullptr, bool bVisible = true, bool bPermanent = false, ::user::place_holder * pholder = nullptr) override;
      virtual bool add_impact_with_icon(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrIcon, const ::atom & idImpact = nullptr, bool bVisible = true, bool bPermanent = false, ::user::place_holder * pholder = nullptr) override;


      void on_change_tab_count(::array < ::user::tab_pane * > array = ::array < ::user::tab_pane * >()) override;

      void on_erase_child(::user::interaction* pinteraction) override;

      void on_erase_place_holder_child(::user::interaction* pinteraction) override;

      void on_hide_child(::user::interaction* pinteraction) override;

      void on_hide_place_holder_child(::user::interaction* pinteraction) override;

      atom get_impact_id() override;

      virtual ::user::place_holder * place_holder_by_id(const ::atom & atom);

      ::user::interaction * get_impact_uie() override;

      virtual ::user::impact_data * get_impact_creator_data();

      ::user::document * get_impact_document() override;

      void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void _001OnDropTab(::collection::index iPane, enum_position eposition) override;

      ::user::interaction * _001GetTabWnd(::collection::index iTab) override;

      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;

      bool on_prepare_impact_data(::user::impact_data* pimpactdata) override;

      void on_after_host_impact(::user::impact_data * pimpactdata) override;

      void _001DropTargetWindowInitialize(::user::tab * pinterface) override;

      void _001DropTargetWindowRelay(::user::tab * pinterface) override;

      void _001DropTargetWindowFinalize(::user::tab * pinterface) override;

      void rotate() override;

      ::user::tab_pane * create_tab_by_id(const ::atom & idTab) override;
      
      void on_create_impact(::user::impact_data * pimpactdata) override;

      virtual void create_impact_menu(::user::impact_data * pimpactdata);

      void prepare_impact_menu(::user::menu * pmenu);

      void _001OnShowTab(::user::tab * ptab) override;

      void _on_change_cur_sel();

      void on_change_cur_sel() override;

      void on_after_change_cur_sel() override;

      void _001OnTabClick(::collection::index iTab) override;

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      bool pre_create_window(::user::system * pusersystem) override;

      void OnActivateImpact(bool bActivate, ::pointer<impact>pActivateImpact, ::pointer<impact>DeactiveImpact) override;

      void _001OnRemoveTab(class tab_pane * ptab) override;

      virtual void prepare_form(const ::atom & atom, ::form_document * pformdocument);
      void on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics) override;

   };


} // namespace user



