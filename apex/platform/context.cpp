#include "framework.h"
#include "acme/id.h"
#include "apex/platform/app_core.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_path.h"


CLASS_DECL_ACME const char* get_server_ca2_cc();


namespace apex
{


   context::context()
   {

      m_papexcontext = this;

   }

   context::~context()
   {


   }

   string context::get_latest_build_number(const char * pszConfiguration, const char * pszAppId)
   {

      string strConfiguration(pszConfiguration);

      auto psystem = get_system()->m_papexsystem;

      if (strConfiguration.is_empty())
      {

         strConfiguration = psystem->get_system_configuration();

      }

      if (m_mapCachedLatestBuild[strConfiguration].length() > 0)
      {

         return m_mapCachedLatestBuild[strConfiguration];

      }

      string strBuild;

      string strSpaIgnitionBaseUrl;

      if (strConfiguration == "basis")
      {

         strSpaIgnitionBaseUrl = string(get_server_ca2_cc()) + "api/spaignition";

      }
      else
      {

         strSpaIgnitionBaseUrl = string(get_server_ca2_cc()) + "api/spaignition";

      }

      int iRetry = 0;

   RetryBuildNumber:

      if (iRetry > 10)
      {

         return "";

      }

      iRetry++;

      strBuild = http_get(strSpaIgnitionBaseUrl + "/query?node=build&configuration=" + strConfiguration + "&id=" + string(pszAppId));

      ::str::_008Trim(strBuild);

      if (strBuild.length() != 19)
      {

         sleep(100_ms * iRetry);

         goto RetryBuildNumber;

      }

      m_mapCachedLatestBuild[strConfiguration] = strBuild;

      return strBuild;

   }


   bool context::is_system() const
   {

      return false;

   }


   bool context::is_session() const
   {

      return false;

   }


   bool context::is_local_data() const
   {

      return true;

   }


   ::e_status context::initialize_context()
   {

      auto estatus = __compose(m_phttp);

      if(!estatus)
      {

         return estatus;

      }

      estatus = __compose(m_pfile);

      if (!estatus)
      {

         return estatus;

      }

      estatus = __compose(m_pdir);

      if (!estatus)
      {

         return estatus;

      }

      if(is_system())
      {

         auto psystem = m_psystem->m_papexsystem;

         //m_papexsession->initialize(psystem);

         ////estatus = m_papexsession->initialize_context();

         //if (!estatus)
         //{

         //   return estatus;

         //}

         estatus = m_pfile->init_system();

         if (!estatus)
         {

            return estatus;

         }

         estatus = m_pdir->init_system();

         if (!estatus)
         {

            return estatus;

         }

      }

      estatus = m_pfile->init_context();

      if(!estatus)
      {

         return estatus;

      }

      estatus = m_pfile->init_context();

      if(!estatus)
      {

         return estatus;

      }

      estatus = __compose(m_pos);

      if (!estatus)
      {

         return estatus;

      }

      on_update_matter_locator();

      return ::success;

   }


   void context::clear_cache()
   {

      m_mapCachedLatestBuild.erase_all();


   }


   ::file::path context::defer_make_file_system_url(string str)
   {

      if (str.is_empty())
      {

         return "";

      }

      auto & dir = this->dir();

      if (dir.image().has_char() && m_psystem->m_pacmepath->final_begins_eat_ci(str, dir.image()))
      {

         return ::file::path("image://") / str;

      }
      else if (dir.music().has_char() && m_psystem->m_pacmepath->final_begins_eat_ci(str, dir.music()))
      {

         return ::file::path("music://") / str;

      }
      else if (dir.video().has_char() && m_psystem->m_pacmepath->final_begins_eat_ci(str, dir.video()))
      {

         return ::file::path("video://") / str;

      }
      else if (dir.document().has_char() && m_psystem->m_pacmepath->final_begins_eat_ci(str, dir.document()))
      {

         return ::file::path("document://") / str;

      }
      else if (dir.download().has_char() && m_psystem->m_pacmepath->final_begins_eat_ci(str, dir.download()))
      {

         return ::file::path("download://") / str;

      }
      else
      {

         return str;

      }

   }


   string context::defer_get_file_title(string strParam)
   {

      if (strParam.is_empty())
      {

         return "";

      }

      ::file::path path = defer_process_path(strParam);

      auto & dir = this->dir();

      if (dir.image().has_char() && path.compare_ci(dir.image()) == 0)
      {

         return "Image";

      }
      else if (dir.music().has_char() && path.compare_ci(dir.music()) == 0)
      {

         return "Music";

      }
      else if (dir.video().has_char() && path.compare_ci(dir.video()) == 0)
      {

         return "Video";

      }
      else if (dir.document().has_char() && path.compare_ci(dir.document()) == 0)
      {

         return "Document";

      }
      else if (dir.download().has_char() && path.compare_ci(dir.download()) == 0)
      {

         return "Download";

      }
      else if (dir.desktop().has_char() && path.compare_ci(dir.desktop()) == 0)
      {

         return "Desktop";

      }
      else if (dir.bookmark().has_char() && path.compare_ci(dir.bookmark()) == 0)
      {

         return "Bookmark";

      }
      else
      {

         return path.title();

      }

   }


   ::file::path context::defer_process_path(::file::path path)
   {

      path = _defer_process_path(path);

      if (path & ::file::e_flag_resolve_alias)
      {

         while (true)
         {

            try
            {

               __keep_thread_flag(id_thread_resolve_alias);

               //if (!os_resolve_alias(path, path,::is_set(get_application())? get_application()->m_puiCurrent.get(): nullptr))
               if (!os_resolve_alias(path, path))
               {

                  break;

               }

            }
            catch (...)
            {

            }

            path = _defer_process_path(path);

         }

      }

      return path;

   }


   ::file::path context::_defer_process_path(::file::path path)
   {

      ::file::path pathProcess = __defer_process_path(path);

      if ((path & ::file::e_flag_required)
         && pathProcess.is_empty()
         && !(path & ::file::e_flag_bypass_cache))
      {

         path |= ::file::e_flag_bypass_cache;

         pathProcess = __defer_process_path(path);

      }

      return pathProcess;

   }


   ::file::path context::__defer_process_path(::file::path path)
   {

      path = defer_process_matter_path(path);

      if (::str::begins_eat_ci(path, "music://"))
      {

         path = dir().music() / path;

      }
      else if (::str::begins_eat_ci(path, "video://"))
      {

         path = dir().video() / path;

      }
      else if (::str::begins_eat_ci(path, "image://"))
      {

         path = dir().image() / path;

      }
      else if (::str::begins_eat_ci(path, "document://"))
      {

         path = dir().document() / path;

      }
      else if (::str::begins_eat_ci(path, "dropbox://"))
      {

         path = dir().dropbox() / path;

      }
      else if (::str::begins_eat_ci(path, "onedrive://"))
      {

         path = dir().onedrive() / path;

      }
      else if (::str::begins_eat_ci(path, "appconfig://"))
      {

         path = get_application()->appconfig_folder() / path;

      }
      else if (::str::begins_eat_ci(path, "download://"))
      {

         path = dir().download() / path;

      }
      else if (::str::begins_eat_ci(path, "usersystem://"))
      {

         path = m_psystem->m_pacmedir->system() / path;

      }
      else if (::str::begins_eat_ci(path, "desktop://"))
      {

         path = dir().desktop() / path;

      }
      else if (::str::begins_eat_ci(path, "bookmark://"))
      {

         path = dir().bookmark() / path;

      }

      return path;

   }


   ::file::path context::full_process_path(::file::path path)
   {

      if (!(path & ::file::e_flag_dont_resolve_alias))
      {

         path |= ::file::e_flag_resolve_alias;

      }

      return defer_process_path(path);

   }


   ::file::path context::defer_process_matter_path(::file::path path)
   {

      if (::str::begins_ci(path, "matter://"))
      {

         path = dir().matter(path, false);

      }

      if (path.begins_ci("appmatter://"))
      {

         path = get_matter_cache_path(path);

      }

      return path;

   }

   ::file::path context::get_matter_path(string strMatter)
   {

      if (::str::begins_eat_ci(strMatter, "appmatter://"))
      {

         return dir().install() / strMatter;

      }

      return strMatter;

   }


   ::file::path context::side_get_matter_path(string strMatter)
   {

      auto psystem = get_system()->m_papexsystem;

      auto pdirsystem = psystem->m_pdirsystem;

      ::file::path pathResource = pdirsystem->m_pathInstall;

   #ifdef __APPLE__

      pathResource = pathResource / "Contents/Resources/appmatter";

   #endif

      return pathResource / strMatter;

   }


   ::file::path context::get_matter_cache_path(::file::path path)
   {

      if (::str::begins_eat_ci((string &) path, "appmatter://"))
      {

         auto psystem = get_system()->m_papexsystem;

         ::file::path pathCache = psystem->m_pdirsystem->m_pathLocalAppMatterFolder / path;

         if ((path & ::file::e_flag_get_local_path)
            || (!(path & ::file::e_flag_bypass_cache) 
               && m_psystem->m_pacmepath->is_file_or_dir(pathCache, nullptr)))
         {

            return pathCache;

         }

         ::file::path pathMeta = pathCache + ".meta_information";

         retry retry(millis(500), one_minute());

         if (!(path & ::file::e_flag_bypass_cache))
         {

            string strFirstLine = m_psystem->m_pacmefile->line(pathMeta, 0);

            if (strFirstLine == "itdoesntexist" && !(path & ::file::e_flag_required))
            {

               return "";

            }
            else if (strFirstLine == "processing")
            {

               if (!retry([this, pathMeta]()
                  {

                     return m_psystem->m_pacmefile->line(pathMeta, 0) != "processing";

                  }))
               {

                  return "";

               }

            }

         }

         ::file::path pathSide = side_get_matter_path(path);

         ::file::enum_type etype = ::file::e_type_none;

         if (m_psystem->m_pacmepath->is_file_or_dir(pathSide, &etype))
         {

            if (etype == ::file::e_type_file)
            {

               file().copy(pathCache, pathSide, true);

            }
            else if (etype == ::file::e_type_folder)
            {

               dir().mk(pathCache);

            }

            return pathCache;

         }

         //auto psystem = get_system()->m_papexsystem;

         if (!psystem->m_pdirsystem->m_bMatterFromHttpCache)
         {

            return "";

         }

         ::str::begins_eat_ci(path, "appmatter://");

         path = "https://ca2.software/matter" / path;

         //if (file().exists(path, this))
         {


            property_set set;

            set["raw_http"] = true;

            set["disable_common_name_cert_check"] = true;

            memory_file_pointer pfile(e_create_new);

            if (!retry([&]()
               {

                  return http().download(path, pfile, set);

               }))
            {

               return "";

            }

            string strFsType;
            
            strFsType = set["get_headers"]["x-fstype"];

            if (strFsType.has_char())
            {
               if (strFsType == "directory")
               {

                  if (!retry([&]()
                     {

                        return dir().mk(pathCache);

                     }))
                  {

                     return "";

                  }


               }
               else
               {
                  pfile->seek_to_begin();

                  if (!retry([&]()
                     {

                        return file().copy(pathCache, pfile, false);

                     }))
                  {

                     return "";

                  }

               }

               if (!retry([&]()
                  {

                     return m_psystem->m_pacmefile->set_line(pathMeta, 0, strFsType);

                  }))
               {

                  return "";

               }

            }
            else
            {
               retry([&]()
                  {

                     return m_psystem->m_pacmefile->set_line(pathMeta, 0, "itdoesntexist");

                  });
               return "";
            }



         }
         //         else if (dir().is(path, this))
         //         {
         //
         //            if (!retry([&]()
         //         {
         //
         //            return file_set_line_dup(pathMeta, 0, "directory");
         //
         //            }))
         //            {
         //
         //               return "";
         //
         //            }


         //         else
         //         {
         //
         //
         //
         //            return "";
         //
         //         }

         return pathCache;

      }

      return path;
   }



   file_pointer context::friendly_get_file(::payload varFile, const ::file::e_open & eopen)
   {

      try
      {

         return file().get_file(varFile, eopen);

      }
      catch (::file::exception& e)
      {

         string strMessage = e.get_message();

         //message_box(strMessage);

         output_debug_string(strMessage);

         return nullptr;

      }

   }

   ::file::listing & context::perform_file_listing(::file::listing & listing)
   {

      return dir().ls(listing);

   }


   ::file::listing & context::perform_file_relative_name_listing(::file::listing & listing)
   {

      return dir().ls_relative_name(listing);

   }


   string context::http_get(const ::string & strUrl, ::property_set & set)
   {

      UNREFERENCED_PARAMETER(strUrl);
      UNREFERENCED_PARAMETER(set);

      return "";

   }


   ::handle::ini context::ini_from_path(::file::path & path)
   {

      ::handle::ini ini;

      ::file_pointer pfile;

      if (dir().is(path))
      {

         pfile = file().get_reader(path / "this.ini");

         //string str;

         //pfile->full_read_string(str);

         //ini.parse_ini(str);

      }
      else if (file().exists(path))
      {

         pfile = file().get_reader(path);
         //ini.parse_ini_file(file().get_file());

      }

      if(pfile)
      {

         string str;

         pfile->full_read_string(str);

         ini.parse_ini(str);

      }

      return ini;

   }


   ::handle::ini context::local_ini()
   {

      ::file::path pathFolder = m_psystem->m_pacmedir->localconfig();

      return ini_from_path(pathFolder);

   }


   string context::get_locale()
   {

      return m_strLocale;

   }


   string context::get_schema()
   {

      return m_strSchema;

   }


   void context::locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema)
   {

      if (get_application())
      {

         get_application()->locale_schema_matter(stra, straMatterLocator, strLocale, strSchema);

      }
      else if (get_session())
      {

         get_session()->locale_schema_matter(stra, straMatterLocator, strLocale, strSchema);

      }
      else
      {

         auto psystem = get_system()->m_papexsystem;

         if (psystem)
         {

            psystem->locale_schema_matter(stra, straMatterLocator, strLocale, strSchema);

         }

      }

   }


   string context::get_locale_schema_dir()
   {

      if (get_application())
      {

         return get_application()->get_locale_schema_dir();

      }
      else if (get_session())
      {

         return get_session()->get_locale_schema_dir();

      }
      else
      {

         auto psystem = get_system()->m_papexsystem;

         if (psystem)
         {

            return psystem->get_locale_schema_dir();

         }
         else
         {

            return "_std/_std";

         }

      }

   }


   bool context::http_download(const char * pszUrl, const char * pszFile)
   {

      string strUrl = pszUrl;

      property_set set;

      set["raw_http"] = true;

      set["disable_common_name_cert_check"] = true;

      return http().download(strUrl, pszFile, set);

   }


   string context::http_get(const char * pszUrl)
   {

      property_set set;

      set["get_response"] = "";

      set["raw_http"] = true;

      set["disable_common_name_cert_check"] = true;

      string strResponse;

      if (!http().get(strResponse, pszUrl, set))
      {

         return "";

      }

      return strResponse;

   }


   bool context::sys_set(string strPath, string strValue)
   {

      return file().put_contents_utf8(m_psystem->m_pacmedir->config() / strPath, strValue);

   }


   string context::sys_get(string strPath, string strDefault)
   {

      string strValue = file().as_string(m_psystem->m_pacmedir->config() / strPath);

      if (strValue.is_empty())
      {

         return strDefault;

      }

      return strValue;

   }


   string context::load_string(const char * psz)
   {

      return psz;

   }


   void context::on_update_matter_locator()
   {

      synchronous_lock synchronouslock(mutex());

      m_straMatterLocator.erase_all();

      m_straMatterLocator.add(m_straMatterLocatorPriority);

      m_straMatterLocator.add(matter_locator("app/main"));

   }





   string context::matter_locator(string strApp)
   {

      string strMatterLocator = strApp;

      if (!strMatterLocator.contains_ci("/_matter/"))
      {

         string_array stra;

         stra.explode("/", strMatterLocator);

         if (stra.get_count() >= 2)
         {

            strMatterLocator = stra[0] + "/_matter/" + stra.slice(1).implode("/");

         }

      }

      return strMatterLocator;

   }


   string context::matter_locator(::application * papp)
   {

      return ::file::path(papp->m_strRoot) / "_matter" / papp->m_strDomain;

   }


   void context::add_matter_locator(string strApp)
   {

      synchronous_lock synchronouslock(mutex());

      string strMatterLocator = matter_locator(strApp);

      m_straMatterLocatorPriority.add(strMatterLocator);

   //   on_update_matter_locator();


   }




   void context::add_matter_locator(::application * papp)
   {

      synchronous_lock synchronouslock(mutex());

      string strMatterLocator = matter_locator(papp);

      add_matter_locator(strMatterLocator);

      on_update_matter_locator();

   }




   ::e_status context::_load_from_file(::matter* pobject, const ::payload& varFile, const ::payload& varOptions)
   {

      binary_stream reader(m_pcontext->m_papexcontext->file().get_reader(varFile));

      read(reader);

      return reader.m_estatus;

   }


   ::e_status context::_save_to_file(const ::payload& varFile, const ::payload& varOptions, const ::matter * pobject)
   {

      binary_stream writer(m_pcontext->m_papexcontext->file().get_writer(varFile));

      write(writer);

      return writer.m_estatus;

   }


//   ::e_status context::destroy()
//   {
//
//      auto estatus = ::object::destroy();
//
//      return estatus;
//
//   }


   file_transport context::get_file(const ::payload& varFile, const ::file::e_open& eopen)
   {

      auto pfile = m_papexcontext->file().get_file(varFile, eopen);

      return pfile;

   }


   void context::on_command_create(::create* pcreate)
   {

      if (m_varFile.is_empty())
      {

         m_varFile = pcreate->m_pcommandline->m_varFile;

      }
      else
      {

         m_varFile.payloada().add(pcreate->m_pcommandline->m_varFile);

      }

      //m_varQuery.propset().merge(pcreate->m_pcommandline->m_varQuery.propset());

      get_property_set().merge(pcreate->m_pcommandline->m_varQuery.propset());


   }


   bool context::contains(::create* pcreate) const
   {

      if (::is_null(pcreate))
      {

         return false;

      }

      synchronous_lock synchronouslock(mutex());

      return m_createaPending.predicate_contains([&pcreate](auto& p) {return p.get() == pcreate; })
             || m_createaHistory.predicate_contains([&pcreate](auto& p) {return p.get() == pcreate; })
             || m_pcreate.get() == pcreate;

   }


   string context::command_line_text() const
   {

      if (!m_pcreate)
      {

         return "";

      }

      if (!m_pcreate->m_pcommandline)
      {

         return "";

      }

      return m_pcreate->m_pcommandline->m_strCommandLine;

   }


   ::e_status context::destroy()
   {

      ::thread::destroy();

      ::acme::context::destroy();

      return success;

   }


   //::task_pool* context::taskpool()
   //{

   //   __defer_construct_new(m_ptaskpool);

   //   return m_ptaskpool;

   //}


   //void command::on_create(::create* pcreate)
   //{

   //   if (m_varFile.is_empty())
   //   {

   //      m_varFile = pcreate->m_pcommandline->m_varFile;

   //   }
   //   else
   //   {

   //      m_varFile.payloada().add(pcreate->m_pcommandline->m_varFile);

   //   }

   //   m_varQuery.propset().merge(pcreate->m_pcommandline->m_varQuery.propset());

   //}


   void context::add_create(::create* pcreate)
   {

      synchronous_lock synchronouslock(mutex());

      if (::is_null(pcreate) || contains(pcreate))
      {

         __throw(error_invalid_argument);

      }

      if (!m_pcreate)
      {

         __refer(m_pcreate, pcreate);

         m_pcreate->m_bNew = true;

         on_command_create(pcreate);

      }
      else
      {

         __refer(m_createaPending.add_new(), pcreate);

      }

   }


   create * context::get_create()
   {

      synchronous_lock synchronouslock(mutex());

      if (!m_pcreate || !m_pcreate->m_bNew)
      {

         if (m_pcreate)
         {

            __release(m_pcreate);

         }

         if (m_createaPending.is_empty())
         {

            return nullptr;

         }

         auto pcreate = m_createaPending[0];

         m_pcreate = pcreate;

         m_pcreate->m_bNew = true;

         on_command_create(pcreate);

         m_createaPending.erase_at(0);

      }

      auto & pcreateNew = m_createaHistory.add_new();

      __refer(pcreateNew, m_pcreate OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_FUNCTION_LINE);

      m_pcreate->m_bNew = false;

      return m_pcreate.get();

   }


} // namespace apex


