#include "framework.h"
////#include "acme/exception/exception.h"
//#include "acme/platform/acme.h"
#include "acme/platform/simple_log.h"
#include "acme/platform/library.h"
#include "acme/platform/system.h"
#include "acme/primitive/primitive/factory.h"
#include "acme/primitive/string/string.h"



//CLASS_DECL_ACME ::acme::system * acmesystem();


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


//    CLASS_DECL_ACME critical_section * ::factory_critical_section()
//    {
//
//       return &::acme::acme::g_p->factory_;
//
//    }


   factory::factory()
   {


   }



   factory::~factory()
   {


   }


   void factory::merge(const ::factory::factory* pfactory)
   {

      for (auto& pair : *pfactory)
      {

         set_at(pair.m_element1, pair.m_element2);

      }

      if (pfactory->m_plibrary)
      {

         ::factory::factory_pointer pfactoryImplicit;
            
         pfactory->m_plibrary->create_factory(pfactoryImplicit);

         for (auto& pair : *pfactoryImplicit)
         {

            set_at(pair.m_element1, pair.m_element2);

         }

      }

   }


   void factory::merge_to_global_factory() const
   {

      ((::factory::factory*)this)->::particle::factory()->merge(this);

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
//      auto & mapFactory = factory()->m_mapFactory[atomSource];
//
//      auto & mapGlobalFactory = factory()->m_mapGlobalFactory;
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








//CLASS_DECL_ACME ::pointer< ::mutex > g_pmutexFactory = nullptr;





















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


//CLASS_DECL_ACME ::pointer<alloc_interface>& get_factory_item2(const ::string & strName)
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
//   auto plibrary = acmesystem()->get_library(strLibrary);
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








//
//template < typename BASE_TYPE >
//inline ::pointer<BASE_TYPE>__create()
//{
//
//   auto pfactory = factory_item < BASE_TYPE >();
//
//   if (!pfactory)
//   {
//
//      return nullptr;
//
//   }
//
//   ::pointer<::matter>ptypeNew = pfactory->call_new();
//
//   if (!ptypeNew)
//   {
//
//      return nullptr;
//
//   }
//
//   ::pointer<BASE_TYPE>pusermessage = ptypeNew;
//
//   if (!pusermessage)
//   {
//
//      return nullptr;
//
//   }
//
//   return pusermessage;
//
//}
//
//
//template < typename BASE_TYPE >
//inline ::pointer<BASE_TYPE>__create(::particle * pparticle)
//{
//
//   auto p = __create < BASE_TYPE >();
//
//   if (!p)
//   {
//
//      return nullptr;
//
//   }
//
//   auto estatus = p->initialize(pparticle);
//
//   if (!estatus)
//   {
//
//      return nullptr;
//
//   }
//
//   return p;
//
//}
//
//
//template < typename BASE_TYPE >
//inline ::pointer<BASE_TYPE>__id_create(const ::atom & atom)
//{
//
//   auto pfactory = factory_item(atom);
//
//   if (!pfactory)
//   {
//
//      return nullptr;
//
//   }
//
//   auto ptypeNew = pfactory->call_new();
//
//   if (!ptypeNew)
//   {
//
//      return nullptr;
//
//   }
//
//   ::pointer<BASE_TYPE>pusermessage = ptypeNew;
//
//   if (!pusermessage)
//   {
//
//      return nullptr;
//
//   }
//
//   pusermessage->m_eobject |= e_object_factory;
//
//   return pusermessage;
//
//}
//
//
//template < typename TYPE >
//inline ::pointer<TYPE>__create_new()
//{
//
//   auto ptype = __new(TYPE);
//
//   if (!ptype)
//   {
//
//      return nullptr;
//
//   }
//
//   return ptype;
//
//}
//
//
//template < typename TYPE >
//inline ::pointer<TYPE>__create_new(const TYPE & t)
//{
//
//   auto ptype = __new(TYPE(t));
//
//   if (!ptype)
//   {
//
//      return nullptr;
//
//   }
//
//   return ptype;
//
//}
//
//
//template < typename TYPE >
//inline ::pointer<TYPE>__create_new(::particle * pparticle)
//{
//
//   auto ptype = __create_new< TYPE > ();
//
//   if (!ptype)
//   {
//
//      return ptype;
//
//   }
//
//   auto estatus = ptype->initialize(pparticle);
//
//   if (!estatus)
//   {
//
//      return nullptr;
//
//   }
//
//   return ptype;
//
//}
//

// __construct __composite


// template < typename OBJECT, typename BASE_TYPE >
// inline void __construct(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite)
// {

//    //if (((uptr)&pcomposite) < (uptr)pparticle || ((uptr)&pcomposite) >= ((uptr)pparticle) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//    //{

//    //   throw ::exception(::status_exception(error_composite_not_composer_member));

//    //}

//    return pparticle->__construct(pcomposite);

// }


// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void __construct(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite, const ::pointer<SOURCE> psource)
// {

//    return __construct(pparticle, pcomposite, psource.m_p);

// }


// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void __construct(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite, const ::member < SOURCE > & psource)
// {

//    return __construct(pparticle, pcomposite, psource.operator SOURCE * ());

// }


// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void __construct(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite, const SOURCE * psource)
// {
// //
// //#ifdef _DEBUG
// //
// //   auto size = sizeof(typename ::raw_type < OBJECT>::RAW_TYPE);
// //
// //   const scoped_string & str = typeid(typename ::raw_type < OBJECT>::RAW_TYPE).name();
// //
// //#endif
// //
// //   if (((uptr)&pcomposite) < (uptr)pparticle || ((uptr)&pcomposite) >= ((uptr)pparticle) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
// //   {
// //
// //      throw ::exception(::status_exception(error_composite_not_composer_member));
// //
// //   }

//    return pparticle->__construct(pcomposite, psource);

// }


// template < typename OBJECT, typename BASE_TYPE >
// inline void __id_construct(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite, const ::atom & atom)
// {

//    //if (((uptr)&pcomposite) < (uptr)pparticle || ((uptr)&pcomposite) >= ((uptr)pparticle) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//    //{

//    //   throw ::exception(::status_exception(error_composite_not_composer_member));

//    //}

//    return pparticle->__id_construct(pcomposite, atom);

// }


// template < typename OBJECT, typename BASE_TYPE >
// inline void __id_construct(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite, const ::type & type)
// {

//    return pparticle->__id_construct(pcomposite, (atom) type);

// }


// template < typename OBJECT, typename TYPE >
// inline void __raw_construct_new(OBJECT && pparticle, ::pointer<TYPE>& pcomposite)
// {

//    return pparticle->__raw_construct_new(pcomposite);

// }


// template < typename OBJECT, typename TYPE >
// inline void __construct_new(OBJECT && pparticle, ::pointer<TYPE>& pcomposite)
// {

//    return pparticle->__construct_new(pcomposite);


// }


// template < typename OBJECT, typename BASE_TYPE >
// inline void __defer_construct(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite) { return !pcomposite ? __construct(pparticle, pcomposite) : ::success; }

// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void __defer_construct(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite, const SOURCE * psource) { return !pcomposite ? __construct(pparticle, pcomposite, psource) : ::success; }

// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void __defer_construct(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite, const ::pointer<SOURCE> psource) { return !pcomposite ? __construct(pparticle, pcomposite, psource) : ::success; }

// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void __defer_construct(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite, const ::member < SOURCE > & psource) { return !pcomposite ? __construct(pparticle, pcomposite, psource) : ::success; }

// template < typename OBJECT, typename BASE_TYPE >
// inline void __defer_id_compose(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite, const ::atom & atom) { return !pcomposite ? __id_construct(pparticle, pcomposite) : ::success; }

// //template < typename OBJECT, typename BASE_TYPE >
// //inline void __defer_id_compose(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite, const ::type & type)  { return !pcomposite ? __construct(pparticle, pcomposite) : ::success; }

// template < typename OBJECT, typename BASE_TYPE >
// inline void __defer_construct_new(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite) { return !pcomposite ? __construct_new(pparticle, pcomposite) : ::success; }


// __construct __reference


//
//template < typename OBJECT, typename BASE_TYPE >
//inline void __refer(OBJECT && pparticle, ::pointer<BASE_TYPE>& preference)
//{
//
//   if (((uptr)&preference) < (uptr)pparticle || ((uptr)&preference) >= ((uptr)pparticle) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//   {
//
//      throw ::exception(::status_exception(error_composite_not_composer_member));
//
//   }
//
//   return pparticle->__internal_onwership(preference);
//
//}

//
//template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//inline void __refer(OBJECT && pparticle, ::pointer<BASE_TYPE>& preference, const ::pointer<SOURCE> psource)
//{
//
//   return __refer(pparticle, preference, psource.m_p);
//
//}
//
//
//template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//inline void __refer(OBJECT && pparticle, ::pointer<BASE_TYPE>& preference, const ::primitive::member < SOURCE > & psource)
//{
//
//   return __refer(pparticle, preference, psource.operator SOURCE * ());
//
//}
//
//
//template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//inline void __refer(OBJECT && pparticle, ::pointer<BASE_TYPE>& preference, const SOURCE * psource)
//{
//
////#ifdef _DEBUG
////
////   auto size = sizeof(typename ::raw_type < OBJECT>::RAW_TYPE);
////
////   const scoped_string & str = typeid(typename ::raw_type < OBJECT>::RAW_TYPE).name();
////
////#endif
////
////   if (((uptr)&preference) < (uptr)pparticle || ((uptr)&preference) >= ((uptr)pparticle) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
////   {
////
////      throw ::exception(::status_exception(error_composite_not_composer_member));
////
////   }
//
//   return pparticle->add_reference(preference, psource);
//
//}


//template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//inline void __defer_refer(OBJECT && pparticle, ::pointer<BASE_TYPE>& preference, const SOURCE * psource) {}
//
//template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//inline void __defer_refer(OBJECT && pparticle, ::pointer<BASE_TYPE>& preference, const ::pointer<SOURCE> psource) {}
//
//template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//inline void __defer_refer(OBJECT && pparticle, ::pointer<BASE_TYPE>& preference, const ::member < SOURCE > & psource) {}


//
//template < typename OBJECT, typename BASE_TYPE >
//inline void __id_refer(OBJECT && pparticle, ::pointer<BASE_TYPE>& preference, const ::atom & atom)
//{
//
//   if (((uptr)&preference) < (uptr)pparticle || ((uptr)&preference) >= ((uptr)pparticle) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//   {
//
//      throw ::exception(::status_exception(error_composite_not_composer_member));
//
//   }
//
//   return pparticle->__id_construct(preference, atom);
//
//}


//template < typename OBJECT, typename BASE_TYPE >
//inline void __id_construct(OBJECT && pparticle, ::pointer<BASE_TYPE>& preference, const ::type & type)
//{
//
//   if (((uptr)&preference) < (uptr)pparticle || ((uptr)&preference) >= ((uptr)pparticle) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//   {
//
//      throw ::exception(::status_exception(error_composite_not_composer_member));
//
//   }
//
//   return pparticle->__id_construct(preference, (atom)type);
//
//}


//template < typename OBJECT, typename BASE_TYPE >
//inline void __construct_new(OBJECT && pparticle, ::pointer<BASE_TYPE>& preference)
//{
//
//   if (((uptr)&preference) < (uptr)pparticle || ((uptr)&preference) >= ((uptr)pparticle) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//   {
//
//      throw ::exception(::status_exception(error_composite_not_composer_member));
//
//   }
//
//   return pparticle->__construct_new(preference);
//
//}


// __construct
//
//
//template < typename BASE_TYPE >
//inline void __construct(::pointer<BASE_TYPE>& pusermessage)
//{
//
//   auto & pfactory = factory_item < BASE_TYPE >();
//
//   if (pfactory)
//   {
//
//      auto ptypeNew = pfactory->call_new();
//
//      if (!ptypeNew)
//      {
//
//         ::release(pusermessage);
//
//         return ::error_no_memory;
//
//      }
//
//      __dynamic_cast(pusermessage, ptypeNew);
//
//   }
//   else
//   {
//
//       return ::error_not_implemented;
//
//   }
//
//
//   if (!pusermessage)
//   {
//
//      return ::error_wrong_type;
//
//   }
//
//   return ::success;
//
//}

//
//template < typename BASE_TYPE >
//inline void __defer_construct(::pointer<BASE_TYPE>& pusermessage)
//{
//
//   ::e_status estatus = ::success_none;
//
//   if(!pusermessage)
//   {
//
//      estatus = __construct(pusermessage);
//
//   }
//
//   return estatus;
//
//}


//template < typename BASE_TYPE >
//inline void __id_construct(::pointer<BASE_TYPE>& pusermessage, const ::atom & atom)
//{
//
//   auto pfactory = factory_item(atom);
//
//   if (!pfactory)
//   {
//
//      ::release(pusermessage);
//
//      return ::error_no_factory;
//
//   }
//
//   auto ptypeNew = pfactory->call_new();
//
//   if (!ptypeNew)
//   {
//
//      ::release(pusermessage);
//
//      return ::error_no_memory;
//
//   }
//
//   pusermessage = ptypeNew;
//
//   if (!pusermessage)
//   {
//
//      return ::error_wrong_type;
//
//   }
//
//   return ::success;
//
//}


//template < typename BASE_TYPE >
//inline void __defer_id_construct(::pointer<BASE_TYPE>& pusermessage, const ::atom & atom) { return !pusermessage ? __construct(pusermessage, atom) : ::success; }


//template < typename TYPE >
//inline void __construct_new(::pointer<TYPE>& ptype)
//{
//
//   ptype = __new(TYPE());
//
//   if (!ptype)
//   {
//
//      return ::error_no_memory;
//
//   }
//
//   return ::success;
//
//}
//
//
//template < typename TYPE >
//inline void __defer_construct_new(::pointer<TYPE>& ptype)
//{
//
//   return !ptype ? __construct_new(ptype) : void(::success);
//
//}
//


namespace factory
{




   //   inline ::pointer<::factory::factory_item_interface>& factory::get_factory_item_from(const ::atom& atom, const ::atom& atomSource)
   //   {
   //
   //      critical_section_lock cs(::factory_critical_section());
   //
   //      return (*get_factory(atomSource))[atom];
   //
   //   }
   //
   //


   //   inline ::factory::factory_item_interface* factory::get_factory_item_from(const ::atom& atom, const ::atom & atomSource) const
   //   {
   //
   //      critical_section_lock cs(::factory_critical_section());
   //
   //      auto p = m_mapFactory.plookup(atomSource);
   //
   //      if (!p)
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      auto p1 = p->m_element2.plookup(atomSource);
   //
   //      if (!p1)
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      return p1->m_element2;
   //
   //   }





   //   template < typename BASE_TYPE >
   //   inline ::pointer<::factory::factory_item_interface>& factory::get_factory_item_from(const ::atom & atomSource)
   //   {
   //
   //      string strTypename(typeid(BASE_TYPE).name());
   //
   //      strTypename = ::demangle(strTypename);
   //
   //      return get_factory_item_from(strTypename, atomSource);
   //
   //   }
   //
   //


} // namespace factory



//#include "factory.h"

#ifndef WINDOWS


#include <cxxabi.h>


thread_local char * t_pszDemangle;
thread_local size_t t_sizeDemangle;
//extern critical_section * g_pcsDemangle;


bool demangle (string & str, const scoped_string & strType)
{

   //critical_section_lock cs(g_pcsDemangle);

   int status = -4;

   t_pszDemangle = abi::__cxa_demangle(pszType, t_pszDemangle, &t_sizeDemangle, &status);

   if (status == 0)
   {

      str = t_pszDemangle;

      return true;

   }

   return false;

}


//bool demangle (string & str)
//{
//
//   return str, str.c_str();
//
//}


#endif


namespace factory
{



   ::pointer < ::particle > factory::create(const ::string & strType)
   {

      //auto psystem = acmesystem();

      //synchronous_lock synchronouslock(&psystem->m_pmutexLibrary);

      //::matter* p = nullptr;

      ////if (get_library() != nullptr)
      ////{

      ////   p = get_library()->new_object(pszClass);

      ////}
      ////else
      //{

      //   p = new_object(pszClass);

      //}

      //auto pparticle = ::move_transfer(p);

      //if (!pparticle)
      //{

      //   return nullptr;

      //}

      //return pparticle;

      auto pfactoryinterface = get_factory_item(strType);

      //if (!pfactoryinterface)
      //{

      //   return error_no_factory;

      //}

      return pfactoryinterface->create_particle();

   }


   bool factory::has_type(const ::string & strType) const
   {

      //auto psystem = acmesystem();

      //synchronous_lock synchronouslock(&psystem->m_pmutexLibrary);

      //if (get_library() == nullptr)
      //{

      //   return false;

      //}

      return get_factory_item(strType) != nullptr;

   }


} // namespace factory



