#pragma once


namespace factory
{


   inline __pointer(factory_item_interface) & get_factory_item(const ::id & id)
   {

      critical_section_lock cs(get_factory_critical_section());

      return (*get_factory())[id];

   }


   inline void set_factory(const ::id & id, const __pointer(factory_item_interface) & pfactory)
   {

      critical_section_lock cs(get_factory_critical_section());

      get_factory()->set_at(id, pfactory);

   }


   template < typename TYPE, typename BASE >
   inline void add_factory_item(const ::id & id)
   {

      set_factory(id, __new(factory_item < TYPE, BASE >()));

   }


   //template < typename TYPE >
   //inline stream & load_object(stream & stream, __pointer(TYPE) & p)
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

   //      auto id = stream.text_to_factory_id(strText);

   //      if (p && id == __type_name(p))
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
   //         else if (__type_name(p)) != id.to_string()
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
//inline __pointer(BASE_TYPE) __create()
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
//   __pointer(::matter) ptypeNew = pfactory->call_new();
//
//   if (!ptypeNew)
//   {
//
//      return nullptr;
//
//   }
//
//   __pointer(BASE_TYPE) pusermessage = ptypeNew;
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
//inline __pointer(BASE_TYPE) __create(::object * pobject)
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
//inline __pointer(BASE_TYPE) __id_create(const ::id & id)
//{
//
//   auto pfactory = ::factory::get_factory_item(id);
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
//   __pointer(BASE_TYPE) pusermessage = ptypeNew;
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
//inline __pointer(TYPE) __create_new()
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
//inline __pointer(TYPE) __create_new(const TYPE & t)
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
//inline __pointer(TYPE) __create_new(::object * pobject)
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

// __compose __composite


// template < typename OBJECT, typename BASE_TYPE >
// inline void __compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite)
// {

//    //if (((uptr)&pcomposite) < (uptr)pobject || ((uptr)&pcomposite) >= ((uptr)pobject) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//    //{

//    //   __throw(::status_exception(error_composite_not_composer_member));

//    //}

//    return pobject->__compose(pcomposite);

// }


// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void __compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite, const __pointer(SOURCE) & psource)
// {

//    return __compose(pobject, pcomposite, psource.m_p);

// }


// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void __compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite, const ::member < SOURCE > & psource)
// {

//    return __compose(pobject, pcomposite, psource.operator SOURCE * ());

// }


// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void __compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite, const SOURCE * psource)
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
// //      __throw(::status_exception(error_composite_not_composer_member));
// //
// //   }

//    return pobject->__compose(pcomposite, psource);

// }


// template < typename OBJECT, typename BASE_TYPE >
// inline void __id_compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite, const ::id & id)
// {

//    //if (((uptr)&pcomposite) < (uptr)pobject || ((uptr)&pcomposite) >= ((uptr)pobject) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//    //{

//    //   __throw(::status_exception(error_composite_not_composer_member));

//    //}

//    return pobject->__id_compose(pcomposite, id);

// }


// template < typename OBJECT, typename BASE_TYPE >
// inline void __id_compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite, const ::type & type)
// {

//    return pobject->__id_compose(pcomposite, (id) type);

// }


// template < typename OBJECT, typename TYPE >
// inline void __raw_compose_new(OBJECT && pobject, __composite(TYPE) & pcomposite)
// {

//    return pobject->__raw_compose_new(pcomposite);

// }


// template < typename OBJECT, typename TYPE >
// inline void __compose_new(OBJECT && pobject, __composite(TYPE) & pcomposite)
// {

//    return pobject->__compose_new(pcomposite);


// }


// template < typename OBJECT, typename BASE_TYPE >
// inline void __defer_compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite) { return !pcomposite ? __compose(pobject, pcomposite) : ::success; }

// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void __defer_compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite, const SOURCE * psource) { return !pcomposite ? __compose(pobject, pcomposite, psource) : ::success; }

// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void __defer_compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite, const __pointer(SOURCE) & psource) { return !pcomposite ? __compose(pobject, pcomposite, psource) : ::success; }

// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline void __defer_compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite, const ::member < SOURCE > & psource) { return !pcomposite ? __compose(pobject, pcomposite, psource) : ::success; }

// template < typename OBJECT, typename BASE_TYPE >
// inline void __defer_id_compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite, const ::id & id) { return !pcomposite ? __id_compose(pobject, pcomposite) : ::success; }

// //template < typename OBJECT, typename BASE_TYPE >
// //inline void __defer_id_compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite, const ::type & type)  { return !pcomposite ? __compose(pobject, pcomposite) : ::success; }

// template < typename OBJECT, typename BASE_TYPE >
// inline void __defer_compose_new(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite) { return !pcomposite ? __compose_new(pobject, pcomposite) : ::success; }


// __compose __reference


//
//template < typename OBJECT, typename BASE_TYPE >
//inline void __refer(OBJECT && pobject, __reference(BASE_TYPE) & preference)
//{
//
//   if (((uptr)&preference) < (uptr)pobject || ((uptr)&preference) >= ((uptr)pobject) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//   {
//
//      __throw(::status_exception(error_composite_not_composer_member));
//
//   }
//
//   return pobject->__internal_onwership(preference);
//
//}

//
//template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//inline void __refer(OBJECT && pobject, __reference(BASE_TYPE) & preference, const __pointer(SOURCE) & psource)
//{
//
//   return __refer(pobject, preference, psource.m_p);
//
//}
//
//
//template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//inline void __refer(OBJECT && pobject, __reference(BASE_TYPE) & preference, const ::primitive::member < SOURCE > & psource)
//{
//
//   return __refer(pobject, preference, psource.operator SOURCE * ());
//
//}
//
//
//template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//inline void __refer(OBJECT && pobject, __reference(BASE_TYPE) & preference, const SOURCE * psource)
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
////      __throw(::status_exception(error_composite_not_composer_member));
////
////   }
//
//   return pobject->add_reference(preference, psource);
//
//}


//template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//inline void __defer_refer(OBJECT && pobject, __reference(BASE_TYPE) & preference, const SOURCE * psource) {}
//
//template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//inline void __defer_refer(OBJECT && pobject, __reference(BASE_TYPE) & preference, const __pointer(SOURCE) & psource) {}
//
//template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//inline void __defer_refer(OBJECT && pobject, __reference(BASE_TYPE) & preference, const ::member < SOURCE > & psource) {}


//
//template < typename OBJECT, typename BASE_TYPE >
//inline void __id_refer(OBJECT && pobject, __reference(BASE_TYPE) & preference, const ::id & id)
//{
//
//   if (((uptr)&preference) < (uptr)pobject || ((uptr)&preference) >= ((uptr)pobject) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//   {
//
//      __throw(::status_exception(error_composite_not_composer_member));
//
//   }
//
//   return pobject->__id_compose(preference, id);
//
//}


//template < typename OBJECT, typename BASE_TYPE >
//inline void __id_compose(OBJECT && pobject, __reference(BASE_TYPE) & preference, const ::type & type)
//{
//
//   if (((uptr)&preference) < (uptr)pobject || ((uptr)&preference) >= ((uptr)pobject) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//   {
//
//      __throw(::status_exception(error_composite_not_composer_member));
//
//   }
//
//   return pobject->__id_compose(preference, (id)type);
//
//}


//template < typename OBJECT, typename BASE_TYPE >
//inline void __compose_new(OBJECT && pobject, __reference(BASE_TYPE) & preference)
//{
//
//   if (((uptr)&preference) < (uptr)pobject || ((uptr)&preference) >= ((uptr)pobject) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//   {
//
//      __throw(::status_exception(error_composite_not_composer_member));
//
//   }
//
//   return pobject->__compose_new(preference);
//
//}


// __construct
//
//
//template < typename BASE_TYPE >
//inline void __construct(__pointer(BASE_TYPE) & pusermessage)
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
//inline void __defer_construct(__pointer(BASE_TYPE) & pusermessage)
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
//inline void __id_construct(__pointer(BASE_TYPE) & pusermessage, const ::id & id)
//{
//
//   auto pfactory = ::factory::get_factory_item(id);
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
//inline void __defer_id_construct(__pointer(BASE_TYPE) & pusermessage, const ::id & id) { return !pusermessage ? __construct(pusermessage, id) : ::success; }


//template < typename TYPE >
//inline void __construct_new(__pointer(TYPE) & ptype)
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
//inline void __defer_construct_new(__pointer(TYPE) & ptype)
//{
//
//   return !ptype ? __construct_new(ptype) : void(::success);
//
//}
//


namespace factory
{


   inline __pointer(::factory::factory_item_interface)& factory::get_factory_item(const ::id& id)
   {

      critical_section_lock cs(::factory::get_factory_critical_section());


      return (*this)[id];

   }


   inline ::factory::factory_item_interface * factory::get_factory_item(const ::id& id) const
   {

      critical_section_lock cs(::factory::get_factory_critical_section());

      auto p = this->plookup(id);

      if (!p)
      {

         return nullptr;

      }

      return p->m_element2;

   }


   template < typename BASE_TYPE >
   inline __pointer(::factory::factory_item_interface)& factory::get_factory_item()
   {

      string strTypename(typeid(BASE_TYPE).name());

      strTypename = ::demangle(strTypename);

      return get_factory_item(strTypename);

   }


   template < typename BASE_TYPE >
   inline __pointer(BASE_TYPE) factory::create()
   {

      auto pfactoryinterface = get_factory_item < BASE_TYPE >();

      if (!pfactoryinterface)
      {

         throw_status(error_no_factory);

      }

      return pfactoryinterface->create_element();

   }


   template < typename TYPE, typename BASE_TYPE>
   inline __pointer(::factory::factory_item_base < BASE_TYPE >) factory::add_factory_item()
   {

      critical_section_lock lock(::factory::get_factory_critical_section());

      auto pfactory = __new(::factory::factory_item< TYPE, BASE_TYPE >());

      get_factory_item < BASE_TYPE >() = pfactory;

      return pfactory;

   }


   template < typename BASE_TYPE >
   inline void factory::__compose(::object* pobjectComposer, __composite(BASE_TYPE)& pcomposite)
   {

      if (!pcomposite)
      {

         auto& pfactoryitem = get_factory_item < BASE_TYPE >();

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
         pobjectComposer->__compose(pcomposite, pelement);

         //if (!pcomposite)
         //{

         //   return estatus;

         //}

      }

      //return ::success;

   }


   template < typename BASE_TYPE >
   inline void factory::__raw_compose(::object* pobjectComposer, __composite(BASE_TYPE)& pcomposite)
   {

      if (!pcomposite)
      {

         auto& pfactoryitem = get_factory_item < BASE_TYPE >();

         if (!pfactoryitem)
         {

            return ::error_no_factory;

         }

         auto pelement = pfactoryitem->create_element();

         if (!pelement)
         {

            return ::error_no_memory;

         }

         auto estatus = pobjectComposer->__raw_compose(pcomposite, pelement);

         if (!estatus)
         {

            return estatus;

         }

      }

      return ::success;

   }



} // namespace factory



