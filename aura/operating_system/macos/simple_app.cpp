#include "framework.h"


//namespace aura
//{
//
//
//   app::app()
//   {
//
//   }
//
//
//   app::~app()
//   {
//
//   }
//
//
//   i32 app::main()
//   {
//
//
////      TCHAR *cmd = pcontext->m_papexcontext->os().get_command_line();
////
////      // Skip program name
////      if(*cmd == _T('"'))
////      {
////         while(*cmd && *cmd != _T('"'))
////            cmd++;
////         if(*cmd == _T('"'))
////            cmd++;
////      }
////      else
////      {
////         while(*cmd > _T(' '))
////            cmd++;
////      }
////
////      // Skip any white space
////      while(*cmd && *cmd <= _T(' '))
////         cmd++;
//
//      body();
//
////      _term_args();
//
//      //::message_box(nullptr,"t3=" + __string(m_iErrorCode),"t3",e_message_box_ok);
//
//
//      return m_iErrorCode;
//
//   }
//
//
//   void app::body()
//   {
//
//      try
//      {
//         if((m_iErrorCode = simple_app_pre_run()) != 0)
//         {
//            return;
//
//         }
//      }
//      catch(...)
//      {
//
//         if(m_iErrorCode == 0)
//            m_iErrorCode = -1;
//
//         return;
//
//      }
//
//
//      try
//      {
//
////         set_main_user_htask(GetCurrentThread());
//
//  //       set_main_user_itask(GetCurrentThreadId());
//
//         if(!pre_run())
//         {
//
//            if(m_iErrorCode == 0)
//               m_iErrorCode = -1;
//
//            return;
//
//         }
//
//         dappy(__type_name(this) + " : s_app pre_runned : " + __string(m_iErrorCode));
//
//         SetCurrentHandles();
//
//         dappy(__type_name(this) + " : handles set s_app : " + __string(m_iErrorCode));
//
//      }
//      catch(...)
//      {
//
//         if(m_iErrorCode == 0)
//            m_iErrorCode = -1;
//
//         return;
//
//      }
//
//
//      try
//      {
//
//         dappy(__type_name(this) + " : s_app going to intro : " + __string(m_iErrorCode));
//
//         if(!intro())
//         {
//
//            if(m_iErrorCode == 0)
//               m_iErrorCode = -1;
//
//            return;
//
//         }
//
//         dappy(__type_name(this) + " : s_app introduced : " + __string(m_iErrorCode));
//
//      }
//      catch(...)
//      {
//
//         if(m_iErrorCode == 0)
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
//         if(m_iErrorCode == 0)
//            m_iErrorCode = -1;
//
//         return;
//
//      }
//
//      try
//      {
//
//         end();
//
//      }
//      catch(...)
//      {
//      }
//
//   }
//
//
//   bool app::intro()
//   {
//
//      return true;
//
//   }
//
//
//   i32 app::refrain()
//   {
//
//      while(true)
//      {
//
//         GetMessage(&m_msg,nullptr,0,0xffffffffu);
//
//         TranslateMessage(&m_msg);
//
//         DispatchMessage(&m_msg);
//
//      }
//
//      return 0;
//
//   }
//
//
//   bool app::end()
//   {
//
//      try
//      {
//
//         m_iErrorCode = exit_thread();
//
//      }
//      catch(...)
//      {
//
//         m_iErrorCode = -1;
//
//      }
//
//      return true;
//
//   }
//
//
//   i32 app::simple_app_pre_run()
//   {
//
//      return 0;
//
//   }
//
//
//} // namespace aura
//
//
//
