#include "framework.h"
#include "context.h"
#include "application.h"
#include "system.h"
#include "node.h"
#include "acme/constant/id.h"
#include "acme/filesystem/file/binary_stream.h"
#include "acme/filesystem/file/exception.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/platform/component.h"
#include "acme/parallelization/retry.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/component_implementation.h"
#include "acme/platform/http.h"
//#include "acme/platform/ini.h"
#include "acme/handler/request.h"
#include "acme/prototype/string/str.h"
#include "apex/filesystem/fs/raw_folder_protocol.h"
#include "apex/networking/http/context.h"


#include "acme/prototype/time/_text_stream.h"


namespace apex
{


   context::context()
   {

      //m_papexcontext = this;

      m_bModifiedFsRawFolderProtocols = true;

   }


   context::~context()
   {


   }


   void context::initialize(::particle * pparticle)
   {

      ::thread::initialize(pparticle);

      ::platform::context::initialize(pparticle);

      ::file::enumerator::initialize(pparticle);

   }


   string context::get_latest_build_number(const ::scoped_string & scopedstrConfiguration, const ::scoped_string & scopedstrAppId)
   {

      string strConfiguration(scopedstrConfiguration);

      auto psystem = system();

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

      strBuild = http()->get(strSpaIgnitionBaseUrl + "/query?node=build&configuration=" + strConfiguration + "&id=" + string(scopedstrAppId));

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

      ::platform::context::initialize_context();

      ///__øconstruct(m_phttp);

      //__øconstruct(m_poscontext);



   }


   void context::initialize_context_1()
   {

      ::platform::context::initialize_context_1();

   }


   void context::initialize_http()
   {

      __øconstruct(m_phttp);

   }


   void context::finalize_context()
   {

//      if (m_poscontext)
//      {
//
//         try
//         {
//
//            m_poscontext->finalize();
//
//         }
//         catch (...)
//         {
//
//
//         }
//
//      }

      if (m_phttp)
      {

         try
         {

            m_phttp->destroy();

         }
         catch (...)
         {


         }

      }

      //m_poscontext.release();

      m_phttp.release();

      ::platform::context::finalize_context();

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

      if (directory()->image().has_character() && path_system()->case_insensitive_real_path_begins_eat(str, directory()->image()))
      {

         return ::file::path("image://") / str;

      }
      else if (directory()->music().has_character() && path_system()->case_insensitive_real_path_begins_eat(str, directory()->music()))
      {

         return ::file::path("music://") / str;

      }
      else if (directory()->video().has_character() && path_system()->case_insensitive_real_path_begins_eat(str, directory()->video()))
      {

         return ::file::path("video://") / str;

      }
      else if (directory()->document().has_character() && path_system()->case_insensitive_real_path_begins_eat(str, directory()->document()))
      {

         return ::file::path("document://") / str;

      }
      else if (directory()->download().has_character() && path_system()->case_insensitive_real_path_begins_eat(str, directory()->download()))
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

      if (directory()->image().has_character() && path.case_insensitive_order(directory()->image()) == 0)
      {

         return "Image";

      }
      else if (directory()->music().has_character() && path.case_insensitive_order(directory()->music()) == 0)
      {

         return "Music";

      }
      else if (directory()->video().has_character() && path.case_insensitive_order(directory()->video()) == 0)
      {

         return "Video";

      }
      else if (directory()->document().has_character() && path.case_insensitive_order(directory()->document()) == 0)
      {

         return "Document";

      }
      else if (directory()->download().has_character() && path.case_insensitive_order(directory()->download()) == 0)
      {

         return "Download";

      }
      else if (directory()->desktop().has_character() && path.case_insensitive_order(directory()->desktop()) == 0)
      {

         return "Desktop";

      }
      else if (directory()->bookmark().has_character() && path.case_insensitive_order(directory()->bookmark()) == 0)
      {

         return "Bookmark";

      }
      else if (directory()->bookmark().has_character() && path == "/")
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

      return ::platform::context::defer_process_path(path);
   //
   //    if (path.flags() & ::file::e_flag_final_path)
   //    {
   //
   //       return path;
   //
   //    }
   //
   //    path = _defer_process_path(path);
   //
   //    if (path.flags() & ::file::e_flag_resolve_alias)
   //    {
   //
   //       while (true)
   //       {
   //
   //          try
   //          {
   //
   //             __keep_task_flag(e_task_flag_resolve_alias);
   //
   //             //if (!os_resolve_alias(path, path,::is_set(get_app())? get_app()->m_puiCurrent.get(): nullptr))
   //             auto plink = os_resolve_alias(path);
   //
   //             if(!plink || plink->m_pathTarget.is_empty() || plink->m_pathTarget == path)
   //             {
   //
   //                break;
   //
   //             }
   //
   //             path = plink->m_pathTarget;
   //
   //          }
   //          catch (...)
   //          {
   //
   //          }
   //
   //          path = _defer_process_path(path);
   //
   //       }
   //
   //    }
   //
   //    path.flags().set(::file::e_flag_final_path);
   //
   //    return path;
   //
   }


   ::file::path context::_defer_process_path(::file::path path)
   {

      return ::platform::context::_defer_process_path(path);

   }


   ::file::path context::__defer_process_path(::file::path path)
   {

      return ::platform::context::__defer_process_path(path);

   }


   bool context::defer_process_media_library_path(::file::path & path)
   {

      return directory_system()->defer_process_media_library_path(path);

   }


   bool context::_001IsProtocol(::file::path & path, const ::scoped_string & scopedstrProtocol)
   {

      if (path.case_insensitive_begins_eat(scopedstrProtocol))
      {

         return true;

      }
      else if ((path.length() <= scopedstrProtocol.size()) && path.case_insensitive_begins(scopedstrProtocol(0, scopedstrProtocol.size() - 3)))
      {

         path.clear();

         return true;

      }

      return false;

   }
   

   void context::defer_calculate_fs_raw_folder_protocols()
   {

      if (application()->m_bEnableFsRawFolderProtocols)
      {

         if (m_bModifiedFsRawFolderProtocols)
         {

            m_bModifiedFsRawFolderProtocols = false;

            auto pcomponent = system()->component("fs_raw_folder_protocol");

            ::cast < ::database::client > pdatabaseclient = pcomponent;

            if (pdatabaseclient)
            {

               ::cast < ::database::client > pdatabaseclientApp = application();

               if (pdatabaseclientApp)
               {

                  pdatabaseclient->initialize_data_client(pdatabaseclientApp->m_pdataserver);

               }

            }

            pcomponent->update();

            if (pcomponent)
            {

               for (auto& strInstalled : pcomponent->m_straImplementationInstalled)
               {

                  try
                  {

                     auto pimplementation = pcomponent->implementation(strInstalled);

                     ::pointer < ::fs::raw_folder_protocol > prawfolderprotocol = pimplementation;

                     if (::is_set(prawfolderprotocol))
                     {

                        if (prawfolderprotocol->is_installed())
                        {

                           ::string strProtocol = prawfolderprotocol->protocol();

                           if (strProtocol.has_character())
                           {

                              m_mapFsRawFolderProtocol[strProtocol] = prawfolderprotocol;

                           }

                        }


                     }


                  }
                  catch (...)
                  {


                  }


               }


            }

         }

      }

   }
   

   bool context::defer_process_fs_raw_folder_protocol_path(::file::path & path)
   {

      defer_calculate_fs_raw_folder_protocols();

      for (auto & pair : m_mapFsRawFolderProtocol)
      {

         auto strProtocol = pair.element1();

         auto pfsrawfolderprotocol = pair.element2();

         if (::is_set(pfsrawfolderprotocol)
            && pfsrawfolderprotocol->is_installed())
         {

            if (_001IsProtocol(path, strProtocol + ":/"))
            {

               path = pfsrawfolderprotocol->raw_path(path);

               return true;

            }
            else if (_001IsProtocol(path, strProtocol + "-app:/"))
            {

               ::file::path pathApp = "application";

               pathApp /= application()->m_strAppId;

               pathApp /= path;

               path = pfsrawfolderprotocol->raw_path(pathApp);

               return true;

            }

         }

      }

      return false;

   }



   bool context::is_fs_raw_folder_protocol_installed(const ::scoped_string & scopedstrProtocol)
   {

      defer_calculate_fs_raw_folder_protocols();

      for (auto & pair : m_mapFsRawFolderProtocol)
      {

         auto strProtocol = pair.element1();

         auto pfsrawfolderprotocol = pair.element2();

         if (::is_set(pfsrawfolderprotocol)
            && pfsrawfolderprotocol->is_installed()
            && scopedstrProtocol == strProtocol)
         {

            return true;

         }

      }

      return false;

   }


   //else if (node()->_is_dropbox_installed() && _001IsProtocol(path, "dropbox:/"))

   bool context::defer_process_known_folder_path(::file::path & path)
   {

      if (_001IsProtocol(path, "music:/"))
      {

         path = directory()->music() / path;

      }
      else if (_001IsProtocol(path, "video:/"))
      {

         path = directory()->video() / path;

      }
      else if (_001IsProtocol(path, "image:/"))
      {

         path = directory()->image() / path;

      }
      else if (_001IsProtocol(path, "document:/"))
      {

         path = directory()->document() / path;

      }
      //else if (node()->_is_dropbox_installed() && _001IsProtocol(path, "dropbox:/"))
      //{

      //   path = directory()->dropbox() / path;

      //}
      //else if (node()->_is_dropbox_installed() && _001IsProtocol(path, "dropbox-app:/"))
      //{

      //   auto papplication = application();

      //   if (!papplication || papplication->m_strAppId.is_empty())
      //   {

      //      return false;

      //   }

      //   path = directory()->dropbox_app() / path;

      //}
      else if (node()->_is_onedrive_installed() && _001IsProtocol(path, "onedrive:/"))
      {

         path = directory()->onedrive() / path;

      }
      else if (_001IsProtocol(path, "appconfig:/"))
      {

         path = get_app()->appconfig_folder() / path;

      }
      else if (_001IsProtocol(path, "download:/"))
      {

         path = directory()->download() / path;

      }
      else if (_001IsProtocol(path, "usersystem:/"))
      {

         path = directory_system()->userconfig() / path;

      }
      else if (_001IsProtocol(path, "desktop:/"))
      {

         path = directory()->desktop() / path;

      }
      else if (_001IsProtocol(path, "bookmark:/"))
      {

         path = directory()->bookmark() / path;

      }
      else
      {

         return false;

      }

      return true;

   }


   bool context::defer_process_protocol_path(::file::path & path)
   {
      
      return path_system()->defer_process_protocol_path(path);
      
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

         informationf(strMessage);

         return nullptr;

      }

   }



   //
   //CLASS_DECL_APEX  bool _os_may_have_alias(const ::scoped_string & scopedstr)
   //{
   //
   //   string str(scopedstr);
   //
   //   return str.case_insensitive_ends(".lnk") || str.case_insensitive_contains(".lnk/") || str.case_insensitive_contains(".lnk\\");
   //
   //}


   ::pointer < ::file::link > context::os_resolve_alias(const ::file::path & path, bool bNoUI, bool bNoMount)
   {

      return ::platform::context::os_resolve_alias(path, bNoUI, bNoMount);

      // auto plink = _os_resolve_alias(path, bNoUI, bNoMount);
      //
      // if(plink)
      // {
      //
      //    return plink;
      //
      // }
      //
      // if (_os_has_alias_in_path(path))
      // {
      //
      //    ::pointer < ::file::link > plink;
      //
      //    ::file::path_array patha;
      //
      //    ::file::path_array pathaRelative;
      //
      //    ascendants_path(path, patha, &pathaRelative);
      //
      //    for (::collection::index i = 0; i < patha.get_count(); i++)
      //    {
      //
      //       ::file::path pathAlias = patha[i];
      //
      //       auto plinkHere = _os_resolve_alias(pathAlias, bNoUI, bNoMount);
      //
      //       if(plinkHere)
      //       {
      //
      //          plink = plinkHere;
      //
      //          plink->m_pathTarget /= pathaRelative[i];
      //
      //       }
      //
      //    }
      //
      //    return plink;
      //
      // }
      //
      // return nullptr;

   }


   bool context::_os_has_alias_in_path(const ::file::path & path, bool bNoUI, bool bNoMount)
   {

      return ::platform::context::_os_has_alias_in_path(path, bNoUI, bNoMount);

      //return node()->has_alias_in_path(path);

   }



   ::pointer < ::file::link > context::_os_resolve_alias(const ::file::path & path, bool bNoUI, bool bNoMount)
   {

      return ::platform::context::_os_resolve_alias(path, bNoUI, bNoMount);

      // if (os_is_alias(path))
      // {
      //
      //    return path_system()->resolve_link(path);
      //
      // }
      //
      // return nullptr;

   }

//
//#ifdef WINDOWS
//
   bool context::os_is_alias(const ::file::path & path)
   {

      return ::platform::context::os_is_alias(path);

//      return node()->is_alias(path);

      //return case_insensitive_string_ends(scopedstr, ".lnk");

   }
//
//#endif
//

   bool context::enumerate(::file::listing & listing)
   {

      return directory()->enumerate(listing);

   }


   /*bool context::perform_file_relative_name_listing(::file::listing & listing)
   {

      return directory()->ls_relative_name(listing);

   }*/

   //
   // string context::get(const ::scoped_string & scopedstrUrl, ::property_set & set)
   // {
   //
   //    __UNREFERENCED_PARAMETER(strUrl);
   //    __UNREFERENCED_PARAMETER(set);
   //
   //    return "";
   //
   // }
   //

   //::handle::ini context::ini_from_path(::file::path & path)
   //{

   //   ::handle::ini ini;

   //   ::file_pointer pfile;

   //   if (directory()->is(path))
   //   {

   //      pfile = file()->get_reader(path / "this.ini");

   //      //string str;

   //      //pfile->full_read_string(str);

   //      //ini.parse_ini(str);

   //   }
   //   else if (file()->exists(path))
   //   {

   //      pfile = file()->get_reader(path);
   //      //ini.parse_ini_file(file()->get_file());

   //   }

   //   if (pfile)
   //   {

   //      auto str = pfile->full_string();

   //      ini.parse_ini(str);

   //   }

   //   return ini;

   //}


   //::handle::ini context::local_ini()
   //{

   //   ::file::path pathFolder = directory_system()->localconfig();

   //   return ini_from_path(pathFolder);

   //}




   // bool context::http_download(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrFile)
   // {
   //
   //    string strUrl = scopedstrUrl;
   //
   //    ::property_set set;
   //
   //    set["raw_http"] = true;
   //
   //    set["disable_common_name_cert_check"] = true;
   //
   //    return http()->download(strUrl, scopedstrFile, set);
   //
   // }


   // string context::http_get(const ::scoped_string & scopedstrUrl)
   // {
   //
   //    ::property_set set;
   //
   //    set["get_response"] = "";
   //
   //    set["raw_http"] = true;
   //
   //    set["disable_common_name_cert_check"] = true;
   //
   //    string strResponse;
   //
   //    http()->get(strResponse, scopedstrUrl, set);
   //
   //    //if (!http()->get(strResponse, pszUrl, set))
   //    //{
   //
   //    //   return "";
   //
   //    //}
   //
   //    return strResponse;
   //
   // }


   ::file::path context::sys_path(const ::scoped_string & scopedstrPath)
   {

      return directory_system()->config() / scopedstrPath;

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

   void context::save_to_file(const ::payload& payloadFile, const ::particle* pparticle)
   {
   }


   void context::save_to_file(const ::payload& payloadFile,const ::payload * ppayload,  const ::particle* pparticle)
   {
   }
   void context::load_from_file(::particle* pparticle, const ::payload& payloadFile)
   {
   }
   void context::load_from_file(::particle* pparticle, const ::payload& payloadFile,const ::payload * ppayload)
   {
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

      auto pfile = file()->get_file(payloadFile, eopen, pfileexception);

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

         m_payloadFile.payload_array_reference().add(prequest->m_payloadFile);

      }

      property_set().merge(prequest->property_set());

      on_request(prequest);

   }


   bool context::contains(::request * prequest) const
   {
      return ::handler::handler::contains(prequest);
   }


   string context::command_line_text() const
   {

      return ::handler::handler::command_line_text();


   }


   void context::destroy()
   {

      ::handler::handler::destroy();

      ::thread::destroy();

      ::platform::context::destroy();

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

      ::handler::handler::post_request(prequest);


   }


   bool context::on_idle()
   {

      return ::handler::handler::on_idle();

   }



   string context::get_store_server_base_url()
   {

      return m_strStoreServerBaseUrl;

   }


   //bool context::os_is_alias(const_char_pointer psz)
   //{

   //   return false;

   //}


//   ::string context::http_text(const ::scoped_string & scopedstrUrl, ::property_set & set)
//   {
//
//      return http()->get(scopedstrUrl, set);
//
//   }
//
//
//   void context::http_download(const ::payload & payloadFile, const ::scoped_string & scopedstrUrl, ::property_set & set)
//   {
//
//      http()->download(scopedstrUrl, payloadFile, set);
//
//   }

   //
   // void context::perform(::nano::http::get * pget)
   // {
   //
   //    http()->perform(pget);
   //
   // }

   //
   // ::url::url context::http_get_effective_url(const ::url::url & url)
   // {
   //
   //    return http()->get_effective_url(url);
   //
   // }
   //

} // namespace apex



