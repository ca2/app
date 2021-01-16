#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/simple/_simple.h"
#endif
#include "_tree.h"


simple_tree_view::simple_tree_view()
{

}

simple_tree_view::~simple_tree_view()
{

}

void simple_tree_view::install_message_routing(::channel * pchannel)
{

   ::user::impact::install_message_routing(pchannel);
   ::user::tree::install_message_routing(pchannel);
   MESSAGE_LINK(e_message_create, pchannel, this, &simple_tree_view::_001OnCreate);

}


void simple_tree_view::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
{

   ::user::impact::on_subject(psubject, pcontext);
   ::user::tree::on_subject(psubject, pcontext);

}



void simple_tree_view::assert_valid() const
{
   ::user::impact::assert_valid();
}

void simple_tree_view::dump(dump_context & dumpcontext) const
{
   ::user::impact::dump(dumpcontext);
}



void simple_tree_view::_001OnCreate(::message::message * pmessage)
{

   __pointer(::message::create) pcreate(pmessage);

   pcreate->previous();


}



