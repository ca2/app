#include "framework.h"
#include "base/user/user/user.h"
#include "base/base/node/metrowin/metrowin.h"


#undef CoreApplication


CLASS_DECL_ACME int app_core_main(const char * pszCmdLine)
{

   if(!defer_core_init())
      return -1;

   if(file_exists(::dir::system() / "config\\system\\beg_debug_box.txt"))
   {
      debug_box("zzzAPPzzz app","zzzAPPzzz app",e_message_box_icon_information);
   }

   ::acme::system * psystem                     = new ::acme::system;

   auto source = ::metrowin::new_directx_application_source(psystem,pszCmdLine);

   ::Windows::ApplicationModel::Core::CoreApplication::Run(source);

   try
   {

      delete psystem;

   }
   catch(...)
   {

   }

   psystem = nullptr;


   defer_core_term();

   char szTimeMessage[2048];

   sprintf(szTimeMessage,"\n\n\n\n\n\n-------------------------------\n|\n|\n|  Total Elapsed Time %d\n|\n|\n-------------------------------\n\n\n",(u32) g_tickStartTime.elapsed());

   ::output_debug_string(szTimeMessage);

   printf(szTimeMessage);

   return 0;




}



void simple_frame_window::defer_set_icon()
{


}




