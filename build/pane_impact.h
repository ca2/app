#pragma once


namespace app_core_build
{


   class CLASS_DECL_APP_CORE_BUILD pane_impact :
      virtual public ::app_consumer < application, ::userex::pane_tab_impact, ::user::form_callback >
   {
   public:


      ::user::split_impact *                            m_ptopviewLast;
      ::user::impact_data *                           m_pimpactdataTopic;
      string                                          m_strTopicTitle;


      pane_impact();
      ~pane_impact() override;


      void on_create_impact(::user::impact_data * pimpactdata) override;

      void install_message_routing(::channel * pchannel) override;

      // void assert_ok() const override;

      // void dump(dump_context & dumpcontext) const override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void handle(::topic * ptopic, ::context * pcontext) override;
      void on_change_cur_sel() override;


      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;



   };


} // namespace app_core_build



