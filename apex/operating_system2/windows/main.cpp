#include "framework.h"
#include "apex/operating_system.h"
#include "apex/platform/node.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/platform/application.h"
#include "apex/platform/system.h"


//CLASS_DECL_APEX string ca2_command_line(hinstance hinstance);

//CLASS_DECL_APEX HRESULT os_create_link(::file::path pathObj, ::file::path pathLink, const ::scoped_string & scopedstrDesc, ::file::path pathIcon = nullptr, int iIcon = 0);

const_char_pointer get_cube_app_id();








CLASS_DECL_APEX int ca2_main();


//void CLASS_DECL_APEX __cdecl _ca2_purecall()
//{
//
//   throw ::exception(::exception());
//
//}


//void __cdecl _null_se_translator(unsigned int uiCode, EXCEPTION_POINTERS * ppointers);
//
//



//void __cdecl _null_se_translator(unsigned int uiCode, EXCEPTION_POINTERS * ppointers)
//{
//   __UNREFERENCED_PARAMETER(uiCode);
//   __UNREFERENCED_PARAMETER(ppointers);
//}













//CLASS_DECL_APEX bool os_init_application()
//{
//
//   return true;
//
//}
//
//
//CLASS_DECL_APEX void os_term_application()
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


// // // namespace apex
// // // {


// // //    bool application::os_on_start_application()
// // //    {

// // //       //if (!::is_debugger_attached())
// // //       {

// // //          ::file::path pathObj;

// // //          ::file::path pathLnk;

// // //          pathObj = file()->module();

// // //          string strLinkTitle;

// // //          strLinkTitle = m_strAppName;

// // //          strLinkTitle.replace_with("_", "/");
// // //          strLinkTitle.replace_with("_", "\\");
// // //          strLinkTitle.replace_with("_", "-");

// // //          pathLnk = directory_system()->localconfig() / "desk/monitor-0/2desk" / strLinkTitle + ".lnk";

// // //          directory_system()->create(pathLnk.folder());

// // //          system()->shell_create_link(pathObj, pathLnk, "app=" + m_strAppName);

// // //       }

// // //       return true;

// // //    }



// // // } // namespace apex




   //
   //void os_post_quit()
   //{
   //
   //
   //
   //}


   //CLASS_DECL_APEX void main_async_runnable(const ::procedure & procedure)
   //{
   //
   //   //::pointer<::object>pobjectTask = pobjectTaskParam;
   //
   //
   //   
   //   psystem->post_predicate([routine]()
   //   {
   //
   //      routine();
   //
   //   });
   //
   //}
   //
   //
   //CLASS_DECL_APEX void main_sync_runnable(const ::procedure & procedure, ::time timeTimeout)
   //{
   //   
   //   psystem->send_routine(routine, timeTimeout);
   //
   //}


void apex_application_main(int argc, char * argv[], const ::scoped_string & scopedstrCommandLine)
{


}
