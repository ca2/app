// From map.h by camilo on 2022-09-12 04:01 <3ThomasBorregaardSørensen!!
#pragma once


#include "set_node.h"


template < typename PAYLOAD, const int DEFAULT_HASH_TABLE_SIZE = 17 >
class set_dynamic_hash_table
{
public:


   using node = set_node < PAYLOAD >;

   using ITEM = node;

   using ITEM_POINTER = ITEM *;

   using iterator = ::list_iterator < ITEM_POINTER >;


   iterator          m_pHashDefault[DEFAULT_HASH_TABLE_SIZE];
   iterator *        m_ppHash;
   ::u32             m_nHashTableSize;


   set_dynamic_hash_table()
   {

      m_ppHash = nullptr;

      m_nHashTableSize = DEFAULT_HASH_TABLE_SIZE;

   }


   ::u32 GetHashTableSize() const
   {

      return m_nHashTableSize;

   }


   void InitHashTable(::u32 nHashSize, bool bAllocNow = true)
   {

      if (nHashSize <= 0)
      {

         throw "Hash table size must be greater than 0";

      }

      if (m_ppHash != nullptr && m_ppHash != m_pHashDefault && m_nHashTableSize > DEFAULT_HASH_TABLE_SIZE)
      {

         delete[] m_ppHash;

      }

      m_ppHash = nullptr;

      if (bAllocNow)
      {

         if (nHashSize <= DEFAULT_HASH_TABLE_SIZE)
         {

            m_ppHash = m_pHashDefault;

         }
         else
         {

            m_ppHash = memory_new iterator[nHashSize];

            ENSURE(m_ppHash != nullptr);

         }

         ::zero(m_ppHash, sizeof(iterator) * nHashSize);

      }

      m_nHashTableSize = nHashSize;

   }


   void erase_all()
   {

      if (m_ppHash != nullptr && m_ppHash != m_pHashDefault && m_nHashTableSize > DEFAULT_HASH_TABLE_SIZE)
      {

         delete[] m_ppHash;

      }

      m_ppHash = nullptr;

   }


};


template < int m_nHashTableSize, typename PAYLOAD >
class set_fixed_hash_table
{
public:


   typedef set_node < PAYLOAD > node;


   node * m_ppHash[m_nHashTableSize];


   set_fixed_hash_table()
   {

      ASSERT(m_nHashTableSize > 0);

      zero(m_ppHash, sizeof(m_ppHash));

   }


   ::u32 GetHashTableSize() const
   {

      return m_nHashTableSize;

   }


   void InitHashTable(::u32 hashSize, bool bAllocNow = true) {  }


   void erase_all()
   {

      zero(m_ppHash, sizeof(m_ppHash));

   }


};



