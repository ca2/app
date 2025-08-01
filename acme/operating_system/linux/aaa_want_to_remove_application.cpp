#include "framework.h"
//#include "acme/node/ansios/ansios.h"
#include "linux.h"

//#include <X11/cursorfont.h>
#include <sys/time.h>
#include <link.h>
#include "acme/operating_system/ansi/_pthread.h"


namespace acme
{

//   application::application(::particle * pparticle) :
//      ::matter(pparticle)
//   {
//
////      m_pthreadimpl.create(this);
////      m_pthreadimpl->m_pthread = this;
//
//  //m_nSafetyPoolSize = 512;        // default size
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


//   ::acme::document * application::_001opendocumentfile(::payload varfile)
//   {
//
//      return m_pimpl->_001opendocumentfile(varfile);
//
//   }
//

   void application::_001EnableShellOpen()
   {
// xxx       ASSERT(m_atomApp == nullptr && m_atomSystemTopic == nullptr); // do once

// xxx       m_atomApp            = ::GlobalAddAtomW(utf8_to_unicode(m_strAppName));
// xxx       m_atomSystemTopic    = ::GlobalAddAtomW(L"system");
   }

//   bool application::_001OnDDECommand(const ::scoped_string & scopedstr)

//   {
//      __UNREFERENCED_PARAMETER(pcsz);

//      return false;
//   }

//   HINSTANCE application::GetHinstance()
//   {
//      return nullptr;
//   }

   string application::get_version()
   {
      return "";

      throw ::exception(todo);

      /*      char pszModuleFilePath[MAX_PATH + 1];

            GetModuleFileName(nullptr, pszModuleFilePath, MAX_PATH + 1);


            unsigned int dw;

            unsigned int dwResSize = GetFileVersionInfoSize(
               pszModuleFilePath,

               &dw);


            if(dwResSize > 0)
            {
               LPVOID pdata = aaa_primitive_new unsigned char[dwResSize];

               if(GetFileVersionInfo(
                  pszModuleFilePath,

                  0,
                  dwResSize,
                  pdata))

               {
                  unsigned int cbTranslate;
                  struct LANGANDCODEPAGE {
                     unsigned short wLanguage;
                     unsigned short wCodePage;
                  } *pTranslate;


                  // read the list of languages and code pages.

                  VerQueryValue(pdata,

                     TEXT("\\VarFileInfo\\Translation"),
                     (LPVOID*)&pTranslate,

                     &cbTranslate);

                  string strKey;
                  //for( i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ )
                  for(int i=0; i < 1; i++ )
                  {
                     char * psz;

                     unsigned int uSize;

                     strKey.formatf(
                        TEXT("\\StringFileInfo\\%04x%04x\\FileDescription"),
                        pTranslate[i].wLanguage,

                        pTranslate[i].wCodePage);





                     strKey.formatf(
                        TEXT("\\StringFileInfo\\%04x%04x\\FileVersion"),
                        pTranslate[i].wLanguage,

                        pTranslate[i].wCodePage);


                     // Retrieve file description for language and code page "i".
                     VerQueryValue(pdata,

                        (char *) (const char *) strKey,
                        (LPVOID *)&psz,

                        &uiSize);


                     string strVersion(scopedstr, uiSize);


                     return strVersion;
                  }
               }
               delete [] (unsigned char *) pdata;

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





   bool application::impl_process_init()
   {

      return true;

   }


   bool application::impl_init1()
   {

//      set_run();

      return true;

   }


   bool application::impl_init2()
   {

      return true;

   }


   bool application::impl_init3()
   {

      return true;

   }


   void application::impl_term1()
   {


   }


   void application::impl_term2()
   {


   }


   void application::impl_term3()
   {


   }


   void application::impl_process_term() // default will 'delete this'
   {

      // avoid calling CloseHandle() on our own thread handle
      // during the thread destructor
      set_os_data(nullptr);

      //m_pimpl->m_bRun = false;
      //LNX_THREAD(m_pimpl->::thread_pointer::m_p)->m_bRun = false;

      //int iRet = ::platform::application::term_instance();

      //::ca2pointer<::ca2::application>::destroy();



      //return 0;
   }
   /*
      // Advanced: exception handling
      LRESULT application::ProcessWndProcException(::exception::acme* e, const MESSAGE* pMsg)
      {
         return   ::win::thread::ProcessWndProcException(e, pMsg);
      }


      // Advanced: handling messages sent to message filter hook
      bool application::ProcessMessageFilter(int code, LPMESSAGE pMsg)

      {
         return  ::win::thread::ProcessMessageFilter(code, pMsg);

      }


      // Advanced: access to GetMainWnd()
      ::pointer<::user::interaction_base>application::GetMainWnd()
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

//   void application::show_wait_cursor(bool bShow)
//   {
//
//   }

//   ::user::interaction_base * application::window_from_os_data(void * pdata)
//   {
//      return nullptr;
//   }

//   ::user::interaction_base * application::window_from_os_data_permanent(void * pdata)
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
//      //ASSERT(this == ::windows_definition::CurrentWinApp);
//      //if(::windows_definition::CurrentAppName != nullptr)
//        // return;
//      //ASSERT(::windows_definition::CurrentAppName == nullptr);
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
//   /*   char szBuff[_MAX_PATH];
//      unsigned int dwRet = ::GetModuleFileName(m_hInstance, szBuff, _MAX_PATH);
//      ASSERT( dwRet != 0 && dwRet != _MAX_PATH );
//      if( dwRet == 0 || dwRet == _MAX_PATH )
//         throw ::exception(aura_exception());*/
//
//      /*
//      char * pszExt = ::PathFindExtension(szBuff);

//      ASSERT(scopedstrExt != nullptr);

//      if( pszExt == nullptr )

//         throw ::exception(aura_exception());
//
//      ASSERT(*pszExt == '.');

//      *pszExt = 0;       // no suffix

//      */
//
//      //string strExeName;
//      //string strTitle = ::acmeacmesystem()->load_string("::acmeacmesystem()->title");
//      // get the exe title from the full path name [no extension]
//      //strExeName = ::acmeacmesystem()->get_module_title();
//
//      m_htask      =  ::GetCurrentThread();
//
//   }




   void application::get_time(struct timeval *point)
   {
#ifdef _WIN32
      FILETIME ft; // Contains a 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601 (UTC).
      GetSystemTimeAsFileTime(&ft);
      unsigned long long tt;
      ::memory_copy(&tt, &ft, sizeof(tt));
      tt /= 10; // make it usecs
      point->tv_sec = (long)tt / 1000000;
      point->tv_usec = (long)tt % 1000000;
#else
      gettimeofday(point, nullptr);
#endif
   }

   void application::set_env_var(const string & payload,const string & value)
   {
#if (defined(SOLARIS8) || defined(SOLARIS))
      {
         static std::collection::map<string, char *> vmap;
         if (vmap.find(payload) != vmap.end())
         {
            delete[] vmap[::payload];
         }
         vmap[::payload] = aaa_primitive_new char[payload.get_length() + 1 + value.get_length() + 1];
         sprintf(vmap[::payload], "%s=%s", payload, value);
         putenv( vmap[::payload] );
      }
#elif defined _WIN32
      {
         string slask = payload + "=" + value;
         _putenv( (const char *)slask);
      }
#else
      setenv(payload, value, 1);
#endif
   }


   itask application::get_thread_id()
   {

      return ::pthread_self();

   }


//   bool application::do_request(::request * prequest)
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
//      get_app()->SetCurrentHandles();
//
//      return true;
//
//   }


   string application::draw2d_get_default_implementation_name()
   {

      return system()->implementation_name("draw2d", "cairo");

   }


   string application::multimedia_audio_get_default_implementation_name()
   {

      return system()->implementation_name("audio", "alsa");

   }


   string application::multimedia_audio_mixer_get_default_implementation_name()
   {

      return system()->implementation_name("audio", "xaudio");

   }


   string application::veriwell_multimedia_music_midi_get_default_implementation_name()
   {

      return "music_midi_alsa";

   }


   bool application::os_on_start_application()
   {

   #ifndef RASPBERRYPIOS

      try
      {

         ::linux::desktop_file file(this);

         file.create();

         file.write();

      }
      catch(...)
      {

         informationf("Could not create .desktop shortcut file for the Linux papp for the current user.");

      }

      #endif

      return true;

   }


} // namespace linux

