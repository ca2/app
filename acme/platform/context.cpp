//Created by camilo on 2021-03-26 00:44 BRT <3ThomasBS_
#include "framework.h"
#include "context.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/filesystem/dir_context.h"
#include "acme/filesystem/filesystem/dir_system.h"
#include "acme/parallelization/counter.h"
#include "acme/parallelization/fork.h"
#include "acme/parallelization/retry.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/application.h"
#include "acme/platform/nano_http.h"
#include "acme/platform/nano_http_response.h"
#include "acme/platform/node.h"
#include "acme/platform/session.h"
#include "acme/platform/system.h"
#include "acme/primitive/text/data.h"
#include "acme/primitive/text/text.h"
#include "acme/primitive/text/translator.h"


namespace acme
{

   
   context::context()
   {

      m_pplatform = nullptr;

      m_pcontext = this;

      m_papexcontext = nullptr;
      m_pauracontext = nullptr;


      m_pacmeapplication = nullptr;
      m_pacmesession = nullptr;
      m_pacmesystem = nullptr;
      m_pacmenode = nullptr;
      
//      m_ptexttranslator = __new< ::text::translator >();
//
//      m_ptexttranslator->m_pcontext = this;

   }


   context::~context()
   {

      //::release(m_ptexttranslator);

   }


   void context::on_set_platform()
   {


   }


   void context::set_platform(::platform::platform * pplatform)
   {

      m_pplatform = pplatform;

      on_set_platform();

   }


   void context::initialize(::particle * pparticle)
   {

      ::task::initialize(pparticle);

      if(!m_pacmesystem)
      {

         m_pacmesystem = pparticle->m_pcontext->m_pacmesystem;

      }

      if(!m_pacmesession)
      {

         m_pacmesession = pparticle->m_pcontext->m_pacmesession;

      }

      if(!m_pacmeapplication)
      {

         m_pacmeapplication = pparticle->m_pcontext->m_pacmeapplication;

      }

      if (!m_pacmenode)
      {

         m_pacmenode = pparticle->m_pcontext->m_pacmenode;

      }

      m_pcontext = this;

   }


   bool context::is_system() const
   {

      return false;

   }


   bool context::is_session() const
   {

      return false;

   }



   void context::initialize_context()
   {

      __construct_new(m_ptexttranslator);


      //auto estatus =


      //if(!estatus)
      //{

      //   return estatus;

      //}

      /*estatus = */ __construct(m_pfile);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus =
      __construct(m_pdir);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //m_papexsystem = system()->m_papexsystem;
      //m_paurasystem = system()->m_paurasystem;
      //m_pbasesystem = system()->m_pbasesystem;
      //m_pbredsystem = system()->m_pbredsystem;
      //m_pcoresystem = system()->m_pcoresystem;

      if (is_system())
      {

         auto psystem = system()->m_papexsystem;

         //m_papexsession->initialize(psystem);

         ////estatus = m_papexsession->initialize_context();

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //estatus = 
         m_pfile->init_system();

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //estatus = 
         m_pdir->init_system();

         //if (!estatus)
         //{

         //   return estatus;

         //}

      }

      //estatus = 
      m_pfile->init_context();

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      m_pdir->init_context();

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 

      /*    if (!estatus)
          {

             return estatus;

          }*/

          //on_update_matter_locator();

          //return ::success;



   }


   void context::initialize_context_1()
   {


   }


   void context::finalize_context()
   {

      try
      {
         m_pdir->term_context();
      }
      catch (...)
      {

      }
      try
      {
         m_pfile->term_context();
      }
      catch (...)
      {

      }
      try
      {
         m_pdir->term_system();
      }
      catch (...)
      {

      }
      try
      {
         m_pfile->term_system();
      }
      catch (...)
      {

      }

      try
      {
         m_pdir->finalize();
      }
      catch (...)
      {

      }


      try
      {
         m_pfile->finalize();
      }
      catch (...)
      {

      }

      m_pdir.release();

      m_pfile.release();

      m_ptexttranslator.release();

   }


   ::dir_context* context::dir()
   {
      if (!m_pdir)
      {

         initialize_context();

      }
      
      
      return m_pdir; 
   }

   ::file_context* context::file() 
   {
      if (!m_pfile)
      {

         initialize_context();

      }
      return m_pfile; 
   }



   ::dir_system * context::dirsystem()
   {

      return m_pacmesystem->m_pdirsystem;

   }


   ::file_system * context::filesystem()
   {

      return m_pacmesystem->m_pfilesystem;

   }


   void context::translate_text_data(::text::data * ptextdata)
   {

      bool bSet = false;

      if (ptextdata->m_atom.is_text())
      {

         if (ptextdata->m_atom.m_str.begins("text://"))
         {

            auto psz = ansi_rchr(ptextdata->m_atom.m_str.c_str() + 7, '/');

            if (psz)
            {

               ptextdata->m_str = psz + 1;

               return;

            }

         }

      }

      ptextdata->m_str = ptextdata->m_atom;

   }


   ::text::text context::__text(const ::atom& atom)
   {

      return m_ptexttranslator->create_text_data(atom);

   }


   //::platform::platform * context::platform() const
   //{

   //   return ((context*)this)->m_pplatform;

   //}



   ::acme_file* context::acmefile() { return m_pacmesystem->m_pacmefile; }
   ::acme_path* context::acmepath() { return m_pacmesystem->m_pacmepath; }
   ::acme_directory* context::acmedirectory() { return m_pacmesystem->m_pacmedirectory; }
   ::acme::node* context::node() { return m_pacmesystem->node(); }



   ::payload context::file_payload(const ::payload & payloadFile)
   {

      return payloadFile;

   }


//   file_pointer context::get_file(const ::payload& payloadFile, ::file::e_open eopen)
//   {
//
//      auto pfile = __create < ::file::file >();
//
//      auto path = payloadFile.file_path();
//
//      pfile->open(path, eopen);
//
//      return pfile;
//
//   }


   ::file::path context::defer_process_path(::file::path path)
   {

      return path;

   }


   void context::fork_count(::count iCount, const ::function < void(index, index, index, index) > & function, const ::procedure & procedureCompletion, index iStart)
   {

      int iAffinityOrder = node()->get_current_process_affinity_order();

      if (::get_task() != nullptr && ::get_task()->m_bAvoidProcedureFork)
      {

         iAffinityOrder = 1;

      }

      ::count cScan = maximum(1, minimum(iCount - iStart, iAffinityOrder));

      auto pcounter = __allocate< ::parallelization::counter >(cScan, procedureCompletion);

      auto ptask = ::get_task();

      for (index iOrder = 0; iOrder < cScan; iOrder++)
      {

         auto ppredtask = __allocate< forking_count_task >(this, iOrder, iOrder + iStart, cScan, iCount, function);

         //if (::is_set(ptask))
         //{

         //   ptask->add_reference(ppredtask);

         //}

         ppredtask->m_pcounter = pcounter;

         ppredtask->branch();

      }

      //return pcounter;

   }


   string context::get_locale()
   {

      return m_strLocale;

   }


   string context::get_schema()
   {

      return m_strSchema;

   }


   void context::locale_schema_matter(string_array& stra, const string_array& straMatterLocator, const ::string& strLocale, const ::string& strSchema)
   {

      if (get_app())
      {

         get_app()->locale_schema_matter(stra, straMatterLocator, strLocale, strSchema);

      }
      else if (session()->m_papexsession)
      {

         session()->locale_schema_matter(stra, straMatterLocator, strLocale, strSchema);

      }
      else
      {

         auto psystem = system();

         if (psystem)
         {

            psystem->locale_schema_matter(stra, straMatterLocator, strLocale, strSchema);

         }

      }

   }


   string context::get_locale_schema_dir()
   {

      if (get_app())
      {

         return get_app()->get_locale_schema_dir();

      }
      else if (session())
      {

         return session()->get_locale_schema_dir();

      }
      else
      {

         auto psystem = system();

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


   ::file::path context::defer_process_matter_path(::file::path path)
   {

      if (string_begins_ci(path, "matter:/"))
      {

         return dir()->matter(path);

      }

      if (path.case_insensitive_begins("appmatter:/"))
      {

         //path = dir()->appmatter(path, false);
         return dir()->appmatter(path);

      }

      if (path.case_insensitive_begins_eat("icon:/"))
      {

         path += ".ico";

         return dir()->matter(path);

      }

      return path;

   }





   ::file::path context::get_matter_path(string strMatter)
   {

      if (strMatter.case_insensitive_begins_eat("appmatter:/"))
      {

         return dir()->install() / strMatter;

      }

      return strMatter;

   }


   ::file::path context::side_get_matter_path(string strMatter)
   {

      auto psystem = system();

      auto pdirsystem = psystem->m_pdirsystem;

      ::file::path pathResource = pdirsystem->m_pathInstall;

#ifdef __APPLE__

      pathResource = pathResource / "Contents/Resources/appmatter";

#endif

      return pathResource / strMatter;

   }


   ::file::path context::get_matter_cache_path(::file::path path)
   {

      if (path.case_insensitive_begins_eat("appmatter:/"))
      {

         auto psystem = system();

         ::file::path pathCache = psystem->m_pdirsystem->m_pathLocalAppMatterFolder / path;

         if (path.flags().has(::file::e_flag_get_local_path)
            || (path.flags().is_clear(::file::e_flag_bypass_cache)
               && ::is_file_or_folder(acmepath()->get_type(pathCache))))
         {

            return pathCache;

         }

         ::file::path pathMeta = pathCache + ".meta_information";

         retry retry(500_ms, 1_minute);

         if (path.flags().is_clear(::file::e_flag_bypass_cache))
         {

            string strFirstLine = acmefile()->line(pathMeta, 0);

            if (strFirstLine == "itdoesntexist" && path.flags().is_clear(::file::e_flag_required))
            {

               return "";

            }
            else if (strFirstLine == "processing")
            {

               if (!retry([this, pathMeta]()
                  {

                     return acmefile()->line(pathMeta, 0) != "processing";

                  }))
               {

                  return "";

               }

            }

         }

         ::file::path pathSide = side_get_matter_path(path);

         auto etype = acmepath()->get_type(pathSide);

         if (::is_file_or_folder(etype))
         {

            if (etype == ::file::e_type_file)
            {

               file()->copy(pathCache, pathSide, true);

            }
            else if (etype == ::file::e_type_folder)
            {

               dir()->create(pathCache);

            }

            return pathCache;

         }

         //auto psystem = system()->m_papexsystem;

         if (!psystem->m_pdirsystem->m_bMatterFromHttpCache)
         {

            return "";

         }

         path.case_insensitive_begins_eat("appmatter:/");

         path = "https://ca2.software/matter" / path;

         //if (file()->exists(path, this))
         {


            property_set set;

            set["raw_http"] = true;

            set["disable_common_name_cert_check"] = true;

            memory_file_pointer pfile(e_create_new, this);

            if (!retry([&]()
               {

                  ::particle * pparticle = this;

                  return pparticle->context()->http_download(pfile, path, set);

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

                        return dir()->create(pathCache);

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

                     return acmefile()->set_line(pathMeta, 0, strFsType);

                  }))
               {

                  return "";

               }

            }
            else
            {
               retry([&]()
                  {

                     return acmefile()->set_line(pathMeta, 0, "itdoesntexist");

                  });
               return "";
            }



         }
         //         else if (dir()->is(path, this))
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


   string context::matter_locator(::acme::application* papp)
   {

      return ::file::path(papp->m_strRoot) / "_matter" / papp->m_strDomain;

   }


   void context::add_matter_locator(string strApp)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      string strMatterLocator = matter_locator(strApp);

      m_straMatterLocatorPriority.add(strMatterLocator);

   }


   void context::add_matter_locator(::acme::application* papp)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      string strMatterLocator = matter_locator(papp);

      add_matter_locator(strMatterLocator);

      //on_update_matter_locator();

   }


   bool context::http_exists(const ::scoped_string & scopedstrUrl, ::property_set & set)
   {

      throw ::interface_only();

      return false;


   }


   ::file::enum_type context::http_get_type(const ::scoped_string & scopedstrUrl, property_set & set)
   {

      throw ::interface_only();

      return ::file::e_type_unknown;

   }


   ::file::enum_type context::http_get_type(const ::scoped_string & scopedstrUrl, ::payload * pvarQuery, property_set & set)
   {

      throw ::interface_only();

      return ::file::e_type_unknown;

   }



   ::string context::http_text(const ::scoped_string & scopedstrUrl)
   {

      auto memory = http_memory(scopedstrUrl);

      ::string str = memory.as_utf8();

      return str;

   }


   ::string context::http_text(const ::scoped_string & scopedstrUrl, ::property_set & set)
   {

      auto memory = http_memory(scopedstrUrl, set);

      ::string str = memory.as_utf8();

      return str;

   }


   ::memory context::http_memory(const ::scoped_string & scopedstrUrl)
   {

      property_set set;

      set["raw_http"] = true;

      set["disable_common_name_cert_check"] = true;

      return http_memory(scopedstrUrl, set);

   }


   ::memory context::http_memory(const ::scoped_string & scopedstrUrl, ::property_set & set)
   {

      //UNREFERENCED_PARAMETER(pcontext);

      try
      {

         ::memory memory;

         ::nano::http_response httpresponse(set, memory);

         system()->nano_http()->memory(scopedstrUrl, httpresponse);

         return ::transfer(memory);

      }
      catch (...)
      {

         set["timeout"] = true;

         return {};

      }

      //return pasynchronousehttpresponse->m_data.m_memory;

   }


   void context::http_download(const ::payload & payloadFile, const ::scoped_string & scopedstrUrl)
   {

      auto pfile = acmefile()->get_writer(payloadFile);

      auto memory = http_memory(scopedstrUrl);

      pfile->write(memory.data(), memory.size());

   }


   void context::http_download(const ::payload & payloadFile, const ::scoped_string & scopedstrUrl, ::property_set & set)
   {

      auto pfile = acmefile()->get_writer(payloadFile);

      auto memory = http_memory(scopedstrUrl, set);

      pfile->write(memory.data(), memory.size());

   }


} // namespace acme



