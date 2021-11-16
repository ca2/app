#include "framework.h"
#include "acme/platform/static_setup.h"


//typedef  void(*PFN_create_factory)();


namespace acme
{


   const char * psz_empty_app_id = "";


   ::e_status library::initialize_matter(::matter * pmatter)
   {

      auto estatus = ::matter::initialize_matter(pmatter);

      m_plibrary = nullptr;

      m_bAutoUnload = false;

      return estatus;

   }


   ::e_status library::initialize_library(::matter * pmatter,int iDesambig,const char * pszRoot, const char * pszName, const char * pszFolder)
   {

      auto estatus = initialize_matter(pmatter);

      if (!estatus)
      {

         return estatus;

      }

      string strRoot(pszRoot);

      strRoot.trim();

      if (strRoot.has_char())
      {

         m_strRoot = strRoot;

      }
      else
      {

         strRoot = m_strRoot;

      }

      m_strName = ::is_null(pszName) ? strRoot : string(pszName);

      if (::is_set(pszFolder))
      {

         m_strFolder = pszFolder;

      }
      else
      {

         m_strFolder = m_strName;

      }

      m_bAutoUnload = false;

      m_plibrary = nullptr;

      m_strCa2Name = strRoot;

      if(strRoot.has_char())
      {

         m_strRoot = strRoot;

         if(m_strRoot.find('/') > 0)
         {

            m_strRoot = m_strRoot.substr(0, m_strRoot.find('/'));

         }

      }

      return estatus;

   }


   library::~library()
   {

      close();

   }


   void library::assert_valid() const
   {

   }
   

   void library::dump(dump_context & dumpcontext) const
   {


   }


   bool library::open(const char * pszPath,bool bAutoClose,bool bCa2Path)
   {

      auto psystem = get_system();

      synchronous_lock synchronouslock(&psystem->m_mutexLibrary);

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

      try
      {

         if(bCa2Path)
         {

            m_plibrary = __node_library_open_ca2(pszPath, m_strMessage);

         }
         else
         {

            m_plibrary = __node_library_open(pszPath, m_strMessage);

         }

         if(m_plibrary == nullptr)
         {

            ERROR("acme::library::open");

            return false;

         }

         m_strPath = pszPath;

      }
      catch(...)
      {

         ERROR("acme::library::open Failed to open library " << ( bCa2Path ? " (ca2 path)" : "") << " with errors " << m_strMessage);

         return false;

      }

      INFORMATION("acme::library::open success");

      if (m_strCa2Name.has_char())
      {

         m_psystem->m_mapLibrary[m_strCa2Name] = this;

      }

      return true;

   }


   bool library::open_library(string strTitle)
   {

      auto psystem = get_system();

      synchronous_lock synchronouslock(&psystem->m_mutexLibrary);

      if (m_pca2library.is_set())
      {

         return true;

      }

      ::exception_engine().reset();

      PFN_NEW_LIBRARY pfnNewAcmeLibrary = nullptr;

      int iPhase = 0;

      try
      {
      
         m_pca2library = psystem->on_get_library(m_strName);

      }
      catch (...)
      {

         m_pca2library.release();

      }

      //if (!m_pca2library)
      //{

      //   try
      //   {

      //      pfnNewAuraLibrary = get_get_new_apex_library(m_strPath);

      //      if (pfnNewAuraLibrary == nullptr)
      //      {

      //         iPhase++;

      //         if (strTitle.has_char())
      //         {

      //            get(pfnNewAuraLibrary, strTitle + "_get_new_library");

      //         }

      //      }

      //      if (pfnNewAuraLibrary == nullptr)
      //      {

      //         iPhase++;

      //         strTitle = m_strPath.title();

      //         get(pfnNewAuraLibrary, strTitle + "_get_new_library");

      //      }

      //      if (pfnNewAuraLibrary == nullptr)
      //      {

      //         iPhase++;

      //         if (::str::begins_eat(strTitle, "lib"))
      //         {

      //            get(pfnNewAuraLibrary, strTitle + "_get_new_library");

      //         }

      //      }

      //      if (pfnNewAuraLibrary == nullptr)
      //      {

      //         iPhase++;

      //         get(pfnNewAuraLibrary, "get_new_library");

      //      }

      //   }
      //   catch (...)
      //   {

      //      close();

      //      return false;

      //   }

      //   if (pfnNewAuraLibrary == nullptr)
      //   {

      //      close();

      //      return false;

      //   }

      //   try
      //   {

      //      m_pca2library = ::move(pfnNewAuraLibrary());

      //   }
      //   catch (...)
      //   {

      //      m_pca2library.release();

      //   }

      //}

      if(m_pca2library.is_null())
      {

         close();

         return false;

      }

      m_pca2library->initialize_library(this, 0, m_strRoot, m_strName, m_strFolder);

      m_pca2library->do_factory_exchange();

      //m_pca2library->initialize(this);

      if (m_pca2library->m_strCa2Name.is_empty())
      {

         m_pca2library->m_strCa2Name = m_strPath.title();

         m_strCa2Name = m_strPath;

      }
      else
      {

         m_strCa2Name = m_pca2library->m_strCa2Name;

      }

      if (m_strCa2Name.has_char())
      {

         m_psystem->m_mapLibrary[m_strCa2Name] = this;

      }

      return true;

   }


   library * library::get_library()
   {

      return m_pca2library;

   }


   string library::get_library_name()
   {

      auto psystem = get_system();

      synchronous_lock synchronouslock(&psystem->m_mutexLibrary);

      if(m_pca2library)
      {

         return m_pca2library->get_library_name();

      }
      else
      {

         string strName(m_strCa2Name);

         string strPrefix(get_root());

#ifdef _UWP

         //         strPrefix = "m_" + strPrefix;

#endif

         strPrefix.replace("-","_");

         strPrefix += "_";

         strName.begins_eat_ci(strPrefix);

         return strName;

      }

   }


   void * library::get_os_data()
   {

      return m_plibrary;

   }


   bool library::close()
   {

      auto psystem = get_system();

      synchronous_lock synchronouslock(&psystem->m_mutexLibrary);

      try
      {

         bool bOk = true;

         m_pca2library.release();

         if (m_bAutoUnload)
         {

            try
            {

               if (m_plibrary != nullptr)
               {

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


   string library::get_app_id(const char * pszAppName)
   {

      auto psystem = get_system();

      synchronous_lock synchronouslock(&psystem->m_mutexLibrary);

      if (!contains_app(pszAppName))
      {

         return "";

      }

      string strPrefix(get_root());

      string strLibraryName(get_library_name());

#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      if(strLibraryName == "libca2")
      {

         strLibraryName = "ca2";

      }
      else if(!::str::begins_eat(strLibraryName,"libca2"))
      {

         ::str::begins_eat(strLibraryName,"lib");

      }

#elif defined(_UWP)

      //      ::str::begins_eat_ci(strLibraryName, "m_");

#endif


      string_array straAppList;

      get_app_list(straAppList);

      strPrefix += "/";

      if(straAppList.get_count() > 1)
      {

         strPrefix += strLibraryName;

         strPrefix += "/";

      }

      return strPrefix + pszAppName;

   }


   string library::get_app_name(const char * pszAppId)
   {

      auto psystem = get_system();

      synchronous_lock synchronouslock(&psystem->m_mutexLibrary);

      string strAppName(pszAppId);

      string strPrefix(get_root());

      string strLibraryName(get_library_name());

#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      if(strLibraryName == "libca2")
      {

         strLibraryName = "ca2";

      }
      else if(!::str::begins_eat(strLibraryName,"libca2"))
      {

         ::str::begins_eat(strLibraryName,"lib");

      }

#elif defined(_UWP)

      //      ::str::begins_eat_ci(strLibraryName, "m_");

#endif

      strPrefix += "/";

      strPrefix += strLibraryName;

      strPrefix += "/";

      ::str::begins_eat(strAppName,strPrefix);

      if(!contains_app(strAppName))
      {

         strAppName     = pszAppId;

         strPrefix      = get_root();

         strPrefix += "/";

         ::str::begins_eat(strAppName,strPrefix);

         if(!contains_app(strAppName))
            return "";
      }

      return strAppName;

   }


   __transport(::matter) library::new_application(const char * pszAppId)
   {

      auto psystem = get_system();

      synchronous_lock synchronouslock(&psystem->m_mutexLibrary);

      try
      {

         auto psetup = ::static_setup::get_first(::static_setup::flag_application, pszAppId);

         if (psetup)
         {

            auto pelementApplication = psetup->create_application_as_element();

            if (pelementApplication)
            {

               return pelementApplication;

            }

         }

         if (get_library() == nullptr)
         {

            open_library();

         }

         if(get_library() != nullptr)
         {

            string strAppName = get_app_name(pszAppId);

            if (strAppName.is_empty())
            {

               return nullptr;

            }

            auto papp = get_library()->new_application(strAppName);

            if (!papp)
            {

               return papp;

            }

            papp->set_library_name(m_strCa2Name);

            return papp;

         }
         else
         {

            auto p = get<PFN_NEW_MATTER>("new_application_as_matter");

            if (p)
            {

               auto papp = (*p)();

               return papp;

            }

         }

      }
      catch(...)
      {

      }

      return nullptr;

   }


   void library::get_extension_list(string_array & stra)
   {


   }


   void library::get_app_list(string_array & stra)
   {

      auto psystem = get_system();

      synchronous_lock synchronouslock(&psystem->m_mutexLibrary);

      if(get_library() != nullptr)
      {
         try
         {
            get_library()->get_app_list(stra);
         }
         catch(...)
         {
         }
      }
      else
      {

         string strAppId = m_strCa2Name;

         stra.add(strAppId);

//
//
//         string strPrefix = get_root();
//
//#if defined(LINUX) || defined(__APPLE__)
//
//         ::str::begins_eat(strAppId,"lib");
//
//#elif defined(_UWP)
//
//         //         strPrefix = "m_" + strPrefix;
//
//#endif
//
//         strPrefix.replace("-","_");
//
//         strPrefix += "_";
//
//         ::str::begins_eat_ci(strAppId,strPrefix);
//
//         //if(::str::begins_eat_ci(strAppId,strPrefix))
//         {
//
//            stra.add(strAppId);
//
//         }

      }

   }


   ::matter* library::new_object(const char * pszClassId)
   {

      if (!m_pca2library)
      {

         return nullptr;

      }

      return m_pca2library->new_object(pszClassId);

   }


   __pointer(::matter) library::create_object(const char * pszClass)
   {

      auto psystem = get_system();

      synchronous_lock synchronouslock(&psystem->m_mutexLibrary);

      ::matter * p = nullptr;

      if(get_library() != nullptr)
      {

         p = get_library()->new_object(pszClass);

      }
      else
      {
         
         p = new_object(pszClass);

      }

      auto pobject = ::move_transfer(p);
      
      if (!pobject)
      {

         return nullptr;

      }

      return pobject;

   }


   bool library::has_object_class(const char * pszClassId)
   {

      auto psystem = get_system();

      synchronous_lock synchronouslock(&psystem->m_mutexLibrary);

      if (get_library() == nullptr)
      {

         return false;

      }

      return get_library()->has_object_class(pszClassId);

   }


   bool library::contains_app(const char * pszAppId)
   {

      auto psystem = get_system();

      synchronous_lock synchronouslock(&psystem->m_mutexLibrary);

      string_array stra;

      get_app_list(stra);

      return stra.contains(pszAppId);

   }


   string library::get_root()
   {

      auto psystem = get_system();

      synchronous_lock synchronouslock(&psystem->m_mutexLibrary);

      if(m_pca2library)
      {

         return m_pca2library->m_strRoot;

      }

      return m_strRoot;

   }


   void library::get_create_view_id_list(::array < ::id > & ida)
   {

      auto psystem = get_system();

      synchronous_lock synchronouslock(&psystem->m_mutexLibrary);

      __UNREFERENCED_PARAMETER(ida);

   }


   bool library::is_opened()
   {

      auto psystem = get_system();

      synchronous_lock synchronouslock(&psystem->m_mutexLibrary);

      return m_plibrary != nullptr;

   }


   bool library::is_closed()
   {

      return !is_opened();

   }


   void * library::raw_get(const char * pszEntryName)
   {

      auto psystem = get_system();

      synchronous_lock synchronouslock(&psystem->m_mutexLibrary);

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


   //void library::initialize_factory()
   //{

   //}

   
   ::e_status library::do_factory_exchange(const ::string& strName, ::factory_map* pfactorymap)
   {

      if (::is_null(pfactorymap))
      {

         pfactorymap = ::factory::get_factory_map();

      }

      auto estatus = factory_exchange(strName, pfactorymap);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status library::factory_exchange(const ::string& strNameParam, ::factory_map * pfactorymap)
   {

      string strName(strNameParam);

      if (pfactorymap == nullptr)
      {

         m_psystem->__construct_new(m_pfactorymap);

         pfactorymap = m_pfactorymap;

      }

      string strFactoryExchange;

      if (strName.is_empty())
      {

         strName = m_strName;

         if (strName.is_empty())
         {

            strName = ::file::path(m_strPath).name();

         }

      }

      if (strName.is_empty())
      {

         strFactoryExchange = "factory_exchange";

      }
      else
      {

         strFactoryExchange = strName + "_factory_exchange";

      }

      auto pfn_create_factory = get < PFN_factory_exchange >(strFactoryExchange);

      if (!pfn_create_factory)
      {

         return error_failed;

      }

      pfn_create_factory(pfactorymap);

      return ::success;

   }



   //bool library::create_factory()
   //{

   //   auto pfn_create_factory = get < PFN_create_factory >("create_factory");

   //   if (pfn_create_factory == nullptr)
   //   {

   //      return false;

   //   }

   //   pfn_create_factory();

   //   return true;

   //}

} // namespace acme


//string_map < __pointer(::acme::library) > * g_pmapLibCall = nullptr;


//::acme::library * lib(const char * psz)
//{
//
//   //if (psystem->m_mapLibCall == nullptr)
//   //{
//
//   //   return nullptr;
//
//   //}
//
//   auto & plibrary = psystem->m_mapLibCall[psz];
//
//   if(!plibrary)
//   {
//      
//      __own(psystem, m_mapLibCall[psz], __new(::acme::library));
//
//      plibrary->initialize(::get_task());
//
//      plibrary->open(psz);
//
//   }
//
//   return plibrary;
//
//}



#if defined(LINUX)

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


