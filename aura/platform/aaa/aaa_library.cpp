#include "framework.h"
#include "aura/platform/system_setup.h"


//extern string_map < ::pointer<::acme::library >>* g_pmapLibrary;

//extern ::pointer< ::mutex > ::auraacmesystem()->m_pmutexLibrary;


typedef  void(*PFN_create_factory)();


namespace aura
{


   const ::scoped_string & scopedstr_empty_app_id = "";


   void     library::initialize(::particle * pparticle)
   {

      auto estatus = ::object::initialize(pparticle);

      m_plibrary = nullptr;

      m_bAutoUnload = false;

      return estatus;

   }


   void library::initialize_aura_library(::particle * pparticle,int iDesambig, const ::scoped_string & scopedstrRoot, const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrFolder)
   {

      auto estatus = initialize(pparticle);

      if (!estatus)
      {

         return estatus;

      }

      string strRoot(scopedstrRoot);

      strRoot.trim();

      if (strRoot.has_character())
      {

         m_strRoot = strRoot;

      }
      else
      {

         strRoot = m_strRoot;

      }

      m_strName = ::is_null(scopedstrName) ? strRoot : string(scopedstrName);

      if (::is_set(scopedstrFolder))
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

      if(strRoot.has_character())
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


   bool library::open(const ::scoped_string & scopedstrPath,bool bAutoClose,bool bCa2Path)
   {

      synchronous_lock synchronouslock(::auraacmesystem()->m_pmutexLibrary);

      m_strMessage.empty();

      auto pfnNewAuraLibrary = get_get_new_aura_library(scopedstrPath);

      if (pfnNewAuraLibrary != nullptr)
      {

         m_strPath = pszPath;

         if (m_strCa2Name.has_character())
         {

            ::auraacmesystem()->m_mapLibrary[m_strCa2Name] = this;

         }

         return true;

      }

      try
      {

         if(bCa2Path)
         {

            m_plibrary = __node_library_open_ca2(scopedstrPath, m_strMessage);

         }
         else
         {

            m_plibrary = __node_library_open(scopedstrPath, m_strMessage);

         }

         if(m_plibrary == nullptr)
         {

            error() <<"acme::library::open error: " << pszPath;

            return false;

         }

         m_strPath = pszPath;

      }
      catch(...)
      {

         errorf("acme::library::open Failed to open library %s with errors %s", (bCa2Path ? " (ca2 path)" : ""), m_strMessage.c_str());

         return false;

      }

      information() << "acme::library::open success";

      if (m_strCa2Name.has_character())
      {

         ::auraacmesystem()->m_mapLibrary.set_at(m_strCa2Name, this);

      }

      return true;

   }


   bool library::open_ca2_library(string strTitle)
   {

      synchronous_lock synchronouslock(::auraacmesystem()->m_pmutexLibrary);

      if (m_pca2library.is_set())
      {

         return true;

      }

      ::exception_engine().reset();

      PFN_NEW_AURA_LIBRARY pfnNewAuraLibrary = nullptr;

      int iPhase = 0;

      try
      {
      
         m_pca2library = ::auraacmesystem()->on_get_library(m_strName);

      }
      catch (...)
      {

         m_pca2library.release();

      }

      if (!m_pca2library)
      {

         try
         {

            pfnNewAuraLibrary = get_get_new_aura_library(m_strPath);

            if (pfnNewAuraLibrary == nullptr)
            {

               iPhase++;

               if (strTitle.has_character())
               {

                  get(pfnNewAuraLibrary, strTitle + "_get_new_library");

               }

            }

            if (pfnNewAuraLibrary == nullptr)
            {

               iPhase++;

               strTitle = m_strPath.title();

               get(pfnNewAuraLibrary, strTitle + "_get_new_library");

            }

            if (pfnNewAuraLibrary == nullptr)
            {

               iPhase++;

               if (strTitle.begins_eat("lib"))
               {

                  get(pfnNewAuraLibrary, strTitle + "_get_new_library");

               }

            }

            if (pfnNewAuraLibrary == nullptr)
            {

               iPhase++;

               get(pfnNewAuraLibrary, "get_new_library");

            }

         }
         catch (...)
         {

            close();

            return false;

         }

         if (pfnNewAuraLibrary == nullptr)
         {

            close();

            return false;

         }

         try
         {

            m_pca2library = ::transfer(pfnNewAuraLibrary());

         }
         catch (...)
         {

            m_pca2library.release();

         }

      }

      if(m_pca2library.is_null())
      {

         close();

         return false;

      }

      m_pca2library->initialize_aura_library(this, 0, m_strRoot, m_strName, m_strFolder);

      m_pca2library->initialize_factory();

      m_pca2library->set_object(this);

      if (m_pca2library->m_strCa2Name.is_empty())
      {

         m_pca2library->m_strCa2Name = m_strPath.title();

         m_strCa2Name = m_strPath;

      }
      else
      {

         m_strCa2Name = m_pca2library->m_strCa2Name;

      }

      if (m_strCa2Name.has_character())
      {

         ::auraacmesystem()->m_mapLibrary.set_at(m_strCa2Name, this);

      }

      return true;

   }


   library * library::get_ca2_library()
   {

      return m_pca2library;

   }


   string library::get_library_name()
   {

      synchronous_lock synchronouslock(::auraacmesystem()->m_pmutexLibrary);

      if(m_pca2library)
      {

         return m_pca2library->get_library_name();

      }
      else
      {

         string strName(m_strCa2Name);

         string strPrefix(get_root());

#ifdef UNIVERSAL_WINDOWS

         //         strPrefix = "m_" + strPrefix;

#endif

         strPrefix.replace("-","_");

         strPrefix += "_";

         strName.case_insensitive_begins_eat(strPrefix);

         return strName;

      }

   }


   void * library::get_os_data()
   {

      return m_plibrary;

   }


   bool library::close()
   {

      synchronous_lock synchronouslock(::auraacmesystem()->m_pmutexLibrary);

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


   string library::get_app_id(const ::scoped_string & scopedstrAppName)
   {

      synchronous_lock synchronouslock(::auraacmesystem()->m_pmutexLibrary);

      if(!contains_app(scopedstrAppName))
         return "";

      string strPrefix(get_root());

      string strLibraryName(get_library_name());

#if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__)

      if(strLibraryName == "libca2")
      {

         strLibraryName = "ca2";

      }
      else if(!strLibraryName.begins_eat("libca2"))
      {

         strLibraryName.begins_eat("lib");

      }

#elif defined(UNIVERSAL_WINDOWS)

      //      strLibraryName.case_insensitive_begins_eat("m_");

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


   string library::get_app_name(const ::scoped_string & scopedstrAppId)
   {

      synchronous_lock synchronouslock(::auraacmesystem()->m_pmutexLibrary);

      string strAppName(scopedstrAppId);

      string strPrefix(get_root());

      string strLibraryName(get_library_name());

#if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__)

      if(strLibraryName == "libca2")
      {

         strLibraryName = "ca2";

      }
      else if(!strLibraryName.begins_eat("libca2"))
      {

         strLibraryName.begins_eat("lib");

      }

#elif defined(UNIVERSAL_WINDOWS)

      //      strLibraryName.case_insensitive_begins_eat("m_");

#endif

      strPrefix += "/";

      strPrefix += strLibraryName;

      strPrefix += "/";

      strAppName.begins_eat(strPrefix);

      if(!contains_app(strAppName))
      {

         strAppName     = pszAppId;

         strPrefix      = get_root();

         strPrefix += "/";

         strAppName.begins_eat(strPrefix);

         if(!contains_app(strAppName))
            return "";
      }

      return strAppName;

   }


   ::pointer<::aura::application>library::get_new_application(::particle * pparticle, const ::scoped_string & scopedstrAppId)
   {

      synchronous_lock synchronouslock(::auraacmesystem()->m_pmutexLibrary);

      try
      {

         auto psetup = ::system_setup::get_first(::system_setup::flag_application, pszAppId);

         if (psetup)
         {

            auto papp = psetup->create_new_application();

            if (papp)
            {

               auto estatus = papp->initialize(pparticle);

               if (!estatus)
               {

                  return estatus;

               }

               return papp;

            }

         }

         if (get_ca2_library() == nullptr)
         {

            open_ca2_library();

         }

         if(get_ca2_library() != nullptr)
         {

            string strAppName = get_app_name(scopedstrAppId);

            if (strAppName.is_empty())
            {

               return nullptr;

            }

            auto papp = get_ca2_library()->get_new_application(pparticle, strAppName);

            if (!papp)
            {

               return papp;

            }

            papp->m_strLibraryName   = m_strCa2Name;

            return papp;

         }
         else
         {

            auto p = get<PFN_NEW_AURA_APPLICATION>("new_aura_application");

            if (p)
            {

               auto papp = (*p)();

               if (papp)
               {

                  papp->initialize(pparticle);

               }

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

      synchronous_lock synchronouslock(::auraacmesystem()->m_pmutexLibrary);

      if(get_ca2_library() != nullptr)
      {
         try
         {
            get_ca2_library()->get_app_list(stra);
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
//         strAppId.begins_eat("lib");
//
//#elif defined(UNIVERSAL_WINDOWS)
//
//         //         strPrefix = "m_" + strPrefix;
//
//#endif
//
//         strPrefix.replace("-","_");
//
//         strPrefix += "_";
//
//         strAppId.case_insensitive_begins_eat(strPrefix);
//
//         //if(strAppId.case_insensitive_begins_eat(strPrefix))
//         {
//
//            stra.add(strAppId);
//
//         }

      }

   }


   ::matter* library::new_object(::object* pparticle, const ::scoped_string & scopedstrClassId)
   {

      return nullptr;

   }


   ::pointer<::matter>library::create_object(::particle * pparticle, const ::scoped_string & scopedstrClass)
   {

      synchronous_lock synchronouslock(::auraacmesystem()->m_pmutexLibrary);

      if (factory_has_object_class(scopedstrClass))
      {

         return factory_create(pparticle, pszClass);

      }
      
      ::matter * p = nullptr;

      if(get_ca2_library() != nullptr)
      {

         p = get_ca2_library()->new_object(pparticle, pszClass);

      }
      else
      {
         
         p = new_object(pparticle, pszClass);

      }

      auto pparticle = ::transfer(p);
      
      if (::is_null(pparticle))
      {

         return nullptr;

      }

      pparticle->initialize(pparticle);

      return pparticle;

   }


   bool library::has_object_class(const ::scoped_string & scopedstrClassId)
   {

      synchronous_lock synchronouslock(::auraacmesystem()->m_pmutexLibrary);

      if (factory_has_object_class(scopedstrClassId))
      {

         return false;

      }

      if (get_ca2_library() == nullptr)
      {

         return false;

      }

      return get_ca2_library()->has_object_class(scopedstrClassId);

   }


   bool library::contains_app(const ::scoped_string & scopedstrAppId)
   {

      synchronous_lock synchronouslock(::auraacmesystem()->m_pmutexLibrary);

      string_array stra;

      get_app_list(stra);

      return stra.contains(scopedstrAppId);

   }


   string library::get_root()
   {

      synchronous_lock synchronouslock(::auraacmesystem()->m_pmutexLibrary);

      if(m_pca2library)
      {

         return m_pca2library->m_strRoot;

      }

      return m_strRoot;

   }


   void library::get_create_impact_id_list(::array < atom > & ida)
   {

      synchronous_lock synchronouslock(::auraacmesystem()->m_pmutexLibrary);

      __UNREFERENCED_PARAMETER(ida);

   }


   bool library::is_opened()
   {

      synchronous_lock synchronouslock(::auraacmesystem()->m_pmutexLibrary);

      return m_plibrary != nullptr;

   }


   bool library::is_closed()
   {

      return !is_opened();

   }


   void * library::raw_get(const ::scoped_string & scopedstrEntryName)
   {

      synchronous_lock synchronouslock(::auraacmesystem()->m_pmutexLibrary);

      return __node_library_raw_get(m_plibrary,pszEntryName);

   }

   
   ::matter* library::factory_new(::object* pparticle, const ::string & lpszClass)
   {

      return nullptr;

   }


   ::pointer<::matter>library::factory_create(::particle * pparticle, const ::string & lpszClass)
   {

      library_object_allocator_base * pallocator = find_allocator(lpszClass);

      if (pallocator == nullptr)
      {

         return nullptr;

      }

      auto p = pallocator->new_object(pparticle);

      auto pparticle = ::transfer(p);

      if (!pparticle)
      {

         return nullptr;

      }

      return pparticle;

   }


   bool library::factory_has_object_class(const ::string & lpszClass)
   {

      return find_allocator(lpszClass) != nullptr;

   }


   library_object_allocator_base * library::find_allocator(const ::string & lpszClass)
   {

      auto pFind = m_allocatorptra.predicate_find_first([&](auto & pallocator)
      {

         return pallocator->m_strName == lpszClass;

      });

      if (::is_null(pFind))
      {

         return nullptr;

      }

      return m_allocatorptra[iFind];

   }


   void library::initialize_factory()
   {

   }


   bool library::add_factory_item()
   {

      auto pfn_create_factory = get < PFN_create_factory >("add_factory_item");

      if (pfn_create_factory == nullptr)
      {

         return false;

      }

      pfn_create_factory();

      return true;

   }

} // namespace aura


//string_map < ::pointer<::acme::library >>* g_pmapLibCall = nullptr;


::acme::library * lib(const ::scoped_string & scopedstr)
{

   //if (::auraacmesystem()->m_mapLibCall == nullptr)
   //{

   //   return nullptr;

   //}

   ::pointer<::acme::library>& plibrary = ::auraacmesystem()->m_mapLibCall[psz];

   if(!plibrary)
   {
      
      plibrary = __allocate ::acme::library();

      plibrary->initialize(::get_task());

      plibrary->open(scopedstr);

   }

   return plibrary;

}



#if defined(LINUX)

::file::path library_file_name(const ::scoped_string & scopedstr)
{
   return "lib" + str + ".so";
}

#elif defined(__ANDROID__)

::file::path library_file_name(const ::scoped_string & scopedstr)
{
   return "lib" + str + ".so";
}

#elif defined(WINDOWS)

::file::path library_file_name(const ::scoped_string & scopedstr)
{
   return str + ".dll";
}

#elif defined(__APPLE__)

::file::path library_file_name(const ::scoped_string & scopedstr)
{
   return "lib" + str + ".dylib";
}

#endif


