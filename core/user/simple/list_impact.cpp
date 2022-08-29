#include "framework.h"
#include "core/user/simple/list_impact.h"


simple_list_impact::simple_list_impact()
{

}


simple_list_impact::~simple_list_impact()
{

}


void simple_list_impact::install_message_routing(::channel * pchannel)
{
   
   BASE_TYPE::install_message_routing(pchannel);
   
}



void simple_list_impact::assert_ok() const
{

   ::user::impact::assert_ok();

}


void simple_list_impact::dump(dump_context & dumpcontext) const
{

   ::user::impact::dump(dumpcontext);

}



