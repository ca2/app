#include "framework.h"
#include "acme/constant/id.h"


#include "acme/_operating_system.h"



void __node_acme_pre_init()
{

   //xxdebug_box("__node_acme_pre_init","box",e_message_box_ok);

   //g_pgdiplusStartupInput     = normal_new Gdiplus::GdiplusStartupInput();

   //g_pgdiplusStartupOutput    = normal_new Gdiplus::GdiplusStartupOutput();

   //g_gdiplusToken             = NULL;

   //g_gdiplusHookToken         = NULL;

   //g_pgdiplusStartupInput->SuppressBackgroundThread = true;

   //Gdiplus::Status statusStartup = GdiplusStartup(&g_gdiplusToken,g_pgdiplusStartupInput,g_pgdiplusStartupOutput);

   //if(statusStartup != Gdiplus::Ok)
   //{

   //   output_error_message("Gdiplus Failed to Startup. ca cannot continue.","Gdiplus Failure",MB_ICONERROR);

   //   return 0;

   //}

   //statusStartup = g_pgdiplusStartupOutput->NotificationHook(&g_gdiplusHookToken);

   //if(statusStartup != Gdiplus::Ok)
   //{

   //   auto pmessagebox = __initialize_new ::message_box(nullptr,"Gdiplus Failed to Hook. ca cannot continue.","Gdiplus Failure",MB_ICONERROR);

pmessagebox->sync();

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

   //return true;

}


//void windows_registry_init();

void CLASS_DECL_ACME __cdecl _ca2_purecall();

void __node_acme_pos_init()
{

   _set_purecall_handler(_ca2_purecall);

   //HMODULE hmoduleUser32 = ::LoadLibraryW(L"User32");
   //g_pfnChangeWindowMessageFilter = (LPFN_ChangeWindowMessageFilter) ::GetProcAddress(hmoduleUser32, "ChangeWindowMessageFilter");


   //windows_registry_init();



   //return true;

}


void __node_acme_pre_term()
{



   //return true;

}


void __node_acme_pos_term()
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

   //if (is_verbose())
   //{

   //   information(L"acme terminating!\n");

   //}

   //::CoUninitialize();


   WSACleanup();


   //return true;

}





// ::time os_get_system_update_poll_time(const ::atom & atom)
// {

//    if (atom == id_user_color)
//    {

//       return 500_ms;

//    }
//    else if (atom == id_os_font_change)
//    {

//       return 0_s;

//    }
//    else if (atom == id_font_enumeration)
//    {

//       return 0_s;

//    }

//    return 500_ms;

// }



CLASS_DECL_ACME string get_command_line()
{

   return GetCommandLineW();

}





