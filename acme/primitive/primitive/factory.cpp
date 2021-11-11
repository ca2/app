#include "framework.h"
#include "acme/platform/static_start_internal.h"


namespace factory
{


   factory_interface::factory_interface()
   {


   }


   factory_interface::~factory_interface()
   {


   }


    CLASS_DECL_ACME factory_array * get_factory_array()
    {

       return ::acme::static_start::g_staticstart.m_pfactorya;

    }


    CLASS_DECL_ACME critical_section * get_factory_critical_section()
    {

       return &::acme::static_start::g_staticstart.m_criticalsectionFactory;

    }


    CLASS_DECL_ACME factory_map * get_factory_map()
    {

       return ::acme::static_start::g_staticstart.m_pfactorymap;

    }



    void factory_init()
    {

       ::acme::static_start::g_staticstart.m_pfactorymap = new factory_map();

       ::acme::static_start::g_staticstart.m_pfactorymap->InitHashTable(16189);

       ::acme::static_start::g_staticstart.m_pfactorya = new factory_array();

    }


   void factory_close()
   {

      critical_section_lock synchronouslock(&::acme::static_start::g_staticstart.m_criticalsectionFactory);

      ::acme::static_start::g_staticstart.m_pfactorymap->erase_all();

      ::acme::static_start::g_staticstart.m_pfactorya->erase_all();

   }

   void factory_term()
   {

      critical_section_lock synchronouslock(&::acme::static_start::g_staticstart.m_criticalsectionFactory);

      ::acme::del(::acme::static_start::g_staticstart.m_pfactorya);

      ::acme::del(::acme::static_start::g_staticstart.m_pfactorymap);

   }


} // namespace factory








//CLASS_DECL_ACME ::mutex * g_pmutexFactory = nullptr;





















CLASS_DECL_ACME bool safe_destroy_element(matter * pmatter)
{

   try
   {

      pmatter->~matter();

   }
   catch(...)
   {

      return false;

   }

   return true;

}


CLASS_DECL_ACME bool safe_free_memory(void * ptype)
{


   try
   {

      memory_free(ptype);

   }
   catch(...)
   {

      return false;

   }

   return true;

}


//CLASS_DECL_ACME __pointer(alloc_interface) & get_factory2(const ::string & strName)
//{
//
//   string_array stra;
//
//   stra.explode("::", strName);
//
//   string strLibrary;
//
//   strLibrary = stra.implode("_");
//
//   auto plibrary = get_system()->get_library(strLibrary);
//
//   plibrary->create_factory();
//
//   auto & pfactory = get_factory(strName);
//
//   if (!pfactory)
//   {
//
//      FORMATTED_INFORMATION("plibrary->create_factory()? : Library \"%s\" didn't register any relevant factory for type name \"%s\"?", strLibrary.c_str(), strName.c_str());
//
//   }
//
//
//   return pfactory;
//
//}





//#ifdef __DEBUG
//#include "acme/inline/factory.cpp"
//#endif


