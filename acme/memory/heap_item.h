#pragma once


class CLASS_DECL_ACME heap_item
{
public:


   u8 *      m_pbStart;
   u8 *      m_pbEnd;
#ifdef _UWP
   DWORD64     m_dwTickCount;
#else
   u32       m_dwTickCount;
#endif


   inline heap_item()
   {
      m_pbStart = nullptr;
      m_pbEnd = nullptr;
   }


#ifdef _UWP
   inline heap_item(void * p,memsize iSize,DWORD64 millis)
#else
   inline heap_item(void * p,memsize iSize,u32 millis)
#endif
   {
      m_pbStart = (u8 *)point;
      m_pbEnd = ((u8 *)point) + max(iSize - 1,0);
      m_dwTickCount = millis;
   }


   inline char compare(void * p)
   {
      if(((u8 *)point) <= m_pbStart)
         return 1;
      else if(((u8 *)point) >= m_pbEnd)
         return -1;
      else
         return 0;
   }

   inline bool contains(void * p)
   {
      if(((u8 *)point) <= m_pbStart)
         return false;
      else if(((u8 *)point) >= m_pbEnd)
         return false;
      else
         return true;
   }

};





