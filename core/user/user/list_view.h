#pragma once


namespace user
{

   class CLASS_DECL_CORE list_view:
      virtual public ::user::show < ::user::margin < ::user::list > >
   {
   public:


      using BASE_VIEW = ::user::show < ::user::margin < ::user::list > >;


      list_view();
      virtual ~list_view();


      virtual void install_message_routing(::channel * pchannel) override;


      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;

      virtual void _001OnSelectionChange() override;


   };


} // namespace user




