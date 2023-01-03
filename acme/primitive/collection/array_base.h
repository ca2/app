#pragma once


#include "_iterator.h"
#include "allocator.h"
#include "acme/platform/common.h"
#include "acme/primitive/primitive/particle.h"

//using tiny_index_array = tiny_array <::index>;




#define __default_array_array_base(TYPE) ::array_base < TYPE, const TYPE &, ::allocator::def < TYPE > >


#define DECLARE_TYPED_ARRAY_ACCESSOR_OF(ITEM, CONTAINER, TYPE, CONTAINER_TYPE) \
::pointer<TYPE>& ITEM ## _at(::index i) { return CONTAINER[i]; } \
const TYPE * ITEM ## _at(::index i) const { return CONTAINER[i]; } \
::pointer<TYPE>* ITEM ## _data() { return CONTAINER.data(); } \
::pointer<TYPE>const * ITEM ## _data() const { return CONTAINER.data(); } \
TYPE * get_ ## ITEM(::index i) const { return CONTAINER.bounds(i) ? CONTAINER[i] : nullptr; } \
::count ITEM ## _count() const { return CONTAINER.get_count(); } \
bool has_ ## ITEM() const { return CONTAINER.has_element(); } \
const CONTAINER_TYPE & ITEM ## a() const { return CONTAINER; } \
CONTAINER_TYPE & ITEM ## a() { return CONTAINER; } \
bool contains_ ## ITEM(const TYPE * p) const { return CONTAINER.contains(p); } \
bool is_there_no_ ## ITEM() const { return CONTAINER.is_empty(); } \
bool has_no_ ## ITEM() const { return is_there_no_ ## ITEM(); } \
::index find_first_ ## ITEM(const TYPE * p, ::index iStart = 0, ::count nCount = -1) const { return CONTAINER.find_first(p, iStart, nCount); } \
::pointer<TYPE>& first_ ## ITEM() { return CONTAINER.first_pointer(); } \
::pointer<TYPE>& last_ ## ITEM() { return CONTAINER.last_pointer(); } \
TYPE * get_first_ ## ITEM() const { return CONTAINER.get_first_pointer(); } \
TYPE * get_last_ ## ITEM() const { return CONTAINER.get_last_pointer(); } \
::index ITEM ## _first_index(::index i = 0) const { return CONTAINER.first_index(i); } \
::index ITEM ## _last_index(::index i = -1) const { return CONTAINER.last_index(i); } \
CONTAINER_TYPE CONTAINER

#define DECLARE_ARRAY_ACCESSOR_OF(ITEM, CONTAINER, TYPE) \
DECLARE_TYPED_ARRAY_ACCESSOR_OF(ITEM, CONTAINER, TYPE, pointer_array < TYPE >)

#define DECLARE_TYPED_ARRAY_OF(ITEM, CONTAINER, TYPE, CONTAINER_TYPE) \
::index add_ ## ITEM(TYPE * p) { return CONTAINER.add_item(p); }      \
::index add_ ## ITEM ## _array(const CONTAINER_TYPE & a) { return CONTAINER.append(a); } \
::index add_unique_ ## ITEM(TYPE * p) { return CONTAINER.add_unique(p); } \
::index add_unique_ ## ITEM ## _array(const CONTAINER_TYPE & a) { return CONTAINER.add_unique(a); } \
::index erase_ ## ITEM(TYPE * p) { return CONTAINER.erase(p); } \
CONTAINER_TYPE ITEM ## a_section(::index iStart = 0, ::count nCount = -1){return CONTAINER.slice < CONTAINER_TYPE >(iStart, nCount);} \
template < typename ARRAY > \
void ITEM ## a_slice(ARRAY & a, ::index iStart = 0, ::count nCount = -1){ CONTAINER.slice(a, iStart, nCount);} \
DECLARE_TYPED_ARRAY_ACCESSOR_OF(ITEM, CONTAINER, TYPE, CONTAINER_TYPE)

#define HAVE_ARRAY_OF(ITEM, CONTAINER, TYPE) \
DECLARE_TYPED_ARRAY_OF(ITEM, CONTAINER, TYPE, pointer_array < TYPE >)

#define DECLARE_ARRAY_CONTAINER_OF(ARRAY, ITEM, CONTAINER, TYPE) \
ARRAY(const ::std::initializer_list < ::pointer<TYPE >>& list) : CONTAINER(list) { } \
DECLARE_TYPED_ARRAY_OF(ITEM, CONTAINER, TYPE, pointer_array < TYPE >)

#define DECLARE_ARRAY_OF(ARRAY, ITEM, TYPE) \
DECLARE_ARRAY_CONTAINER_OF(ARRAY, ITEM, m_ ## ITEM ## a, TYPE)





// raw_array is an array that does not call constructors or destructor in elements
// array is an array that call only copy constructor and destructor in elements
// array is an array that call default constructors, copy constructs and destructors in elements
template < class TYPE, class ARG_TYPE, class ALLOCATOR, ::enum_type m_etypeContainer >
class array_base :
   virtual public ::particle,
   //public ::array_range < ::range < TYPE * > >
   public ::range < TYPE * >
{
public:


   //using ARRAY_RANGE = ::array_range < ::range < TYPE * > >;
   using ARRAY_RANGE = ::range < TYPE * >;
   using array_range = ::range < TYPE * >;

   using PRIMITIVE_CONTAINER_TAG = PRIMITIVE_CONTAINER_TAG_TYPE;

   using CONTAINER_ITEM_TYPE = TYPE;
   using TYPE_IS_PTR = TYPE;

   using iterator = typename ARRAY_RANGE::iterator;
   using const_iterator = typename ARRAY_RANGE::const_iterator;


   //TYPE * this->m_begin;    // the actual array of data
   //::count   this->size();    // # of elements (upperBound - 1)
   ::count   m_nMaxSize; // maximum allocated
   ::count   m_nGrowBy;  // grow amount

   //__declare_iterator_struct_ok(array_base, TYPE *, m_pelement, this->m_pelement >= this->m_pcontainer->m_begin && this->m_pelement < this->m_pcontainer->end());

   //using RANGE::RANGE;

   array_base();
   array_base(std::initializer_list < TYPE > initializer_list);
   array_base(const array_base & a);
   array_base(array_base && a) noexcept;
   array_base(const TYPE * p, ::count c);
   array_base(::range < const_iterator > constrange) : array_base(constrange.begin(), constrange.end()) {}
   template < primitive_integral INTEGRAL >
   array_base(const_iterator begin, INTEGRAL count) : array_base(begin, begin + count) {}
   array_base(const_iterator begin, const_iterator end)
   {
      auto p = this->begin();
      while (p != end) add(*p);
   }
   virtual ~array_base();


   void defer_destroy()
   {

      if (this->m_begin != nullptr)
      {

         destroy();

      }

   }


   array_base & operator = (const array_base & array_base)
   {

      if (this != &array_base)
      {

         for (auto & item : array_base)
         {

            add(item);

         }

      }
      
      return *this; 
   
   }


   array_base & operator = (array_base && array_base)
   {

      if (this != &array_base)
      {

         transfer(::transfer(array_base));

      }
      
      return *this;
   
   }



   void add_initializer_list(const ::std::initializer_list < TYPE > & initializer_list)
   {

      for (auto & item : initializer_list)
      {

         add(item);

      }

   }


   inline array_base & transfer(array_base && a)
   {

      if (this != &a)
      {

         destroy();

         ARRAY_RANGE::operator=(::transfer(a));

         m_nGrowBy = a.m_nGrowBy;

         m_nMaxSize = a.m_nMaxSize;

      }

      return *this;

   }


   //template < typename iterator >
   //struct make_iterator : iterator
   //{

   //   using CONTAINER = typename iterator::CONTAINER;


   //   make_iterator()
   //   {
   //      this->m_pelementBeg = (TYPE *)nullptr;
   //      this->m_pelementEnd = (TYPE *)nullptr;
   //      this->m_pcontainer = (CONTAINER *)nullptr;
   //      this->m_pelement = this->m_pelementBeg;
   //   }

   //   make_iterator(::index iStart, ::index iEnd, const CONTAINER * parray = nullptr)
   //   {
   //      this->m_pelementBeg = (TYPE *)(parray->m_begin + iStart);
   //      this->m_pelementEnd = (TYPE *)(parray->m_begin + (iEnd < 0 ? parray->size() + iEnd + 1 : iEnd));
   //      this->m_pcontainer = (CONTAINER *)parray;
   //      this->m_pelement = this->m_pelementBeg;
   //   }

   //   make_iterator(const CONTAINER * parray, const TYPE * pmatter = nullptr, const TYPE * pelementEnd = nullptr)
   //   {
   //      this->m_pelementBeg = (TYPE *)pmatter;
   //      this->m_pelementEnd = (TYPE *)pelementEnd;
   //      this->m_pcontainer = (CONTAINER *)parray;
   //      this->m_pelement = this->m_pelementBeg;
   //   }


   //   make_iterator(const make_iterator & iterator)
   //   {
   //      this->m_pelementBeg = (TYPE *)iterator.m_pelementBeg;
   //      this->m_pelementEnd = (TYPE *)iterator.m_pelementEnd;
   //      this->m_pelement = iterator.m_pelement;
   //      this->m_pcontainer = iterator.m_pcontainer;
   //   }


   //   make_iterator begin()
   //   {

   //      return make_iterator(this->m_pcontainer, this->m_pelementBeg, this->m_pelementEnd);

   //   }


   //   make_iterator end()
   //   {

   //      return make_iterator(this->m_pcontainer, this->m_pelementEnd, this->m_pelementEnd);

   //   }


   //   make_iterator & operator ++ ()
   //   {

   //      this->m_pelement++;
   //      return *this;

   //   }


   //   make_iterator operator ++ (i32)
   //   {

   //      auto it = *this;

   //      this->m_pelement++;
   //      return it;

   //   }


   //   make_iterator operator + (::count c) const
   //   {

   //      return { this->m_pcontainer, this->m_pelement + c };

   //   }


   //   make_iterator operator - (const make_iterator & it) const
   //   {

   //      return { this->m_pcontainer, this->m_pelement - it.index() };

   //   }


   //   bool operator == (const make_iterator & it) const
   //   {


   //      if (this->m_pcontainer != it.m_pcontainer)
   //      {

   //         return false;

   //      }

   //      return this->m_pelement == it.m_pelement;

   //   }


   //   bool operator >= (const make_iterator & it) const
   //   {


   //      if (this->m_pcontainer != it.m_pcontainer)
   //      {

   //         return false;

   //      }

   //      return this->m_pelement >= it.m_pelement;

   //   }


   //   bool operator > (const make_iterator & it) const
   //   {

   //      if (this->m_pcontainer != it.m_pcontainer)
   //      {

   //         return false;

   //      }

   //      return this->m_pelement > it.m_pelement;

   //   }


   //   bool operator != (const make_iterator & it) const
   //   {

   //      if (this->m_pcontainer != it.m_pcontainer)
   //      {

   //         return true;

   //      }

   //      return this->m_pelement != it.m_pelement;

   //   }

   //   bool operator < (const make_iterator & it) const
   //   {

   //      if (this->m_pcontainer != it.m_pcontainer)
   //      {

   //         return false;

   //      }

   //      return this->m_pelement < it.m_pelement;


   //   }

   //   bool operator <= (const make_iterator & it) const
   //   {

   //      if (this->m_pcontainer != it.m_pcontainer)
   //      {

   //         return false;

   //      }

   //      return this->m_pelement <= it.m_pelement;


   //   }


   //   bool operator == (const TYPE * pmatter) const
   //   {


   //      if (!this->m_pcontainer->contains(pmatter))
   //      {

   //         return false;

   //      }

   //      return this->m_pelement == pmatter;

   //   }


   //   bool operator >= (const TYPE * pmatter) const
   //   {


   //      if (!this->m_pcontainer->contains(pmatter))
   //      {

   //         return false;

   //      }

   //      return this->m_pelement >= pmatter;

   //   }


   //   bool operator > (const TYPE * pmatter) const
   //   {

   //      if (!this->m_pcontainer->contains(pmatter))
   //      {

   //         return false;

   //      }

   //      return this->m_pelement > pmatter;

   //   }


   //   bool operator != (const TYPE * pmatter) const
   //   {

   //      if (!this->m_pcontainer->contains(pmatter))
   //      {

   //         return true;

   //      }

   //      return this->m_pelement != pmatter;

   //   }

   //   bool operator < (const TYPE * pmatter) const
   //   {

   //      if (!this->m_pcontainer->contains(pmatter))
   //      {

   //         return false;

   //      }

   //      return this->m_pelement < pmatter;


   //   }

   //   bool operator <= (const TYPE * pmatter) const
   //   {

   //      if (!this->m_pcontainer->contains(pmatter))
   //      {

   //         return false;

   //      }

   //      return this->m_pelement <= pmatter;


   //   }

   //   make_iterator & operator = (const make_iterator & it)
   //   {

   //      if (this != &it)
   //      {

   //         this->m_pcontainer = it.m_pcontainer;

   //         this->m_pelement = it.m_pelement;

   //      }

   //      return *this;

   //   }

   //   ::index index() const { return this->m_pelement - this->m_pcontainer->m_begin; }

   //};

   //__declare_iterator(iterator, this->m_pelement);
   //__declare_iterator(ref_iterator, *this->m_pelement);

   void this_is_a_container() {}

   enum_type get_payload_type() const override { return m_etypeContainer; }


   inline memsize length_in_bytes() const { return this->size() * sizeof(TYPE); }

   //inline auto values(index iStart = 0, index iEnd = -1) const { return iterator(iStart, iEnd, this); }


   //inline iterator begin()
   //{

   //   return iterator(0, (::index)this->size(), this);

   //}


   //inline iterator end()
   //{

   //   return iterator((::index)this->size(), (::index)this->size(), this);

   //}





   //inline const TYPE * get_data() const { return this->begin(); }
   //inline TYPE * get_data() { return this->begin(); }




   inline bool contains(const TYPE * pmatter) const { return pmatter >= this->m_begin && pmatter < this->end(); }


   inline ::count get_size() const;
   inline ::count get_size_in_bytes() const;
   inline ::count get_count() const;
   inline ::count get_byte_count() const;
   inline ::count get_length() const;
   //inline ::count size() const;
   inline ::count count() const;
   inline ::count length() const;
   inline ::count byte_count() const { return get_byte_count(); }


   inline bool has_element() const noexcept { return this->size() > 0; }
   inline bool is_empty(::count countMinimum = 0) const noexcept { return this->size() <= countMinimum; }
   inline bool empty(::count countMinimum = 0) const noexcept { return this->size() <= countMinimum; }
   inline bool has_elements(::count countMinimum = 1) const noexcept { return this->size() >= countMinimum; }
   inline ::index get_lower_bound(::index i = 0) const;
   inline ::index get_middle_index(::index i = 0) const;
   inline ::index get_upper_bound(::index i = -1) const;
   inline ::index lower_bound(::index i = 0) const { return get_lower_bound(i); }
   inline ::index upper_bound(::index i = -1) const { return get_upper_bound(i); }
   inline ::index first_index(::index i = 0) const { return lower_bound(i); }
   inline ::index middle_index(::index i = 0) const { return get_middle_index(i); }
   inline ::index last_index(::index i = -1) const { return upper_bound(i); }
   inline bool bounds(::index i) const;
   inline bool contains_index(::index i) const { return  bounds(i); }


   inline const TYPE * ptr_at(::index nIndex) const { return this->m_begin + nIndex; }
   inline TYPE * ptr_at(::index nIndex) { return this->m_begin + nIndex; }

   inline const TYPE & element_at(::index nIndex) const;
   inline TYPE & element_at(::index nIndex);

   inline TYPE & first(::index n = 0);
   inline const TYPE & first(::index n = 0) const;

   inline TYPE & last(::index n = -1);
   inline const TYPE & last(::index n = -1) const;

   inline TYPE & middle(::index n = 0);
   inline const TYPE & middle(::index n = 0) const;

   inline void set_at_grow(::index nIndex, ARG_TYPE newElement, ::count nGrowBy = -1);
   inline TYPE & element_at_grow(::index nIndex, ::count nGrowBy = -1);

   inline void set_each(ARG_TYPE element, ::index iStart = 0, ::count c = -1);

   template < ::std::size_t N >
   TYPE & get() { return element_at(N); }


   void reserve(::count nReserve) { set_size(get_size(), nReserve); }


   ::count set_size(::count nNewSize, ::count nGrowBy = -1); // does not call default constructors on memory_new items/elements
   ::count allocate(::count nNewSize, ::count nGrowBy = -1, const TYPE * ptype = nullptr); // does not call default constructors on memory_new items/elements
   ::count allocate_in_bytes(::count nNewSize, ::count nGrowBy = -1); // does not call default constructors on memory_new items/elements
   ::count set_raw_size(::count nNewSize, ::count nGrowBy = -1); // does not call constructors and destructors on items/elements
   ::count resize(::count nNewSize) { return set_size(nNewSize); } // does not call default constructors on memory_new items/elements
   ::count resize(::count nNewSize, ARG_TYPE t, ::count nGrowBy = -1); // does not call default constructors on memory_new items/elements

   void free_extra();
   void destroy() override;

   inline void __swap(::index index1, ::index index2);
   inline void __swap(iterator index1, iterator index2);


   void set_all(const TYPE & t);


   void zero(::index iStart = 0, ::count c = -1);

   template < primitive_array ARRAY >
   void _001RemoveIndexes(ARRAY & ia);
   
   template < primitive_array ARRAY >
   void erase_indexes(const ARRAY & ia);

   template < primitive_array ARRAY >
   void erase_descending_indexes(const ARRAY & ia);


   inline bool prepare_first_last(::index & first, ::index & last) const;
   inline bool prepare_first_in_count_last_out(::index & first, ::count & inCountLastOut) const;


   inline void erase_last();
   inline ::count erase_all();
   inline void clear();


   void on_construct_element(TYPE * p) { ALLOCATOR::construct(p); }
   void on_construct_element(TYPE * p, ::count c) { ALLOCATOR::construct_count(p, c); }
   void on_destruct_element(TYPE * p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) { ALLOCATOR::destruct(p  OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS); }
   void on_copy_element(::index i, const TYPE * p) { ALLOCATOR::copy(&this->m_begin[i], p); }


   inline const TYPE & operator[](::index i) const;
   inline TYPE & operator[](::index i);


   ::index insert_at(::index nIndex, const TYPE & newElement, ::count nCount = 1);
   ::index erase_at(::index nIndex, ::count nCount = 1);
   ::index insert_at(::index nStartIndex, array_base * pNewArray);

   ::index make_room_at(::index nIndex, ::count nCount = 1);


   TYPE pick_at(::index nIndex);
   TYPE pick_first(::index nIndex = 0) { return ::transfer(pick_at(nIndex)); }
   TYPE pick_last(::index nIndex = -1) { return ::transfer(pick_at(this->size() + nIndex)); }
   array_base pick_at(::index nIndex, ::count nCount);


   ::index erase_item(TYPE * p);

   ::index index_of(const TYPE * p) const { auto i = p - this->m_begin; return i >= 0 && i < this->size() ? i : -1; }


   bool erase(const TYPE * p) { auto i = index_of(p); if (not_found(i)) return false; return found(erase_at(i)); }
   ::count erase(const TYPE * begin, const TYPE * end);

   iterator erase(iterator p) 
   { 

      this->erase_at(index_of(p));
   
      return p;
   
   }

   template < typename ITERATOR2 >
   inline void erase(const ITERATOR2 & begin, const ITERATOR2 & last);


   inline TYPE pop(::index i = -1);
   inline ::index push(ARG_TYPE newElement, ::index i = 0);
   inline void pop_back(::index i = -1);
   inline void push_back(ARG_TYPE newElement, ::index = 0);


   inline TYPE pop_first(::index i = 0);

   inline TYPE takeAt(::index i);
   inline TYPE takeFirst(::index i = 0);
   inline TYPE takeLast(::index i = -1);

   virtual ::count append(const array_base & src); // return old size_i32
   virtual void copy(const array_base & src);


   template < primitive_container CONTAINER >
   ::count append(const CONTAINER & container)
   {

      ::count c = 0;

      for (auto& item : container)
      {

         add(item);

         c++;

      }

      return c;

   }



   virtual void on_after_read();

   template < typename PRED >
   ::count predicate_each(PRED pred, ::index iStart = 0, ::count c = -1)
   {

      ::index iEnd = c < 0 ? get_count() + c : iStart + c - 1;

      int cProcessed = 0;

      for (::index i = iStart; i <= iEnd; i++)
      {

         pred(this->m_begin[i]);

         cProcessed++;

      }

      return cProcessed;

   }

   template < typename PRED >
   ::count predicate_each(PRED pred, ::index iStart = 0, ::count c = -1) const
   {

      return ((array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >*)this)->predicate_each(pred, iStart, c);

   }


   inline bool is_index_ok(::index iIndex) const { return iIndex >= 0 && iIndex < get_count(); }

   inline bool is_last_index(::index iIndex) const { return iIndex >= get_upper_bound(); }

   template < typename PRED >
   bool predicate_contains(PRED pred, ::index iStart = 0, ::index iEnd = -1) const
   {

      return this->predicate_find_first(pred, iStart, iEnd) >= 0;

   }

   template < typename OTHER_IS_PTR >
   TYPE_IS_PTR get_existing_defer_add(const OTHER_IS_PTR& pother)
   {

      for (::index i = 0; i < this->get_count(); i++)
      {

         if (*this->element_at(i) == *pother)
         {

            return this->element_at(i);

         }

      }

      this->add(pother);

      return pother;

   }


   template < typename OTHER_IS_PTR >
   TYPE_IS_PTR get_existing(const OTHER_IS_PTR & pother) const
   {

      for (::index i = 0; i < this->get_count(); i++)
      {

         if (*this->element_at(i) == *pother)
         {

            return this->element_at(i);

         }

      }

      return pother;

   }

   template < typename OBJECT, typename ATTRIBUTE >
   TYPE_IS_PTR merge_get_existing(const TYPE_IS_PTR & p, const OBJECT& pparticle, const ATTRIBUTE& attribute)
   {

      auto pModified = __new(typename TYPE_IS_PTR::TYPE(*p));

      pModified->process(pparticle, attribute);

      return this->get_existing(pModified);

   }



   template < typename PRED >
   ::index predicate_find_first(PRED pred, ::index iStart = 0, ::index iEnd = -1) const
   {

      if (iEnd < 0)
      {

         iEnd += get_count();

      }

      if (iEnd >= get_count())
      {

         iEnd = get_count() - 1;

      }

      for (::index i = iStart; i <= iEnd; i++)
      {

         if (pred(this->m_begin[i]))
         {

            return i;

         }

      }

      return -1;

   }

   template < typename PRED >
   ::index predicate_find_last(PRED pred, ::index iLast = -1)
   {

      if (iLast < 0)
      {

         iLast += get_count();

      }

      for (::index i = iLast; i >= 0; i--)
      {

         if (pred(this->m_begin[i]))
         {

            return i;

         }

      }

      return -1;

   }

   template < typename PRED >
   TYPE * predicate_get_first(PRED pred)
   {
      for (int i = 0; i < get_count(); i++)
      {

         if (pred(this->m_begin[i]))
         {

            return &element_at(i);

         }

      }

      return nullptr;

   }

   //template < typename VAR >
   //inline array_base & operator = (const class ::payload_type < VAR > & a);


   template < typename PRED >
   ::count predicate_get_count(PRED pred)
   {

      ::count c = 0;

      for (int i = 0; i < get_count(); i++)
      {

         if (pred(this->m_begin[i]))
         {

            c++;

         }

      }

      return c;

   }


   inline ::index add(ARG_TYPE newElement)
   {

      auto nIndex = this->size();

      this->allocate((::count) (nIndex + 1));

      this->last() = newElement;

      return (::index) nIndex;

   }


   TYPE & add_new()
   {

      auto nIndex = this->size();

      this->allocate((::count)(nIndex + 1));

      return this->last();

   }


   template < typename PRED >
   ::count predicate_erase(PRED pred)
   {
      ::count cTotal = 0;
      for (int i = 0; i < get_count();)
      {

         if (!pred(this->m_begin[i]))
         {
            i++;
         }
         else
         {

            int iStart = i;

            int iCount = 1;

            i++;

            for (; i < get_count();)
            {

               if (!pred(this->m_begin[i]))
               {

                  break;

               }

               iCount++;

               i++;

            }

            erase_at(iStart, iCount);

            cTotal += iCount;

            i = iStart;

         }

      }
      return cTotal;
   }

   template < typename F >
   void each(F f)
   {

      for (::index i = 0; i < get_count(); i++)
      {
         f(this->m_begin[i]);
      }

   }


   template < typename PRED >
   void predicate_sort(PRED pred);

   template < typename T, typename PRED >
   ::index predicate_binary_search(const T & t, PRED pred) const;

   inline bool valid_iter(iterator first, iterator last)
   {

      return first < last;

   }

   inline bool rvalid_iter(iterator first, iterator last)
   {

      return first > last;

   }


   inline TYPE& operator%(::index nIndex)
   {

      return this->operator[](nIndex% this->get_size());

   }

   inline const TYPE& operator%(::index nIndex) const
   {

      return this->operator[](nIndex% this->get_size());

   }


   bool is_version(index i)
   {

      return true;

      //if (!m_pvarOptions)
      //{

      //   return i <= 0;

      //}

      //return i <= options()["version"].i32();

   }


};


template < primitive_integral INTEGRAL, class TYPE, class ARG_TYPE, class ALLOCATOR = allocator::nodef < TYPE >, ::enum_type m_etypeContainer = e_type_element >
inline TYPE& operator%(INTEGRAL nIndex, const array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & a)
{

   return (TYPE &) (a % nIndex);

}






template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::array_base() :
ARRAY_RANGE()
{

   m_nGrowBy = 0;
   m_nMaxSize = 0;

}

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::array_base(array_base && array) noexcept :
   ARRAY_RANGE(array)
{

   this->m_nGrowBy = array.m_nGrowBy;
   this->m_nMaxSize = array.m_nMaxSize;

   array.m_begin = nullptr;
   array.m_end = 0;
   array.m_nMaxSize = 0;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::array_base(std::initializer_list<TYPE > initializer_list) :
   array_base()
{

   for (auto & item : initializer_list)
   {

      add(item);

   }

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::array_base(const array_base & array)
{

   m_nGrowBy = 0;
   this->m_begin = nullptr;
   this->m_end = nullptr;
   m_nMaxSize = 0;

   set_size(array.get_size());

   for (::index i = 0; i < array.get_size(); i++)
   {

      element_at(i) = array[i];

   }

}



template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::~array_base ()
{

   defer_destroy();

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
::count array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::resize(::count nNewSize, ARG_TYPE t, ::count nGrowBy)
{

   return allocate(nNewSize, nGrowBy, &t);

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
::count array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::allocate_in_bytes(::count nNewSize,::count nGrowBy)
{

   if(nGrowBy < 0)
   {

      return allocate(nNewSize / sizeof(TYPE),-1);

   }
   else
   {

      return allocate(nNewSize / sizeof(TYPE),nGrowBy / sizeof(TYPE));

   }

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
::index array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::erase_at(::index nIndex,::count nCount)
{

   //ASSERT_VALID(this);

   ::index nUpperBound = nIndex + nCount;

   if (nIndex < 0 || nCount < 0 || (nUpperBound > this->size()) || (nUpperBound < nIndex) || (nUpperBound < nCount))
   {

      throw_exception(error_bad_argument);

   }

   ::count nMoveCount = this->size() - (nUpperBound);

   ALLOCATOR::destruct_count(this->m_begin + nIndex, nCount OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

   if(nMoveCount)
   {

      ::acme::memmove_s(this->m_begin + nIndex,(size_t)nMoveCount * sizeof(TYPE),this->m_begin + nUpperBound,(size_t)nMoveCount * sizeof(TYPE));

   }

   this->m_end -= nCount;

   return nIndex;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
::index array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::erase_item(TYPE * p)
{

   return erase_at(p - this->m_begin);

}



template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
void array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::free_extra()
{

   if(this->size() != m_nMaxSize)
   {
      // shrink to desired size_i32
#ifdef SIZE_T_MAX
      ASSERT(this->size() <= SIZE_T_MAX / sizeof(TYPE)); // no overflow
#endif
      TYPE* pNewData = nullptr;
      if(this->size() != 0)
      {
         TYPE * pNewData;
#if defined(__MCRTDBG) || MEMDLEAK
         #ifdef __MCRTDBG
         if (::get_task() != nullptr)
         {
            if (::get_task()->m_strFile.has_char())
            {
               pNewData = ALLOCATOR::alloc(this->size(), ::get_task()->m_strFile, ::get_task()->m_iLine);
            }
            else
            {
               pNewData = ALLOCATOR::alloc(this->size(), __FILE__, __LINE__);
            }
         }
         else
         {
            pNewData = ALLOCATOR::alloc(this->size(), __FILE__, __LINE__);
         }
#else

         if (::get_task()->m_strDebug.has_char())
         {

            pNewData = ALLOCATOR::alloc(this->size(), ::get_task()->m_strDebug, 0);

         }
         else
         {

            pNewData = ALLOCATOR::alloc(this->size(), __FILE__, __LINE__);

         }

#endif

#else

         pNewData = ALLOCATOR::alloc(this->size());

#endif      // copy memory_new data from old

         // copy memory_new data from old
         ::acme::memcpy_s(pNewData, (size_t)this->size() * sizeof(TYPE),this->m_begin, (size_t)this->size() * sizeof(TYPE));

      }

      // get rid of old stuff (note: no destructors called)
      ALLOCATOR::_free(this->m_begin);

      this->m_begin = pNewData;

      m_nMaxSize = this->size();

   }

}



template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
void array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::destroy()
{

   if(this->m_begin != nullptr)
   {

      ALLOCATOR::destruct_count(this->m_begin, this->size() OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

      ALLOCATOR::_free(this->m_begin);

      this->m_begin     = nullptr;
      this->m_end       = nullptr;
      m_nMaxSize        = 0;

   }

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
::index array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::insert_at(::index nIndex,const TYPE & newElement,::count nCount /*=1*/)
{

   ::index nIndexParam = make_room_at(nIndex, nCount);

   while(nCount--)
   {

      ALLOCATOR::copy(this->m_begin + nIndex, &newElement);

      nIndex++;

   }

   return nIndexParam;

}

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
::index array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::make_room_at(::index nIndex, ::count nCount /*=1*/)
{

   ASSERT(nIndex >= 0);    // will expand to meet need

   if(nCount <= 0)
      return -1;

   if(nIndex < 0)
      throw_exception(error_bad_argument);

   if(nIndex >= this->size())
   {

      // adding after the end of the array
      set_size(nIndex + nCount,-1);   // grow so nIndex is valid

   }
   else
   {

      // inserting in the middle of the array
      ::count nOldSize = (::count) this->size();

      set_size((::count) this->size() + nCount,-1);  // grow it to memory_new size_i32
      // destroy intial data before copying over it
      // shift old data up to fill gap
      ::acme::memmove_s(this->m_begin + nIndex + nCount,(size_t) ((nOldSize - nIndex) * sizeof(TYPE)),this->m_begin + nIndex,(size_t)((nOldSize - nIndex) * sizeof(TYPE)));

      ::zero(this->m_begin + nIndex, nCount* sizeof(TYPE));

      ALLOCATOR::construct_count(this->m_begin + nIndex,nCount);

   }

   // insert memory_new value in the gap
   ASSERT(nIndex + nCount <= this->size());

   return nIndex;

}



template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
::count array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::append(const array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & src)
{

   ::count nOldSize = this->size();

   ::count nSrcSize = src.size();   // to enable to append to itself

   allocate(nOldSize + nSrcSize);

   ALLOCATOR::copy_count((this->m_begin + nOldSize), src.m_begin, nSrcSize);

   return nOldSize;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
void array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::copy(const array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & src)
{

   if(this == &src)
   {

      return;

   }

   ::count nSrcSize = src.size();

   allocate(nSrcSize);

   ALLOCATOR::copy_count(this->m_begin,src.m_begin, nSrcSize);

}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//template < primitive_container CONTAINER >
//array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >
//array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::operator + (const CONTAINER & array) const
//{
//
//   auto a = *this;
//
//   a.append(array);
//
//   return ::transfer(a);
//
//}

//#include "sort.h"

// take in accptr that _001RemoveIndexes machine
// the ::index raw_array by sorting it and returning
// only the indexes that could be erased
// without indexes duplicates
template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
template < primitive_array ARRAY >
void array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::_001RemoveIndexes(ARRAY & ia)
{

   // sort
   //::sort::quick_sort(ia,true);

   ia.sort();

   ::index i = ia.get_upper_bound();

   // filter out of upper bound indexes
   while(i >= 0 && ia[i] >= get_size())
   {

      ia.erase_at(i);

      i--;

   }

   // filter out of lower bound indexes
   while(ia.get_size() > 0 && ia[0] < 0)
   {

      ia.erase_at(0);

   }

   i = ia.get_upper_bound();

   // filter out duplicates
   while(i > 0 && ia[i] >= get_size())
   {

      if(ia[i] == ia[i - 1])
         ia.erase_at(i);

      i--;

   }

   erase_indexes(ia);

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
template < primitive_array ARRAY >
void array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::erase_indexes(const ARRAY & ia)
{


   // erase indexes
   for(::index i = ia.get_upper_bound(); i >= 0; i--)
   {

      erase_at(ia[i]);

   }

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
template < primitive_array ARRAY >
void array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::erase_descending_indexes(const ARRAY & ia)
{

   for(::index i = 0; i < ia.get_count(); i++)
   {

      erase_at(ia[i]);

   }

}



template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
::index array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::insert_at(::index nIndex,array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > * pNewArray)
{

   ASSERT(pNewArray != nullptr);
   ASSERT(nIndex >= 0);    // will expand to meet need

   ::count nCount = pNewArray->get_size();

   if (nCount <= 0)
      return -1;

   if (nIndex < 0)
      throw_exception(error_bad_argument);

   if (nIndex >= this->size())
   {

      // adding after the end of the array
      set_size(nIndex + nCount, -1);   // grow so nIndex is valid

   }
   else
   {

      // inserting in the middle of the array
      ::count nOldSize = (::count) this->size();

      set_size((::count) (this->size() + nCount), -1);  // grow it to memory_new size_i32
      // destroy intial data before copying over it
      // shift old data up to fill gap
      ::acme::memmove_s(this->m_begin + nIndex + nCount, (size_t) ((nOldSize - nIndex) * sizeof(TYPE)), this->m_begin + nIndex, (size_t) ((nOldSize - nIndex) * sizeof(TYPE)));

      ::zero(this->m_begin + nIndex, nCount* sizeof(TYPE));

      ALLOCATOR::construct_count(this->m_begin + nIndex, nCount);

   }

   // insert memory_new value in the gap
   ASSERT(nIndex + nCount <= this->size());

   ::index nIndexParam = nIndex;

   ::index i = 0;

   while (nCount--)
   {

      ALLOCATOR::copy(this->m_begin + nIndex, pNewArray->m_begin + i);

      nIndex++;

   }

   return nIndexParam;


}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
TYPE array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::pick_at(::index nIndex)
{

   ::count nCount = 1;

   ::index nUpperBound = nIndex + nCount;

   if (nIndex < 0 || nCount < 0 || (nUpperBound > this->size()) || (nUpperBound < nIndex) || (nUpperBound < nCount))
   {

      throw_exception(error_bad_argument);

   }

   ::count nMoveCount = this->size() - (nUpperBound);

   auto t = this->m_begin[nIndex];

   ALLOCATOR::destruct_count(this->m_begin + nIndex, nCount OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

   if (nMoveCount)
   {

      ::acme::memmove_s(this->m_begin + nIndex, (size_t)nMoveCount * sizeof(TYPE), this->m_begin + nUpperBound, (size_t)nMoveCount * sizeof(TYPE));

   }

   this->m_end -= nCount;

   return ::transfer(t);

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::pick_at(::index nIndex, ::count nCount)
{

   //ASSERT_VALID(this);

   ::index nUpperBound = nIndex + nCount;

   if (nIndex < 0 || nCount < 0 || (nUpperBound > this->size()) || (nUpperBound < nIndex) || (nUpperBound < nCount))
   {

      throw_exception(error_bad_argument);

   }

   ::count nMoveCount = this->size() - (nUpperBound);

   array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > a(this->m_begin + nIndex, (size_t)nMoveCount);

   ALLOCATOR::destruct_count(this->m_begin + nIndex, nCount OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

   if (nMoveCount)
   {

      ::acme::memmove_s(this->m_begin + nIndex, (size_t)nMoveCount * sizeof(TYPE), this->m_begin + nUpperBound, (size_t)nMoveCount * sizeof(TYPE));

   }

   this->m_end -= nCount;

   return a;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
::count array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::set_raw_size(::count nNewSize,::count nGrowBy)
{

   ::count countOld = get_count();

   ASSERT(nNewSize >= 0);

   if(nNewSize < 0)
      throw_exception(error_bad_argument);

   if(nGrowBy >= 0)
      m_nGrowBy = nGrowBy;  // set memory_new size_i32

   if(nNewSize == 0)
   {

      // shrink to nothing
      if(this->m_begin != nullptr)
      {

         ALLOCATOR::_free(this->m_begin);

         this->m_begin = nullptr;

      }

      this->m_end = nullptr;
      m_nMaxSize = 0;
   }
   else if (this->m_begin == nullptr)
   {
      // create buffer big enough to hold number of requested elements or
      // m_nGrowBy elements, whichever is larger.
#ifdef SIZE_T_MAX
      if (nNewSize > SIZE_T_MAX / sizeof(TYPE))
         throw_exception(error_no_memory);
      ASSERT(nNewSize <= SIZE_T_MAX / sizeof(TYPE));    // no overflow
#endif
      ::count nAllocSize = (::count) maximum(nNewSize, m_nGrowBy);
#if defined(__MCRTDBG) || MEMDLEAK
      if (::get_task() != nullptr)
      {
#if defined(MEMDLEAK)

         if (::get_task()->m_strFile.has_char())
         {

            this->m_begin = ALLOCATOR::alloc(nAllocSize, ::get_task()->m_strFile, 0);

         }
         else
         {

            this->m_begin = ALLOCATOR::alloc(nAllocSize, __FILE__, __LINE__);

         }

#else

         if (::get_task()->m_strDebug.has_char())
         {

            this->m_begin = ALLOCATOR::alloc(nAllocSize, ::get_task()->m_strDebug, ::get_task()->m_iLine);

         }
         else
         {

            this->m_begin = ALLOCATOR::alloc(nAllocSize, __FILE__, __LINE__);

         }

#endif

      }
      else
      {

         this->m_begin = ALLOCATOR::alloc(nAllocSize, __FILE__, __LINE__);

      }

#else

      this->m_begin = ALLOCATOR::alloc(nAllocSize);

#endif

      this->m_end = this->m_begin+ nNewSize;
      m_nMaxSize = nAllocSize;
   }
   else if(nNewSize <= m_nMaxSize)
   {
      this->m_end = this->m_begin+nNewSize;
   }
   else
   {
      // otherwise, grow aaa_base_array
      nGrowBy = (::count) m_nGrowBy;
      if(nGrowBy == 0)
      {
         // heuristically determine growth when nGrowBy == 0
         //  (this avoids heap fragmentation in many situations)
         nGrowBy = (::count) this->size();
         nGrowBy = (nGrowBy < 4) ? 4 : ((nGrowBy > 1024) ? 1024 : nGrowBy);
      }
      ::count nNewMax;
      if(nNewSize < m_nMaxSize + nGrowBy)
         nNewMax = (::count) (m_nMaxSize + nGrowBy);  // granularity
      else
         nNewMax = nNewSize;  // no slush

      ASSERT(nNewMax >= m_nMaxSize);  // no wrap around

      if(nNewMax  < m_nMaxSize)
         throw_exception(error_bad_argument);

#ifdef SIZE_T_MAX
      ASSERT(nNewMax <= SIZE_T_MAX / sizeof(TYPE)); // no overflow
#endif
      TYPE * pNewData;
#if defined(__MCRTDBG) || MEMDLEAK
      #ifdef __MCRTDBG

      if (::get_task() != nullptr)
      {

         if (::get_task()->m_strFile.has_char())
         {

            pNewData = ALLOCATOR::alloc(nNewMax, ::get_task()->m_strFile, ::get_task()->m_iLine);

         }
         else
         {

            pNewData = ALLOCATOR::alloc(nNewMax, __FILE__, __LINE__);

         }

      }
      else
      {

         pNewData = ALLOCATOR::alloc(nNewMax, __FILE__, __LINE__);

      }

#else

      if (::get_task()->m_strDebug.has_char())
      {

         pNewData = ALLOCATOR::alloc(nNewMax, ::get_task()->m_strDebug, ::get_task()->m_iLine);

      }
      else
      {

         pNewData = ALLOCATOR::alloc(nNewMax, __FILE__, __LINE__);

      }

#endif

#else

      pNewData = ALLOCATOR::alloc(nNewMax);

#endif      // copy memory_new data from old

      ::acme::memcpy_s(pNewData,(size_t)nNewMax * sizeof(TYPE),this->m_begin,(size_t)this->size() * sizeof(TYPE));

      ///for(i32 i = 0; i < nNewSize - this->size(); i++)
      // get rid of old stuff (note: no destructors called)
      ALLOCATOR::_free(this->m_begin);

      this->m_begin = pNewData;

      this->m_end = this->m_begin + nNewSize;

      m_nMaxSize = nNewMax;

   }

   return countOld;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
::count array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::allocate(::count nNewSize,::count nGrowBy, const TYPE * ptype)
{

   ::count countOld = get_count();

   ASSERT(nNewSize >= 0);

   if(nNewSize < 0)
   {

      throw_exception(error_bad_argument);

   }

   if(nGrowBy >= 0)
   {

      m_nGrowBy = nGrowBy;  // set memory_new size_i32

   }


   if(nNewSize == this->size())
   {

      return this->size();

   }

   if(nNewSize == 0)
   {

      // shrink to nothing
      if(this->m_begin != nullptr)
      {

         ALLOCATOR::destruct_count(this->m_begin, this->size()  OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

         ALLOCATOR::_free(this->m_begin);

         this->m_begin = nullptr;

      }

      this->m_end = nullptr;
      
      m_nMaxSize = 0;

   }
   else if(this->m_begin == nullptr)
   {

      // create buffer big enough to hold number of requested elements or
      // m_nGrowBy elements, whichever is larger.
#ifdef SIZE_T_MAX
      if(::comparison::gt(nNewSize, SIZE_T_MAX / sizeof(TYPE)))
         throw_exception(error_no_memory);
      ASSERT(::comparison::lt(nNewSize, SIZE_T_MAX / sizeof(TYPE)));    // no overflow
#endif

      auto nAllocSize = maximum(nNewSize, m_nGrowBy);

#if MEMDLEAK  || defined(__MCRTDBG)

      if(::get_task() != nullptr)
      {

#if defined(__MCRTDBG)

         if(::get_task()->m_strFile.has_char())
         {

            this->m_begin = ALLOCATOR::alloc(nAllocSize, ::get_task()->m_strFile, ::get_task()->m_iLine);

         }
         else
         {

            this->m_begin = ALLOCATOR::alloc(nAllocSize, __FILE__, __LINE__);

         }

#else

         if (::get_task()->m_strDebug.has_char())
         {

            this->m_begin = ALLOCATOR::alloc(nAllocSize, "thread://" + typeid(*::get_task()).name()) + ", " + ::get_task()->m_strDebug + ", " + string(__FILE__), __LINE__;

         }
         else
         {

            this->m_begin = ALLOCATOR::alloc(nAllocSize, "thread://" + typeid(*::get_task()).name()) + ", " + string(__FILE__), __LINE__;

         }

#endif

      }
      else
      {

         this->m_begin = ALLOCATOR::alloc(nAllocSize, __FILE__, __LINE__);

      }

#else

      this->m_begin = ALLOCATOR::alloc(nAllocSize);

#endif

      if (::is_null(ptype))
      {

         ALLOCATOR::construct_count(this->m_begin, nNewSize);

      }
      else
      {

         ALLOCATOR::copy_construct_count(this->m_begin, nNewSize, *ptype);

      }

      this->m_end = this->m_begin + nNewSize;

      m_nMaxSize = nAllocSize;

   }
   else if(nNewSize <= m_nMaxSize)
   {

      if(nNewSize > this->size())
      {

         if (::is_null(ptype))
         {

            ALLOCATOR::construct_count(this->end(), nNewSize - this->size());

         }
         else
         {

            ALLOCATOR::copy_construct_count(this->end(), nNewSize - this->size(), *ptype);

         }

      }
      else if(this->size() > nNewSize)
      {

         ALLOCATOR::destruct_count(this->m_begin + nNewSize,this->size() - nNewSize OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

      }

      this->m_end = this->m_begin + nNewSize;

   }
   else
   {

      // otherwise, grow aaa_base_array
      nGrowBy = m_nGrowBy;

      if(nGrowBy == 0)
      {

         // heuristically determine growth when nGrowBy == 0
         //  (this avoids heap fragmentation in many situations)
         nGrowBy = this->size();
         nGrowBy = (nGrowBy < 4) ? 4 : ((nGrowBy > 1024) ? 1024 : nGrowBy);

      }

      ::count nNewMax;

      if(nNewSize < m_nMaxSize+ nGrowBy)
      {

         nNewMax = m_nMaxSize+ nGrowBy;  // granularity

      }
      else
      {

         nNewMax = nNewSize;  // no slush

      }

      ASSERT(nNewMax >= m_nMaxSize);  // no wrap around

      if(nNewMax  < m_nMaxSize)
      {

         throw_exception(error_bad_argument);

      }

#ifdef SIZE_T_MAX

      ASSERT(::comparison::lt(nNewMax, SIZE_T_MAX / sizeof(TYPE))); // no overflow

#endif

#if MEMDLEAK || defined(__MCRTDBG)

      TYPE* pNewData =  nullptr;

      if(::get_task() != nullptr)
      {

#if defined(__MCRTDBG)

         if(::get_task()->m_strFile.has_char())
         {

            pNewData = ALLOCATOR::alloc(nNewMax, ::get_task()->m_strFile,::get_task()->m_iLine);

         }
         else
         {

            pNewData = ALLOCATOR::alloc(nNewMax, __FILE__, __LINE__);

         }

#else

         if (::get_task()->m_strDebug.has_char())
         {

            pNewData = ALLOCATOR::alloc(nNewMax, "thread://" + typeid(*::get_task()).name()) + ", " + ::get_task()->m_strDebug + ", " + string(__FILE__), __LINE__;

         }
         else
         {

            pNewData = ALLOCATOR::alloc(nNewMax, "thread://" + typeid(*::get_task()).name()) + ", " + string(__FILE__), __LINE__;

         }

#endif

      }
      else
      {

         pNewData = ALLOCATOR::alloc(nNewMax, __FILE__, __LINE__);

      }


#else

      TYPE* pNewData = ALLOCATOR::alloc(nNewMax);

#endif

      // copy memory_new data from old
      ::acme::memcpy_s(pNewData,(size_t)nNewMax * sizeof(TYPE),this->m_begin,(size_t)this->size() * sizeof(TYPE));

      // construct remaining elements
      ASSERT(nNewSize > this->size());

      if (nNewSize > this->size())
      {

         if (::is_null(ptype))
         {

            ALLOCATOR::construct_count(pNewData + this->size(), nNewSize - this->size());

         }
         else
         {

            ALLOCATOR::copy_construct_count(pNewData + this->size(), nNewSize - this->size(), *ptype);

         }

      }

      // get rid of old stuff (note: no destructors called)
      ALLOCATOR::_free(this->m_begin);

      this->m_begin = pNewData;

      this->m_end = this->m_begin + nNewSize;

      m_nMaxSize = nNewMax;

   }

   return countOld;

}



template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
void array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::on_after_read()
{


}





template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline void array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::set_at_grow(::index nIndex, ARG_TYPE newElement, ::count nGrowBy)
{

   ASSERT(nIndex >= 0);

   if (nIndex >= this->size())
   {

      this->set_size(nIndex + 1, nGrowBy);

   }

   this->m_begin[nIndex] = newElement;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline TYPE & array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::element_at_grow(::index nIndex, ::count nGrowBy)
{

   ASSERT(nIndex >= 0);

   if (nIndex >= this->size())
   {

      this->set_size(nIndex + 1, nGrowBy);

   }

   return this->m_begin[nIndex];

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline void array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::set_each(ARG_TYPE element, ::index first, ::count in_count_out_last)
{

   prepare_first_in_count_last_out(first, in_count_out_last);

   for(::index i = first; i <= in_count_out_last; i++)
   {

      this->m_begin[i] = element;

   }

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
template < typename ITERATOR2 >
inline void array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::erase(const ITERATOR2 & begin, const ITERATOR2 & last)
{

   auto start = begin.index();

   auto end = last.index();

   if(start < 0 || end < start)
   {

      return;

   }

   auto count = end - start;

   erase_at(start, count);

}



template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
bool array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::prepare_first_last(::index & first, ::index & last) const
{

   if (first < 0)
   {

      first += this->get_count();

   }

   if (last < 0)
   {

      last += this->get_count();

   }

   return last >= first;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
bool array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::prepare_first_in_count_last_out(::index & first, ::count & in_count_out_last) const
{

   if (first < 0)
   {

      first += this->get_count();

   }

   if (in_count_out_last < 0)
   {

      in_count_out_last += this->get_count();

   }
   else
   {

      in_count_out_last = first + in_count_out_last - 1;

   }

   return in_count_out_last >= first;

}


//
// see collection_array_decl.h for declaration
//
// raw_array is an array that does not call constructors or destructor in elements
// array is an array that call only copy constructor and destructor in elements
// array is an array that call default constructors, copy constructs and destructors in elements

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::get_size() const
{
   return (::count) this->size();
}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::get_count() const
{
   return (::count) this->size();
}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::get_length() const
{
   return (::count) this->size();
}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::get_size_in_bytes() const
{
   return (::count)this->size() * sizeof(TYPE);
}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::get_byte_count() const
{
   return (::count) (this->size() * sizeof(TYPE));
}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::size() const
//{
//   return this->get_size();
//}
//

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::count() const
{
   return this->get_count();
}

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::length() const
{
   return this->get_length();
}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline bool array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::is_empty(::count countMinimum) const
//{
//   return this->size() < countMinimum;
//}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline bool array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::empty(::count countMinimum) const
//{
//   return is_empty(countMinimum);
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline bool array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::isEmpty(::count countMinimum) const
//{
//   return empty(countMinimum);
//}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline bool array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::has_elements(::count countMinimum) const
//{
//   return this->size() >= countMinimum;
//}
template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline ::index array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::get_lower_bound(::index i) const
{
   return i < this->size() ? i : -1;
}

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline ::index array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::get_middle_index(::index iIndex) const
{
   return this->size() / 2 + iIndex;
}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline ::index array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::get_upper_bound(::index iIndex) const
{
   return this->size() + iIndex;
}

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline bool array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::bounds(::index i) const
{
   return i >= 0 && i < this->size();
}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::erase_all()
{
   return allocate(0, -1);
}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::set_size(::index nNewSize, ::count nGrowBy) // does not call default constructors on memory_new items/elements
{
   return allocate(nNewSize, nGrowBy);
}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline void array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::clear()
{
   erase_all();
}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline void array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::erase_last()
{
   ASSERT(this->size() > 0);
   erase_at(get_upper_bound());
}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline void array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::zero(::index iStart,::count c)
{
   if(c < 0)
   {
      c = get_size() - iStart;
   }
   ::zero(&this->m_begin[iStart],c * sizeof(TYPE));
}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline const TYPE& array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::element_at(::index nIndex) const
{

   ASSERT(nIndex >= 0 && nIndex < this->size());

   return this->m_begin[nIndex];

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline TYPE& array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::element_at(::index nIndex)
{

   ASSERT(nIndex >= 0 && nIndex < this->size());

   return this->m_begin[nIndex];

}

//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline const TYPE& array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::first(::index nIndex) const
//{
//   return this->element_at(nIndex);
//}
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline TYPE& array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::first(::index nIndex)
//{
//   return this->element_at(nIndex);
//}
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline const TYPE& array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::last(::index i) const
//{
//   return this->element_at(this->get_upper_bound(i);
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline TYPE& array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::last(::index i)
//{
//   return this->element_at(this->get_upper_bound(i);
//}




//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline const TYPE* array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::get_data() const
//{
//   return (const TYPE*)this->m_begin;
//}
//
//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//inline TYPE* array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::get_data()
//{
//   return (TYPE*)this->m_begin;
//}

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline const TYPE& array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::operator[](::index i) const
{

   return this->m_begin[i];

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline TYPE& array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::operator[](::index i)
{

   return this->m_begin[i];

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline void array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::__swap(::index index1, ::index index2)
{

   ::__swap(this->m_begin[index1], this->m_begin[index2]);

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline void array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::__swap(iterator it1, iterator it2)
{

   TYPE t = *it1;

   *it1 = *it2;

   *it2 = t;

}



template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline const TYPE& array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::first(::index nIndex) const
{

   return this->element_at(nIndex);

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline TYPE & array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::first(::index nIndex)
{

   return this->element_at(nIndex);

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline const TYPE & array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::last(::index i) const
{

   return element_at(this->get_upper_bound(i));

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline TYPE & array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::last(::index i)
{

   return element_at(this->get_upper_bound(i));

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline const TYPE & array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::middle(::index i) const
{

   return element_at(this->get_middle_index(i));

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline TYPE & array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::middle(::index i)
{

   return element_at(this->get_middle_index(i));

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
void  array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::set_all(const TYPE & t)
{

   for (::index i = 0; i < get_count(); i++)
   {

      this->m_begin[i] = t;

   }

}


//template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
//template < typename VAR >
//inline array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::operator = (const payload_type < VAR > & a)
//{
//
//   ::count c = a.this_var()->array_get_count();
//
//   for(::index i = 0; i < c; i++)
//   {
//
//      add((ARG_TYPE)(payload_cast)a.this_var()->at(i));
//
//   }
//
//   return *this;
//
//}









template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline TYPE array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::pop(::index n)
{

   ::index i = this->get_upper_bound(n);

   TYPE t = element_at(i);

   this->erase_at(i);

   return t;

}

template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline TYPE array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::pop_first(::index i)
{

   auto t = ::transfer(this->first(i));

   this->erase_at(i);

   return t;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline void array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::pop_back(::index n)
{

   erase_at(this->get_upper_bound(n));

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline ::index array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::push(ARG_TYPE newElement, ::index n)
{

   return insert_at(this->get_upper_bound(n), newElement);

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline void array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::push_back(ARG_TYPE newElement, ::index n)
{

   insert_at(this->get_upper_bound(n), newElement);

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline TYPE array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::takeAt(::index i)
{

   TYPE t = element_at(i);

   this->erase_at(i);

   return t;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline TYPE array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::takeFirst(::index i)
{

   TYPE t = element_at(i);

   this->erase_at(i);

   return t;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline TYPE array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::takeLast(::index n)
{

   ::index i = this->get_upper_bound(n);

   TYPE t = element_at(i);

   this->erase_at(i);

   return t;

}


template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer >::array_base(const TYPE * p, ::count c)
{

   m_nGrowBy = 0;
   this->m_begin = nullptr;
   this->m_end = nullptr;
   m_nMaxSize = 0;

   set_size(c);

   for (::index i = 0; i < c; i++)
   {

      element_at(i) = p[i];

   }

}





template < typename TYPE, typename ARG_TYPE, typename ALLOCATOR, ::enum_type m_etypeContainer >
inline ::count array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > ::erase(const TYPE * begin, const TYPE * last)
{

   auto iStart = index_of(begin);

   auto iEnd = index_of(last);

   // iEnd exclusive
   return erase_at(iStart, iEnd - iStart);

}

//template < typename TYPE1, typename TYPE2 >
//concept is_same_family = ::std::is_base_of<TYPE1, TYPE2> || ::std::is_base_of<TYPE2, TYPE1>;


namespace generic
{


   namespace array
   {

   
      template < typename ARRAY, typename CONTAINER >
      ARRAY & append(ARRAY & a, const CONTAINER & container)
      {
         
         if constexpr( ::std::is_base_of_v<ARRAY, CONTAINER> || ::std::is_base_of_v<CONTAINER, ARRAY>)
         {
            
            a.append(container);
            
         }
         else
         {
            
            for (auto & item : container)
            {
               
               ::copy(a.add_new(), item);
               
            }
            
         }
         
         return a;
         
      }


      template < typename ARRAY, typename CONTAINER >
      ARRAY & copy(ARRAY & a, const CONTAINER & container)
      {
         
         if constexpr(::std::is_base_of_v<ARRAY, CONTAINER> || ::std::is_base_of_v<CONTAINER, ARRAY>)
         {
            
            a.append(container);
            
         }
         else
         {
            
            a.clear();
            
            append(a, container);
            
         }
         
         return a;
         
      }


   } // namespace array


} // namespace generic


