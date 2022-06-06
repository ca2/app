#include "framework.h"
#include "acme/platform/acme.h"
#include "acme/platform/simple_log.h"
#include "acme/platform/library.h"


CLASS_DECL_ACME class ::system * get_system();


namespace factory
{


   factory_item_interface::factory_item_interface()
   {


   }


   factory_item_interface::~factory_item_interface()
   {


   }


//    CLASS_DECL_ACME factory_array * get_factory_item_array()
//    {
//
//       return ::acme::acme::g_pstaticstatic->m_pfactorya;
//
//    }


    CLASS_DECL_ACME critical_section * get_factory_critical_section()
    {

       return ::acme::acme::g_p->m_pcriticalsectionFactory;

    }


    CLASS_DECL_ACME factory * get_factory()
    {

       return ::acme::acme::g_p->m_pfactory;

    }


   CLASS_DECL_ACME factory * get_factory(const ::atom & atomSource)
   {

      auto & pfactory = ::acme::acme::g_p->m_mapFactory[atomSource];

      if (!pfactory)
      {

         auto psystem = ::get_system();
         
         psystem->__construct_new(pfactory);

      }

      return pfactory;

   }


   void factory::merge(const ::factory::factory* pfactory)
   {

      for (auto& pair : *pfactory)
      {

         set_at(pair.m_element1, pair.m_element2);

      }

      if (pfactory->m_plibrary)
      {

         auto pfactoryImplicit = pfactory->m_plibrary->create_factory();

         for (auto& pair : *pfactoryImplicit)
         {

            set_at(pair.m_element1, pair.m_element2);

         }

      }

   }


   void factory::merge_to_global_factory() const
   {

      ::factory::get_factory()->merge(this);

   }


   void factory::set_currently_loading_library()
   {

      if (m_plibrary)
      {

         throw ::exception(error_wrong_state);

      }

      //if (::acme::library::loading_library() != nullptr)
      //{

      //   m_plibrary = ::acme::library::loading_library();

      //}

   }


   //CLASS_DECL_ACME::factory::factory * loading_library_factory()
   //{

   //   auto plibrary = ::acme::library::loading_library();
   // 
   //   if (::is_null(plibrary))
   //   {

   //      return nullptr;

   //   }

   //   auto pfactory = plibrary->get_factory();

   //   if (::is_null(pfactory))
   //   {

   //      return nullptr;

   //   }

   //   return pfactory;

   //}


//   void merge_library_to_global_factory(const ::atom & atomSource)
//   {
//
//      auto & mapFactory = ::factory::get_factory()->m_mapFactory[atomSource];
//
//      auto & mapGlobalFactory = ::factory::get_factory()->m_mapGlobalFactory;
//
//      for (auto& pair : mapFactory)
//      {
//
//         mapGlobalFactory.set_at(pair.m_element1, pair.m_element2);
//
//      }
//
//   }


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
