#include "framework.h"
#include "acme/platform/acme.h"
//#include "system_impl.h"
#include "library.h"

CLASS_DECL_ACME bool is_verbose_log();


//typedef  void(*PFN_create_factory)();


namespace acme
{


   const char * psz_empty_app_id = "";

   //::mutex* library::s_pmutexLoading = nullptr;
   //::acme::library* library::s_plibraryLoading = nullptr;


   library::library()
   {

   }


   void library::initialize_matter(::matter * pmatter)
   {

      ::matter::initialize_matter(pmatter);

      m_plibrary = nullptr;

      //m_bAutoUnload = false;

      //return estatus;

   }


   //void library::initialize_library(::matter * pmatter,int iDesambig,const char * pszRoot, const char * pszName, const char * pszFolder)
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


   void library::assert_ok() const
   {

   }
   

   void library::dump(dump_context & dumpcontext) const
   {


   }


   //void library::open(const char * pszPath,bool bAutoClose,bool bCa2Path)
   void library::open(const char* pszPath)
   {

      auto psystem = get_system();

      synchronous_lock synchronouslock(&psystem->m_mutexLibrary4);

      m_strMessage.Empty();

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

         //__keep(s_plibraryLoading, this, nullptr);

         m_plibrary = __node_library_open(pszPath, m_strMessage);

      //}
            
            
      //s_plibraryLoading = nullptr;

///         }

         //if(m_plibrary == nullptr)
         //{


         //}

         //m_strPath = pszPath;

         m_strName = ::file::path(pszPath).title();

      //}
      //catch(...)
      //{

         //ERROR("acme::library::open Failed to open library " << ( bCa2Path ? " (ca2 path)" : "") << " with errors " << m_strMessage);

         //return false;

      //}

      //INFORMATION("acme::library::open success : " << m_strMessage);
      
      if(is_verbose_log())
      {
      
         INFORMATION("acme::library::open success : " << m_strName);
         
      }

      if (m_strName.has_char())
      {

         m_psystem->m_mapLibrary4[m_strName] = this;

      }

      //return true;

   }


   //::acme::library* library::loading_library()
   //{

   //   return s_plibraryLoading;

   //}


   //bool library::open_library(string strTitle)
   //{

   //   auto psystem = get_system();

   //   synchronous_lock synchronouslock(&psystem->m_mutexRawLibrary);

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

   //   //         if (::str::begins_eat(strTitle, "lib"))
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

   //   //      m_pca2library = ::move(pfnNewAuraLibrary());

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

   //      m_psystem->m_mapLibrary[m_strCa2Name] = this;

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

//      auto psystem = get_system();
//
//      synchronous_lock synchronouslock(&psystem->m_mutexLibrary);
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
//#ifdef _UWP
//
//         //         strPrefix = "m_" + strPrefix;
//
//#endif
//
//         strPrefix.replace("-","_");
//
//         strPrefix += "_";
//
//         strName.begins_eat_ci(strPrefix);
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

      auto psystem = get_system();

      synchronous_lock synchronouslock(&psystem->m_mutexLibrary4);

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

                     if (m_psystem->m_etracelevel <= e_trace_level_information)
                     {

                        output_debug_string("Closing library : " + m_strName + "\n");

                     }

                  }

                  bOk = ::__node_library_close(m_plibrary);

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


//   string library::get_app_id(const char * pszAppName)
//   {
//
//      auto psystem = get_system();
//
//      synchronous_lock synchronouslock(&psystem->m_mutexRawLibrary);
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
//      else if(!::str::begins_eat(strLibraryName,"libca2"))
//      {
//
//         ::str::begins_eat(strLibraryName,"lib");
//
//      }
//
//#elif defined(_UWP)
//
//      //      ::str::begins_eat_ci(strLibraryName, "m_");
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


//   string library::get_app_name(const char * pszAppId)
//   {
//
//      auto psystem = get_system();
//
//      synchronous_lock synchronouslock(&psystem->m_mutexRawLibrary);
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
//      else if(!::str::begins_eat(strLibraryName,"libca2"))
//      {
//
//         ::str::begins_eat(strLibraryName,"lib");
//
//      }
//
//#elif defined(_UWP)
//
//      //      ::str::begins_eat_ci(strLibraryName, "m_");
//
//#endif
//
//      strPrefix += "/";
//
//      strPrefix += strLibraryName;
//
//      strPrefix += "/";
//
//      ::str::begins_eat(strAppName,strPrefix);
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
//         ::str::begins_eat(strAppName,strPrefix);
//
//         if(!contains_app(strAppName))
//            return "";
//      }
//
//      return strAppName;
//
//   }


   //__pointer(::object) library::new_application(const ::string & strAppId)
   //{

   //   auto psystem = get_system();

   //   synchronous_lock synchronouslock(&psystem->m_mutexRawLibrary);

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
//      auto psystem = get_system();
//
//      synchronous_lock synchronouslock(&psystem->m_mutexLibrary);
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
////         ::str::begins_eat(strAppId,"lib");
////
////#elif defined(_UWP)
////
////         //         strPrefix = "m_" + strPrefix;
////
////#endif
////
////         strPrefix.replace("-","_");
////
////         strPrefix += "_";
////
////         ::str::begins_eat_ci(strAppId,strPrefix);
////
////         //if(::str::begins_eat_ci(strAppId,strPrefix))
////         {
////
////            stra.add(strAppId);
////
////         }
//
//      }
//
//   }


   //::matter* library::new_object(const char * pszClassId)
   //{

   //   if (!m_pca2library)
   //   {

   //      return nullptr;

   //   }

   //   return m_pca2library->new_object(pszClassId);

   //}




   //bool library::contains_app(const char * pszAppId)
   //{

   //   auto psystem = get_system();

   //   synchronous_lock synchronouslock(&psystem->m_mutexLibrary);

   //   string_array stra;

   //   get_app_list(stra);

   //   return stra.contains(pszAppId);

   //}


   //string library::get_root()
   //{

   //   //auto psystem = get_system();

   //   //synchronous_lock synchronouslock(&psystem->m_mutexLibrary);

   //   //if(m_pca2library)
   //   //{

   //   //   return m_pca2library->m_strRoot;

   //   //}

   //   return m_strRoot;

   //}


   //void library::get_create_view_id_list(::array < ::atom > & ida)
   //{

   //   auto psystem = get_system();

   //   synchronous_lock synchronouslock(&psystem->m_mutexLibrary);

   //   __UNREFERENCED_PARAMETER(ida);

   //}


   bool library::is_opened()
   {

      //auto psystem = get_system();

      //synchronous_lock synchronouslock(&psystem->m_mutexLibrary);

      return m_plibrary != nullptr;

   }


   bool library::is_closed()
   {

      return !is_opened();

   }


   void * library::raw_get(const char * pszEntryName)
   {

      auto psystem = get_system();

      synchronous_lock synchronouslock(&psystem->m_mutexLibrary4);

      return __node_library_raw_get(m_plibrary,pszEntryName);

   }

   
   //::matter* library::factory_new(::object * pobject, const char* lpszClass)
   //{

   //   return nullptr;

   //}


   //__pointer(::matter) library::factory_create(const char * lpszClass)
   //{

   //   library_object_allocator_base * pallocator = find_allocator(lpszClass);

   //   if (pallocator == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   auto p = pallocator->new_object();

   //   auto pobject = ::move(p);

   //   if (!pobject)
   //   {

   //      return nullptr;

   //   }

   //   return pobject;

   //}


   //bool library::factory_has_object_class(const char * lpszClass)
   //{

   //   return find_allocator(lpszClass) != nullptr;

   //}


   //library_object_allocator_base * library::find_allocator(const char * lpszClass)
   //{

   //   index iFind = m_allocatorptra.predicate_find_first([&](auto & pallocator)
   //   {

   //      return pallocator->m_strName == lpszClass;

   //   });

   //   if (iFind < 0)
   //   {

   //      return nullptr;

   //   }

   //   return m_allocatorptra[iFind];

   //}

   
   //__pointer(::factory::factory)& library::factory(const ::string& strComponent, const ::string& strImplementation)
   //{

   //   if (strComponent.is_empty() || strImplementation.is_empty())
   //   {

   //      throw error_bad_argument;

   //   }

   //   string strLibrary;

   //   strLibrary = strComponent + "_" + strImplementation;

   //   auto& pfactory = factory(strLibrary);

   //   if (!pfactory)
   //   {

   //      return pfactory;

   //   }

   //   return pfactory;


   //}


   //__pointer(::factory::factory) & library::factory(const ::string& strLibrary)
   //{

   //   if (strLibrary.is_empty())
   //   {

   //      throw error_bad_argument;

   //   }

   //   auto& pfactory = m_mapFactory[strLibrary];

   //   if (pfactory.is_initialized())
   //   {

   //      return pfactory;

   //   }

   //   _load_factory(pfactory, strLibrary);

   //   return pfactory;

   //}


   //void library::_load_factory(__pointer(::factory::factory) & pfactory, const ::string & strComponent)
   //{

   //   if (strComponent.is_empty())
   //   {

   //      throw error_bad_argument;

   //   }

   //   string strFactory;

   //   strFactory = strComponent + "_factory";

   //   auto pfn_factory = get < PFN_factory >(strFactory);

   //   if (!pfn_factory)
   //   {

   //      pfactory = (const ::extended::status &) error_failed;

   //      return;

   //   }

   //   pfactory = __new(::factory::factory);

   //   if (!pfactory)
   //   {

   //      pfactory = (const ::extended::status &) error_failed;

   //      return;

   //   }

   //   try
   //   {

   //      pfn_factory(pfactory);

   //   }
   //   catch (const ::exception& e)
   //   {

   //   }

   //}


   //bool library::add_factory_item()
   //{

   //   auto pfn_create_factory = get < PFN_create_factory >("add_factory_item");

   //   if (pfn_create_factory == nullptr)
   //   {

   //      return false;

   //   }

   //   pfn_create_factory();

   //   return true;

   //}


//   __pointer(::factory::factory) library::create_factory(const ::string & strLibrary)
//   {
//
//      string strFactory = factory_name(strLibrary);
//
////      auto pfnFactory = get < PFN_factory >(strFactory);
////
////      if (::is_null(pfnFactory))
////      {
////
////         throw ::exception(error_function_entry_not_found);
////
////      }
//
//      auto pfactory = m_psystem->__create_new < ::factory::factory >();
//
//      //pfactory->m_plibrary = this;
//
//      //pfnFactory(pfactory);
//
//      return pfactory;
//
//   }


   __pointer(::factory::factory) library::create_factory()
   {

      string strName = m_strName;

      auto pfactory = ::factory::get_factory(strName);

      if (!pfactory)
      {

         throw ::exception(error_wrong_state);

      }

      string strFactoryFunction;

      strFactoryFunction = strName + "_factory";

      auto pfnFactory = get < PFN_factory >(strFactoryFunction);

      if (::is_null(pfnFactory))
      {

         string strDetails;

         strDetails = "Function \"" + strFactoryFunction + "\" wasn't found";
      
         throw ::exception(error_function_entry_not_found, "Function \""+strFactoryFunction + "\" not found", strDetails);
      
      }

      pfnFactory(pfactory);

      return pfactory;

   }


} // namespace acme


#if defined(LINUX) || defined(FREEBSD)

::file::path libfilename(const ::string & str)
{
   return "lib" + str + ".so";
}

#elif defined(ANDROID)

::file::path libfilename(const ::string & str)
{
   return "lib" + str + ".so";
}

#elif defined(WINDOWS)

::file::path libfilename(const ::string & str)
{
   return str + ".dll";
}

#elif defined(__APPLE__)

::file::path libfilename(const ::string & str)
{
   return "lib" + str + ".dylib";
}

#endif


CLASS_DECL_ACME string implementation_name(const ::string& strComponent, const ::string& strImplementation)
{

   if (strImplementation.begins_ci(strComponent) && strImplementation[strComponent.length()] == '_')
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

   strLibrary.ends_eat_ci(".dll");
   strLibrary.ends_eat_ci(".so");
   strLibrary.ends_eat_ci(".dylib");
   strLibrary.begins_eat_ci("lib");

   return strLibrary;

}
