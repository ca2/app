#include "framework.h"
#include <mach-o/dyld.h>



namespace acme
{


//   application::application(::matter * pobject) :
//      ::matter(pobject)
//   {
//
////      m_pthreadimpl.create(this);
////      m_pthreadimpl->m_pthread = this;
//
//      shell::theLinuxShell.Initialize();
//
//   }
//
//   application::~application()
//   {
//
//   }
//
//
//   void application::_001OnFileNew()
//   {
//      //      ::ca2::pointer < ::application_base > ::m_p->_001OnFileNew(nullptr);
//   }
//
//   ::user::document * application::_001OpenDocumentFile(var varFile)
//   {
//      //    return ::ca2::pointer < ::application_base > ::m_p->_001OpenDocumentFile(varFile);
//      return nullptr;
//   }

   void application::_001EnableShellOpen()
   {
      // xxx       ASSERT(m_atomApp == nullptr && m_atomSystemTopic == nullptr); // do once

      // xxx       m_atomApp            = ::GlobalAddAtomW(::str::international::utf8_to_unicode(m_strAppName));
      // xxx       m_atomSystemTopic    = ::GlobalAddAtomW(L"system");
   }

//   bool application::_001OnDDECommand(const char * pcsz)
//   {
//      UNREFERENCED_PARAMETER(pcsz);
//      return FALSE;
//   }
//
//
//   HINSTANCE application::GetHinstance()
//   {
//
//      return nullptr;
//
//   }


   string application::get_version()
   {

      return "";


   }



//
//
//   void application::TermThread(HINSTANCE hInstTerm)
//   {
//
//
//   }
//
//
//


//   bool application::impl_process_init()
//   {
//
//      return true;
//
//   }


//   bool application::impl_init1()
//   {
//
//      return true;
//
//   }


//   bool application::impl_init2()
//   {
//
//      return true;
//
//   }


//   bool application::impl_init3()
//   {
//
//      return true;
//
//   }


   // thread termination
//   void application::impl_process_term() // default will 'delete this'
//   {
//
//      // avoid calling CloseHandle() on our own thread handle
//      // during the thread destructor
//      //m_pthreadimpl->set_os_data(nullptr);
//
//      set_os_data(nullptr);
//
//
//      //i32 iRet = ::acme::application::term_instance();
//
//
//      int iRet = 0;
//
//
//      return iRet;
//
//
//   }

//   void application::impl_term1()
//   {
//   }    void application::impl_term2()
//   {
//   }    void application::impl_term3()
//   {
//   }



   /*
   // Advanced: exception handling
   LRESULT application::ProcessWndProcException(::exception::acme* e, const MESSAGE* pMsg)
   {
   return   ::win::thread::ProcessWndProcException(e, pMsg);
   }


   // Advanced: handling messages sent to message filter hook
   bool application::ProcessMessageFilter(i32 code, LPMESSAGE lpMsg)
   {
   return  ::win::thread::ProcessMessageFilter(code, lpMsg);
   }


   // Advanced: access to GetMainWnd()
   ::user::interaction* application::GetMainWnd()
   {
   return ::win::thread::GetMainWnd();
   }



   void application::assert_valid() const
   {
   ::win::thread::assert_valid();
   }

   void application::dump(dump_context & dumpcontext) const
   {
   ::win::thread::dump(dumpcontext);
   }


   void application::CommonConstruct()
   {
   ::win::thread::CommonConstruct();
   }
   void application::Delete()
   {
   ::win::thread::Delete();
   }
   // 'delete this' only if m_bAutoDelete == TRUE

   bool application::DispatchThreadMessageEx(MESSAGE* msg)  // helper
   {
   return ::win::thread::DispatchThreadMessageEx(msg);
   }*/

   /*   ::draw2d::graphics * application::graphics_from_os_data(void * pdata)
   {
   return ::win::graphics::from_handle((HDC) pdata);
   }*/

//   __pointer(::user::interaction) application::window_from_os_data(void * pdata)
//   {
//      return ::ios::window::from_handle((oswindow) pdata);
//   }
//
//   __pointer(::user::interaction) application::window_from_os_data_permanent(void * pdata)
//   {
//      ::window * pwnd = ::ios::window::FromHandlePermanent((oswindow) pdata);
//      if(pwnd != nullptr)
//         return pwnd;
//      user::interaction_ptr_array wndptra = System.frames();
//      for(i32 i = 0; i < wndptra.get_count(); i++)
//      {
//         if(wndptra[i].get_safe_handle() == (oswindow) pdata)
//         {
//            return wndptra[i].get_wnd();
//         }
//      }
//      return nullptr;
//   }

//   ::thread * application::GetThread()
//   {
//      return ::get_task();
//   }
//
//   void application::set_thread(::thread * pthread)
//   {
//      ::set_thread(pthread);
//   }

   ///////////////////////////////////////////////////////////////////////////
   // application Initialization

//   void application::SetCurrentHandles()
//   {
//      //ASSERT(this == afxCurrentWinApp);
//      //if(afxCurrentAppName != nullptr)
//      // return;
//      //ASSERT(afxCurrentAppName == nullptr);
//
//
//      // Note: there are a number of _tcsdup (aka _strdup) calls that are
//      // made here for the exe path, help file path, etc.  In previous
//      // versions of ca2 API, this memory was never freed.  In this and future
//      // versions this memory is automatically freed during application's
//      // destructor.  If you are freeing the memory yourself, you should
//      // either remove the code or set the pointers to nullptr after freeing
//      // the memory.
//
//      // get path of executable
//      /*   char szBuff[_MAX_PATH];
//      ::u32 dwRet = ::GetModuleFileName(m_hInstance, szBuff, _MAX_PATH);
//      ASSERT( dwRet != 0 && dwRet != _MAX_PATH );
//      if( dwRet == 0 || dwRet == _MAX_PATH )
//      __throw(user_exception());*/
//
//      /*
//       LPTSTR lpszExt = ::PathFindExtension(szBuff);
//       ASSERT(lpszExt != nullptr);
//       if( lpszExt == nullptr )
//       __throw(user_exception());
//
//       ASSERT(*lpszExt == '.');
//       *lpszExt = 0;       // no suffix
//       */
//
//      //      string strExeName;
//      //string strTitle = System.load_string("System.title");
//      // get the exe title from the full path name [no extension]
//      //    strExeName = System.get_module_title();
//
//
//
//      m_pimpl->set_os_data(::GetCurrentThread());
//
//
//   }



   void application::get_time(struct timeval *p)
   {
      gettimeofday(p, nullptr);
   }

//   void application::set_env_var(const string & var,const string & value)
//   {
////#if (defined(SOLARIS8) || defined(SOLARIS))
////      {
////         static std::collection::map<string, char *> vmap;
////         if (vmap.find(var) != vmap.end())
////         {
////            delete[] vmap[var];
////         }
////         vmap[var] = new char[var.get_length() + 1 + value.get_length() + 1];
////         sprintf(vmap[var], "%s=%s", var, value);
////         putenv( vmap[var] );
////      }
////#elif defined _WIN32
////      {
////         string slask = var + "=" + value;
////         _putenv( (const char *)slask);
////      }
////#else
//      setenv(var, value, 1);
////#endif
//   }

//   ITHREAD application::get_thread_id()
//   {
//      return ::GetCurrentThreadId();
//   }



//   bool application::request(::create * pdata)
//   {
//
////      m_pmaindata = (::ios::main_init_data *) pdata;
////
////      if(m_pmaindata != nullptr && m_pimpl->is_system())
////      {
////         if(!win_init(m_pmaindata))
////            return false;
////      }
//
//      m_pcommand = pdata;
//
//      if(m_pcommand != nullptr && is_system())
//      {
//
//         string strCmdLine          = pdata->m_strCommandLine;
//
////         System.m_strCmdLine = strCmdLine;
//
//         SetCurrentHandles();
//
//         __init_thread();
//
//      }
//      return true;
//
//   }

//   bool application::win_init(main_init_data * pdata)
//   {
//      ASSERT(pdata->m_hPrevInstance == nullptr);
//
//      string strCmdLine          = pdata->m_strCommandLine;
//
//      // handle critical errors and avoid Windows message boxes
//      // xxx         SetErrorMode(SetErrorMode(0) | SEM_FAILCRITICALERRORS | SEM_NOOPENFILEERRORBOX);
//
//      System.m_strCmdLine = strCmdLine;
//      //pApp->SetCurrentHandles();
//      SetCurrentHandles();
//
//      __init_thread();
//
//      return true;
//   }



//   __pointer(::user::printer) application::get_printer(const char * pszDeviceName)
//   {
//
//      __pointer(::ios2::printer) pprinter = create_object <  ::user::printer  > ();
//
//      if(!pprinter->open(pszDeviceName))
//      {
//
//         return nullptr;
//
//      }
//
//      return pprinter;
//
//   }

//
//   void application::ShowWaitCursor(bool bShow)
//   {
//
//      UNREFERENCED_PARAMETER(bShow);
//
//   }
//


//   string application::draw2d_get_default_library_name()
//   {
//
//      return "draw2d_quartz2d";
//
//   }
   string application::multimedia_audio_get_default_library_name()
   {

      return "audio_core_audio";

   }

   string application::multimedia_audio_mixer_get_default_library_name()
   {

      return "audio_mixer_core_audio";

   }
   string application::veriwell_multimedia_music_midi_get_default_library_name()
   {

      return "music_midi_core_audio";

   }

//   void application::ShowWaitCursor(bool bShow)
//   {
//
//      UNREFERENCED_PARAMETER(bShow);
//
//   }




   void application::ShowWaitCursor(bool bShow)
   {

      UNREFERENCED_PARAMETER(bShow);

   }


   bool application::os_on_start_application()
   {

      return true;

   }



} // namespace acme



