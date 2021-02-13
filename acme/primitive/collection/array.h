#pragma once



template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = ::allocator::def < TYPE > >
class array :
   public ::array_base < TYPE, ARG_TYPE, ALLOCATOR >
{
public:


   typedef TYPE BASE_TYPE;
   typedef ARG_TYPE BASE_ARG_TYPE;
   typedef array < TYPE, ARG_TYPE > BASE_ARRAY;
   typedef ::array_base < TYPE, ARG_TYPE, ALLOCATOR > ARRAY_BASE;
   typedef typename ARRAY_BASE::iterator iterator;
   typedef typename ARRAY_BASE::const_iterator const_iterator;
   typedef typename ARRAY_BASE::iterator_range iterator_range;
   typedef typename ARRAY_BASE::const_iterator_range const_iterator_range;


   explicit array(::matter * pobjectContext = nullptr, ::count nGrowBy = 0);

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
   array(array && a) noexcept : array_base< TYPE, ARG_TYPE, ALLOCATOR >(::move(a)) { }
   virtual ~array();


   inline const TYPE& get_at(::index nIndex) const;
   inline TYPE& get_at(::index nIndex);
   inline void set_at(::index nIndex, ARG_TYPE newElement);



   inline const TYPE* get_data() const;
   inline TYPE* get_data();

   // must not be overloaded!!
   inline ::index add_item(ARG_TYPE newElement);


   inline ::index add(ARG_TYPE newElement);
   template < container_type CONTAINER >
   inline ::index add(const CONTAINER & container);
   inline ::index append(ARG_TYPE newElement);
   inline ::index append(const array& src);
   inline void copy(const array& src);

   inline TYPE & add_new();
   inline ::index add_new( ::count count);


   inline array & operator << (ARG_TYPE newElement) { add(newElement); return *this; }




   // Operations that move elements around
   //inline ::index insert_at(::index nIndex, ARG_TYPE newElement, ::count nCount = 1);
   //void _001RemoveIndexes(index_array & ia);
   //void remove_indexes(const index_array & ia); // remove indexes from ::index array upper bound to ::index array lower bound
   //void remove_descending_indexes(const index_array & ia); // remove indexes from ::index array lower bound to ::index array upper bound
   //::index insert_at(::index nStartIndex, array* pNewArray);

   using array_base < TYPE, ARG_TYPE, ALLOCATOR > ::operator=;
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

   operator TYPE *() {return this->m_pData;}
   operator const TYPE *() const {return this->m_pData;}

   template < container_type CONTAINER >
   inline array & operator += (const CONTAINER & container);

   template < typename... T >
   void fadd(T... a)
   {

      add(TYPE(a...));

   }


   template < typename PRED >
   bool pred_add_unique(TYPE t, PRED pred)
   {

      if (this->pred_contains(pred))
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


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
bool array_base < TYPE, ARG_TYPE, ALLOCATOR > ::prepare_first_last(::index & first, ::index & last) const
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


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
bool array_base < TYPE, ARG_TYPE, ALLOCATOR > ::prepare_first_in_count_last_out(::index & first, ::count & in_count_out_last) const
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

