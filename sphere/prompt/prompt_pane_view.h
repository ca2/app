#pragma once


namespace prompt
{


   class CLASS_DECL_SPHERE pane_view :
      virtual public ::userex::pane_tab_view,
      virtual public ::filemanager::callback,
      virtual public prompt::form_callback
   {
   public:


      


      pane_view(::object * pobject);
      virtual ~pane_view();


      void rotate() override;

      void on_create_impact(::user::impact_data * pimpactdata) override;
      void on_change_cur_sel() override;

      virtual void install_message_routing(::channel * pchannel) override;

      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;
      virtual bool pre_create_window(::user::system * pusersystem) override;


      void OnFileManagerOpenFile(::filemanager::data * pdata, ::file::item_array & itema);

      DECLARE_MESSAGE_HANDLER(_001OnMenuMessage);

      virtual void on_control_event(::user::control_event * pevent) override;

      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_size);
   };


} // namespace prompt



