#pragma once


class CLASS_DECL_APEX interlocked_long_pulse
{
public:


   interlocked_long *   m_plockedlong;
   long                 m_lLevel;

      
   interlocked_long_pulse(interlocked_long * plockedlong, long lLevel);
   virtual ~interlocked_long_pulse();


};
