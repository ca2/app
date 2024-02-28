// Created by camilo on 2021-09-06 14:37 BRT <3ThomasBS_!!
#pragma once


#include "acme/parallelization/synchronous_lock.h"


template < typename TYPE >
class ___synchronously_keep_bit :
   public set_bit < TYPE >
{
public:

   
   ::matter *  m_pmatterLock;
   bool        m_bKeepValue;
   bool        m_bKeepAwayValue;
   bool        m_bKept;


   ___synchronously_keep_bit(::matter * pmatterLock, TYPE & field, ::u64 mask, bool bKeepValue) :
      ___synchronously_keep_bit(pmatterLock, field, mask, bKeepValue, (field & mask) == mask) {}

   ___synchronously_keep_bit(::matter * pmatterLock, TYPE & field, ::u64 mask, bool bKeepValue, bool bKeepAwayValue) :
      set_bit < TYPE > (field, mask), m_pmatterLock(pmatterLock), m_bKeepValue(bKeepValue), m_bKeepAwayValue(bKeepAwayValue), m_bKept(false)
   {

      keep();

   }

   ~___synchronously_keep_bit()
   {

      keep_away();

   }


   void keep()
   {

      if (m_bKept)
      {

         return;

      }

      m_bKept = true;

      _synchronous_lock synchronouslock(m_pmatterLock->synchronization());

      this->set(m_bKeepValue);

   }


   void keep_away()
   {

      if (!m_bKept)
      {

         return;

      }

      m_bKept = false;

      _synchronous_lock synchronouslock(m_pmatterLock->synchronization());

      this->set(m_bKeepAwayValue);

   }


};


template < typename TYPE >
auto synchronously_keep_bit(::matter * pmatterLock, TYPE & field, ::u64 mask, bool bKeepValue)
{
   
   return ___synchronously_keep_bit < TYPE >(pmatterLock, field, mask, bKeepValue);

}


template < typename TYPE >
auto synchronously_keep_bit(::matter * pmatterLock, TYPE & field, ::u64 mask, bool bKeepValue, bool bKeepAwayValue)
{

   return ___synchronously_keep_bit < TYPE >(pmatterLock, field, mask, bKeepValue, bKeepAwayValue);

}



