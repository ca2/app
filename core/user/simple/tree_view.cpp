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
   IGUI_MSG_LINK(WM_CREATE, pchannel, this, &simple_tree_view::_001OnCreate);

}


void simple_tree_view::update(::update * pupdate)
{

   ::user::impact::update(pupdate);
   ::user::tree::update(pupdate);

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

   SCAST_PTR(::message::create, pcreate, pmessage);

   pcreate->previous();


}



