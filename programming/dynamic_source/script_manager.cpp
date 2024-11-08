#include "framework.h"
#include "script_manager.h"
#include "script_cache.h"
#include "script_compiler.h"
#include "script_instance.h"
#include "script_main.h"
#include "ds_script.h"
#include "session.h"
#include "httpd_socket.h"
#include "acme/exception/exit.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"

#include "acme/prototype/string/str.h"
#include "acme/crypto/crypto.h"
#include "acme/crypto/rsa.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/watcher/action.h"
#include "acme/filesystem/watcher/watcher.h"
#include "apex/networking/sockets/link_in_socket.h"
#include "apex/networking/sockets/link_out_socket.h"
#include "acme/constant/id.h"
#include "axis/platform/system.h"


#include "acme/_operating_system.h"
#include "programming/dynamic_source/httpd_socket.h"


namespace dynamic_source
{


   //unsigned int ThreadProcRsa(void  lp);


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


   script_manager::plugin_map_item::plugin_map_item(const plugin_map_item& item)
   {

      operator = (item);

   }


   script_manager::plugin_map_item& script_manager::plugin_map_item::operator = (const plugin_map_item& item)
   {

      m_strHost = item.m_strHost;
      m_strScript = item.m_strScript;
      m_strPlugin = item.m_strPlugin;

      return *this;

   }


   script_manager::script_manager()
   {

      m_pnetnodescriptmanager = nullptr;

      defer_create_synchronization();

      m_bCompiler = true;

      m_timeBuildInterval = 30_s;
      m_timeTimeRandomInterval = 30_s;
      m_timeDatabaseWaitTimeOut = 15_minutes;

      m_mapIncludeMatchesFileExists.InitHashTable(256 * 1024);
      m_mapIncludeMatchesIsDir.InitHashTable(256 * 1024);
      m_mapIncludeHasScript.InitHashTable(256 * 1024);
      m_mapIncludeExpandMd5.InitHashTable(256 * 1024);
      m_mapSession.InitHashTable(256 * 1024);

      m_strRepos = "app-core";
      m_strNamespace = "netnode"; // default namespace is linked to outer project netnode

#ifdef LINUX

      m_strNetnodePath = "/netnodenet/";
      m_strNetseedPath = "/netnodenet/net/";
      m_strNetseedDsCa2Path = "/netnodenet/net/";

#else

      m_strNetnodePath = "C:\\netnodenet\\";
      m_strNetseedPath = "C:\\netnodenet\\net\\";
      m_strNetseedDsCa2Path = "C:\\netnodenet\\net\\";

#endif

      m_iTunnelPluginCount = 0;


      m_strSeed = "system/seed";

      m_timeSessionExpiration = 10_min;

   }


   script_manager::~script_manager()
   {

   }


   void script_manager::initialize(::particle* pparticle)
   {

      //auto estatus = ::user::message_window_listener::initialize(pparticle);
      //auto estatus = 

      ::channel::initialize(pparticle);




      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = __construct_new(m_pmessagequeue);
      //
      //if(!estatus)
      //{
      //   
      //   return estatus;
      //   
      //}


      m_pmutexSession = node()->create_mutex();
      m_pmutexIncludeMatches = node()->create_mutex();
      m_pmutexIncludeHasScript = node()->create_mutex();
      m_pmutexShouldBuild = node()->create_mutex();
      m_pmutexIncludeExpandMd5 = node()->create_mutex();
      m_pmutexOutLink = node()->create_mutex();
      m_pmutexInLink = node()->create_mutex();
      m_pmutexTunnel = node()->create_mutex();
      m_pmutexImageSize = node()->create_mutex();
      m_pmutexSimage = node()->create_mutex();
      m_pmutexSpider = node()->create_mutex();
      m_pmutexRsa = node()->create_mutex();
      m_pmutexMusicDbPool = node()->create_mutex();
      m_pmutexWayDbPool = node()->create_mutex();
      m_pmutexPersistentStr = node()->create_mutex();
      m_pmutexUiRedir = node()->create_mutex();
      m_pmutexTagId = node()->create_mutex();
      m_pmutexTagName = node()->create_mutex();

      calc_rsa_key();

      //estatus = 

      init1();

      //if (!estatus)
      //{

      //   return estatus;

      //}
      fork([this]()
         {

            ::task_set_name("clrses20s");

            while (::task_get_run())
            {

               try
               {

                  defer_clean_session();

               }
               catch (...)
               {


               }

               ::preempt(20_s);

            }

         });

      //return estatus;

   }


   void script_manager::destroy()
   {

      m_pcache.defer_destroy();

      m_pcompiler.defer_destroy();

      ::channel::destroy();

   }


   void script_manager::init1()
   {

      if (m_bCompiler)
      {

         //auto estatus = 

         __construct_new(m_pcache);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         m_pcache->m_pmanager = this;

         m_pcompiler = __allocate script_compiler();

         //estatus = 

         m_pcompiler->initialize_dynamic_source_script_compiler(this);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         m_pcompiler->m_pmanager = this;

         //estatus = 

         m_pcompiler->init1();

         //if (!estatus)
         //{

         //   return estatus;

         //}

      }

#ifdef WINDOWS

      // auto pcontext = get_context();

      {

         auto pwatcher = __allocate clear_include_matches_file_watcher(this);

         pwatcher->m_pmanager = this;

         // auto pcontext = get_context();

         file_watcher()->add_watch(m_strNetseedDsCa2Path, pwatcher, true);

      }

      ::file::listing listing;

      auto papp = get_app();

      listing.set_listing(m_strNetnodePath);

      directory()->enumerate(listing);

      for (auto& path : listing)
      {

         if (case_insensitive_string_begins(path.title(), "net-"))
         {

            auto pwatcher = __allocate clear_include_matches_file_watcher(this);

            pwatcher->m_pmanager = this;

            file_watcher()->add_watch(path, pwatcher, true);

         }

      }

#endif

      LoadEnv();

      //return true;

   }


   ::pointer<script_instance>script_manager::get(const ::string& strName)
   {

      ::pointer<script>pscript;

      return get(strName, pscript);

   }


   ::pointer<script_instance>script_manager::get(const ::string& strName, ::pointer<script>& pscript)
   {

      return m_pcache->create_instance(strName, pscript);

   }


   void script_manager::handle(::dynamic_source::httpd_socket* pdssocket)
   {

      string strHead;

      ::pointer<script_instance>pinstance = get(m_strSeed);

      if (!pinstance)
      {

         string strHtml;

         strHtml += "<html>";
         strHtml += "<head>";
         strHtml += "<title>";
         strHtml += "Try again soon";
         strHtml += "</title>";
         strHtml += "</head>";
         strHtml += "<body>";
         strHtml += "<h1>";
         strHtml += "Try again soon";
         strHtml += "</h1>";
         strHtml += "<p>";
         strHtml += "Root Script (seed) failed to compile.";
         strHtml += "</p>";
         strHtml += "</body>";
         strHtml += "</html>";

         pdssocket->m_response.file()->print(strHtml);

         return;

      }

      auto pmain = __create < script_main >();

      pmain->m_pscript2 = pinstance->m_pscript2;

      pmain->defer_run_property(id_create);

      pmain->call_procedures(id_create);

      pmain->m_pmain = pmain;

      pmain->m_psocket2 = pdssocket;

      pmain->m_pmanager2 = this;

      //::string strUrl;

      //strUrl = pdssocket->request().m_strRequestUri;

      //pmain->m_url = strUrl;

      pmain->m_pscript2 = pinstance->m_pscript2;

      pmain->init1();

      pinstance->m_pmain = pmain;

      pdssocket->m_pscript = pinstance;

      pinstance->initialize(pmain);

      pinstance->defer_run_property(id_create);

      pinstance->call_procedures(id_create);

      auto pthread = pdssocket->get_thread();

      if (::is_set(pthread))
      {

         pthread->m_pobjectScript = pinstance;

         //if (::is_set(pinstance))
         //{

         //   pinstance->set_context_thread(pthread REFERENCING_DEBUGGING_COMMA_P_FUNCTION_LINE(pinstance));

         //}

      }

      if (pinstance != nullptr)
      {

         pinstance->m_strDebugRequestUri = pdssocket->inattr("request_uri");

         if (pinstance->m_strDebugRequestUri.case_insensitive_find_index("google") > 0)
         {

            informationf("resident");

         }

         pinstance->m_strDebugThisScript = m_strSeed;

         pinstance->dinit();

      }

      if (pinstance != nullptr)
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
            catch (const exit_exception&)
            {

            }
            catch (const ::exception& e)
            {

               string str = e.get_message();

               pinstance->dprint("str");

               informationf("Error: exception * at script_manager::handle run");

               informationf("%s", str.c_str());

            }
            catch (...)
            {

               informationf("Error: Exception at script_manager::handle run");

            }

         }

         try
         {

            pinstance->m_pmain->main_finalize();

         }
         catch (const ::exception&)
         {

            informationf("Error: exception at script_manager::handle main_finalize");

         }
         catch (...)
         {

            informationf("Error: Exception at script_manager::handle main_finalize");

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

      //pinst2->destroy();

      //if (pinst2->m_countReference > 2)
      //{

      //   pinstance.m_p = nullptr;



      //   try
      //   {
      //      pinst2->release();
      //   }
      //   catch (const ::exception&)
      //   {
      //      informationf("Error: exception at script_manager::handle destroy pinstance");
      //   }
      //   catch (...)
      //   {
      //      informationf("Error: Exception at script_manager::handle destroy pinstance");
      //   }
      //   __check_pending_releases(pinst2);

      //}


      //try
      //{
      //   pinstance.release();
      //}
      //catch (const ::exception&)
      //{
      //   informationf("Error: exception at script_manager::handle destroy pinstance");
      //}
      //catch (...)
      //{
      //   informationf("Error: Exception at script_manager::handle destroy pinstance");
      //}

      //auto pmain2 = pmain.m_p;

      //pmain2->destroy();

      //if (pmain2->m_countReference > 0)
      //{

      //   pmain.m_p = nullptr;

      //   auto c = pmain2->release();

      //   if (c > 0)
      //   {

      //      __check_pending_releases(pmain2);

      //   }

      //}

      ::defer_destroy_and_release(pmain);

      ::defer_destroy_and_release(pinstance);

      if (::is_set(pthread))
      {

         pthread->m_pobjectScript.release();

      }

   }


   ::payload script_manager::get_output_internal(::dynamic_source::script_interface* pinstanceParent, const ::string& strNameParam)
   {

      string strName = ::str::get_word(strNameParam, "?");

      if (strName.is_empty())
      {

         if (pinstanceParent != nullptr)
         {

            if (pinstanceParent->m_pmain->m_iDebug > 0)
            {

               if (pinstanceParent->m_pscript2->m_textstreamError.m_pfile->size() > 0)
               {

                  pinstanceParent->m_pmain->netnodesocket()->response().m_pmemfileBody->print("script_manager::get_output_internal is_empty script parent" + pinstanceParent->m_pscript2->m_strName);

               }

            }

         }

         return e_type_empty;

      }

      ::payload payload;

      {

         ::pointer<script>pscript;

         {

            ::pointer<script_interface>pimpl;

            ::pointer<::dynamic_source::script_instance>pinstance;

            {

               auto pmain = pinstanceParent->main();

               pinstance = get(strName, pscript);

               if (pinstance == nullptr || pscript == nullptr)
               {

                  return false;

               }

               if (pinstance && pinstanceParent && pscript)
               {

                  pimpl = pmain;

                  //pimpl = ::__create < script_interface >();

                  //pimpl->m_strNote = "impl://" + pinstance->m_strNote;

                  //pimpl->initialize(pinstanceParent);

                  //pimpl->m_pscript2 = pinstance->m_pscript2;

                  //pimpl->run_property(id_create);
                  //
                  //pimpl->call_routine(CREATE_ROUTINE);

                  //pimpl->init1();

                  pinstance->m_pmain = pmain;

                  if (pinstanceParent->m_bOnTopicInclude && !pmain->m_pscriptinterfaceTopic)
                  {

                     pmain->m_pscriptinterfaceTopic = pinstance;

                  }

                  pinstance->initialize(pimpl);

                  pinstance->m_pinstanceParent2 = pinstanceParent;

                  pinstance->defer_run_property(id_create);

                  pinstance->call_procedures(id_create);

                  if (pinstanceParent->m_pmain->m_iDebug > 0)
                  {

                     pinstanceParent->m_strDebugRequestUri = pinstanceParent->m_pmain->netnodesocket()->m_request.m_strRequestUri;

                     pinstanceParent->m_strDebugThisScript = strName;

                     ::pointer<::dynamic_source::ds_script>pdsscript = pscript;

                     if (pdsscript != nullptr)
                     {

                        try
                        {

                           if (pdsscript->m_strError.has_character())
                           {

                              pinstanceParent->output_file()->print(pscript->m_strError);

                           }

                        }
                        catch (...)
                        {

                        }

                     }

                  }

               }

               if (pscript->HasCompileOrLinkError())
               {

                  try
                  {

                     pinstance->destroy();

                  }

                  catch (...)
                  {

                  }
                  return false;

               }

               pinstance->dinit();

               payload = pinstance->run_script();

               try
               {

                  pinstance->destroy();

               }
               catch (...)
               {

               }

            }

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

      pimpl->destroy();*/

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
      unsigned int dwSize = GetDllDirectory(nullptr, nullptr);
      buf = ___new char[dwSize + 1024];
      GetDllDirectory(dwSize + 1024, buf);
      information(buf);
      //SetDllDirectory(buf);
      GetDllDirectory(dwSize + 1024, buf);
      information(buf);
      del*/

      //// auto pcontext = get_context();


      ::file::path str;
      str = directory()->module();
      str.ascend(2);
      str = str / "stage\\basis";
      str = ";" + str;
      ::file::path str2;
      str2 = directory()->module();
      str2.ascend(2);
      str2 = str2 / "netnode\\library\\include";
      str2 = ";" + str2;
      str = str + str2;

      string strNew;
#ifdef WINDOWS_DESKTOP
      unsigned int dwSize = GetEnvironmentVariableW(L"PATH", nullptr, 0);
      LPWSTR lpsz = __raw_new wchar_t[dwSize + 1024];
      dwSize = GetEnvironmentVariableW(L"PATH", lpsz, dwSize + 1024);
      strNew = lpsz;
      delete lpsz;
#elif defined(UNIVERSAL_WINDOWS)

      throw ::exception(todo);

#else
      strNew = getenv("PATH");
#endif
      strNew += str;
#ifdef WINDOWS_DESKTOP
      SetEnvironmentVariableW(L"PATH", wstring(strNew));
#elif defined(UNIVERSAL_WINDOWS)

      throw ::exception(todo);

#else
      setenv("PATH", strNew, 1);
#endif


      // just verifying

#ifdef WINDOWS_DESKTOP

      string strPath = node()->get_environment_variable("PATH");

#elif defined(UNIVERSAL_WINDOWS)

      throw ::exception(todo);

#else
      //      LPCTSTR pcsz = getenv("PATH");
#endif

      on_load_env();

   }


   void script_manager::run(const ::string& lpcszName)
   {

      auto pmemfile = create_memory_file();

      script_instance* pinstance = get(lpcszName);

      if (pinstance != nullptr)
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

         _synchronous_lock synchronouslock(m_pmutexIncludeMatches);

         try
         {

            m_mapIncludeMatchesFileExists.erase_item(path);

         }
         catch (...)
         {

         }

         try
         {

            m_mapIncludeMatchesIsDir.erase_item(path);

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

         _synchronous_lock synchronouslock(m_pmutexIncludeExpandMd5);

         m_mapIncludeExpandMd5.erase_item(path);

      }
      catch (...)
      {

      }

   }


   void script_manager::clear_include_matches()
   {

      try
      {

         _synchronous_lock synchronouslock(m_pmutexIncludeMatches);

         try
         {

            m_mapIncludeMatchesFileExists.erase_all();

         }
         catch (...)
         {

         }

         try
         {

            m_mapIncludeMatchesIsDir.erase_all();

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

         _synchronous_lock synchronouslock(m_pmutexIncludeExpandMd5);

         m_mapIncludeExpandMd5.erase_all();

      }
      catch (...)
      {

      }


   }

   
   bool script_manager::include_matches_file_exists(const ::string& strPath)
   {

      // auto pcontext = get_context();

      _synchronous_lock synchronouslock(m_pmutexIncludeMatches);

      auto p = m_mapIncludeMatchesFileExists.plookup(strPath);

      if (p)
      {

         return p->payload();

      }

      bool bFileExists = file()->exists(strPath);

      m_mapIncludeMatchesFileExists.set_at(strPath, bFileExists);

      return bFileExists;

   }


   void script_manager::set_include_matches_file_exists(const ::string& strPath, bool bFileExists)
   {

      _synchronous_lock synchronouslock(m_pmutexIncludeMatches);

      m_mapIncludeMatchesFileExists.set_at(strPath, bFileExists);

   }


   bool script_manager::include_matches_is_dir(const ::string& strPath)
   {

      _synchronous_lock synchronouslock(m_pmutexIncludeMatches);

      auto p = m_mapIncludeMatchesIsDir.plookup(strPath);

      //// auto pcontext = get_context();

      if (p)
      {
         return p->element2();
      }

      bool bIsDir = directory()->is(strPath);
      m_mapIncludeMatchesIsDir.set_at(strPath, bIsDir);
      return bIsDir;
   }


   bool script_manager::include_has_script(const ::string& strPath)
   {

      if (strPath.is_empty())
      {

         return false;

      }

      _synchronous_lock synchronouslock(m_pmutexIncludeHasScript);

      auto p = m_mapIncludeHasScript.plookup(strPath);

      if (p)
      {

         return p->element2();

      }

      // auto pcontext = get_context();

      // roughly detect this way: by finding the <?

      bool bHasScript = file()->safe_get_string(strPath).contains("<?");

      m_mapIncludeHasScript.set_at(strPath, bHasScript);

      return bHasScript;


   }


   string script_manager::include_expand_md5(const ::string& strPath)
   {
      
      _synchronous_lock synchronouslock(m_pmutexIncludeExpandMd5);

      return m_mapIncludeExpandMd5[strPath];

   }


   void script_manager::set_include_expand_md5(const ::string& strPath, const ::string& strMd5)
   {
   
      _synchronous_lock synchronouslock(m_pmutexIncludeExpandMd5);

      m_mapIncludeExpandMd5[strPath] = strMd5;

   }


   script_manager::clear_include_matches_file_watcher::clear_include_matches_file_watcher(::particle* pparticle)
   {

      m_pmanager = nullptr;

      initialize(pparticle);

   }


   void script_manager::clear_include_matches_file_watcher::operator()(::file::action* paction)
   {

      ::file::path path;

      path = paction->m_pathFolder;

      path /= paction->m_pathFile;

      if (path.case_insensitive_contains("\\.git\\") || path.case_insensitive_contains("/.git/"))
      {

         return;

      }

      if (path.case_insensitive_contains("\\.git") || path.case_insensitive_contains("/.git"))
      {

         return;

      }

      if (path.case_insensitive_ends(".tmp"))
      {

         return;

      }

      // todo (camilo) equal file comparison, for clearing include matching only changed files
      try
      {

         m_pmanager->clear_include_matches(path);

      }
      catch (...)
      {

      }

      try
      {

         _synchronous_lock synchronouslock(m_pmanager->m_pmutexShouldBuild);

         m_pmanager->m_mapShouldBuild[path] = true;

      }
      catch (...)
      {

      }

   }


   ::file::path script_manager::real_path(const ::file::path& strBase, const ::file::path& str)
   {
      ::file::path strRealPath = strBase / str;
      if (include_matches_file_exists(strRealPath))
         return strRealPath;
      else if (include_matches_is_dir(strRealPath))
         return strRealPath;
      else
         return "";
   }

   // #ifdef WINDOWS
   // #define is_absolute_path(psz) ((isalpha(psz[0]) && psz[1] == ':') \
   //    || (psz[0] == '\\' && psz[1] == '\\'))
   // #else
   // #define is_absolute_path(psz) (psz[0] == '/')
   // #endif


   ::file::path script_manager::real_path(const ::file::path& str)
   {

      //#ifdef WINDOWS
      //
      //      if(file_path_is_absolute(str))
      //      {
      //
      //         if(include_matches_file_exists(str))
      //            return str;
      //         return "";
      //      }
      //      else
      //      {
      //         return real_path(m_strNetseedDsCa2Path, str);
      //      }
      //#else
      if (file_path_is_absolute(str))
      {
         if (include_matches_file_exists(str))
            return str;
         return real_path(m_strNetseedDsCa2Path, str);
      }
      else
      {
         return real_path(m_strNetseedDsCa2Path, str);
      }
      //#endif
   }


   ::pointer<::dynamic_source::session>script_manager::get_session(const ::string& pszId)
   {

      _synchronous_lock synchronouslock(m_pmutexSession);

      auto p = m_mapSession.plookup(pszId);

      if (p)
      {

         auto timeNow = ::earth::time::now();

         auto timeExpiry = p->element2()->m_timeExpiry;

         if (timeNow < timeExpiry)
         {

            p->element2()->m_timeExpiry = ::earth::time::now() + m_timeSessionExpiration;

            return p->element2();

         }

         p->element2().m_p->~session();


         ::new(p->element2().m_p) ::dynamic_source::session();
         

         p->element2()->initialize_dynamic_source_session(pszId, this);

         return p->element2();

      }

      auto psession = __allocate ::dynamic_source::session();

      psession->initialize_dynamic_source_session(pszId, this);

      psession->m_timeExpiry = ::earth::time::now() + m_timeSessionExpiration;

      m_mapSession.set_at(pszId, psession);

      return psession;

   }


   void script_manager::defer_clean_session()
   {

      _synchronous_lock synchronouslock(m_pmutexSession);

      ::earth::time timeNow;

      timeNow = ::earth::time::now();

      auto p = m_mapSession.begin();

      while (::is_ok(p))
      {

         auto pNext = p + 1;

         if (p->payload().is_null())
         {

            m_mapSession.erase(p);

         }
         else if (p->element2()->m_countReference <= 1)
         {

            if (timeNow > p->element2()->m_timeExpiry)
            {

               m_mapSession.erase(p);

            }

         }

         p = pNext;

      }

   }


   //   unsigned int ThreadProcRsa(LPVOID lp)
   //   {
   //      script_manager * pmanager = (script_manager *) lp;
   //      pmanager->calc_rsa_key();
   //      return 0;
   //   }

   ::pointer<::crypto::rsa>script_manager::get_rsa_key()
   {

      /*if(m_timeLastRsa.elapsed() > (5000))
      {

         calc_rsa_key();

         m_timeLastRsa= ::time::now();

      }*/

      _synchronous_lock synchronouslock(m_pmutexRsa);

      auto psystem = system();

      auto pcrypto = psystem->crypto();

      return pcrypto->generate_rsa_key();

   }


   string script_manager::get_rsa_key(script_interface* pscriptinterface)
   {

      pscriptinterface->session_id(); // trigger session creation;

      ::pointer<::crypto::rsa>prsa = get_rsa_key();

      pscriptinterface->set_session_payload("rsa", prsa);

      return prsa->n;

   }




   void script_manager::calc_rsa_key()
   {

      auto psystem = system();

      auto pcrypto = psystem->crypto();

      auto prsa = pcrypto->generate_rsa_key();

      _synchronous_lock synchronouslock(m_pmutexRsa);

      m_rsaptra.add(prsa);

      if (m_rsaptra.get_size() > 23)
      {

         m_rsaptra.erase_at(0);

      }

   }

   void script_manager::on_load_env()
   {
   }

   void script_manager::register_plugin(const ::string& strHost, const ::string& strScript, const ::string& strName, script* pscript)
   {

      plugin_map_item item;

      item.m_strHost = strHost;
      item.m_strScript = strScript;
      item.m_strPlugin = strName;

      m_pluginmapitema.add(___new plugin_map_item(item));

      m_pcache->register_script(strName, pscript);


   }

   string script_manager::get_root_plugin()
   {
      return "netnode://script_seed";
   }


   void script_manager::wait_link_out(const ::string& pszServer, ::sockets::link_in_socket* pinsocket)
   {

      while (true)
      {

         if (has_link_out_link(pszServer, pinsocket, nullptr))
            break;

         sleep(100_ms);

      }

   }


   bool script_manager::has_link_out_link(const ::string& pszServer, ::sockets::link_in_socket* pinsocket, ::httpd::socket* phttpdsocket)
   {

      _synchronous_lock synchronouslock(m_pmutexOutLink);

      auto p = m_mapOutLink.plookup(pszServer);

      ::sockets::link_out_socket* psocket = nullptr;

      if (::is_ok(p))
      {

         psocket = p->element2();

         if (psocket != nullptr)
         {

            single_lock sl2(m_pmutexInLink, true);

            if (phttpdsocket != nullptr)
            {

               pinsocket->m_in = phttpdsocket;

               ASSERT(pinsocket->get_input_memory_file() != nullptr);

               pinsocket->get_input_memory_file()->write(phttpdsocket->get_input_memory_file());

               pinsocket->server_to_link_in(phttpdsocket);

               phttpdsocket->set_end();

            }

            m_pmapInLink->set_at(psocket, pinsocket);

         }

         m_mapOutLink.erase_item(pszServer);

      }

      if (psocket == nullptr)
         return false;

      return true;

   }

   ::sockets::link_in_socket* script_manager::get_link_in(const ::string& pszServer, ::sockets::link_out_socket* poutsocket)
   {

      single_lock sl2(m_pmutexInLink, true);

      auto ppair = m_pmapInLink->plookup(poutsocket);

      {

         single_lock sl3(m_pmutexTunnel, true);

         tunnel_map_item item;

         item.m_strServer = pszServer;
         item.m_time.Now();

         m_mapTunnel.set_at(pszServer, item);

      }

      if (::is_ok(ppair))
         return nullptr;

      ::sockets::link_in_socket* pinsocket = ppair->element2();

      m_pmapInLink->erase_item(poutsocket);

      return pinsocket;

   }


   bool script_manager::is_online(const ::string& pszServer)
   {

      _synchronous_lock synchronouslock(m_pmutexTunnel);

      auto p = m_mapTunnel.plookup(pszServer);

      if (::is_end(p))
      {

         return false;

      }

      if (p->payload().m_time.elapsed() > 60_s)
      {

         return false;

      }

      return true;

   }


   ::sockets::link_out_socket* script_manager::create_link_out(const ::string& pszServer, ::httpd::socket* phttpdsocket)
   {

      ::sockets::link_out_socket* psocket = ___new sockets::link_out_socket ();

      //psocket->m_phandler = phttpdsocket->m_phandler;

      psocket->SetSocketHandler(phttpdsocket->socket_handler());

      {

         _synchronous_lock synchronouslock(m_pmutexTunnel);

         tunnel_map_item item;

         item.m_strServer = pszServer;
         item.m_time.Now();

         m_mapTunnel.set_at(pszServer, item);

      }

      {

         _synchronous_lock synchronouslock(m_pmutexOutLink);

         m_mapOutLink.set_at(pszServer, psocket);

      }

      return psocket;

   }


   int_size script_manager::get_image_size(const ::file::path& strFile)
   {

      _single_lock synchronouslock(m_pmutexImageSize);

      synchronouslock._lock();

      ::int_size size;

      if (m_mapImageSize.lookup(strFile, size))
         return size;

      synchronouslock.unlock();

      size.cx() = 49;

      size.cy() = 49;

      if (extract_image_size(strFile, &size))
      {

         synchronouslock._lock();

         m_mapImageSize.set_at(strFile, size);

         synchronouslock.unlock();

      }

      return size;

   }


   bool script_manager::extract_image_size(const ::file::path& strFile, ::int_size* psize)
   {

      // auto pcontext = get_context();

      auto pfile = file()->get_file(strFile, ::file::e_open_binary | ::file::e_open_read | ::file::e_open_share_deny_write | ::file::e_open_no_exception_on_open);

      if (!pfile || pfile->m_estatus.failed())
      {

         return false;

      }

      // http://www.cplusplus.com/forum/beginner/45217/

      pfile->seek_to_end();

      filesize len = pfile->get_position();

      if (len < 24)
      {
         return false;
      }

      pfile->seek_to_begin();

      // Strategy:
      // reading GIF dimensions requires the first 10 bytes of the file
      // reading PNG dimensions requires the first 24 bytes of the file
      // reading JPEG dimensions requires scanning through jpeg chunks
      // In all formats, the file is at least 24 bytes big, so we'hi read that always
      unsigned char buf[24];

      if (pfile->read({ buf, 24 }) < 24)
      {
         return false;
      }

      // http://www.64lines.com/jpeg-width-height
      if (buf[0] == 0xFF && buf[1] == 0xD8 && buf[2] == 0xFF && buf[3] == 0xE0 && buf[6] == 'J' && buf[7] == 'F' && buf[8] == 'I' && buf[9] == 'F' && buf[10] == '\0')
      {
         unsigned short block_length = buf[4] * 256 + buf[5];
         int i = 4;
         while (i < len)
         {

            i += block_length;               //Increase the file index to get to the next block

            if (i >= len)
               return false;   //Check to protect against segmentation faults

            pfile->set_position(i);

            if (pfile->read({ buf, 4 }) < 4)
               return false;

            if (buf[i] != 0xFF)
               return false;   //Check that we are truly at the start of another block

            if (buf[i + 1] == 0xC0)
            {
               //0xFFC0 is the "Start of frame" marker which contains the file int_size
               //The structure of the 0xFFC0 block is quite simple [0xFFC0][ushort length][uchar precision][ushort x][ushort y]

               if (pfile->read({ buf, 5 }) < 5)
                  return false;

               psize->cy() = buf[i + 1] * 256 + buf[i + 2];
               psize->cx() = buf[i + 3] * 256 + buf[i + 4];
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
      if (buf[0] == 0xFF && buf[1] == 0xD8 && buf[2] == 0xFF)
      {

         psize->cy() = (buf[7] << 8) + buf[8];

         psize->cx() = (buf[9] << 8) + buf[10];

         return true;

      }

      // GIF: first three bytes say "GIF", next three give version number. Then dimensions
      if (buf[0] == 'G' && buf[1] == 'I' && buf[2] == 'F')
      {

         psize->cx() = buf[6] + (buf[7] << 8);

         psize->cy() = buf[8] + (buf[9] << 8);

         return true;

      }

      // PNG: the first frame is by definition an IHDR frame, which gives dimensions
      if (buf[0] == 0x89 && buf[1] == 'P' && buf[2] == 'N' && buf[3] == 'G' && buf[4] == 0x0D && buf[5] == 0x0A && buf[6] == 0x1A && buf[7] == 0x0A
         && buf[12] == 'I' && buf[13] == 'H' && buf[14] == 'D' && buf[15] == 'R')
      {

         psize->cx() = (buf[16] << 24) + (buf[17] << 16) + (buf[18] << 8) + (buf[19] << 0);

         psize->cy() = (buf[20] << 24) + (buf[21] << 16) + (buf[22] << 8) + (buf[23] << 0);

         return true;

      }

      return false;

   }


   ::file::path script_manager::get_stage_path(const ::file::path& strScriptPath)
   {

      ::file::path strPath = strScriptPath;

      strPath.find_replace(":/", ".");
      strPath.find_replace(":\\", ".");
      strPath.find_replace("/", ".");
      strPath.find_replace("\\", ".");
#ifdef WINDOWS
      return ::file::path("C:\\netnode") / m_pcompiler->m_strDynamicSourceStage / m_pcompiler->m_pintegrationcontext->m_strStagePlatform / m_pcompiler->m_strDynamicSourceConfiguration / strPath;
#else
      strPath.begins_eat(".");
      //return "/ca2/stage/"+m_pcompiler->m_strStagePlatform+"/","lib" + strPath);
      return ::file::path("/ca2") / m_pcompiler->m_strDynamicSourceStage / "x86" / "lib" + strPath;
#endif

   }


   ::file::path script_manager::get_full_stage_path(const ::file::path& strScript)
   {

      return get_stage_path(strScript);

   }


   ::file::path script_manager::get_script_path(const ::file::path& strName, const ::string& strModifier)
   {

      ::file::path strTransformName = strName;

      strTransformName.find_replace(":", "");

      ::file::path strScript;

      strScript = strName.title();

      //// auto pcontext = get_context();

#ifdef WINDOWS

      return m_pcompiler->m_pintegrationcontext->m_pathBuildFolder / m_pcompiler->m_strDynamicSourceStage / m_pcompiler->m_pintegrationcontext->m_strPlatform / m_pcompiler->m_strDynamicSourceConfiguration / "dynamic_source" / strTransformName.folder() / strScript + strModifier + ".dll";

#else

      return m_pcompiler->m_pintegrationcontext->m_pathBuildFolder / m_pcompiler->m_strDynamicSourceStage / m_pcompiler->m_pintegrationcontext->m_strStagePlatform / m_pcompiler->m_strDynamicSourceConfiguration / "dynamic_source" / strTransformName.folder() / strScript + strModifier + ".so";

#endif

   }


   bool script_manager::should_build(const ::file::path& strScriptPath)
   {

      _synchronous_lock synchronouslock(m_pmutexShouldBuild);

      bool bShouldBuild = false;

      if (!m_mapShouldBuild.lookup(strScriptPath, bShouldBuild))
         return false;

      return bShouldBuild;

   }

} // namespace dynamic_source





