#include "framework.h"


namespace factory
{

   CLASS_DECL_ACME critical_section * g_pcsFactory = nullptr;
   CLASS_DECL_ACME factory_map * g_pfactorymap = nullptr;
   CLASS_DECL_ACME factory_array * g_pfactorya = nullptr;


   factory_interface::factory_interface()
   {


   }


   factory_interface::~factory_interface()
   {


   }


   void factory_init()
   {

      g_pcsFactory = new critical_section();

      g_pfactorymap = new factory_map();

      g_pfactorymap->InitHashTable(16189);

      g_pfactorya = new factory_array();

   }


   void factory_close()
   {

      cslock sl(g_pcsFactory);

      g_pfactorymap->remove_all();

      g_pfactorya->remove_all();

   }

   void factory_term()
   {

      cslock sl(g_pcsFactory);

      ::acme::del(g_pfactorya);

      ::acme::del(g_pfactorymap);

      ::acme::del(g_pcsFactory);

   }


} // namespace factory








//CLASS_DECL_ACME ::mutex * g_pmutexFactory = nullptr;





















CLASS_DECL_ACME bool safe_destroy_element(elemental * pelement)
{

   try
   {

      pelement->~elemental();

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


//CLASS_DECL_ACME __pointer(alloc_interface) & get_factory2(const string & strName)
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
//   auto plibrary = ::get_context_system()->get_library(strLibrary);
//
//   plibrary->create_factory();
//
//   auto & pfactory = get_factory(strName);
//
//   if (!pfactory)
//   {
//
//      INFO("plibrary->create_factory()? : Library \"%s\" didn't register any relevant factory for type name \"%s\"?", strLibrary.c_str(), strName.c_str());
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


