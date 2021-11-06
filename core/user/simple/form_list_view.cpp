#include "framework.h"
#include "core/user/simple/_simple.h"


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


bool simple_form_list_view::pre_create_window(::user::system * pusersystem) 
{

#ifdef WINDOWS_DESKTOP
   


#endif
   
   return ::user::impact::pre_create_window(pusersystem);

}


void simple_form_list_view::handle(::subject * psubject, ::context * pcontext)
{

   BASE::handle(psubject, pcontext);

}
