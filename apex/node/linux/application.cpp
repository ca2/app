#include "framework.h"
//#include "apex/node/ansios/ansios.h"
#include "_linux.h"
#include "apex/os/linux/_linux.h"


//#include <X11/cursorfont.h>
#include <sys/time.h>
#include <link.h>
#include "acme/os/ansios/_pthread.h"


namespace apex
{

//   application::application(::layered * pobjectContext) :
//      ::object(pobject)
//   {
//
////      m_pthreadimpl.create(this);
////      m_pthreadimpl->m_pthread = this;
//
//  //m_nSafetyPoolSize = 512;        // default size_i32
//
//      shell::theLinuxShell.Initialize();
//   }
//
//   application::~application()
//   {
//
//   }


//   void application::_001OnFileNew()
//   {
//
////      _001OnFileNew(nullptr);
//
//   }


//   ::apex::document * application::_001opendocumentfile(::payload varfile)
//   {
//
//      return m_pimpl->_001opendocumentfile(varfile);
//
//   }
//

   ::e_status application::_001InitializeShellOpen()
   {
// xxx       ASSERT(m_atomApp == nullptr && m_atomSystemTopic == nullptr); // do once

// xxx       m_atomApp            = ::GlobalAddAtomW(::str::international::utf8_to_unicode(m_strAppName));
// xxx       m_atomSystemTopic    = ::GlobalAddAtomW(L"system");

      return ::success;

   }

//   bool application::_001OnDDECommand(const char * pcsz)

//   {
//      UNREFERENCED_PARAMETER(pcsz);

//      return false;
//   }

//   HINSTANCE application::GetHinstance()
//   {
//      return nullptr;
//   }

   string application::get_version()
   {
      return "";

      __throw(todo);

      /*      char pszModuleFilePath[MAX_PATH + 1];

            GetModuleFileName(nullptr, pszModuleFilePath, MAX_PATH + 1);


            ::u32 dw;

            ::u32 dwResSize = GetFileVersionInfoSize(
               pszModuleFilePath,

               &dw);


            if(dwResSize > 0)
            {
               LPVOID pdata = new byte[dwResSize];

               if(GetFileVersionInfo(
                  pszModuleFilePath,

                  0,
                  dwResSize,
                  pdata))

               {
                  ::u32 cbTranslate;
                  struct LANGANDCODEPAGE {
                     ::u16 wLanguage;
                     ::u16 wCodePage;
                  } *pTranslate;


                  // read the list of languages and code pages.

                  VerQueryValue(pdata,

                     TEXT("\\VarFileInfo\\Translation"),
                     (LPVOID*)&pTranslate,

                     &cbTranslate);

                  string strKey;
                  //for( i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ )
                  for(i32 i=0; i < 1; i++ )
                  {
                     char * psz;

                     ::u32 uSize;

                     strKey.Format(
                        TEXT("\\StringFileInfo\\%04x%04x\\FileDescription"),
                        pTranslate[i].wLanguage,

                        pTranslate[i].wCodePage);





                     strKey.Format(
                        TEXT("\\StringFileInfo\\%04x%04x\\FileVersion"),
                        pTranslate[i].wLanguage,

                        pTranslate[i].wCodePage);


                     // Retrieve file description for language and code page "i".
                     VerQueryValue(pdata,

                        (char *) (const char *) strKey,
                        (LPVOID *)&psz,

                        &uiSize);


                     string strVersion(psz, uiSize);


                     return strVersion;
                  }
               }
               delete [] (byte *) pdata;

            }
      */

      return "";

   }



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
////      set_run();
//
//      return true;
//
//   }
//
//
//   bool application::impl_init2()
//   {
//
//      return true;
//
//   }
//
//
//   bool application::impl_init3()
//   {
//
//      return true;
//
//   }

//
//   void application::impl_term1()
//   {
//
//
//   }
//
//
//   void application::impl_term2()
//   {
//
//
//   }
//
//
//   void application::impl_term3()
//   {
//
//
//   }


//   void application::impl_process_term() // default will 'delete this'
//   {
//
//      // avoid calling CloseHandle() on our own thread handle
//      // during the thread destructor
//      set_os_data(nullptr);
//
//      //m_pimpl->m_bRun = false;
//      //LNX_THREAD(m_pimpl->::thread_pointer::m_p)->m_bRun = false;
//
//      //i32 iRet = ::apex::application::term_instance();
//
//      //::ca2::pointer<::ca2::application>::destroy();
//
//
//
//      //return 0;
//   }
   /*
      // Advanced: exception handling
      LRESULT application::ProcessWndProcException(::exception::apex* e, const MESSAGE* pMsg)
      {
         return   ::win::thread::ProcessWndProcException(e, pMsg);
      }


      // Advanced: handling messages sent to message filter hook
      bool application::ProcessMessageFilter(i32 code, MESSAGE * pMsg)

      {
         return  ::win::thread::ProcessMessageFilter(code, pMsg);

      }


      // Advanced: access to GetMainWnd()
      __pointer(::user::primitive) application::GetMainWnd()
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
      // 'delete this' only if m_bAutoDelete == true

      bool application::DispatchThreadMessageEx(MESSAGE* msg)  // helper
      {
         return ::win::thread::DispatchThreadMessageEx(msg);
      }*/

   /*   ::draw2d::graphics * application::graphics_from_os_data(void * pdata)
      {
         return ::win::graphics::from_handle((HDC) pdata);
      }*/

   void application::show_wait_cursor(bool bShow)
   {

   }

//   ::user::primitive * application::window_from_os_data(void * pdata)
//   {
//      return nullptr;
//   }

//   ::user::primitive * application::window_from_os_data_permanent(void * pdata)
//   {
//      return nullptr;
//   }

//   ::thread * application::GetThread()
//   {
//      if(::get_task() == nullptr)
//         return nullptr;
//      else
//         return ::get_task();
//   }

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
//        // return;
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
//   /*   char szBuff[_MAX_PATH];
//      ::u32 dwRet = ::GetModuleFileName(m_hInstance, szBuff, _MAX_PATH);
//      ASSERT( dwRet != 0 && dwRet != _MAX_PATH );
//      if( dwRet == 0 || dwRet == _MAX_PATH )
//         __throw(apex_exception());*/
//
//      /*
//      char * pszExt = ::PathFindExtension(szBuff);

//      ASSERT(pszExt != nullptr);

//      if( pszExt == nullptr )

//         __throw(apex_exception());
//
//      ASSERT(*pszExt == '.');

//      *pszExt = 0;       // no suffix

//      */
//
//      //string strExeName;
//      //string strTitle = System->load_string("System->title");
//      // get the exe title from the full path name [no extension]
//      //strExeName = System->get_module_title();
//
//      m_hthread      =  ::GetCurrentThread();
//
//   }



//   void application::get_time(struct timeval * ptimeval)
//   {
//
//      gettimeofday(ptimeval, nullptr);
//
//   }


//   void application::set_env_var(const string & payload,const string & value)
//   {
//#if (defined(SOLARIS8) || defined(SOLARIS))
//      {
//         static std::collection::map<string, char *> vmap;
//         if (vmap.find(payload) != vmap.end())
//         {
//            delete[] vmap[::payload];
//         }
//         vmap[::payload] = new char[payload.get_length() + 1 + value.get_length() + 1];
//         sprintf(vmap[::payload], "%s=%s", payload, value);
//         putenv( vmap[::payload] );
//      }
//#elif defined _WIN32
//      {
//         string slask = payload + "=" + value;
//         _putenv( (const char *)slask);
//      }
//#else
//      setenv(payload, value, 1);
//#endif
//   }


//   ithread_t application::get_thread_id()
//   {
//
//      return ::pthread_self();
//
//   }


//   bool application::do_request(::create * pcreate)
//   {
//
//      if(::is_null(pcreate))
//      {
//
//         return false;
//
//      }
//
////      m_pcommand =  pdata;
//
//      string strCmdLine          = pdata->m_strCommandLine;
//
//      get_context_application()->SetCurrentHandles();
//
//      return true;
//
//   }


//   string system::draw2d_get_default_library_name()
//   {
//
//      return "draw2d_cairo";
//
//   }


   string application::multimedia_audio_get_default_library_name()
   {

      return "audio_alsa";

   }


   string application::multimedia_audio_mixer_get_default_library_name()
   {

      return "audio_mixer_alsa";

   }


   string application::veriwell_multimedia_music_midi_get_default_library_name()
   {

      return "music_midi_alsa";

   }


   bool application::os_on_start_application()
   {

//   #ifndef RASPBIAN
//
//      try
//      {
//
//         auto pfile = __create_new < ::linux::desktop_file >();
//
//         pfile->create();
//
//         pfile->write();
//
//      }
//      catch(...)
//      {
//
//         TRACE("Could not create .desktop shortcut file for the Linux Application for the current user.");
//
//      }
//
//      #endif

      return true;

   }


} // namespace linux



