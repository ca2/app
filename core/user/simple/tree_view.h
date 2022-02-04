#pragma once


class CLASS_DECL_CORE simple_tree_view :
   virtual public ::user::show < ::user::tree >
{
public:


   simple_tree_view();
   virtual ~simple_tree_view();

   void install_message_routing(::channel * pchannel) override;


   DECLARE_MESSAGE_HANDLER(on_message_create);

   virtual void handle(::topic * psubject, ::context * pcontext) override;


   void assert_valid() const override;
   void dump(dump_context & dumpcontext) const override;


};
