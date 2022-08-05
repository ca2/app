#pragma once


namespace user
{


   class tab_pane;
   class tab_drop_target_window;
   class single_document_template;


   class CLASS_DECL_BASE tab_impact :
      virtual public ::user::impact_host,
      virtual public ::user::tab,
      virtual public ::user::tab_callback
   {
   public:


      __pointer(tab_drop_target_window)         m_pdroptargetwindow;
      ::user::impact_data *                     m_pimpactdata;
      ::user::impact_data *                     m_pimpactdataOld;
      ::user::impact_creator *                  m_pviewcreator;
      bool                                      m_bCloseDocumentIfNoTabs;
      //__pointer(::user::impact)                 m_pimpactTopic;


      tab_impact();
      ~tab_impact() override;


      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;


      void install_message_routing(::channel * pchannel) override;


      DECLARE_MESSAGE_HANDLER(_001OnMenuMessage);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_set_focus);


      virtual bool add_impact(const ::string & strName, const ::atom & idImpact = nullptr, bool bVisible = true, bool bPermanent = false, ::user::place_holder * pholder = nullptr) override;
      virtual bool add_impact_with_icon(const ::string & strName, const ::string & strIcon, const ::atom & idImpact = nullptr, bool bVisible = true, bool bPermanent = false, ::user::place_holder * pholder = nullptr) override;


      void on_change_tab_count(::array < ::user::tab_pane * > array = ::array < ::user::tab_pane * >()) override;

      void on_erase_child(::user::interaction* pinteraction) override;

      void on_erase_place_holder_child(::user::interaction* pinteraction) override;

      void on_hide_child(::user::interaction* pinteraction) override;

      void on_hide_place_holder_child(::user::interaction* pinteraction) override;

      atom get_impact_id() override;

      ::user::interaction * get_impact_uie() override;

      virtual ::user::impact_data * get_impact_creator_data();

      ::user::document * get_impact_document() override;

      void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void _001OnDropTab(index iPane, enum_position eposition) override;

      ::user::interaction * _001GetTabWnd(::index iTab) override;

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

      void _001OnTabClick(::index iTab) override;

      void handle(::topic * ptopic, ::context * pcontext) override;

      bool pre_create_window(::user::system * pusersystem) override;

      void OnActivateImpact(bool bActivate, __pointer(impact) pActivateImpact, __pointer(impact) pDeactiveImpact) override;

      void _001OnRemoveTab(class tab_pane * ptab) override;


   };


} // namespace user



