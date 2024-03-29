#pragma once


#include "array_base.h"


// raw_array_non_particle is an array that does not call constructors or destructor in elements
// array is an array that call only copy constructor and destructor in elements
// array is an array that call default constructors, copy constructs and destructors in elements


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
class raw_array_non_particle :
   public array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >
{
public:


   typedef TYPE BASE_TYPE;
   typedef ARG_TYPE BASE_ARG_TYPE;
   typedef raw_array_non_particle < TYPE,ARG_TYPE > BASE_ARRAY;
   using ARRAY_BASE = array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >;
   using iterator = typename ARRAY_BASE::iterator;
   using const_iterator = typename ARRAY_BASE::const_iterator;


   raw_array_non_particle() {}
   raw_array_non_particle(std::initializer_list < TYPE > initializer_list) : ARRAY_BASE(initializer_list) {}
   raw_array_non_particle(const raw_array_non_particle <TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > & a);
   raw_array_non_particle(raw_array_non_particle <TYPE,ARG_TYPE, TYPED, MEMORY, t_etypeContainer > && a) noexcept;
   raw_array_non_particle(ARG_TYPE t, ::count n);
   raw_array_non_particle(::range < const_iterator > constrange) : ARRAY_BASE(constrange) {}
   raw_array_non_particle(const_iterator begin, const_iterator end) : ARRAY_BASE(begin, end) { }
   raw_array_non_particle(const TYPE * ptypea, ::count n);
   virtual ~raw_array_non_particle();


   //// void assert_ok() const override;
   //// void dump(dump_context & dumpcontext) const override;




   void erase_last();

   ::count erase_all();
   void clear();




   // Accessing elements
   inline const TYPE& get_at(::index nIndex) const;
   inline TYPE& get_at(::index nIndex);
   inline void set_at(::index nIndex, ARG_TYPE newElement);


   // Direct Access to the matter data (may return nullptr)
   inline const TYPE* get_data() const;
   inline TYPE* get_data();

   // Potentially growing the raw_array_non_particle
   //void set_at_grow(::index nIndex, ARG_TYPE newElement);
   //TYPE & element_at_grow(::index nIndex);
   TYPE get_at_grow(::index nIndex);
   ::index add(ARG_TYPE newElement) { return add_item(newElement); }
   ::index add_item(ARG_TYPE newElement);
   ::index append(const TYPE * p, ::count c);
   ::index append(const raw_array_non_particle& src);
   virtual TYPE * add_new(::count count);
   virtual TYPE & add_new();
   //::index append(const raw_array_non_particle& src);
   //void copy(const raw_array_non_particle& src);


   inline TYPE pop(::index i = -1);
   inline ::index push(ARG_TYPE newElement);
   inline void pop_back(::index i = -1);



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
   //inline const TYPE& operator[](::index nIndex) const;
   //inline TYPE& operator[](::index nIndex);

    //that transfer elements around
   TYPE & insert_at(::index nIndex, ARG_TYPE newElement, ::count nCount = 1);
   //::index erase_at(::index nIndex, ::count nCount = 1);
   //void _001RemoveIndexes(index_array & ia);
   //void erase_indexes(const index_array & ia); // erase indexes from ::index raw_array_non_particle upper bound to ::index raw_array_non_particle lower bound
   //void erase_descending_indexes(const index_array & ia); // erase indexes from ::index raw_array_non_particle lower bound to ::index raw_array_non_particle upper bound
   //::index insert_at(::index nStartIndex, raw_array_non_particle* pNewArray);
   //void __swap(::index index1, ::index index2);

   raw_array_non_particle & operator = (const raw_array_non_particle & src);

   ::index find_first(ARG_TYPE t, ::index (* pfnCompare)(ARG_TYPE, ARG_TYPE), ::index start = 0, ::index last = -1) const;

   ::index raw_find_first(TYPE * p, ::index first = 0, ::index last = -1) const;

   template < class DERIVED >
   ::index find_first(DERIVED * p, ::index first = 0, ::index last = -1)
   {
      return raw_find_first(dynamic_cast < TYPE * > (p), first, last);
   }

   template < class ARRAY >
   ::count get_array(ARRAY & a, ::index iStart = 0, ::count nCount = -1)
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


   raw_array_non_particle & operator += (const raw_array_non_particle & a);
   raw_array_non_particle operator + (const raw_array_non_particle & a) const;


   using array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator =;
   inline raw_array_non_particle & operator = (raw_array_non_particle && a);
   inline raw_array_non_particle & transfer(raw_array_non_particle && a);


   //operator TYPE *() { return this->m_begin;  }
   //operator const TYPE *() const { return this->m_begin; }
   
   
   
   operator ::count () const { return this->get_count(); }


};


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
class raw_array :
   virtual public ::particle,
   public raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >
{
public:


   raw_array() : raw_array_non_particle< TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >() {}
   template < typename ...Args >
   raw_array(Args&&... args) :
      raw_array_non_particle< TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >(::std::forward < Args >(args)...)
   {
   }
   raw_array(std::initializer_list < TYPE > initializer_list) : raw_array_non_particle< TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >(initializer_list) {}


};


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline ::count raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::erase_all()
{
   
   return this->allocate(0, false, false);
   
}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
void raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::clear()
{
   
   erase_all();
   
}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline void raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::erase_last()
{

   this->erase_at(this->get_upper_bound());

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline TYPE& raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::get_at(::index nIndex)
{

   return get_data()[nIndex];
   
}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline const TYPE& raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::get_at(::index nIndex) const
{

   return get_data()[nIndex];

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline void raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::set_at(::index nIndex, ARG_TYPE newElement)
{

   get_data()[nIndex] = newElement;

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline const TYPE* raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::get_data() const
{

   return (const TYPE*)this->m_begin;

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline TYPE* raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::get_data()
{

   return (TYPE*)this->m_begin;

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline ::index raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::add_item(ARG_TYPE newElement)
{

   ::index nIndex = this->size();

   this->set_at_grow(nIndex, newElement);

   return nIndex;

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline ::index raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::append(const TYPE * p, ::count c)
{

   return ARRAY_BASE::append(p, c);

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline ::index raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::append(const raw_array_non_particle & src)
{

   return ARRAY_BASE::append(src);

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline TYPE * raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::add_new(::count count)
{

   this->allocate(this->size() + count, false, true);

   return this->m_begin + (this->get_size() - count);

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline TYPE & raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::add_new()
{

   this->allocate(this->size() + 1, false, true);

   return this->last();

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline TYPE raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::pop(::index n)
{

   ::index i = this->get_upper_bound(n);

   TYPE t = this->element_at(i);

   this->erase_at(i);

   return t;

}

template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline void raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::pop_back(::index n)
{

   this->erase_at(this->get_upper_bound(n));

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline ::index raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::push(ARG_TYPE newElement)
{

   return this->index_of(&insert_at(this->size(), newElement));

}

//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline void raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::add(ARG_TYPE newElement, ::index n)
//{
//   insert_at(this->get_upper_bound(n), newElement);
//}


//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline const TYPE& raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator[](::index nIndex) const
//{
//
//   return this->element_at(nIndex);
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline TYPE& raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator[](::index nIndex)
//{
//
//   return this->element_at(nIndex);
//
//}


//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline void raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::__swap(::index index1, ::index index2)
//{
//   TYPE t = get_data()[index1];
//   get_data()[index1] = get_data()[index2];
//   get_data()[index2] = t;
//}

template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > & raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator = (const raw_array_non_particle & src)
{
   if(&src != this)
   {
      this->copy(src);
   }
   return *this;
}



// out-of-line functions



//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_array_non_particle(::std::initializer_list < TYPE >  l)
//{
//   for(auto & item : l)
//   {
//      add((ARG_TYPE) item);
//   }
//}



template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_array_non_particle(const raw_array_non_particle <TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > & array):
   ARRAY_BASE(array)
{

}

template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_array_non_particle(raw_array_non_particle <TYPE,ARG_TYPE, TYPED, MEMORY, t_etypeContainer > && a) noexcept :
   ARRAY_BASE(::transfer(a))
{

}

//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >:: raw_array_non_particle(::count n)
//{
//   this->allocate(n);
//}

template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_array_non_particle(ARG_TYPE t, ::count n)
{
   insert_at(0, t, n);
}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_array_non_particle(const TYPE * ptypea, ::count n)
{

   this->set_size(n);

   memcpy(this->m_begin, ptypea, this->length_in_bytes());

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::~raw_array_non_particle()
{

   this->destroy();

}

//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//void raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::destroy()
//{
//   if (m_begin != nullptr)
//   {
//      for( i32 i = 0; i < m_nSize; i++ )
//         destruct_element(m_begin + i)->~TYPE();
//      delete[] (::u8*)m_begin;
//      m_begin     = nullptr;
//      m_nSize     = 0;
//      m_countAllocation  = 0;
//   }
//
//}


//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//::count raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::set_size(::count nNewSize, ::count nGrowBy)
//{
//   return allocate(nNewSize, nGrowBy);
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//::count raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::resize(::count nNewSize, ::count nGrowBy)
//{
//   return allocate(nNewSize, nGrowBy);
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//::count raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::allocate_in_bytes(::count nNewSize, ::count nGrowBy)
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
//::count raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::allocate(::count nNewSize, ::count nGrowBy)
//{
//   ::count countOld = get_count();
//   ASSERT_VALID(this);
//   ASSERT(nNewSize >= 0);
//
//   if(nNewSize < 0 )
//      throw ::exception(error_bad_argument);
//
//   if (nGrowBy >= 0)
//      m_countAddUp = nGrowBy;  // set aaa_memory_new size_i32
//
//   if (nNewSize == 0)
//   {
//      // shrink to nothing
//      if (m_begin != nullptr)
//      {
////         for( i32 i = 0; i < m_nSize; i++ )
////            (m_begin + i)->~TYPE();
//         delete[] (::u8*)m_begin;
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
//      ::count nAllocSize = maximum(nNewSize, m_countAddUp);
////
//      m_begin = (TYPE*) __new< ::u8[(size_t)nAllocSize * sizeof >(TYPE)];
//      //memory_set((void *)m_begin, 0, (size_t)nAllocSize * sizeof(TYPE));
////      for( ::index i = 0; i < nNewSize; i++ )
//  //       ::__new< ( (void *) >( m_begin + i ) ) TYPE;
////
//      m_nSize = nNewSize;
//      m_countAllocation = nAllocSize;
//   }
//   else if (nNewSize <= m_countAllocation)
//   {
//      // it fits
//      if (nNewSize > m_nSize)
//      {
//         // initialize the new elements
////         memory_set((void *)(m_begin + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
////         for( i32 i = 0; i < nNewSize-m_nSize; i++ )
////
////            ::__new< ( (void *) >( m_begin + m_nSize + i ) ) TYPE;
////
//      }
//      else if (m_nSize > nNewSize)
//      {
//         // destroy the old elements
////         for( i32 i = 0; i < m_nSize-nNewSize; i++ )
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
//      ::count nNewMax;
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
//      TYPE* pNewData = (TYPE*) __new< ::u8[(size_t)nNewMax * sizeof >(TYPE)];
//
//
//      // copy new data from old
//      ::acme::memcpy_s(pNewData, (size_t)nNewMax * sizeof(TYPE),
//         m_begin, (size_t)m_nSize * sizeof(TYPE));
//
//      // construct remaining elements
//      ASSERT(nNewSize > m_nSize);
////      memory_set((void *)(pNewData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
////      for( i32 i = 0; i < nNewSize-m_nSize; i++ )
////
////         ::__new< ( (void *) >( pNewData + m_nSize + i ) ) TYPE;
////
//      // get rid of old stuff (note: no destructors called)
//      delete[] (::u8*)m_begin;
//      m_begin = pNewData;
//      m_nSize = nNewSize;
//      m_countAllocation = nNewMax;
//   }
//   return countOld;
//}
//

//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//void raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::free_extra()
//{
//   ASSERT_VALID(this);
//
//   if (m_nSize != m_countAllocation)
//   {
//      // shrink to desired size_i32
//#ifdef SIZE_T_MAX
//      ASSERT(m_nSize <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
//#endif
//      TYPE* pNewData = nullptr;
//      if (m_nSize != 0)
//      {
//         pNewData = (TYPE*) __new< ::u8[m_nSize * sizeof >(TYPE)];
//         // copy new data from old
//         ::acme::memcpy_s(pNewData, m_nSize * sizeof(TYPE),
//            m_begin, m_nSize * sizeof(TYPE));
//      }
//
//      // get rid of old stuff (note: no destructors called)
//      delete[] (::u8*)m_begin;
//      m_begin = pNewData;
//      m_countAllocation = m_nSize;
//   }
//}

//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//void array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::set_at_grow(::index nIndex, ARG_TYPE newElement)
//{
//   //ASSERT_VALID(this);
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
inline TYPE raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::get_at_grow(::index nIndex)
{

   return this->element_at_grow(nIndex);

}


//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline TYPE & raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::element_at_grow(::index nIndex)
//{
//   if (nIndex >= this->m_nSize)
//      this->allocate(nIndex+1, -1);
//   return get_data()[nIndex];
//}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
TYPE & raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::insert_at(::index nIndex, ARG_TYPE newElement, ::count nCount /*=1*/)
{

   return array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::insert_at(nIndex, newElement,nCount);

}


//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//::index raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::insert_at(::index nStartIndex, raw_array_non_particle * pNewArray)
//{
//   ASSERT_VALID(this);
//   ASSERT(pNewArray != nullptr);
//   ASSERT_VALID(pNewArray);
//   ASSERT(nStartIndex >= 0);
//
//   if(pNewArray == nullptr || nStartIndex < 0)
//      throw ::exception(error_bad_argument);
//
//   if (pNewArray->get_size() > 0)
//   {
//      insert_at(nStartIndex, pNewArray->element_at(0), pNewArray->get_size());
//      for (::index i = 1; i < pNewArray->get_size(); i++)
//         insert_at(nStartIndex + i, pNewArray->element_at(i));
//   }
//
//   return nStartIndex;
//
//}


//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//void raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::dump(dump_context & dumpcontext) const
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
//void raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::assert_ok() const
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
//typename raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::iterator raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::erase(iterator pos)
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
//typename  raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::iterator raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::erase(iterator begin, iterator last)
//{
//   if(begin.m_parray == this && last.m_parray == this)
//   {
//      if(begin.m_i >= 0 && begin.m_i < this->get_size())
//      {
//         ::count nCount = last.m_i - begin.m_i;
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
::index raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_find_first(TYPE *p, ::index find, ::index last) const
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
::index raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::find_first(ARG_TYPE t, ::index ( * pfnCompare )(ARG_TYPE, ARG_TYPE), ::index find, ::index last) const

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
raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > & raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator += (const raw_array_non_particle & a)
{

   if(&a == this)
   {
      raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > aCopy(a);
      append(aCopy);
   }
   else
   {
      append(a);
   }
   return *this;

}

template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator + (const raw_array_non_particle & a) const
{
   raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > aNew(*this);
   aNew += a;
   return a;
}








template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > & raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator =(raw_array_non_particle && a)
{

   return transfer(::transfer(a));

}





template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > & raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::transfer(raw_array_non_particle && a)
{

   if (&a != this)
   {
      this->destroy();

      this->m_countAddUp = a.m_countAddUp;
      this->m_begin = a.m_begin;
      this->m_end = a.m_end;
      this->m_countAllocation = a.m_countAllocation;

      a.m_begin = nullptr;
      a.m_end = nullptr;
      a.m_countAllocation = 0;

   }

   return *this;

}





//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline ::count raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::erase_all()
//{
//   return this->allocate(0, -1);
//}
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//void raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::
//clear()
//{
//   erase_all();
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline void raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::erase_last()
//{
//
//   this->erase_at(this->get_upper_bound());
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline TYPE& raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::get_at(::index nIndex)
//{
//
//   return get_data()[nIndex];
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline const TYPE& raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::get_at(::index nIndex) const
//{
//
//   return get_data()[nIndex];
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline void raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::set_at(::index nIndex, ARG_TYPE newElement)
//{
//
//   get_data()[nIndex] = newElement;
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline const TYPE* raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::get_data() const
//{
//
//   return (const TYPE*)this->m_begin;
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline TYPE* raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::get_data()
//{
//
//   return (TYPE*)this->m_begin;
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline ::index raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::add(ARG_TYPE newElement)
//{
//
//   ::index nIndex = (::index_cast ) this->m_nSize;
//
//   set_at_grow(nIndex, newElement);
//
//   return nIndex;
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline ::index raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::add(const raw_array_non_particle & src)
//{
//
//   return this->append(src);
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline ::index raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::add_new(::count count)
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
//inline TYPE & raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::add_new()
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
//inline TYPE raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::pop(::index n)
//{
//
//   ::index i = this->get_upper_bound(n);
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
//inline void raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::pop_back(::index n)
//{
//
//   this->erase_at(this->get_upper_bound(n));
//
//}
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline ::index raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::push(ARG_TYPE newElement, ::index n)
//{
//   return insert_at(this->get_upper_bound(n), newElement);
//}
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline void raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::add(ARG_TYPE newElement, ::index n)
//{
//   insert_at(this->get_upper_bound(n), newElement);
//}
//
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////inline const TYPE& raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator[](::index nIndex) const
////{
////
////   return this->element_at(nIndex);
////
////}
////
////
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////inline TYPE& raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator[](::index nIndex)
////{
////
////   return this->element_at(nIndex);
////
////}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline void raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::__swap(::index index1, ::index index2)
//{
//   TYPE t = get_data()[index1];
//   get_data()[index1] = get_data()[index2];
//   get_data()[index2] = t;
//}
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > & raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator = (const raw_array_non_particle & src)
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
//raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_array_non_particle(::particle * pparticle)
////:
////::matter(pparticle)
//{
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_array_non_particle(::std::initializer_list < TYPE >  l)
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
//raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_array_non_particle(const raw_array_non_particle <TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > & a)// :
//// matter(a.get_app())
//{
//   ::array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator = (a);
//}
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_array_non_particle(raw_array_non_particle <TYPE,ARG_TYPE, TYPED, MEMORY, t_etypeContainer > && a) //:
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
//raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >:: raw_array_non_particle(::count n)
//{
//   this->allocate(n);
//}
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_array_non_particle(ARG_TYPE t, ::count n)
//{
//   insert_at(0, t, n);
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_array_non_particle(TYPE * ptypea, ::count n)
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
//raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::~raw_array_non_particle()
//{
//
//   this->destroy();
//
//}
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////void raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::destroy()
////{
////   if (m_begin != nullptr)
////   {
////      for( i32 i = 0; i < m_nSize; i++ )
////         destruct_element(m_begin + i)->~TYPE();
////      delete[] (::u8*)m_begin;
////      m_begin     = nullptr;
////      m_nSize     = 0;
////      m_countAllocation  = 0;
////   }
////
////}
//
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////::count raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::set_size(::count nNewSize, ::count nGrowBy)
////{
////   return allocate(nNewSize, nGrowBy);
////}
////
////
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////::count raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::resize(::count nNewSize, ::count nGrowBy)
////{
////   return allocate(nNewSize, nGrowBy);
////}
////
////
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////::count raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::allocate_in_bytes(::count nNewSize, ::count nGrowBy)
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
////::count raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::allocate(::count nNewSize, ::count nGrowBy)
////{
////   ::count countOld = get_count();
////   ASSERT_VALID(this);
////   ASSERT(nNewSize >= 0);
////
////   if(nNewSize < 0 )
////      throw ::exception(error_bad_argument);
////
////   if (nGrowBy >= 0)
////      m_countAddUp = nGrowBy;  // set aaa_memory_new size_i32
////
////   if (nNewSize == 0)
////   {
////      // shrink to nothing
////      if (m_begin != nullptr)
////      {
//////         for( i32 i = 0; i < m_nSize; i++ )
//////            (m_begin + i)->~TYPE();
////         delete[] (::u8*)m_begin;
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
////      ::count nAllocSize = maximum(nNewSize, m_countAddUp);
//////
////      m_begin = (TYPE*) __new< ::u8[(size_t)nAllocSize * sizeof >(TYPE)];
////      //memory_set((void *)m_begin, 0, (size_t)nAllocSize * sizeof(TYPE));
//////      for( ::index i = 0; i < nNewSize; i++ )
////  //       ::__new< ( (void *) >( m_begin + i ) ) TYPE;
//////
////      m_nSize = nNewSize;
////      m_countAllocation = nAllocSize;
////   }
////   else if (nNewSize <= m_countAllocation)
////   {
////      // it fits
////      if (nNewSize > m_nSize)
////      {
////         // initialize the new elements
//////         memory_set((void *)(m_begin + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
//////         for( i32 i = 0; i < nNewSize-m_nSize; i++ )
//////
//////            ::__new< ( (void *) >( m_begin + m_nSize + i ) ) TYPE;
//////
////      }
////      else if (m_nSize > nNewSize)
////      {
////         // destroy the old elements
//////         for( i32 i = 0; i < m_nSize-nNewSize; i++ )
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
////      ::count nNewMax;
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
////      TYPE* pNewData = (TYPE*) __new< ::u8[(size_t)nNewMax * sizeof >(TYPE)];
////
////
////      // copy new data from old
////      ::acme::memcpy_s(pNewData, (size_t)nNewMax * sizeof(TYPE),
////         m_begin, (size_t)m_nSize * sizeof(TYPE));
////
////      // construct remaining elements
////      ASSERT(nNewSize > m_nSize);
//////      memory_set((void *)(pNewData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
//////      for( i32 i = 0; i < nNewSize-m_nSize; i++ )
//////
//////         ::__new< ( (void *) >( pNewData + m_nSize + i ) ) TYPE;
//////
////      // get rid of old stuff (note: no destructors called)
////      delete[] (::u8*)m_begin;
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
////void raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::free_extra()
////{
////   ASSERT_VALID(this);
////
////   if (m_nSize != m_countAllocation)
////   {
////      // shrink to desired size_i32
////#ifdef SIZE_T_MAX
////      ASSERT(m_nSize <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
////#endif
////      TYPE* pNewData = nullptr;
////      if (m_nSize != 0)
////      {
////         pNewData = (TYPE*) __new< ::u8[m_nSize * sizeof >(TYPE)];
////         // copy new data from old
////         ::acme::memcpy_s(pNewData, m_nSize * sizeof(TYPE),
////            m_begin, m_nSize * sizeof(TYPE));
////      }
////
////      // get rid of old stuff (note: no destructors called)
////      delete[] (::u8*)m_begin;
////      m_begin = pNewData;
////      m_countAllocation = m_nSize;
////   }
////}
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////void array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::set_at_grow(::index nIndex, ARG_TYPE newElement)
////{
////   //ASSERT_VALID(this);
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
//inline TYPE raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::get_at_grow(::index nIndex)
//{
//   return element_at_grow(nIndex);
//}
//
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////inline TYPE & raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::element_at_grow(::index nIndex)
////{
////   if (nIndex >= this->m_nSize)
////      this->allocate(nIndex+1, -1);
////   return get_data()[nIndex];
////}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//::index raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::insert_at(::index nIndex, ARG_TYPE newElement, ::count nCount /*=1*/)
//{
//
//   return array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::insert_at(nIndex, newElement,nCount);
//
//}
//
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////::index raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::insert_at(::index nStartIndex, raw_array_non_particle * pNewArray)
////{
////   ASSERT_VALID(this);
////   ASSERT(pNewArray != nullptr);
////   ASSERT_VALID(pNewArray);
////   ASSERT(nStartIndex >= 0);
////
////   if(pNewArray == nullptr || nStartIndex < 0)
////      throw ::exception(error_bad_argument);
////
////   if (pNewArray->get_size() > 0)
////   {
////      insert_at(nStartIndex, pNewArray->element_at(0), pNewArray->get_size());
////      for (::index i = 1; i < pNewArray->get_size(); i++)
////         insert_at(nStartIndex + i, pNewArray->element_at(i));
////   }
////
////   return nStartIndex;
////
////}
//
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
////void raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::dump(dump_context & dumpcontext) const
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
////void raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::assert_ok() const
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
////typename raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::iterator raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::erase(iterator pos)
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
////typename  raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::iterator raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::erase(iterator begin, iterator last)
////{
////   if(begin.m_parray == this && last.m_parray == this)
////   {
////      if(begin.m_i >= 0 && begin.m_i < this->get_size())
////      {
////         ::count nCount = last.m_i - begin.m_i;
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
//::index raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::raw_find_first(TYPE *point, ::index find, ::index last) const
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
//::index raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::find_first(ARG_TYPE t, ::index ( * pfnCompare )(ARG_TYPE, ARG_TYPE), ::index find, ::index last) const
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
//raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > & raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator += (const raw_array_non_particle & a)
//{
//
//   if(&a == this)
//   {
//      raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > aCopy(a);
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
//raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator + (const raw_array_non_particle & a) const
//{
//   raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > aNew(*this);
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
//inline raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > & raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::operator =(raw_array_non_particle && a)
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
//inline raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer > & raw_array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY,t_etypeContainer >::transfer(raw_array_non_particle && a)
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



