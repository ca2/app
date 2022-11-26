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
   inline heap_item(void * p,memsize iSize,DWORD64 class ::time)
#else
   inline heap_item(void * p,memsize iSize,u32 class ::time)
#endif
   {
      m_pbStart = (u8 *)point_i32;
      m_pbEnd = ((u8 *)point_i32) + maximum(iSize - 1,0);
      m_dwTickCount = class ::time;
   }


   inline char compare(void * p)
   {
      if(((u8 *)point_i32) <= m_pbStart)
         return 1;
      else if(((u8 *)point_i32) >= m_pbEnd)
         return -1;
      else
         return 0;
   }

   inline bool contains(void * p)
   {
      if(((u8 *)point_i32) <= m_pbStart)
         return false;
      else if(((u8 *)point_i32) >= m_pbEnd)
         return false;
      else
         return true;
   }

};





