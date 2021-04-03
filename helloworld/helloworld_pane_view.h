#pragma once


namespace helloworld
{


   class CLASS_DECL_APP_HELLOWORLD pane_view :
      virtual public ::userex::pane_tab_view,
      virtual public ::user::form_callback
   {
   public:


      ::user::split_view *                            m_ptopviewLast;
      impact_base *                                     m_pviewLast;
      view *                                          m_pviewLastBilbo;
      ::user::impact_data *                     m_pviewdataTopic;
      string                                          m_strTopicTitle;


      __pointer(::user::document)                            m_pdocMenu;
      ::calculator::plain_edit_view *                 m_prollfps;
      array < ::user::check_box * >                   m_checkptraBilbo;


      pane_view(::object * pobject);
      virtual ~pane_view();


      void on_create_impact(::user::impact_data * pimpactdata);

      virtual void install_message_routing(::channel * pchannel);

      virtual void assert_valid() const;

      virtual void dump(dump_context & dumpcontext) const;

      DECL_GEN_SIGNAL(on_message_create);
      void on_control_event(::user::control_event * pevent);
      void on_change_cur_sel();

      virtual ::file::path prepare_menu_view();

      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;


      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

   };


} // namespace helloworld













