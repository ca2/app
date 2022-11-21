﻿#pragma once


#include "array_base.h"
#include "copy_elements.h"



template < class TYPE, class ARG_TYPE, class ALLOCATOR, ::enum_type m_etypeContainer >
class array :
   public ::array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >
{
public:


   typedef TYPE BASE_TYPE;
   typedef ARG_TYPE BASE_ARG_TYPE;
   typedef array < TYPE, ARG_TYPE > BASE_ARRAY;
   typedef ::array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ARRAY_BASE;
   typedef typename ARRAY_BASE::iterator iterator;
   typedef typename ARRAY_BASE::const_iterator const_iterator;
   typedef typename ARRAY_BASE::iterator_range iterator_range;
   typedef typename ARRAY_BASE::const_iterator_range const_iterator_range;


   explicit array(::particle * pparticle = nullptr, ::count nGrowBy = 0);

   template < typename ITERATOR >
   array(ITERATOR iterator, ::count count) :
      array(iterator, iterator + count)
   {

   }

   template < typename ITERATOR, typename STOP >
   array(ITERATOR iterator, STOP stop)
   {

      while(iterator < stop)
      {

         add(*iterator);

         iterator++;

      }

   }

   array(nullptr_t) : array() {}
   array(const array & a);
   array(::std::initializer_list < TYPE > l);
   array(enum_create_new, ::count n);
   array(::count n, ARG_TYPE t);
   array(array && a) noexcept : array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >(::move(a)) { }
   ~array() override;


   inline const TYPE& get_at(::index nIndex) const;
   inline TYPE& get_at(::index nIndex);
   inline void set_at(::index nIndex, ARG_TYPE newElement);




   inline const TYPE * data() const { return this->get_data(); }
   inline TYPE * data() { return this->get_data(); }

   // must not be overloaded!!
   inline ::index add_item(ARG_TYPE newElement);


   inline ::index add(ARG_TYPE newElement);
   inline ::count append(const array& src);

   template < primitive_container CONTAINER >
      inline ::count append(const CONTAINER& container)
   {

         return ARRAY_BASE::append(container);

   }


   inline void copy(const array& src);

   inline TYPE & add_new(::count c = 1);


   inline TYPE & add_new_at(::index iIndex, ::count count = 1);


   inline array & operator << (ARG_TYPE newElement) { add(newElement); return *this; }


   // Operations that move elements around
   //inline ::index insert_at(::index nIndex, ARG_TYPE newElement, ::count nCount = 1);
   //void _001RemoveIndexes(index_array & ia);
   //void erase_indexes(const index_array & ia); // erase indexes from ::index array upper bound to ::index array lower bound
   //void erase_descending_indexes(const index_array & ia); // erase indexes from ::index array lower bound to ::index array upper bound
   //::index insert_at(::index nStartIndex, array* pNewArray);

   using array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::operator=;
   inline array & operator = (const array & src);
   inline array & operator = (array && a);
   inline array & move (array && a);


   //inline ::index find_first(ARG_TYPE t, ::index (* pfnCompare)(ARG_TYPE, ARG_TYPE), ::index start = 0, ::index last = -1) const;

   //::index raw_find_first(TYPE * point, ::index first = 0, ::index last = -1) const;

   //template < class DERIVED >
   //inline ::index find_first(DERIVED * point, ::index first = 0, ::index last = -1)
   //{
   //   return raw_find_first(dynamic_cast < TYPE * > (point), first, last);
   //}

   template < class ARRAY >
   inline ::count slice(ARRAY & a, ::index iStart = 0, ::count nCount = -1)
   {

      ::count ca = 0;

      ::index iEnd;

      if(nCount < 0)
         iEnd = this->get_upper_bound(nCount);
      else
         iEnd = iStart + nCount - 1;

      for(::index i = iStart; i <= iEnd; i++)
      {

         a.add(this->element_at(i));
         ca++;

      }

      return ca;

   }

   template < typename ARRAY >
   inline ARRAY slice(::index iStart = 0, ::count nCount = -1)
   {

      ARRAY a;

      slice(a, iStart, nCount);

      return a;

   }

   //operator TYPE *() {return this->m_pData;}
   //operator const TYPE *() const {return this->m_pData;}

   template < container_type CONTAINER >
   inline array & operator += (const CONTAINER & container);

   template < typename... T >
   void fadd(T... a)
   {

      add(TYPE(a...));

   }

   template < typename PREDICATE >
   ::index predicate_index_index(::index iPredicateIndex, PREDICATE predicate)
   {

      if (iPredicateIndex < 0)
      {

         return -1;

      }

      for (::index iIndex = 0; iIndex < this->get_size(); iIndex++)
      {

         auto & element = this->element_at(iIndex);

         if (predicate(element))
         {

            if (iPredicateIndex <= 0)
            {

               return iIndex;

            }

            iPredicateIndex--;

         }

      }

      return -1;

   }

   template < typename PREDICATE >
   ::index index_predicate_index(::index iIndex, PREDICATE predicate)
   {

      ::index iPredicateIndex = -1;

      ::index i = 0;

      for (; i <= iIndex && i < this->get_size(); i++)
      {

         auto& element = this->element_at(i);

         if (predicate(element))
         {

            iPredicateIndex++;

         }

      }

      if (i <= iIndex)
      {

         return -1;

      }

      return iPredicateIndex;

   }

   template < typename PRED >
   bool predicate_add_unique(TYPE t, PRED pred)
   {

      if (this->predicate_contains(pred))
      {

         return false;

      }

      this->add(t);

      return true;

   }


   template < typename ITERABLE >
   array_base< TYPE, ARG_TYPE,  ALLOCATOR > & copy_iter(const ITERABLE & iterable)
   {

      this->set_size(0, maximum(__iterable_count(iterable), 17));

      for (auto & item : iterable)
      {

         add_item(item);

      }

      return *this;

   }

};



template < class TYPE, class ARG_TYPE = const TYPE & >
class nodefctr_array :
   public array < TYPE, ARG_TYPE, ::constructor::nodef < TYPE > >
{
public:


   nodefctr_array(::count nGrowBy = 32) : array < TYPE, ARG_TYPE, ::constructor::nodef < TYPE > > (nGrowBy) {}
   nodefctr_array(const array <TYPE, ARG_TYPE> & a) : array < TYPE, ARG_TYPE, ::constructor::nodef < TYPE >  > (a) {}
   //nodefctr_array(::count n) : array < TYPE, ARG_TYPE, ::constructor::nodef < TYPE > > (n) {}
   virtual ~nodefctr_array() {}

};





template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline TYPE& array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::get_at(::index nIndex)
{

   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);

   return this->get_data()[nIndex];

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline const TYPE& array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::get_at(::index nIndex) const
{

   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);

   return this->get_data()[nIndex];

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline void array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::set_at(::index nIndex, ARG_TYPE newElement)
{

   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);

   this->get_data()[nIndex] = newElement;

}



template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline ::index array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::add_item(ARG_TYPE newElement)
{

   auto nIndex = this->m_nSize;

   this->allocate(nIndex + 1);

   this->last() = newElement;

   return nIndex;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline ::index array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::add(ARG_TYPE newElement)
{

   return add_item(newElement);

}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//template < container_type CONTAINER >
//inline ::index array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::add(const CONTAINER & container)
//{
//
//   ::index i = -1;
//
//   for(auto & item : container)
//   {
//
//      i = add_item(item);
//
//   }
//
//   return i;
//
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline ::index array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::append(ARG_TYPE newElement)
//{
//   return add(newElement);
//}




template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >  & array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::operator = (const array & src)
{

   if(&src != this)
   {

      copy(src);

   }

   return *this;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::array(::particle * pparticle, ::count nGrowBy) //:
{


}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::array(const array & a)
{

   operator = (a);

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::array(::std::initializer_list < TYPE >  l)
{

   for(auto & item : l)
   {

      add((ARG_TYPE) item);

   }

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > :: array(enum_create_new, ::count n)
{

this->allocate(n);

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::array(::count n, ARG_TYPE t)
{

while (n > 0)
{

add(t);

n--;

}

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::~array()
{

   this->erase_all(); // on_destruct_element is virtual and won't be available for array_base

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline ::index array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::append(const array& src)
{
   // ASSERT_VALID(this);
   ASSERT(this != &src);   // cannot append to itself

   if(this == &src)
      throw_exception(error_bad_argument);

   ::count nOldSize = this->m_nSize;
   this->allocate(this->m_nSize + src.m_nSize);
   CopyElements<TYPE>(&this->m_pData[nOldSize], src.m_pData, src.m_nSize);
   return nOldSize;
}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline void array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::copy(const array& src)
{

   ASSERT(this != &src);

   if(this != &src)
   {

      auto nSrcSize = src.m_nSize;

      this->allocate(nSrcSize);

      CopyElements<TYPE>(this->m_pData,src.m_pData, nSrcSize);

   }

}




template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
template < container_type CONTAINER >
inline array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::operator += (const CONTAINER & container)
{

   if(&container == this)
   {

      array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > aCopy(container);

      append(aCopy);

   }
   else
   {

      append(container);

   }

   return *this;

}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//template < container CONTAINER >
//inline array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >  array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::operator + (const CONTAINER & container) const
//{
//
//   array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >  aNew(*this);
//
//   aNew.add(container);
//
//   return aNew;
//
//}
//

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline TYPE & array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::add_new(::count c)
{

if (c <= 0)
{

throw_exception(error_bad_argument);

}

auto end = this->m_nSize;

this->set_size(end + c);

return this->element_at(end);

}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline TYPE & array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::add_new_at(int iIndex)
//{
//
//   this->make_room_at(iIndex);
//
//   return this->element_at(iIndex);
//
//}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline TYPE & array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::add_new_at(::index iIndex, ::count nCount)
{

   this->make_room_at(iIndex, nCount);

   return this->element_at(iIndex);

}



template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::move(array && a)
{

   if(&a != this)
   {

      this->destroy();

      this->m_nGrowBy = a.m_nGrowBy;
      this->m_pData = a.m_pData;
      this->m_nSize = a.m_nSize;
      this->m_nMaxSize = a.m_nMaxSize;

      a.m_pData = nullptr;
      a.m_nSize = 0;
      a.m_nMaxSize = 0;

   }

   return *this;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::operator = (array && a)
{

   move(::move(a));

   return *this;

}




