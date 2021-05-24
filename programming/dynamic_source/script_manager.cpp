#include "framework.h"
#include "_.h"
#include "acme/const/id.h"
#include "aura/user/_user.h"


namespace dynamic_source
{

   
   ::u32 ThreadProcRsa(LPVOID lp);


   //script_instance * get_seed_instance()
   //{
   //   
   //   return thread_property(id_thread_dynamic_source_script_instance).cast < script_instance >();

   //}


   //void set_seed_instance(script_instance * pinstance)
   //{

   //   thread_property(id_thread_dynamic_source_script_instance) = pinstance;

   //}


   script_manager::plugin_map_item::plugin_map_item()
   {

   }


   script_manager::plugin_map_item::plugin_map_item(const plugin_map_item & item)
   {

      operator = (item);

   }


   script_manager::plugin_map_item & script_manager::plugin_map_item::operator = (const plugin_map_item & item)
   {

      m_strHost         = item.m_strHost;
      m_strScript       = item.m_strScript;
      m_strPlugin       = item.m_strPlugin;

      return *this;

   }


   script_manager::script_manager()
   {

      m_posdataNetnodeManager = nullptr;

      defer_create_mutex();
      
      m_bCompiler = true;

      m_iBuildTimeWindow        = 30 * 1000;
      m_iBuildTimeRandomWindow  = 30 * 1000;
      m_iDatabaseWaitTimeOut     = 15 * 1000 * 1000 * 60;

      m_mapIncludeMatchesFileExists.InitHashTable(256 * 1024);
      m_mapIncludeMatchesIsDir.InitHashTable(256 * 1024);
      m_mapIncludeHasScript.InitHashTable(256 * 1024);
      m_mapIncludeExpandMd5.InitHashTable(256 * 1024);
      m_mapSession.InitHashTable(256 * 1024);

      m_strRepos                 = "app-core";
      m_strNamespace             = "netnode"; // default namespace is linked to outer project netnode

#ifdef LINUX

      m_strNetnodePath           = "/netnodenet/";
      m_strNetseedPath           = "/netnodenet/net/";
      m_strNetseedDsCa2Path      = "/netnodenet/net/";

#else

      m_strNetnodePath           = "C:\\netnodenet\\";
      m_strNetseedPath           = "C:\\netnodenet\\net\\";
      m_strNetseedDsCa2Path      = "C:\\netnodenet\\net\\";

#endif

      m_iTunnelPluginCount       = 0;


      m_strSeed = "system/seed";

   }


   script_manager::~script_manager()
   {

   }


   ::e_status script_manager::initialize(::object * pobject)
   {

      auto estatus = ::user::message_window_listener::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }
      
      estatus = __compose_new(m_pmessagequeue);
      
      if(!estatus)
      {
         
         return estatus;
         
      }

      calc_rsa_key();

      estatus = init1();
      if (!estatus)
      {

         return estatus;

      }
      return estatus;

   }


   ::e_status script_manager::init1()
   {

      if(m_bCompiler)
      {

         auto estatus = __construct_new(m_pcache);

         if (!estatus)
         {

            return estatus;

         }

         m_pcache->m_pmanager = this;

         m_pcompiler = __new(script_compiler);

         estatus = m_pcompiler->initialize_dynamic_source_script_compiler(this);

         if (!estatus)
         {

            return estatus;

         }

         m_pcompiler->m_pmanager = this;

         estatus = m_pcompiler->init1();

         if (!estatus)
         {

            return estatus;

         }

      }

#ifdef WINDOWS

      auto pcontext = get_context();

      {

         auto pwatcher = __new(clear_include_matches_file_watcher(this));

         pwatcher->m_pmanager = this;

         auto pcontext = get_context();

         pcontext->m_papexcontext->dir().watcher().add_watch(m_strNetseedDsCa2Path, pwatcher, true);

      }

      ::file::listing listing;

      auto papplication = get_application();

      pcontext->m_papexcontext->dir().ls_dir(listing, m_strNetnodePath);

      forallref(listing)
      {

         if(::str::begins_ci(item.title(),"net-"))
         {

            auto pwatcher = __new(clear_include_matches_file_watcher(this));

            pwatcher->m_pmanager = this;

            pcontext->m_papexcontext->dir().watcher().add_watch(item, pwatcher, true);

         }

      }

#endif

      LoadEnv();

      return true;

   }


   __pointer(script_instance) script_manager::get(const string & strName)
   {

      __pointer(script) pscript;

      return get(strName, pscript);

   }


   __pointer(script_instance) script_manager::get(const string & strName, __pointer(script) & pscript)
   {

      return m_pcache->create_instance(strName, pscript);

   }


   void script_manager::handle(::dynamic_source::httpd_socket * pdssocket)
   {
      
      string strHead;
      
      __pointer(script_instance) pinstance = get(m_strSeed);

      if (!pinstance)
      {

         string strHtml;

         strHtml+="<html>";
         strHtml+="<head>";
         strHtml+="<title>";
         strHtml+="Try again soon";
         strHtml+="</title>";
         strHtml+="</head>";
         strHtml+="<body>";
         strHtml+="<h1>";
         strHtml+="Try again soon";
         strHtml+="</h1>";
         strHtml +="<p>";
         strHtml += "Root Script (seed) failed to compile.";
         strHtml += "</p>";
         strHtml+="</body>";
         strHtml+="</html>";

         pdssocket->m_response.file()->print(strHtml);

         return;

      }

      auto pmain = __create < script_main >();

      pmain->m_pscript2 = pinstance->m_pscript2;

      pmain->run_property("on_create");

      pmain->call_routine(CREATE_ROUTINE);

      pmain->m_pmain = pmain;
      
      pmain->m_psocket2 = pdssocket;

      pmain->m_pmanager2 = this;

      pmain->m_pscript2 = pinstance->m_pscript2;

      pmain->init1();

      pinstance->initialize(pmain);

      pinstance->run_property("on_create");

      pinstance->call_routine(CREATE_ROUTINE);

      auto pthread = pdssocket->get_thread();

      if (::is_set(pthread))
      {

         pthread->m_pobjectScript = pinstance;

         //if (::is_set(pinstance))
         //{

         //   pinstance->set_context_thread(pthread OBJ_REF_DBG_COMMA_P_FUNCTION_LINE(pinstance));

         //}

      }

      if (pinstance != nullptr)
      {
         
         pinstance->m_strDebugRequestUri = pdssocket->inattr("request_uri");

         if (pinstance->m_strDebugRequestUri.find_ci("google") > 0)
         {

            output_debug_string("resident");

         }

         pinstance->m_strDebugThisScript = m_strSeed;
         
         pinstance->dinit();

      }

      if(pinstance != nullptr)
      {
         
         pinstance->m_pmain->main_initialize();
         
         if (pinstance->m_iDebug > 0)
         {

            pinstance->print(pinstance->m_pscript2->m_strError);

         }

         if (!pinstance->m_pscript2->HasCompileOrLinkError())
         {

            try
            {

               pinstance->run();

            }
            catch (const exit_exception &)
            {

            }
            catch (const ::exception::exception & e)
            {

               string str = e.get_message();

               pinstance->dprint("str");

               TRACE("Error: exception * at script_manager::handle run");

               TRACE("%s", str.c_str());

            }
            catch (...)
            {

               TRACE("Error: Exception at script_manager::handle run");

            }

         }

         try
         {
            pinstance->m_pmain->main_finalize();
         }
         catch(const ::exception::exception &)
         {
            TRACE("Error: exception at script_manager::handle main_finalize");
         }
         catch(...)
         {
            TRACE("Error: Exception at script_manager::handle main_finalize");
         }


      }
      //else
      //{
      //   pdssocket->write("<html>");
      //   pdssocket->write("<head>");.
      //   pdssocket->write("<title>");
      //   pdssocket->write("Try again soon");
      //   pdssocket->write("</title>");
      //   pdssocket->write("</head>");
      //   pdssocket->write("<body>");
      //   pdssocket->write("<h1>");
      //   pdssocket->write("Try again soon");
      //   pdssocket->write("</h1>");
      //   pdssocket->write("</body>");
      //   pdssocket->write("</html>");
      //}

      //auto pinst2 = pinstance.m_p;

      //pinst2->finalize();

      //if (pinst2->m_countReference > 2)
      //{

      //   pinstance.m_p = nullptr;



      //   try
      //   {
      //      pinst2->release();
      //   }
      //   catch (const ::exception::exception&)
      //   {
      //      TRACE("Error: exception at script_manager::handle destroy pinstance");
      //   }
      //   catch (...)
      //   {
      //      TRACE("Error: Exception at script_manager::handle destroy pinstance");
      //   }
      //   __check_pending_releases(pinst2);

      //}


      try
      {
         pinstance.release();
      }
      catch (const ::exception::exception&)
      {
         TRACE("Error: exception at script_manager::handle destroy pinstance");
      }
      catch (...)
      {
         TRACE("Error: Exception at script_manager::handle destroy pinstance");
      }

      auto pmain2 = pmain.m_p;

      pmain2->finalize();

      if (pmain2->m_countReference > 0)
      {

         pmain.m_p = nullptr;

         auto c = pmain2->release();

         if (c > 0)
         {

            __check_pending_releases(pmain2);

         }

      }



   }


   ::payload script_manager::get_output_internal(::dynamic_source::script_interface * pinstanceParent, const string & strNameParam)
   {

      string strName = ::str::get_word(strNameParam, "?");

      if(strName.is_empty())
      {

         if(pinstanceParent != nullptr)
         {

            if(pinstanceParent->m_pmain->m_iDebug > 0)
            {

               if(pinstanceParent->m_pscript2->m_streamError.m_p->get_size() > 0)
               {

                  pinstanceParent->m_pmain->netnodesocket()->response().print("script_manager::get_output_internal is_empty script parent" + pinstanceParent->m_pscript2->m_strName);

               }

            }

         }

         return e_type_empty;

      }

      ::payload payload;

      __pointer(script_interface) pimpl;

      __pointer(::dynamic_source::script_instance) pinstance;

      __pointer(script) pscript;

      {

         //auto pmain = pinstanceParent->main();

         pinstance = get(strName, pscript);

         if (pinstance && pinstanceParent && pscript)
         {

            pimpl = ::__create < script_interface >();

            pimpl->m_strNote = "impl://" + pinstance->m_strNote;

            pimpl->initialize(pinstanceParent);

            pimpl->m_pscript2 = pinstance->m_pscript2;

            pimpl->run_property("on_create");
            
            pimpl->call_routine(CREATE_ROUTINE);

            pimpl->init1();

            pinstance->initialize(pimpl);

            pinstance->m_pinstanceParent2 = pinstanceParent;

            pinstance->run_property("on_create");
            
            pinstance->call_routine(CREATE_ROUTINE);

            if (pinstanceParent->m_pmain->m_iDebug > 0)
            {

               pinstanceParent->m_strDebugRequestUri = pinstanceParent->m_pmain->netnodesocket()->m_request.m_strRequestUri;

               pinstanceParent->m_strDebugThisScript = strName;

               __pointer(::dynamic_source::ds_script) pdsscript = pscript;

               if (pdsscript != nullptr)
               {

                  try
                  {

                     if (pdsscript->m_strError.has_char())
                     {

                        pinstanceParent->file()->print(pscript->m_strError);

                     }

                  }
                  catch (...)
                  {

                  }

               }

            }

         }

         if (pinstance == nullptr || pscript == nullptr)
         {

            return false;

         }

         if (pscript->HasCompileOrLinkError())
         {

            try
            {

               pinstance->finalize();

            }

            catch (...)
            {

            }
            return false;

         }

         pinstance->dinit();

         payload = pinstance->call_run();

         try
         {

            pinstance->finalize();

         }
         catch (...)
         {

         }

      }

      //auto pinst2 = pinstance.m_p;

      //if (pinst2->m_countReference > 1)
      //{

      //   pinstance.m_p = nullptr;

      //   //pinst2->release();

      //   __check_pending_releases(pinst2);

      //}

 /*     auto pimpl2 = pimpl.m_p;

      pimpl->finalize();*/

      //if (pimpl2->m_countReference > 1)
      //{

      //   pimpl.m_p = nullptr;

      //   //pimpl2->release();

      //   __check_pending_releases(pimpl2);

      //}

      return payload;

   }


   void script_manager::LoadEnv()
   {
      /*char * buf;
      u32 dwSize = GetDllDirectory(nullptr, nullptr);
      buf = new char[dwSize + 1024];
      GetDllDirectory(dwSize + 1024, buf);
      TRACE(buf);
      //SetDllDirectory(buf);
      GetDllDirectory(dwSize + 1024, buf);
      TRACE(buf);
      del*/

      auto pcontext = get_context();


      ::file::path str;
      str = pcontext->m_papexcontext->dir().module();
      str.go_up(2);
      str = str/ "stage\\basis";
      str = ";" + str;
      ::file::path str2;
      str2 = pcontext->m_papexcontext->dir().module();
      str2.go_up(2);
      str2 = str2/ "netnode\\library\\include";
      str2 = ";" + str2;
      str = str + str2;

      string strNew;
#ifdef WINDOWS_DESKTOP
      u32 dwSize = GetEnvironmentVariableW(L"PATH", nullptr, 0);
      LPWSTR lpsz = new wchar_t[dwSize + 1024];
      dwSize = GetEnvironmentVariableW(L"PATH", lpsz, dwSize + 1024);
      strNew = lpsz;
      delete lpsz;
#elif defined(_UWP)

      __throw(todo);

#else
      strNew = getenv("PATH");
#endif
      strNew += str;
#ifdef WINDOWS_DESKTOP
      SetEnvironmentVariableW(L"PATH", wstring(strNew));
#elif defined(_UWP)

      __throw(todo);

#else
      setenv("PATH", strNew, 1);
#endif


      // just verifying

#ifdef WINDOWS_DESKTOP
      dwSize = GetEnvironmentVariableW(L"PATH", nullptr, 0);
      lpsz = new wchar_t[dwSize + 1024];
      dwSize = GetEnvironmentVariableW(L"PATH", lpsz, dwSize + 1024);
      TRACE(lpsz);
      delete lpsz;
#elif defined(_UWP)

      __throw(todo);

#else
      //      LPCTSTR pcsz = getenv("PATH");
#endif

      on_load_env();

   }


   void script_manager::run(const char * lpcszName)
   {
      
      auto pmemfile = create_memory_file();

      script_instance * pinstance = get(lpcszName);

      if(pinstance != nullptr)
      {

         pinstance->m_pscript2->run(pinstance);

      }

   }


   string script_manager::get_library_build_log()
   {
      
      //string_stream str;

      //POSITION pos = m_pcompiler->m_mapLib.get_start_position();
      //while(pos != nullptr)
      {
//      library_class * plib;
//      string strClass;
//         m_pcompiler->m_mapLib.get_next_assoc(pos, strClass, (void * &) plib);
//         memfile.transfer_from(plib->m_memfileError);
      }

      //str << m_strPersistentError;

      //return str;

      return m_strPersistentError;

   }


   void script_manager::clear_include_matches(::file::path path)
   {

      try
      {
         single_lock synchronouslock(&m_mutexIncludeMatches, true);

         try
         {

            m_mapIncludeMatchesFileExists.erase_key(path);

         }
         catch (...)
         {

         }

         try
         {

            m_mapIncludeMatchesIsDir.erase_key(path);

         }
         catch (...)
         {

         }

      }
      catch (...)
      {

      }

      try
      {

         single_lock synchronouslock(&m_mutexIncludeExpandMd5, true);

         m_mapIncludeExpandMd5.erase_key(path);

      }
      catch (...)
      {

      }

   }


   void script_manager::clear_include_matches()
   {

      try
      {
         single_lock synchronouslock(&m_mutexIncludeMatches, true);

         try
         {

            m_mapIncludeMatchesFileExists.erase_all();

         }
         catch(...)
         {

         }

         try
         {

            m_mapIncludeMatchesIsDir.erase_all();

         }
         catch(...)
         {

         }

      }
      catch(...)
      {

      }

      try
      {

         single_lock synchronouslock(&m_mutexIncludeExpandMd5, true);

         m_mapIncludeExpandMd5.erase_all();

      }
      catch(...)
      {

      }


   }

   bool script_manager::include_matches_file_exists(const string & strPath)
   {

      auto pcontext = get_context();
      single_lock synchronouslock(&m_mutexIncludeMatches, true);
      string_map < bool >::pair * ppair = m_mapIncludeMatchesFileExists.plookup(strPath);
      if (ppair != nullptr)
      {

         return ppair->element2();

      }

      bool bFileExists = pcontext->m_papexcontext->file().exists(strPath);
      
      m_mapIncludeMatchesFileExists.set_at(strPath, bFileExists);

      return bFileExists;

   }




   void script_manager::set_include_matches_file_exists(const string & strPath, bool bFileExists)
   {
      single_lock synchronouslock(&m_mutexIncludeMatches, true);
      m_mapIncludeMatchesFileExists.set_at(strPath, bFileExists);
   }

   bool script_manager::include_matches_is_dir(const string & strPath)
   {
      single_lock synchronouslock(&m_mutexIncludeMatches, true);
      string_map < bool >::pair * ppair = m_mapIncludeMatchesIsDir.plookup(strPath);

      auto pcontext = get_context();

      if (ppair != nullptr)
      {
         return ppair->element2();
      }

      bool bIsDir = pcontext->m_papexcontext->dir().is(strPath);
         m_mapIncludeMatchesIsDir.set_at(strPath, bIsDir);
         return bIsDir;
   }

   bool script_manager::include_has_script(const string & strPath)
   {

      if(strPath.is_empty())
         return false;

      single_lock synchronouslock(&m_mutexIncludeHasScript, true);
      string_map < bool >::pair * ppair = m_mapIncludeHasScript.plookup(strPath);
      if (ppair != nullptr)
      {

         return ppair->element2();

      }
      
      auto pcontext = get_context();

         // roughly detect this way: by finding the <?

         bool bHasScript = pcontext->m_papexcontext->file().as_string(strPath).find("<?") >= 0;

         m_mapIncludeHasScript.set_at(strPath, bHasScript);

         return bHasScript;

      
   }


   string script_manager::include_expand_md5(const string & strPath)
   {
      single_lock synchronouslock(&m_mutexIncludeExpandMd5, true);
      return m_mapIncludeExpandMd5[strPath];
   }

   void script_manager::set_include_expand_md5(const string & strPath, const string & strMd5)
   {
      single_lock synchronouslock(&m_mutexIncludeExpandMd5, true);
      m_mapIncludeExpandMd5[strPath] = strMd5;
   }


   script_manager::clear_include_matches_file_watcher::clear_include_matches_file_watcher(::object * pobject)
   {

      initialize(pobject);

   }


   void script_manager::clear_include_matches_file_watcher::handle_file_action(::file::action * paction)
   {

      ::file::path path;

      path = paction->m_pathFolder;

      path /= paction->m_pathFile;

      if (path.contains_ci("\\.git\\") || path.contains_ci("/.git/"))
      {

         return;

      }

      if (path.contains_ci("\\.git") || path.contains_ci("/.git"))
      {

         return;

      }

      if (path.ends_ci(".tmp"))
      {

         return;

      }

      // todo (camilo) equal file comparison, for clearing include matching only changed files
      try
      {

         m_pmanager->clear_include_matches(path);

      }
      catch(...)
      {

      }

      try
      {

         synchronous_lock synchronouslock(&m_pmanager->m_mutexShouldBuild);

         m_pmanager->m_mapShouldBuild[path] = true;

      }
      catch (...)
      {

      }

   }


   ::file::path script_manager::real_path(const ::file::path & strBase,const ::file::path & str)
   {
      ::file::path strRealPath = strBase/ str;
      if(include_matches_file_exists(strRealPath))
         return strRealPath;
      else if(include_matches_is_dir(strRealPath))
         return strRealPath;
      else
         return "";
   }

#ifdef WINDOWS
#define is_absolute_path(psz) ((isalpha(psz[0]) && psz[1] == ':') \
   || (psz[0] == '\\' && psz[1] == '\\'))
#else
#define is_absolute_path(psz) (psz[0] == '/')
#endif

   ::file::path script_manager::real_path(const ::file::path & str)
   {
#ifdef WINDOWS
      if(is_absolute_path(str))
      {
         if(include_matches_file_exists(str))
            return str;
         return "";
      }
      else
      {
         return real_path(m_strNetseedDsCa2Path, str);
      }
#else
      if(is_absolute_path(str))
      {
         if(include_matches_file_exists(str))
            return str;
         return real_path(m_strNetseedDsCa2Path, str);
      }
      else
      {
         return real_path(m_strNetseedDsCa2Path, str);
      }
#endif
   }


   __pointer(::dynamic_source::session) script_manager::get_session(const char * pszId)
   {

      single_lock synchronouslock(&m_mutexSession, true);

      auto ppair = m_mapSession.plookup(pszId);

      if (ppair != nullptr)
      {

         if (::datetime::time::get_current_time() < ppair->element2()->m_timeExpiry)
         {

            ppair->element2()->m_timeExpiry = ::datetime::time::get_current_time() + minutes(9);

            return ppair->element2();

         }

         ppair->element2().m_p->~session();

#undef new
         ::new(ppair->element2().m_p) ::dynamic_source::session();
#define new ACME_NEW

         ppair->element2()->initialize_dynamic_source_session(pszId, this);

         return ppair->element2();

      }

      auto psession = __new(::dynamic_source::session);

      psession->initialize_dynamic_source_session(pszId, this);

      psession->m_timeExpiry = ::datetime::time::get_current_time() + minutes(9);

      m_mapSession.set_at(pszId, psession);

      return psession;

   }


   void script_manager::defer_clean_session()
   {
      
      single_lock synchronouslock(&m_mutexSession, true);
      
      ::datetime::time time;
      
      time = ::datetime::time::get_current_time();
      
      auto passoc = m_mapSession.get_start();
      
      decltype(passoc) passocNext;

      while(passoc != nullptr)
      {

         passocNext = passoc->m_pnext;

         if(passoc->element2().is_null())
         {

            m_mapSession.erase_item(passoc);

         }
         else if(passoc->element2()->get_ref_count() <= 1)
         {

            if(passoc->element2()->m_timeExpiry < time)
            {

               m_mapSession.erase_item(passoc);

            }

         }

         passoc = passocNext;

      }

   }


   ::u32 ThreadProcRsa(LPVOID lp)
   {
      script_manager * pmanager = (script_manager *) lp;
      pmanager->calc_rsa_key();
      return 0;
   }

   __pointer(::crypto::rsa) script_manager::get_rsa_key()
   {

      /*if(m_millisLastRsa.elapsed() > (5000))
      {

         calc_rsa_key();

         m_millisLastRsa= ::millis::now();

      }*/

      single_lock synchronouslock(&m_mutexRsa, true);

      auto psystem = m_psystem->m_paurasystem;

      auto pcrypto = psystem->crypto();

      return pcrypto->generate_rsa_key();

   }


   string script_manager::get_rsa_key(script_interface * pscriptinterface)
   {

      pscriptinterface->session_id(); // trigger session creation;

      __pointer(::crypto::rsa) prsa = get_rsa_key();

      pscriptinterface->set_session_value("rsa", prsa);

      return prsa->n;

   }




   void script_manager::calc_rsa_key()
   {

      auto psystem = m_psystem->m_paurasystem;

      auto pcrypto = psystem->crypto();

      auto prsa = pcrypto->generate_rsa_key();

      single_lock synchronouslock(&m_mutexRsa, true);

      m_rsaptra.add(prsa);

      if(m_rsaptra.get_size() > 23)
      {

         m_rsaptra.erase_at(0);

      }

   }

   void script_manager::on_load_env()
   {
   }

   void script_manager::register_plugin(const string & strHost, const string & strScript, const string & strName, script * pscript)
   {

      plugin_map_item item;

      item.m_strHost       = strHost;
      item.m_strScript     = strScript;
      item.m_strPlugin     = strName;

      m_pluginmapitema.add(new plugin_map_item(item));

      m_pcache->register_script(strName, pscript);


   }

   string script_manager::get_root_plugin()
   {
      return "netnode://script_seed";
   }


   void script_manager::wait_link_out(const char * pszServer, ::sockets::link_in_socket * pinsocket)
   {

      while(true)
      {

         if(has_link_out_link(pszServer, pinsocket, nullptr))
            break;

         sleep(100_ms);

      }

   }

   bool script_manager::has_link_out_link(const char * pszServer, ::sockets::link_in_socket * pinsocket, ::sockets::httpd_socket * phttpdsocket)
   {

      single_lock synchronouslock(&m_mutexOutLink, true);

      auto ppair = m_mapOutLink.plookup(pszServer);

      ::sockets::link_out_socket * psocket = nullptr;

      if(ppair != nullptr)
      {

         psocket = ppair->element2();

         if(psocket != nullptr)
         {

            single_lock sl2(&m_mutexInLink, true);

            if(phttpdsocket != nullptr)
            {

               pinsocket->m_in = phttpdsocket;

               ASSERT(pinsocket->m_pmemfileInput != nullptr);

               pinsocket->m_pmemfileInput->from(phttpdsocket->m_pmemfileInput);

               pinsocket->server_to_link_in(phttpdsocket);

               phttpdsocket->m_bEnd = true;

            }

            m_mapInLink.set_at(psocket, pinsocket);

         }

         m_mapOutLink.erase_key(pszServer);

      }

      if(psocket == nullptr)
         return false;

      return true;

   }

   ::sockets::link_in_socket * script_manager::get_link_in(const char * pszServer, ::sockets::link_out_socket * poutsocket)
   {

      single_lock sl2(&m_mutexInLink, true);

      auto ppair = m_mapInLink.plookup(poutsocket);

      {

         single_lock sl3(&m_mutexTunnel, true);

         tunnel_map_item item;

         item.m_strServer    = pszServer;
         item.m_tick.Now();

         m_mapTunnel.set_at(pszServer, item);

      }

      if(ppair == nullptr)
         return nullptr;

      ::sockets::link_in_socket * pinsocket = ppair->element2();

      m_mapInLink.erase_key(poutsocket);

      return pinsocket;

   }


   bool script_manager::is_online(const char * pszServer)
   {

      single_lock synchronouslock(&m_mutexTunnel, true);

      string_map < tunnel_map_item >::pair * ppair = m_mapTunnel.plookup(pszServer);

      if(ppair == nullptr)
         return false;

      if (ppair->element2().m_tick.elapsed().seconds() > 60)
      {

         return false;

      }

      return true;

   }


   ::sockets::link_out_socket * script_manager::create_link_out(const char * pszServer, ::sockets::httpd_socket * phttpdsocket)
   {

      ::sockets::link_out_socket * psocket = new sockets::link_out_socket();

      //psocket->m_phandler = phttpdsocket->m_phandler;

      psocket->m_psockethandler = phttpdsocket->m_psockethandler;

      {

         single_lock synchronouslock(&m_mutexTunnel, true);

         tunnel_map_item item;

         item.m_strServer    = pszServer;
         item.m_tick.Now();

         m_mapTunnel.set_at(pszServer, item);

      }

      {

         single_lock synchronouslock(&m_mutexOutLink, true);
         m_mapOutLink.set_at(pszServer, psocket);

      }

      return psocket;

   }

   size_i32 script_manager::get_image_size(const ::file::path & strFile)
   {

      single_lock synchronouslock(&m_mutexImageSize, false);

      synchronouslock.lock();

      ::size_i32 size;

      if(m_mapImageSize.lookup(strFile, size))
         return size;

      synchronouslock.unlock();

      size.cx = 49;

      size.cy = 49;

      if(extract_image_size(strFile, &size))
      {

         synchronouslock.lock();

         m_mapImageSize.set_at(strFile, size);

         synchronouslock.unlock();

      }

      return size;

   }


   bool script_manager::extract_image_size(const ::file::path & strFile,::size_i32 * psize)
   {

      file_pointer f;

      try
      {

         auto pcontext = get_context();

         f = pcontext->m_papexcontext->file().get_file(strFile, ::file::e_open_binary | ::file::e_open_read | ::file::e_open_share_deny_write);

      }
      catch(...)
      {

         return false;

      }

      if(f.is_null())
      {

         return false;

      }

      // http://www.cplusplus.com/forum/beginner/45217/

      filesize len = f->seek_to_end();

      if(len < 24)
      {
         return false;
      }

      f->seek_to_begin();

      // Strategy:
      // reading GIF dimensions requires the first 10 bytes of the file
      // reading PNG dimensions requires the first 24 bytes of the file
      // reading JPEG dimensions requires scanning through jpeg chunks
      // In all formats, the file is at least 24 bytes big, so we'll read that always
      unsigned char buf[24];

      if(f->read(buf, 24) < 24)
      {
         return false;
      }

      // http://www.64lines.com/jpeg-width-height
      if (buf[0]==0xFF && buf[1]==0xD8 && buf[2]==0xFF && buf[3]==0xE0 && buf[6]=='J' && buf[7]=='F' && buf[8]=='I' && buf[9]=='F' && buf[10]=='\0')
      {
         unsigned short block_length = buf[4] * 256 + buf[5];
         int i = 4;
         while(i < len)
         {

            i += block_length;               //Increase the file index to get to the next block

            if(i >= len)
               return false;   //Check to protect against segmentation faults

            f->seek(i, ::file::seek_begin);

            if(f->read(buf, 4) < 4)
               return false;

            if(buf[i] != 0xFF)
               return false;   //Check that we are truly at the start of another block

            if(buf[i+1] == 0xC0)
            {
               //0xFFC0 is the "Start of frame" marker which contains the file size_i32
               //The structure of the 0xFFC0 block is quite simple [0xFFC0][ushort length][uchar precision][ushort x][ushort y]

               if(f->read(buf, 5) < 5)
                  return false;

               psize->cy = buf[i+1]*256 + buf[i+2];
               psize->cx = buf[i+3]*256 + buf[i+4];
               return true;
            }
            else
            {
               block_length = buf[2] * 256 + buf[3];   //Go to the next block
            }
         }
         return false;
      }

      // JPEG: (first two bytes of buf are first two bytes of the jpeg file; rest of buf is the DCT frame
      if (buf[0]==0xFF && buf[1]==0xD8 && buf[2]==0xFF)
      {

         psize->cy = (buf[7]<<8) + buf[8];

         psize->cx = (buf[9]<<8) + buf[10];

         return true;

      }

      // GIF: first three bytes say "GIF", next three give version number. Then dimensions
      if (buf[0]=='G' && buf[1]=='I' && buf[2]=='F')
      {

         psize->cx = buf[6] + (buf[7]<<8);

         psize->cy = buf[8] + (buf[9]<<8);

         return true;

      }

      // PNG: the first frame is by definition an IHDR frame, which gives dimensions
      if(buf[0]==0x89 && buf[1]=='P' && buf[2]=='N' && buf[3]=='G' && buf[4]==0x0D && buf[5]==0x0A && buf[6]==0x1A && buf[7]==0x0A
            && buf[12]=='I' && buf[13]=='H' && buf[14]=='D' && buf[15]=='R')
      {

         psize->cx = (buf[16]<<24) + (buf[17]<<16) + (buf[18]<<8) + (buf[19]<<0);

         psize->cy = (buf[20]<<24) + (buf[21]<<16) + (buf[22]<<8) + (buf[23]<<0);

         return true;

      }

      return false;

   }

   ::file::path script_manager::get_stage_path(const ::file::path & strScriptPath)
   {

      ::file::path strPath = strScriptPath;

      strPath.replace(":/",".");
      strPath.replace(":\\",".");
      strPath.replace("/",".");
      strPath.replace("\\",".");
#ifdef WINDOWS
      return ::file::path("C:\\netnode")/ m_pcompiler->m_strDynamicSourceStage / m_pcompiler->m_strStagePlatform / m_pcompiler->m_strDynamicSourceConfiguration / strPath;
#else
      ::str::begins_eat(strPath,".");
      //return "/ca2/stage/"+m_pcompiler->m_strStagePlatform+"/","lib" + strPath);
      return ::file::path("/ca2") / m_pcompiler->m_strDynamicSourceStage /  "x86" / "lib" + strPath;
#endif

   }


   ::file::path script_manager::get_full_stage_path(const ::file::path & strScript)
   {

      return get_stage_path(strScript);

   }


   ::file::path script_manager::get_script_path(const ::file::path & strName, const string & strModifier)
   {

      ::file::path strTransformName = strName;

      strTransformName.replace(":","");

      ::file::path strScript;

      strScript = strName.title();

      auto pcontext = get_context();

#ifdef WINDOWS

      return pcontext->m_papexcontext->dir().install()/m_pcompiler->m_strDynamicSourceStage /m_pcompiler->m_strStagePlatform /m_pcompiler->m_strDynamicSourceConfiguration/"dynamic_source" /strTransformName.folder()/strScript + strModifier + ".dll";

#else

      return pcontext->m_papexcontext->dir().install() / m_pcompiler->m_strDynamicSourceStage / m_pcompiler->m_strStagePlatform / m_pcompiler->m_strDynamicSourceConfiguration / "dynamic_source" / strTransformName.folder() / strScript + strModifier + ".so";

#endif

   }


   bool script_manager::should_build(const ::file::path & strScriptPath)
   {

      single_lock synchronouslock(&m_mutexShouldBuild, true);

      bool bShouldBuild = false;

      if(!m_mapShouldBuild.lookup(strScriptPath, bShouldBuild))
         return false;

      return bShouldBuild;

   }

} // namespace dynamic_source





