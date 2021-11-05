#pragma once


// raw_array is an array that does not call constructors or destructor in elements
// array is an array that call only copy constructor and destructor in elements
// array is an array that call default constructors, copy constructs and destructors in elements


template < typename TYPE, typename ARG_TYPE = const TYPE &, typename ALLOCATOR = ::allocator::nodef < TYPE >, enum_type t_etypePayload = e_type_element >
class raw_array :
   public array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >
{
public:


   typedef TYPE BASE_TYPE;
   typedef ARG_TYPE BASE_ARG_TYPE;
   typedef raw_array < TYPE,ARG_TYPE > BASE_ARRAY;
   using ARRAY_BASE = array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >;
   typedef typename ARRAY_BASE::iterator iterator;


   explicit raw_array(::matter * pobject = nullptr);
   raw_array(std::initializer_list < TYPE >  l);
   raw_array(const raw_array <TYPE, ARG_TYPE, ALLOCATOR> & a);
   raw_array(raw_array <TYPE,ARG_TYPE,ALLOCATOR> && a) noexcept;
   raw_array(::count n);
   raw_array(ARG_TYPE t, ::count n);
   raw_array(TYPE * ptypea, ::count n);
   virtual ~raw_array();


   //void assert_valid() const override;
   //void dump(dump_context & dumpcontext) const override;




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

   // Potentially growing the raw_array
   //void set_at_grow(::index nIndex, ARG_TYPE newElement);
   //TYPE & element_at_grow(::index nIndex);
   TYPE get_at_grow(::index nIndex);
   ::index add(ARG_TYPE newElement) { return add_item(newElement); }
   ::index add_item(ARG_TYPE newElement);
   ::index add(const raw_array& src);
   virtual ::index add_new(::count count);
   virtual TYPE & add_new();
   //::index append(const raw_array& src);
   //void copy(const raw_array& src);


   inline TYPE pop(::index i = -1);
   inline ::index push(ARG_TYPE newElement,::index i = 0);
   inline void pop_back(::index i = -1);
   inline void push_back(ARG_TYPE newElement, ::index = 0);



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

   // Operations that move elements around
   ::index insert_at(::index nIndex, ARG_TYPE newElement, ::count nCount = 1);
   //::index erase_at(::index nIndex, ::count nCount = 1);
   //void _001RemoveIndexes(index_array & ia);
   //void erase_indexes(const index_array & ia); // erase indexes from ::index raw_array upper bound to ::index raw_array lower bound
   //void erase_descending_indexes(const index_array & ia); // erase indexes from ::index raw_array lower bound to ::index raw_array upper bound
   //::index insert_at(::index nStartIndex, raw_array* pNewArray);
   void __swap(::index index1, ::index index2);

   raw_array & operator = (const raw_array & src);

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


   raw_array & operator += (const raw_array & a);
   raw_array operator + (const raw_array & a) const;


   using array_base < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload >::operator =;
   inline raw_array & operator = (raw_array && a);
   inline raw_array & move(raw_array && a);


   operator TYPE *() { return this->m_pData;  }
   operator const TYPE *() const { return this->m_pData; }
   operator ::count () const { return this->get_count(); }


};


