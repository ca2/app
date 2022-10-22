#include "framework.h"
#include "acme/platform/acme.h"
#include "acme/platform/simple_log.h"
#include "acme/platform/library.h"


CLASS_DECL_ACME ::acme::system * get_system();


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

      auto & pfactory = (*::acme::acme::g_p->m_pmapFactory)[atomSource];

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






namespace factory
{


   inline ::pointer<factory_item_interface> & get_factory_item(const ::atom & atom)
   {

      critical_section_lock cs(get_factory_critical_section());

      return (*get_factory())[atom];

   }


   inline ::pointer<factory_item_interface> & get_existing_factory_item(const ::atom & atom)
   {

      auto & pfactoryitem = get_factory_item(atom);

      if (!pfactoryitem)
      {

         throw ::exception(error_no_factory, "No factory for \"" + atom + "\"");

      }

      return pfactoryitem;

   }


   inline ::pointer<factory_item_interface> & get_factory_item(const ::atom & atom, const ::atom & atomSource)
   {

      critical_section_lock cs(get_factory_critical_section());

      return (*get_factory(atomSource))[atom];

   }


   inline bool has(const ::atom & atom)
   {

      critical_section_lock cs(get_factory_critical_section());

      auto passociation = get_factory()->get_association(atom);

      if (::is_null(passociation))
      {

         return false;

      }

      if (::is_null(passociation->m_element2))
      {

         return false;

      }

      return true;

   }



   inline void set_factory(const ::atom & atom, const ::pointer<factory_item_interface> & pfactory)
   {

      critical_section_lock cs(get_factory_critical_section());

      get_factory()->set_at(atom, pfactory);

   }


   inline void set_factory_from(const ::atom & atom, const ::atom & atomSource, const ::pointer<factory_item_interface> & pfactory)
   {

      critical_section_lock cs(get_factory_critical_section());

      get_factory(atomSource)->set_at(atom, pfactory);

   }


   template < typename TYPE, typename BASE >
   inline void add_factory_item(const ::atom & atom)
   {

      set_factory(atom, __new(factory_item < TYPE, BASE >()));

   }


   //template < typename TYPE >
   //inline stream & load_object(stream & stream, ::pointer<TYPE>& p)
   //{

   //   string strText;

   //   stream >> strText;

   //   if (strText.is_empty() || strText.begins_eat_ci("factoryless://"))
   //   {

   //      if (p && __type_name(p)) == strText
   //      {

   //         ::output_debug_string("loading into existing matter of same class type (1)");

   //      }
   //      else
   //      {

   //         p.defer_create_new();

   //         if (!p)
   //         {

   //            ::output_debug_string("defer_new failed (1.1)");

   //            stream.set_fail_bit();

   //         }
   //         else if (__type_name(p)) != strText
   //         {

   //            ::output_debug_string("allocated matter type is different from streamed matter type (1.2)");

   //            stream.set_fail_bit();

   //         }

   //      }

   //   }
   //   else
   //   {

   //      auto atom = stream.text_to_factory_id(strText);

   //      if (p && atom == __type_name(p))
   //      {

   //         ::output_debug_string("loading into existing matter of same class type (2)");

   //      }
   //      else
   //      {

   //         p = stream.create_object_from_text(strText);

   //         if (!p)
   //         {

   //            ::output_debug_string("stream::alloc_object_from_text failed (2.1)");

   //         }
   //         else if (__type_name(p)) != atom.to_string()
   //         {

   //            ::output_debug_string("allocated matter type is different from streamed matter type (2.2)");

   //            stream.set_fail_bit();

   //         }

   //      }

   //   }

   //   if (!stream.fail())
   //   {

   //      if (p->has(e_object_factory))
   //      {

   //         p->read(stream);

   //      }
   //      else
   //      {

   //         stream >> *p;

   //      }

   //   }

   //   return stream;

   //}


} // namespace factory


//
//template < typename BASE_TYPE >
//inline ::pointer<BASE_TYPE>__create()
//{
//
//   auto pfactory = ::factory::get_factory_item < BASE_TYPE >();
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
//inline ::pointer<BASE_TYPE>__create(::object * pobject)
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
//   auto estatus = p->initialize(pobject);
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
//   auto pfactory = ::factory::get_factory_item(atom);
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
//inline ::pointer<TYPE>__create_new(::object * pobject)
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
//   auto estatus = ptype->initialize(pobject);
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
// inline void __construct(OBJECT && pobject, ::pointer<BASE_TYPE>& pcomposite)
// {

//    //if (((uptr)&pcomposite) < (uptr)pobject || ((uptr)&pcomposite) >= ((uptr)pobject) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//    //{

//    //   throw ::exception(::status_exception(error_composite_not_composer_member));

//    //}

//    return pobject->__construct(pcomposite);

// }


// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void __construct(OBJECT && pobject, ::pointer<BASE_TYPE>& pcomposite, const ::pointer<SOURCE> psource)
// {

//    return __construct(pobject, pcomposite, psource.m_p);

// }


// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void __construct(OBJECT && pobject, ::pointer<BASE_TYPE>& pcomposite, const ::member < SOURCE > & psource)
// {

//    return __construct(pobject, pcomposite, psource.operator SOURCE * ());

// }


// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void __construct(OBJECT && pobject, ::pointer<BASE_TYPE>& pcomposite, const SOURCE * psource)
// {
// //
// //#ifdef _DEBUG
// //
// //   auto size = sizeof(typename ::raw_type < OBJECT>::RAW_TYPE);
// //
// //   const char * psz = typeid(typename ::raw_type < OBJECT>::RAW_TYPE).name();
// //
// //#endif
// //
// //   if (((uptr)&pcomposite) < (uptr)pobject || ((uptr)&pcomposite) >= ((uptr)pobject) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
// //   {
// //
// //      throw ::exception(::status_exception(error_composite_not_composer_member));
// //
// //   }

//    return pobject->__construct(pcomposite, psource);

// }


// template < typename OBJECT, typename BASE_TYPE >
// inline void __id_construct(OBJECT && pobject, ::pointer<BASE_TYPE>& pcomposite, const ::atom & atom)
// {

//    //if (((uptr)&pcomposite) < (uptr)pobject || ((uptr)&pcomposite) >= ((uptr)pobject) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//    //{

//    //   throw ::exception(::status_exception(error_composite_not_composer_member));

//    //}

//    return pobject->__id_construct(pcomposite, atom);

// }


// template < typename OBJECT, typename BASE_TYPE >
// inline void __id_construct(OBJECT && pobject, ::pointer<BASE_TYPE>& pcomposite, const ::type & type)
// {

//    return pobject->__id_construct(pcomposite, (atom) type);

// }


// template < typename OBJECT, typename TYPE >
// inline void __raw_construct_new(OBJECT && pobject, ::pointer<TYPE>& pcomposite)
// {

//    return pobject->__raw_construct_new(pcomposite);

// }


// template < typename OBJECT, typename TYPE >
// inline void __construct_new(OBJECT && pobject, ::pointer<TYPE>& pcomposite)
// {

//    return pobject->__construct_new(pcomposite);


// }


// template < typename OBJECT, typename BASE_TYPE >
// inline void __defer_construct(OBJECT && pobject, ::pointer<BASE_TYPE>& pcomposite) { return !pcomposite ? __construct(pobject, pcomposite) : ::success; }

// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void __defer_construct(OBJECT && pobject, ::pointer<BASE_TYPE>& pcomposite, const SOURCE * psource) { return !pcomposite ? __construct(pobject, pcomposite, psource) : ::success; }

// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void __defer_construct(OBJECT && pobject, ::pointer<BASE_TYPE>& pcomposite, const ::pointer<SOURCE> psource) { return !pcomposite ? __construct(pobject, pcomposite, psource) : ::success; }

// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void __defer_construct(OBJECT && pobject, ::pointer<BASE_TYPE>& pcomposite, const ::member < SOURCE > & psource) { return !pcomposite ? __construct(pobject, pcomposite, psource) : ::success; }

// template < typename OBJECT, typename BASE_TYPE >
// inline void __defer_id_compose(OBJECT && pobject, ::pointer<BASE_TYPE>& pcomposite, const ::atom & atom) { return !pcomposite ? __id_construct(pobject, pcomposite) : ::success; }

// //template < typename OBJECT, typename BASE_TYPE >
// //inline void __defer_id_compose(OBJECT && pobject, ::pointer<BASE_TYPE>& pcomposite, const ::type & type)  { return !pcomposite ? __construct(pobject, pcomposite) : ::success; }

// template < typename OBJECT, typename BASE_TYPE >
// inline void __defer_construct_new(OBJECT && pobject, ::pointer<BASE_TYPE>& pcomposite) { return !pcomposite ? __construct_new(pobject, pcomposite) : ::success; }


// __construct __reference


//
//template < typename OBJECT, typename BASE_TYPE >
//inline void __refer(OBJECT && pobject, ::pointer<BASE_TYPE>& preference)
//{
//
//   if (((uptr)&preference) < (uptr)pobject || ((uptr)&preference) >= ((uptr)pobject) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//   {
//
//      throw ::exception(::status_exception(error_composite_not_composer_member));
//
//   }
//
//   return pobject->__internal_onwership(preference);
//
//}

//
//template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//inline void __refer(OBJECT && pobject, ::pointer<BASE_TYPE>& preference, const ::pointer<SOURCE> psource)
//{
//
//   return __refer(pobject, preference, psource.m_p);
//
//}
//
//
//template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//inline void __refer(OBJECT && pobject, ::pointer<BASE_TYPE>& preference, const ::primitive::member < SOURCE > & psource)
//{
//
//   return __refer(pobject, preference, psource.operator SOURCE * ());
//
//}
//
//
//template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//inline void __refer(OBJECT && pobject, ::pointer<BASE_TYPE>& preference, const SOURCE * psource)
//{
//
////#ifdef _DEBUG
////
////   auto size = sizeof(typename ::raw_type < OBJECT>::RAW_TYPE);
////
////   const char * psz = typeid(typename ::raw_type < OBJECT>::RAW_TYPE).name();
////
////#endif
////
////   if (((uptr)&preference) < (uptr)pobject || ((uptr)&preference) >= ((uptr)pobject) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
////   {
////
////      throw ::exception(::status_exception(error_composite_not_composer_member));
////
////   }
//
//   return pobject->add_reference(preference, psource);
//
//}


//template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//inline void __defer_refer(OBJECT && pobject, ::pointer<BASE_TYPE>& preference, const SOURCE * psource) {}
//
//template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//inline void __defer_refer(OBJECT && pobject, ::pointer<BASE_TYPE>& preference, const ::pointer<SOURCE> psource) {}
//
//template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//inline void __defer_refer(OBJECT && pobject, ::pointer<BASE_TYPE>& preference, const ::member < SOURCE > & psource) {}


//
//template < typename OBJECT, typename BASE_TYPE >
//inline void __id_refer(OBJECT && pobject, ::pointer<BASE_TYPE>& preference, const ::atom & atom)
//{
//
//   if (((uptr)&preference) < (uptr)pobject || ((uptr)&preference) >= ((uptr)pobject) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//   {
//
//      throw ::exception(::status_exception(error_composite_not_composer_member));
//
//   }
//
//   return pobject->__id_construct(preference, atom);
//
//}


//template < typename OBJECT, typename BASE_TYPE >
//inline void __id_construct(OBJECT && pobject, ::pointer<BASE_TYPE>& preference, const ::type & type)
//{
//
//   if (((uptr)&preference) < (uptr)pobject || ((uptr)&preference) >= ((uptr)pobject) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//   {
//
//      throw ::exception(::status_exception(error_composite_not_composer_member));
//
//   }
//
//   return pobject->__id_construct(preference, (atom)type);
//
//}


//template < typename OBJECT, typename BASE_TYPE >
//inline void __construct_new(OBJECT && pobject, ::pointer<BASE_TYPE>& preference)
//{
//
//   if (((uptr)&preference) < (uptr)pobject || ((uptr)&preference) >= ((uptr)pobject) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//   {
//
//      throw ::exception(::status_exception(error_composite_not_composer_member));
//
//   }
//
//   return pobject->__construct_new(preference);
//
//}


// __construct
//
//
//template < typename BASE_TYPE >
//inline void __construct(::pointer<BASE_TYPE>& pusermessage)
//{
//
//   auto & pfactory = ::factory::get_factory_item < BASE_TYPE >();
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
//   auto pfactory = ::factory::get_factory_item(atom);
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


   inline ::pointer<::factory::factory_item_interface> & factory::get_factory_item(const ::atom & atom)
   {

      critical_section_lock cs(::factory::get_factory_critical_section());


      return this->operator[](atom);

   }


   //   inline ::pointer<::factory::factory_item_interface>& factory::get_factory_item_from(const ::atom& atom, const ::atom& atomSource)
   //   {
   //
   //      critical_section_lock cs(::factory::get_factory_critical_section());
   //
   //      return (*get_factory(atomSource))[atom];
   //
   //   }
   //
   //


   inline ::factory::factory_item_interface * factory::get_factory_item(const ::atom & atom) const
   {

      critical_section_lock cs(::factory::get_factory_critical_section());

      auto p = this->plookup(atom);

      if (!p)
      {

         return nullptr;

      }

      return p->m_element2;

   }


   //   inline ::factory::factory_item_interface* factory::get_factory_item_from(const ::atom& atom, const ::atom & atomSource) const
   //   {
   //
   //      critical_section_lock cs(::factory::get_factory_critical_section());
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


   template < typename BASE_TYPE >
   inline ::pointer<::factory::factory_item_interface> & factory::get_factory_item()
   {

      string strTypename(typeid(BASE_TYPE).name());

      strTypename = ::demangle(strTypename);

      return get_factory_item(strTypename);

   }


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
   template < typename BASE_TYPE >
   inline ::pointer<BASE_TYPE>factory::create()
   {

      auto pfactoryinterface = get_factory_item < BASE_TYPE >();

      if (!pfactoryinterface)
      {

         throw ::exception(error_no_factory);

      }

      return pfactoryinterface->create_element();

   }


   template < typename TYPE, typename BASE_TYPE>
   inline pointer< ::factory::factory_item_base < BASE_TYPE > > factory::add_factory_item()
   {

      critical_section_lock lock(::factory::get_factory_critical_section());

      auto pfactory = __new(::factory::factory_item< TYPE, BASE_TYPE >());

      this->get_factory_item < BASE_TYPE >() = pfactory;

      return pfactory;

   }


   //   template < typename TYPE, typename BASE_TYPE>
   //   inline pointer< ::factory::factory_item_base < BASE_TYPE > > factory::_add_factory_item_from(const ::atom & atomSource)
   //   {
   //
   //      critical_section_lock lock(::factory::get_factory_critical_section());
   //
   //      auto pfactory = __new(::factory::factory_item< TYPE, BASE_TYPE >());
   //
   //      get_factory_item_from < BASE_TYPE >(atomSource) = pfactory;
   //
   //      return pfactory;
   //
   //   }
   //
   //


   template < typename BASE_TYPE >
   inline void factory::__construct(::object * pobjectComposer, ::pointer<BASE_TYPE> & pcomposite)
   {

      if (!pcomposite)
      {

         auto & pfactoryitem = get_factory_item < BASE_TYPE >();

         //if (!pfactoryitem)
         //{

         //   return ::error_no_factory;

         //}

         auto pelement = ::move(pfactoryitem->create_element());

         //if (!pelement)
         //{

         //   return ::error_no_memory;

         //}

         //auto estatus = 
         pobjectComposer->__construct(pcomposite, pelement);

         //if (!pcomposite)
         //{

         //   return estatus;

         //}

      }

      //return ::success;

   }


   //template < typename BASE_TYPE >
   //inline void factory::__raw_construct(::object* pobjectComposer, ::pointer<BASE_TYPE> pcomposite)
   //{

   //   if (!pcomposite)
   //   {

   //      auto& pfactoryitem = get_factory_item < BASE_TYPE >();

   //      auto pelement = pfactoryitem->create_element();

   //      pobjectComposer->__raw_construct(pcomposite, pelement);

   //   }

   //}


} // namespace factory



