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


      __pointer(tab_drop_target_window)             m_pdroptargetwindow;
      ::user::impact_data *                  m_pimpactdata;
      ::user::impact_data *                  m_pimpactdataOld;
      ::user::impact_creator *               m_pviewcreator;
      bool                                   m_bCloseDocumentIfNoTabs;



      tab_view();
      virtual ~tab_view();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      virtual void install_message_routing(::channel * pchannel) override;


      DECL_GEN_SIGNAL(_001OnMenuMessage);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnSetFocus);


      virtual void on_change_pane_count(::array < ::user::tab_pane * > array = ::array < ::user::tab_pane * >()) override;

      virtual void on_remove_child(::user::interaction* pinteraction) override;

      virtual void on_remove_place_holder_child(::user::interaction* pinteraction) override;

      virtual void on_hide_child(::user::interaction* pinteraction) override;

      virtual void on_hide_place_holder_child(::user::interaction* pinteraction) override;

      virtual id get_view_id() override;

      virtual ::user::interaction * get_view_uie() override;

      virtual ::user::impact_data * get_view_creator_data();

      virtual ::user::document * get_view_document() override;

      virtual void _000OnDraw1(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnDropTab(index iPane, e_position eposition) override;

      virtual ::user::interaction * _001GetTabWnd(::index iTab) override;

      virtual void route_command_message(::user::command * pcommand) override;

      virtual bool on_prepare_impact_data(::user::impact_data* pimpactdata) override;

      virtual void on_after_host_impact(::user::impact_data * pimpactdata) override;

      virtual void _001DropTargetWindowInitialize(::user::tab * pinterface) override;

      virtual void _001DropTargetWindowRelay(::user::tab * pinterface) override;

      virtual void _001DropTargetWindowFinalize(::user::tab * pinterface) override;

      virtual void rotate() override;

      virtual ::index create_tab_by_id(id id) override;

      virtual void _001OnShowTab(::user::tab * ptab) override;

      virtual void on_change_cur_sel() override;

      virtual void _001OnTabClick(::index iTab) override;

      virtual void update(::update * pupdate) override;

      virtual bool pre_create_window(::user::create_struct& cs) override;

      virtual void OnActivateView(bool bActivate, __pointer(impact) pActivateView, __pointer(impact) pDeactiveView) override;

      virtual void _001OnRemoveTab(class tab_pane * ptab) override;


   };



} // namespace user
