#pragma once


#include "acme/prototype/collection/packset.h"


template <class TYPEA, class TYPEB, class ARRAYA, class ARRAYB  >
class spreadset
{
public:

   using PACK_SET_AB = packset < TYPEA, TYPEB, ARRAYB >;
   using PACK_SET_BA = packset < TYPEB, TYPEA, ARRAYA >;

   using ARG_TYPEA = typename PACK_SET_AB::ARG_ID_TYPE;
   using ARG_TYPEB = typename PACK_SET_BA::ARG_ID_TYPE;


   PACK_SET_AB m_packsetAB;
   PACK_SET_BA m_packsetBA;


   void spread(ARG_TYPEA a, ARG_TYPEB b);


   ARRAYB & b(ARG_TYPEA a);
   ARRAYA & a(ARG_TYPEB b);


   ::collection::count get_a_item_count();
   ::collection::count get_b_item_count();
   ::collection::count get_a_pack_count();
   ::collection::count get_b_pack_count();


   void erase_all();


};


template <class TYPEA, class TYPEB, class ARRAYA, class ARRAYB >
void spreadset <TYPEA, TYPEB, ARRAYA, ARRAYB>::
spread(ARG_TYPEA a, ARG_TYPEB b)
{
   m_packsetAB.pack(a, b);
   m_packsetBA.pack(b, a);
}

template <class TYPEA, class TYPEB, class ARRAYA, class ARRAYB >
ARRAYB & spreadset <TYPEA, TYPEB, ARRAYA, ARRAYB>::
b(ARG_TYPEA a)
{
   return m_packsetAB[a];
}


template <class TYPEA, class TYPEB, class ARRAYA, class ARRAYB >
ARRAYA & spreadset <TYPEA, TYPEB, ARRAYA, ARRAYB>::
a(ARG_TYPEB b)
{
   return m_packsetBA[b];
}

template <class TYPEA, class TYPEB, class ARRAYA, class ARRAYB >
::collection::count spreadset <TYPEA, TYPEB, ARRAYA, ARRAYB>::
get_a_item_count()
{
   return m_packsetBA.get_item_count();
}

template <class TYPEA, class TYPEB, class ARRAYA, class ARRAYB >
::collection::count spreadset <TYPEA, TYPEB, ARRAYA, ARRAYB>::
get_b_item_count()
{
   return m_packsetAB.get_item_count();
}

template <class TYPEA, class TYPEB, class ARRAYA, class ARRAYB >
::collection::count spreadset <TYPEA, TYPEB, ARRAYA, ARRAYB>::
get_a_pack_count()
{
   return m_packsetAB.get_pack_count();
}

template <class TYPEA, class TYPEB, class ARRAYA, class ARRAYB >
::collection::count spreadset <TYPEA, TYPEB, ARRAYA, ARRAYB>::
get_b_pack_count()
{
   return m_packsetBA.get_pack_count();
}


template <class TYPEA, class TYPEB, class ARRAYA, class ARRAYB >
void spreadset <TYPEA, TYPEB, ARRAYA, ARRAYB>::erase_all()
{
   m_packsetAB.erase_all();
   m_packsetBA.erase_all();
}


#if OSBIT == 32

using iptr_spreadset = i32_spreadset;

#else

using iptr_spreadset = i64_spreadset;

#endif



