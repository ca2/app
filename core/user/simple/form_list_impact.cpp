#include "framework.h"
#include "form_list_impact.h"
#include "acme/handler/item.h"


simple_form_list_impact::simple_form_list_impact()
{

}


simple_form_list_impact::~simple_form_list_impact()
{

}


void simple_form_list_impact::install_message_routing(::channel * pchannel)
{
   BASE::install_message_routing(pchannel);
   //::user::impact::install_message_routing(pchannel);
   //::user::form_list::install_message_routing(pchannel);
}



//void simple_form_list_impact::assert_ok() const
//{
//   ::user::impact::assert_ok();
//}
//
//
//void simple_form_list_impact::dump(dump_context & dumpcontext) const
//{
//
//   ::user::impact::dump(dumpcontext);
//
//}


bool simple_form_list_impact::pre_create_window(::user::system * pusersystem) 
{

#ifdef WINDOWS_DESKTOP
   


#endif
   
   return ::user::impact::pre_create_window(pusersystem);

}


void simple_form_list_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
{

   BASE::handle(ptopic, phandlercontext);

}
