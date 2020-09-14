#include "framework.h"




CLASS_DECL_ACME string ca2_command_line(HINSTANCE hinstance);

CLASS_DECL_ACME HRESULT os_create_link(::file::path pathObj, ::file::path pathLink, string strDesc, ::file::path pathIcon = nullptr, int iIcon = 0);

//const char* get_cube_app_id();








CLASS_DECL_ACME i32 ca2_main();


void CLASS_DECL_ACME __cdecl _ca2_purecall()
{

   __throw(::exception::exception());

}


void __cdecl _null_se_translator(u32 uiCode, EXCEPTION_POINTERS * ppointers);





void __cdecl _null_se_translator(u32 uiCode, EXCEPTION_POINTERS * ppointers)
{
   UNREFERENCED_PARAMETER(uiCode);
   UNREFERENCED_PARAMETER(ppointers);
}









#undef new



//CLASS_DECL_ACME bool os_init_application()
//{
//
//   return true;
//
//}
//
//
//CLASS_DECL_ACME void os_term_application()
//{
//
//
//
//}

//
//string ca2_command_line(HINSTANCE hinstance)
//{
//
//#ifdef CUBE
//
//   string strAppId = get_cube_app_id();
//
//#else
//
//   string strAppId = read_resource_as_string(hinstance, 1, "APPID");
//
//#endif
//
//   if (strAppId.is_empty())
//   {
//
//      return "";
//
//   }
//
//   return "app.exe : app=" + strAppId;
//
//}


//
//
//namespace acme
//{
//
//
//   bool application::os_on_start_application()
//   {
//
//      if (!::is_debugger_attached())
//      {
//
//         ::file::path pathObj;
//
//         ::file::path pathLnk;
//
//         pathObj = Context.file().module();
//
//         string strLinkTitle;
//
//         strLinkTitle = m_strAppName;
//
//         strLinkTitle.replace("/", "_");
//         strLinkTitle.replace("\\", "_");
//         strLinkTitle.replace("-", "_");
//
//         pathLnk = ::dir::localconfig() / "desk/monitor-0/2desk" / strLinkTitle + ".lnk";
//
//         ::dir::mk(pathLnk.folder());
//
//         os_create_link(pathObj, pathLnk, "app=" + m_strAppName);
//
//      }
//
//      return true;
//
//   }
//
//
//} // namespace acme
//



void os_post_quit()
{



}


//
//
//CLASS_DECL_ACME void main_async_runnable(::generic * pobjectTaskParam)
//{
//
//   __pointer(::generic) pobjectTask = pobjectTaskParam;
//   
//   ::get_context_system()->post_pred([pobjectTask]()
//   {
//
//      pobjectTask->call();
//
//   });
//
//}

//
//CLASS_DECL_ACME void main_sync_runnable(::generic * pobjectTaskParam, ::duration durationTimeout)
//{
//   
//   __pointer(::generic) pobjectTask = pobjectTaskParam;
//   
//   ::get_context_system()->send_pred([pobjectTask]()
//   {
//
//      pobjectTask->call();
//
//   });
//
//}




