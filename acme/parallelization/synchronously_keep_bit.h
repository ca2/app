// Created by camilo on 2021-09-06 14:37 BRT <3ThomasBS_!!
#pragma once


template < primitive_integral INTEGRAL >
class ___synchronously_keep_bit :
   public set_bit < INTEGRAL >
{
public:

   
   ::matter *  m_pmatterLock;
   bool        m_bKeepValue;
   bool        m_bKeepAwayValue;
   bool        m_bKept;


   ___synchronously_keep_bit(::matter * pmatterLock, INTEGRAL & field, INTEGRAL mask, bool bKeepValue) :
      ___synchronously_keep_bit(pmatterLock, field, mask, bKeepValue, (field & mask) == mask) {}

   ___synchronously_keep_bit(::matter * pmatterLock, INTEGRAL & field, INTEGRAL mask, bool bKeepValue, bool bKeepAwayValue) :
      set_bit < INTEGRAL > (field, mask), m_pmatterLock(pmatterLock), m_bKeepValue(bKeepValue), m_bKeepAwayValue(bKeepAwayValue), m_bKept(false)
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

      _synchronous_lock synchronouslock(m_pmatterLock->mutex());

      this->set(m_bKeepValue);

   }


   void keep_away()
   {

      if (!m_bKept)
      {

         return;

      }

      m_bKept = false;

      _synchronous_lock synchronouslock(m_pmatterLock->mutex());

      this->set(m_bKeepAwayValue);

   }


};


template < primitive_integral INTEGRAL >
auto synchronously_keep_bit(::matter * pmatterLock, INTEGRAL & field, INTEGRAL mask, bool bKeepValue)
{
   
   return ___synchronously_keep_bit < INTEGRAL >(pmatterLock, field, mask, bKeepValue);

}


template < primitive_integral INTEGRAL >
auto synchronously_keep_bit(::matter * pmatterLock, INTEGRAL & field, INTEGRAL mask, bool bKeepValue, bool bKeepAwayValue)
{

   return ___synchronously_keep_bit < INTEGRAL >(pmatterLock, field, mask, bKeepValue, bKeepAwayValue);

}



