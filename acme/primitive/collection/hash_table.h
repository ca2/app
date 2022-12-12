// From map.h by camilo on 2022-09-12 04:01 <3ThomasBorregaardSorensen!!
#pragma once


#include "map_association.h"


template < typename PAYLOAD, const int DEFAULT_HASH_TABLE_SIZE = 17 >
class set_dynamic_hash_table
{
public:


   using association = map_association < PAYLOAD >;

   using ITEM = association;

   using ITEM_POINTER = ITEM *;

   using iterator = ::list_iterator < ITEM_POINTER >;


   ITEM_POINTER      m_passociationHashDefault[DEFAULT_HASH_TABLE_SIZE];
   ITEM_POINTER *    m_ppassociationHash;
   ::u32             m_nHashTableSize;


   set_dynamic_hash_table()
   {

      m_ppassociationHash = nullptr;

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

      if (m_ppassociationHash != nullptr && m_ppassociationHash != m_passociationHashDefault && m_nHashTableSize > DEFAULT_HASH_TABLE_SIZE)
      {

         delete[] m_ppassociationHash;

      }

      m_ppassociationHash = nullptr;

      if (bAllocNow)
      {

         if (nHashSize <= DEFAULT_HASH_TABLE_SIZE)
         {

            m_ppassociationHash = m_passociationHashDefault;

         }
         else
         {

            m_ppassociationHash = memory_new ITEM_POINTER[nHashSize];

            ENSURE(m_ppassociationHash != nullptr);

         }

         ::zero(m_ppassociationHash, sizeof(ITEM_POINTER) * nHashSize);

      }

      m_nHashTableSize = nHashSize;

   }


   void erase_all()
   {

      if (m_ppassociationHash != nullptr && m_ppassociationHash != m_passociationHashDefault && m_nHashTableSize > DEFAULT_HASH_TABLE_SIZE)
      {

         delete[] m_ppassociationHash;

      }

      m_ppassociationHash = nullptr;

   }


};


template < int m_nHashTableSize, typename PAYLOAD >
class set_fixed_hash_table
{
public:


   typedef map_association < PAYLOAD > association;


   association * m_ppassociationHash[m_nHashTableSize];


   set_fixed_hash_table()
   {

      ASSERT(m_nHashTableSize > 0);

      zero(m_ppassociationHash, sizeof(m_ppassociationHash));

   }


   ::u32 GetHashTableSize() const
   {

      return m_nHashTableSize;

   }


   void InitHashTable(::u32 hashSize, bool bAllocNow = true) {  }


   void erase_all()
   {

      zero(m_ppassociationHash, sizeof(m_ppassociationHash));

   }


};



