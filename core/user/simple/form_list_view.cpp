#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/simple/_simple.h"
#endif


simple_form_list_view::simple_form_list_view()
{

}


simple_form_list_view::~simple_form_list_view()
{

}


void simple_form_list_view::install_message_routing(::channel * pchannel)
{
   BASE::install_message_routing(pchannel);
   //::user::impact::install_message_routing(pchannel);
   //::user::form_list::install_message_routing(pchannel);
}



void simple_form_list_view::assert_valid() const
{
   ::user::impact::assert_valid();
}

void simple_form_list_view::dump(dump_context & dumpcontext) const
{
   ::user::impact::dump(dumpcontext);
}

bool simple_form_list_view::pre_create_window(::user::create_struct& cs) 
{
   
   cs.style |= WS_CLIPCHILDREN;
   
   return ::user::impact::pre_create_window(cs);
}

void simple_form_list_view::update(::update * pupdate)
{

   BASE::update(pupdate);

}