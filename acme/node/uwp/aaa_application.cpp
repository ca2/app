#include "framework.h"
//#include "universal_windows.h"


//extern thread_local_storage * gen_ThreadData;


//namespace universal_windows
namespace acme
{


   //application::application(::matter * pobject) :
   //   ::matter(pobject)
   //{

   //   m_pthreadimpl.create(this);
   //   m_pthreadimpl->m_pthread = this;

   //   m_psystem = papp->m_psystem;

   //   m_atomApp = m_atomSystemTopic = nullptr;

   //}

   //application::~application()
   //{

   //}


   //void application::_001OnFileNew()
   //{
   //   m_pimpl->_001OnFileNew(nullptr);
   //}

   //::user::document * application::_001OpenDocumentFile(::payload payloadFile)
   //{
   //   return m_pimpl->_001OpenDocumentFile(payloadFile);
   //}

   void application::_001EnableShellOpen()
   {
      //ASSERT(m_atomApp == nullptr && m_atomSystemTopic == nullptr); // do once
      /*
            m_atomApp            = ::GlobalAddAtomW(::str::international::utf8_to_unicode(m_strAppName));
            m_atomSystemTopic    = ::GlobalAddAtomW(L"system");*/
   }

   //bool application::_001OnDDECommand(const char * pcsz)
   //{
   //   __UNREFERENCED_PARAMETER(pcsz);
   //   return false;
   //}

   //HINSTANCE application::GetHinstance()
   //{
   //   return nullptr;
   //}

   string application::get_version()
   {
#ifdef WINDOWS_DESKTOP
      char lpszModuleFilePath[MAX_PATH + 1];
      GetModuleFileName(nullptr, lpszModuleFilePath, MAX_PATH + 1);

      ::u32 dw;

      ::u32 dwResSize = GetFileVersionInfoSize(
                        lpszModuleFilePath,
                        &dw);


      if(dwResSize > 0)
      {
         LPVOID lpdata = new byte[dwResSize];
         if(GetFileVersionInfo(
               lpszModuleFilePath,
               0,
               dwResSize,
               lpdata))
         {
            ::u32 cbTranslate;
            struct LANGANDCODEPAGE
            {
               ::u16 wLanguage;
               ::u16 wCodePage;
            } *lpTranslate;

            // read the list of languages and code pages.

            VerQueryValue(lpdata,
                          TEXT("\\VarFileInfo\\Translation"),
                          (LPVOID*)&lpTranslate,
                          &cbTranslate);

            string strKey;
            //for( i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ )
            for(int i=0; i < 1; i++ )
            {
               char * lpsz;
               ::u32 uSize;

               strKey.format(
               TEXT("\\StringFileInfo\\%04x%04x\\FileDescription"),
               lpTranslate[i].wLanguage,
               lpTranslate[i].wCodePage);




               strKey.format(
               TEXT("\\StringFileInfo\\%04x%04x\\FileVersion"),
               lpTranslate[i].wLanguage,
               lpTranslate[i].wCodePage);

               // Retrieve file description for language and code page "i".
               VerQueryValue(lpdata,
                             (char *) (const char *) strKey,
                             (LPVOID *)&lpsz,
                             &uiSize);


               string strVersion(lpsz, uiSize);

               return strVersion;
            }
         }
         delete [] (LPBYTE) lpdata;
      }


      return "";
#else
      TRACE("returning hard coded default 1.0 version for universal_windows::application::get_version");
      return "1.0";
#endif

   }



   //bool application::impl_process_init()
   //{

   //   return true;
   //}

   //bool application::impl_init1()
   //{

   //   return true;

   //}

   //bool application::impl_init2()
   //{
   //   return true;
   //}

   //bool application::impl_init3()
   //{
   //   return true;
   //}

   // thread termination
   //void application::impl_process_term() // default will 'delete this'
   //{

   //   // avoid calling CloseHandle() on our own thread handle
   //   // during the thread destructor
   //   set_os_data(nullptr);
   //   //i32 iRet = ::acme::application::term_instance();

   //   //pointer < application_base >::destroy();

   //   //return iRet;
   //   //return 0;

   //}

   //void application::impl_term3()
   //{

   //}

   //void application::impl_term2()
   //{

   //}


   //void application::impl_term1()
   //{

   //}

   /*
      // Advanced: exception handling
      LRESULT application::ProcessWndProcException(::exception::acme* e, const MSG* pMsg)
      {
         return   ::universal_windows::thread::ProcessWndProcException(e, pMsg);
      }


      // Advanced: handling messages sent to message filter hook
      bool application::ProcessMessageFilter(int code, LPMSG lpMsg)
      {
         return  ::universal_windows::thread::ProcessMessageFilter(code, lpMsg);
      }


      // Advanced: access to GetMainWnd()
      ::user::interaction* application::GetMainWnd()
      {
         return ::universal_windows::thread::GetMainWnd();
      }



      void application::assert_ok() const
      {
         ::universal_windows::thread::assert_ok();
      }

      void application::dump(dump_context & dumpcontext) const
      {
         ::universal_windows::thread::dump(dumpcontext);
      }


      void application::CommonConstruct()
      {
         ::universal_windows::thread::CommonConstruct();
      }
      void application::Delete()
      {
         ::universal_windows::thread::Delete();
      }
      // 'delete this' only if m_bAutoDelete == true

      bool application::DispatchThreadMessageEx(MSG* msg)  // helper
      {
         return ::universal_windows::thread::DispatchThreadMessageEx(msg);
      }*/

   /*   ::draw2d::graphics * application::graphics_from_os_data(void * pdata)
      {
         return ::universal_windows::graphics::from_handle((HDC) pdata);
      }*/


   /*void application::BaseSetCurrentHandles()
   {

      set_os_data(::get_current_htask());
      set_os_int(::GetCurrentThreadId());


   }
   */


//   void application::get_time(struct timeval *p)
//   {
//#ifdef WINDOWS
//      FILETIME ft; // Contains a 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601 (UTC).
//      GetSystemTimeAsFileTime(&ft);
//      u64 tt;
//      ::memcpy_dup(&tt, &ft, sizeof(tt));
//      tt /= 10; // make it usecs
//      p->tv_sec = (long)tt / 1000000;
//      p->tv_usec = (long)tt % 1000000;
//#else
//      gettimeofday(p, nullptr);
//#endif
//   }

//
//   void application::set_env_var(const string & payload,const string & value)
//   {
//#if (defined(SOLARIS8) || defined(SOLARIS))
//      {
//         static std::map<string, char *> vmap;
//         if (vmap.find(payload) != vmap.end())
//         {
//            delete[] vmap[::payload];
//         }
//         vmap[::payload] = new char[payload.get_length() + 1 + value.get_length() + 1];
//         sprintf(vmap[::payload], "%s=%s", payload, value);
//         putenv( vmap[::payload] );
//      }
//#elif defined WINDOWS_DESKTOP
//      {
//         string slask = payload + "=" + value;
//         _putenv( (const char *)slask);
//      }
//#elif defined _UWP
//
//
//#else
//      setenv(payload, value, 1);
//#endif
//   }


   //u32 application::get_thread_id()
   //{

   //   return ::GetCurrentThreadId();

   //}


   //bool application::request(::create * pdata)
   //{

   //   m_pcommand = pdata;

   //   SetCurrentHandles();

   //   __init_thread();

   //   return true;

   //}





//   void application::show_wait_cursor(bool bShow)
//   {
//
//   }


   string application::veriwell_multimedia_music_midi_get_default_library_name()
   {

      return "music_midi_winrt";

   }


   string application::multimedia_audio_mixer_get_default_library_name()
   {

      return "";

   }


   string application::multimedia_audio_get_default_library_name()
   {

      return "audio_xaudio";

   }


   bool application::os_on_start_application()
   {

      return true;

   }

} // namespace universal_windows



















