#include "framework.h"
#include "acme/operating_system.h"


CLASS_DECL_ACME string ca2_command_line(hinstance hinstance);

//CLASS_DECL_ACME HRESULT os_create_link(::file::path pathObj, ::file::path pathLink, string strDesc, ::file::path pathIcon = nullptr, int iIcon = 0);

//const char* get_cube_app_id();


CLASS_DECL_ACME i32 ca2_main();


void __cdecl _null_se_translator(u32 uiCode, EXCEPTION_POINTERS * ppointers);


void __cdecl _null_se_translator(u32 uiCode, EXCEPTION_POINTERS * ppointers)
{

   UNREFERENCED_PARAMETER(uiCode);
   UNREFERENCED_PARAMETER(ppointers);

}



#undef new


CLASS_DECL_ACME bool os_init_application()
{

   return true;

}


CLASS_DECL_ACME void os_term_application()
{


}


string ca2_command_line(hinstance hinstance)
{

#ifdef CUBE

   string strAppId = get_cube_app_id();

#else

   string strAppId = read_resource_as_string(hinstance, 1, "APPID");

#endif

   if (strAppId.is_empty())
   {

      return "";

   }

   return "app.exe : app=" + strAppId;

}


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
//         pathObj = m_pcontext->m_papexcontext->file().module();
//
//         string strLinkTitle;
//
//         strLinkTitle = m_strAppName;
//
//         strLinkTitle.replace("/", "_");
//         strLinkTitle.replace("\\", "_");
//         strLinkTitle.replace("-", "_");
//
//         pathLnk = pacmedir->localconfig() / "desk/monitor-0/2desk" / strLinkTitle + ".lnk";
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
//CLASS_DECL_ACME void main_async_runnable(::matter * pobjectTaskParam)
//{
//
//   __pointer(::matter) pobjectTask = pobjectTaskParam;
//   
//   get_system()->post_predicate([pobjectTask]()
//   {
//
//      pobjectTask->call();
//
//   });
//
//}

//
//CLASS_DECL_ACME void main_sync_runnable(::matter * pobjectTaskParam, ::duration durationTimeout)
//{
//   
//   __pointer(::matter) pobjectTask = pobjectTaskParam;
//   
//   get_system()->send_predicate([pobjectTask]()
//   {
//
//      pobjectTask->call();
//
//   });
//
//}




