#pragma once


#ifdef cplusplus


CLASS_DECL_AXIS bool vfxResolveShortcut(string & strTarget,const char * pszSource,__pointer(::user::primitive) puiMessageParentOptional);



#endif


//#ifdef cplusplus
//
//namespace axis
//{
//
//
//   template < class APP >
//   static i32 app_main(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR pCmdLine,edisplay edisplay)

//   {
//
//      if(!defer_axis_init())
//      {
//
//         ::output_debug_string("Failed to defer_axis_init.");
//
//         return -2;
//
//      }
//
//      APP  * papp = new APP;
//
//      __node_init_main_data(papp, hInstance,hPrevInstance,pCmdLine,nCmdShow);

//
//      i32 iRet;
//
//      iRet = papp->main();
//
//      try
//      {
//
//         delete papp;
//
//         papp = nullptr;
//
//      }
//      catch(...)
//      {
//      }
//
//      if(!defer_axis_term())
//      {
//
//         ::output_debug_string("Failed to defer_axis_term.");
//
//         iRet -= 9011;
//
//      }
//
//      return iRet;
//
//   }
//
//
//} // namespace axis
//
//
//
//
//
//#endif




CLASS_DECL_AXIS WSADATA get_wsadata();

#ifdef cplusplus

namespace hotplugin
{



} // namespace hotplugin

#endif

