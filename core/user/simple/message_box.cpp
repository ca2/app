#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/simple/_simple.h"
#endif


//CLASS_DECL_CORE void aura_message_box(oswindow interaction_impl,const char * pText,const char * lpCaption,u32 uiFlags, function_arg functionargResult);


//i32(*g_pfn_message_box)(oswindow,const char *,const char *,u32, const function_arg &) = nullptr;


//CLASS_DECL_CORE ::estatus os_message_box(oswindow oswindow, const char * pszText, const char * pszTitle, u32 uFlags, function_arg function)
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


//CLASS_DECL_CORE ::estatus os_message_box(const var & varParam)
//{
//   
//   var var;
//   
//   if(varParam.get_type () != type_propset)
//   {
//      
//      var["message"] = varParam.get_string();
//      
//   }
//   else
//   {
//      
//      var = varParam;
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
//   puiParent = var["parent"].cast < ::user::primitive >();
//
//   strMessage = var["message"];
//
//   strTitle = var["title"];
//
//   uFlags = var["flags"];
//
//   durationTimeout = var["duration"];
//
//   callback = var["callback"];
//
//   return ::os_message_box(puiParent->get_safe_handle(), strMessage.c_str(), strTitle.c_str(), uFlags, functionarg);
//
//}


//CLASS_DECL_CORE void aura_message_box(oswindow interaction_impl,const char * pText,const char * lpCaption,u32 uiFlags)
//{
//
//   ::os_message_box(interaction_impl,pText,lpCaption,uiFlags);
//
//}


//CLASS_DECL_CORE void set_message_box(i32(*pfn)(oswindow, const char *, const char *, u32, const ::function_arg & ))
//{
//
//   g_pfn_message_box = pfn;
//
//}
