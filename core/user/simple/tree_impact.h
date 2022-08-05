#pragma once


class CLASS_DECL_CORE simple_tree_impact :
   virtual public ::user::show < ::user::tree >
{
public:


   simple_tree_impact();
   virtual ~simple_tree_impact();

   void install_message_routing(::channel * pchannel) override;


   DECLARE_MESSAGE_HANDLER(on_message_create);

   virtual void handle(::topic * ptopic, ::context * pcontext) override;


   void assert_ok() const override;
   void dump(dump_context & dumpcontext) const override;


};
