#include "framework.h"
#include "core/user/simple/_simple.h"


//CLASS_DECL_CORE void aura_message_box(oswindow interaction_impl, const ::string & pText, const ::string & lpCaption,u32 uFlags, function_arg functionargResult);


//i32(*g_pfn_message_box)(oswindow, const ::string &, const ::string &,u32, const function_arg &) = nullptr;


//CLASS_DECL_CORE ::e_status os_message_box(oswindow oswindow, const ::string & pszText, const ::string & pszTitle, u32 uFlags, function_arg function)
//{
//
//#ifndef _UWP
//
//   if(g_pfn_message_box != nullptr)
//   {
//
//      (*g_pfn_message_box)(oswindow, pszText, pszTitle, uFlags, function);
//
//   }
//
//#endif
//
//   aura_message_box(oswindow, pszText, pszTitle, uFlags, function);
//
//}


//CLASS_DECL_CORE ::e_status os_message_box(const ::payload & varParam)
//{
//   
//   ::payload payload;
//   
//   if(varParam.get_type () != e_type_property_set)
//   {
//      
//      payload["message"] = varParam.get_string();
//      
//   }
//   else
//   {
//      
//      payload = varParam;
//      
//   }
//
//   __pointer(::user::primitive) puiParent;
//
//   string strMessage;
//
//   string strTitle;
//
//   u32 uFlags = 0;
//
//   ::duration durationTimeout;
//
//   ::callback callback;
//
//   puiParent = payload["parent"].cast < ::user::primitive >();
//
//   strMessage = payload["message"];
//
//   strTitle = payload["title"];
//
//   uFlags = payload["flags"];
//
//   durationTimeout = payload["duration"];
//
//   callback = payload["callback"];
//
//   return ::os_message_box(puiParent->get_safe_handle(), strMessage.c_str(), strTitle.c_str(), uFlags, functionarg);
//
//}


//CLASS_DECL_CORE void aura_message_box(oswindow interaction_impl, const ::string & pText, const ::string & lpCaption,u32 uFlags)
//{
//
//   ::os_message_box(interaction_impl,pText,lpCaption,uFlags);
//
//}


//CLASS_DECL_CORE void set_message_box(i32(*pfn)(oswindow, const ::string &, const ::string &, u32, const ::function_arg & ))
//{
//
//   g_pfn_message_box = pfn;
//
//}
