#pragma once


namespace app_core_build
{


   class CLASS_DECL_APP_CORE_BUILD pane_view :
      virtual public ::application_consumer < application, ::userex::pane_tab_view, ::user::form_callback >
   {
   public:


      ::user::split_view *                            m_ptopviewLast;
      ::user::impact_data *                           m_pviewdataTopic;
      string                                          m_strTopicTitle;


      pane_view();
      ~pane_view() override;


      void on_create_impact(::user::impact_data * pimpactdata) override;

      void install_message_routing(::channel * pchannel) override;

      void assert_ok() const override;

      void dump(dump_context & dumpcontext) const override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void handle(::topic * ptopic, ::context * pcontext) override;
      void on_change_cur_sel() override;


      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;



   };


} // namespace app_core_build



