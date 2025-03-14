#pragma once


#define TINY_ARRAY_BUILTIN_SIZE 4


template < typename TYPE >
class tiny_array
{
public:


   TYPE *      m_p;
   int       m_iCount;
   int       m_iAllocation;
   TYPE        m_typea[TINY_ARRAY_BUILTIN_SIZE];



   tiny_array() : m_iCount(0), m_iAllocation(0), m_p(nullptr) { }
   ~tiny_array() { free(); }


   void allocate(int iCount);
   void free();
   void zero();
   void set_at_grow(int iIndex, const TYPE& t);
   void erase_at(int iIndex);
   void push(const TYPE & t) { set_at_grow(count(), t);}
   TYPE pop() { TYPE t = element_at(count() - 1); erase_at(count() -1); return t;   }
   int count() const {return m_iCount;}

   TYPE& element_at_grow(int iIndex);
   TYPE& element_at(int iIndex) { return m_p[iIndex];}


};





// Created by camilo on 2021-03-09 00:43 BRT <3ThomasBS_!!


template < typename TYPE >
void tiny_array < TYPE > ::allocate(int iCount)
{

   if (iCount < 0)
   {

      throw_exception(error_bad_argument);

      return;

   }

   if (iCount > TINY_ARRAY_BUILTIN_SIZE || m_iAllocation > 0)
   {

      if (m_iAllocation <= 0)
      {

         memsize sizeAllocated = 0;

         auto p = (TYPE *) ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(sizeof(TYPE) * iCount, &sizeAllocated);

         auto iAllocation = (int) (sizeAllocated / sizeof(TYPE));

         ::zero(p, sizeof(TYPE) * iAllocation);

         m_iAllocation = iAllocation;

         m_p = p;

      }

      else if (iCount > m_iAllocation)
      {

         auto p = (TYPE *) ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->reallocate(m_p, sizeof(TYPE) * iCount);

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

      ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(m_p);

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
void tiny_array < TYPE > ::erase_at(int iIndex)
{

   if(iIndex < 0 || iIndex >= m_iCount)
   {

      throw_exception(error_index_out_of_bounds);

   }

   auto iNext = iIndex + 1;

   auto countMove = m_iCount - iNext;

   if(countMove > 0)
   {

      ::memory_transfer(m_p + iIndex, m_p + iNext, countMove * sizeof(TYPE));

   }

   m_iCount--;

}


template < typename TYPE >
TYPE & tiny_array < TYPE > ::element_at_grow(int iIndex)
{

   if (iIndex < 0)
   {

      throw_exception(error_bad_argument);

   }

   if (iIndex >= m_iCount)
   {

      allocate(iIndex + 1);

   }

   return m_p[iIndex];

}



