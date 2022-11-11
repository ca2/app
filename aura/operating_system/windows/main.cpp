#include "framework.h"




//CLASS_DECL_AURA string ca2_command_line(hinstance hinstance);
//
//CLASS_DECL_AURA HRESULT os_create_link(::file::path pathObj, ::file::path pathLink, string strDesc, ::file::path pathIcon = nullptr, int iIcon = 0);
//
//const char* get_cube_app_id();








CLASS_DECL_AURA i32 ca2_main();



//void __cdecl _null_se_translator(u32 uiCode, EXCEPTION_POINTERS * ppointers);





//void __cdecl _null_se_translator(u32 uiCode, EXCEPTION_POINTERS * ppointers)
//{
//   __UNREFERENCED_PARAMETER(uiCode);
//   __UNREFERENCED_PARAMETER(ppointers);
//}













//CLASS_DECL_AURA bool os_init_application()
//{
//
//   return true;
//
//}


//CLASS_DECL_AURA void os_term_application()
//{
//
//
//
//}


//string ca2_command_line(hinstance hinstance)
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


//namespace aura
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
//         pathObj = pcontext->m_papexcontext->file()->module();
//
//         string strLinkTitle;
//
//         strLinkTitle = m_strAppName;
//
//         strLinkTitle.replace("/", "_");
//         strLinkTitle.replace("\\", "_");
//         strLinkTitle.replace("-", "_");
//
//         pathLnk =          auto psystem = acmesystem();

//         auto pacmedirectory = psystem->m_pacmedirectory;
//
//pacmedirectory->localconfig() / "desk/monitor-0/2desk" / strLinkTitle + ".lnk";
//
//                  auto psystem = acmesystem();

//         auto pacmedirectory = psystem->m_pacmedirectory;
//
//pacmedirectory->create(pathLnk.folder());
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
//} // namespace aura


//
//
//void os_post_quit()
//{
//
//   psystem->exception::translator::detach();
//
//}


//CLASS_DECL_AURA void main_async_runnable(::object * pobjectTaskParam)
//{
//
//   ::pointer<::object>pobjectTask = pobjectTaskParam;
//   
//   psystem->post_predicate([pobjectTask]()
//   {
//
//      pobjectTask->call();
//
//   });
//
//}


//CLASS_DECL_AURA void main_sync_runnable(::object * pobjectTaskParam, ::duration durationTimeout)
//{
//   
//   ::pointer<::object>pobjectTask = pobjectTaskParam;
//   
//   psystem->send_predicate([pobjectTask]()
//   {
//
//      pobjectTask->call();
//
//   });
//
//}


void aura_application_main(int argc, char* argv[], const ::string & pszCommandLine)
{


}



