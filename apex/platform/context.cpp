#include "framework.h"
#include "context.h"
#include "application.h"
#include "system.h"
#include "os_context.h"
#include "acme/constant/id.h"
#include "acme/filesystem/file/binary_stream.h"
#include "acme/filesystem/file/exception.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme/filesystem/filesystem/link.h"
#include "acme/parallelization/retry.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/parallelization/task_flag.h"
#include "acme/platform/ini.h"
#include "acme/handler/request.h"
#include "acme/primitive/string/str.h"
#include "acme/filesystem/filesystem/dir_context.h"
#include "acme/filesystem/filesystem/dir_system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/networking/http/context.h"


#include "acme/primitive/time/_text_stream.h"


namespace apex
{


   context::context()
   {

      m_papexcontext = this;

   }

   context::~context()
   {


   }


   void context::initialize(::particle * pparticle)
   {

      ::thread::initialize(pparticle);

      ::acme::context::initialize(pparticle);

      ::file::enumerator::initialize(pparticle);

   }


   string context::get_latest_build_number(const ::scoped_string & scopedstrConfiguration, const ::scoped_string & scopedstrAppId)
   {

      string strConfiguration(scopedstrConfiguration);

      auto psystem = acmesystem()->m_papexsystem;

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

      string strStoreBaseUrl = get_store_server_base_url();;

      if (strConfiguration == "basis")
      {

         strSpaIgnitionBaseUrl = ::file::path(strStoreBaseUrl) / "api/spaignition";

      }
      else
      {

         strSpaIgnitionBaseUrl = ::file::path(strStoreBaseUrl) / "api/spaignition";

      }

      int iRetry = 0;

   RetryBuildNumber:

      if (iRetry > 10)
      {

         return "";

      }

      iRetry++;

      strBuild = http_get(strSpaIgnitionBaseUrl + "/query?node=build&configuration=" + strConfiguration + "&id=" + string(scopedstrAppId));

      ::str::_008Trim(strBuild);

      if (strBuild.length() != 19)
      {

         preempt(100_ms * iRetry);

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


   void context::initialize_context()
   {

      ::acme::context::initialize_context();

      __construct(m_phttp);

      __construct(m_poscontext);



   }


   void context::initialize_context_1()
   {

      ::acme::context::initialize_context_1();

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

      if (dir()->image().has_char() && acmepath()->case_insensitive_real_path_begins_eat(str, dir()->image()))
      {

         return ::file::path("image://") / str;

      }
      else if (dir()->music().has_char() && acmepath()->case_insensitive_real_path_begins_eat(str, dir()->music()))
      {

         return ::file::path("music://") / str;

      }
      else if (dir()->video().has_char() && acmepath()->case_insensitive_real_path_begins_eat(str, dir()->video()))
      {

         return ::file::path("video://") / str;

      }
      else if (dir()->document().has_char() && acmepath()->case_insensitive_real_path_begins_eat(str, dir()->document()))
      {

         return ::file::path("document://") / str;

      }
      else if (dir()->download().has_char() && acmepath()->case_insensitive_real_path_begins_eat(str, dir()->download()))
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

      if (dir()->image().has_char() && path.case_insensitive_order(dir()->image()) == 0)
      {

         return "Image";

      }
      else if (dir()->music().has_char() && path.case_insensitive_order(dir()->music()) == 0)
      {

         return "Music";

      }
      else if (dir()->video().has_char() && path.case_insensitive_order(dir()->video()) == 0)
      {

         return "Video";

      }
      else if (dir()->document().has_char() && path.case_insensitive_order(dir()->document()) == 0)
      {

         return "Document";

      }
      else if (dir()->download().has_char() && path.case_insensitive_order(dir()->download()) == 0)
      {

         return "Download";

      }
      else if (dir()->desktop().has_char() && path.case_insensitive_order(dir()->desktop()) == 0)
      {

         return "Desktop";

      }
      else if (dir()->bookmark().has_char() && path.case_insensitive_order(dir()->bookmark()) == 0)
      {

         return "Bookmark";

      }
      else if (dir()->bookmark().has_char() && path == "/")
      {

         return "File System";

      }
      else
      {

         return path.title();

      }

   }


   ::file::path context::defer_process_path(::file::path path)
   {

      if (path.flags() & ::file::e_flag_final_path)
      {

         return path;

      }

      path = _defer_process_path(path);

      if (path.flags() & ::file::e_flag_resolve_alias)
      {

         while (true)
         {

            try
            {

               __keep_task_flag(e_task_flag_resolve_alias);

               //if (!os_resolve_alias(path, path,::is_set(get_app())? get_app()->m_puiCurrent.get(): nullptr))
               auto plink = os_resolve_alias(path);

               if(!plink || plink->m_pathTarget.is_empty() || plink->m_pathTarget == path)
               {

                  break;

               }

               path = plink->m_pathTarget;

            }
            catch (...)
            {

            }

            path = _defer_process_path(path);

         }

      }

      path.flags().set(::file::e_flag_final_path);

      return path;

   }


   ::file::path context::_defer_process_path(::file::path path)
   {

      ::file::path pathProcess = __defer_process_path(path);

      if (path.flags().is(::file::e_flag_required)
         && pathProcess.is_empty()
         && path.flags().is_clear(::file::e_flag_bypass_cache))
      {

         path.flags() += ::file::e_flag_bypass_cache;

         pathProcess = __defer_process_path(path);

      }

      return pathProcess;

   }


   bool context::defer_process_media_library_path(::file::path & path)
   {

      return acmedirectory()->defer_process_media_library_path(path);

   }


   ::file::path context::__defer_process_path(::file::path path)
   {

      path = defer_process_matter_path(path);
      
      if(path.is_empty())
      {
         
         return {};
         
      }

      path = acmepath()->defer_process_relative_path(path);

      if (defer_process_media_library_path(path))
      {

         return path;

      }
      else
      {

         defer_process_known_folder_path(path);

      }

      return path;

   }


   bool context::_001IsProtocol(::file::path & path, const ::string & strProtocol)
   {

      if (path.case_insensitive_begins_eat(strProtocol))
      {

         return true;

      }
      else if ((path.length() <= strProtocol.length()) && path.case_insensitive_begins(strProtocol(0, strProtocol.length() - 3)))
      {

         path.clear();

         return true;

      }

      return false;

   }


   bool context::defer_process_known_folder_path(::file::path & path)
   {

      if (_001IsProtocol(path, "music:/"))
      {

         path = dir()->music() / path;

      }
      else if (_001IsProtocol(path, "video:/"))
      {

         path = dir()->video() / path;

      }
      else if (_001IsProtocol(path, "image:/"))
      {

         path = dir()->image() / path;

      }
      else if (_001IsProtocol(path, "document:/"))
      {

         path = dir()->document() / path;

      }
      else if (_001IsProtocol(path, "dropbox:/"))
      {

         path = dir()->dropbox() / path;

      }
      else if (_001IsProtocol(path, "dropbox-app:/"))
      {

         auto papplication = acmeapplication();

         if (!papplication || papplication->m_strAppId.is_empty())
         {

            return false;

         }

         path = dir()->dropbox_app() / path;

      }
      else if (_001IsProtocol(path, "onedrive:/"))
      {

         path = dir()->onedrive() / path;

      }
      else if (_001IsProtocol(path, "appconfig:/"))
      {

         path = get_app()->m_papexapplication->appconfig_folder() / path;

      }
      else if (_001IsProtocol(path, "download:/"))
      {

         path = dir()->download() / path;

      }
      else if (_001IsProtocol(path, "usersystem:/"))
      {

         path = acmedirectory()->system() / path;

      }
      else if (_001IsProtocol(path, "desktop:/"))
      {

         path = dir()->desktop() / path;

      }
      else if (_001IsProtocol(path, "bookmark:/"))
      {

         path = dir()->bookmark() / path;

      }
      else
      {

         return false;

      }

      return true;

   }


   ::file::path context::full_process_path(::file::path path)
   {

      if (path.flags().is_clear(::file::e_flag_dont_resolve_alias))
      {

         path.flags().set(::file::e_flag_resolve_alias);

      }

      return defer_process_path(path);

   }


   file_pointer context::friendly_get_file(::payload payloadFile, ::file::e_open eopen)
   {

      try
      {

         return file()->get_file(payloadFile, eopen);

      }
      catch (::file::exception & e)
      {

         string strMessage = e.get_message();

         //message_box(strMessage);

         information(strMessage);

         return nullptr;

      }

   }



   //
   //CLASS_DECL_APEX  bool _os_may_have_alias(const ::scoped_string & scopedstr)
   //{
   //
   //   string str(psz);
   //
   //   return str.case_insensitive_ends(".lnk") || str.case_insensitive_contains(".lnk/") || str.case_insensitive_contains(".lnk\\");
   //
   //}


   ::pointer < ::file::link > context::os_resolve_alias(const ::file::path & path, bool bNoUI, bool bNoMount)
   {

      auto plink = _os_resolve_alias(path, bNoUI, bNoMount);

      if(plink)
      {

         return plink;

      }

      if (_os_has_alias_in_path(path))
      {

         ::pointer < ::file::link > plink;

         ::file::path_array patha;

         ::file::path_array pathaRelative;

         ascendants_path(path, patha, &pathaRelative);

         for (index i = 0; i < patha.get_count(); i++)
         {

            ::file::path pathAlias = patha[i];

            auto plinkHere = _os_resolve_alias(pathAlias, bNoUI, bNoMount);

            if(plinkHere)
            {

               plink = plinkHere;

               plink->m_pathTarget /= pathaRelative[i];

            }

         }

         return plink;

      }

      return nullptr;

   }


   bool context::_os_has_alias_in_path(const ::file::path & path, bool bNoUI, bool bNoMount)
   {

      return os_context()->has_alias_in_path(path);

   }



   ::pointer < ::file::link > context::_os_resolve_alias(const ::file::path & path, bool bNoUI, bool bNoMount)
   {

      if (os_is_alias(path))
      {

         return acmepath()->resolve_link(path);

      }

      return nullptr;

   }

//
//#ifdef WINDOWS
//
   bool context::os_is_alias(const ::file::path & path)
   {

      return os_context()->is_alias(path);

      //return string_ends_ci(psz, ".lnk");

   }
//
//#endif
//

   bool context::enumerate(::file::listing & listing)
   {

      return dir()->enumerate(listing);

   }


   /*bool context::perform_file_relative_name_listing(::file::listing & listing)
   {

      return dir()->ls_relative_name(listing);

   }*/


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

      if (dir()->is(path))
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

      if (pfile)
      {

         auto str = pfile->full_string();

         ini.parse_ini(str);

      }

      return ini;

   }


   ::handle::ini context::local_ini()
   {

      ::file::path pathFolder = acmedirectory()->localconfig();

      return ini_from_path(pathFolder);

   }




   bool context::http_download(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrFile)
   {

      string strUrl = scopedstrUrl;

      property_set set;

      set["raw_http"] = true;

      set["disable_common_name_cert_check"] = true;

      return http().download(strUrl, scopedstrFile, set);

   }


   string context::http_get(const ::scoped_string & scopedstrUrl)
   {

      property_set set;

      set["get_response"] = "";

      set["raw_http"] = true;

      set["disable_common_name_cert_check"] = true;

      string strResponse;

      http().get(strResponse, scopedstrUrl, set);

      //if (!http().get(strResponse, pszUrl, set))
      //{

      //   return "";

      //}

      return strResponse;

   }


   ::file::path context::sys_path(const ::scoped_string & scopedstrPath)
   {

      return acmedirectory()->config() / scopedstrPath;

   }


   void context::sys_set(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrValue)
   {

      auto pathSys = sys_path(scopedstrPath);

      file()->put_text_utf8(pathSys, scopedstrValue);

   }


   string context::sys_get(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrDefault)
   {

      auto pathSys = sys_path(scopedstrPath);

      if (!file()->exists(pathSys))
      {

         return scopedstrDefault;

      }

      auto strValue = file()->safe_get_string(pathSys);

      return strValue;

   }


   string context::load_string(const ::scoped_string & scopedstr)
   {

      return scopedstr;

   }


   //void context::on_update_matter_locator()
   //{

   //}



   void context::_load_from_file(::particle * pparticle, const ::payload & payloadFile, const ::payload & varOptions)
   {

      binary_stream read(file()->get_reader(payloadFile));

      //read(reader);

      ///return reader.m_estatus;

   }


   void context::_save_to_file(const ::payload & payloadFile, const ::payload & varOptions, const ::particle * pparticle)
   {

      binary_stream write(file()->get_writer(payloadFile));

      //write(writer);

      ///return writer.m_estatus;

   }


   //   void context::destroy()
   //   {
   //
   //      auto estatus = ::object::destroy();
   //
   //      return estatus;
   //
   //   }


   file_pointer context::get_file(const ::payload & payloadFile, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception)
   {

      auto pfile = m_papexcontext->file()->get_file(payloadFile, eopen, pfileexception);

      return pfile;

   }


   void context::request(::request * prequest)
   {

      m_prequest = prequest;

      if (m_payloadFile.is_empty())
      {

         m_payloadFile = prequest->m_payloadFile;

      }
      else
      {

         m_payloadFile.payloada().add(prequest->m_payloadFile);

      }

      get_property_set().merge(prequest->get_property_set());

      on_request(prequest);

   }


   bool context::contains(::request * prequest) const
   {

      if (::is_null(prequest))
      {

         return false;

      }

      synchronous_lock synchronouslock(this->synchronization());

      return m_requestaPending.predicate_contains([&prequest](auto & p) {return p.get() == prequest; })
         || m_requestaHistory.predicate_contains([&prequest](auto & p) {return p.get() == prequest; })
         || m_prequest.get() == prequest;

   }


   string context::command_line_text() const
   {

      if (!m_prequest)
      {

         return "";

      }

      //if (!m_prequest->m_pcommandline)
      //{

      //   return "";

      //}

      return m_prequest->m_strCommandLine;

   }


   void context::destroy()
   {

      ::thread::destroy();

      ::acme::context::destroy();

      //return success;

   }


   //::task_pool* context::taskpool()
   //{

   //   __defer_construct_new(m_ptaskpool);

   //   return m_ptaskpool;

   //}


   //void command::on_create(::request* prequest)
   //{

   //   if (m_payloadFile.is_empty())
   //   {

   //      m_payloadFile = prequest->m_payloadFile;

   //   }
   //   else
   //   {

   //      m_payloadFile.payloada().add(prequest->m_payloadFile);

   //   }

   //   ).merge(prequest->));

   //}

   //void context::on_idle()
   //{

   //   post_next_pending_request();

   //}


   void context::post_request(::request * prequest)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (::is_null(prequest) || contains(prequest))
      {

         throw ::exception(error_bad_argument);

      }

      prequest->m_bNew = true;

      m_requestaPending.add(prequest);

      kick_idle();

   }


   bool context::on_idle()
   {

      if (post_next_pending_request())
      {

         return true;

      }

      return false;

   }


   bool context::post_next_pending_request()
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (!m_requestaPending.has_element())
      {

         return false;

      }

      auto prequest = m_requestaPending.pick_first();

      m_requestaHistory.add(prequest);

      ::thread::post_request(prequest);

      return true;

   }


   string context::get_store_server_base_url()
   {

      return m_strStoreServerBaseUrl;

   }


   //bool context::os_is_alias(const char *psz)
   //{

   //   return false;

   //}


   ::string context::http_text(const ::scoped_string & scopedstrUrl, ::property_set & set)
   {

      return http().get(scopedstrUrl, set);

   }


   void context::http_download(const ::payload & payloadFile, const ::scoped_string & scopedstrUrl, ::property_set & set)
   {

      http().download(scopedstrUrl, payloadFile, set);

   }


   ::memory context::http_memory(const ::scoped_string& scopedstrUrl, ::property_set& set)
   {

      ::memory memory;
      
      http().get(&memory, scopedstrUrl, set);

      return ::transfer(memory);

   }


} // namespace apex



