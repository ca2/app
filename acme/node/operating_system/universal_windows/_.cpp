#include "framework.h"
#include "acme/operating_system.h"
//#include "_uwp.h"
#include "acme/id.h"


bool __node_acme_pre_init()
{

   //xxdebug_box("__node_acme_pre_init","box",e_message_box_ok);

   //g_pgdiplusStartupInput     = new Gdiplus::GdiplusStartupInput();

   //g_pgdiplusStartupOutput    = new Gdiplus::GdiplusStartupOutput();

   //g_gdiplusToken             = NULL;

   //g_gdiplusHookToken         = NULL;

   //g_pgdiplusStartupInput->SuppressBackgroundThread = true;

   //Gdiplus::Status statusStartup = GdiplusStartup(&g_gdiplusToken,g_pgdiplusStartupInput,g_pgdiplusStartupOutput);

   //if(statusStartup != Gdiplus::Ok)
   //{

   //   output_message_box_error("Gdiplus Failed to Startup. ca cannot continue.","Gdiplus Failure",MB_ICONERROR);

   //   return 0;

   //}

   //statusStartup = g_pgdiplusStartupOutput->NotificationHook(&g_gdiplusHookToken);

   //if(statusStartup != Gdiplus::Ok)
   //{

   //   os_message_box(nullptr,"Gdiplus Failed to Hook. ca cannot continue.","Gdiplus Failure",MB_ICONERROR);

   //   return 0;

   //}

// #ifndef USE_OS_IMAGE_LOADER

//    try
//    {

//       FreeImage_Initialise(false);

//    }
//    catch (...)
//    {

//       ::message_box(nullptr, "Failure to initialize FreeImage (::acme::init_core)", "FreeImage_Initialise failure", e_message_box_icon_exclamation);

//       return false;

//    }

// #endif // SMALLCODE

   return true;

}


//void windows_registry_init();



bool __node_acme_pos_init()
{

   _set_purecall_handler(_ca2_purecall);

   //HMODULE hmoduleUser32 = ::LoadLibraryW(L"User32");
   //g_pfnChangeWindowMessageFilter = (LPFN_ChangeWindowMessageFilter) ::GetProcAddress(hmoduleUser32, "ChangeWindowMessageFilter");


   //windows_registry_init();



   return true;

}


bool __node_acme_pre_term()
{



   return true;

}

bool __node_acme_pos_term()
{


   // #ifndef USE_OS_IMAGE_LOADER

   //    try
   //    {

   //       FreeImage_DeInitialise();

   //    }
   //    catch (...)
   //    {

   //    }

   // #endif // USE_OS_IMAGE_LOADER


      //if (g_pgdiplusStartupOutput != nullptr)
      //{

      //   g_pgdiplusStartupOutput->NotificationUnhook(g_gdiplusHookToken);


      //   ::Gdiplus::GdiplusShutdown(g_gdiplusToken);


      //   ::acme::del(g_pgdiplusStartupInput);
      //   ::acme::del(g_pgdiplusStartupOutput);
      //}

   if (is_verbose())
   {

      output_debug_string(L"acme terminating!\n");

   }

   //::CoUninitialize();


   WSACleanup();


   return true;

}





::millis os_get_system_update_poll_time(const ::id & id)
{

   if (id == id_os_dark_mode)
   {

      return 500;

   }
   else if (id == id_os_font_change)
   {

      return 0;

   }
   else if (id == id_font_enumeration)
   {

      return 0;

   }

   return 500;

}






