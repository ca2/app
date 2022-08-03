#include "framework.h"
#include "core/user/simple/_simple.h"


simple_list_view::simple_list_view()
{

}


simple_list_view::~simple_list_view()
{

}


void simple_list_view::install_message_routing(::channel * pchannel)
{
   
   BASE_TYPE::install_message_routing(pchannel);
   
}



void simple_list_view::assert_ok() const
{

   ::user::impact::assert_ok();

}


void simple_list_view::dump(dump_context & dumpcontext) const
{

   ::user::impact::dump(dumpcontext);

}



