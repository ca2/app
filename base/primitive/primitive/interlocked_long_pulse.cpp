#include "framework.h"


interlocked_long_pulse::interlocked_long_pulse(interlocked_long * plockedlong, long lLevel)
{
   m_plockedlong     = plockedlong;
   m_lLevel          = lLevel;
   if(m_plockedlong != nullptr)
   {
      m_plockedlong->add(m_lLevel);
   }
}

interlocked_long_pulse::~interlocked_long_pulse()
{
   if(m_plockedlong != nullptr)
   {
      m_plockedlong->subtract(m_lLevel);
   }
}


