// Created by camilo on 2021-03-09 00:43 BRT <3ThomasBS_!!


template < typename TYPE >
void tiny_array < TYPE > ::allocate(int iCount)
{

   if (iCount < 0)
   {

      throw ::exception(error_bad_argument);

      return;

   }

   if (iCount > TINY_ARRAY_BUILTIN_SIZE || m_iAllocation > 0)
   {

      if (m_iAllocation <= 0)
      {

         auto p = (TYPE *) ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(sizeof(TYPE) * iCount);

         ::zero(p, sizeof(TYPE) * iCount);

         m_iAllocation = iCount;

         m_p = p;

      }

      else if (iCount > m_iAllocation)
      {

         auto p = (TYPE *) memory_reallocate(m_p, sizeof(TYPE) * iCount);

         ::zero(p + m_iCount, sizeof(TYPE) * (iCount - m_iAllocation));

         m_iAllocation = iCount;

         m_p = p;

      }

   }
   else
   {

      m_p = m_typea;

   }

   m_iCount = iCount;

}


template < typename TYPE >
void tiny_array < TYPE > ::free()
{

   if (m_iAllocation > 0)
   {

      ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->free(m_p);

   }

   m_iCount = 0;
   
   m_iAllocation = 0;

   m_p = nullptr;

}


template < typename TYPE >
void tiny_array < TYPE > ::zero()
{

   ::zero(m_p, sizeof(TYPE) * m_iCount);

}


template < typename TYPE >
void tiny_array < TYPE > ::set_at_grow(int iIndex, const TYPE& t)
{

   element_at_grow(iIndex) = t;

}


template < typename TYPE >
TYPE & tiny_array < TYPE > ::element_at_grow(int iIndex)
{

   if (iIndex < 0)
   {

      throw ::exception(error_bad_argument);

   }

   if (iIndex >= m_iCount)
   {

      allocate(iIndex + 1);

   }

   return m_p[iIndex];

}



