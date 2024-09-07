#include "framework.h"
#include "context.h"
#include "acme/platform/application.h"
#include "apex/platform/system.h"
#include "aura/graphics/image/context.h"


namespace aura
{


   context::context()
   {

      m_pauracontext = this;

   }


   context::~context()
   {

   }


   void context::initialize_context()
   {

      //auto estatus =

      ::apex::context::initialize_context();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return ::success;

   }


   void context::initialize_context_1()
   {

      ::apex::context::initialize_context_1();

      defer_initialize_context_image();

   }


   void context::defer_initialize_context_image()
   {

      if (application()->m_bImaging)
      {

         try
         {

            __construct(m_pimagecontext);

         }
         catch (...)
         {


         }

      }

   }


   void context::finalize()
   {

      if (m_pimagecontext)
      {

         try
         {

            m_pimagecontext->finalize();

         }
         catch (...)
         {


         }

      }

      m_pimagecontext.release();


      apex::context::finalize();

   }


   //pointer< ::extended::sequence < ::conversation > > context::message_box(::user::interaction * puserinteraction, const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox)
   //{

   //   auto pmessagebox = __create < ::user::message_box >();

   //   auto pfuture = pmessagebox->::extended::asynchronous<::conversation>::sequence();

   //   auto pextendedfuture = pmessagebox->show(puserinteraction, strMessage, strTitle, emessagebox);

   //   return pextendedfuture;

   //}


//   ::file::path context::defer_make_file_system_url(string str)
//   {
//
//      if (str.is_empty())
//      {
//
//         return "";
//
//      }
//
//      auto& dir = this->dir();
//
//      if (dir.image().has_char() && ::file::case_insensitive_begins_eat(str, dir.image()))
//      {
//
//         return ::file::path("image://") / str;
//
//      }
//      else if (dir.music().has_char() && ::file::case_insensitive_begins_eat(str, dir.music()))
//      {
//
//         return ::file::path("music://") / str;
//
//      }
//      else if (dir.video().has_char() && ::file::case_insensitive_begins_eat(str, dir.video()))
//      {
//
//         return ::file::path("video://") / str;
//
//      }
//      else if (dir.document().has_char() && ::file::case_insensitive_begins_eat(str, dir.document()))
//      {
//
//         return ::file::path("document://") / str;
//
//      }
//      else if (dir.download().has_char() && ::file::case_insensitive_begins_eat(str, dir.download()))
//      {
//
//         return ::file::path("download://") / str;
//
//      }
//      else
//      {
//
//         return str;
//
//      }
//
//   }
//
//
//   string context::defer_get_file_title(string strParam)
//   {
//
//      if (strParam.is_empty())
//      {
//
//         return "";
//
//      }
//
//      ::file::path path = defer_process_path(strParam);
//
//      auto& dir = this->dir();
//
//      if (dir.image().has_char() && path.case_insensitive_order(dir.image()) == 0)
//      {
//
//         return "Image";
//
//      }
//      else if (dir.music().has_char() && path.case_insensitive_order(dir.music()) == 0)
//      {
//
//         return "Music";
//
//      }
//      else if (dir.video().has_char() && path.case_insensitive_order(dir.video()) == 0)
//      {
//
//         return "Video";
//
//      }
//      else if (dir.document().has_char() && path.case_insensitive_order(dir.document()) == 0)
//      {
//
//         return "Document";
//
//      }
//      else if (dir.download().has_char() && path.case_insensitive_order(dir.download()) == 0)
//      {
//
//         return "Download";
//
//      }
//      else if (dir.desktop().has_char() && path.case_insensitive_order(dir.desktop()) == 0)
//      {
//
//         return "Desktop";
//
//      }
//      else if (dir.bookmark().has_char() && path.case_insensitive_order(dir.bookmark()) == 0)
//      {
//
//         return "Bookmark";
//
//      }
//      else
//      {
//
//         return path.title();
//
//      }
//
//   }
//
//
//   ::file::path context::defer_process_path(::file::path path)
//   {
//
//      path = _defer_process_path(path);
//
//      if (path & ::file::e_flag_resolve_alias)
//      {
//
//         while (true)
//         {
//
//            try
//            {
//
//               __keep_thread_flag(id_thread_resolve_alias);
//
//               //if (!os_resolve_alias(path, path,::is_set(get_app())? get_app()->m_puiCurrent.get(): nullptr))
//               if (!os_resolve_alias(path, path))
//               {
//
//                  break;
//
//               }
//
//            }
//            catch (...)
//            {
//
//            }
//
//            path = _defer_process_path(path);
//
//         }
//
//      }
//
//      return path;
//
//   }
//
//
//   ::file::path context::_defer_process_path(::file::path path)
//   {
//
//      ::file::path pathProcess = __defer_process_path(path);
//
//      if ((path & ::file::e_flag_required)
//         && pathProcess.is_empty()
//         && !(path & ::file::e_flag_bypass_cache))
//      {
//
//         path |= ::file::e_flag_bypass_cache;
//
//         pathProcess = __defer_process_path(path);
//
//      }
//
//      return pathProcess;
//
//   }
//
//
//   ::file::path context::__defer_process_path(::file::path path)
//   {
//
//      path = defer_process_matter_path(path);
//
//      if (path.case_insensitive_begins_eat("music://"))
//      {
//
//         path = dir()->music() / path;
//
//      }
//      else if (path.case_insensitive_begins_eat("video://"))
//      {
//
//         path = dir()->video() / path;
//
//      }
//      else if (path.case_insensitive_begins_eat("image://"))
//      {
//
//         path = dir()->image() / path;
//
//      }
//      else if (path.case_insensitive_begins_eat("document://"))
//      {
//
//         path = dir()->document() / path;
//
//      }
//      else if (path.case_insensitive_begins_eat("dropbox://"))
//      {
//
//         path = dir()->dropbox() / path;
//
//      }
//      else if (path.case_insensitive_begins_eat("onedrive://"))
//      {
//
//         path = dir()->onedrive() / path;
//
//      }
//      else if (path.case_insensitive_begins_eat("appconfig://"))
//      {
//
//         path = get_app()->appconfig_folder() / path;
//
//      }
//      else if (path.case_insensitive_begins_eat("download://"))
//      {
//
//         path = dir()->download() / path;
//
//      }
//      else if (path.case_insensitive_begins_eat("usersystem://"))
//      {
//
//         path = acmedirectory()->system() / path;
//
//      }
//      else if (path.case_insensitive_begins_eat("desktop://"))
//      {
//
//         path = dir()->desktop() / path;
//
//      }
//      else if (path.case_insensitive_begins_eat("bookmark://"))
//      {
//
//         path = dir()->bookmark() / path;
//
//      }
//
//      return path;
//
//   }
//
//
//   ::file::path context::full_process_path(::file::path path)
//   {
//
//      if (!(path & ::file::e_flag_dont_resolve_alias))
//      {
//
//         path |= ::file::e_flag_resolve_alias;
//
//      }
//
//      return defer_process_path(path);
//
//   }
//
//
//   ::file::path context::defer_process_matter_path(::file::path path)
//   {
//
//      if (case_insensitive_string_begins(path, "matter://"))
//      {
//
//         path = dir()->matter(path, false);
//
//      }
//
//      if (path.case_insensitive_begins("appmatter://"))
//      {
//
//         path = get_matter_cache_path(path);
//
//      }
//
//      return path;
//
//   }
//
//   ::file::path context::get_matter_path(string strMatter)
//   {
//
//      if (strMatter.case_insensitive_begins_eat("appmatter://"))
//      {
//
//         return dir()->install() / strMatter;
//
//      }
//
//      return strMatter;
//
//   }
//
//
//   ::file::path context::side_get_matter_path(string strMatter)
//   {
//
//      auto psystem = system()->m_papexsystem;
//
//      auto pdirsystem = psystem->m_pdirsystem;
//
//      ::file::path pathResource = pdirsystem->m_pathInstall;
//
//#ifdef __APPLE__
//
//      pathResource = pathResource / "Contents/Resources/appmatter";
//
//#endif
//
//      return pathResource / strMatter;
//
//   }
//
//
//   ::file::path context::get_matter_cache_path(::file::path path)
//   {
//
//      if (::str::case_insensitive_begins_eat((string&)path, "appmatter://"))
//      {
//
//         auto psystem = system()->m_papexsystem;
//
//         ::file::path pathCache = psystem->m_pdirsystem->m_pathLocalAppMatterFolder / path;
//
//         if ((path & ::file::e_flag_get_local_path)
//            || (!(path & ::file::e_flag_bypass_cache) && acmepath()->is_file_or_dir(pathCache, nullptr)))
//         {
//
//            return pathCache;
//
//         }
//
//         ::file::path pathMeta = pathCache + ".meta_information";
//
//         retry retry(::time(500), one_minute());
//
//         if (!(path & ::file::e_flag_bypass_cache))
//         {
//
//            string strFirstLine = acmefile()->line(pathMeta, 0);
//
//            if (strFirstLine == "itdoesntexist" && !(path & ::file::e_flag_required))
//            {
//
//               return "";
//
//            }
//            else if (strFirstLine == "processing")
//            {
//
//               if (!retry([pathMeta]()
//               {
//
//                  return acmefile()->line(pathMeta, 0) != "processing";
//
//               }))
//               {
//
//                  return "";
//
//               }
//
//            }
//
//         }
//
//         ::file::path pathSide = side_get_matter_path(path);
//
//         ::file::enum_type etype = ::file::e_type_none;
//
//         if (acmepath()->is_file_or_dir(pathSide, &etype))
//         {
//
//            if (etype == ::file::e_type_file)
//            {
//
//               file()->copy(pathCache, pathSide, true);
//
//            }
//            else if (etype == ::file::e_type_folder)
//            {
//
//               dir()->mk(pathCache);
//
//            }
//
//            return pathCache;
//
//         }
//
//         //auto psystem = system()->m_papexsystem;
//
//         if (!psystem->m_pdirsystem->m_bMatterFromHttpCache)
//         {
//
//            return "";
//
//         }
//
//         path.case_insensitive_begins_eat("appmatter://");
//
//         path = string(get_server_ca2_cc()) + "matter" / path;
//
//         //if (file()->exists(path, this))
//         {
//
//
//            property_set set;
//
//            set["raw_http"] = true;
//
//            set["disable_common_name_cert_check"] = true;
//
//            memory_file_pointer pfile(e_create_new);
//
//            if (!retry([&]()
//            {
//
//               return http()->download(path, pfile, set);
//
//            }))
//            {
//
//               return "";
//
//            }
//
//            string strFsType;
//
//            strFsType = set["get_headers"]["x-fstype"];
//
//            if (strFsType.has_char())
//            {
//               if (strFsType == "directory")
//               {
//
//                  if (!retry([&]()
//                  {
//
//                     return dir()->mk(pathCache);
//
//                  }))
//                  {
//
//                     return "";
//
//                  }
//
//
//               }
//               else
//               {
//                  pfile->seek_to_begin();
//
//                  if (!retry([&]()
//                  {
//
//                     return file()->copy(pathCache, pfile, false);
//
//                  }))
//                  {
//
//                     return "";
//
//                  }
//
//               }
//
//               if (!retry([&]()
//               {
//
//                  return file_set_line_dup(pathMeta, 0, strFsType);
//
//               }))
//               {
//
//                  return "";
//
//               }
//
//            }
//            else
//            {
//               retry([&]()
//               {
//
//                  return file_set_line_dup(pathMeta, 0, "itdoesntexist");
//
//               });
//               return "";
//            }
//
//
//
//         }
//         //         else if (dir()->is(path, this))
//         //         {
//         //
//         //            if (!retry([&]()
//         //         {
//         //
//         //            return file_set_line_dup(pathMeta, 0, "directory");
//         //
//         //            }))
//         //            {
//         //
//         //               return "";
//         //
//         //            }
//
//
//         //         else
//         //         {
//         //
//         //
//         //
//         //            return "";
//         //
//         //         }
//
//         return pathCache;
//
//      }
//
//      return path;
//   }
//
//
//
//   file_pointer context::friendly_get_file(::payload payloadFile, ::file::e_open eopen)
//   {
//
//      try
//      {
//
//         return file()->get_file(payloadFile, eopen);
//
//      }
//      catch (::file::exception& e)
//      {
//
//         string strMessage = e.get_message();
//
//         message_box(strMessage);
//
//         return nullptr;
//
//      }
//
//   }
//
//   ::file::listing& context::perform_file_listing(::file::listing& listing)
//   {
//
//      return dir()->ls(listing);
//
//   }
//
//
//   ::file::listing& context::perform_file_relative_name_listing(::file::listing& listing)
//   {
//
//      return dir()->ls_relative_name(listing);
//
//   }
//
//
//   string context::http_get(const string& strUrl, ::property_set& set)
//   {
//
//      __UNREFERENCED_PARAMETER(strUrl);
//      __UNREFERENCED_PARAMETER(set);
//
//      return "";
//
//   }
//
//
//   ::handle::ini context::ini_from_path(::file::path& path)
//   {
//
//      ::handle::ini ini;
//
//      ::file_pointer pfile;
//
//      if (dir()->is(path))
//      {
//
//         pfile = file()->get_reader(path / "this.ini");
//
//         //string str;
//
//         //pfile->full_read_string(str);
//
//         //ini.parse_ini(str);
//
//      }
//      else if (file()->exists(path))
//      {
//
//         pfile = file()->get_reader(path);
//         //ini.parse_ini_file(file()->get_file());
//
//      }
//
//      if (pfile)
//      {
//
//         string str;
//
//         pfile->full_read_string(str);
//
//         ini.parse_ini(str);
//
//      }
//
//      return ini;
//
//   }
//
//
//   ::handle::ini context::local_ini()
//   {
//
//      ::file::path pathFolder = acmedirectory()->localconfig();
//
//      return ini_from_path(pathFolder);
//
//   }
//
//
//   string context::get_locale()
//   {
//
//      return m_strLocale;
//
//   }
//
//
//   string context::get_schema()
//   {
//
//      return m_strSchema;
//
//   }
//
//
//   void context::locale_schema_matter(string_array& stra, const string_array& straMatterLocator, const string& strLocale, const string& strSchema)
//   {
//
//      if (get_app())
//      {
//
//         get_app()->locale_schema_matter(stra, straMatterLocator, strLocale, strSchema);
//
//      }
//      else if (get_session())
//      {
//
//         get_session()->locale_schema_matter(stra, straMatterLocator, strLocale, strSchema);
//
//      }
//      else
//      {
//
//         auto psystem = system()->m_papexsystem;
//
//         if (psystem)
//         {
//
//            psystem->locale_schema_matter(stra, straMatterLocator, strLocale, strSchema);
//
//         }
//
//      }
//
//   }
//
//
//   string context::get_locale_schema_dir()
//   {
//
//      if (get_app())
//      {
//
//         return get_app()->get_locale_schema_dir();
//
//      }
//      else if (get_session())
//      {
//
//         return get_session()->get_locale_schema_dir();
//
//      }
//      else
//      {
//
//         auto psystem = system()->m_papexsystem;
//
//         if (psystem)
//         {
//
//            return psystem->get_locale_schema_dir();
//
//         }
//         else
//         {
//
//            return "_std/_std";
//
//         }
//
//      }
//
//   }
//
//
//   bool context::http_download(const ::string & pszUrl, const ::string & pszFile)
//   {
//
//      string strUrl = pszUrl;
//
//      property_set set;
//
//      set["raw_http"] = true;
//
//      set["disable_common_name_cert_check"] = true;
//
//      return http()->download(strUrl, pszFile, set);
//
//   }
//
//
//   string context::http_get(const ::string & pszUrl)
//   {
//
//      property_set set;
//
//      set["get_response"] = "";
//
//      set["raw_http"] = true;
//
//      set["disable_common_name_cert_check"] = true;
//
//      string strResponse;
//
//      if (!http()->get(strResponse, pszUrl, set))
//      {
//
//         return "";
//
//      }
//
//      return strResponse;
//
//   }
//
//
//   bool context::sys_set(string strPath, string strValue)
//   {
//
//      return file()->put_text_utf8(acmedirectory()->config() / strPath, strValue);
//
//   }
//
//
//   string context::sys_get(string strPath, string strDefault)
//   {
//
//      string strValue = file()->as_string(acmedirectory()->config() / strPath);
//
//      if (strValue.is_empty())
//      {
//
//         return strDefault;
//
//      }
//
//      return strValue;
//
//   }
//
//
//   string context::load_string(const ::string & psz)
//   {
//
//      return psz;
//
//   }
//
//
//   void context::on_update_matter_locator()
//   {
//
//      synchronous_lock synchronouslock(this->synchronization());
//
//      m_straMatterLocator.erase_all();
//
//      m_straMatterLocator.add(m_straMatterLocatorPriority);
//
//      m_straMatterLocator.add(matter_locator("app/main"));
//
//   }
//
//
//
//
//
//   string context::matter_locator(string strApp)
//   {
//
//      string strMatterLocator = strApp;
//
//      if (!strMatterLocator.case_insensitive_contains("/_matter/"))
//      {
//
//         string_array stra;
//
//         stra.explode("/", strMatterLocator);
//
//         if (stra.get_count() >= 2)
//         {
//
//            strMatterLocator = stra[0] + "/_matter/" + stra.slice(1).implode("/");
//
//         }
//
//      }
//
//      return strMatterLocator;
//
//   }
//
//
//   string context::matter_locator(::apex::application* papp)
//   {
//
//      return ::file::path(papp->m_strRoot) / "_matter" / papp->m_strDomain;
//
//   }
//
//
//   void context::add_matter_locator(string strApp)
//   {
//
//      synchronous_lock synchronouslock(this->synchronization());
//
//      string strMatterLocator = matter_locator(strApp);
//
//      m_straMatterLocatorPriority.add(strMatterLocator);
//
//      //   on_update_matter_locator();
//
//
//   }
//
//
//
//
//   void context::add_matter_locator(::apex::application* papp)
//   {
//
//      synchronous_lock synchronouslock(this->synchronization());
//
//      string strMatterLocator = matter_locator(papp);
//
//      add_matter_locator(strMatterLocator);
//
//      on_update_matter_locator();
//
//   }
//
//
//
//
//   void context::_load_from_file(::particle * pparticle, const ::payload& payloadFile, const ::payload& varOptions)
//   {
//
//      binary_stream reader(file()->get_reader(payloadFile));
//
//      read(reader);
//
//      return reader.m_estatus;
//
//   }
//
//
//   void context::_save_to_file(const ::payload& payloadFile, const ::payload& varOptions, const ::particle * pparticle)
//   {
//
//      binary_stream writer(file()->get_writer(payloadFile));
//
//      write(writer);
//
//      return writer.m_estatus;
//
//   }
//
//
//   void context::destroy()
//   {
//
//      auto estatus = ::object::destroy();
//
//      return estatus;
//
//   }

   //::image::image_pointer context::create_image()
   //{

   //   auto pimage = __create < ::image::image >();

   //   if (!pimage)
   //   {

   //      return nullptr;

   //   }

   //   return ::transfer(pimage);

   //}


   //::image::image_pointer context::create_image(const ::size_i32 & size, const image32_t * pcolor, int iScan, ::enum_flag eflagCreate)
   //{

   //   auto pimage = m_pcontext->__create < ::image::image >();

   //   if (!pimage)
   //   {

   //      return nullptr;

   //   }

   //   //auto estatus =
   //   pimage->create(size, eflagCreate);

   //   if (::is_set(pcolor))
   //   {

   //      pimage->map();

   //      copy_image32(pimage->data(), size.cx(), size.cy(), pimage->m_iScan, pcolor, iScan);

   //   }

   //   //if (!estatus)
   //   //{

   //   //   return nullptr;

   //   //}

   //   return ::transfer(pimage);

   //}


} // namespace apex


