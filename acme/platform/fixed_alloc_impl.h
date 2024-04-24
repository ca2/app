#pragma once


inline void * fixed_alloc_sync::Alloc()
{

   // veripseudo-random generator, don't need to be
   // perfectly sequential or perfectly distributed,
   // just fair well distributed
   // but very important is extremely fast
   i32 i = m_i;
   if(i >= m_iShareCount)
   {
      i = 0;
      m_i = 1;
   }
   else
   {
      m_i++;
   }


   void * p = nullptr;
   m_criticalsectiona[0].lock();
   try
   {
      p = m_allocptra.get_data()[i]->Alloc();
   }
   catch(...)
   {
   }
   m_criticalsectiona[i].unlock();
   if(p == nullptr)
      return nullptr;
   ((i32 *) p)[0] = i;
   return &((i32 *)p)[1];
}

inline void fixed_alloc_sync::Free(void * p)
{

   if (p == nullptr)
      return;

   i32 i = ((i32 *)p)[-1];

   critical_section_lock l(&m_criticalsectiona[i]);

   m_allocptra.get_data()[i]->Free(&((i32 *)p)[-1]);

}



inline void * fixed_alloc::Alloc()
{

   // veripseudo-random generator, don't need to be
   // perfectly sequential or perfectly distributed,
   // just fair well distributed
   // but very important is extremely fast
   i32 i = m_i;
   if(i >= m_iShareCount)
   {
      i = 0;
      m_i = 1;
   }
   else
   {
      m_i++;
   }


   void * p  = m_allocptra.get_data()[i]->Alloc();

   ((i32 *) p)[0] = i;

   return &((i32 *)p)[1];

}

inline void fixed_alloc::Free(void * p)
{

   if (p == nullptr)
      return;

   i32 i = ((i32 *)p)[-1];

   m_allocptra.get_data()[i]->Free(&((i32 *)p)[-1]);

}






extern CLASS_DECL_ACME fixed_alloc_array g_fixedalloca;
