#pragma once


class CLASS_DECL_ACME heap_item
{
public:


   unsigned char *      m_pbStart;
   unsigned char *      m_pbEnd;
#ifdef UNIVERSAL_WINDOWS
   DWORD64     m_dwTickCount;
#else
   unsigned int       m_dwTickCount;
#endif


   inline heap_item()
   {
      m_pbStart = nullptr;
      m_pbEnd = nullptr;
   }


#ifdef UNIVERSAL_WINDOWS
   inline heap_item(void * p,memsize iSize,DWORD64 class ::time)
#else
   inline heap_item(void * p,memsize iSize,unsigned int class ::time)
#endif
   {
      m_pbStart = (unsigned char *)int_point;
      m_pbEnd = ((unsigned char *)int_point) + maximum(iSize - 1,0);
      m_dwTickCount = class ::time;
   }


   inline char compare(void * p)
   {
      if(((unsigned char *)int_point) <= m_pbStart)
         return 1;
      else if(((unsigned char *)int_point) >= m_pbEnd)
         return -1;
      else
         return 0;
   }

   inline bool contains(void * p)
   {
      if(((unsigned char *)int_point) <= m_pbStart)
         return false;
      else if(((unsigned char *)int_point) >= m_pbEnd)
         return false;
      else
         return true;
   }

};





