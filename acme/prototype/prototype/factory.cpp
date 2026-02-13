#include "framework.h"
#include "acme/exception/interface_only.h"
#include "acme/platform/simple_log.h"
#include "acme/platform/library.h"
#include "acme/platform/system.h"
#include "acme/prototype/prototype/factory.h"


namespace factory
{


   factory_item_interface::factory_item_interface()
   {

#if REFERENCING_DEBUGGING

      disable_referencing_debugging();

#endif

   }


   factory_item_interface::~factory_item_interface()
   {


   }


   string factory_item_interface::base_type_raw_name() const
   {

      throw ::interface_only();

      return {};

   }


   string factory_item_interface::base_type_name() const
   {
   
      throw ::interface_only();
      
      return {};
   
   }


   string factory_item_interface::type_raw_name() const
   {

      throw ::interface_only();

      return {};

   }


   string factory_item_interface::type_name() const
   {

      throw ::interface_only();
   
      return {};

   }


   ::pointer < ::subparticle > factory_item_interface::__call__create_particle()
   {

      throw ::interface_only();

      return {};

   }


   void factory_item_interface::return_back(::subparticle * pelement)
   {
      
      throw ::interface_only();
      
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
//       return &::acme::acme::g_pacme->factory_;
//
//    }


   factory::factory()
   {


   }



   factory::~factory()
   {


   }

#if REFERENCING_DEBUGGING



   factory * factory::__call__add_referer2(const ::reference_referer & referer) const
   {

      ::allocator::defer_push_referer(nullptr, referer);

      return (factory *)this;

   }


#endif


   void factory::merge(const ::factory::factory* pfactory)
   {

      //for (auto& pair : pfactory->m_mapByRawNamePointer)
      //{

      //this->m_mapByRawNamePointer.merge_set(pfactory->m_mapByRawNamePointer);
      this->m_mapByTypeName.merge_set(pfactory->m_mapByTypeName);
      this->m_mapByTypeIndex.merge_set(pfactory->m_mapByTypeIndex);
      this->m_mapByCustomNameId2.merge_set(pfactory->m_mapByCustomNameId2);
      this->m_mapByCustomIpairId.merge_set(pfactory->m_mapByCustomIpairId);
        //    .set_at(pair.m_element1, pair.m_element2);

      //}

      //for (auto& pair : pfactory->m_mapById)
      //{

      //   this->m_mapById.set_at(pair.m_element1, pair.m_element2);

      //}

      if (pfactory->m_plibrary)
      {

         auto plibrary = pfactory->m_plibrary;

         //::factory::factory_pointer pfactoryImplicit;
            
         plibrary->create_factory();

         auto pfactoryImplicit = plibrary->m_pfactory;

         //this->m_mapByRawNamePointer.merge_set(pfactoryImplicit->m_mapByRawNamePointer);
         this->m_mapByTypeName.merge_set(pfactoryImplicit->m_mapByTypeName);
         this->m_mapByTypeIndex.merge_set(pfactoryImplicit->m_mapByTypeIndex);
         this->m_mapByCustomNameId2.merge_set(pfactoryImplicit->m_mapByCustomNameId2);
         this->m_mapByCustomIpairId.merge_set(pfactoryImplicit->m_mapByCustomIpairId);

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


   void factory::terminate()
   {

      critical_section_lock lock(&m_criticalsection);

      m_mapByTypeName.erase_all();

      m_mapByTypeIndex.erase_all();

      m_mapByCustomNameId2.erase_all();

      m_mapByCustomIpairId.erase_all();

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

      ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(ptype);

   }
   catch(...)
   {

      return false;

   }

   return true;

}


//CLASS_DECL_ACME ::pointer<alloc_interface>& get_factory_item2(const ::scoped_string & scopedstrName)
//{
//
//   string_array_base stra;
//
//   stra.explode("::", strName);
//
//   string strLibrary;
//
//   strLibrary = stra.implode("_");
//
//   auto plibrary = system()->get_library(strLibrary);
//
//   plibrary->add_factory_item();
//
//   auto & pfactory = get_factory_item(strName);
//
//   if (!pfactory)
//   {
//
//      informationf("plibrary->add_factory_item()? : Library \"%s\" didn't register any relevant factory_item for type name \"%s\"?", strLibrary.c_str(), strName.c_str());
//
//   }
//
//
//   return pfactory;
//
//}





//#ifdef _DEBUG
//#include "acme/inline/factory_item.cpp"
//#endif








//
//template < typename BASE_TYPE >
//inline ::pointer<BASE_TYPE>øcreate()
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
//inline ::pointer<BASE_TYPE>øcreate(::particle * pparticle)
//{
//
//   auto p = øcreate < BASE_TYPE >();
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
//inline ::pointer<BASE_TYPE>øcreate_by_type(const ::atom & atom)
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
//inline ::pointer<TYPE>øcreate_new()
//{
//
//   auto ptype = øallocate TYPE();
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
//inline ::pointer<TYPE>øcreate_new(const TYPE & t)
//{
//
//   auto ptype = øallocate TYPE(t);
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
//inline ::pointer<TYPE>øcreate_new(::particle * pparticle)
//{
//
//   auto ptype = øcreate_new< TYPE > ();
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

// øconstruct __composite


// template < typename OBJECT, typename BASE_TYPE >
// inline void øconstruct(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite)
// {

//    //if (((uptr)&pcomposite) < (uptr)pparticle || ((uptr)&pcomposite) >= ((uptr)pparticle) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//    //{

//    //   throw ::exception(::status_exception(error_composite_not_composer_member));

//    //}

//    return pparticle->øconstruct(pcomposite);

// }


// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void øconstruct(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite, const ::pointer<SOURCE> psource)
// {

//    return øconstruct(pparticle, pcomposite, psource.m_p);

// }


// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void øconstruct(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite, const ::member < SOURCE > & psource)
// {

//    return øconstruct(pparticle, pcomposite, psource.operator SOURCE * ());

// }


// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void øconstruct(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite, const SOURCE * psource)
// {
// //
// //#ifdef _DEBUG
// //
// //   auto size = sizeof(typename ::raw_type < OBJECT>::RAW_TYPE);
// //
// //   const ::scoped_string & scopedstr = typeid(typename ::raw_type < OBJECT>::RAW_TYPE).name();
// //
// //#endif
// //
// //   if (((uptr)&pcomposite) < (uptr)pparticle || ((uptr)&pcomposite) >= ((uptr)pparticle) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
// //   {
// //
// //      throw ::exception(::status_exception(error_composite_not_composer_member));
// //
// //   }

//    return pparticle->øconstruct(pcomposite, psource);

// }


// template < typename OBJECT, typename BASE_TYPE >
// inline void øconstruct_by_custom_id(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite, const ::atom & atom)
// {

//    //if (((uptr)&pcomposite) < (uptr)pparticle || ((uptr)&pcomposite) >= ((uptr)pparticle) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//    //{

//    //   throw ::exception(::status_exception(error_composite_not_composer_member));

//    //}

//    return pparticle->øconstruct_by_custom_id(pcomposite, atom);

// }


// template < typename OBJECT, typename BASE_TYPE >
// inline void øconstruct_by_id(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite, const ::platform::type & type)
// {

//    return pparticle->øconstruct_by_custom_id(pcomposite, (atom) type);

// }


// template < typename OBJECT, typename TYPE >
// inline void __raw_construct_new(OBJECT && pparticle, ::pointer<TYPE>& pcomposite)
// {

//    return pparticle->__raw_construct_new(pcomposite);

// }


// template < typename OBJECT, typename TYPE >
// inline void øconstruct_new(OBJECT && pparticle, ::pointer<TYPE>& pcomposite)
// {

//    return pparticle->øconstruct_new(pcomposite);


// }


// template < typename OBJECT, typename BASE_TYPE >
// inline void ødefer_construct(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite) { return !pcomposite ? øconstruct(pparticle, pcomposite) : ::success; }

// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void ødefer_construct(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite, const SOURCE * psource) { return !pcomposite ? øconstruct(pparticle, pcomposite, psource) : ::success; }

// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void ødefer_construct(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite, const ::pointer<SOURCE> psource) { return !pcomposite ? øconstruct(pparticle, pcomposite, psource) : ::success; }

// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void ødefer_construct(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite, const ::member < SOURCE > & psource) { return !pcomposite ? øconstruct(pparticle, pcomposite, psource) : ::success; }

// template < typename OBJECT, typename BASE_TYPE >
// inline void __defer_id_compose(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite, const ::atom & atom) { return !pcomposite ? øconstruct_by_custom_id(pparticle, pcomposite) : ::success; }

// //template < typename OBJECT, typename BASE_TYPE >
// //inline void __defer_id_compose(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite, const ::platform::type & type)  { return !pcomposite ? øconstruct(pparticle, pcomposite) : ::success; }

// template < typename OBJECT, typename BASE_TYPE >
// inline void ødefer_construct_new(OBJECT && pparticle, ::pointer<BASE_TYPE>& pcomposite) { return !pcomposite ? øconstruct_new(pparticle, pcomposite) : ::success; }


// øconstruct __reference


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
//inline void __refer(OBJECT && pparticle, ::pointer<BASE_TYPE>& preference, const ::prototype::member < SOURCE > & psource)
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
////   const ::scoped_string & scopedstr = typeid(typename ::raw_type < OBJECT>::RAW_TYPE).name();
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
//   return pparticle->øconstruct_by_custom_id(preference, atom);
//
//}


//template < typename OBJECT, typename BASE_TYPE >
//inline void øconstruct_by_id(OBJECT && pparticle, ::pointer<BASE_TYPE>& preference, const ::platform::type & type)
//{
//
//   if (((uptr)&preference) < (uptr)pparticle || ((uptr)&preference) >= ((uptr)pparticle) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//   {
//
//      throw ::exception(::status_exception(error_composite_not_composer_member));
//
//   }
//
//   return pparticle->øconstruct_by_custom_id(preference, (atom)type);
//
//}


//template < typename OBJECT, typename BASE_TYPE >
//inline void øconstruct_new(OBJECT && pparticle, ::pointer<BASE_TYPE>& preference)
//{
//
//   if (((uptr)&preference) < (uptr)pparticle || ((uptr)&preference) >= ((uptr)pparticle) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//   {
//
//      throw ::exception(::status_exception(error_composite_not_composer_member));
//
//   }
//
//   return pparticle->øconstruct_new(preference);
//
//}


// øconstruct
//
//
//template < typename BASE_TYPE >
//inline void øconstruct(::pointer<BASE_TYPE>& pusermessage)
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
//inline void ødefer_construct(::pointer<BASE_TYPE>& pusermessage)
//{
//
//   ::e_status estatus = ::success_none;
//
//   if(!pusermessage)
//   {
//
//      estatus = øconstruct(pusermessage);
//
//   }
//
//   return estatus;
//
//}


//template < typename BASE_TYPE >
//inline void øconstruct_by_custom_id(::pointer<BASE_TYPE>& pusermessage, const ::atom & atom)
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
//inline void __defer_id_construct(::pointer<BASE_TYPE>& pusermessage, const ::atom & atom) { return !pusermessage ? øconstruct(pusermessage, atom) : ::success; }


//template < typename TYPE >
//inline void øconstruct_new(::pointer<TYPE>& ptype)
//{
//
//   ptype = øallocate TYPE();
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
//inline void ødefer_construct_new(::pointer<TYPE>& ptype)
//{
//
//   return !ptype ? øconstruct_new(ptype) : void(::success);
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
   //      auto p = m_mapFactory.find(atomSource);
   //
   //      if (!p)
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      auto p1 = p->m_element2.find(atomSource);
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
   //      string strTypename(::type<BASE_TYPE>().name());
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


bool demangle (string & str, const_char_pointer pszType)
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


   // ::particle_pointer factory::__call__create_by_type_index(const ::std::type_index & typeindex, ::particle * pparticle)
   // {
   //
   //    //auto psystem = system();
   //
   //    //synchronous_lock synchronouslock(&psystem->m_pmutexLibrary);
   //
   //    //::matter* p = nullptr;
   //
   //    ////if (get_library() != nullptr)
   //    ////{
   //
   //    ////   p = get_library()->new_object(scopedstrClass);
   //
   //    ////}
   //    ////else
   //    //{
   //
   //    //   p = new_object(scopedstrClass);
   //
   //    //}
   //
   //    //auto pparticle = ::pointer_transfer(p);
   //
   //    //if (!pparticle)
   //    //{
   //
   //    //   return nullptr;
   //
   //    //}
   //
   //    //return pparticle;
   //
   //    auto pfactoryinterface = _get_factory_item_by_type_index(typeindex);
   //
   //    //if (!pfactoryinterface)
   //    //{
   //
   //    //   return error_no_factory;
   //
   //    //}
   //
   //    return pfactoryinterface->__call__create_particle();
   //
   // }


   ::particle_pointer factory::__call__create_by_custom_id(const ::type_custom_id & typecustomid, ::particle* pparticle)
   {

      //auto psystem = system();

      //synchronous_lock synchronouslock(&psystem->m_pmutexLibrary);

      //::matter* p = nullptr;

      ////if (get_library() != nullptr)
      ////{

      ////   p = get_library()->new_object(scopedstrClass);

      ////}
      ////else
      //{

      //   p = new_object(scopedstrClass);

      //}

      //auto pparticle = ::pointer_transfer(p);

      //if (!pparticle)
      //{

      //   return nullptr;

      //}

      //return pparticle;

      auto pfactoryinterface = _find_factory_item_by_custom_id(typecustomid);

      //if (!pfactoryinterface)
      //{

      //   return error_no_factory;

      //}

      return pfactoryinterface->__call__create_particle();

   }





   // bool factory::has_by_type_index(const ::std::type_index & typeindex) const
   // {
   //
   //    return has_factory_item_by_type_index(typeindex);
   //
   // }
   //
   //
   //
   // bool factory::has_by_custom_id(const ::type_custom_id & typecustomid) const
   // {
   //
   //    return has_factory_item_by_custom_id(typecustomid);
   //
   // }


   ::factory::factory_item_interface* factory::_find_factory_item_by_type_index(const ::std::type_index & typeindex) const
   {

      critical_section_lock cs(&((factory*)this)->m_criticalsection);

      {

         auto p = this->m_mapByTypeIndex.find(typeindex);

         if (p)
         {

            auto pfactoryitem = p->payload().m_p;

            if (::is_set(pfactoryitem))
            {

               return pfactoryitem;

            }

         }

      }

      // error() << "factory::get_factory_item FAILED!! the following atom wasn't found by raw name pointer and text: \"" << typeindex << "\"";
      //
      return nullptr;

   }


   ::factory::factory_item_interface* factory::_find_factory_item_by_type_name(const ::scoped_string & scopedstrTypeName) const
   {

      critical_section_lock cs(&((factory*)this)->m_criticalsection);

      {

         auto p = this->m_mapByTypeName.find(scopedstrTypeName);

         if (p)
         {

            auto pfactoryitem =  p->payload().m_p;

            if (::is_set(pfactoryitem))
            {

               return pfactoryitem;

            }

         }

      }

      //error() << "factory::get_factory_item FAILED!! the following atom wasn't found by raw name pointer and text: \"" << typeindex << "\"";

      return nullptr;

   }


   factory_item_interface * factory::_find_factory_item_by_type_id(const ::type_id & type_id) const
   {

      auto typeindex = type_id.m_typeindex;

      if (::is_type_index_set(typeindex))
      {

         auto pfactoryitem = _find_factory_item_by_type_index(typeindex);

         if (pfactoryitem)
         {

            return pfactoryitem;

         }

      }

      auto strTypeName = type_id.m_strTypeName;

      if (strTypeName.has_character())
      {

         auto pfactoryitem = _find_factory_item_by_type_name(strTypeName);

         if (pfactoryitem)
         {

            return pfactoryitem;

         }

      }

      //error() << "factory::get_factory_item FAILED!! the following atom wasn't found by raw name pointer and text: \"" << typeindex << "\"";

      return nullptr;

   }


   // factory_item_interface * factory::get_factory_item_by_type_id(const ::type_id & type_id)
   // {
   //
   //    if (type_id.is_empty())
   //    {
   //
   //       throw ::exception(error_bad_argument);
   //
   //    }
   //
   //    auto pfactoryitem = _get_factory_item_by_type_id(type_id);
   //
   //    if (::is_set(pfactoryitem))
   //    {
   //
   //       return pfactoryitem;
   //
   //    }
   //
   //    ::string strError;
   //
   //    strError.format("factory::get_factory_item_by_type_id FAILED!! "
   //       "the following type_id wasn't found by "
   //       "type index or type name (raw name): \"{}\" (\"{}\").",
   //       type_id.m_strTypeName, type_id.m_strRawTypeName);
   //
   //    throw ::exception(error_not_found, strError);
   //
   //    return nullptr;
   //
   // }

   factory_item_interface * factory::_find_factory_item(const ::platform::type & type) const
   {

      if (type.is_empty())
      {

         throw ::exception(error_bad_argument);

      }

      if (type.m_typeid.is_set())
      {

         auto pfactoryitem = _find_factory_item_by_type_id(type.m_typeid);

         if (::is_set(pfactoryitem))
         {

            return pfactoryitem;

         }

      }

      if (type.m_customid.is_set())
      {

         auto pfactoryitem = _find_factory_item_by_custom_id(type.m_customid);

         if (::is_set(pfactoryitem))
         {

            return pfactoryitem;

         }

      }

      return nullptr;

   }


   bool factory::has_factory_item(const ::platform::type & type) const
   {

      auto pfactoryitem = _find_factory_item(type);

      if (::is_null(pfactoryitem))
      {

         return false;

      }

      return true;

   }



   ::factory::factory_item_interface * factory::_find_factory_item_by_custom_id(const ::type_custom_id & typecustomid) const
   {

      critical_section_lock cs(&((factory*)this)->m_criticalsection);

      auto ipairId = typecustomid.m_ipairId;

      if (ipairId.is_set())
      {

         auto iterator = this->m_mapByCustomIpairId.find(ipairId);

         if (iterator)
         {

            auto pfactoryitem = iterator->payload();

            if (::is_set(pfactoryitem))
            {

               return pfactoryitem;

            }

         }

      }

      auto strNameId = typecustomid.m_strNameId;

      if (strNameId.has_character())
      {

         auto iterator = this->m_mapByCustomNameId2.find(strNameId);

         if (iterator)
         {

            auto pfactoryitem = iterator->payload();

            if (::is_set(pfactoryitem))
            {

               return pfactoryitem;

            }

         }

      }

      warning("factory::get_factory_item_by_custom_id FAILED!! ipair, name: ({},{}), \"{}\"",
         typecustomid.m_ipairId.normal1(),
         typecustomid.m_ipairId.normal2(),
         typecustomid.m_strNameId);

      return nullptr;

   }


   ::factory::factory_item_interface* factory::_find_factory_item_by_ipair(const ::type_iptr_pair & ipairId) const
   {

      critical_section_lock cs(&((factory*)this)->m_criticalsection);

      if (ipairId.is_set())
      {

         auto iterator = this->m_mapByCustomIpairId.find(ipairId);

         if (iterator)
         {

            auto pfactoryitem = iterator->payload();

            if (::is_set(pfactoryitem))
            {

               return pfactoryitem;

            }

         }

      }

      return nullptr;

   }


   bool factory::has_factory_item_by_type_index(const ::std::type_index & typeindex) const
   {

      critical_section_lock cs(&((factory*)this)->m_criticalsection);

      {

         auto p = this->m_mapByTypeIndex.find(typeindex);

         if (p && p->payload())
         {

            return true;

         }

      }

      //{

      //   auto p = this->m_mapByTypeIndex.find(pszRawName);

      //   if (p && p->payload())
      //   {

      //      return true;

      //   }

      //}

      return false;

   }


   bool factory::has_factory_item_by_custom_id(const ::type_custom_id & typecustomid) const
   {

      auto pfactoryitem = this->_find_factory_item_by_custom_id(typecustomid);

      if (::is_null(pfactoryitem))
      {

         return false;

      }

      return true;

   }


   //::factory::factory_item_interface * factory::get_factory_item_by_type_index(const ::std::type_index & typeindex) const
   //{

   //   critical_section_lock cs(&m_criticalsection);

   //   auto& pfactoryiteminterface = this->m_mapByTypeIndex.get(pszRawName)->element2();

   //   if (!pfactoryiteminterface)
   //   {

   //      //warning() << "factory::get_factory_item (2) : \"" << atom.as_string() << "\"";

   //   }

   //   return pfactoryiteminterface;

   //}



   //::pointer<::factory::factory_item_interface> & factory::get_factory_item_by_custom_id(const ::atom & atom)
   //{

   //   critical_section_lock cs(&m_criticalsection);

   //   auto & pfactoryiteminterface = this->m_mapById.get(atom)->element2();

   //   if(!pfactoryiteminterface)
   //   {

   //      //warning() << "factory::get_factory_item (2) : \"" << atom.as_string() << "\"";

   //   }

   //   return pfactoryiteminterface;

   //}


   ////inline ::pointer<factory_item_interface> & factory::get_factory_item(const ::atom & atom)
   ////{

   ////   critical_section_lock cs(&m_criticalsection);

   ////   return (*get_factory())[atom];

   ////}



   void factory::set_factory_item_by_type(const ::platform::type & type, const ::pointer<::factory::factory_item_interface> & pfactoryitem)
   {

      if (type.is_empty())
      {

         throw ::exception(error_bad_argument, "type is empty");

      }

      if (type.m_typeid.is_set())
      {

         set_factory_item_by_type(type.m_typeid, pfactoryitem);

      }

      if (type.m_customid.is_set())
      {

         set_factory_item_by_custom_id(type.m_customid, pfactoryitem);

      }

   }


   void factory::set_factory_item_by_custom_id(const ::type_custom_id & typecustomid, const ::pointer<::factory::factory_item_interface> & pfactoryitem)
   {

      if (typecustomid.is_empty())
      {

         throw ::exception(error_bad_argument, "type custom id is all empty");

      }

      critical_section_lock lock(&m_criticalsection);

      if (typecustomid.m_strNameId.has_character())
      {

         m_mapByCustomNameId2[typecustomid.m_strNameId] = pfactoryitem;

      }

      if (typecustomid.m_ipairId.is_set())
      {

         m_mapByCustomIpairId[typecustomid.m_ipairId] = pfactoryitem;

      }

   }


   // void platform::set_factory_item_by_type(const ::platform::type & type, const ::pointer<::factory::factory_item_interface> & pfactoryitem)
   // {
   //
   //    critical_section_lock cs(&m_criticalsection);
   //
   //    m_pfactory->set_factory_item_by_type(type, pfactoryitem);
   //
   //    ASSERT(::is_type_index_set(type.m_typeindex));
   //
   //    ASSERT(type.m_strTypeName.has_character());
   //
   //    m_pfactory->m_mapByTypeIndex.set_at(type.m_typeindex, pfactoryitem);
   //
   //    m_pfactory->m_mapByTypeName.set_at(type.m_strTypeName, pfactoryitem);
   //
   // }

   // factory_item_interface * get_factory_item_by_type_index(const ::std::type_index & typeindex)
   // {
   //
   //    auto pplatform = ::platform::get();
   //
   //    return pplatform->get_factory_item_by_type_index(typeindex);
   //
   // }
   //
   //
   // factory_item_interface * get_factory_item_by_custom_id(const ::atom & atom)
   // {
   //
   //    auto pplatform = ::platform::get();
   //
   //    return pplatform->get_factory_item_by_custom_id(atom);
   //
   // }
   //
   //
   // factory_item_interface * get_existing_factory_item_by_type_index(const ::std::type_index & typeindex)
   // {
   //
   //    auto pfactoryitem = get_factory_item_by_type_index(typeindex);
   //
   //    if (!pfactoryitem)
   //    {
   //
   //       throw_exception(error_no_factory, "No factory for type_index with name: \"" + ::string(typeindex.name()) + "\"");
   //
   //    }
   //
   //    return pfactoryitem;
   //
   // }
   //
   //
   // factory_item_interface * get_existing_factory_item_by_custom_id(const ::atom & atom)
   // {
   //
   //    auto pfactoryitem = get_factory_item_by_custom_id(atom);
   //
   //    if (!pfactoryitem)
   //    {
   //
   //       throw_exception(error_no_factory, "No factory for id: \"" + atom + "\"");
   //
   //    }
   //
   //    return pfactoryitem;
   //
   // }
   //
   //
   // factory_item_interface * get_factory_item_by_type_index(const ::std::type_index & typeindex, const ::atom & atomFactory)
   // {
   //
   //    auto pplatform = ::platform::get();
   //
   //    auto pfactoryitem = pplatform->get_factory_item_by_type_index(typeindex, atomFactory);
   //
   //    if (!pfactoryitem)
   //    {
   //
   //       throw_exception(error_no_factory, "No factory for type_index with name: \"" + ::string(typeindex.name()) + "\"");
   //
   //    }
   //
   //    return pfactoryitem;
   //
   // }
   //
   //
   // factory_item_interface * get_factory_item_by_custom_id(const ::atom & atom, const ::atom& atomFactory)
   // {
   //
   //    auto pplatform = ::platform::get();
   //
   //    auto pfactoryitem = pplatform->get_factory_item_by_custom_id(atom, atomFactory);
   //
   //    if (!pfactoryitem)
   //    {
   //
   //       throw_exception(error_no_factory, "No factory for id: \"" + atom.as_string() + "\"");
   //
   //    }
   //
   //    return pfactoryitem;
   //
   // }
   //

} // namespace factory



