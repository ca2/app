#pragma once


namespace browser
{


   class CLASS_DECL_APP_BROWSER pane_view :
      virtual public ::userex::pane_tab_view,
      virtual public ::user::form_callback
   {
   public:


      ::user::split_view *                            m_ptopviewLast;
      impact_base *                                     m_pviewLast;
      impact *                                          m_pviewLastBilbo;
      ::user::impact_data *                     m_pviewdataTopic;
      string                                          m_strTopicTitle;


      ::user::document *                              m_pdocMenu;
      ::user::plain_edit_view *                       m_prollfps;
      address_array < ::user::check_box * >           m_checkptraBilbo;


      pane_view(::object * pobject);
      virtual ~pane_view();


      void on_create_impact(::user::impact_data * pimpactdata);

      void install_message_routing(::channel * pchannel) override;

      void assert_ok() const override;

      void dump(dump_context & dumpcontext) const override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void handle(::topic * ptopic, ::context * pcontext);
      void on_change_cur_sel();

      virtual ::file::path prepare_menu_view();

      virtual void handle(::topic * ptopic, ::context * pcontext) override;


      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

   };


} // namespace browser



