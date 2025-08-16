#pragma once


#include "acme/prototype/collection/array_base.h"


//raw_array_base is an array that does not call constructors or destructor in elements
// array is an array that call only copy constructor and destructor in elements
// array is an array that call default constructors, copy constructs and destructors in elements


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
class raw_array_base :
   public array_base < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >
{
public:


   using BASE_TYPE = TYPE;
   using BASE_ARG_TYPE = ARG_TYPE;
   using BASE_ARRAY = array_base < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >;
   using ARRAY_BASE = base_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >;
   using BASE_RAW_RANGE = typename BASE_ARRAY::BASE_RAW_RANGE;
   using iterator = typename ARRAY_BASE::iterator;
   using const_iterator = typename ARRAY_BASE::const_iterator;


   using BASE_ARRAY::BASE_ARRAY;
   using BASE_ARRAY::operator =;

   //raw_array_base() {}
   //raw_array_base(std::initializer_list < TYPE > initializer_list) : ARRAY_BASE(initializer_list) {}
   //raw_array_base(constraw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > & a);
   //raw_array_base(raw_array_base <TYPE,ARG_TYPE, TYPED, MEMORY, t_etypeContainer > && a) noexcept;
   //raw_array_base(ARG_TYPE t, ::collection::count n);
   //raw_array_base(::range < const_iterator > constrange) : ARRAY_BASE(constrange) {}
   //raw_array_base(const_iterator begin, const_iterator end) : ARRAY_BASE(begin, end) { }
   //raw_array_base(const TYPE * ptypea, ::collection::count n);
   //virtual ~raw_array_base();


   //// void assert_ok() const override;
   //// void dump(dump_context & dumpcontext) const override;




   void erase_last();

   ::collection::count erase_all();
   void clear();




   // Accessing elements
   inline const TYPE& get_at(::collection::index nIndex) const;
   inline TYPE& get_at(::collection::index nIndex);
   inline void set_at(::collection::index nIndex, ARG_TYPE newElement);


   // Direct Access to the matter data (may return nullptr)
   inline const TYPE* get_data() const;
   inline TYPE* get_data();

   // Potentially growing theraw_array_base
   //void set_at_grow(::collection::index nIndex, ARG_TYPE newElement);
   //TYPE & element_at_grow(::collection::index nIndex);
   TYPE get_at_grow(::collection::index nIndex);
   ::collection::index add(ARG_TYPE newElement) { return add_item(newElement); }
   ::collection::index add_item(ARG_TYPE newElement);
   ::collection::index append(const TYPE * p, ::collection::count c);
   ::collection::index append(const raw_array_base& src);
   virtual TYPE * add_new(::collection::count count);
   virtual TYPE & add_new();

   //::collection::index append(const raw_array_base& src);
   //void copy(const raw_array_base& src);


   inline TYPE pop(::collection::index i = -1);
   inline ::collection::index push(ARG_TYPE newElement);
   inline void pop_back(::collection::index i = -1);



   //iterator erase(iterator pos);
   //iterator erase(iterator first, iterator last);
   //iterator begin()
   //{
   //   return iterator(0, this);
   //}

   //iterator end()
   //{
   //   return iterator(this->get_size(), this);
   //}


   // overloaded operator helpers
   //inline const TYPE& operator[](::collection::index nIndex) const;
   //inline TYPE& operator[](::collection::index nIndex);

    //that transfer elements around
   TYPE & insert_at(::collection::index nIndex, ARG_TYPE newElement, ::collection::count nCount = 1);
   //::collection::index erase_at(::collection::index nIndex, ::collection::count nCount = 1);
   //void _001RemoveIndexes(index_array & ia);
   //void erase_indexes(const index_array & ia); // erase indexes from ::collection::index raw_array_base upper bound to ::collection::index raw_array_base lower bound
   //void erase_descending_indexes(const index_array & ia); // erase indexes from ::collection::index raw_array_base lower bound to ::collection::index raw_array_base upper bound
   //::collection::index insert_at(::collection::index nStartIndex, raw_array_base* pNewArray);
   //void __swap(::collection::index index1, ::collection::index index2);

   //raw_array_base & operator = (const raw_array_base & src);

   ::collection::index find_first(ARG_TYPE t, ::collection::index (* pfnCompare)(ARG_TYPE, ARG_TYPE), ::collection::index start = 0, ::collection::index last = -1) const;

   ::collection::index raw_find_first(TYPE * p, ::collection::index first = 0, ::collection::index last = -1) const;

   template < class DERIVED >
   ::collection::index find_first(DERIVED * p, ::collection::index first = 0, ::collection::index last = -1)
   {
      return raw_find_first(dynamic_cast < TYPE * > (p), first, last);
   }

   template < class ARRAY >
   ::collection::count get_array(ARRAY & a, ::collection::index iStart = 0, ::collection::count nCount = -1)
   {

      ::collection::count ca = 0;

      ::collection::index iEnd;

      if(nCount < 0)
         iEnd = this->get_upper_bound(nCount);
      else
         iEnd = iStart + nCount - 1;

      for(::collection::index i = iStart; i <= iEnd; i++)
      {

         a.add(this->element_at(i));
         ca++;

      }

      return ca;

   }


   raw_array_base & operator += (const raw_array_base & a);
   raw_array_base operator + (const raw_array_base & a) const;


   //using base_array < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator =;
   //inline raw_array_base & operator = (raw_array_base && a);
   //inline raw_array_base & transfer(raw_array_base && a);


   //operator TYPE *() { return this->m_begin;  }
   //operator const TYPE *() const { return this->m_begin; }
   
   
   
   operator ::collection::count () const { return this->get_count(); }


};

//
// template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
// class raw_array_base :
//    virtual public ::particle,
//    public raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >
// {
// public:
//
//
//    raw_array_base() : raw_array_base< TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >() {}
//    template < typename ...Args >
//    raw_array_base(Args&&... args) :
//       raw_array_base< TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >(::std::forward < Args >(args)...)
//    {
//    }
//    raw_array_base(std::initializer_list < TYPE > initializer_list) : raw_array_base< TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >(initializer_list) {}
//
//
// };
//

template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline ::collection::count raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::erase_all()
{
   
   return this->allocate(0, false, false);
   
}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
void raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::clear()
{
   
   erase_all();
   
}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline void raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::erase_last()
{

   this->erase_at(this->get_upper_bound());

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline TYPE& raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::get_at(::collection::index nIndex)
{

   return get_data()[nIndex];
   
}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline const TYPE& raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::get_at(::collection::index nIndex) const
{

   return get_data()[nIndex];

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline void raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::set_at(::collection::index nIndex, ARG_TYPE newElement)
{

   get_data()[nIndex] = newElement;

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline const TYPE* raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::get_data() const
{

   return (const TYPE*)this->m_begin;

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline TYPE* raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::get_data()
{

   return (TYPE*)this->m_begin;

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline ::collection::index raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::add_item(ARG_TYPE newElement)
{

   ::collection::index nIndex = this->size();

   this->set_at_grow(nIndex, newElement);

   return nIndex;

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline ::collection::index raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::append(const TYPE * p, ::collection::count c)
{

   return ARRAY_BASE::append(p, c);

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline ::collection::index raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::append(const raw_array_base & src)
{

   return ARRAY_BASE::append(src);

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline TYPE * raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::add_new(::collection::count count)
{

   this->allocate(this->size() + count, false, true);

   return this->m_begin + (this->get_size() - count);

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline TYPE & raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::add_new()
{

   this->allocate(this->size() + 1, false, true);

   return this->last();

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline TYPE raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::pop(::collection::index n)
{

   ::collection::index i = this->get_upper_bound(n);

   TYPE t = this->element_at(i);

   this->erase_at(i);

   return t;

}

template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline void raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::pop_back(::collection::index n)
{

   this->erase_at(this->get_upper_bound(n));

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline ::collection::index raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::push(ARG_TYPE newElement)
{

   return this->index_of(&insert_at(this->size(), newElement));

}

//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline void raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::add(ARG_TYPE newElement, ::collection::index n)
//{
//   insert_at(this->get_upper_bound(n), newElement);
//}


//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline const TYPE& raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator[](::collection::index nIndex) const
//{
//
//   return this->element_at(nIndex);
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline TYPE& raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator[](::collection::index nIndex)
//{
//
//   return this->element_at(nIndex);
//
//}


//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline void raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::__swap(::collection::index index1, ::collection::index index2)
//{
//   TYPE t = get_data()[index1];
//   get_data()[index1] = get_data()[index2];
//   get_data()[index2] = t;
//}

//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > & raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator = (const raw_array_base & src)
//{
//   if(&src != this)
//   {
//      this->copy(src);
//   }
//   return *this;
//}
//
//
//
// out-of-line functions



//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_array_base(::std::initializer_list < TYPE >  l)
//{
//   for(auto & item : l)
//   {
//      add((ARG_TYPE) item);
//   }
//}



//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_array_base(const raw_array_base  & array):
//   ARRAY_BASE(array)
//{
//
//}
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_array_base(raw_array_base <TYPE,ARG_TYPE, TYPED, MEMORY, t_etypeContainer > && a) noexcept :
//   ARRAY_BASE(::transfer(a))
//{
//
//}
//
////
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >:: raw_array_base(::collection::count n)
////{
////   this->allocate(n);
////}
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_array_base(ARG_TYPE t, ::collection::count n)
//{
//   insert_at(0, t, n);
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_array_base(const TYPE * ptypea, ::collection::count n)
//{
//
//   this->set_size(n);
//
//   ::memory_copy(this->m_begin, ptypea, this->length_in_bytes());
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::~raw_array_base()
//{
//
//   this->destroy();
//
//}

//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//void raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::destroy()
//{
//   if (m_begin != nullptr)
//   {
//      for( int i = 0; i < m_nSize; i++ )
//         destruct_element(m_begin + i)->~TYPE();
//      delete[] (unsigned char*)m_begin;
//      m_begin     = nullptr;
//      m_nSize     = 0;
//      m_countAllocation  = 0;
//   }
//
//}


//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//::collection::count raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::set_size(::collection::count nNewSize, ::collection::count nGrowBy)
//{
//   return allocate(nNewSize, nGrowBy);
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//::collection::count raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::resize(::collection::count nNewSize, ::collection::count nGrowBy)
//{
//   return allocate(nNewSize, nGrowBy);
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//::collection::count raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::allocate_in_bytes(::collection::count nNewSize, ::collection::count nGrowBy)
//{
//   if(nGrowBy < 0)
//   {
//      return allocate(nNewSize / sizeof(TYPE), -1);
//   }
//   else
//   {
//      return allocate(nNewSize / sizeof(TYPE), nGrowBy / sizeof(TYPE));
//   }
//}

//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//::collection::count raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::allocate(::collection::count nNewSize, ::collection::count nGrowBy)
//{
//   ::collection::count countOld = get_count();
//   ASSERT_OK(this);
//   ASSERT(nNewSize >= 0);
//
//   if(nNewSize < 0 )
//      throw ::exception(error_bad_argument);
//
//   if (nGrowBy >= 0)
//      m_countAddUp = nGrowBy;  // set aaa_memory_new int_size
//
//   if (nNewSize == 0)
//   {
//      // shrink to nothing
//      if (m_begin != nullptr)
//      {
////         for( int i = 0; i < m_nSize; i++ )
////            (m_begin + i)->~TYPE();
//         delete[] (unsigned char*)m_begin;
//         m_begin = nullptr;
//      }
//      m_nSize = m_countAllocation = 0;
//   }
//   else if (m_begin == nullptr)
//   {
//      // create buffer big enough to hold number of requested elements or
//      // m_countAddUp elements, whichever is larger.
//#ifdef SIZE_T_MAX
//      if(nNewSize > SIZE_T_MAX/sizeof(TYPE))
//         throw ::exception(error_no_memory);
//      ASSERT(nNewSize <= SIZE_T_MAX/sizeof(TYPE));    // no overflow
//#endif
//      ::collection::count nAllocSize = maximum(nNewSize, m_countAddUp);
////
//      m_begin = (TYPE*) __allocate< unsigned char[(size_t)nAllocSize * sizeof >(TYPE)];
//      //memory_set((void *)m_begin, 0, (size_t)nAllocSize * sizeof(TYPE));
////      for( ::collection::index i = 0; i < nNewSize; i++ )
//  //       ::__allocate< ( (void *) >( m_begin + i ) ) TYPE;
////
//      m_nSize = nNewSize;
//      m_countAllocation = nAllocSize;
//   }
//   else if (nNewSize <= m_countAllocation)
//   {
//      // it fits
//      if (nNewSize > m_nSize)
//      {
//         // initialize the ___new elements
////         memory_set((void *)(m_begin + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
////         for( int i = 0; i < nNewSize-m_nSize; i++ )
////
////            ::__allocate< ( (void *) >( m_begin + m_nSize + i ) ) TYPE;
////
//      }
//      else if (m_nSize > nNewSize)
//      {
//         // destroy the old elements
////         for( int i = 0; i < m_nSize-nNewSize; i++ )
//  //          (m_begin + nNewSize + i)->~TYPE();
//      }
//      m_nSize = nNewSize;
//   }
//   else
//   {
//      // otherwise, grow aaa_base_array
//      nGrowBy = m_countAddUp;
//      if (nGrowBy == 0)
//      {
//         // heuristically determine growth when nGrowBy == 0
//         //  (this avoids heap fragmentation in many situations)
//         nGrowBy = m_nSize / 8;
//         nGrowBy = (nGrowBy < 4) ? 4 : ((nGrowBy > 1024) ? 1024 : nGrowBy);
//      }
//      ::collection::count nNewMax;
//      if (nNewSize < m_countAllocation + nGrowBy)
//         nNewMax = m_countAllocation + nGrowBy;  // granularity
//      else
//         nNewMax = nNewSize;  // no slush
//
//      ASSERT(nNewMax >= m_countAllocation);  // no wrap around
//
//      if(nNewMax  < m_countAllocation)
//         throw ::exception(error_bad_argument);
//
//#ifdef SIZE_T_MAX
//      ASSERT(nNewMax <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
//#endif
//
//      TYPE* pNewData = (TYPE*) __allocate< unsigned char[(size_t)nNewMax * sizeof >(TYPE)];
//
//
//      // copy ___new data from old
//      ::safe_memory_copy(pNewData, (size_t)nNewMax * sizeof(TYPE),
//         m_begin, (size_t)m_nSize * sizeof(TYPE));
//
//      // construct remaining elements
//      ASSERT(nNewSize > m_nSize);
////      memory_set((void *)(pNewData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
////      for( int i = 0; i < nNewSize-m_nSize; i++ )
////
////         ::__allocate< ( (void *) >( pNewData + m_nSize + i ) ) TYPE;
////
//      // get rid of old stuff (note: no destructors called)
//      delete[] (unsigned char*)m_begin;
//      m_begin = pNewData;
//      m_nSize = nNewSize;
//      m_countAllocation = nNewMax;
//   }
//   return countOld;
//}
//

//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//void raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::free_extra()
//{
//   ASSERT_OK(this);
//
//   if (m_nSize != m_countAllocation)
//   {
//      // shrink to desired int_size
//#ifdef SIZE_T_MAX
//      ASSERT(m_nSize <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
//#endif
//      TYPE* pNewData = nullptr;
//      if (m_nSize != 0)
//      {
//         pNewData = (TYPE*) __allocate< unsigned char[m_nSize * sizeof >(TYPE)];
//         // copy ___new data from old
//         ::safe_memory_copy(pNewData, m_nSize * sizeof(TYPE),
//            m_begin, m_nSize * sizeof(TYPE));
//      }
//
//      // get rid of old stuff (note: no destructors called)
//      delete[] (unsigned char*)m_begin;
//      m_begin = pNewData;
//      m_countAllocation = m_nSize;
//   }
//}

//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//void base_array < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::set_at_grow(::collection::index nIndex, ARG_TYPE newElement)
//{
//   //ASSERT_OK(this);
//   //ASSERT(nIndex >= 0);
//
//   if(nIndex < 0)
//      throw ::exception(error_bad_argument);
//
//   if (nIndex >= this->m_nSize)
//      this->allocate(nIndex+1, -1);
//   get_data()[nIndex] = newElement;
//}

template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline TYPE raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::get_at_grow(::collection::index nIndex)
{

   return this->element_at_grow(nIndex);

}


//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline TYPE & raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::element_at_grow(::collection::index nIndex)
//{
//   if (nIndex >= this->m_nSize)
//      this->allocate(nIndex+1, -1);
//   return get_data()[nIndex];
//}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
TYPE & raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::insert_at(::collection::index nIndex, ARG_TYPE newElement, ::collection::count nCount /*=1*/)
{

   return base_array < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::insert_at(nIndex, newElement,nCount);

}


//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//::collection::index raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::insert_at(::collection::index nStartIndex, raw_array_base * pNewArray)
//{
//   ASSERT_OK(this);
//   ASSERT(pNewArray != nullptr);
//   ASSERT_OK(pNewArray);
//   ASSERT(nStartIndex >= 0);
//
//   if(pNewArray == nullptr || nStartIndex < 0)
//      throw ::exception(error_bad_argument);
//
//   if (pNewArray->get_size() > 0)
//   {
//      insert_at(nStartIndex, pNewArray->element_at(0), pNewArray->get_size());
//      for (::collection::index i = 1; i < pNewArray->get_size(); i++)
//         insert_at(nStartIndex + i, pNewArray->element_at(i));
//   }
//
//   return nStartIndex;
//
//}


//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//void raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::dump(dump_context & dumpcontext) const
//{
//
//   matter::dump(dumpcontext);
//
//   dumpcontext << "with " << this->m_nSize << " elements";
//
//   if (dumpcontext.GetDepth() > 0)
//   {
//
//      dumpcontext << "\n";
//
//      dump_elements<TYPE>(dumpcontext,get_data(), this->m_nSize);
//
//   }
//
//   dumpcontext << "\n";
//
//}


//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//void raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::assert_ok() const
//{
//
//   matter::assert_ok();
//
//
//   if (get_data() == nullptr)
//   {
//
//      ASSERT(this->m_nSize == 0);
//      ASSERT(this->m_countAllocation >= 0);
//
//   }
//   else
//   {
//
//      ASSERT(this->m_nSize >= 0);
//      ASSERT(this->m_countAllocation >= 0);
//      ASSERT(this->m_nSize <= this->m_countAllocation);
//      ASSERT(is_memory_segment_ok(this->m_begin, (::memsize_cast) this->m_countAllocation * sizeof(TYPE)));
//
//   }
//
//}


//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//typename raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::iterator raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::erase(iterator pos)
//{
//   if(pos.m_parray == this)
//   {
//      this->erase_at(pos.m_i);
//      return iterator(pos.m_i, this);
//   }
//   else
//   {
//      return this->end();
//   }
//}

//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//typename  raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::iterator raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::erase(iterator begin, iterator last)
//{
//   if(begin.m_parray == this && last.m_parray == this)
//   {
//      if(begin.m_i >= 0 && begin.m_i < this->get_size())
//      {
//         ::collection::count nCount = last.m_i - begin.m_i;
//         erase_at(begin.m_i, nCount);
//         return iterator(begin.m_i, this);
//      }
//      else
//      {
//         return this->end();
//      }
//   }
//   else
//   {
//      return this->end();
//   }
//}
//
//
template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
::collection::index raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_find_first(TYPE *p, ::collection::index find, ::collection::index last) const
{

   if(find < 0)
      find += this->get_count();

   if(last < 0)
      last += this->get_count();

   for(; find <= last; find++)
   {

      if (&this->element_at(find) == p)
      {

         return find;

      }

   }

   return -1;

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
::collection::index raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::find_first(ARG_TYPE t, ::collection::index ( * pfnCompare )(ARG_TYPE, ARG_TYPE), ::collection::index find, ::collection::index last) const

{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find <= last; find++)
   {
      if(pfnCompare((ARG_TYPE)this->element_at(find), (ARG_TYPE)t) == 0)

         return find;
   }
   return -1;
}




template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > & raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator += (const raw_array_base & a)
{

   if(&a == this)
   {
      raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > aCopy(a);
      append(aCopy);
   }
   else
   {
      append(a);
   }
   return *this;

}

template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator + (const raw_array_base & a) const
{
   raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > aNew(*this);
   aNew += a;
   return a;
}








//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > & raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator =(raw_array_base && a)
//{
//
//   return transfer(::transfer(a));
//
//}
//




//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > & raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::transfer(raw_array_base && a)
//{
//
//   if (&a != this)
//   {
//      this->destroy();
//
//      this->m_countAddUp = a.m_countAddUp;
//      this->m_begin = a.m_begin;
//      this->m_end = a.m_end;
//      this->m_countAllocation = a.m_countAllocation;
//
//      a.m_begin = nullptr;
//      a.m_end = nullptr;
//      a.m_countAllocation = 0;
//
//   }
//
//   return *this;
//
//}
//
//



//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline ::collection::count raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::erase_all()
//{
//   return this->allocate(0, -1);
//}
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//void raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::
//clear()
//{
//   erase_all();
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline void raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::erase_last()
//{
//
//   this->erase_at(this->get_upper_bound());
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline TYPE& raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::get_at(::collection::index nIndex)
//{
//
//   return get_data()[nIndex];
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline const TYPE& raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::get_at(::collection::index nIndex) const
//{
//
//   return get_data()[nIndex];
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline void raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::set_at(::collection::index nIndex, ARG_TYPE newElement)
//{
//
//   get_data()[nIndex] = newElement;
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline const TYPE* raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::get_data() const
//{
//
//   return (const TYPE*)this->m_begin;
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline TYPE* raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::get_data()
//{
//
//   return (TYPE*)this->m_begin;
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline ::collection::index raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::add(ARG_TYPE newElement)
//{
//
//   ::collection::index nIndex = (::index_cast ) this->m_nSize;
//
//   set_at_grow(nIndex, newElement);
//
//   return nIndex;
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline ::collection::index raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::add(const raw_array_base & src)
//{
//
//   return this->append(src);
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline ::collection::index raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::add_new(::collection::count count)
//{
//
//   this->allocate(this->size() + count);
//
//   return this->get_upper_bound();
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline TYPE & raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::add_new()
//{
//
//   this->allocate(this->size() + 1);
//
//   return this->last();
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline TYPE raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::pop(::collection::index n)
//{
//
//   ::collection::index i = this->get_upper_bound(n);
//
//   TYPE t = this->element_at(i);
//
//   this->erase_at(i);
//
//   return t;
//
//}
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline void raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::pop_back(::collection::index n)
//{
//
//   this->erase_at(this->get_upper_bound(n));
//
//}
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline ::collection::index raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::push(ARG_TYPE newElement, ::collection::index n)
//{
//   return insert_at(this->get_upper_bound(n), newElement);
//}
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline void raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::add(ARG_TYPE newElement, ::collection::index n)
//{
//   insert_at(this->get_upper_bound(n), newElement);
//}
//
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////inline const TYPE& raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator[](::collection::index nIndex) const
////{
////
////   return this->element_at(nIndex);
////
////}
////
////
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////inline TYPE& raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator[](::collection::index nIndex)
////{
////
////   return this->element_at(nIndex);
////
////}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline void raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::__swap(::collection::index index1, ::collection::index index2)
//{
//   TYPE t = get_data()[index1];
//   get_data()[index1] = get_data()[index2];
//   get_data()[index2] = t;
//}
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > & raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator = (const raw_array_base & src)
//{
//   if(&src != this)
//   {
//      this->copy(src);
//   }
//   return *this;
//}
//
//
//
//// out-of-line functions
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_array_base(::particle * pparticle)
////:
////::matter(pparticle)
//{
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_array_base(::std::initializer_list < TYPE >  l)
//{
//   forallref(l)
//   {
//      add((ARG_TYPE) item);
//   }
//}
//
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_array_base(const raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > & a)// :
//// matter(a.get_app())
//{
//   ::base_array < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator = (a);
//}
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_array_base(raw_array_base <TYPE,ARG_TYPE, TYPED, MEMORY, t_etypeContainer > && a) //:
////   matter(a.get_app())
//{
//
//   this->m_countAddUp = a.m_countAddUp;
//   this->m_begin = a.m_begin;
//   this->m_nSize = a.m_nSize;
//   this->m_countAllocation = a.m_countAllocation;
//
//   //a.m_countAddUp = 0;
//   a.m_begin = nullptr;
//   //a.m_nSize = 0;
//   //a.m_countAllocation = 0;
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >:: raw_array_base(::collection::count n)
//{
//   this->allocate(n);
//}
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_array_base(ARG_TYPE t, ::collection::count n)
//{
//   insert_at(0, t, n);
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_array_base(TYPE * ptypea, ::collection::count n)
//{
//
//   this->allocate(n);
//
//   for(int i = 0; i < n; i++)
//   {
//
//      this->element_at(i) = ptypea[i];
//
//   }
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::~raw_array_base()
//{
//
//   this->destroy();
//
//}
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////void raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::destroy()
////{
////   if (m_begin != nullptr)
////   {
////      for( int i = 0; i < m_nSize; i++ )
////         destruct_element(m_begin + i)->~TYPE();
////      delete[] (unsigned char*)m_begin;
////      m_begin     = nullptr;
////      m_nSize     = 0;
////      m_countAllocation  = 0;
////   }
////
////}
//
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////::collection::count raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::set_size(::collection::count nNewSize, ::collection::count nGrowBy)
////{
////   return allocate(nNewSize, nGrowBy);
////}
////
////
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////::collection::count raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::resize(::collection::count nNewSize, ::collection::count nGrowBy)
////{
////   return allocate(nNewSize, nGrowBy);
////}
////
////
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////::collection::count raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::allocate_in_bytes(::collection::count nNewSize, ::collection::count nGrowBy)
////{
////   if(nGrowBy < 0)
////   {
////      return allocate(nNewSize / sizeof(TYPE), -1);
////   }
////   else
////   {
////      return allocate(nNewSize / sizeof(TYPE), nGrowBy / sizeof(TYPE));
////   }
////}
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////::collection::count raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::allocate(::collection::count nNewSize, ::collection::count nGrowBy)
////{
////   ::collection::count countOld = get_count();
////   ASSERT_OK(this);
////   ASSERT(nNewSize >= 0);
////
////   if(nNewSize < 0 )
////      throw ::exception(error_bad_argument);
////
////   if (nGrowBy >= 0)
////      m_countAddUp = nGrowBy;  // set aaa_memory_new int_size
////
////   if (nNewSize == 0)
////   {
////      // shrink to nothing
////      if (m_begin != nullptr)
////      {
//////         for( int i = 0; i < m_nSize; i++ )
//////            (m_begin + i)->~TYPE();
////         delete[] (unsigned char*)m_begin;
////         m_begin = nullptr;
////      }
////      m_nSize = m_countAllocation = 0;
////   }
////   else if (m_begin == nullptr)
////   {
////      // create buffer big enough to hold number of requested elements or
////      // m_countAddUp elements, whichever is larger.
////#ifdef SIZE_T_MAX
////      if(nNewSize > SIZE_T_MAX/sizeof(TYPE))
////         throw ::exception(error_no_memory);
////      ASSERT(nNewSize <= SIZE_T_MAX/sizeof(TYPE));    // no overflow
////#endif
////      ::collection::count nAllocSize = maximum(nNewSize, m_countAddUp);
//////
////      m_begin = (TYPE*) __allocate< unsigned char[(size_t)nAllocSize * sizeof >(TYPE)];
////      //memory_set((void *)m_begin, 0, (size_t)nAllocSize * sizeof(TYPE));
//////      for( ::collection::index i = 0; i < nNewSize; i++ )
////  //       ::__allocate< ( (void *) >( m_begin + i ) ) TYPE;
//////
////      m_nSize = nNewSize;
////      m_countAllocation = nAllocSize;
////   }
////   else if (nNewSize <= m_countAllocation)
////   {
////      // it fits
////      if (nNewSize > m_nSize)
////      {
////         // initialize the ___new elements
//////         memory_set((void *)(m_begin + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
//////         for( int i = 0; i < nNewSize-m_nSize; i++ )
//////
//////            ::__allocate< ( (void *) >( m_begin + m_nSize + i ) ) TYPE;
//////
////      }
////      else if (m_nSize > nNewSize)
////      {
////         // destroy the old elements
//////         for( int i = 0; i < m_nSize-nNewSize; i++ )
////  //          (m_begin + nNewSize + i)->~TYPE();
////      }
////      m_nSize = nNewSize;
////   }
////   else
////   {
////      // otherwise, grow aaa_base_array
////      nGrowBy = m_countAddUp;
////      if (nGrowBy == 0)
////      {
////         // heuristically determine growth when nGrowBy == 0
////         //  (this avoids heap fragmentation in many situations)
////         nGrowBy = m_nSize / 8;
////         nGrowBy = (nGrowBy < 4) ? 4 : ((nGrowBy > 1024) ? 1024 : nGrowBy);
////      }
////      ::collection::count nNewMax;
////      if (nNewSize < m_countAllocation + nGrowBy)
////         nNewMax = m_countAllocation + nGrowBy;  // granularity
////      else
////         nNewMax = nNewSize;  // no slush
////
////      ASSERT(nNewMax >= m_countAllocation);  // no wrap around
////
////      if(nNewMax  < m_countAllocation)
////         throw ::exception(error_bad_argument);
////
////#ifdef SIZE_T_MAX
////      ASSERT(nNewMax <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
////#endif
////
////      TYPE* pNewData = (TYPE*) __allocate< unsigned char[(size_t)nNewMax * sizeof >(TYPE)];
////
////
////      // copy ___new data from old
////      ::safe_memory_copy(pNewData, (size_t)nNewMax * sizeof(TYPE),
////         m_begin, (size_t)m_nSize * sizeof(TYPE));
////
////      // construct remaining elements
////      ASSERT(nNewSize > m_nSize);
//////      memory_set((void *)(pNewData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
//////      for( int i = 0; i < nNewSize-m_nSize; i++ )
//////
//////         ::__allocate< ( (void *) >( pNewData + m_nSize + i ) ) TYPE;
//////
////      // get rid of old stuff (note: no destructors called)
////      delete[] (unsigned char*)m_begin;
////      m_begin = pNewData;
////      m_nSize = nNewSize;
////      m_countAllocation = nNewMax;
////   }
////   return countOld;
////}
////
//
////
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////void raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::free_extra()
////{
////   ASSERT_OK(this);
////
////   if (m_nSize != m_countAllocation)
////   {
////      // shrink to desired int_size
////#ifdef SIZE_T_MAX
////      ASSERT(m_nSize <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
////#endif
////      TYPE* pNewData = nullptr;
////      if (m_nSize != 0)
////      {
////         pNewData = (TYPE*) __allocate< unsigned char[m_nSize * sizeof >(TYPE)];
////         // copy ___new data from old
////         ::safe_memory_copy(pNewData, m_nSize * sizeof(TYPE),
////            m_begin, m_nSize * sizeof(TYPE));
////      }
////
////      // get rid of old stuff (note: no destructors called)
////      delete[] (unsigned char*)m_begin;
////      m_begin = pNewData;
////      m_countAllocation = m_nSize;
////   }
////}
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////void base_array < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::set_at_grow(::collection::index nIndex, ARG_TYPE newElement)
////{
////   //ASSERT_OK(this);
////   //ASSERT(nIndex >= 0);
////
////   if(nIndex < 0)
////      throw ::exception(error_bad_argument);
////
////   if (nIndex >= this->m_nSize)
////      this->allocate(nIndex+1, -1);
////   get_data()[nIndex] = newElement;
////}
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline TYPE raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::get_at_grow(::collection::index nIndex)
//{
//   return element_at_grow(nIndex);
//}
//
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////inline TYPE & raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::element_at_grow(::collection::index nIndex)
////{
////   if (nIndex >= this->m_nSize)
////      this->allocate(nIndex+1, -1);
////   return get_data()[nIndex];
////}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//::collection::index raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::insert_at(::collection::index nIndex, ARG_TYPE newElement, ::collection::count nCount /*=1*/)
//{
//
//   return base_array < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::insert_at(nIndex, newElement,nCount);
//
//}
//
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////::collection::index raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::insert_at(::collection::index nStartIndex, raw_array_base * pNewArray)
////{
////   ASSERT_OK(this);
////   ASSERT(pNewArray != nullptr);
////   ASSERT_OK(pNewArray);
////   ASSERT(nStartIndex >= 0);
////
////   if(pNewArray == nullptr || nStartIndex < 0)
////      throw ::exception(error_bad_argument);
////
////   if (pNewArray->get_size() > 0)
////   {
////      insert_at(nStartIndex, pNewArray->element_at(0), pNewArray->get_size());
////      for (::collection::index i = 1; i < pNewArray->get_size(); i++)
////         insert_at(nStartIndex + i, pNewArray->element_at(i));
////   }
////
////   return nStartIndex;
////
////}
//
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////void raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::dump(dump_context & dumpcontext) const
////{
////
////   matter::dump(dumpcontext);
////
////   dumpcontext << "with " << this->m_nSize << " elements";
////
////   if (dumpcontext.GetDepth() > 0)
////   {
////
////      dumpcontext << "\n";
////
////      dump_elements<TYPE>(dumpcontext,get_data(), this->m_nSize);
////
////   }
////
////   dumpcontext << "\n";
////
////}
//
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////void raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::assert_ok() const
////{
////
////   matter::assert_ok();
////
////
////   if (get_data() == nullptr)
////   {
////
////      ASSERT(this->m_nSize == 0);
////      ASSERT(this->m_countAllocation >= 0);
////
////   }
////   else
////   {
////
////      ASSERT(this->m_nSize >= 0);
////      ASSERT(this->m_countAllocation >= 0);
////      ASSERT(this->m_nSize <= this->m_countAllocation);
////      ASSERT(is_memory_segment_ok(this->m_begin, (::memsize_cast) this->m_countAllocation * sizeof(TYPE)));
////
////   }
////
////}
//
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////typename raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::iterator raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::erase(iterator pos)
////{
////   if(pos.m_parray == this)
////   {
////      this->erase_at(pos.m_i);
////      return iterator(pos.m_i, this);
////   }
////   else
////   {
////      return this->end();
////   }
////}
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////typename  raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::iterator raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::erase(iterator begin, iterator last)
////{
////   if(begin.m_parray == this && last.m_parray == this)
////   {
////      if(begin.m_i >= 0 && begin.m_i < this->get_size())
////      {
////         ::collection::count nCount = last.m_i - begin.m_i;
////         erase_at(begin.m_i, nCount);
////         return iterator(begin.m_i, this);
////      }
////      else
////      {
////         return this->end();
////      }
////   }
////   else
////   {
////      return this->end();
////   }
////}
////
////
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//::collection::index raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_find_first(TYPE *point, ::collection::index find, ::collection::index last) const
//{
//   if(find < 0)
//      find += this->get_count();
//   if(last < 0)
//      last += this->get_count();
//   for(; find <= last; find++)
//   {
//      if(&this->element_at(find) == point)
//         return find;
//   }
//   return -1;
//}
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//::collection::index raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::find_first(ARG_TYPE t, ::collection::index ( * pfnCompare )(ARG_TYPE, ARG_TYPE), ::collection::index find, ::collection::index last) const
//
//{
//   if(find < 0)
//      find += this->get_count();
//   if(last < 0)
//      last += this->get_count();
//   for(; find <= last; find++)
//   {
//      if(pfnCompare((ARG_TYPE)this->element_at(find), (ARG_TYPE)t) == 0)
//
//         return find;
//   }
//   return -1;
//}
//
//
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > & raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator += (const raw_array_base & a)
//{
//
//   if(&a == this)
//   {
//      raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > aCopy(a);
//      add(aCopy);
//   }
//   else
//   {
//      add(a);
//   }
//   return *this;
//
//}
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator + (const raw_array_base & a) const
//{
//   raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > aNew(*this);
//   aNew += a;
//   return a;
//}
//
//
//
//
//
//
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > & raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator =(raw_array_base && a)
//{
//
//   return transfer(::transfer(a));
//
//}
//
//
//
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > & raw_array_base < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::transfer(raw_array_base && a)
//{
//
//   if (&a != this)
//   {
//      this->destroy();
//
//      this->m_countAddUp = a.m_countAddUp;
//      this->m_begin = a.m_begin;
//      this->m_nSize = a.m_nSize;
//      this->m_countAllocation = a.m_countAllocation;
//
//      a.m_begin = nullptr;
//
//   }
//
//   return *this;
//
//}
//
//
//



