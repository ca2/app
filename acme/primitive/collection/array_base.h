#pragma once

//
//#include "_iterator.h"
//#include "acme/memory/typed.h"
//#include "acme/memory/typed_memory.h"
//#include "acme/platform/common.h"
//
////using tiny_index_array = tiny_array <::index>;
//
//
//CLASS_DECL_ACME ::string get_task_object_name();
//
//#ifdef _DEBUG
//
//CLASS_DECL_ACME ::string get_task_object_debug();
//
//#endif
//
//
//#define __default_array_array_base_non_particle(TYPE) ::array_base_non_particle < TYPE, const TYPE &, ::allocator::def < TYPE > >
//
//
//#define DECLARE_TYPED_ARRAY_ACCESSOR_OF(ITEM, CONTAINER, TYPE, CONTAINER_TYPE) \
//::pointer<TYPE>& ITEM ## _at(::index i) { return CONTAINER[i]; } \
//const TYPE * ITEM ## _at(::index i) const { return CONTAINER[i]; } \
//::pointer<TYPE>* ITEM ## _data() { return CONTAINER.data(); } \
//::pointer<TYPE>const * ITEM ## _data() const { return CONTAINER.data(); } \
//TYPE * get_ ## ITEM(::index i) const { return CONTAINER.bounds(i) ? CONTAINER[i] : nullptr; } \
//::count ITEM ## _count() const { return CONTAINER.get_count(); } \
//bool has_ ## ITEM() const { return CONTAINER.has_element(); } \
//const CONTAINER_TYPE & ITEM ## a() const { return CONTAINER; } \
//CONTAINER_TYPE & ITEM ## a() { return CONTAINER; } \
//bool contains_ ## ITEM(const TYPE * p) const { return CONTAINER.contains(p); } \
//bool is_there_no_ ## ITEM() const { return CONTAINER.is_empty(); } \
//bool has_no_ ## ITEM() const { return is_there_no_ ## ITEM(); } \
//::index find_first_ ## ITEM(const TYPE * p, ::index iStart = 0, ::count nCount = -1) const { return CONTAINER.find_first(p, iStart, nCount); } \
//::pointer<TYPE>& first_ ## ITEM() { return CONTAINER.first_pointer(); } \
//::pointer<TYPE>& last_ ## ITEM() { return CONTAINER.last_pointer(); } \
//TYPE * get_first_ ## ITEM() const { return CONTAINER.get_first_pointer(); } \
//TYPE * get_last_ ## ITEM() const { return CONTAINER.get_last_pointer(); } \
//::index ITEM ## _first_index(::index i = 0) const { return CONTAINER.first_index(i); } \
//::index ITEM ## _last_index(::index i = -1) const { return CONTAINER.last_index(i); } \
//CONTAINER_TYPE CONTAINER
//
//#define DECLARE_ARRAY_ACCESSOR_OF(ITEM, CONTAINER, TYPE) \
//DECLARE_TYPED_ARRAY_ACCESSOR_OF(ITEM, CONTAINER, TYPE, pointer_array < TYPE >)
//
//#define DECLARE_TYPED_ARRAY_OF(ITEM, CONTAINER, TYPE, CONTAINER_TYPE) \
//::index add_ ## ITEM(TYPE * p) { return CONTAINER.add_item(p); }      \
//::index add_ ## ITEM ## _array(const CONTAINER_TYPE & a) { return CONTAINER.append(a); } \
//::index add_unique_ ## ITEM(TYPE * p) { return CONTAINER.add_unique(p); } \
//::index add_unique_ ## ITEM ## _array(const CONTAINER_TYPE & a) { return CONTAINER.add_unique(a); } \
//::index erase_ ## ITEM(TYPE * p) { return CONTAINER.erase(p); } \
//CONTAINER_TYPE ITEM ## a_section(::index iStart = 0, ::count nCount = -1){return CONTAINER.slice < CONTAINER_TYPE >(iStart, nCount);} \
//template < typename ARRAY > \
//void ITEM ## a_slice(ARRAY & a, ::index iStart = 0, ::count nCount = -1){ CONTAINER.slice(a, iStart, nCount);} \
//DECLARE_TYPED_ARRAY_ACCESSOR_OF(ITEM, CONTAINER, TYPE, CONTAINER_TYPE)
//
//#define HAVE_ARRAY_OF(ITEM, CONTAINER, TYPE) \
//DECLARE_TYPED_ARRAY_OF(ITEM, CONTAINER, TYPE, pointer_array < TYPE >)
//
//#define DECLARE_ARRAY_CONTAINER_OF(ARRAY, ITEM, CONTAINER, TYPE) \
//ARRAY(const ::std::initializer_list < ::pointer<TYPE >>& list) : CONTAINER(list) { } \
//DECLARE_TYPED_ARRAY_OF(ITEM, CONTAINER, TYPE, pointer_array < TYPE >)
//
//#define DECLARE_ARRAY_OF(ARRAY, ITEM, TYPE) \
//DECLARE_ARRAY_CONTAINER_OF(ARRAY, ITEM, m_ ## ITEM ## a, TYPE)
//
//template < typename TYPE >
//class pointer_rear_iterator
//{
//public:
//
//
//   using ITEM = non_const < TYPE >;
//   using ITEM_POINTER = ITEM *;
//
//   using iterator = ::pointer_rear_iterator < ITEM >;
//   using const_iterator = ::pointer_rear_iterator < const ITEM >;
//
//
//   TYPE* m_p;
//
//
//   pointer_rear_iterator() { m_p = nullptr; }
//   pointer_rear_iterator(const ITEM * p) { m_p = (TYPE *) p; }
//   pointer_rear_iterator(const iterator & i) { m_p = (TYPE *)i.m_p; }
//   pointer_rear_iterator(const const_iterator & i) { m_p = (TYPE *)i.m_p; }
//
//
//   auto& operator *() { return *m_p; }
//   auto& operator *() const { return *m_p; }
//   auto operator ->() { return m_p; }
//   auto operator ->() const { return m_p; }
//
//   pointer_rear_iterator & operator ++()
//   {
//      m_p--;
//      return *this;
//
//   }
//   pointer_rear_iterator& operator --()
//   {
//      m_p++;
//      return *this;
//
//   }
//
//   pointer_rear_iterator operator ++(int)
//   {
//      auto p = *this;
//      m_p--;
//
//      return p;
//
//   }
//   pointer_rear_iterator operator --(int)
//   {
//      auto p = *this;
//      m_p++;
//
//      return p;
//
//   }
//   template < primitive_integral INTEGRAL >
//   pointer_rear_iterator operator +(INTEGRAL i)
//   {
//
//      return m_p - i;
//
//   }
//   template < primitive_integral INTEGRAL >
//   pointer_rear_iterator operator -(INTEGRAL i)
//   {
//
//      return m_p + i;
//
//   }
//
//   template < primitive_integral INTEGRAL >
//   pointer_rear_iterator & operator +=(INTEGRAL i)
//   {
//      m_p -= i;
//      return *this;
//
//   }
//   template < primitive_integral INTEGRAL >
//   pointer_rear_iterator & operator -=(INTEGRAL i)
//   {
//      m_p += i;
//      return *this;
//
//   }
//
//
//   bool operator ==(const pointer_rear_iterator& p) const { return m_p == p.m_p; }
//   bool operator ==(const TYPE * p) const { return m_p == p; }
//   ::std::strong_ordering operator <=>(const pointer_rear_iterator& p) const { return this->m_p <=> p.m_p; }
//
//   ::count operator - (const pointer_rear_iterator& p) const { return this->m_p - p.m_p; }
//
//};
//
//
//template < typename A, typename B >
//auto distance(const pointer_rear_iterator < A > & a, const pointer_rear_iterator < B > & b) { return (a < b) ? (b - a) : (a - b); }
//template < typename A, typename B >
//auto distance(const A * pa, const B * pb) { return (pa < pb) ? (pb - pa) : (pa - pb); }
//
//
//// raw_array is an array that does not call constructors or destructor in elements
//// array is an array that call only copy constructor and destructor in elements
//// array is an array that call default constructors, copy constructs and destructors in elements
//template < class TYPE, class ARG_TYPE, class TYPED, class MEMORY, ::enum_type t_etypeContainer >
//class array_base_non_particle :
//   //virtual public ::particle,
//   //public ::array_range < ::range < TYPE * > >
//   public ::range < TYPE * >,
//   public TYPED,
//   public MEMORY
//{
//public:
//
//
//   using rear_iterator = ::pointer_rear_iterator<TYPE>;
//   using const_rear_iterator = ::pointer_rear_iterator<const TYPE>;
//
//   //using ARRAY_RANGE = ::array_range < ::range < TYPE * > >;
//   using ARRAY_RANGE = ::range < TYPE * >;
//   using array_range = ::range < TYPE * >;
//
//   using PRIMITIVE_CONTAINER_TAG = PRIMITIVE_CONTAINER_TAG_TYPE;
//
//   using CONTAINER_ITEM_TYPE = TYPE;
//   using TYPE_IS_PTR = TYPE;
//
//   using this_iterator = typename ARRAY_RANGE::this_iterator;
//   using iterator = typename ARRAY_RANGE::iterator;
//   using const_iterator = typename ARRAY_RANGE::const_iterator;
//
//
//   ::count   m_countAllocation;
//   ::count   m_countAddUp;
//
//
//   array_base_non_particle();
//   array_base_non_particle(std::initializer_list < TYPE > initializer_list);
//   array_base_non_particle(const array_base_non_particle & a);
//   array_base_non_particle(array_base_non_particle && a) noexcept;
//   array_base_non_particle(const TYPE * p, ::count c);
//   array_base_non_particle(::range < const_iterator > constrange) : array_base_non_particle(constrange.begin(), constrange.end()) {}
//   template < primitive_integral INTEGRAL >
//   array_base_non_particle(const_iterator begin, INTEGRAL count) : array_base_non_particle(begin, begin + count) {}
//   array_base_non_particle(const_iterator begin, const_iterator end)
//   {
//      auto p = this->begin();
//      while (p != end) add(*p);
//   }
//   virtual ~array_base_non_particle();
//
//
//   void defer_destroy()
//   {
//
//      if (this->m_begin != nullptr)
//      {
//
//         destroy();
//
//      }
//
//   }
//
//
//   array_base_non_particle & operator = (const array_base_non_particle & a)
//   {
//
//      if (this != &a)
//      {
//         
//         auto c = a.size();
//         
//         set_size(c);
//         
//         auto ptarget = this->data();
//         
//         auto psource = a.data();
//
//         while(c > 0)
//         {
//            
//            *ptarget = *psource;
//            
//            ptarget++;
//            
//            psource++;
//            
//            c--;
//            
//         }
//
//      }
//      
//      return *this; 
//   
//   }
//
//
//   array_base_non_particle & operator = (array_base_non_particle && array_base_non_particle)
//   {
//
//      if (this != &array_base_non_particle)
//      {
//
//         transfer(::transfer(array_base_non_particle));
//
//      }
//      
//      return *this;
//   
//   }
//
//
//
//   void add_initializer_list(const ::std::initializer_list < TYPE > & initializer_list)
//   {
//
//      for (auto & item : initializer_list)
//      {
//
//         add_item(item);
//
//      }
//
//   }
//
//
//   inline array_base_non_particle & transfer(array_base_non_particle && a)
//   {
//
//      if (this != &a)
//      {
//
//         destroy();
//
//         ARRAY_RANGE::operator=(::transfer(a));
//
//         m_countAddUp = a.m_countAddUp;
//
//         m_countAllocation = a.m_countAllocation;
//
//      }
//
//      return *this;
//
//   }
//
//
//   inline ::range<rear_iterator> rear_payloads()
//   { 
//
//      return ::range<rear_iterator>(this->rear_begin(), this->rear_end());
//   
//   }
//
//
//   inline ::range<const_rear_iterator> rear_payloads() const
//   {
//
//      return ::range<const_rear_iterator>(this->rear_begin(), this->rear_end());
//
//   }
//
//   //template < typename iterator >
//   //struct make_iterator : iterator
//   //{
//
//   //   using CONTAINER = typename iterator::CONTAINER;
//
//
//   //   make_iterator()
//   //   {
//   //      this->m_pelementBeg = (TYPE *)nullptr;
//   //      this->m_pelementEnd = (TYPE *)nullptr;
//   //      this->m_pcontainer = (CONTAINER *)nullptr;
//   //      this->m_pelement = this->m_pelementBeg;
//   //   }
//
//   //   make_iterator(::index iStart, ::index iEnd, const CONTAINER * parray = nullptr)
//   //   {
//   //      this->m_pelementBeg = (TYPE *)(parray->m_begin + iStart);
//   //      this->m_pelementEnd = (TYPE *)(parray->m_begin + (iEnd < 0 ? parray->size() + iEnd + 1 : iEnd));
//   //      this->m_pcontainer = (CONTAINER *)parray;
//   //      this->m_pelement = this->m_pelementBeg;
//   //   }
//
//   //   make_iterator(const CONTAINER * parray, const TYPE * pmatter = nullptr, const TYPE * pelementEnd = nullptr)
//   //   {
//   //      this->m_pelementBeg = (TYPE *)pmatter;
//   //      this->m_pelementEnd = (TYPE *)pelementEnd;
//   //      this->m_pcontainer = (CONTAINER *)parray;
//   //      this->m_pelement = this->m_pelementBeg;
//   //   }
//
//
//   //   make_iterator(const make_iterator & iterator)
//   //   {
//   //      this->m_pelementBeg = (TYPE *)iterator.m_pelementBeg;
//   //      this->m_pelementEnd = (TYPE *)iterator.m_pelementEnd;
//   //      this->m_pelement = iterator.m_pelement;
//   //      this->m_pcontainer = iterator.m_pcontainer;
//   //   }
//
//
//   //   make_iterator begin()
//   //   {
//
//   //      return make_iterator(this->m_pcontainer, this->m_pelementBeg, this->m_pelementEnd);
//
//   //   }
//
//
//   //   make_iterator end()
//   //   {
//
//   //      return make_iterator(this->m_pcontainer, this->m_pelementEnd, this->m_pelementEnd);
//
//   //   }
//
//
//   //   make_iterator & operator ++ ()
//   //   {
//
//   //      this->m_pelement++;
//   //      return *this;
//
//   //   }
//
//
//   //   make_iterator operator ++ (i32)
//   //   {
//
//   //      auto it = *this;
//
//   //      this->m_pelement++;
//   //      return it;
//
//   //   }
//
//
//   //   make_iterator operator + (::count c) const
//   //   {
//
//   //      return { this->m_pcontainer, this->m_pelement + c };
//
//   //   }
//
//
//   //   make_iterator operator - (const make_iterator & it) const
//   //   {
//
//   //      return { this->m_pcontainer, this->m_pelement - it.index() };
//
//   //   }
//
//
//   //   bool operator == (const make_iterator & it) const
//   //   {
//
//
//   //      if (this->m_pcontainer != it.m_pcontainer)
//   //      {
//
//   //         return false;
//
//   //      }
//
//   //      return this->m_pelement == it.m_pelement;
//
//   //   }
//
//
//   //   bool operator >= (const make_iterator & it) const
//   //   {
//
//
//   //      if (this->m_pcontainer != it.m_pcontainer)
//   //      {
//
//   //         return false;
//
//   //      }
//
//   //      return this->m_pelement >= it.m_pelement;
//
//   //   }
//
//
//   //   bool operator > (const make_iterator & it) const
//   //   {
//
//   //      if (this->m_pcontainer != it.m_pcontainer)
//   //      {
//
//   //         return false;
//
//   //      }
//
//   //      return this->m_pelement > it.m_pelement;
//
//   //   }
//
//
//   //   bool operator != (const make_iterator & it) const
//   //   {
//
//   //      if (this->m_pcontainer != it.m_pcontainer)
//   //      {
//
//   //         return true;
//
//   //      }
//
//   //      return this->m_pelement != it.m_pelement;
//
//   //   }
//
//   //   bool operator < (const make_iterator & it) const
//   //   {
//
//   //      if (this->m_pcontainer != it.m_pcontainer)
//   //      {
//
//   //         return false;
//
//   //      }
//
//   //      return this->m_pelement < it.m_pelement;
//
//
//   //   }
//
//   //   bool operator <= (const make_iterator & it) const
//   //   {
//
//   //      if (this->m_pcontainer != it.m_pcontainer)
//   //      {
//
//   //         return false;
//
//   //      }
//
//   //      return this->m_pelement <= it.m_pelement;
//
//
//   //   }
//
//
//   //   bool operator == (const TYPE * pmatter) const
//   //   {
//
//
//   //      if (!this->m_pcontainer->contains(pmatter))
//   //      {
//
//   //         return false;
//
//   //      }
//
//   //      return this->m_pelement == pmatter;
//
//   //   }
//
//
//   //   bool operator >= (const TYPE * pmatter) const
//   //   {
//
//
//   //      if (!this->m_pcontainer->contains(pmatter))
//   //      {
//
//   //         return false;
//
//   //      }
//
//   //      return this->m_pelement >= pmatter;
//
//   //   }
//
//
//   //   bool operator > (const TYPE * pmatter) const
//   //   {
//
//   //      if (!this->m_pcontainer->contains(pmatter))
//   //      {
//
//   //         return false;
//
//   //      }
//
//   //      return this->m_pelement > pmatter;
//
//   //   }
//
//
//   //   bool operator != (const TYPE * pmatter) const
//   //   {
//
//   //      if (!this->m_pcontainer->contains(pmatter))
//   //      {
//
//   //         return true;
//
//   //      }
//
//   //      return this->m_pelement != pmatter;
//
//   //   }
//
//   //   bool operator < (const TYPE * pmatter) const
//   //   {
//
//   //      if (!this->m_pcontainer->contains(pmatter))
//   //      {
//
//   //         return false;
//
//   //      }
//
//   //      return this->m_pelement < pmatter;
//
//
//   //   }
//
//   //   bool operator <= (const TYPE * pmatter) const
//   //   {
//
//   //      if (!this->m_pcontainer->contains(pmatter))
//   //      {
//
//   //         return false;
//
//   //      }
//
//   //      return this->m_pelement <= pmatter;
//
//
//   //   }
//
//   //   make_iterator & operator = (const make_iterator & it)
//   //   {
//
//   //      if (this != &it)
//   //      {
//
//   //         this->m_pcontainer = it.m_pcontainer;
//
//   //         this->m_pelement = it.m_pelement;
//
//   //      }
//
//   //      return *this;
//
//   //   }
//
//   //   ::index index() const { return this->m_pelement - this->m_pcontainer->m_begin; }
//
//   //};
//
//   //__declare_iterator(iterator, this->m_pelement);
//   //__declare_iterator(ref_iterator, *this->m_pelement);
//
//   void this_is_a_container() {}
//
//   //enum_type get_payload_type() const override { return t_etypeContainer; }
//
//
//   inline memsize length_in_bytes() const { return this->size() * sizeof(TYPE); }
//
//   //inline auto values(index iStart = 0, index iEnd = -1) const { return iterator(iStart, iEnd, this); }
//
//
//   //inline iterator begin()
//   //{
//
//   //   return iterator(0, (::index)this->size(), this);
//
//   //}
//
//
//   //inline iterator end()
//   //{
//
//   //   return iterator((::index)this->size(), (::index)this->size(), this);
//
//   //}
//
//
//
//
//
//   //inline const TYPE * get_data() const { return this->begin(); }
//   //inline TYPE * get_data() { return this->begin(); }
//
//
//
//
//   inline bool contains_address(const TYPE * pmatter) const { return pmatter >= this->m_begin && pmatter < this->end(); }
//
//
//   inline ::count get_size() const;
//   inline ::count get_size_in_bytes() const;
//   inline ::count get_count() const;
//   inline ::count get_byte_count() const;
//   inline ::count get_length() const;
//   //inline ::count size() const;
//   inline ::count count() const;
//   inline ::count length() const;
//   inline ::count byte_count() const { return get_byte_count(); }
//
//
//   inline bool has_element() const noexcept { return this->size() > 0; }
//   inline bool is_empty(::count countMinimum = 0) const noexcept { return this->size() <= countMinimum; }
//   inline bool empty(::count countMinimum = 0) const noexcept { return this->size() <= countMinimum; }
//   inline bool has_elements(::count countMinimum = 1) const noexcept { return this->size() >= countMinimum; }
//   inline ::index get_lower_bound(::index i = 0) const;
//   inline ::index get_middle_index(::index i = 0) const;
//   inline ::index get_upper_bound(::index i = -1) const;
//   inline ::index lower_bound(::index i = 0) const { return this->get_lower_bound(i); }
//   inline ::index upper_bound(::index i = -1) const { return this->get_upper_bound(i); }
//   inline ::index first_index(::index i = 0) const { return this->lower_bound(i); }
//   inline ::index middle_index(::index i = 0) const { return this->get_middle_index(i); }
//   inline ::index last_index(::index i = -1) const { return this->get_upper_bound(i); }
//   inline bool bounds(::index i) const;
//   inline bool contains_index(::index i) const { return  bounds(i); }
//
//
//   inline this_iterator back(::index i = -1) { return (this_iterator)(this->begin() + this->get_upper_bound(i)); }
//   inline const_iterator back(::index i = -1) const { return (const_iterator)(this->begin() + this->get_upper_bound(i)); }
//
//   void ensure_index_ok(::index nIndex) const { if (nIndex < 0 || nIndex >= this->size()) throw_exception(error_index_out_of_bounds); }
//
//   inline const TYPE * ptr_at(::index nIndex) const { return this->m_begin + nIndex; }
//   inline TYPE * ptr_at(::index nIndex) { return this->m_begin + nIndex; }
//
//   inline const TYPE & element_at(::index nIndex) const;
//   inline TYPE & element_at(::index nIndex);
//
//   inline const TYPE& at(::index nIndex) const { ensure_index_ok(nIndex); return element_at(nIndex); }
//   inline TYPE& at(::index nIndex) { ensure_index_ok(nIndex); return element_at(nIndex); }
//
//   inline TYPE & first(::index n = 0);
//   inline const TYPE & first(::index n = 0) const;
//
//   inline TYPE & last(::index n = -1);
//   inline const TYPE & last(::index n = -1) const;
//
//   inline TYPE & middle(::index n = 0);
//   inline const TYPE & middle(::index n = 0) const;
//
//   inline void set_at_grow(::index nIndex, ARG_TYPE newElement);
//   inline TYPE & element_at_grow(::index nIndex);
//
//   inline void set_each(ARG_TYPE element, ::index iStart = 0, ::count c = -1);
//
//   template < ::std::size_t N >
//   TYPE & get() { return element_at(N); }
//
//
//   void reserve(::count newAllocationSize);
//
//   
//   ::count set_size(::count nNewSize);
//   
//
//   //::count set_size(::count nNewSize, ::count nGrowBy = -1); // does not call default constructors on new items/elements
//   
//   /// if bRaw is true does not call default constructors on new elements
//   template < pointer_not_castable_to < TYPE * > P >
//   ::count allocate(::count nNewSize, bool bShrink, bool bRaw, P & p)
//   {
//      TYPE t(p);
//      return _allocate(nNewSize, bShrink, bRaw, &t);
//   }
//   template < pointer_castable_to < TYPE * > T >
//   ::count allocate(::count nNewSize, bool bShrink, bool bRaw, T & t)
//   {
//      return _allocate(nNewSize, bShrink, bRaw, &t);
//   }
//   ::count allocate(::count nNewSize, bool bShrink, bool bRaw)
//   {
//      return _allocate(nNewSize, bShrink, bRaw, nullptr);
//   }
//   ::count _allocate(::count nNewSize, bool bShrink, bool bRaw, const TYPE * type);
//   
//   //::count allocate(::count nNewSize, bool bShrink, const TYPE * ptype = nullptr);
//   
//   ::count allocate_in_bytes(::count nNewSize, bool bShrink, bool bRaw);
//   
////   ::count set_raw_size(::count nNewSize, ::count nGrowBy = -1); // does not call constructors and destructors on items/elements
//   
//   ::count resize(::count nNewSize) { return set_size(nNewSize); }
//   ::count resize(::count nNewSize, ARG_TYPE t);
//
//   void free_extra();
//   virtual void destroy();
//
//   inline void __swap(::index index1, ::index index2);
//   inline void __swap(iterator index1, iterator index2);
//   inline void __swap(const_iterator index1, const_iterator index2);
//
//
//   void set_all(const TYPE & t);
//
//
//   rear_iterator rear_begin()
//   {
//      return this->m_end - 1;
//   }
//
//   rear_iterator rear_end()
//   {
//      return this->m_begin - 1;
//   }
//
//   const_rear_iterator rear_begin() const
//   {
//      return (const_rear_iterator&)this->m_end - 1;
//   }
//
//   const_rear_iterator rear_end() const
//   {
//      return (const_rear_iterator&)this->m_begin - 1;
//   }
//
//
//   void zero(::index iStart = 0, ::count c = -1);
//
//   //template < primitive_array ARRAY >
//   //void _001RemoveIndexes(ARRAY & ia);
//   
//   template < primitive_array ARRAY >
//   void erase_indexes(const ARRAY & ia);
//
//   template < primitive_array ARRAY >
//   void erase_descending_indexes(const ARRAY & ia);
//
//
//   inline bool prepare_first_last(::index & first, ::index & last) const;
//   inline bool prepare_first_in_count_last_out(::index & first, ::count & inCountLastOut) const;
//
//
//   inline void erase_last();
//   inline ::count erase_all();
//   inline void clear();
//
//
//   void on_construct_element(TYPE * p) { TYPED::construct(p); }
//   void on_construct_element(TYPE * p, ::count c) { TYPED::construct_count(p, c); }
//   void on_destruct_element(TYPE * p) { TYPED::destruct(p); }
//   void on_copy_element(::index i, const TYPE * p) { TYPED::copy(&this->m_begin[i], p); }
//
//
//   // FISC - Flaw in some compiler
//   //inline operator TYPE *() { return this->m_begin; }
//   //inline operator const TYPE *() const { return this->m_begin; }
//
//
//   inline const TYPE & operator[](::index i) const { return this->m_begin[i]; }
//   inline TYPE & operator[](::index i) { return this->m_begin[i]; }
//
//   
//   TYPE * raw_allocate_at(::index i, ::count c);
//   
//
//   TYPE & insert_at(::index nIndex, const TYPE & newElement, ::count nCount = 1);
//   TYPE * insert_at(::index nStartIndex, const TYPE * p, ::count nCount = 1);
//
//   TYPE * insert_array_at(::index nStartIndex, const array_base_non_particle * pNewArray);
//
//
//   ::index erase_at(::index nIndex, ::count nCount = 1);
//
//   //::index allocate_at(::index nIndex, ::count nCount = 1);
//
//
//   TYPE pick_at(::index nIndex);
//   TYPE pick_first(::index nIndex = 0) { return ::transfer(pick_at(nIndex)); }
//   TYPE pick_last(::index nIndex = -1) { return ::transfer(pick_at(this->size() + nIndex)); }
//   array_base_non_particle pick_at(::index nIndex, ::count nCount);
//
//
//   ::index erase_item(TYPE * p);
//
//   ::index index_of(const TYPE * p) const { auto i = p - this->m_begin; return i >= 0 && i < this->size() ? i : -1; }
//
//
//   bool erase(const TYPE * p) { auto i = index_of(p); if (not_found(i)) return false; return found(erase_at(i)); }
//   ::count erase(const TYPE * begin, const TYPE * end);
//
//   iterator erase(iterator p) 
//   { 
//
//      this->erase_at(index_of(p));
//   
//      return p;
//   
//   }
//
//   template < typename ITERATOR2 >
//   inline void erase(const ITERATOR2 & begin, const ITERATOR2 & last);
//
//
//   inline TYPE pop(::index i = -1);
//   inline ::index push(ARG_TYPE newElement);
//   inline void pop_back(::index i = -1);
//   inline TYPE & add_item(ARG_TYPE newElement);
//   inline TYPE & add(ARG_TYPE newElement) { return this->add_item(newElement); }
//   inline TYPE& add_new();
//
//
//   inline TYPE pop_first(::index i = 0);
//
//   inline TYPE takeAt(::index i);
//   inline TYPE takeFirst(::index i = 0);
//   inline TYPE takeLast(::index i = -1);
//
//   virtual ::count append(const array_base_non_particle & src); // return old size_i32
//   virtual void copy(const array_base_non_particle & src);
//
//
//   template < primitive_container CONTAINER >
//   ::count append(const CONTAINER & container)
//   {
//
//      ::count c = 0;
//
//      for (auto& item : container)
//      {
//
//         add(item);
//
//         c++;
//
//      }
//
//      return c;
//
//   }
//
//
//
//   virtual void on_after_read();
//
//   template < typename PRED >
//   ::count predicate_each(PRED pred, ::index iStart = 0, ::count c = -1)
//   {
//
//      ::index iEnd = c < 0 ? get_count() + c : iStart + c - 1;
//
//      int cProcessed = 0;
//
//      for (::index i = iStart; i <= iEnd; i++)
//      {
//
//         pred(this->m_begin[i]);
//
//         cProcessed++;
//
//      }
//
//      return cProcessed;
//
//   }
//
//   template < typename PRED >
//   ::count predicate_each(PRED pred, ::index iStart = 0, ::count c = -1) const
//   {
//
//      return ((array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >*)this)->predicate_each(pred, iStart, c);
//
//   }
//
//
//   inline bool is_index_ok(::index iIndex) const { return iIndex >= 0 && iIndex < get_count(); }
//
//   
//   inline bool is_last_index(::index iIndex) const { return iIndex >= get_upper_bound(); }
//
//
//   template < typename PRED >
//   bool predicate_contains(PRED pred, ::index iStart = 0, ::index iEnd = -1) const
//   {
//
//      return this->predicate_find_first(pred, iStart, iEnd) >= 0;
//
//   }
//
//   template < typename OTHER_IS_PTR >
//   TYPE_IS_PTR get_existing_defer_add(const OTHER_IS_PTR & p)
//   {
//
//      for (::index i = 0; i < this->get_count(); i++)
//      {
//
//         auto & pelementHere = this->element_at(i);
//
//         if (pelementHere == p)
//         {
//
//            return pelementHere;
//
//         }
//         else if (*pelementHere == *p)
//         {
//
//            return pelementHere;
//
//         }
//
//      }
//
//      this->add(p);
//
//      return p;
//
//   }
//
//
//   template < typename OTHER_IS_PTR >
//   void defer_use_existing(OTHER_IS_PTR & p)
//   {
//
//      for (::index i = 0; i < this->get_count(); i++)
//      {
//
//         auto & pelementHere = this->element_at(i);
//
//         if (pelementHere == p)
//         {
//
//            return;
//
//         }
//         else if (*pelementHere == *p)
//         {
//
//            p = pelementHere;
//
//            return;
//
//         }
//
//      }
//
//      this->add(p);
//
//   }
//
//
//   template < typename OTHER_IS_PTR >
//   TYPE_IS_PTR get_existing(const OTHER_IS_PTR & p) const
//   {
//
//      for (::index i = 0; i < this->get_count(); i++)
//      {
//
//         auto & pelementHere = this->element_at(i);
//
//         if (pelementHere == p)
//         {
//
//            return pelementHere;
//
//         }
//         else if (*pelementHere == *p)
//         {
//
//            return pelementHere;
//
//         }
//
//      }
//
//      return p;
//
//   }
//
//
//   template < typename OBJECT, typename ATTRIBUTE >
//   TYPE_IS_PTR merge_get_existing(const TYPE_IS_PTR & p, const OBJECT& pparticle, const ATTRIBUTE& attribute)
//   {
//
//      auto pModified = __call__allocate< typename TYPE_IS_PTR::TYPE >(*p);
//
//      pModified->process(pparticle, attribute);
//
//      return this->get_existing(pModified);
//
//   }
//
//
//   template < typename PRED >
//   ::index predicate_find_first(PRED pred, ::index iStart = 0, ::index iEnd = -1) const
//   {
//
//      if (iEnd < 0)
//      {
//
//         iEnd += get_count();
//
//      }
//
//      if (iEnd >= get_count())
//      {
//
//         iEnd = get_count() - 1;
//
//      }
//
//      for (::index i = iStart; i <= iEnd; i++)
//      {
//
//         if (pred(this->m_begin[i]))
//         {
//
//            return i;
//
//         }
//
//      }
//
//      return -1;
//
//   }
//
//
//   template < typename PRED >
//   ::index predicate_find_last(PRED pred, ::index iLast = -1)
//   {
//
//      if (iLast < 0)
//      {
//
//         iLast += get_count();
//
//      }
//
//      for (::index i = iLast; i >= 0; i--)
//      {
//
//         if (pred(this->m_begin[i]))
//         {
//
//            return i;
//
//         }
//
//      }
//
//      return -1;
//
//   }
//
//
//   template < typename PRED >
//   TYPE * predicate_get_first(PRED pred)
//   {
//
//      for (int i = 0; i < get_count(); i++)
//      {
//
//         if (pred(this->m_begin[i]))
//         {
//
//            return &element_at(i);
//
//         }
//
//      }
//
//      return nullptr;
//
//   }
//
//
//   template < typename PRED >
//   ::count predicate_get_count(PRED pred)
//   {
//
//      ::count c = 0;
//
//      for (int i = 0; i < get_count(); i++)
//      {
//
//         if (pred(this->m_begin[i]))
//         {
//
//            c++;
//
//         }
//
//      }
//
//      return c;
//
//   }
//
//
//   template < typename PRED >
//   ::count predicate_erase(PRED pred)
//   {
//
//      ::count cTotal = 0;
//
//      for (int i = 0; i < get_count();)
//      {
//
//         if (!pred(this->m_begin[i]))
//         {
//
//            i++;
//
//         }
//         else
//         {
//
//            int iStart = i;
//
//            int iCount = 1;
//
//            i++;
//
//            for (; i < get_count();)
//            {
//
//               if (!pred(this->m_begin[i]))
//               {
//
//                  break;
//
//               }
//
//               iCount++;
//
//               i++;
//
//            }
//
//            erase_at(iStart, iCount);
//
//            cTotal += iCount;
//
//            i = iStart;
//
//         }
//
//      }
//   
//      return cTotal;
//
//   }
//
//
//   template < typename F >
//   void each(F f)
//   {
//
//      for (::index i = 0; i < get_count(); i++)
//      {
//
//         f(this->m_begin[i]);
//
//      }
//
//   }
//
//
//   template < typename PRED >
//   void predicate_sort(PRED pred);
//
//
//   template < typename T, typename PRED >
//   ::index predicate_binary_search(const T & t, PRED pred) const;
//
//
//   inline bool valid_iter(iterator first, iterator last)
//   {
//
//      return first < last;
//
//   }
//
//
//   inline bool rvalid_iter(iterator first, iterator last)
//   {
//
//      return first > last;
//
//   }
//
//
//   inline TYPE& operator%(::index nIndex)
//   {
//
//      return this->element_at(nIndex% this->get_size());
//
//   }
//
//
//   inline const TYPE& operator%(::index nIndex) const
//   {
//
//      return this->element_at(nIndex% this->get_size());
//
//   }
//
//
//   bool is_version(index i)
//   {
//
//      return true;
//
//      //if (!m_pvarOptions)
//      //{
//
//      //   return i <= 0;
//
//      //}
//
//      //return i <= options()["version"].i32();
//
//   }
//
//
//};


#include "array_base_non_particle.h"
#include "acme/primitive/primitive/particle.h"


template < class TYPE, class ARG_TYPE, class TYPED, class MEMORY, ::enum_type t_etypeContainer >
class array_base :
   virtual public ::particle,
   public array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >
{
public:


   using BASE_ARRAY = array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >;


   //array_base() : array_base_non_particle< TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >() {}
   //template < typename ...Args >
   //array_base(Args&&... args) : 
   //   array_base_non_particle< TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >(::std::forward < Args >(args)...)
   //{
   //}

   array_base() {}
   array_base(std::initializer_list < TYPE > initializer_list) :BASE_ARRAY(initializer_list) {}
   array_base(const BASE_ARRAY & a) :BASE_ARRAY(a) {}
   array_base(BASE_ARRAY && a) noexcept :BASE_ARRAY(a) {}
   array_base(const TYPE * p, ::count c) :BASE_ARRAY(p, c) {}
   array_base(::range < typename BASE_ARRAY::const_iterator > constrange) :
      BASE_ARRAY(constrange.begin(), constrange.end()) {}
   template < primitive_integral INTEGRAL >
   array_base(typename BASE_ARRAY::const_iterator begin, INTEGRAL count) :
      BASE_ARRAY(begin, begin + count) {}
   array_base(typename BASE_ARRAY::const_iterator begin, typename BASE_ARRAY::const_iterator end)
   {
      auto p = this->begin();
      while (p != end) add(*p);
   }


   void destroy()
   {

      particle::destroy();

      BASE_ARRAY::destroy();

   }


};


//template < primitive_integral INTEGRAL, class TYPE, class ARG_TYPE, class TYPED = ::typed::nodef < TYPE >, class MEMORY = ::heap::typed_memory < TYPE, ::heap::e_memory_array >, ::enum_type t_etypeContainer = e_type_element >
//inline TYPE& operator%(INTEGRAL nIndex, const array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > & a)
//{
//
//   return (TYPE &) (a % nIndex);
//
//}
//
//
//
//
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::array_base_non_particle() :
//ARRAY_RANGE()
//{
//
//   m_countAddUp = 0;
//   m_countAllocation = 0;
//
//}
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::array_base_non_particle(array_base_non_particle && array) noexcept :
//   ARRAY_RANGE(array)
//{
//
//   this->m_countAddUp = array.m_countAddUp;
//   this->m_countAllocation = array.m_countAllocation;
//
//   array.m_begin = nullptr;
//   array.m_end = 0;
//   array.m_countAllocation = 0;
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::array_base_non_particle(std::initializer_list<TYPE > initializer_list) :
//   array_base_non_particle()
//{
//
//   for (auto & item : initializer_list)
//   {
//
//      add(item);
//
//   }
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::array_base_non_particle(const array_base_non_particle & array)
//{
//
//   m_countAddUp = 0;
//   this->m_begin = nullptr;
//   this->m_end = nullptr;
//   m_countAllocation = 0;
//
//   set_size(array.get_size());
//
//   for (::index i = 0; i < array.get_size(); i++)
//   {
//
//      element_at(i) = array[i];
//
//   }
//
//}
//
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::~array_base_non_particle ()
//{
//
//   defer_destroy();
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//::count array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::resize(::count nNewSize, ARG_TYPE t)
//{
//
//   return allocate(nNewSize, false, false, t);
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//::count array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::allocate_in_bytes(::count nNewSize, bool bShrink, bool bRaw)
//{
//
//   return allocate((nNewSize + sizeof(TYPE)) / sizeof(TYPE), bShrink, bRaw);
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//::index array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::erase_at(::index first, ::count in_count_out_last)
//{
//
//   if (!prepare_first_in_count_last_out(first, in_count_out_last))
//   {
//
//      //throw_exception(error_bad_argument);
//
//      return -1;
//
//   }
//   
//   auto nCount = in_count_out_last - first + 1;
//
//   ::count nMoveCount = this->size() - in_count_out_last;
//
//   TYPED::destruct_count(this->m_begin + first, nCount);
//
//   if(nMoveCount)
//   {
//
//      ::acme::memmove_s(this->m_begin + first, (size_t) nMoveCount * sizeof(TYPE), this->m_begin + in_count_out_last + 1, (size_t) nMoveCount * sizeof(TYPE));
//
//   }
//
//   this->m_end -= nCount;
//
//   return first;
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//::index array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::erase_item(TYPE * p)
//{
//
//   return erase_at(p - this->m_begin);
//
//}
//
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//void array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::free_extra()
//{
//
//   auto size = this->size();
//
//   if(size != m_countAllocation)
//   {
//      
//      // shrink to desired size
//
//#ifdef SIZE_T_MAX
//      
//      ASSERT(size <= SIZE_T_MAX / sizeof(TYPE)); // no overflow
//
//#endif
//      
//      TYPE* pNewData = nullptr;
//
//      if(size != 0)
//      {
//
//         TYPE * pNewData;
//
//#if defined(__MCRTDBG) || MEMDLEAK
//
//         #ifdef __MCRTDBG
//
//         if (::get_task() != nullptr)
//         {
//
//            if (::get_task()->m_strFile.has_char())
//            {
//
//               pNewData = MEMORY::allocate(size, ::get_task()->m_strFile, ::get_task()->m_iLine);
//
//            }
//            else
//            {
//
//               pNewData = MEMORY::allocate(size, __FILE__, __LINE__);
//
//            }
//
//         }
//         else
//         {
//
//            pNewData = MEMORY::allocate(size, __FILE__, __LINE__);
//
//         }
//
//#else
//
//         if (::get_task_object_debug().has_char())
//         {
//
//            pNewData = MEMORY::allocate(size, ::get_task_object_debug(), 0);
//
//         }
//         else
//         {
//
//            pNewData = MEMORY::allocate(size, __FILE__, __LINE__);
//
//         }
//
//#endif
//
//#else
//
//         pNewData = MEMORY::allocate(size);
//
//#endif
//
//         // copy new data from old
//         ::acme::memcpy_s(pNewData, (size_t)size * sizeof(TYPE),this->m_begin, (size_t)size * sizeof(TYPE));
//
//      }
//
//      // get rid of old stuff (note: no destructors called)
//      MEMORY::free(this->m_begin);
//
//      this->m_begin = pNewData;
//
//      m_countAllocation = size;
//
//      this->m_end = this->m_begin + size;
//
//   }
//
//}
//
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//void array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::destroy()
//{
//
//   if(this->m_begin != nullptr)
//   {
//
//      auto size = this->size();
//
//      TYPED::destruct_count(this->m_begin, size);
//
//      MEMORY::free(this->m_begin);
//
//      this->m_begin     = nullptr;
//      this->m_end       = nullptr;
//      m_countAllocation        = 0;
//
//   }
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//TYPE * array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::raw_allocate_at(::index i, ::count c)
//{
//   
//   auto newSize = this->size() + c;
//   
//   auto nMove = this->size() - i;
//   
//   this->allocate(newSize, false, true);
//   
//   ::acme::memmove_s(this->m_begin + i + c, (size_t) (nMove * sizeof(TYPE)), this->m_begin + i, (size_t) (nMove * sizeof(TYPE)));
//
//   return this->m_begin + i;
//   
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//TYPE & array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::insert_at(::index i, const TYPE & element, ::count c)
//{
//
//   auto p = this->raw_allocate_at(i, c);
//
//   TYPED::copy_construct_count(p, c, element);
// 
//   return *p;
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//TYPE * array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::insert_at(::index i, const TYPE * pelements, ::count c)
//{
//
//   auto p = this->raw_allocate_at(i, c);
//
//   TYPED::copy_construct_count(p, c, pelements);
// 
//   return p;
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//TYPE * array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::insert_array_at(::index i, const array_base_non_particle * p)
//{
//
//   return this->insert_at(i, p->m_begin, p->size());
//
//}
//
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
////::index array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::allocate_at(::index nIndex, ::count nCount)
////{
////
////   if(nCount <= 0)
////   {
////      
////      return -1;
////      
////   }
////
////   if(nIndex < 0)
////   {
////      
////      throw_exception(error_bad_argument);
////      
////   }
////
////   if(nIndex >= this->size())
////   {
////
////      // adding after the end of the array
////      set_size(nIndex + nCount, -1);   // grow so nIndex is valid
////
////   }
////   else
////   {
////
////      // inserting in the middle of the array
////      ::count nOldSize = (::count) this->size();
////
////      // grow it to new size
////      set_size((::count) this->size() + nCount, -1);
////      
////      // shift old data up to fill gap
////      ::acme::memmove_s(this->m_begin + nIndex + nCount, (size_t) ((nOldSize - nIndex) * sizeof(TYPE)), this->m_begin + nIndex, (size_t) ((nOldSize - nIndex) * sizeof(TYPE)));
////
////      ::zero(this->m_begin + nIndex, nCount * sizeof(TYPE));
////
////      TYPED::construct_count(this->m_begin + nIndex, nCount);
////
////   }
////
////   // insert new value in the gap
////   ASSERT(nIndex + nCount <= this->size());
////
////   return nIndex;
////
////}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//::count array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::append(const array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > & src)
//{
//
//   ::count nOldSize = this->size();
//
//   ::count nSrcSize = src.size();   // to enable to append to itself
//
//   allocate(nOldSize + nSrcSize, false, true);
//
//   TYPED::copy_construct_count((this->m_begin + nOldSize), nSrcSize, src.m_begin);
//
//   return nOldSize;
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//void array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::copy(const array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > & src)
//{
//
//   if(this == &src)
//   {
//
//      return;
//
//   }
//   
//   erase_all();
//   
//   append(src);
//
////   ::count nSrcSize = src.size();
////
////   allocate(nSrcSize);
////
////   TYPED::copy_count(this->m_begin,src.m_begin, nSrcSize);
//
//}
//
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
////template < primitive_container CONTAINER >
////array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >
////array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::operator + (const CONTAINER & array) const
////{
////
////   auto a = *this;
////
////   a.append(array);
////
////   return ::transfer(a);
////
////}
//
////#include "sort.h"
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//template < primitive_array ARRAY >
//void array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::erase_indexes(const ARRAY & ia)
//{
//
//
//   // erase indexes
//   for(::index i = ia.get_upper_bound(); i >= 0; i--)
//   {
//
//      erase_at(ia[i]);
//
//   }
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//template < primitive_array ARRAY >
//void array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::erase_descending_indexes(const ARRAY & ia)
//{
//
//   for(::index i = 0; i < ia.get_count(); i++)
//   {
//
//      erase_at(ia[i]);
//
//   }
//
//}
//
//
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
////TYPE * array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::insert_at(::index nIndex,array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > * pNewArray)
////{
////
////   ASSERT(pNewArray != nullptr);
////   ASSERT(nIndex >= 0);    // will expand to meet need
////
////   ::count nCount = pNewArray->get_size();
////
////   if (nCount <= 0)
////      return this->end();
////
////   if (nIndex < 0)
////      throw_exception(error_bad_argument);
////
////   if (nIndex >= this->size())
////   {
////
////      // adding after the end of the array
////      set_size(nIndex + nCount, -1);   // grow so nIndex is valid
////
////   }
////   else
////   {
////
////      // inserting in the middle of the array
////      ::count nOldSize = (::count) this->size();
////
////      set_size((::count) (this->size() + nCount), -1);  // grow it to new size_i32
////      // destroy intial data before copying over it
////      // shift old data up to fill gap
////      ::acme::memmove_s(this->m_begin + nIndex + nCount, (size_t) ((nOldSize - nIndex) * sizeof(TYPE)), this->m_begin + nIndex, (size_t) ((nOldSize - nIndex) * sizeof(TYPE)));
////
////      ::zero(this->m_begin + nIndex, nCount* sizeof(TYPE));
////
////      TYPED::construct_count(this->m_begin + nIndex, nCount);
////
////   }
////
////   // insert new value in the gap
////   ASSERT(nIndex + nCount <= this->size());
////
////   ::index nIndexParam = nIndex;
////
////   ::index i = 0;
////
////   while (nCount--)
////   {
////
////      TYPED::copy(this->m_begin + nIndex, pNewArray->m_begin + i);
////
////      nIndex++;
////
////   }
////
////   return this->m_begin + nIndexParam;
////
////
////}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//TYPE array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::pick_at(::index nIndex)
//{
//
//   ::count nCount = 1;
//
//   ::index nUpperBound = nIndex + nCount;
//
//   if (nIndex < 0 || nCount < 0 || (nUpperBound > this->size()) || (nUpperBound < nIndex) || (nUpperBound < nCount))
//   {
//
//      throw_exception(error_bad_argument);
//
//   }
//
//   ::count nMoveCount = this->size() - (nUpperBound);
//
//   auto t = ::transfer(this->m_begin[nIndex]);
//
//   //TYPED::destruct_count(this->m_begin + nIndex, nCount REFERENCING_DEBUGGING_COMMA_THIS);
//
//   if (nMoveCount)
//   {
//
//      ::acme::memmove_s(this->m_begin + nIndex, (size_t)nMoveCount * sizeof(TYPE), this->m_begin + nUpperBound, (size_t)nMoveCount * sizeof(TYPE));
//
//   }
//
//   this->m_end -= nCount;
//
//   return ::transfer(t);
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::pick_at(::index nIndex, ::count nCount)
//{
//
//   //ASSERT_VALID(this);
//
//   ::index nUpperBound = nIndex + nCount;
//
//   if (nIndex < 0 || nCount < 0 || (nUpperBound > this->size()) || (nUpperBound < nIndex) || (nUpperBound < nCount))
//   {
//
//      throw_exception(error_bad_argument);
//
//   }
//
//   ::count nMoveCount = this->size() - (nUpperBound);
//
//   array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > a(this->m_begin + nIndex, (size_t)nMoveCount);
//
//   TYPED::destruct_count(this->m_begin + nIndex, nCount);
//
//   if (nMoveCount)
//   {
//
//      ::acme::memmove_s(this->m_begin + nIndex, (size_t)nMoveCount * sizeof(TYPE), this->m_begin + nUpperBound, (size_t)nMoveCount * sizeof(TYPE));
//
//   }
//
//   this->m_end -= nCount;
//
//   return a;
//
//}
//
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
////::count array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::set_raw_size(::count nNewSize,::count nGrowBy)
////{
////
////   ::count countOld = get_count();
////
////   ASSERT(nNewSize >= 0);
////
////   if(nNewSize < 0)
////      throw_exception(error_bad_argument);
////
////   if(nGrowBy >= 0)
////      m_countAddUp = nGrowBy;  // set new size_i32
////
////   if(nNewSize == 0)
////   {
////
////      // shrink to nothing
////      if(this->m_begin != nullptr)
////      {
////
////         MEMORY::free(this->m_begin);
////
////         this->m_begin = nullptr;
////
////      }
////
////      this->m_end = nullptr;
////      m_countAllocation = 0;
////   }
////   else if (this->m_begin == nullptr)
////   {
////      // create buffer big enough to hold number of requested elements or
////      // m_countAddUp elements, whichever is larger.
////#ifdef SIZE_T_MAX
////      if (nNewSize > SIZE_T_MAX / sizeof(TYPE))
////         throw_exception(error_no_memory);
////      ASSERT(nNewSize <= SIZE_T_MAX / sizeof(TYPE));    // no overflow
////#endif
////      ::count nAllocSize = (::count) maximum(nNewSize, m_countAddUp);
////#if defined(__MCRTDBG) || MEMDLEAK
////      if (::get_task() != nullptr)
////      {
////#if defined(MEMDLEAK)
////
////         if (::get_task()->m_strFile.has_char())
////         {
////
////            this->m_begin = MEMORY::allocate(nAllocSize, ::get_task()->m_strFile, 0);
////
////         }
////         else
////         {
////
////            this->m_begin = MEMORY::allocate(nAllocSize, __FILE__, __LINE__);
////
////         }
////
////#else
////
////         if (::get_task_object_debug().has_char())
////         {
////
////            this->m_begin = MEMORY::allocate(nAllocSize, ::get_task_object_debug(), ::get_task()->m_iLine);
////
////         }
////         else
////         {
////
////            this->m_begin = MEMORY::allocate(nAllocSize, __FILE__, __LINE__);
////
////         }
////
////#endif
////
////      }
////      else
////      {
////
////         this->m_begin = MEMORY::allocate(nAllocSize, __FILE__, __LINE__);
////
////      }
////
////#else
////
////      this->m_begin = MEMORY::allocate(nAllocSize);
////
////#endif
////
////      this->m_end = this->m_begin+ nNewSize;
////      m_countAllocation = nAllocSize;
////   }
////   else if(nNewSize <= m_countAllocation)
////   {
////      this->m_end = this->m_begin+nNewSize;
////   }
////   else
////   {
////      // otherwise, grow aaa_base_array
////      nGrowBy = (::count) m_countAddUp;
////      if(nGrowBy == 0)
////      {
////         // heuristically determine growth when nGrowBy == 0
////         //  (this avoids heap fragmentation in many situations)
////         nGrowBy = (::count) this->size();
////         nGrowBy = (nGrowBy < 4) ? 4 : ((nGrowBy > 1024) ? 1024 : nGrowBy);
////      }
////      ::count nNewMax;
////      if(nNewSize < m_countAllocation + nGrowBy)
////         nNewMax = (::count) (m_countAllocation + nGrowBy);  // granularity
////      else
////         nNewMax = nNewSize;  // no slush
////
////      ASSERT(nNewMax >= m_countAllocation);  // no wrap around
////
////      if(nNewMax  < m_countAllocation)
////         throw_exception(error_bad_argument);
////
////#ifdef SIZE_T_MAX
////      ASSERT(nNewMax <= SIZE_T_MAX / sizeof(TYPE)); // no overflow
////#endif
////      TYPE * pNewData;
////#if defined(__MCRTDBG) || MEMDLEAK
////      #ifdef __MCRTDBG
////
////      if (::get_task() != nullptr)
////      {
////
////         if (::get_task()->m_strFile.has_char())
////         {
////
////            pNewData = MEMORY::allocate(nNewMax, ::get_task()->m_strFile, ::get_task()->m_iLine);
////
////         }
////         else
////         {
////
////            pNewData = MEMORY::allocate(nNewMax, __FILE__, __LINE__);
////
////         }
////
////      }
////      else
////      {
////
////         pNewData = MEMORY::allocate(nNewMax, __FILE__, __LINE__);
////
////      }
////
////#else
////
////      if (::get_task_object_debug().has_char())
////      {
////
////         pNewData = MEMORY::allocate(nNewMax, ::get_task_object_debug(), ::get_task()->m_iLine);
////
////      }
////      else
////      {
////
////         pNewData = MEMORY::allocate(nNewMax, __FILE__, __LINE__);
////
////      }
////
////#endif
////
////#else
////
////      pNewData = MEMORY::allocate(nNewMax);
////
////#endif      // copy new data from old
////
////      ::acme::memcpy_s(pNewData,(size_t)nNewMax * sizeof(TYPE),this->m_begin,(size_t)this->size() * sizeof(TYPE));
////
////      ///for(i32 i = 0; i < nNewSize - this->size(); i++)
////      // get rid of old stuff (note: no destructors called)
////      MEMORY::free(this->m_begin);
////
////      this->m_begin = pNewData;
////
////      this->m_end = this->m_begin + nNewSize;
////
////      m_countAllocation = nNewMax;
////
////   }
////
////   return countOld;
////
////}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//void array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::reserve(::count newAllocationSize)
//{
//
//   if(newAllocationSize <= m_countAllocation)
//   {
//
//      return;
//
//   }
//
//   if(m_countAllocation <= 0)
//   {
//
//      ASSERT(this->m_begin == nullptr && this->m_end == nullptr);
//
//      if(newAllocationSize > UPTR_MAXIMUM / sizeof(TYPE))
//      {
//         
//         throw_exception(error_no_memory);
//         
//      }
//
//      newAllocationSize = maximum(newAllocationSize, m_countAddUp);
//
//#if MEMDLEAK || defined(__MCRTDBG)
//
//      if(::get_task() != nullptr)
//      {
//
//#if defined(__MCRTDBG)
//
//         if(::get_task()->m_strFile.has_char())
//         {
//
//            this->m_begin = MEMORY::allocate(newAllocationSize, ::get_task()->m_strFile, ::get_task()->m_iLine);
//
//         }
//         else
//         {
//
//            this->m_begin = MEMORY::allocate(newAllocationSize, __FILE__, __LINE__);
//
//         }
//
//#else
//
//         if (::get_task_object_debug().has_char())
//         {
//
//            this->m_begin = MEMORY::allocate(newAllocationSize, "thread://" + ::get_task_object_name() + ", " + ::get_task_object_debug() + ", " + string(__FILE__), __LINE__);
//
//         }
//         else
//         {
//
//            this->m_begin = MEMORY::allocate(newAllocationSize, "thread://" + ::get_task_object_name() + ", " + string(__FILE__), __LINE__);
//
//         }
//
//#endif
//
//      }
//      else
//      {
//
//         this->m_begin = MEMORY::allocate(newAllocationSize, __FILE__, __LINE__);
//
//      }
//
//#else
//
//      this->m_begin = MEMORY::allocate(newAllocationSize);
//
//#endif
//      
//      this->m_end = this->m_begin;
//
//   }
//   else
//   {
//      
//      auto countOld = this->size();
//
//      auto countAddUp = m_countAddUp;
//
//      if(countAddUp <= 0)
//      {
//
//         countAddUp = this->size();
//         
//         constrain(countAddUp, 4, 1024);
//
//      }
//
//      if(newAllocationSize < m_countAllocation + countAddUp)
//      {
//
//         newAllocationSize = m_countAllocation + countAddUp;
//
//      }
//
//      if(newAllocationSize > UPTR_MAXIMUM / sizeof(TYPE))
//      {
//         
//         throw_exception(error_no_memory);
//         
//      }
//
//#if MEMDLEAK || defined(__MCRTDBG)
//
//      TYPE* pNewData =  nullptr;
//
//      if(::get_task() != nullptr)
//      {
//
//#if defined(__MCRTDBG)
//
//         if(::get_task()->m_strFile.has_char())
//         {
//
//            pNewData = MEMORY::allocate(newAllocationSize, ::get_task()->m_strFile,::get_task()->m_iLine);
//
//         }
//         else
//         {
//
//            pNewData = MEMORY::allocate(newAllocationSize, __FILE__, __LINE__);
//
//         }
//
//#else
//
//         if (::get_task_object_debug().has_char())
//         {
//
//            pNewData = MEMORY::allocate(newAllocationSize, "thread://" + ::get_task_object_name() + ", " + ::get_task_object_debug() + ", " + string(__FILE__), __LINE__);
//
//         }
//         else
//         {
//
//            pNewData = MEMORY::allocate(newAllocationSize, "thread://" + ::get_task_object_name() + ", " + string(__FILE__), __LINE__);
//
//         }
//
//#endif
//
//      }
//      else
//      {
//
//         pNewData = MEMORY::allocate(newAllocationSize, __FILE__, __LINE__);
//
//      }
//
//#else
//
//      TYPE * pNewData = MEMORY::allocate(newAllocationSize);
//
//#endif
//
//      // copy new data from old
//      ::acme::memcpy_s(pNewData, (size_t)newAllocationSize * sizeof(TYPE), this->m_begin, (size_t) this->size() * sizeof(TYPE));
//
//      // get rid of old stuff (note: no destructors called)
//      MEMORY::free(this->m_begin);
//
//      this->m_begin = pNewData;
//
//      this->m_end = this->m_begin + countOld;
//
//   }
//
//   m_countAllocation = newAllocationSize;
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//::count array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::_allocate(::count nNewSize, bool bShrink, bool bRaw, const TYPE * ptype)
//{
//
//   ASSERT(nNewSize >= 0);
//
//   if(nNewSize < 0)
//   {
//
//      throw_exception(error_bad_argument);
//
//   }
//
//   ::count countOld = get_count();
//
//   if(nNewSize == countOld)
//   {
//
//      return countOld;
//
//   }
//
//   if(nNewSize == 0)
//   {
//
//      if(this->m_begin != nullptr)
//      {
//
//         TYPED::destruct_count(this->m_begin, this->size());
//         
//         if(bShrink)
//         {
//            
//            MEMORY::free(this->m_begin);
//            
//            this->m_begin = nullptr;
//            
//            m_countAllocation = 0;
//
//         }
//
//      }
//
//      this->m_end = this->m_begin;
//      
//   }
//   else if(this->m_begin == nullptr)
//   {
//
//      if(nNewSize > UPTR_MAXIMUM / sizeof(TYPE))
//      {
//         
//         throw_exception(error_no_memory);
//         
//      }
//
//      auto nAllocSize = maximum(nNewSize, m_countAddUp);
//
//#if MEMDLEAK || defined(__MCRTDBG)
//
//      if(::get_task() != nullptr)
//      {
//
//#if defined(__MCRTDBG)
//
//         if(::get_task()->m_strFile.has_char())
//         {
//
//            this->m_begin = MEMORY::allocate(nAllocSize, ::get_task()->m_strFile, ::get_task()->m_iLine);
//
//         }
//         else
//         {
//
//            this->m_begin = MEMORY::allocate(nAllocSize, __FILE__, __LINE__);
//
//         }
//
//#else
//
//         if (::get_task_object_debug().has_char())
//         {
//
//            this->m_begin = MEMORY::allocate(nAllocSize, "thread://" + ::get_task_object_name() + ", " + ::get_task_object_debug() + ", " + string(__FILE__), __LINE__);
//
//         }
//         else
//         {
//
//            this->m_begin = MEMORY::allocate(nAllocSize, "thread://" + ::get_task_object_name() + ", " + string(__FILE__), __LINE__);
//
//         }
//
//#endif
//
//      }
//      else
//      {
//
//         this->m_begin = MEMORY::allocate(nAllocSize, __FILE__, __LINE__);
//
//      }
//
//#else
//
//      this->m_begin = MEMORY::allocate(nAllocSize);
//
//#endif
//      
//      if(!bRaw)
//      {
//         
//         if (::is_null(ptype))
//         {
//            
//            TYPED::construct_count(this->m_begin, nNewSize);
//            
//         }
//         else
//         {
//            
//            TYPED::copy_construct_count(this->m_begin, nNewSize, *ptype);
//            
//         }
//         
//      }
//
//      this->m_end = this->m_begin + nNewSize;
//
//      m_countAllocation = nAllocSize;
//
//   }
//   else if(nNewSize <= m_countAllocation)
//   {
//
//      if (!bRaw)
//      {
//
//         if (nNewSize > countOld)
//         {
//
//            if (::is_null(ptype))
//            {
//
//               TYPED::construct_count(this->m_begin + countOld, nNewSize - countOld);
//
//            }
//            else
//            {
//
//               TYPED::copy_construct_count(this->m_begin + countOld, nNewSize - countOld, *ptype);
//
//            }
//
//         }
//         else if (countOld > nNewSize)
//         {
//
//            TYPED::destruct_count(this->m_begin + nNewSize, countOld - nNewSize);
//
//         }
//
//      }
//
//      this->m_end = this->m_begin + nNewSize;
//
//   }
//   else
//   {
//
//      auto countAddUp = m_countAddUp;
//
//      if(countAddUp <= 0)
//      {
//
//         countAddUp = this->size();
//         
//         constrain(countAddUp, 4, 1024);
//
//      }
//
//      ::count countNewAllocation;
//
//      if(nNewSize < m_countAllocation + countAddUp)
//      {
//
//         countNewAllocation = m_countAllocation + countAddUp;
//
//      }
//      else
//      {
//
//         countNewAllocation = nNewSize;
//
//      }
//
//      if(countNewAllocation > UPTR_MAXIMUM / sizeof(TYPE))
//      {
//         
//         throw_exception(error_no_memory);
//         
//      }
//
//#if MEMDLEAK || defined(__MCRTDBG)
//
//      TYPE* pNewData =  nullptr;
//
//      if(::get_task() != nullptr)
//      {
//
//#if defined(__MCRTDBG)
//
//         if(::get_task()->m_strFile.has_char())
//         {
//
//            pNewData = MEMORY::allocate(countNewAllocation, ::get_task()->m_strFile,::get_task()->m_iLine);
//
//         }
//         else
//         {
//
//            pNewData = MEMORY::allocate(countNewAllocation, __FILE__, __LINE__);
//
//         }
//
//#else
//
//         if (::get_task_object_debug().has_char())
//         {
//
//            pNewData = MEMORY::allocate(countNewAllocation, "thread://" + ::get_task_object_name() + ", " + ::get_task_object_debug() + ", " + string(__FILE__), __LINE__);
//
//         }
//         else
//         {
//
//            pNewData = MEMORY::allocate(countNewAllocation, "thread://" + ::get_task_object_name() + ", " + string(__FILE__), __LINE__);
//
//         }
//
//#endif
//
//      }
//      else
//      {
//
//         pNewData = MEMORY::allocate(countNewAllocation, __FILE__, __LINE__);
//
//      }
//
//
//#else
//
//      TYPE * pNewData = MEMORY::allocate(countNewAllocation);
//
//#endif
//
//      // copy new data from old
//      ::acme::memcpy_s(pNewData, (size_t)countNewAllocation * sizeof(TYPE), this->m_begin, (size_t) countOld * sizeof(TYPE));
//
//      if(!bRaw)
//      {
//         
//         // construct remaining elements
//         ASSERT(nNewSize > countOld);
//         
//         if (nNewSize > countOld)
//         {
//            
//            if (::is_null(ptype))
//            {
//               
//               TYPED::construct_count(pNewData + countOld, nNewSize - countOld);
//               
//            }
//            else
//            {
//               
//               TYPED::copy_construct_count(pNewData + countOld, nNewSize - countOld, *ptype);
//               
//            }
//            
//         }
//         
//      }
//
//      // get rid of old stuff (note: no destructors called)
//      MEMORY::free(this->m_begin);
//
//      this->m_begin = pNewData;
//
//      this->m_end = this->m_begin + nNewSize;
//
//      m_countAllocation = countNewAllocation;
//
//   }
//
//   return countOld;
//
//}
//
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
////::count array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::allocate(::count nNewSize, bShrink, const TYPE * ptype)
////{
////
////   ::count countOld = get_count();
////   
////   auto countOldRawAllocate = raw_allocate_at(nNewSize, bShrink);
////
////   if(countOldRawAllocate == countOld)
////   {
////      
////      return countOld;
////      
////   }
////   
////   if(nNewSize == 0)
////   {
////
////      // shrink to nothing
////      if(this->m_begin != nullptr)
////      {
////
////         TYPED::destruct_count(this->m_begin, this->size()  REFERENCING_DEBUGGING_COMMA_THIS);
////
////         MEMORY::free(this->m_begin);
////
////         this->m_begin = nullptr;
////
////      }
////
////      this->m_end = nullptr;
////      
////      m_countAllocation = 0;
////
////   }
////   else if(this->m_begin == nullptr)
////   {
////
////      // create buffer big enough to hold number of requested elements or
////      // m_countAddUp elements, whichever is larger.
////#ifdef SIZE_T_MAX
////      if(::comparison::gt(nNewSize, SIZE_T_MAX / sizeof(TYPE)))
////         throw_exception(error_no_memory);
////      ASSERT(::comparison::lt(nNewSize, SIZE_T_MAX / sizeof(TYPE)));    // no overflow
////#endif
////
////      auto nAllocSize = maximum(nNewSize, m_countAddUp);
////
////#if MEMDLEAK  || defined(__MCRTDBG)
////
////      if(::get_task() != nullptr)
////      {
////
////#if defined(__MCRTDBG)
////
////         if(::get_task()->m_strFile.has_char())
////         {
////
////            this->m_begin = MEMORY::allocate(nAllocSize, ::get_task()->m_strFile, ::get_task()->m_iLine);
////
////         }
////         else
////         {
////
////            this->m_begin = MEMORY::allocate(nAllocSize, __FILE__, __LINE__);
////
////         }
////
////#else
////
////         if (::get_task_object_debug().has_char())
////         {
////
////            this->m_begin = MEMORY::allocate(nAllocSize, "thread://" + ::get_task_object_name() + ", " + ::get_task_object_debug() + ", " + string(__FILE__), __LINE__;
////
////         }
////         else
////         {
////
////            this->m_begin = MEMORY::allocate(nAllocSize, "thread://" + ::get_task_object_name() + ", " + string(__FILE__), __LINE__;
////
////         }
////
////#endif
////
////      }
////      else
////      {
////
////         this->m_begin = MEMORY::allocate(nAllocSize, __FILE__, __LINE__);
////
////      }
////
////#else
////
////      this->m_begin = MEMORY::allocate(nAllocSize);
////
////#endif
////
////      if (::is_null(ptype))
////      {
////
////         TYPED::construct_count(this->m_begin, nNewSize);
////
////      }
////      else
////      {
////
////         TYPED::copy_construct_count(this->m_begin, nNewSize, *ptype);
////
////      }
////
////      this->m_end = this->m_begin + nNewSize;
////
////      m_countAllocation = nAllocSize;
////
////   }
////   else if(nNewSize <= m_countAllocation)
////   {
////
////      if(nNewSize > this->size())
////      {
////
////         if (::is_null(ptype))
////         {
////
////            TYPED::construct_count(this->end(), nNewSize - this->size());
////
////         }
////         else
////         {
////
////            TYPED::copy_construct_count(this->end(), nNewSize - this->size(), *ptype);
////
////         }
////
////      }
////      else if(this->size() > nNewSize)
////      {
////
////         TYPED::destruct_count(this->m_begin + nNewSize,this->size() - nNewSize REFERENCING_DEBUGGING_COMMA_THIS);
////
////      }
////
////      this->m_end = this->m_begin + nNewSize;
////
////   }
////   else
////   {
////
////      // otherwise, grow aaa_base_array
////      nGrowBy = m_countAddUp;
////
////      if(nGrowBy == 0)
////      {
////
////         // heuristically determine growth when nGrowBy == 0
////         //  (this avoids heap fragmentation in many situations)
////         nGrowBy = this->size();
////         nGrowBy = (nGrowBy < 4) ? 4 : ((nGrowBy > 1024) ? 1024 : nGrowBy);
////
////      }
////
////      ::count nNewMax;
////
////      if(nNewSize < m_countAllocation+ nGrowBy)
////      {
////
////         nNewMax = m_countAllocation+ nGrowBy;  // granularity
////
////      }
////      else
////      {
////
////         nNewMax = nNewSize;  // no slush
////
////      }
////
////      ASSERT(nNewMax >= m_countAllocation);  // no wrap around
////
////      if(nNewMax  < m_countAllocation)
////      {
////
////         throw_exception(error_bad_argument);
////
////      }
////
////#ifdef SIZE_T_MAX
////
////      ASSERT(::comparison::lt(nNewMax, SIZE_T_MAX / sizeof(TYPE))); // no overflow
////
////#endif
////
////#if MEMDLEAK || defined(__MCRTDBG)
////
////      TYPE* pNewData =  nullptr;
////
////      if(::get_task() != nullptr)
////      {
////
////#if defined(__MCRTDBG)
////
////         if(::get_task()->m_strFile.has_char())
////         {
////
////            pNewData = MEMORY::allocate(nNewMax, ::get_task()->m_strFile,::get_task()->m_iLine);
////
////         }
////         else
////         {
////
////            pNewData = MEMORY::allocate(nNewMax, __FILE__, __LINE__);
////
////         }
////
////#else
////
////         if (::get_task_object_debug().has_char())
////         {
////
////            pNewData = MEMORY::allocate(nNewMax, "thread://" + ::get_task_object_name() + ", " + ::get_task_object_debug() + ", " + string(__FILE__), __LINE__;
////
////         }
////         else
////         {
////
////            pNewData = MEMORY::allocate(nNewMax, "thread://" + ::get_task_object_name() + ", " + string(__FILE__), __LINE__;
////
////         }
////
////#endif
////
////      }
////      else
////      {
////
////         pNewData = MEMORY::allocate(nNewMax, __FILE__, __LINE__);
////
////      }
////
////
////#else
////
////      TYPE* pNewData = MEMORY::allocate(nNewMax);
////
////#endif
////
////      // copy new data from old
////      ::acme::memcpy_s(pNewData,(size_t)nNewMax * sizeof(TYPE),this->m_begin,(size_t)this->size() * sizeof(TYPE));
////
////      // construct remaining elements
////      ASSERT(nNewSize > this->size());
////
////      if (nNewSize > this->size())
////      {
////
////         if (::is_null(ptype))
////         {
////
////            TYPED::construct_count(pNewData + this->size(), nNewSize - this->size());
////
////         }
////         else
////         {
////
////            TYPED::copy_construct_count(pNewData + this->size(), nNewSize - this->size(), *ptype);
////
////         }
////
////      }
////
////      // get rid of old stuff (note: no destructors called)
////      MEMORY::free(this->m_begin);
////
////      this->m_begin = pNewData;
////
////      this->m_end = this->m_begin + nNewSize;
////
////      m_countAllocation = nNewMax;
////
////   }
////
////   return countOld;
////
////}
//
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//void array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::on_after_read()
//{
//
//
//}
//
//
//
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline void array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::set_at_grow(::index nIndex, ARG_TYPE newElement)
//{
//
//   ASSERT(nIndex >= 0);
//
//   if (nIndex >= this->size())
//   {
//
//      this->set_size(nIndex + 1);
//
//   }
//
//   this->m_begin[nIndex] = newElement;
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline TYPE & array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::element_at_grow(::index nIndex)
//{
//
//   ASSERT(nIndex >= 0);
//
//   if (nIndex >= this->size())
//   {
//
//      this->set_size(nIndex + 1);
//
//   }
//
//   return this->m_begin[nIndex];
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline void array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::set_each(ARG_TYPE element, ::index first, ::count in_count_out_last)
//{
//
//   prepare_first_in_count_last_out(first, in_count_out_last);
//
//   for(::index i = first; i <= in_count_out_last; i++)
//   {
//
//      this->m_begin[i] = element;
//
//   }
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//template < typename ITERATOR2 >
//inline void array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::erase(const ITERATOR2 & begin, const ITERATOR2 & last)
//{
//
//   auto start = this->index_of(begin);
//
//   auto end = this->index_of(last);
//
//   if(start < 0 || (end <= start && end >= 0))
//   {
//
//      return;
//
//   }
//
//   auto count = end > start ? end - start : -1;
//
//   erase_at(start, count);
//
//}
//
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//bool array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::prepare_first_last(::index & first, ::index & last) const
//{
//
//   if (first < 0)
//   {
//
//      first += this->get_count();
//
//   }
//
//   if (last < 0)
//   {
//
//      last += this->get_count();
//
//   }
//
//   return last >= first;
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//bool array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::prepare_first_in_count_last_out(::index & first, ::count & in_count_out_last) const
//{
//
//   if (first < 0)
//   {
//
//      first += this->get_count();
//
//   }
//   
//   if(first < 0)
//   {
//      
//      first = 0;
//      
//   }
//
//   if (in_count_out_last < 0)
//   {
//
//      in_count_out_last += this->get_count();
//
//   }
//   else
//   {
//
//      in_count_out_last = first + in_count_out_last - 1;
//
//   }
//
//   return in_count_out_last >= first;
//
//}
//
//
////
//// see collection_array_decl.h for declaration
////
//// raw_array is an array that does not call constructors or destructor in elements
//// array is an array that call only copy constructor and destructor in elements
//// array is an array that call default constructors, copy constructs and destructors in elements
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline ::count array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::get_size() const
//{
//   return (::count) this->size();
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline ::count array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::get_count() const
//{
//   return (::count) this->size();
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline ::count array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::get_length() const
//{
//   return (::count) this->size();
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline ::count array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::get_size_in_bytes() const
//{
//   return (::count)this->size() * sizeof(TYPE);
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline ::count array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::get_byte_count() const
//{
//   return (::count) (this->size() * sizeof(TYPE));
//}
//
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
////inline ::count array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::size() const
////{
////   return this->get_size();
////}
////
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline ::count array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::count() const
//{
//   return this->get_count();
//}
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline ::count array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::length() const
//{
//   return this->get_length();
//}
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
////inline bool array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::is_empty(::count countMinimum) const
////{
////   return this->size() < countMinimum;
////}
//
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
////inline bool array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::empty(::count countMinimum) const
////{
////   return is_empty(countMinimum);
////}
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
////inline bool array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::isEmpty(::count countMinimum) const
////{
////   return empty(countMinimum);
////}
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
////inline bool array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::has_elements(::count countMinimum) const
////{
////   return this->size() >= countMinimum;
////}
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline ::index array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::get_lower_bound(::index i) const
//{
//   return i < this->size() ? i : -1;
//}
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline ::index array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::get_middle_index(::index iIndex) const
//{
//   return this->size() / 2 + iIndex;
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline ::index array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::get_upper_bound(::index iIndex) const
//{
//   return this->size() + iIndex;
//}
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline bool array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::bounds(::index i) const
//{
//   return i >= 0 && i < this->size();
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline ::count array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::erase_all()
//{
//   
//   return allocate(0, false, false);
//   
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline ::count array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::set_size(::index nNewSize)
//{
//   
//   return allocate(nNewSize, false, false);
//   
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline void array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::clear()
//{
//   
//   erase_all();
//   
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline void array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::erase_last()
//{
//   ASSERT(this->size() > 0);
//   erase_at(get_upper_bound());
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline void array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::zero(::index iStart,::count c)
//{
//   if(c < 0)
//   {
//      c = get_size() - iStart;
//   }
//   ::zero(&this->m_begin[iStart],c * sizeof(TYPE));
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline const TYPE& array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::element_at(::index nIndex) const
//{
//
//   ASSERT(nIndex >= 0 && nIndex < this->size());
//
//   return this->m_begin[nIndex];
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline TYPE& array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::element_at(::index nIndex)
//{
//
//   ASSERT(nIndex >= 0 && nIndex < this->size());
//
//   return this->m_begin[nIndex];
//
//}
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
////inline const TYPE& array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::first(::index nIndex) const
////{
////   return this->element_at(nIndex);
////}
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
////inline TYPE& array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::first(::index nIndex)
////{
////   return this->element_at(nIndex);
////}
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
////inline const TYPE& array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::last(::index i) const
////{
////   return this->element_at(this->get_upper_bound(i);
////}
////
////
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
////inline TYPE& array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::last(::index i)
////{
////   return this->element_at(this->get_upper_bound(i);
////}
//
//
//
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
////inline const TYPE* array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::get_data() const
////{
////   return (const TYPE*)this->m_begin;
////}
////
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
////inline TYPE* array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::get_data()
////{
////   return (TYPE*)this->m_begin;
////}
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
////inline const TYPE& array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::operator[](::index i) const
////{
////
////   return this->m_begin[i];
////
////}
//
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
////inline TYPE& array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::operator[](::index i)
////{
////
////   return this->m_begin[i];
////
////}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline void array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::__swap(::index index1, ::index index2)
//{
//
//   ::__swap(this->m_begin[index1], this->m_begin[index2]);
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline void array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::__swap(iterator it1, iterator it2)
//{
//
//   TYPE t = *it1;
//
//   *it1 = *it2;
//
//   *it2 = t;
//
//}
//
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline void array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::__swap(const_iterator it1, const_iterator it2)
//{
//
//   auto t = (TYPE) *it1;
//
//   ((TYPE &)*it1) = (const TYPE &) *it2;
//
//   ((TYPE &)*it2) = t;
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline const TYPE& array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::first(::index nIndex) const
//{
//
//   return this->element_at(nIndex);
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline TYPE & array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::first(::index nIndex)
//{
//
//   return this->element_at(nIndex);
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline const TYPE & array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::last(::index i) const
//{
//
//   return element_at(this->get_upper_bound(i));
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline TYPE & array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::last(::index i)
//{
//
//   return element_at(this->get_upper_bound(i));
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline const TYPE & array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::middle(::index i) const
//{
//
//   return element_at(this->get_middle_index(i));
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline TYPE & array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::middle(::index i)
//{
//
//   return element_at(this->get_middle_index(i));
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//void  array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::set_all(const TYPE & t)
//{
//
//   for (::index i = 0; i < get_count(); i++)
//   {
//
//      this->m_begin[i] = t;
//
//   }
//
//}
//
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
////template < typename VAR >
////inline array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > & array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::operator = (const payload_type < VAR > & a)
////{
////
////   ::count c = a.this_var()->array_get_count();
////
////   for(::index i = 0; i < c; i++)
////   {
////
////      add((ARG_TYPE)(payload_cast)a.this_var()->at(i));
////
////   }
////
////   return *this;
////
////}
//
//
//
//
//
//
//
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline TYPE array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::pop(::index n)
//{
//
//   ::index i = this->get_upper_bound(n);
//
//   TYPE t = element_at(i);
//
//   this->erase_at(i);
//
//   return t;
//
//}
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline TYPE array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::pop_first(::index i)
//{
//
//   auto t = ::transfer(this->first(i));
//
//   this->erase_at(i);
//
//   return t;
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline void array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::pop_back(::index n)
//{
//
//   erase_at(this->get_upper_bound(n));
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline ::index array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::push(ARG_TYPE newElement)
//{
//
//   return index_of(&insert_at(this->size(), newElement));
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline TYPE& array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::add_item(ARG_TYPE newElement)
//{
//
//   auto nIndex = this->size();
//
//   this->allocate(nIndex + 1, false, false, newElement);
//
//   return this->element_at(nIndex);
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//TYPE& array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::add_new()
//{
//
//   auto nIndex = this->size();
//
//   this->allocate(nIndex + 1, false, false);
//
//   return this->last();
//
//}
//
//
////template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
////inline TYPE & array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::add_item(ARG_TYPE newElement)
////{
////
////   return insert_at(this->size(), newElement);
////
////}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline TYPE array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::takeAt(::index i)
//{
//
//   TYPE t = element_at(i);
//
//   this->erase_at(i);
//
//   return t;
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline TYPE array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::takeFirst(::index i)
//{
//
//   TYPE t = element_at(i);
//
//   this->erase_at(i);
//
//   return t;
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline TYPE array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::takeLast(::index n)
//{
//
//   ::index i = this->get_upper_bound(n);
//
//   TYPE t = element_at(i);
//
//   this->erase_at(i);
//
//   return t;
//
//}
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >::array_base_non_particle(const TYPE * p, ::count c)
//{
//
//   m_countAddUp = 0;
//   this->m_begin = nullptr;
//   this->m_end = nullptr;
//   m_countAllocation = 0;
//
//   set_size(c);
//
//   for (::index i = 0; i < c; i++)
//   {
//
//      element_at(i) = p[i];
//
//   }
//
//}
//
//
//
//
//
//template < typename TYPE, typename ARG_TYPE, typename TYPED, typename MEMORY,  ::enum_type t_etypeContainer >
//inline ::count array_base_non_particle < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > ::erase(const TYPE * begin, const TYPE * last)
//{
//
//   auto iStart = index_of(begin);
//
//   auto iEnd = index_of(last);
//
//   // iEnd exclusive
//   return erase_at(iStart, iEnd - iStart);
//
//}
//
////template < typename TYPE1, typename TYPE2 >
////concept is_same_family = ::std::is_base_of<TYPE1, TYPE2> || ::std::is_base_of<TYPE2, TYPE1>;
//
//
//
//
