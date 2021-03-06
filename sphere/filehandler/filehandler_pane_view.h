#pragma once


namespace filehandler
{


   class CLASS_DECL_SPHERE pane_view :
      virtual public ::userex::pane_tab_view
   {
   public:


            pane_view(::object * pobject);

      void rotate() override;

      void on_create_impact(::user::impact_data * pimpactdata) override;
      virtual void install_message_routing(::channel * pchannel) override;

      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;
      virtual bool pre_create_window(::user::system * pusersystem) override;

      DECLARE_MESSAGE_HANDLER(_001OnMenuMessage);
      virtual ~pane_view();

      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
   };


} // namespace filehandler


