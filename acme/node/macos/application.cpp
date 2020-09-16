#include "framework.h"
#include "_.h"
#include "acme/os/_.h"
#include <mach-o/dyld.h>
#include <sys/time.h>


//namespace macos
namespace acme
{


//   application::application(::generic * pobject) :
//      ::generic(pobject)
//   {
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

//   void application::_001EnableShellOpen()
//   {
//      // xxx       ASSERT(m_atomApp == nullptr && m_atomSystemTopic == nullptr); // do once
//
//      // xxx       m_atomApp            = ::GlobalAddAtomW(::str::international::utf8_to_unicode(m_strAppName));
//      // xxx       m_atomSystemTopic    = ::GlobalAddAtomW(L"system");
//   }

//   bool application::_001OnDDECommand(const char * pcsz)
//   {
//      UNREFERENCED_PARAMETER(pcsz);
//      return FALSE;
//   }

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

//   void application::TermThread(HINSTANCE hInstTerm)
//   {
//
//
//   }



//   bool application::impl_process_init()
//   {
//
//      return true;
//
//   }

//   void application::impl_process_term()
//   {
//
//   }
//
//
//   bool application::impl_init1()
//   {
//
//      return true;
//
//   }
//
//
//   void application::impl_term1()
//   {
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
//   void application::impl_term2()
//   {
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
//
//   void application::impl_term3()
//   {
//
//   }

   // thread termination
//   void application::impl_term_instance() // default will 'delete this'
//   {
//
//      // avoid calling CloseHandle() on our own thread handle
//      // during the thread destructor
//      set_os_data(nullptr);
//
//
//  //    i32 iRet = ::acme::application::term_instance();
//
//       int iRet = 0;
//
//      return iRet;
//   }


//   ::thread * application::GetThread()
//   {
//
//      return ::get_thread();
//
//   }
//
//
//   void application::set_thread(::thread * pthread)
//   {
//
//      ::set_thread(pthread);
//
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
//      DWORD dwRet = ::GetModuleFileName(m_hInstance, szBuff, _MAX_PATH);
//      ASSERT( dwRet != 0 && dwRet != _MAX_PATH );
//      if( dwRet == 0 || dwRet == _MAX_PATH )
//      __throw(user_exception());*/
//
//      /*
//      LPTSTR lpszExt = ::PathFindExtension(szBuff);
//      ASSERT(lpszExt != nullptr);
//      if( lpszExt == nullptr )
//      __throw(user_exception());
//
//      ASSERT(*lpszExt == '.');
//      *lpszExt = 0;       // no suffix
//      */
//
////      string strExeName;
//      //string strTitle = System.load_string("System.title");
//      // get the exe title from the full path name [no extension]
//  //    strExeName = System.get_module_title();
//
//
//
//      m_pimpl->set_os_data(::GetCurrentThread());
//
//
//   }



   // void application::get_time(struct timeval *p)
   // {

   //    gettimeofday(p, nullptr);

   // }

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
//
//
//   ITHREAD application::get_thread_id()
//   {
//
//      return ::GetCurrentThreadId();
//
//   }
//
//
////
////   ::estatus     application::do_request(::create * pcreate)
////   {
////
////      //m_pcommand = pcommand;
////
////      if(pcreate != nullptr && is_system())
////      {
////
////         SetCurrentHandles();
////
////         __init_thread();
////
////      }
////
////      return error_failed;
////
////   }
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
//      return "music_midi_core_midi";
//
//   }


//   void application::ShowWaitCursor(bool bShow)
//   {
//
//      UNREFERENCED_PARAMETER(bShow);
//
//   }


//   bool application::os_on_start_application()
//   {
//
//      ::file::path path = Context.file().module();
//
//      path -= 3;
//
//      if(::dir::is(path))
//      {
//
//         ::file::path path2 = ::dir::localconfig() / "monitor-0/desk/2desk" / path.name();
//
//         if(::file_exists(path2))
//         {
//
//            ::unlink(path2);
//
//         }
//
//         auto pathFolder2 = path2.folder();
//
//         ::dir::mk(pathFolder2);
//
//         bool bFilePathIsLink = file_path_is_link(path2);
//
//         if(!bFilePathIsLink && ::dir::is(pathFolder2))
//         {
//
//            ::system("ln -s \"" + path + "\"" + " \"" + path2 + "\"");
//
//         }
//
//      }
//
//      return true;
//
//   }


//   bool application::os_on_start_application()
//   {
//
//      return true;
//
//   }
//

//} // namespace macos

} // namespace acme




//
//bool on_application_menu_action(const char * pszCommand)
//{
//   ::get_context_system()->on_application_menu_action(pszCommand);
//}
