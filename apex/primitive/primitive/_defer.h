#pragma once

#ifdef new
#undef new
#endif

#define new ACME_NEW




template < typename TYPE, typename BASE_TYPE>
inline __pointer(::factory::factory_base < BASE_TYPE >) create_factory(const ::id & id)
{

   cslock lock(::factory::g_pcsFactory);

   auto pfactory = __new(::factory::factory< TYPE, BASE_TYPE >());

   ::factory::g_pfactorymap->set_at(id, pfactory);

   return pfactory;

}


template < typename TYPE, typename BASE_TYPE>
inline __pointer(::factory::factory_base < BASE_TYPE >) create_factory()
{

   cslock lock(::factory::g_pcsFactory);

   auto pfactory = __new(::factory::factory< TYPE, BASE_TYPE >());

   ::factory::get_factory < BASE_TYPE >() = pfactory;

   return pfactory;

}




template < typename TYPE1, typename TYPE2 >
inline void __dynamic_cast(TYPE1*& ptype1, const __pointer(TYPE2)& ptype2)
{

   ptype1 = ptype2.template cast < TYPE1 >().m_p;

}


