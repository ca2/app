#pragma once


namespace user
{


   class tab_pane;
   class tab_drop_target_window;
   class single_document_template;


   class CLASS_DECL_BASE tab_view :
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


      tab_view();
      virtual ~tab_view();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      virtual void install_message_routing(::channel * pchannel) override;


      DECLARE_MESSAGE_HANDLER(_001OnMenuMessage);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(_001OnSetFocus);


      virtual void on_change_tab_count(::array < ::user::tab_pane * > array = ::array < ::user::tab_pane * >()) override;

      virtual void on_erase_child(::user::interaction* pinteraction) override;

      virtual void on_erase_place_holder_child(::user::interaction* pinteraction) override;

      virtual void on_hide_child(::user::interaction* pinteraction) override;

      virtual void on_hide_place_holder_child(::user::interaction* pinteraction) override;

      virtual id get_view_id() override;

      virtual ::user::interaction * get_view_uie() override;

      virtual ::user::impact_data * get_view_creator_data();

      virtual ::user::document * get_view_document() override;

      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnDropTab(index iPane, enum_position eposition) override;

      virtual ::user::interaction * _001GetTabWnd(::index iTab) override;

      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;

      virtual bool on_prepare_impact_data(::user::impact_data* pimpactdata) override;

      virtual void on_after_host_impact(::user::impact_data * pimpactdata) override;

      virtual void _001DropTargetWindowInitialize(::user::tab * pinterface) override;

      virtual void _001DropTargetWindowRelay(::user::tab * pinterface) override;

      virtual void _001DropTargetWindowFinalize(::user::tab * pinterface) override;

      virtual void rotate() override;

      virtual ::user::tab_pane * create_tab_by_id(id id) override;

      virtual void _001OnShowTab(::user::tab * ptab) override;

      virtual void on_change_cur_sel() override;

      virtual void _001OnTabClick(::index iTab) override;

      virtual void handle(::subject * psubject, ::context * pcontext) override;

      virtual bool pre_create_window(::user::system * pusersystem) override;

      virtual void OnActivateView(bool bActivate, __pointer(impact) pActivateView, __pointer(impact) pDeactiveView) override;

      virtual void _001OnRemoveTab(class tab_pane * ptab) override;


   };


} // namespace user



