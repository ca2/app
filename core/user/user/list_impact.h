#pragma once


namespace user
{

   class CLASS_DECL_CORE list_impact:
      virtual public ::user::show < ::user::margin < ::user::list > >
   {
   public:


      using BASE_VIEW = ::user::show < ::user::margin < ::user::list > >;


      list_impact();
      virtual ~list_impact();


      void install_message_routing(::channel * pchannel) override;


      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      virtual void _001OnSelectionChange() override;


   };


} // namespace user




