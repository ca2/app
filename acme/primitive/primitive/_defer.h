#pragma once

#ifdef memory_new

#endif

//#define memory_new ACME_NEW

//
//namespace factory
//{
//
//
//   CLASS_DECL_ACME critical_section * ::factory_critical_section();
//
//
//   template < typename TYPE, typename BASE_TYPE>
//   inline pointer< ::factory::factory_item_base < BASE_TYPE > > add_factory_item(const ::atom & atom)
//   {
//
//      critical_section_lock lock(::factory_critical_section());
//
//      auto pfactory = __new(::factory::factory_item< TYPE, BASE_TYPE >());
//
//      ::factory::get_factory()->set_at(atom, pfactory);
//
//      return pfactory;
//
//   }
//
//
//   CLASS_DECL_ACME ::factory::factory * loading_library_factory();
//
//
//   template < typename TYPE, typename BASE_TYPE>
//   inline pointer< ::factory::factory_item_base < BASE_TYPE > > _add_factory_item_from(const ::atom & atomSource)
//   {
//
//      critical_section_lock lock(::factory_critical_section());
//
//      auto pfactory = ::factory::loading_library_factory();
//
//      if (::is_set(pfactory))
//      {
//
//         return pfactory->add_factory_item < TYPE, BASE_TYPE >();
//
//      }
//
//      auto pfactoryitem = __new(::factory::factory_item< TYPE, BASE_TYPE >());
//
//      ::factory::get_factory_item < BASE_TYPE >(atomSource) = pfactoryitem;
//
//      return pfactoryitem;
//
//   }
//
//
//   template < typename TYPE, typename BASE_TYPE>
//   inline pointer< ::factory::factory_item_base < BASE_TYPE > > add_factory_item()
//   {
//
//      critical_section_lock lock(::factory_critical_section());
//
//      auto pfactory = __new(::factory::factory_item< TYPE, BASE_TYPE >());
//
//      ::factory::get_factory_item < BASE_TYPE >() = pfactory;
//
//      return pfactory;
//
//   }
//
//
//   template < typename TYPE, typename BASE_TYPE>
//   inline pointer< ::factory::factory_item_base < BASE_TYPE > > create_reusable_factory()
//   {
//
//      critical_section_lock lock(::factory_critical_section());
//
//      auto pfactory = __new(::factory::reusable_factory_item< TYPE, BASE_TYPE >());
//
//      ::factory::get_factory_item < BASE_TYPE >() = pfactory;
//
//      return pfactory;
//
//   }
//
//
//} // namespace factory
//


template < typename TYPE1, typename TYPE2 >
inline void __dynamic_cast(TYPE1*& ptype1, const ::pointer<TYPE2> ptype2)
{

   ptype1 = ptype2.template cast < TYPE1 >().m_p;

}


//namespace acme
//{
//
//
//   namespace property_set
//   {
//
//
//      inline string get_string(const ::property_object & object, const ::string & strKey);
//
//
//
//
//
//   } // namespace property_set
//
//
//} // namespace acme





