#pragma once


#include "acme/prototype/collection/array_base.h"
#include "acme/prototype/collection/copy_elements.h"



template < class TYPE, class ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
class array_non_particle :
   public ::array_base_quantum < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >
{
public:


   using THIS_ARRAY = array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >;


   using BASE_TYPE = TYPE;
   using BASE_ARG_TYPE = ARG_TYPE;


   using BASE_ARRAY = ::array_base_quantum < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >;


   using iterator = typename BASE_ARRAY::iterator;
   using const_iterator = typename BASE_ARRAY::const_iterator;

   using ITERATOR_RANGE = typename BASE_ARRAY::array_range;

   using CONST_RANGE = typename BASE_ARRAY::CONST_RANGE;
   using CONST_RAW_RANGE = typename BASE_ARRAY::CONST_RAW_RANGE;

   using BASE_ARRAY::BASE_ARRAY;

   array_non_particle();
   array_non_particle(nullptr_t) : array_non_particle() {}
   array_non_particle(std::initializer_list < TYPE > initializer_list) : BASE_ARRAY(initializer_list) {}
   //array_non_particle(const_iterator begin, const_iterator end) : BASE_ARRAY(begin, end) {}
   array_non_particle(const array_non_particle & a);
   array_non_particle(enum_create_new, ::collection::count n);
   array_non_particle(::collection::count n);
   array_non_particle(::collection::count n, ARG_TYPE t);
   array_non_particle(::range < const_iterator > constrange) : BASE_ARRAY(constrange) {}
   template < primitive_integral INTEGRAL >
   array_non_particle(const_iterator begin, INTEGRAL count) : BASE_ARRAY(begin, count) {}
   array_non_particle(const_iterator begin, const_iterator end) : BASE_ARRAY(begin, end) {}
   array_non_particle(array_non_particle && a) noexcept : array_base_quantum < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >(::transfer(a)) { }
   ~array_non_particle() override;


   array_non_particle & operator = (const array_non_particle & array_non_particle) { BASE_ARRAY::operator=(array_non_particle); return *this; }
   array_non_particle & operator = (array_non_particle && array_non_particle) { BASE_ARRAY::operator=(::transfer(array_non_particle)); return *this; }
   array_non_particle & operator = (std::initializer_list < TYPE > initializer_list)
   {
      this->clear();
      for (auto & item : initializer_list) this->add(item);
      return *this;
   }



   inline const TYPE & get_at(::collection::index nIndex) const;
   inline TYPE & get_at(::collection::index nIndex);
   inline void set_at(::collection::index nIndex, ARG_TYPE newElement);


   //inline const TYPE * data() const { return this->m_begin; }
   //inline TYPE * data() { return this->m_begin; }

   // must not be overloaded!!
   inline ::collection::index add_item(ARG_TYPE newElement);


   inline ::collection::index add(ARG_TYPE newElement);
   inline ::collection::index add_copies(ARG_TYPE newElement, ::collection::count cCopies)
   {
      ::collection::index iLastInsertIndex = -1;
      while (cCopies > 0)
      {

         iLastInsertIndex =add_item(newElement);

         cCopies--;

      }

      return iLastInsertIndex;
   }
   ///inline ::collection::count append(const array_non_particle & src);


   //template < primitive_container CONTAINER >
   //inline ::collection::count append(const CONTAINER & container)
   //{

   //   return BASE_ARRAY::append(container);

   //}*/


   template < typename CONTAINER >
   inline array_non_particle appended_container(const CONTAINER & container)
   {

      auto array_non_particle = *this;

      array_non_particle.append_container(container);

      return ::transfer(array_non_particle);

   }





   inline void copy(const array_non_particle & src);

   inline TYPE & add_new(::collection::count c = 1);


   inline TYPE & add_new_at(::collection::index iIndex, ::collection::count count = 1);


   inline array_non_particle & operator << (ARG_TYPE newElement) { add(newElement); return *this; }


   //that transfer elements around
  //inline ::collection::index insert_at(::collection::index nIndex, ARG_TYPE newElement, ::collection::count nCount = 1);
  //void _001RemoveIndexes(index_array & ia);
  //void erase_indexes(const index_array & ia); // erase indexes from ::collection::index array_non_particle upper bound to ::collection::index array_non_particle lower bound
  //void erase_descending_indexes(const index_array & ia); // erase indexes from ::collection::index array_non_particle lower bound to ::collection::index array_non_particle upper bound
  //::collection::index insert_at(::collection::index nStartIndex, array_non_particle* pNewArray);

   using array_base_quantum < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::operator=;
   //inline array_non_particle & operator = (const array_non_particle & src);
   //inline array_non_particle & operator = (array_non_particle && a);



   //inline ::collection::index find_first(ARG_TYPE t, ::collection::index (* pfnCompare)(ARG_TYPE, ARG_TYPE), ::collection::index start = 0, ::collection::index last = -1) const;

   //::collection::index raw_find_first(TYPE * point, ::collection::index first = 0, ::collection::index last = -1) const;

   //template < class DERIVED >
   //inline ::collection::index find_first(DERIVED * point, ::collection::index first = 0, ::collection::index last = -1)
   //{
   //   return raw_find_first(dynamic_cast < TYPE * > (point), first, last);
   //}

   template < class ARRAY >
   inline ::collection::count slice(ARRAY & a, ::collection::index iStart = 0, ::collection::count nCount = -1)
   {

      ::collection::count ca = 0;

      ::collection::index iEnd;

      if (nCount < 0)
         iEnd = this->get_upper_bound(nCount);
      else
         iEnd = iStart + nCount - 1;

      for (::collection::index i = iStart; i <= iEnd; i++)
      {

         a.add(this->element_at(i));
         ca++;

      }

      return ca;

   }

   template < typename ARRAY >
   inline ARRAY slice(::collection::index iStart = 0, ::collection::count nCount = -1)
   {

      ARRAY a;

      slice(a, iStart, nCount);

      return a;

   }

   //operator TYPE *() {return this->m_begin;}
   //operator const TYPE *() const {return this->m_begin;}

   template < primitive_container CONTAINER >
   inline array_non_particle & operator += (const CONTAINER & container);

   template < typename... T >
   void fadd(T... a)
   {

      add(TYPE(a...));

   }

   template < typename PREDICATE >
   ::collection::index predicate_index_index(::collection::index iPredicateIndex, PREDICATE predicate)
   {

      if (iPredicateIndex < 0)
      {

         return -1;

      }

      for (::collection::index iIndex = 0; iIndex < this->get_size(); iIndex++)
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
   ::collection::index index_predicate_index(::collection::index iIndex, PREDICATE predicate)
   {

      ::collection::index iPredicateIndex = -1;

      ::collection::index i = 0;

      for (; i <= iIndex && i < this->get_size(); i++)
      {

         auto & element = this->element_at(i);

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
   array_base_quantum< TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > & copy_iter(const ITERABLE & iterable)
   {

      this->set_size(0, maximum(__iterable_count(iterable), 17));

      for (auto & item : iterable)
      {

         add_item(item);

      }

      return *this;

   }

};


template < typename CONTAINER, typename T > 
auto container_predicate_get(const CONTAINER & source, const ::function < bool(const T & t) >& predicate)
{

   CONTAINER result;

   for (auto& item : source)
   {

      if (predicate(item))
      {

         result.add(item);

      }

   }

   return ::transfer(result);

}


template < class TYPE, class ARG_TYPE = const TYPE & >
class nodefctr_array :
   public array_non_particle < TYPE, ARG_TYPE, ::constructor::nodef < TYPE > >
{
public:


   nodefctr_array(::collection::count nGrowBy = 32) : array_non_particle < TYPE, ARG_TYPE, ::constructor::nodef < TYPE > >(nGrowBy) {}
   nodefctr_array(const array_non_particle <TYPE, ARG_TYPE> & a) : array_non_particle < TYPE, ARG_TYPE, ::constructor::nodef < TYPE >  >(a) {}
   //nodefctr_array(::collection::count n) : array_non_particle < TYPE, ARG_TYPE, ::constructor::nodef < TYPE > > (n) {}
   virtual ~nodefctr_array() {}

};

template < class TYPE, class ARG_TYPE, class TYPED, class MEMORY, ::enum_type t_etypeContainer >
class array :
   virtual public ::particle,
   public array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >
{
public:

   using BASE_ARRAY = array_non_particle< TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >;

   //array() : array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >() {}
   //template < typename ...Args >
   //array(Args&&... args) :
   //   array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >(::std::forward < Args >(args)...)
   //{
   //}
   array() {}
   array(nullptr_t) : BASE_ARRAY() {}
   array(std::initializer_list < TYPE > initializer_list) : BASE_ARRAY(initializer_list) {}
   //array_non_particle(const_iterator begin, const_iterator end) : BASE_ARRAY(begin, end) {}
   array(const BASE_ARRAY & a) : BASE_ARRAY(a) {}
   array(BASE_ARRAY && a) noexcept : BASE_ARRAY(::transfer(a)) { }
   array(enum_create_new, ::collection::count n) : BASE_ARRAY(e_create_new, n) {}
   array(pre_allocate_t, ::collection::count n) : BASE_ARRAY() { this->m_countAddUp = n; }
   array(zeroe_on_allocation_t, ::collection::count n) : BASE_ARRAY(zeroe_on_allocation_t{}, n) { }
   array(::collection::count n) : BASE_ARRAY(n) {}
   array(::collection::count n, ARG_TYPE t) : BASE_ARRAY(n, t) {}
   array(::range < typename BASE_ARRAY::const_iterator > constrange) : BASE_ARRAY(constrange) {}
   template < primitive_integral INTEGRAL >
   array(typename BASE_ARRAY::const_iterator begin, INTEGRAL count) : BASE_ARRAY(begin, count) {}
   array(typename BASE_ARRAY::const_iterator begin, typename BASE_ARRAY::const_iterator end) : BASE_ARRAY(begin, end) {}



   void destroy() override
   {

      ::particle::destroy();
      BASE_ARRAY::destroy();

   }

};



template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline TYPE & array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::get_at(::collection::index nIndex)
{

   ASSERT(nIndex >= 0 && nIndex < this->size());

   return this->m_begin[nIndex];

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline const TYPE & array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::get_at(::collection::index nIndex) const
{

   ASSERT(nIndex >= 0 && nIndex < this->size());

   return this->m_begin[nIndex];

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline void array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::set_at(::collection::index nIndex, ARG_TYPE newElement)
{

   ASSERT(nIndex >= 0 && nIndex < this->size());

   this->m_begin[nIndex] = newElement;

}



template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline ::collection::index array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::add_item(ARG_TYPE newElement)
{

   auto nIndex = this->size();

   this->allocate(nIndex + 1, false, false, newElement);

   //this->last() = newElement;

   return nIndex;

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline ::collection::index array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::add(ARG_TYPE newElement)
{

   return add_item(newElement);

}


//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//template < container_type CONTAINER >
//inline ::collection::index array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::add(const CONTAINER & container)
//{
//
//   ::collection::index i = -1;
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

//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline ::collection::index array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::append(ARG_TYPE newElement)
//{
//   return add(newElement);
//}



//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >  & array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::operator = (const array_non_particle & src)
//{
//
//   if(&src != this)
//   {
//
//      copy(src);
//
//   }
//
//   return *this;
//
//}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::array_non_particle() :
   BASE_ARRAY::array_base_quantum()
{


}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::array_non_particle(const array_non_particle & a) :
   BASE_ARRAY::array_base_quantum(a)
{

}


//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::array_non_particle(::std::initializer_list < TYPE >  l)
//{
//
//   for(auto & item : l)
//   {
//
//      add((ARG_TYPE) item);
//
//   }
//
//}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::array_non_particle(enum_create_new, ::collection::count n)
{

   this->set_size(n);

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::array_non_particle(::collection::count n) :
   array_non_particle()
{

   this->set_size(n);

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::array_non_particle(::collection::count n, ARG_TYPE t) :
   array_non_particle()
{

   while (n > 0)
   {

      add(t);

      n--;

   }

}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::~array_non_particle()
{

   this->erase_all(); // on_destruct_element is virtual and won't be available for array_base_quantum

}


//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline ::collection::index array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::append(const array_non_particle & src)
//{
//
//   auto countOld = this->size();
//
//   this->allocate(countOld + src.size(), false, true);
//
//   TYPED::copy_construct_count(this->m_begin + countOld, src.size(), src.m_begin);
//
//   return countOld;
//
//}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline void array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::copy(const array_non_particle & src)
{

   ASSERT(this != &src);

   if (this != &src)
   {

      this->erase_all();

      this->append(src);

      //      auto nSrcSize = src.size();
      //
      //      this->allocate(nSrcSize);
      //
      //      CopyElements<TYPE>(this->m_begin,src.m_begin, nSrcSize);

   }

}




template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
template < primitive_container CONTAINER >
inline array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > & array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::operator += (const CONTAINER & container)
{

   if (&container == this)
   {

      array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > aCopy(container);

      this->append_container(aCopy);

   }
   else
   {

      this->append_container(container);

   }

   return *this;

}


//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//template < container CONTAINER >
//inline array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >  array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::operator + (const CONTAINER & container) const
//{
//
//   array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >  aNew(*this);
//
//   aNew.add(container);
//
//   return aNew;
//
//}
//

template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline TYPE & array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::add_new(::collection::count c)
{

   if (c <= 0)
   {

      throw_exception(error_bad_argument);

   }

   auto end = this->size();

   this->set_size(end + c);

   return this->element_at(end);

}

//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline TYPE & array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::add_new_at(int iIndex)
//{
//
//   this->make_room_at(iIndex);
//
//   return this->element_at(iIndex);
//
//}


template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
inline TYPE & array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::add_new_at(::collection::index i, ::collection::count c)
{

   this->raw_allocate_at(i, c);

   TYPED::construct_count(this->m_begin + i, c);

   return this->element_at(i);

}



//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > & array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::transfer(array_non_particle && a)
//{
//
//   if(&a != this)
//   {
//
//      this->destroy();
//
//      this->m_nGrowBy = a.m_nGrowBy;
//      this->m_begin = a.m_begin;
//      this->m_end = a.m_end;
//      this->m_nMaxSize = a.m_nMaxSize;
//
//      a.m_begin = nullptr;
//      a.m_end = nullptr;
//      a.m_nMaxSize = 0;
//
//   }
//
//   return *this;
//
//}


//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY, ::enum_type t_etypeContainer >
//inline array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > & array_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::operator = (array_non_particle && a)
//{
//
//   transfer(::transfer(a));
//
//   return *this;
//
//}




