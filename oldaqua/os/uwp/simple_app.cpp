#include "framework.h"
//#include "uwp.h"

//namespace aqua
//{
//
//   app::app()
//   {
//
//      m_iErrorCode = 0;
//
//   }
//
//   app::~app()
//   {
//
//   }
//
//
//   int app::main()
//   {
//
//      //Sleep(15 * 1000);
//
//#ifdef WINDOWS_DESKTOP
//
//
//      TCHAR *cmd = GetCommandLine();
//
//      // Skip program name
//      if (*cmd == _T('"'))
//      {
//         while (*cmd && *cmd != _T('"'))
//            cmd++;
//         if (*cmd == _T('"'))
//            cmd++;
//      }
//      else
//      {
//         while (*cmd > _T(' '))
//            cmd++;
//      }
//
//      // Skip any white space
//      while (*cmd && *cmd <= _T(' '))
//         cmd++;
//
//      STARTUPINFO si;
//      si.dwFlags = 0;
//      GetStartupInfo(&si);
//
//      initialize_primitive_heap();
//
//
//      initialize_primitive_trace();
//
//      if(!os_initialize())
//         return -1;
//
//      if(!main_initialize())
//         return -1;
//
//      body();
//
//      finalize_primitive_trace();
//
//      main_finalize();
//
//      os_finalize();
//
//      finalize_primitive_heap();
//
//      //_doexit();
//      _term_args();
//
//#endif
//
//      return m_iErrorCode;
//
//   }
//
//
//   void app::body()
//   {
//
//
//      try
//      {
//
//         if(!initialize())
//         {
//
//            if(m_iErrorCode > 0)
//               m_iErrorCode = -1;
//
//            return;
//
//         }
//
//      }
//      catch(...)
//      {
//
//         if(m_iErrorCode > 0)
//            m_iErrorCode = -1;
//
//         return;
//
//      }
//
//      try
//      {
//
//         m_iErrorCode = run();
//
//      }
//      catch(...)
//      {
//
//         if(m_iErrorCode > 0)
//            m_iErrorCode = -1;
//
//         return;
//
//      }
//
//      try
//      {
//
//         finalize();
//
//      }
//      catch(...)
//      {
//      }
//
//   }
//
//   bool app::intro()
//   {
//      return true;
//   }
//
//   int app::refrain()
//   {
//
//#ifdef WINDOWS_DESKTOP
//      while(true)
//      {
//         GetMessage(&m_msg, nullptr, 0, 0xffffffffu);
//         TranslateMessage(&m_msg);
//         DispatchMessage(&m_msg);
//}
//#endif
//
//      return 0;
//}
//
//   bool app::end()
//   {
//      return true;
//   }
//
//
//   int app::simple_app_pre_run()
//   {
//
//      return 0;
//
//   }
//
//
//} // namespace aqua
//
//
//
