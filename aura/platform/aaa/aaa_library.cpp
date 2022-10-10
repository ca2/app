#include "framework.h"
#include "aura/platform/system_setup.h"


//extern string_map < ::pointer<::acme::library >>* g_pmapLibrary;

//extern ::mutex * ::aura::get_system()->m_mutexLibrary;


typedef  void(*PFN_create_factory)();


namespace aura
{


   const char * psz_empty_app_id = "";


   void     library::initialize(::object * pobject)
   {

      auto estatus = ::object::initialize(pobject);

      m_plibrary = nullptr;

      m_bAutoUnload = false;

      return estatus;

   }


   void library::initialize_aura_library(::object * pobject,int iDesambig, const ::string & pszRoot, const ::string & pszName, const ::string & pszFolder)
   {

      auto estatus = initialize(pobject);

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


   bool library::open(const ::string & pszPath,bool bAutoClose,bool bCa2Path)
   {

      synchronous_lock synchronouslock(::aura::get_system()->m_mutexLibrary);

      m_strMessage.Empty();

      auto pfnNewAuraLibrary = get_get_new_aura_library(pszPath);

      if (pfnNewAuraLibrary != nullptr)
      {

         m_strPath = pszPath;

         if (m_strCa2Name.has_char())
         {

            ::aura::get_system()->m_mapLibrary[m_strCa2Name] = this;

         }

         return true;

      }

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

            ERROR("acme::library::open error: " << pszPath);

            return false;

         }

         m_strPath = pszPath;

      }
      catch(...)
      {

         FORMATTED_ERROR("acme::library::open Failed to open library %s with errors %s", (bCa2Path ? " (ca2 path)" : ""), m_strMessage.c_str());

         return false;

      }

      INFORMATION("acme::library::open success");

      if (m_strCa2Name.has_char())
      {

         ::aura::get_system()->m_mapLibrary.set_at(m_strCa2Name, this);

      }

      return true;

   }


   bool library::open_ca2_library(string strTitle)
   {

      synchronous_lock synchronouslock(::aura::get_system()->m_mutexLibrary);

      if (m_pca2library.is_set())
      {

         return true;

      }

      ::exception_engine().reset();

      PFN_NEW_AURA_LIBRARY pfnNewAuraLibrary = nullptr;

      int iPhase = 0;

      try
      {
      
         m_pca2library = ::aura::get_system()->on_get_library(m_strName);

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

               if (strTitle.has_char())
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

               if (::str().begins_eat(strTitle, "lib"))
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

            m_pca2library = ::move(pfnNewAuraLibrary());

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

      if (m_strCa2Name.has_char())
      {

         ::aura::get_system()->m_mapLibrary.set_at(m_strCa2Name, this);

      }

      return true;

   }


   library * library::get_ca2_library()
   {

      return m_pca2library;

   }


   string library::get_library_name()
   {

      synchronous_lock synchronouslock(::aura::get_system()->m_mutexLibrary);

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

      synchronous_lock synchronouslock(::aura::get_system()->m_mutexLibrary);

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


   string library::get_app_id(const ::string & pszAppName)
   {

      synchronous_lock synchronouslock(::aura::get_system()->m_mutexLibrary);

      if(!contains_app(pszAppName))
         return "";

      string strPrefix(get_root());

      string strLibraryName(get_library_name());

#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      if(strLibraryName == "libca2")
      {

         strLibraryName = "ca2";

      }
      else if(!::str().begins_eat(strLibraryName,"libca2"))
      {

         ::str().begins_eat(strLibraryName,"lib");

      }

#elif defined(_UWP)

      //      ::str().begins_eat_ci(strLibraryName, "m_");

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


   string library::get_app_name(const ::string & pszAppId)
   {

      synchronous_lock synchronouslock(::aura::get_system()->m_mutexLibrary);

      string strAppName(pszAppId);

      string strPrefix(get_root());

      string strLibraryName(get_library_name());

#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      if(strLibraryName == "libca2")
      {

         strLibraryName = "ca2";

      }
      else if(!::str().begins_eat(strLibraryName,"libca2"))
      {

         ::str().begins_eat(strLibraryName,"lib");

      }

#elif defined(_UWP)

      //      ::str().begins_eat_ci(strLibraryName, "m_");

#endif

      strPrefix += "/";

      strPrefix += strLibraryName;

      strPrefix += "/";

      ::str().begins_eat(strAppName,strPrefix);

      if(!contains_app(strAppName))
      {

         strAppName     = pszAppId;

         strPrefix      = get_root();

         strPrefix += "/";

         ::str().begins_eat(strAppName,strPrefix);

         if(!contains_app(strAppName))
            return "";
      }

      return strAppName;

   }


   ::pointer<::aura::application>library::get_new_application(::object * pobject, const ::string & pszAppId)
   {

      synchronous_lock synchronouslock(::aura::get_system()->m_mutexLibrary);

      try
      {

         auto psetup = ::system_setup::get_first(::system_setup::flag_application, pszAppId);

         if (psetup)
         {

            auto papp = psetup->create_new_application();

            if (papp)
            {

               auto estatus = papp->initialize(pobject);

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

            string strAppName = get_app_name(pszAppId);

            if (strAppName.is_empty())
            {

               return nullptr;

            }

            auto papp = get_ca2_library()->get_new_application(pobject, strAppName);

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

                  papp->initialize(pobject);

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

      synchronous_lock synchronouslock(::aura::get_system()->m_mutexLibrary);

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
//         ::str().begins_eat(strAppId,"lib");
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
//         ::str().begins_eat_ci(strAppId,strPrefix);
//
//         //if(::str().begins_eat_ci(strAppId,strPrefix))
//         {
//
//            stra.add(strAppId);
//
//         }

      }

   }


   ::matter* library::new_object(::object* pobject, const ::string & pszClassId)
   {

      return nullptr;

   }


   ::pointer<::matter>library::create_object(::object * pobject, const ::string & pszClass)
   {

      synchronous_lock synchronouslock(::aura::get_system()->m_mutexLibrary);

      if (factory_has_object_class(pszClass))
      {

         return factory_create(pobject, pszClass);

      }
      
      ::matter * p = nullptr;

      if(get_ca2_library() != nullptr)
      {

         p = get_ca2_library()->new_object(pobject, pszClass);

      }
      else
      {
         
         p = new_object(pobject, pszClass);

      }

      auto pobject = ::move(p);
      
      if (::is_null(pobject))
      {

         return nullptr;

      }

      pobject->initialize(pobject);

      return pobject;

   }


   bool library::has_object_class(const ::string & pszClassId)
   {

      synchronous_lock synchronouslock(::aura::get_system()->m_mutexLibrary);

      if (factory_has_object_class(pszClassId))
      {

         return false;

      }

      if (get_ca2_library() == nullptr)
      {

         return false;

      }

      return get_ca2_library()->has_object_class(pszClassId);

   }


   bool library::contains_app(const ::string & pszAppId)
   {

      synchronous_lock synchronouslock(::aura::get_system()->m_mutexLibrary);

      string_array stra;

      get_app_list(stra);

      return stra.contains(pszAppId);

   }


   string library::get_root()
   {

      synchronous_lock synchronouslock(::aura::get_system()->m_mutexLibrary);

      if(m_pca2library)
      {

         return m_pca2library->m_strRoot;

      }

      return m_strRoot;

   }


   void library::get_create_impact_id_list(::array < atom > & ida)
   {

      synchronous_lock synchronouslock(::aura::get_system()->m_mutexLibrary);

      __UNREFERENCED_PARAMETER(ida);

   }


   bool library::is_opened()
   {

      synchronous_lock synchronouslock(::aura::get_system()->m_mutexLibrary);

      return m_plibrary != nullptr;

   }


   bool library::is_closed()
   {

      return !is_opened();

   }


   void * library::raw_get(const ::string & pszEntryName)
   {

      synchronous_lock synchronouslock(::aura::get_system()->m_mutexLibrary);

      return __node_library_raw_get(m_plibrary,pszEntryName);

   }

   
   ::matter* library::factory_new(::object* pobject, const ::string & lpszClass)
   {

      return nullptr;

   }


   ::pointer<::matter>library::factory_create(::object * pobject, const ::string & lpszClass)
   {

      library_object_allocator_base * pallocator = find_allocator(lpszClass);

      if (pallocator == nullptr)
      {

         return nullptr;

      }

      auto p = pallocator->new_object(pobject);

      auto pobject = ::move(p);

      if (!pobject)
      {

         return nullptr;

      }

      return pobject;

   }


   bool library::factory_has_object_class(const ::string & lpszClass)
   {

      return find_allocator(lpszClass) != nullptr;

   }


   library_object_allocator_base * library::find_allocator(const ::string & lpszClass)
   {

      index iFind = m_allocatorptra.predicate_find_first([&](auto & pallocator)
      {

         return pallocator->m_strName == lpszClass;

      });

      if (iFind < 0)
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


::acme::library * lib(const ::string & psz)
{

   //if (::aura::get_system()->m_mapLibCall == nullptr)
   //{

   //   return nullptr;

   //}

   ::pointer<::acme::library>& plibrary = ::aura::get_system()->m_mapLibCall[psz];

   if(!plibrary)
   {
      
      plibrary = __new(::acme::library);

      plibrary->initialize(::get_task());

      plibrary->open(psz);

   }

   return plibrary;

}



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


