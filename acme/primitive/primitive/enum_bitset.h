// Created by camilo on 2021-10-13 01:02 BRT <3ThomasBorregaardSørensen!!
#pragma once


template < typename ENUM, int m_iBitCount >
class enum_bitset
{
public:


   ::u64 m_array[((m_iBitCount - 1) >> 6) + 1];


   void set(ENUM e) { m_array[e >> 6] |= (1ull << (e & 63)); }
   void clear(ENUM e) { m_array[e >> 6] &= ~(1ull << (e & 63)); }
   bool is_set(ENUM e) { return m_array[e >> 6] & (1ull << (e & 63)); }
   void set(ENUM e, bool bSet) { if (bSet) set(e); else clear(e); }


};



