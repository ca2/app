#pragma once


inline void * fixed_alloc_sync::Alloc()
{

   // veripseudo-random generator, don't need to be
   // perfectly sequential or perfectly distributed,
   // just fair well distributed
   // but very important is extremely fast
   int i = m_i;
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
   m_protectptra.get_data()[i]->lock();
   try
   {
      p = m_allocptra.get_data()[i]->Alloc();
   }
   catch(...)
   {
   }
   m_protectptra.get_data()[i]->unlock();
   if(p == nullptr)
      return nullptr;
   ((int *) p)[0] = i;
   return &((int *)p)[1];
}

inline void fixed_alloc_sync::Free(void * p)
{

   if (p == nullptr)
      return;

   int i = ((int *)p)[-1];

   cslock l(m_protectptra.get_data()[i]);

   m_allocptra.get_data()[i]->Free(&((int *)p)[-1]);

}



inline void * fixed_alloc::Alloc()
{

   // veripseudo-random generator, don't need to be
   // perfectly sequential or perfectly distributed,
   // just fair well distributed
   // but very important is extremely fast
   int i = m_i;
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

   ((int *) p)[0] = i;

   return &((int *)p)[1];

}

inline void fixed_alloc::Free(void * p)
{

   if (p == nullptr)
      return;

   int i = ((int *)p)[-1];

   m_allocptra.get_data()[i]->Free(&((int *)p)[-1]);

}






extern CLASS_DECL_AURA fixed_alloc_array g_fixedalloca;
