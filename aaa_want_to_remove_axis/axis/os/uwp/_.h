#pragma once



namespace base
{


   template < class APP >
   static i32 app_main(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,i32 nCmdShow)
   {

      if(!defer_base_init())
      {
         return -1;
      }

      APP  * papp = new APP;

      __node_init_main_data(papp,hInstance,hPrevInstance,lpCmdLine,nCmdShow);

      i32 iRet;

      iRet = papp->main();

      try
      {

         delete papp;

         papp = nullptr;

      }
      catch(...)
      {
      }

      defer_base_term();

      return iRet;

   }


} // namespace base











//#include "_UWP_simple_ui.h"
#include "_UWP_sockets.h"
#include "_UWP_user_impl.h"
//#include "_UWP_window_impl.h"





#pragma once


#ifdef __cplusplus

CLASS_DECL_AXIS string normalize_path(const char * lpcszPath);


//string key_to_char(WPARAM wparam,LPARAM lparam);

#endif

//extern CLASS_DECL_AXIS int g_iMouse;

#define GW_HWNDFIRST        0
#define GW_HWNDLAST         1
#define GW_HWNDNEXT         2
#define GW_HWNDPREV         3
#define GW_OWNER            4
#define GW_CHILD            5
#if(WINVER <= 0x0400)
#define GW_MAX              5
#else
#define GW_ENABLEDPOPUP     6
#define GW_MAX              6
#endif


//CLASS_DECL_AXIS bool __cdecl __is_idle_message(::message::message * pmessage);
//CLASS_DECL_AXIS bool __cdecl __is_idle_message(MESSAGE * pMsg);




//CLASS_DECL_AXIS int WINAPI GetSystemMetrics(int i);




//#include "_UWP_gdi_winrt.h"