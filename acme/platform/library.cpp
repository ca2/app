#include "framework.h"
#include "library.h"
////#include "acme/exception/exception.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/acme.h"
#include "acme/platform/system.h"
//#include "system_impl.h"

CLASS_DECL_ACME bool is_verbose_log();


//typedef  void(*PFN_create_factory)();


namespace acme
{


   const ::scoped_string & scopedstr_empty_app_id = "";


   library::library()
   {

      m_pfnFactory = nullptr;
      m_plibrary = nullptr;

   }


   //void library::initialize_matter(::matter * pmatter)
   //{

   //   ::matter::initialize_matter(pmatter);

   //   m_plibrary = nullptr;

   //   //m_bAutoUnload = false;

   //   //return estatus;

   //}


   //void library::initialize_library(::matter * pmatter,int iDesambig,const ::scoped_string & scopedstrRoot, const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrFolder)
   //{

   //   auto estatus = initialize_matter(pmatter);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   string strRoot(pszRoot);

   //   strRoot.trim();

   //   if (strRoot.has_char())
   //   {

   //      m_strRoot = strRoot;

   //   }
   //   else
   //   {

   //      strRoot = m_strRoot;

   //   }

   //   m_strName = ::is_null(pszName) ? strRoot : string(pszName);

   //   if (::is_set(pszFolder))
   //   {

   //      m_strFolder = pszFolder;

   //   }
   //   else
   //   {

   //      m_strFolder = m_strName;

   //   }

   //   m_bAutoUnload = false;

   //   m_plibrary = nullptr;

   //   m_strCa2Name = strRoot;

   //   if(strRoot.has_char())
   //   {

   //      m_strRoot = strRoot;

   //      if(m_strRoot.find('/') > 0)
   //      {

   //         m_strRoot = m_strRoot.substr(0, m_strRoot.find('/'));

   //      }

   //   }

   //   return estatus;

   //}


   library::~library()
   {

      close();

   }


   //void library::assert_ok() const
   //{

   //}
   //

   //void library::dump(dump_context & dumpcontext) const
   //{


   //}


   //void library::open(const ::file::path & path,bool bAutoClose,bool bCa2Path)
   void library::open(const ::file::path & path)
   {

      auto psystem = acmesystem();

      critical_section_lock synchronouslock(&psystem->m_psubsystem->m_criticalsection);

      m_strMessage.empty();

      //auto pfnNewAuraLibrary = psystem->load_(pszPath);

      //if (pfnNewAuraLibrary != nullptr)
      //{

      //   m_strPath = pszPath;

      //   if (m_strCa2Name.has_char())
      //   {

      //      __own(psystem, m_mapLibrary[m_strCa2Name], this);

      //   }

      //   return true;

      //}

      //try
      //{

         //if(bCa2Path)
         //{

         //   m_plibrary = __node_library_open_ca2(pszPath, m_strMessage);

         //}
         //else
         //{

      //{

         //synchronous_lock synchronouslock(s_pmutexLoading);

         //KEEP(s_plibraryLoading, this, nullptr);

         m_plibrary = acmesystem()->operating_system_library_open(path, m_strMessage);

      //}
            
            
      //s_plibraryLoading = nullptr;

///         }

         //if(m_plibrary == nullptr)
         //{


         //}

         //m_strPath = pszPath;

         m_strName = ::file::path(path).title();

      //}
      //catch(...)
      //{

         //ERROR("acme::library::open Failed to open library " << ( bCa2Path ? " (ca2 path)" : "") << " with errors " << m_strMessage);

         //return false;

      //}

      //INFORMATION("acme::library::open success : " << m_strMessage);
      
      if(is_verbose_log())
      {
      
         FORMATTED_INFORMATION("acme::library::open success : %s", m_strName.c_str());
         
      }

      if (m_strName.has_char())
      {

         subsystem()->m_mapLibrary[m_strName] = this;

      }

      //return true;

   }


   //::acme::library* library::loading_library()
   //{

   //   return s_plibraryLoading;

   //}


   //bool library::open_library(string strTitle)
   //{

   //   auto psystem = acmesystem();

   //   synchronous_lock synchronouslock(&psystem->m_pmutexRawLibrary);

   //   if (m_pca2library.is_set())
   //   {

   //      return true;

   //   }

   //   ::exception_engine().reset();

   //   PFN_NEW_LIBRARY pfnNewAcmeLibrary = nullptr;

   //   int iPhase = 0;

   //   try
   //   {
   //   
   //      m_pca2library = psystem->on_get_library(m_strName);

   //   }
   //   catch (...)
   //   {

   //      m_pca2library.release();

   //   }

   //   //if (!m_pca2library)
   //   //{

   //   //   try
   //   //   {

   //   //      pfnNewAuraLibrary = get_get_new_apex_library(m_strPath);

   //   //      if (pfnNewAuraLibrary == nullptr)
   //   //      {

   //   //         iPhase++;

   //   //         if (strTitle.has_char())
   //   //         {

   //   //            get(pfnNewAuraLibrary, strTitle + "_get_new_library");

   //   //         }

   //   //      }

   //   //      if (pfnNewAuraLibrary == nullptr)
   //   //      {

   //   //         iPhase++;

   //   //         strTitle = m_strPath.title();

   //   //         get(pfnNewAuraLibrary, strTitle + "_get_new_library");

   //   //      }

   //   //      if (pfnNewAuraLibrary == nullptr)
   //   //      {

   //   //         iPhase++;

   //   //         if (strTitle.begins_eat("lib"))
   //   //         {

   //   //            get(pfnNewAuraLibrary, strTitle + "_get_new_library");

   //   //         }

   //   //      }

   //   //      if (pfnNewAuraLibrary == nullptr)
   //   //      {

   //   //         iPhase++;

   //   //         get(pfnNewAuraLibrary, "get_new_library");

   //   //      }

   //   //   }
   //   //   catch (...)
   //   //   {

   //   //      close();

   //   //      return false;

   //   //   }

   //   //   if (pfnNewAuraLibrary == nullptr)
   //   //   {

   //   //      close();

   //   //      return false;

   //   //   }

   //   //   try
   //   //   {

   //   //      m_pca2library = ::transfer(pfnNewAuraLibrary());

   //   //   }
   //   //   catch (...)
   //   //   {

   //   //      m_pca2library.release();

   //   //   }

   //   //}

   //   if(m_pca2library.is_null())
   //   {

   //      close();

   //      return false;

   //   }

   //   m_pca2library->initialize_library(this, 0, m_strRoot, m_strName, m_strFolder);

   //   //m_pca2library->factory();

   //   //m_pca2library->initialize(this);

   //   if (m_pca2library->m_strCa2Name.is_empty())
   //   {

   //      m_pca2library->m_strCa2Name = m_strPath.title();

   //      m_strCa2Name = m_strPath;

   //   }
   //   else
   //   {

   //      m_strCa2Name = m_pca2library->m_strCa2Name;

   //   }

   //   if (m_strCa2Name.has_char())
   //   {

   //      acmesystem()->m_mapLibrary[m_strCa2Name] = this;

   //   }

   //   return true;

   //}


   //library * library::get_library()
   //{

   //   return m_pca2library;

   //}


   string library::get_library_name()
   {

      return m_strName;

//      auto psystem = acmesystem();
//
//      synchronous_lock synchronouslock(&psystem->m_pmutexLibrary);
//
//      if(m_pca2library)
//      {
//
//         return m_pca2library->get_library_name();
//
//      }
//      else
//      {
//
//         string strName(m_strCa2Name);
//
//         string strPrefix(get_root());
//
//#ifdef UNIVERSAL_WINDOWS
//
//         //         strPrefix = "m_" + strPrefix;
//
//#endif
//
//         strPrefix.replace("-","_");
//
//         strPrefix += "_";
//
//         strName.case_insensitive_begins_eat(strPrefix);
//
//         return strName;
//
//      }

   }


   void * library::get_os_data()
   {

      return m_plibrary;

   }


   bool library::close()
   {

      if (!m_plibrary)
      {

         return true;

      }

      critical_section_lock synchronouslock(&::acme::acme::g_pacme->m_psubsystem->m_criticalsection);

      try
      {

         bool bOk = true;

//         m_pca2library.release();

         //if (m_bAutoUnload)
         {

            try
            {

               if (m_plibrary != nullptr)
               {

                  if(is_verbose_log())
                  {

                     if (acmesystem()->m_etracelevel <= e_trace_level_information)
                     {

                        output_debug_string("Closing library : " + m_strName + "\n");

                     }

                  }

                  bOk = acmesystem()->operating_system_library_close(m_plibrary);

                  m_plibrary = nullptr;

               }

            }
            catch (...)
            {

               m_plibrary = nullptr;

               bOk = false;

            }

         }

         return bOk;

      }
      catch(...)
      {
         return false;
      }

   }


//   string library::get_app_id(const ::scoped_string & scopedstrAppName)
//   {
//
//      auto psystem = acmesystem();
//
//      synchronous_lock synchronouslock(&psystem->m_pmutexRawLibrary);
//
//      if (!contains_app(pszAppName))
//      {
//
//         return "";
//
//      }
//
//      string strPrefix(get_root());
//
//      string strLibraryName(get_library_name());
//
//#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)
//
//      if(strLibraryName == "libca2")
//      {
//
//         strLibraryName = "ca2";
//
//      }
//      else if(!strLibraryName.begins_eat("libca2"))
//      {
//
//         strLibraryName.begins_eat("lib");
//
//      }
//
//#elif defined(UNIVERSAL_WINDOWS)
//
//      //      strLibraryName.case_insensitive_begins_eat("m_");
//
//#endif
//
//
//      string_array straAppList;
//
//      get_app_list(straAppList);
//
//      strPrefix += "/";
//
//      if(straAppList.get_count() > 1)
//      {
//
//         strPrefix += strLibraryName;
//
//         strPrefix += "/";
//
//      }
//
//      return strPrefix + pszAppName;
//
//   }


//   string library::get_app_name(const ::scoped_string & scopedstrAppId)
//   {
//
//      auto psystem = acmesystem();
//
//      synchronous_lock synchronouslock(&psystem->m_pmutexRawLibrary);
//
//      string strAppName(pszAppId);
//
//      string strPrefix(get_root());
//
//      string strLibraryName(get_library_name());
//
//#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)
//
//      if(strLibraryName == "libca2")
//      {
//
//         strLibraryName = "ca2";
//
//      }
//      else if(!strLibraryName.begins_eat("libca2"))
//      {
//
//         strLibraryName.begins_eat("lib");
//
//      }
//
//#elif defined(UNIVERSAL_WINDOWS)
//
//      //      strLibraryName.case_insensitive_begins_eat("m_");
//
//#endif
//
//      strPrefix += "/";
//
//      strPrefix += strLibraryName;
//
//      strPrefix += "/";
//
//      strAppName.begins_eat(strPrefix);
//
//      if(!contains_app(strAppName))
//      {
//
//         strAppName     = pszAppId;
//
//         strPrefix      = get_root();
//
//         strPrefix += "/";
//
//         strAppName.begins_eat(strPrefix);
//
//         if(!contains_app(strAppName))
//            return "";
//      }
//
//      return strAppName;
//
//   }


   //::pointer<::object>library::new_application(const ::string & strAppId)
   //{

   //   auto psystem = acmesystem();

   //   synchronous_lock synchronouslock(&psystem->m_pmutexRawLibrary);

   //   try
   //   {

   //      auto psetup = ::system_setup::get_first(::system_setup::flag_application, pszAppId);

   //      if (psetup)
   //      {

   //         auto pelementApplication = psetup->create_application_as_element();

   //         if (pelementApplication)
   //         {

   //            return pelementApplication;

   //         }

   //      }

   //      string strAppId(pszAppId);

   //      strAppId.replace("/", "_");

   //      strAppId.replace("-", "_");

   //      auto & pfactory = this->factory(strAppId);

   //         //string strAppName = get_app_name(pszAppId);

   //      if (!pfactory)
   //      {

   //         return nullptr;

   //      }

   //      auto papp = pfactory->create("application");

   //         //auto papp = get_library()->new_application(strAppName);

   //         //if (!papp)
   //         //{

   //         //   return papp;

   //         //}

   //         //papp->set_library_name(m_strCa2Name);

   //      papp->set_library_name(m_strName);

   //      return papp;

   //      }
   //      //else
   //      //{

   //      //   auto p = get<PFN_NEW_MATTER>("new_application_as_matter");

   //      //   if (p)
   //      //   {

   //      //      auto papp = (*p)();

   //      //      return papp;

   //      //   }

   //      //}

   //   }
   //   catch(...)
   //   {

   //   }

   //   return nullptr;

   //}


   //void library::get_extension_list(string_array & stra)
   //{


   //}


//   void library::get_app_list(string_array & stra)
//   {
//
//      auto psystem = acmesystem();
//
//      synchronous_lock synchronouslock(&psystem->m_pmutexLibrary);
//
//      if(get_library() != nullptr)
//      {
//         try
//         {
//            get_library()->get_app_list(stra);
//         }
//         catch(...)
//         {
//         }
//      }
//      else
//      {
//
//         string strAppId = m_strCa2Name;
//
//         stra.add(strAppId);
//
////
////
////         string strPrefix = get_root();
////
////#if defined(LINUX) || defined(__APPLE__)
////
////         strAppId.begins_eat("lib");
////
////#elif defined(UNIVERSAL_WINDOWS)
////
////         //         strPrefix = "m_" + strPrefix;
////
////#endif
////
////         strPrefix.replace("-","_");
////
////         strPrefix += "_";
////
////         strAppId.case_insensitive_begins_eat(strPrefix);
////
////         //if(strAppId.case_insensitive_begins_eat(strPrefix))
////         {
////
////            stra.add(strAppId);
////
////         }
//
//      }
//
//   }


   //::matter* library::new_object(const ::scoped_string & scopedstrClassId)
   //{

   //   if (!m_pca2library)
   //   {

   //      return nullptr;

   //   }

   //   return m_pca2library->new_object(pszClassId);

   //}




   //bool library::contains_app(const ::scoped_string & scopedstrAppId)
   //{

   //   auto psystem = acmesystem();

   //   synchronous_lock synchronouslock(&psystem->m_pmutexLibrary);

   //   string_array stra;

   //   get_app_list(stra);

   //   return stra.contains(pszAppId);

   //}


   //string library::get_root()
   //{

   //   //auto psystem = acmesystem();

   //   //synchronous_lock synchronouslock(&psystem->m_pmutexLibrary);

   //   //if(m_pca2library)
   //   //{

   //   //   return m_pca2library->m_strRoot;

   //   //}

   //   return m_strRoot;

   //}


   //void library::get_create_impact_id_list(::array < ::atom > & ida)
   //{

   //   auto psystem = acmesystem();

   //   synchronous_lock synchronouslock(&psystem->m_pmutexLibrary);

   //   UNREFERENCED_PARAMETER(ida);

   //}


   bool library::is_opened()
   {

      //auto psystem = acmesystem();

      //synchronous_lock synchronouslock(&psystem->m_pmutexLibrary);

      return m_plibrary != nullptr;

   }


   bool library::is_closed()
   {

      return !is_opened();

   }


   void * library::raw_get(const ::scoped_string & scopedstrEntryName)
   {

      auto psystem = acmesystem();

      critical_section_lock synchronouslock(&psystem->m_psubsystem->m_criticalsection);

      return acmesystem()->operating_system_library_raw_get(m_plibrary,scopedstrEntryName);

   }

   
   void library::create_factory(::pointer<::factory::factory>& pfactory)
   {

      string strName = m_strName;

      //INFORMATION("library::create_factory \""+strName+"\": starting...");

      //auto pfactory = factory(strName);

      //if (!pfactory)
      //{

      //   FORMATTED_INFORMATION("library::create_factory factory(\"%s\") failed!!", strName.c_str());

      //   throw ::exception(error_wrong_state);

      //}

      //INFORMATION("library::create_factory factory(\""+strName+"\") succeeded!!");

      if (!m_pfnFactory)
      {

         string strFactoryFunction;

         strFactoryFunction = strName + "_factory";

         //INFORMATION("library::create_factory factory function not initialized!!");
         //INFORMATION("library::create_factory factory function name: \"" << strFactoryFunction << "\"");

         auto pfnFactory = get < PFN_factory >(strFactoryFunction);

         if (::is_null((const void *) pfnFactory))
         {

            FORMATTED_WARNING("library::create_factory factory function: \"%s\" doesn't exist!!!", strFactoryFunction.c_str());

            FORMATTED_WARNING("Is _factory.cpp included in the project \"%s\"???", strName.c_str());
            FORMATTED_WARNING("Does it contain the implementation of factory function \"%s\"???", strFactoryFunction.c_str());

            string strDetails;

            strDetails = "Function \"" + strFactoryFunction + "\" wasn't found";

            throw ::exception(error_function_entry_not_found, "Function \"" + strFactoryFunction + "\" not found", strDetails);

         }

         m_pfnFactory = pfnFactory;

      }

      __defer_construct_new(pfactory);

      m_pfnFactory(pfactory);

      FORMATTED_INFORMATION("%s_factory succeeded!",strName.c_str());

      //return pfactory;

   }


} // namespace acme



CLASS_DECL_ACME string implementation_name(const ::string& strComponent, const ::string& strImplementation)
{

   if (strImplementation.case_insensitive_begins(strComponent) && strImplementation[strComponent.length()] == '_')
   {

      return strImplementation.c_str() + strComponent.length() + 1;

   }

   return strImplementation;

}


CLASS_DECL_ACME string library_name(const ::string& strComponent, const ::string& strImplementation)
{

   string strLibrary;

   strLibrary = strComponent + "_" + implementation_name(strComponent, strImplementation);

   return strLibrary;

}


CLASS_DECL_ACME string factory_name(const ::string& strLibrary)
{

   string strFactory;

   strFactory = strLibrary + "_factory";

   return strFactory;

}


CLASS_DECL_ACME string library_filter(const ::string& str)
{

   string strLibrary;

   strLibrary = str;

   strLibrary.case_insensitive_ends_eat(".dll");
   strLibrary.case_insensitive_ends_eat(".so");
   strLibrary.case_insensitive_ends_eat(".dylib");
   strLibrary.case_insensitive_begins_eat("lib");

   return strLibrary;

}
