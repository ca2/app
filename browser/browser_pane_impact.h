#pragma once


namespace browser
{


   class CLASS_DECL_APP_BROWSER pane_impact :
      virtual public ::userex::pane_tab_impact,
      virtual public ::user::form_callback
   {
   public:


      ::user::split_impact *                            m_ptopviewLast;
      impact_base *                                     m_pimpactLast;
      impact *                                          m_pimpactLastBilbo;
      ::user::impact_data *                     m_pimpactdataTopic;
      string                                          m_strTopicTitle;


      ::user::document *                              m_pdocMenu;
      ::user::plain_edit_impact *                       m_prollfps;
      address_array < ::user::check_box * >           m_checkptraBilbo;


      pane_impact(::particle * pparticle);
      virtual ~pane_impact();


      void on_create_impact(::user::impact_data * pimpactdata);

      void install_message_routing(::channel * pchannel) override;

      void assert_ok() const override;

      void dump(dump_context & dumpcontext) const override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void handle(::topic * ptopic, ::context * pcontext);
      void on_change_cur_sel();

      virtual ::file::path prepare_menu_impact();

      virtual void handle(::topic * ptopic, ::context * pcontext) override;


      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

   };


} // namespace browser



