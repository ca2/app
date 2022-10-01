#include "framework.h"
//#include <mach-o/dyld.h>


namespace apex
{


//   application::application(::object * pobject) :
//      ::object(pobject)
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
//   ::user::document * application::_001OpenDocumentFile(::payload payloadFile)
//   {
//      //    return ::ca2::pointer < ::application_base > ::m_p->_001OpenDocumentFile(payloadFile);
//      return nullptr;
//   }
//
//   void application::_001EnableShellOpen()
//   {
//      // xxx       ASSERT(m_atomApp == nullptr && m_atomSystemTopic == nullptr); // do once
//
//      // xxx       m_atomApp            = ::GlobalAddAtomW(utf8_to_unicode(m_strAppName));
//      // xxx       m_atomSystemTopic    = ::GlobalAddAtomW(L"system");
//   }

//   bool application::_001OnDDECommand(const char * pcsz)
//   {
//      __UNREFERENCED_PARAMETER(pcsz);
//      return false;
//   }
//
//
//   HINSTANCE application::GetHinstance()
//   {
//
//      return nullptr;
//
//   }


//   string application::get_version()
//   {
//
//      return "";
//
//
//   }



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
//      //i32 iRet = ::application::term_instance();
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
   LRESULT application::ProcessWndProcException(::exception::apex* e, const MESSAGE* pMsg)
   {
   return   ::win::thread::ProcessWndProcException(e, pMsg);
   }


   // Advanced: handling messages sent to message filter hook
   bool application::ProcessMessageFilter(i32 code, MESSAGE * lpMsg)
   {
   return  ::win::thread::ProcessMessageFilter(code, lpMsg);
   }


   // Advanced: access to GetMainWnd()
   ::user::interaction* application::GetMainWnd()
   {
   return ::win::thread::GetMainWnd();
   }



   void application::assert_ok() const
   {
   ::win::thread::assert_ok();
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
   // 'delete this' only if m_bAutoDelete == true

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
//      ::window * puserinteraction = ::ios::window::FromHandlePermanent((oswindow) pdata);
//      if(puserinteraction != nullptr)
//         return puserinteraction;
//      user::interaction_ptr_array wndptra = ::apex::get_system()->frames();
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
//      // either erase the code or set the pointers to nullptr after freeing
//      // the memory.
//
//      // get path of executable
//      /*   char szBuff[_MAX_PATH];
//      ::u32 dwRet = ::GetModuleFileName(m_hInstance, szBuff, _MAX_PATH);
//      ASSERT( dwRet != 0 && dwRet != _MAX_PATH );
//      if( dwRet == 0 || dwRet == _MAX_PATH )
//      throw ::exception(user_exception());*/
//
//      /*
//       char * lpszExt = ::PathFindExtension(szBuff);
//       ASSERT(lpszExt != nullptr);
//       if( lpszExt == nullptr )
//       throw ::exception(user_exception());
//
//       ASSERT(*lpszExt == '.');
//       *lpszExt = 0;       // no suffix
//       */
//
//      //      string strExeName;
//      //string strTitle = ::apex::get_system()->load_string("::apex::get_system()->title");
//      // get the exe title from the full path name [no extension]
//      //    strExeName = ::apex::get_system()->get_module_title();
//
//
//
//      m_pimpl->set_os_data(::GetCurrentThread());
//
//
//   }


//
//   void application::get_time(struct timeval *p)
//   {
//      gettimeofday(p, nullptr);
//   }

//   void application::set_env_var(const string & payload,const string & value)
//   {
////#if (defined(SOLARIS8) || defined(SOLARIS))
////      {
////         static std::collection::map<string, char *> vmap;
////         if (vmap.find(payload) != vmap.end())
////         {
////            delete[] vmap[::payload];
////         }
////         vmap[::payload] = memory_new char[payload.get_length() + 1 + value.get_length() + 1];
////         sprintf(vmap[::payload], "%s=%s", payload, value);
////         putenv( vmap[::payload] );
////      }
////#elif defined _WIN32
////      {
////         string slask = payload + "=" + value;
////         _putenv( (const char *)slask);
////      }
////#else
//      setenv(payload, value, 1);
////#endif
//   }

//   itask_t application::get_thread_id()
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
////         ::apex::get_system()->m_strCmdLine = strCmdLine;
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
//      ::apex::get_system()->m_strCmdLine = strCmdLine;
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
//   void application::show_wait_cursor(bool bShow)
//   {
//
//      __UNREFERENCED_PARAMETER(bShow);
//
//   }
//


//   string application::draw2d_get_default_library_name()
//   {
//
//      return "draw2d_quartz2d";
//
//   }
//   string application::multimedia_audio_get_default_library_name()
//   {
//
//      return "audio_core_audio";
//
//   }

//   string application::multimedia_audio_mixer_get_default_library_name()
//   {
//
//      return "audio_mixer_core_audio";
//
//   }
//   string application::veriwell_multimedia_music_midi_get_default_library_name()
//   {
//
//      return "music_midi_core_audio";
//
//   }

//   void application::show_wait_cursor(bool bShow)
//   {
//
//      __UNREFERENCED_PARAMETER(bShow);
//
//   }




//   void application::show_wait_cursor(bool bShow)
//   {
//
//      __UNREFERENCED_PARAMETER(bShow);
//
//   }

//


   bool application::os_on_start_application()
   {

      return true;

   }


} // namespace apex



