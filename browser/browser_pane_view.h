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
      view *                                          m_pviewLastBilbo;
      ::user::impact_data *                     m_pviewdataTopic;
      string                                          m_strTopicTitle;


      ::user::document *                              m_pdocMenu;
      ::user::plain_edit_view *                       m_prollfps;
      address_array < ::user::check_box * >           m_checkptraBilbo;


      pane_view(::object * pobject);
      virtual ~pane_view();


      void on_create_impact(::user::impact_data * pimpactdata);

      virtual void install_message_routing(::channel * pchannel);

      virtual void assert_valid() const;

      virtual void dump(dump_context & dumpcontext) const;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void on_control_event(::user::control_event * pevent);
      void on_change_cur_sel();

      virtual ::file::path prepare_menu_view();

      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;


      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

   };


} // namespace browser



