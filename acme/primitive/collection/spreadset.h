#pragma once




template <class TYPEA, class ARG_TYPEA, class TYPEB, class ARG_TYPEB, class ARRAYA, class ARRAYB  >
class spreadset
{
public:


   packset < TYPEA, ARG_TYPEA, TYPEB, ARG_TYPEB, ARRAYB > m_packsetAB;
   packset < TYPEB, ARG_TYPEB, TYPEA, ARG_TYPEA, ARRAYA > m_packsetBA;


   void spread(ARG_TYPEA a, ARG_TYPEB b);


   ARRAYB & b(ARG_TYPEA a);
   ARRAYA & a(ARG_TYPEB b);


   ::count get_a_item_count();
   ::count get_b_item_count();
   ::count get_a_pack_count();
   ::count get_b_pack_count();


   void erase_all();


};


template <class TYPEA, class ARG_TYPEA, class TYPEB, class ARG_TYPEB, class ARRAYA, class ARRAYB >
void spreadset <TYPEA, ARG_TYPEA, TYPEB, ARG_TYPEB, ARRAYA, ARRAYB>::
spread(ARG_TYPEA a, ARG_TYPEB b)
{
   m_packsetAB.pack(a, b);
   m_packsetBA.pack(b, a);
}

template <class TYPEA, class ARG_TYPEA, class TYPEB, class ARG_TYPEB, class ARRAYA, class ARRAYB >
ARRAYB & spreadset <TYPEA, ARG_TYPEA, TYPEB, ARG_TYPEB, ARRAYA, ARRAYB>::
b(ARG_TYPEA a)
{
   return m_packsetAB[a];
}


template <class TYPEA, class ARG_TYPEA, class TYPEB, class ARG_TYPEB, class ARRAYA, class ARRAYB >
ARRAYA & spreadset <TYPEA, ARG_TYPEA, TYPEB, ARG_TYPEB, ARRAYA, ARRAYB>::
a(ARG_TYPEB b)
{
   return m_packsetBA[b];
}

template <class TYPEA, class ARG_TYPEA, class TYPEB, class ARG_TYPEB, class ARRAYA, class ARRAYB >
::count spreadset <TYPEA, ARG_TYPEA, TYPEB, ARG_TYPEB, ARRAYA, ARRAYB>::
get_a_item_count()
{
   return m_packsetBA.get_item_count();
}

template <class TYPEA, class ARG_TYPEA, class TYPEB, class ARG_TYPEB, class ARRAYA, class ARRAYB >
::count spreadset <TYPEA, ARG_TYPEA, TYPEB, ARG_TYPEB, ARRAYA, ARRAYB>::
get_b_item_count()
{
   return m_packsetAB.get_item_count();
}

template <class TYPEA, class ARG_TYPEA, class TYPEB, class ARG_TYPEB, class ARRAYA, class ARRAYB >
::count spreadset <TYPEA, ARG_TYPEA, TYPEB, ARG_TYPEB, ARRAYA, ARRAYB>::
get_a_pack_count()
{
   return m_packsetAB.get_pack_count();
}

template <class TYPEA, class ARG_TYPEA, class TYPEB, class ARG_TYPEB, class ARRAYA, class ARRAYB >
::count spreadset <TYPEA, ARG_TYPEA, TYPEB, ARG_TYPEB, ARRAYA, ARRAYB>::
get_b_pack_count()
{
   return m_packsetBA.get_pack_count();
}


template <class TYPEA, class ARG_TYPEA, class TYPEB, class ARG_TYPEB, class ARRAYA, class ARRAYB >
void spreadset <TYPEA, ARG_TYPEA, TYPEB, ARG_TYPEB, ARRAYA, ARRAYB>::erase_all()
{
   m_packsetAB.erase_all();
   m_packsetBA.erase_all();
}


#if OSBIT == 32

using iptr_spreadset = i32_spreadset;

#else

using iptr_spreadset = i64_spreadset;

#endif



