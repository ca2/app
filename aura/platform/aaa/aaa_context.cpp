#include "framework.h"
#include "acme/constant/id.h"
#include "aura/platform/app_core.h"


extern const char* g_pszServerCa2Cc;


string context::get_latest_build_number(const ::string & pszConfiguration, const ::string & pszAppId)
{

   string strConfiguration(pszConfiguration);

   if (strConfiguration.is_empty())
   {

      strConfiguration = ::auraacmesystem()->get_system_configuration();

   }

   if (m_mapCachedLatestBuild[strConfiguration].length() > 0)
   {

      return m_mapCachedLatestBuild[strConfiguration];

   }

   string strBuild;

   string strSpaIgnitionBaseUrl;

   if (strConfiguration == "basis")
   {

      strSpaIgnitionBaseUrl = string(g_pszServerCa2Cc) + "api/spaignition";

   }
   else
   {

      strSpaIgnitionBaseUrl = string(g_pszServerCa2Cc) + "api/spaignition";

   }

   int iRetry = 0;

RetryBuildNumber:

   if (iRetry > 10)
   {

      return "";

   }

   iRetry++;

   strBuild = http_get(strSpaIgnitionBaseUrl + "/query?node=build&configuration=" + strConfiguration + "&atom=" + string(pszAppId));

   ::str::_008Trim(strBuild);

   if (strBuild.length() != 19)
   {

      sleep(100 * iRetry);

      goto RetryBuildNumber;

   }

   m_mapCachedLatestBuild[strConfiguration] = strBuild;

   return strBuild;

}


bool context::is_system() const
{

   return false;

}


void context::initialize_context()
{

   auto estatus = __øconstruct(m_phttp);

   if(!estatus)
   {

      return estatus;

   }

   estatus = __øconstruct(m_pfile);

   if (!estatus)
   {

      return estatus;

   }

   estatus = __øconstruct(m_pdir);

   if (!estatus)
   {

      return estatus;

   }

   if(is_system())
   {

      get_session()->set_object(get_context_system());

      estatus = get_session()->initialize_context();

      if (!estatus)
      {

         return estatus;

      }

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

   estatus = __øconstruct(m_pos);

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

   if (dir.image().has_character() && ::file::case_insensitive_begins_eat(str, dir.image()))
   {

      return ::file::path("image://") / str;

   }
   else if (dir.music().has_character() && ::file::case_insensitive_begins_eat(str, dir.music()))
   {

      return ::file::path("music://") / str;

   }
   else if (dir.video().has_character() && ::file::case_insensitive_begins_eat(str, dir.video()))
   {

      return ::file::path("video://") / str;

   }
   else if (dir.document().has_character() && ::file::case_insensitive_begins_eat(str, dir.document()))
   {

      return ::file::path("document://") / str;

   }
   else if (dir.download().has_character() && ::file::case_insensitive_begins_eat(str, dir.download()))
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

   if (dir.image().has_character() && path.case_insensitive_order(dir.image()) == 0)
   {

      return "Image";

   }
   else if (dir.music().has_character() && path.case_insensitive_order(dir.music()) == 0)
   {

      return "Music";

   }
   else if (dir.video().has_character() && path.case_insensitive_order(dir.video()) == 0)
   {

      return "Video";

   }
   else if (dir.document().has_character() && path.case_insensitive_order(dir.document()) == 0)
   {

      return "Document";

   }
   else if (dir.download().has_character() && path.case_insensitive_order(dir.download()) == 0)
   {

      return "Download";

   }
   else if (dir.desktop().has_character() && path.case_insensitive_order(dir.desktop()) == 0)
   {

      return "Desktop";

   }
   else if (dir.bookmark().has_character() && path.case_insensitive_order(dir.bookmark()) == 0)
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

            if (!os_resolve_alias(path, path,::is_set(get_app())? papp->m_puiCurrent: nullptr))
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

   if (path.case_insensitive_begins_eat("music://"))
   {

      path = directory()->music() / path;

   }
   else if (path.case_insensitive_begins_eat("video://"))
   {

      path = directory()->video() / path;

   }
   else if (path.case_insensitive_begins_eat("image://"))
   {

      path = directory()->image() / path;

   }
   else if (path.case_insensitive_begins_eat("document://"))
   {

      path = directory()->document() / path;

   }
   else if (path.case_insensitive_begins_eat("dropbox://"))
   {

      path = directory()->dropbox() / path;

   }
   else if (path.case_insensitive_begins_eat("dropbox-app://"))
   {

      path = directory()->dropbox_app() / path;

   }
   else if (path.case_insensitive_begins_eat("onedrive://"))
   {

      path = directory()->onedrive() / path;

   }
   else if (path.case_insensitive_begins_eat("appconfig://"))
   {

      path = papp->appconfig_folder() / path;

   }
   else if (path.case_insensitive_begins_eat("download://"))
   {

      path = directory()->download() / path;

   }
   else if (path.case_insensitive_begins_eat("usersystem://"))
   {

      path =          auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / path;

   }
   else if (path.case_insensitive_begins_eat("desktop://"))
   {

      path = directory()->desktop() / path;

   }
   else if (path.case_insensitive_begins_eat("bookmark://"))
   {

      path = directory()->bookmark() / path;

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

   if (case_insensitive_string_begins(path, "matter://"))
   {

      path = directory()->matter(path, false);

   }

   if (path.case_insensitive_begins("appmatter://"))
   {

      path = get_matter_cache_path(path);

   }

   return path;

}

::file::path context::get_matter_path(string strMatter)
{

   if (strMatter.case_insensitive_begins_eat("appmatter://"))
   {

      return directory()->install() / strMatter;

   }

   return strMatter;

}


::file::path context::side_get_matter_path(string strMatter)
{

   auto pdirsystem = ::auraacmesystem()->m_pdirectorysystem;

   ::file::path pathResource = pdirsystem->m_pathInstall;

#ifdef __APPLE__

   pathResource = pathResource / "Contents/Resources/appmatter";

#endif

   return pathResource / strMatter;

}


::file::path context::get_matter_cache_path(::file::path path)
{

   if (::str::case_insensitive_begins_eat((string &) path, "appmatter://"))
   {

      ::file::path pathCache = ::auraacmesystem()->m_pdirectorysystem->m_pathLocalAppMatterFolder / path;

      if ((path & ::file::e_flag_get_local_path)
         || (!(path & ::file::e_flag_bypass_cache) && path_system()->is_file_or_dir(pathCache, nullptr)))
      {

         return pathCache;

      }

      ::file::path pathMeta = pathCache + ".meta_information";

      retry retry(::duration(500), one_minute());

      if (!(path & ::file::e_flag_bypass_cache))
      {

         string strFirstLine = file_system()->line(pathMeta, 0);

         if (strFirstLine == "itdoesntexist" && !(path & ::file::e_flag_required))
         {

            return "";

         }
         else if (strFirstLine == "processing")
         {

            if (!retry([pathMeta]()
               {

                  return file_system()->line(pathMeta, 0) != "processing";

               }))
            {

               return "";

            }

         }

      }

      ::file::path pathSide = side_get_matter_path(path);

      ::file::enum_type etype = ::file::e_type_none;

      if (path_system()->is_file_or_dir(pathSide, &etype))
      {

         if (etype == ::file::e_type_file)
         {

            file()->copy(pathCache, pathSide, true);

         }
         else if (etype == ::file::e_type_folder)
         {

            directory()->mk(pathCache);

         }

         return pathCache;

      }

      if (!::auraacmesystem()->m_pdirectorysystem->m_bMatterFromHttpCache)
      {

         return "";

      }

      path.case_insensitive_begins_eat("appmatter://");

      path = string(g_pszServerCa2Cc) + "matter" / path;

      //if (file()->exists(path, this))
      {


         ::property_set set;

         set["raw_http"] = true;

         set["disable_common_name_cert_check"] = true;

         memory_file_pointer pfile(e_create_new);

         if (!retry([&]()
            {

               return http()->download(path, pfile, set);

            }))
         {

            return "";

         }


            string strFsType = set["get_headers"]["x-fstype"];

            if (strFsType.has_character())
            {
               if (strFsType == "directory")
               {

                  if (!retry([&]()
                     {

                        return directory()->mk(pathCache);

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

                        return file()->copy(pathCache, pfile, false);

                     }))
                  {

                     return "";

                  }

               }

               if (!retry([&]()
                  {

                     return file_set_line_dup(pathMeta, 0, strFsType);

                  }))
               {

                  return "";

               }

            }
            else
            {
               retry([&]()
                  {

                     return file_set_line_dup(pathMeta, 0, "itdoesntexist");

                  });
               return "";
            }



      }
      //         else if (directory()->is(path, this))
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



file_pointer context::friendly_get_file(::payload payloadFile, unsigned int nOpenFlags)
{

   try
   {

      return file()->get_file(payloadFile, nOpenFlags);

   }
   catch (::file::exception& e)
   {

      string strMessage = e.get_message();

      message_box(strMessage);

      return nullptr;

   }

}

::file::listing & context::perform_file_listing(::file::listing & listing)
{

   return directory()->ls(listing);

}


::file::listing & context::perform_file_relative_name_listing(::file::listing & listing)
{

   return directory()->ls_relative_name(listing);

}


string context::http_get(const ::string & strUrl, ::property_set & set)
{

   __UNREFERENCED_PARAMETER(strUrl);
   __UNREFERENCED_PARAMETER(set);

   return "";

}


::handle::ini context::ini_from_path(::file::path & path)
{

   ::handle::ini ini;

   ::file_pointer pfile;

   if (directory()->is(path))
   {

      pfile = file()->get_reader(path / "this.ini");

      //string str;

      //pfile->full_read_string(str);

      //ini.parse_ini(str);

   }
   else if (file()->exists(path))
   {

      pfile = file()->get_reader(path);
      //ini.parse_ini_file(file()->get_file());

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

   ::file::path pathFolder =          auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->localconfig();

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

   if (get_app())
   {

      get_app()->locale_schema_matter(stra, straMatterLocator, strLocale, strSchema);

   }
   else if (get_session())
   {

      get_session()->locale_schema_matter(stra, straMatterLocator, strLocale, strSchema);

   }
   else if (get_context_system())
   {

      ::auraacmesystem()->locale_schema_matter(stra, straMatterLocator, strLocale, strSchema);

   }

}


string context::get_locale_schema_dir()
{

   if (get_app())
   {

      return get_app()->get_locale_schema_dir();

   }
   else if (get_session())
   {

      return get_session()->get_locale_schema_dir();

   }
   else if (get_context_system())
   {

      return ::auraacmesystem()->get_locale_schema_dir();

   }
   else
   {

      return "_std/_std";

   }

}


bool context::http_download(const ::string & pszUrl, const ::string & pszFile)
{

   string strUrl = pszUrl;

   ::property_set set;

   set["raw_http"] = true;

   set["disable_common_name_cert_check"] = true;

   return http()->download(strUrl, pszFile, set);

}


string context::http_get(const ::string & pszUrl)
{

   ::property_set set;

   set["get_response"] = "";

   set["raw_http"] = true;

   set["disable_common_name_cert_check"] = true;

   string strResponse;

   if (!http()->get(strResponse, pszUrl, set))
   {

      return "";

   }

   return strResponse;

}


bool context::sys_set(string strPath, string strValue)
{

   return file()->put_text_utf8(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->config() / strPath, strValue);

}


string context::sys_get(string strPath, string strDefault)
{

   string strValue = file()->as_string(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->config() / strPath);

   if (strValue.is_empty())
   {

      return strDefault;

   }

   return strValue;

}


string context::load_string(const ::string & psz)
{

   return psz;

}


void context::on_update_matter_locator()
{

   synchronous_lock synchronouslock(this->synchronization());

   m_straMatterLocator.erase_all();

   m_straMatterLocator.add(m_straMatterLocatorPriority);

   m_straMatterLocator.add(matter_locator("app/main"));

}





string context::matter_locator(string strApp)
{

   string strMatterLocator = strApp;

   if (!strMatterLocator.case_insensitive_contains("/_matter/"))
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


string context::matter_locator(::aura::application * papp)
{

   return ::file::path(papp->m_strRoot) / "_matter" / papp->m_strDomain;

}


void context::add_matter_locator(string strApp)
{

   synchronous_lock synchronouslock(this->synchronization());

   string strMatterLocator = matter_locator(strApp);

   m_straMatterLocatorPriority.add(strMatterLocator);

//   on_update_matter_locator();


}




void context::add_matter_locator(::aura::application * papp)
{

   synchronous_lock synchronouslock(this->synchronization());

   string strMatterLocator = matter_locator(papp);

   add_matter_locator(strMatterLocator);

   on_update_matter_locator();

}




void context::_load_from_file(::particle * pparticle, const ::payload& payloadFile, const ::payload& varOptions)
{

   binary_stream reader(file()->get_reader(payloadFile));

   read(reader);

   return reader.m_estatus;

}


void context::_save_to_file(const ::payload& payloadFile, const ::payload& varOptions, const ::particle * pparticle)
{

   binary_stream writer(file()->get_writer(payloadFile));

   write(writer);

   return writer.m_estatus;

}


void context::destroy()
{

   ::object::destroy();

   m_papp.release();

   m_psession.release();

   m_psystemContext.release();

}



