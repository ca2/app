#include "framework.h"
#include "core/user/simple/_simple.h"
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
   MESSAGE_LINK(e_message_create, pchannel, this, &simple_tree_view::on_message_create);

}


void simple_tree_view::handle(::subject * psubject, ::context * pcontext)
{

   ::user::impact::handle(psubject, pcontext);
   ::user::tree::handle(psubject, pcontext);

}



void simple_tree_view::assert_valid() const
{
   ::user::impact::assert_valid();
}

void simple_tree_view::dump(dump_context & dumpcontext) const
{
   ::user::impact::dump(dumpcontext);
}



void simple_tree_view::on_message_create(::message::message * pmessage)
{

   __pointer(::message::create) pcreate(pmessage);

   pcreate->previous();


}



