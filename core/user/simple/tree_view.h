#pragma once


class CLASS_DECL_CORE simple_tree_view :
   virtual public ::user::show < ::user::tree >
{
public:


   simple_tree_view();
   virtual ~simple_tree_view();

   virtual void install_message_routing(::channel * pchannel) override;


   DECL_GEN_SIGNAL(on_message_create);

   virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;


   virtual void assert_valid() const override;
   virtual void dump(dump_context & dumpcontext) const override;


};
