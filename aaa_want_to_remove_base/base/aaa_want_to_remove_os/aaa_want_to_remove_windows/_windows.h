#pragma once


#include "aura/os/windows/_windows.h"


#ifdef cplusplus

#ifdef WINDOWS_DESKTOP

namespace base
{


   class system_interaction_impl;


} // namespace axis


#endif

//namespace base
//{
//
//
//   template < class APP >
//   static i32 app_main(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR pCmdLine,edisplay edisplay)

//   {
//
//      APP  * papp = new APP;
//
//      __node_init_main_data(papp,hInstance,hPrevInstance,pCmdLine,nCmdShow);

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
//      defer_base_term();
//
//      return iRet;
//
//   }
//
//
//} // namespace base
//

#endif

//#include "windows_window_buffer.h"

#include "extract_icon.h"



