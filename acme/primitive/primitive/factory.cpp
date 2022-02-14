#include "framework.h"
#include "acme/platform/static_start_internal.h"
#include "acme/platform/simple_log.h"




namespace factory
{


   factory_item_interface::factory_item_interface()
   {


   }


   factory_item_interface::~factory_item_interface()
   {


   }


    CLASS_DECL_ACME factory_array * get_factory_item_array()
    {

       return ::acme::static_start::g_staticstart.m_pfactorya;

    }


    CLASS_DECL_ACME critical_section * get_factory_critical_section()
    {

       return ::acme::static_start::g_staticstart.m_pcriticalsectionFactory;

    }


    CLASS_DECL_ACME factory * get_factory()
    {

       return ::acme::static_start::g_staticstart.m_pfactory;

    }



    void factory_init()
    {

       ::acme::static_start::g_staticstart.m_pfactory = new factory();

       ::acme::static_start::g_staticstart.m_pfactory->m_mapGlobalFactory.InitHashTable(16189);

       ::acme::static_start::g_staticstart.m_pfactorya = new factory_array();



       ____creatable(manual_reset_event);
       ____creatable(task);


       ____creatable_from_base(simple_log, logger);


       //operating_system_initialize_nano();


    }


   void factory_close()
   {

      critical_section_lock synchronouslock(::acme::static_start::g_staticstart.m_pcriticalsectionFactory);

      ::acme::static_start::g_staticstart.m_pfactory->m_mapGlobalFactory.erase_all();

      ::acme::static_start::g_staticstart.m_pfactorya->erase_all();

   }

   void factory_term()
   {

      critical_section_lock synchronouslock(::acme::static_start::g_staticstart.m_pcriticalsectionFactory);

      ::acme::del(::acme::static_start::g_staticstart.m_pfactorya);

      ::acme::del(::acme::static_start::g_staticstart.m_pfactory);

   }


   void factory::merge(const ::factory::factory* pfactory)
   {

      for (auto& pair : pfactory->m_mapGlobalFactory)
      {

         m_mapGlobalFactory.set_at(pair.m_element1, pair.m_element2);

      }

      for (auto& pair : pfactory->m_mapFactory)
      {

         auto& map = m_mapFactory[pair.m_element1];

         for (auto& pair2 : pair.m_element2)
         {

            map.set_at(pair2.m_element1, pair2.m_element2);

         }

      }

   }


   void factory::merge_to_global_factory() const
   {

      ::factory::get_factory()->merge(this);

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


//CLASS_DECL_ACME __pointer(alloc_interface) & get_factory_item2(const ::string & strName)
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
//   plibrary->add_factory_item();
//
//   auto & pfactory = get_factory_item(strName);
//
//   if (!pfactory)
//   {
//
//      FORMATTED_INFORMATION("plibrary->add_factory_item()? : Library \"%s\" didn't register any relevant factory_item for type name \"%s\"?", strLibrary.c_str(), strName.c_str());
//
//   }
//
//
//   return pfactory;
//
//}





//#ifdef __DEBUG
//#include "acme/inline/factory_item.cpp"
//#endif


