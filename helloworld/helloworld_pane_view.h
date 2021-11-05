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
      impact *                                          m_pviewLastBilbo;
      ::user::impact_data *                     m_pviewdataTopic;
      string                                          m_strTopicTitle;


      __pointer(::user::document)                            m_pdocMenu;
      ::calculator::plain_edit_view *                 m_prollfps;
      array < ::user::check_box * >                   m_checkptraBilbo;


      pane_view(::object * pobject);
      virtual ~pane_view();


      void on_create_impact(::user::impact_data * pimpactdata);

      void install_message_routing(::channel * pchannel) override;

      void assert_valid() const override;

      void dump(dump_context & dumpcontext) const override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void handle(::subject * psubject, ::context * pcontext);
      void on_change_cur_sel();

      virtual ::file::path prepare_menu_view();

      virtual void handle(::subject * psubject, ::context * pcontext) override;


      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

   };


} // namespace helloworld













