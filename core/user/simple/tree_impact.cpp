#include "framework.h"
#include "tree_impact.h"
#include "aura/message/user.h"


simple_tree_impact::simple_tree_impact()
{

}


simple_tree_impact::~simple_tree_impact()
{

}

void simple_tree_impact::install_message_routing(::channel * pchannel)
{

   ::user::impact::install_message_routing(pchannel);
   ::user::tree::install_message_routing(pchannel);
   MESSAGE_LINK(e_message_create, pchannel, this, &simple_tree_impact::on_message_create);

}


void simple_tree_impact::handle(::topic * ptopic, ::context * pcontext)
{

   ::user::impact::handle(ptopic, pcontext);
   ::user::tree::handle(ptopic, pcontext);

}



void simple_tree_impact::assert_ok() const
{
   ::user::impact::assert_ok();
}

void simple_tree_impact::dump(dump_context & dumpcontext) const
{
   ::user::impact::dump(dumpcontext);
}



void simple_tree_impact::on_message_create(::message::message * pmessage)
{

   ::pointer<::message::create>pcreate(pmessage);

   pcreate->previous();


}



