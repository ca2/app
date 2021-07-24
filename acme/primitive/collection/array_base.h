#pragma once


template < typename ARRAY >
concept indexed_array = requires(ARRAY array, ::index i)
{
   array.get_size();
   array.element_at(i);
};


#define __default_array_array_base(TYPE) ::array_base < TYPE, const TYPE &, ::allocator::def < TYPE > >


#define DECLARE_TYPED_ARRAY_ACCESSOR_OF(ITEM, CONTAINER, TYPE, CONTAINER_TYPE) \
__pointer(TYPE) & ITEM ## _at(::index i) { return CONTAINER[i]; } \
const TYPE * ITEM ## _at(::index i) const { return CONTAINER[i]; } \
TYPE ** ITEM ## _data() { return (TYPE **) CONTAINER.get_data(); } \
TYPE * const * ITEM ## _data() const { return (TYPE * const *) CONTAINER.get_data(); } \
TYPE * get_ ## ITEM(::index i) const { return CONTAINER.bounds(i) ? CONTAINER[i] : nullptr; } \
::count ITEM ## _count() const { return CONTAINER.get_count(); } \
bool has_ ## ITEM() const { return CONTAINER.has_element(); } \
CONTAINER_TYPE ITEM ## a() const { return CONTAINER; } \
CONTAINER_TYPE & ITEM ## a() { return CONTAINER; } \
bool contains_ ## ITEM(const TYPE * p) const { return CONTAINER.contains(p); } \
bool is_there_no_ ## ITEM() const { return CONTAINER.is_empty(); } \
bool has_no_ ## ITEM() const { return is_there_no_ ## ITEM(); } \
::index find_first_ ## ITEM(const TYPE * p, ::index iStart = 0, ::count nCount = -1) const { return CONTAINER.find_first(p, iStart, nCount); } \
__pointer(TYPE) & first_ ## ITEM() { return CONTAINER.first_pointer(); } \
__pointer(TYPE) & last_ ## ITEM() { return CONTAINER.last_pointer(); } \
TYPE * get_first_ ## ITEM() const { return CONTAINER.get_first_pointer(); } \
TYPE * get_last_ ## ITEM() const { return CONTAINER.get_last_pointer(); } \
::index ITEM ## _first_index(::index i = 0) const { return CONTAINER.first_index(i); } \
::index ITEM ## _last_index(::index i = -1) const { return CONTAINER.last_index(i); } \
CONTAINER_TYPE CONTAINER

#define DECLARE_ARRAY_ACCESSOR_OF(ITEM, CONTAINER, TYPE) \
DECLARE_TYPED_ARRAY_ACCESSOR_OF(ITEM, CONTAINER, TYPE, __pointer_array(TYPE))

#define DECLARE_TYPED_ARRAY_OF(ITEM, CONTAINER, TYPE, CONTAINER_TYPE) \
::index add_ ## ITEM(TYPE * p) { return CONTAINER.add_item(p); } \
::index add_unique_ ## ITEM(TYPE * p) { return CONTAINER.add_unique(p); } \
::index erase_ ## ITEM(TYPE * p) { return CONTAINER.erase(p); } \
CONTAINER_TYPE ITEM ## a_section(::index iStart = 0, ::count nCount = -1){return CONTAINER.slice < CONTAINER_TYPE >(iStart, nCount);} \
template < typename ARRAY > \
void ITEM ## a_slice(ARRAY & a, ::index iStart = 0, ::count nCount = -1){ CONTAINER.slice(a, iStart, nCount);} \
DECLARE_TYPED_ARRAY_ACCESSOR_OF(ITEM, CONTAINER, TYPE, CONTAINER_TYPE)

#define HAVE_ARRAY_OF(ITEM, CONTAINER, TYPE) \
DECLARE_TYPED_ARRAY_OF(ITEM, CONTAINER, TYPE, __pointer_array(TYPE))

#define DECLARE_ARRAY_CONTAINER_OF(ARRAY, ITEM, CONTAINER, TYPE) \
ARRAY(const ::std::initializer_list < TYPE * > & list) : CONTAINER(list) { } \
DECLARE_TYPED_ARRAY_OF(ITEM, CONTAINER, TYPE, __pointer_array(TYPE))

#define DECLARE_ARRAY_OF(ARRAY, ITEM, TYPE) \
DECLARE_ARRAY_CONTAINER_OF(ARRAY, ITEM, m_ ## ITEM ## a, TYPE)


template < typename CONTAINER >
concept container_type = requires(CONTAINER container)
{

   {container.this_is_a_container()} -> std::same_as<void>;

};


template < container_type CONTAINERX, container_type CONTAINERY >
inline CONTAINERX operator +(CONTAINERX x, const CONTAINERY & y)
{

   x += y;

   return x;

}



// raw_array is an array that does not call constructors or destructor in elements
// array is an array that call only copy constructor and destructor in elements
// array is an array that call default constructors, copy constructs and destructors in elements
template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = allocator::nodef < TYPE > >
class array_base :
   public ::matter
{
public:


   typedef TYPE BASE_TYPE;
   using TYPE_IS_PTR = TYPE;


   TYPE *            m_pData;    // the actual array of data
   ::count   m_nSize;    // # of elements (upperBound - 1)
   ::count   m_nMaxSize; // maximum allocated
   ::count   m_nGrowBy;  // grow amount

   __declare_iterator_struct_ok(array_base, TYPE *, m_pelement, this->m_pelement >= this->m_pcontainer->m_pData && this->m_pelement < this->m_pcontainer->m_pData + this->m_pcontainer->m_nSize);

   array_base();
   array_base(TYPE * p, ::count c);
   array_base(const array_base & a);
   array_base(array_base && a) noexcept;
   virtual ~array_base();


   template < typename ITERATOR >
   struct make_iterator : ITERATOR
   {

      using CONTAINER = typename ITERATOR::CONTAINER;


      make_iterator()
      {
         this->m_pelementBeg = (TYPE*)nullptr;
         this->m_pelementEnd = (TYPE*)nullptr;
         this->m_pcontainer = (CONTAINER*)nullptr;
         this->m_pelement = this->m_pelementBeg;
      }

      make_iterator(::index iStart, ::index iEnd, const CONTAINER * parray = nullptr)
      {
         this->m_pelementBeg = (TYPE *) (parray->m_pData + iStart);
         this->m_pelementEnd = (TYPE *)(parray->m_pData + (iEnd < 0 ? parray->m_nSize + iEnd + 1 : iEnd));
         this->m_pcontainer = (CONTAINER *)parray;
         this->m_pelement = this->m_pelementBeg;
      }

      make_iterator(const CONTAINER * parray, const TYPE * pmatter = nullptr, const TYPE * pelementEnd = nullptr)
      {
         this->m_pelementBeg = (TYPE *) pmatter;
         this->m_pelementEnd = (TYPE *) pelementEnd;
         this->m_pcontainer = (CONTAINER *)parray;
         this->m_pelement = this->m_pelementBeg;
      }


      make_iterator(const make_iterator & iterator)
      {
         this->m_pelementBeg = (TYPE *) iterator.m_pelementBeg;
         this->m_pelementEnd = (TYPE *) iterator.m_pelementEnd;
         this->m_pelement = iterator.m_pelement;
         this->m_pcontainer = iterator.m_pcontainer;
      }


      make_iterator begin()
      {

         return make_iterator(this->m_pcontainer, this->m_pelementBeg, this->m_pelementEnd);

      }


      make_iterator end()
      {

         return make_iterator(this->m_pcontainer, this->m_pelementEnd, this->m_pelementEnd);

      }


      make_iterator & operator ++ ()
      {

         this->m_pelement++;
         return *this;

      }


      make_iterator operator ++ (i32)
      {

         auto it = *this;

         this->m_pelement++;
         return it;

      }


      make_iterator operator + (::count c) const
      {

         return { this->m_pcontainer, this->m_pelement + c};

      }


      make_iterator operator - (const make_iterator & it) const
      {

         return { this->m_pcontainer, this->m_pelement - it.index() };

      }


      bool operator == (const make_iterator & it) const
      {


         if (this->m_pcontainer != it.m_pcontainer)
         {

            return false;

         }

         return this->m_pelement == it.m_pelement;

      }


      bool operator >= (const make_iterator & it) const
      {


         if (this->m_pcontainer != it.m_pcontainer)
         {

            return false;

         }

         return this->m_pelement >= it.m_pelement;

      }


      bool operator > (const make_iterator & it) const
      {

         if (this->m_pcontainer != it.m_pcontainer)
         {

            return false;

         }

         return this->m_pelement > it.m_pelement;

      }


      bool operator != (const make_iterator & it) const
      {

         if (this->m_pcontainer != it.m_pcontainer)
         {

            return true;

         }

         return this->m_pelement != it.m_pelement;

      }

      bool operator < (const make_iterator & it) const
      {

         if (this->m_pcontainer != it.m_pcontainer)
         {

            return false;

         }

         return this->m_pelement < it.m_pelement;


      }

      bool operator <= (const make_iterator & it) const
      {

         if (this->m_pcontainer != it.m_pcontainer)
         {

            return false;

         }

         return this->m_pelement <= it.m_pelement;


      }


      bool operator == (const TYPE * pmatter) const
      {


         if (!this->m_pcontainer->contains(pmatter))
         {

            return false;

         }

         return this->m_pelement == pmatter;

      }


      bool operator >= (const TYPE * pmatter) const
      {


         if (!this->m_pcontainer->contains(pmatter))
         {

            return false;

         }

         return this->m_pelement >= pmatter;

      }


      bool operator > (const TYPE * pmatter) const
      {

         if (!this->m_pcontainer->contains(pmatter))
         {

            return false;

         }

         return this->m_pelement > pmatter;

      }


      bool operator != (const TYPE * pmatter) const
      {

         if (!this->m_pcontainer->contains(pmatter))
         {

            return true;

         }

         return this->m_pelement != pmatter;

      }

      bool operator < (const TYPE * pmatter) const
      {

         if (!this->m_pcontainer->contains(pmatter))
         {

            return false;

         }

         return this->m_pelement < pmatter;


      }

      bool operator <= (const TYPE * pmatter) const
      {

         if (!this->m_pcontainer->contains(pmatter))
         {

            return false;

         }

         return this->m_pelement <= pmatter;


      }

      make_iterator & operator = (const make_iterator & it)
      {

         if (this != &it)
         {

            this->m_pcontainer = it.m_pcontainer;

            this->m_pelement = it.m_pelement;

         }

         return *this;

      }

      ::index index() const { return this->m_pelement - this->m_pcontainer->m_pData; }

   };

   __declare_iterator(iterator, this->m_pelement);
   __declare_iterator(ref_iterator, *this->m_pelement);

   void this_is_a_container() {}

   inline auto values(index iStart = 0, index iEnd = -1) const { return iterator(iStart, iEnd, this); }


   inline iterator begin()
   {

      return iterator (0, (::index)m_nSize, this);

   }


   inline iterator end()
   {

      return iterator((::index)m_nSize, (::index)m_nSize, this);

   }


   inline const_iterator begin() const
   {

      return const_iterator(0, (::index) m_nSize, this);

   }


   inline const_iterator end() const
   {

      return const_iterator((::index) m_nSize,(::index) m_nSize, this);

   }


   inline bool contains(const TYPE * pmatter) const { return pmatter >= m_pData && pmatter < m_pData + m_nSize; }


   inline ::count get_size() const;
   inline ::count get_size_in_bytes() const;
   inline ::count get_count() const;
   inline ::count get_byte_count() const;
   inline ::count get_length() const;
   inline ::count size() const;
   inline ::count count() const;
   inline ::count length() const;


   inline bool has_element() const noexcept { return m_nSize > 0; }
   inline bool is_empty(::count countMinimum = 0) const noexcept { return m_nSize <= countMinimum; }
   inline bool empty(::count countMinimum = 0) const noexcept { return m_nSize <= countMinimum; }
   inline bool has_elements(::count countMinimum = 1) const noexcept { return m_nSize >= countMinimum; }
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


   inline TYPE * ptr_at(::index nIndex) const { return m_pData + nIndex; }
   inline TYPE * ptr_at(::index nIndex) { return m_pData + nIndex; }

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

   template < ::std::size_t N >
   TYPE& get() { return element_at(N); }


   ::count set_size(::count nNewSize, ::count nGrowBy = -1); // does not call default constructors on new items/elements
   ::count allocate(::count nNewSize, ::count nGrowBy = -1); // does not call default constructors on new items/elements
   ::count allocate_in_bytes(::count nNewSize, ::count nGrowBy = -1); // does not call default constructors on new items/elements
   ::count set_raw_size(::count nNewSize, ::count nGrowBy = -1); // does not call constructors and destructors on items/elements
   ::count resize(::count nNewSize, ::count nGrowBy = -1); // does not call default constructors on new items/elements

   void free_extra();
   virtual void destroy();

   inline void __swap(::index index1, ::index index2);
   inline void __swap(iterator index1, iterator index2);


   void set_all(const TYPE & t);


   void zero(::index iStart = 0, ::count c = -1);

   void _001RemoveIndexes(index_array & ia);
   void erase_indexes(const index_array & ia);
   void erase_descending_indexes(const index_array & ia);


   inline bool prepare_first_last(::index & first, ::index& last) const;
   inline bool prepare_first_in_count_last_out(::index& first, ::count & inCountLastOut) const;


   inline void erase_last();
   inline ::count erase_all();
   inline void clear();


   void on_construct_element(TYPE * p) { ALLOCATOR::construct(p); }
   void on_construct_element(TYPE * p, ::count c) { ALLOCATOR::construct_count(p, c); }
   void on_destruct_element(TYPE * p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) { ALLOCATOR::destruct(p  OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS); }
   void on_copy_element(::index i, const TYPE * p) { ALLOCATOR::copy(&m_pData[i], p); }


   inline const TYPE& operator[](::index i) const;
   inline TYPE& operator[](::index i);


   ::index insert_at(::index nIndex, const TYPE & newElement, ::count nCount = 1);
   ::index erase_at(::index nIndex, ::count nCount = 1);
   ::index insert_at(::index nStartIndex, array_base * pNewArray);


   ::index make_room_at(::index nIndex, ::count nCount = 1);

   
   TYPE pick_at(::index nIndex);
   TYPE pick_first(::index nIndex = 0) { return pick_at(nIndex); }
   TYPE pick_last(::index nIndex = -1) { return pick_at(m_nSize + nIndex); }
   array_base pick_at(::index nIndex, ::count nCount);


   ::index erase_item(TYPE * p);

   ::index index_of(const TYPE * p) const { auto i = p - this->m_pData; return i >= 0 && i < this->m_nSize ? i : -1; }


   bool erase(const TYPE * p) { auto i = index_of(p); if (!__found(i)) return false; return __found(erase_at(i)); }
   ::count erase(const TYPE * begin, const TYPE * end);

   template < typename ITERATOR > ITERATOR erase(ITERATOR it) { return ::papaya::iterator::erase(*this, it); }

   template < typename ITERATOR >
   inline void erase(const ITERATOR & begin, const ITERATOR & last);


   inline TYPE pop(::index i = -1);
   inline ::index push(ARG_TYPE newElement, ::index i = 0);
   inline void pop_back(::index i = -1);
   inline void push_back(ARG_TYPE newElement, ::index = 0);

   inline TYPE takeAt(::index i);
   inline TYPE takeFirst(::index i = 0);
   inline TYPE takeLast(::index i = -1);

   virtual ::count append(const array_base & src); // return old size_i32
   virtual void copy(const array_base & src);

   virtual void on_after_read();

   template < typename PRED >
   ::count predicate_each(PRED pred, ::index iStart = 0, ::count c = -1)
   {

      ::index iEnd = c < 0 ? get_count() + c : iStart + c - 1;

      int cProcessed = 0;

      for (::index i = iStart; i <= iEnd; i++)
      {

         pred(m_pData[i]);

         cProcessed++;

      }

      return cProcessed;

   }

   template < typename PRED >
   ::count predicate_each(PRED pred, ::index iStart = 0, ::count c = -1) const
   {

      return ((array_base < TYPE, ARG_TYPE, ALLOCATOR >*)this)->predicate_each(pred, iStart, c);

   }


   inline bool is_valid_index(::index i) const { return i >= 0 && i < get_count(); }

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
   TYPE_IS_PTR merge_get_existing(const TYPE_IS_PTR & p, const OBJECT& pobject, const ATTRIBUTE& attribute)
   {

      auto pModified = __new(typename TYPE_IS_PTR::TYPE(*p));

      pModified->process(pobject, attribute);

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

         if (pred(m_pData[i]))
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

         if (pred(m_pData[i]))
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

         if (pred(m_pData[i]))
         {

            return &element_at(i);

         }

      }

      return nullptr;

   }

   template < typename VAR >
   inline array_base & operator = (const class ::payload_type < VAR > & a);


   template < typename PRED >
   ::count predicate_get_count(PRED pred)
   {

      ::count c = 0;

      for (int i = 0; i < get_count(); i++)
      {

         if (pred(m_pData[i]))
         {

            c++;

         }

      }

      return c;

   }


   inline ::index add(ARG_TYPE newElement)
   {

      auto nIndex = this->m_nSize;

      this->allocate((::count) (nIndex + 1));

      this->last() = newElement;

      return (::index) nIndex;

   }


   template < typename PRED >
   ::count predicate_erase(PRED pred)
   {
      ::count cTotal = 0;
      for (int i = 0; i < get_count();)
      {

         if (!pred(m_pData[i]))
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

               if (!pred(m_pData[i]))
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
         f(m_pData[i]);
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

};


template < class TYPE, class ARG_TYPE, class ALLOCATOR = allocator::nodef < TYPE > >
inline TYPE& operator%(::index nIndex, const array_base < TYPE, ARG_TYPE, ALLOCATOR > & a)
{

   return (TYPE &) (a % nIndex);

}



