#pragma once


//#include "pointer_array_process.h"
#include  "acme/primitive/collection/array.h"
//#include "acme/primitive/primitive/pointer.h"
//#include "comparable_eq_array.h"
//#include "comparable_array.h"


template < class T >
class pointer_array :
   public pointer_array_process < comparable_array < ::pointer < T >, const T * >, T >
{
public:

   using BASE_ARRAY = pointer_array_process < comparable_array < ::pointer < T >, const T * > , T >;

   //using ref_iterator = typename ARRAY_BASE::ref_iterator;
   ///using ref_iterator_range = typename ARRAY_BASE::ref_iterator_range;

   using comparable_array < ::pointer < T >, const T * >::operator &=;
   using comparable_array < ::pointer < T >, const T * >::operator -=;
   using comparable_array < ::pointer < T >, const T * >::operator |=;
   using comparable_array < ::pointer < T >, const T * >::operator -;
//   using comparable_array < ::pointer<T > > ::operator ==;
//   using comparable_array < ::pointer<T > > ::operator !=;

   pointer_array()
   {

   }


   explicit pointer_array(std::nullptr_t)
   {

   }


   virtual ~pointer_array()
   {

      this->erase_all();

   }


   pointer_array(const pointer_array & a) : BASE_ARRAY(a) { }

   pointer_array(pointer_array && a) : BASE_ARRAY(::transfer(a)) { }


   template < typename OTHER >
   pointer_array(const pointer_array < OTHER > & a)
   {

      for(auto & p : a)
      {

         pointer < T > pNew = p;

         if(pNew)
         {

            add(pNew);

         }

      }

   }


   pointer_array(const std::initializer_list < ::pointer<T >>& list)
   {

      for(auto & p : list)
      {

         add(p);

      }

   }


   pointer < T >& add_new()
   {

      return comparable_array < ::pointer<T >, const T * >::add_new();

   }


   template < typename OBJECT >
   pointer < T > & add_construct(OBJECT * pparticle)
   {

      pointer < T > & p = comparable_array < ::pointer<T >, const T * >::add_new();

      pparticle->__construct(p);

      return p;

   }


   ::raw::count set_size(::raw::count nNewSize, ::raw::count nGrowBy = -1)
   {

      return comparable_array < ::pointer<T >, const T * > :: set_size(nNewSize);

   }

   template < typename OBJECT >
   ::raw::count set_size_create(OBJECT * pparticle, ::raw::count nNewSize, ::raw::count nGrowBy = -1);


   template < class DERIVED >
   ::pointer<DERIVED>get(::raw::index iStart = 0)
   {

      ::pointer<DERIVED>pderived;

      for(::raw::index i = iStart; i < this->get_count(); i++)
      {

         try
         {

            pderived = this->element_at(i);

         }
         catch(...)
         {

         }

         if (pderived.is_set())
         {

            return pderived;

         }

      }

      return nullptr;

   }


   template < class DERIVED >
   ::pointer<DERIVED>typed_ptr_at(::raw::index iIndex)
   {

      return this->element_at(iIndex);

   }


   /// consumes a referer
   inline ::raw::index add_item(const pointer < T > & p)
   {

      ::raw::index nIndex = this->size();

      this->allocate(nIndex + 1, false, false, p);

      return nIndex;

   }


   /// referer is transfered?
   inline ::raw::index add_item(pointer < T > && p)
   {

      ::raw::index nIndex = this->size();

      this->allocate(nIndex + 1, false, true);

      ::new (this->m_begin + nIndex) ::pointer < T >(::transfer(p));

      return nIndex;

   }
   

   template < container_type CONTAINER >
   ::raw::index append(const CONTAINER & a)
   {

      return BASE_ARRAY::append(a);

   }


   //::raw::index add(T * p)
   //{

   //   return this->add_item(p);

   //}


   /// consumes a referer
   ::raw::index add(const pointer < T > & p)
   {

      return this->add_item(p);

   }


   /// referer is transferred?
   ::raw::index add(pointer < T > && p)
   {

      return this->add_item(::transfer(p));

   }


   /// consumes a referer
   ::raw::index add_non_null(T* p)
   {

      if (::is_null(p))
      {

         return -1;

      }

      return this->add_item(p);

   }


   /// consumes a referer
   void insert_at(::raw::index i, T* p)
   {

      //::raw::index nIndex = this->size();

      comparable_array < ::pointer<T >, const T * >::insert_at(i, p);

      //this->element_at(i)->add_reference_item();

   }


   bool insert_unique_at(::raw::index i, T * p);


   /// consumes a referer
   bool add_unique(T * p)
   {

      if (contains(p))
      {

         return false;

      }

      this->add_item(p);

      return true;

   }


   template < typename TYPE >
   ::pointer<TYPE>find_first() const
   {

      for (auto & pointer : this->ptra())
      {

         ::pointer<TYPE> ptype = pointer;

         if(ptype)
         {

            return ptype;

         }

      }

      return nullptr;

   }

   template < typename TYPE >
   bool contains() const
   {

      return find_first < TYPE >();

   }


   template < typename TYPE >
   bool has() const
   {

      return contains < TYPE >();

   }

   ::raw::count add_unique(const pointer_array & a)
   {

      ::raw::count c = 0;

      for (::raw::index i = 0; i < a.get_count(); i++)
      {

         if (add_unique((T *) a[i]))
            c++;

      }

      return c;

   }

   bool contains(const T * p, ::raw::index iStart = 0, ::raw::count nCount = -1) const
   {

      return find_first(p, iStart, nCount) >= 0;

   }


   ::raw::index find_first(const T * p, ::raw::index iStart = 0, ::raw::count inCountLastOut = -1) const
   {

      this->prepare_first_in_count_last_out(iStart, inCountLastOut);

      for(::raw::index i = iStart; i <= inCountLastOut; i++)
      {

         auto& pointer = this->element_at(i);

         if (pointer && pointer.m_p == p)
         {

            return i;

         }

      }

      return -1;

   }


   void call_member(enum_id eid, ::raw::index iStart = 0, ::raw::count inCountLastOut = -1)
   {

      this->prepare_first_in_count_last_out(iStart, inCountLastOut);

      //::raw::count cFailed = 0;

      //::raw::count cSucceeded = 0;

      for (::raw::index i = iStart; i <= inCountLastOut; i++)
      {

         auto p = this->element_at(i);

         p->call_member(eid);

      }

      //auto estatus = _003CountStatus(cSucceeded, cFailed);

      //return estatus;

   }


   ::raw::index comp_find_first(const T & t, ::raw::index (* pfnCompare)(const T *, const T *), ::raw::index iStart = 0, ::raw::count nCount = -1) const
   {

      return this->comp_find_first(&t, pfnCompare, iStart, nCount);

   }


   ::raw::index comp_find_first(const T * p, ::raw::index (* pfnCompare)(const T *, const T *), ::raw::index iStart = 0, ::raw::count inCountLastOut = -1) const
   {

      this->prepare_first_in_count_last_out(iStart, inCountLastOut);

      for(::raw::index i = iStart; i <= inCountLastOut; i++)
      {

         if (pfnCompare(this->element_at(i).m_p, p) == 0)
         {

            return i;

         }

      }

      return -1;

   }


   template < class DERIVED >
   pointer_array & operator -= (DERIVED * p)
   {

      this->erase(dynamic_cast < T * > (p));

      return *this;

   }

   
   /// consumes a releaser
   ::raw::count erase(T* p)
   {

      return this->erase_item(p);

   }


   ::raw::count erase_item(T * p)
   {

      ::raw::count ca = 0;

      ::raw::index iFind = 0;

      while((iFind = this->find_first(p, iFind)) >= 0)
      {

         ca++;

         this->erase_at(iFind);

      }

      return ca;

   }


   //inline const pointer < T > & element_at(::raw::index i) const { return ARRAY_BASE::element_at(i); }
   //inline pointer < T > & element_at(::raw::index i) { return ARRAY_BASE::element_at(i); }


   template < typename TYPE >
   ::raw::count erase_type(TYPE *)
   {

      ::raw::count c = 0;

      for (::raw::index i = this->get_upper_bound(); i >= 0; i--)
      {

         if (typeid(*this->element_at(i).m_p) == typeid(TYPE))
         {

            this->erase_at(i);

            c++;

         }

      }

      return c;

   }



   template < typename PRED >
   ::raw::index predicate_erase_first(PRED pred, ::raw::index iStart = 0)
   {

      for (::raw::index i = iStart; i < this->get_count(); i++)
      {

         if (pred(this->m_begin[i]))
         {

            this->erase_at(i);

            return i;

         }

      }

      return -1;

   }


   template < typename PRED >
   ::raw::index predicate_erase_last(PRED pred, ::raw::index iStart = 0)
   {

      for (::raw::index i = this->get_upper_bound(); i >= 0; i--)
      {

         if (pred(this->m_begin[i]))
         {

            this->erase_at(i);

            return i;

         }

      }

      return -1;

   }

   template < typename PRED >
   pointer < T > predicate_erase_all_get_first(PRED pred, ::raw::index iStart = 0, ::raw::index iEnd = -1)
   {

      pointer < T > sp;

      if (iEnd < 0)
      {

         iEnd += this->get_count();

      }

      if (iEnd >= this->get_count())
      {

         iEnd = this->get_count() - 1;

      }


      for (::raw::index i = iStart; i <= iEnd;)
      {

         if (pred(this->m_pData[i]))
         {

            if (sp.is_null())
            {

               sp = this->m_pData[i];

            }

            this->erase_at(i);

         }
         else
         {

            i++;

         }

      }

      return sp;

   }



   const pointer < T > & sp_at(::raw::index nIndex) const
   {

      return this->comparable_array < ::pointer<T >, const T * > ::element_at(nIndex);

   }


   pointer < T > & sp_at(::raw::index nIndex)
   {

      return this->comparable_array < ::pointer<T >, const T * > ::element_at(nIndex);

   }


   T * ptr_at(::raw::index nIndex) const
   {

      return this->sp_at(nIndex);

   }


   T * ptr_at(::raw::index nIndex)
   {

      return this->sp_at(nIndex);

   }


   T & at(::raw::index nIndex) const
   {

      return *this->ptr_at(nIndex);

   }


   T & at(::raw::index nIndex)
   {

      return *this->ptr_at(nIndex);

   }

   T * get_first_pointer(::raw::index n = 0) const
   {

      return this->is_empty() ? nullptr : this->comparable_array < ::pointer<T >, const T *> ::first(n);

   }

   
   pointer < T > pop_first(::raw::index n = 0)
   {

      auto p = ::transfer(this->comparable_array < ::pointer<T >, const T * > ::first(n));
      
      this->comparable_array < ::pointer<T >, const T * > ::erase_at(n);
      
      return p;

   }


   pointer < T > & first_pointer(::raw::index n = 0)
   {

      return this->comparable_array < ::pointer<T >, const T * > ::first(n);

   }


   T * first_ptr(::raw::index n = 0) const
   {

      if (this->is_empty())
      {

         return nullptr;

      }

      return this->get_first_pointer(n);

   }


   T * first_ptr(::raw::index n = 0)
   {

      return this->first_pointer(n);

   }


   T * get_last_pointer(::raw::index n = -1) const
   {

      return this->is_empty() ? nullptr : this->comparable_array < ::pointer<T >, const T * > ::last(n);

   }


   pointer < T > & last_pointer(::raw::index n = -1)
   {

      return this->comparable_array < ::pointer<T >, const T * > ::last(n);

   }


   T * last_ptr(::raw::index n = -1) const
   {

      return this->get_last_pointer(n);

   }


   T * last_ptr(::raw::index n = -1)
   {

      return this->last_pointer(n);

   }


   const T & operator() (::raw::index nIndex) const
   {

      return *this->sp_at(nIndex);

   }


   T & operator() (::raw::index nIndex)
   {

      return *this->sp_at(nIndex);

   }



   template < typename PRED >
   T * predicate_ptr_first(PRED pred)
   {

      ::raw::index i = this->predicate_find_first(pred);

      if(i < 0)
         return nullptr;

      return this->ptr_at(i);

   }



   //template < primitive_container ARRAY >
   //::raw::count add(const ARRAY * pa)
   //{

   //   ::raw::count c = pa->get_count(); // allow to append to itself one time

   //   for(::raw::index i = 0; i < c; i++)
   //   {
   //      this->add(pa->element_at(i));
   //   }

   //   return c;

   //}

   template < primitive_container ARRAY >
   ::raw::count add(const ::pointer<ARRAY>& pa)
   {

      ::raw::count c = pa->get_count(); // allow to append to itself one time

      for(::raw::index i = 0; i < c; i++)
      {
         this->add(pa->element_at(i));
      }

      return c;

   }

   template < primitive_container ARRAY >
   ::raw::count add(const ARRAY & a)
   {

      ::raw::count c = a.get_count(); // allow to append to itself one time

      for(::raw::index i = 0; i < c; i++)
      {
         this->add(a.element_at(i));
      }

      return c;

   }


   ::raw::count append(const pointer_array & a)
   {

      ::raw::count c = a.get_count(); // allow to append to itself one time

      for(::raw::index i = 0; i < c; i++)
      {

         this->add(a.sp_at(i));

      }

      return c;

   }


   template < primitive_container ARRAY >
   ::raw::count append_ptra(const ARRAY* pptra)
   {

      ::raw::count c = pptra->get_count(); // allow to append to itself one time

      for(::raw::index i = 0; i < c; i++)
      {
         this->add(*pptra->element_at(i));
      }

      return c;

   }

   //template < class ARRAY >
   //pointer_array & copy(const ARRAY * pa)
   //{

   //   if(pa == dynamic_cast < ARRAY * > (this))
   //      return *this;

   //   this->erase_all();

   //   this->append(pa);

   //   return *this;

   //}

   template < class ARRAY >
   pointer_array & copy(const ::pointer<ARRAY>& pa)
   {

      if(pa == dynamic_cast < ARRAY * > (this))
         return *this;

      this->erase_all();

      this->append(pa);

      return *this;

   }


   ::raw::count erase_all()
   {

      //auto size = this->size();

      for (::raw::index i = 0; i < this->get_size(); i++)
      {

         try
         {

            auto & p = this->element_at(i);

            if (p)
            {

               p.release();

            }

         }
         catch (...)
         {

         }

      }

      return comparable_array < ::pointer<T >, const T * > ::erase_all();

   }

   //template < class ARRAY >
   //pointer_array & copy(const ARRAY & a)
   //{

   //   this->erase_all();

   //   this->append(a);

   //   return *this;

   //}

   pointer_array & copy(const pointer_array & a)
   {

      if(&a == this)
         return *this;

      this->erase_all();

      this->append(a);

      return *this;

   }

   template < class ARRAY >
   pointer_array & copy_ptra(const ARRAY * pptra)
   {

      if(pptra == dynamic_cast < ARRAY * > (this))
         return *this;

      this->erase_all();

      this->append(pptra);

      return *this;

   }



   inline pointer_array & operator = (const pointer_array & a)
   {

      copy(a);

      return *this;

   }


   inline pointer_array & operator = (pointer_array && a)
   {

      comparable_array < ::pointer<T >, const T * > ::operator = (::transfer(a));

      return *this;

   }

   void destroy_all()
   {

      for (auto& p : *this)
      {

         p->destroy();

      }

   }

};


//
//
//
//// Range-based for loop support
//// smart_pointer_range2 indirect/interpreted contribution from
///**
//* pugixml parser - version 1.5
//* --------------------------------------------------------
//* Copyright (C) 2006-2014, by Arseny Kapoulkine (arseny.kapoulkine@gmail.com)
//* Report bugs and download new versions at http://pugixml.org/
//*
//* This library is distributed under the MIT License. See notice at the end
//* of this file.
//*
//* This work is based on the pugxml parser, which is:
//* Copyright (C) 2003, by Kristen Wegner (kristen@tima.net)
//*/
//
//template < typename Iterator > class smart_pointer_range2
//{
//public:
//
//   Iterator m_beg;
//   Iterator m_end;
//
//   smart_pointer_range2(Iterator beg,Iterator end): m_beg(beg),m_end(end)
//   {
//   }
//
//   Iterator begin()  const { return m_beg; }
//   Iterator end()    const { return m_end; }
//
//private:
//
//};
//
//
//template < class T >
//class smart_pointer_array2:
//   public comparable_array < ::pointer<T >>
//{
//public:
//
//
//   class ref_iterator
//   {
//   public:
//
//      typedef T BASE_TYPE;
//      typedef const T & BASE_ARG_TYPE;
//      typedef smart_pointer_array2 BASE_ARRAY;
//
//      ::raw::index            m_i;
//      BASE_ARRAY *     m_parray;
//
//      ref_iterator()
//      {
//         m_i = 0;
//         m_parray = nullptr;
//      }
//
//      ref_iterator(::raw::index i,BASE_ARRAY * parray)
//      {
//         m_i = i;
//         m_parray = parray;
//      }
//
//      ref_iterator(const ref_iterator & it)
//      {
//         operator = (it);
//      }
//
//
//      ref_iterator & operator = (const ref_iterator & it)
//      {
//         if(this != &it)
//         {
//            m_i         = it.m_i;
//            m_parray    = it.m_parray;
//         }
//         return *this;
//      }
//
//      bool operator == (const ref_iterator & it)
//      {
//         if(this == &it)
//            return true;
//         if(m_parray != it.m_parray)
//            return false;
//         if(m_i >= m_parray->get_size() && it.m_i >= m_parray->get_size())
//            return true;
//         if(m_i <= 0 && it.m_i <= 0)
//            return true;
//         return m_i == it.m_i;
//      }
//
//      bool operator != (const ref_iterator & it)
//      {
//         return !operator==(it);
//      }
//
//      ref_iterator operator ++(int)
//      {
//         ref_iterator it = *this;
//         operator ++();
//         return it;
//      }
//
//      ref_iterator operator --(int)
//      {
//         ref_iterator it = *this;
//         operator --();
//         return it;
//      }
//
//      ref_iterator & operator ++()
//      {
//         m_i++;
//         if(m_i >= m_parray->get_size())
//            m_i = m_parray->get_size();
//         return *this;
//      }
//
//      ref_iterator & operator +(::raw::index i)
//      {
//         m_i += i;
//         if(m_i >= m_parray->get_size())
//            m_i = m_parray->get_size();
//         return *this;
//      }
//
//      ref_iterator & operator --()
//      {
//         m_i--;
//         if(m_i < 0)
//            m_i = 0;
//         return *this;
//      }
//
//      ref_iterator mid(const ref_iterator & i) const
//      {
//         return ref_iterator((m_i + i.m_i + 1) / 2,m_parray);
//      }
//
//      ref_iterator & operator -(::raw::count c)
//      {
//         m_i-=c;
//         if(m_i < 0)
//            m_i = 0;
//         return *this;
//      }
//
//      bool operator < (const ref_iterator & i) const
//      {
//
//         return m_i < i.m_i;
//
//      }
//
//      ::raw::count get_count() const
//      {
//         return m_parray->get_count();
//      }
//
//
//      T & operator * ()
//      {
//         return m_parray->at(m_i);
//      }
//
//      const T & operator * () const
//      {
//         return m_parray->at(m_i);
//      }
//
//
//   };
//
//   typedef smart_pointer_range2 < ref_iterator > ref_range;
//
//
//   smart_pointer_array2()
//   {
//
//   }
//
//   virtual ~smart_pointer_array2()
//   {
//
//      this->erase_all();
//
//   }
//
//#if defined(MOVE_SEMANTICS)
//
//   smart_pointer_array2(smart_pointer_array2 && a)
//   {
//
//      comparable_array < ::pointer<T > > ::operator = (a);
//
//   }
//
//   inline smart_pointer_array2 & operator = (smart_pointer_array2 && a)
//   {
//
//      comparable_array < ::pointer<T > > ::operator = (a);
//
//      return *this;
//
//   }
//
//#endif
//
//   smart_pointer_array2(const smart_pointer_array2 & a):
//      comparable_array < ::pointer<T >>a)
//   {
//
//      comparable_array < ::pointer<T > > ::operator = (a);
//
//   }
//
//   inline smart_pointer_array2 & operator = (const smart_pointer_array2 & a)
//   {
//
//      copy(a);
//
//      return *this;
//
//   }
//
//
//   smart_pointer_array2(::particle * pparticle):
//      ::matter(pparticle),
//      comparable_array < ::pointer<T >>pparticle)
//   {
//   }
//
//   pointer < T > & add_new()
//   {
//
//      pointer < T > & sp = comparable_array < ::pointer<T > > ::add_new();
//
//      sp.alloc(this->create_new, this);
//
//      return sp;
//
//   }
//
//
//   ::raw::count set_size(::raw::count nNewSize,::raw::count nGrowBy = -1)
//   {
//
//      return comparable_array < ::pointer<T > > ::: set_size(nNewSize);
//
//   }
//
//   ::raw::count set_size_create(::raw::count nNewSize,::raw::count nGrowBy = -1)
//   {
//      ::raw::index i = this->get_size();
//      comparable_array < ::pointer<T > > ::: set_size(nNewSize);
//      ::raw::count ca = this->get_size();
//      for(; i < ca; i++)
//      {
//         this->element_at(i).alloc(this->create_new, this);
//      }
//      return ca;
//   }
//
//
//   template < class DERIVED >
//   DERIVED * get(::raw::index iStart = 0)
//   {
//
//      DERIVED * pderived = nullptr;
//
//      for(::raw::index i = iStart; i < this->get_count(); i++)
//      {
//
//         try
//         {
//
//            pderived = dynamic_cast < DERIVED * > (this->element_at(i).m_p);
//
//         }
//         catch(...)
//         {
//
//         }
//
//         if(pderived != nullptr)
//            return pderived;
//
//      }
//
//      return nullptr;
//
//   }
//
//   template < class DERIVED >
//   DERIVED * typed_ptr_at(::raw::index iIndex)
//   {
//
//      return dynamic_cast < DERIVED * > (this->element_at(iIndex).m_p);
//
//   }
//
//   pointer < T > & add(T * p)
//   {
//
//      return comparable_array < ::pointer<T > > ::add_new() = p;
//
//   }
//
//
//   bool add_unique(T * p)
//   {
//
//      if(contains(p))
//         return false;
//
//      this->add(p);
//
//      return true;
//
//   }
//
//   ::raw::count add_unique(const smart_pointer_array2 & a)
//   {
//
//      ::raw::count c = 0;
//
//      for(::raw::index i = 0; i < a.get_count(); i++)
//      {
//
//         if(add_unique((T *)a[i]))
//            c++;
//
//      }
//
//      return c;
//
//   }
//
//   bool contains(const T * p,::raw::index iStart = 0,::raw::count nCount = -1) const
//   {
//
//      return find_first(p,iStart,nCount) >= 0;
//
//   }
//
//   ::raw::index find_first(const T * p,::raw::index iStart = 0,::raw::count nCount = -1) const
//   {
//
//      ::raw::index iEnd;
//
//      if(nCount < 0)
//         iEnd = this->get_upper_bound(nCount);
//      else
//         iEnd = iStart + nCount - 1;
//
//      for(::raw::index i = iStart; i <= iEnd; i++)
//      {
//
//         if(this->element_at(i).m_p == p)
//            return i;
//
//      }
//
//      return -1;
//
//   }
//
//
//   ::raw::index find_first(const T & t,::raw::index(* pfnCompare)(const T *,const T *),::raw::index iStart = 0,::raw::count nCount = -1) const
//
//   {
//
//      return this->find_first(&t,pfnCompare,iStart,nCount);
//
//
//   }
//
//
//   ::raw::index find_first(const T * p,::raw::index(* pfnCompare)(const T *,const T *),::raw::index iStart = 0,::raw::count nCount = -1) const
//
//   {
//
//      ::raw::index iEnd;
//
//      if(nCount < 0)
//         iEnd = this->get_upper_bound(nCount);
//      else
//         iEnd = iStart + nCount - 1;
//
//      for(::raw::index i = iStart; i <= iEnd; i++)
//      {
//
//         if(pfnCompare(this->element_at(i).m_p,p) == 0)
//
//            return i;
//
//      }
//
//      return -1;
//
//   }
//
//   template < class DERIVED >
//   smart_pointer_array2 & operator -= (DERIVED * p)
//   {
//
//      this->erase(dynamic_cast < T * > (p));
//
//      return *this;
//
//   }
//
//   ::raw::count erase(T * p)
//   {
//
//      ::raw::count ca = 0;
//
//      ::raw::index iFind = 0;
//
//      while((iFind = this->find_first(p,iFind)) >= 0)
//      {
//
//         ca++;
//
//         this->erase_at(iFind);
//
//      }
//
//      return ca;
//
//   }
//
//
//   template < typename TYPE >
//   ::raw::count erase_type(TYPE *)
//   {
//
//      ::raw::count c = 0;
//
//      for(::raw::index i = this->get_upper_bound(); i >= 0; i--)
//      {
//
//         if(typeid(*this->element_at(i).m_p) == typeid(TYPE))
//         {
//
//            this->erase_at(i);
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
//   // overloaded operator helpers
//   T  & element_at(::raw::index nIndex) const
//   {
//
//      return *this->comparable_array < ::pointer<T > > ::element_at(nIndex).m_p;
//
//   }
//
//   T  & element_at(::raw::index nIndex)
//   {
//
//      return *this->comparable_array < ::pointer<T > > ::element_at(nIndex).m_p;
//
//   }
//
//   const pointer < T > & sp_at(::raw::index nIndex) const
//   {
//
//      return this->comparable_array < ::pointer<T > > ::element_at(nIndex);
//
//   }
//
//
//   pointer < T > & sp_at(::raw::index nIndex)
//   {
//
//      return this->comparable_array < ::pointer<T > > ::element_at(nIndex);
//
//   }
//
//
//   T * ptr_at(::raw::index nIndex) const
//   {
//
//      return this->sp_at(nIndex);
//
//   }
//
//
//   T * ptr_at(::raw::index nIndex)
//   {
//
//      return this->sp_at(nIndex);
//
//   }
//
//
//   T & at(::raw::index nIndex) const
//   {
//
//      return *this->ptr_at(nIndex);
//
//   }
//
//
//   T & at(::raw::index nIndex)
//   {
//
//      return *this->ptr_at(nIndex);
//
//   }
//
//   const pointer < T > & first_pointer(::raw::index n = 0) const
//   {
//
//      return this->comparable_array < ::pointer<T > > ::first(n);
//
//   }
//
//
//   pointer < T > & first_pointer(::raw::index n = 0)
//   {
//
//      return this->comparable_array < ::pointer<T > > ::first(n);
//
//   }
//
//
//   T * first_ptr(::raw::index n = 0) const
//   {
//
//      return this->first_pointer(n);
//
//   }
//
//
//   T * first_ptr(::raw::index n = 0)
//   {
//
//      return this->first_pointer(n);
//
//   }
//
//
//   T & first(::raw::index n = 0) const
//   {
//
//      return *this->first_ptr(n);
//
//   }
//
//
//   T & first(::raw::index n = 0)
//   {
//
//      return *this->first_ptr(n);
//
//   }
//
//
//   T * last_pointer(::raw::index n = -1) const
//   {
//
//      return this->comparable_array < ::pointer<T > > ::last(n);
//
//   }
//
//
//   pointer < T > & last_pointer(::raw::index n = -1)
//   {
//
//      return this->comparable_array < ::pointer<T > > ::last(n);
//
//   }
//
//
//   T * last_ptr(::raw::index n = -1) const
//   {
//
//      return this->last_pointer(n);
//
//   }
//
//
//   T * last_ptr(::raw::index n = -1)
//   {
//
//      return this->last_pointer(n);
//
//   }
//
//
//   T & last(::raw::index n = -1) const
//   {
//
//      return *last_ptr(n);
//
//   }
//
//
//   T & last(::raw::index n = -1)
//   {
//
//      return *this->last_ptr(n);
//
//   }
//
//
//   const T & operator() (::raw::index nIndex) const
//   {
//
//      return *this->sp_at(nIndex);
//
//   }
//
//
//   T & operator() (::raw::index nIndex)
//   {
//
//      return *this->sp_at(nIndex);
//
//   }
//
//
//   template < class ARRAY >
//   smart_pointer_array2 & append(const ARRAY * pa)
//   {
//
//      ::raw::count c = pa->get_count(); // allow to append to itself one time
//
//      for(::raw::index i = 0; i < c; i++)
//      {
//         this->add(pa->element_at(i));
//      }
//
//      return *this;
//
//   }
//
//   template < class ARRAY >
//   smart_pointer_array2 & append(const ::pointer<ARRAY>& pa)
//   {
//
//      ::raw::count c = pa->get_count(); // allow to append to itself one time
//
//      for(::raw::index i = 0; i < c; i++)
//      {
//         this->add(pa->element_at(i));
//      }
//
//      return *this;
//
//   }
//
//   template < class ARRAY >
//   smart_pointer_array2 & append(const ARRAY & a)
//   {
//
//      ::raw::count c = a.get_count(); // allow to append to itself one time
//
//      for(::raw::index i = 0; i < c; i++)
//      {
//         this->add(a.element_at(i));
//      }
//
//      return *this;
//
//   }
//
//
//   smart_pointer_array2 & append(const smart_pointer_array2 & a)
//   {
//
//      ::raw::count c = a.get_count(); // allow to append to itself one time
//
//      for(::raw::index i = 0; i < c; i++)
//      {
//
//         this->add(a.sp_at(i));
//
//      }
//
//      return *this;
//
//   }
//
//
//   template < class ARRAY >
//   smart_pointer_array2 & append_ptra(const ARRAY * pptra)
//   {
//
//      ::raw::count c = pptra->get_count(); // allow to append to itself one time
//
//      for(::raw::index i = 0; i < c; i++)
//      {
//         this->add(*pptra->element_at(i));
//      }
//
//      return *this;
//
//   }
//
//   template < class ARRAY >
//   smart_pointer_array2 & copy(const ARRAY * pa)
//   {
//
//      if(pa == dynamic_cast < ARRAY * > (this))
//         return *this;
//
//      this->erase_all();
//
//      this->append(pa);
//
//      return *this;
//
//   }
//
//   template < class ARRAY >
//   smart_pointer_array2 & copy(const ::pointer<ARRAY>& pa)
//   {
//
//      if(pa == dynamic_cast < ARRAY * > (this))
//         return *this;
//
//      this->erase_all();
//
//      this->append(pa);
//
//      return *this;
//
//   }
//
//   template < class ARRAY >
//   smart_pointer_array2 & copy(const ARRAY & a)
//   {
//
//      if(&a == dynamic_cast < ARRAY * > (this))
//         return *this;
//
//      this->erase_all();
//
//      this->append(a);
//
//      return *this;
//
//   }
//
//   smart_pointer_array2 & copy(const smart_pointer_array2 & a)
//   {
//
//      if(&a == this)
//         return *this;
//
//      this->erase_all();
//
//      this->append(a);
//
//      return *this;
//
//   }
//
//   template < class ARRAY >
//   smart_pointer_array2 & copy_ptra(const ARRAY * pptra)
//   {
//
//      if(pptra == dynamic_cast < ARRAY * > (this))
//         return *this;
//
//      this->erase_all();
//
//      this->append(pptra);
//
//      return *this;
//
//   }
//
//   ref_iterator ref_it(::raw::index iStart) { return ref_iterator(iStart,this); }
//   ref_iterator ref_it(::raw::index iStart,::raw::count cCount) { return ref_iterator(iStart + (cCount < 0 ? this->get_count() + cCount + 1 : cCount),this); }
//
//   ref_range refa(::raw::index iStart = 0,::raw::count cCount = -1) { return smart_pointer_range2 < ref_iterator >(ref_it(iStart),ref_it(iStart,cCount)); }
//
//};

//#define sspa(TYPE) array_base < ::pointer<TYPE >>
//#define spa2(TYPE) ::smart_pointer_array2 < TYPE >
///#define __xmlspa(TYPE) ::pointer_array < TYPE >

typedef pointer_array < matter > object_pointera;

typedef pointer_array < matter > simple_object_pointera;


template < typename T >
bool pointer_array < T > ::insert_unique_at(::raw::index i, T * p)
{

   if (i < 0 || i > this->get_size())
   {

      throw_exception(error_bad_argument);

   }

   auto iFind = this->find_first(p);

   if (iFind < 0)
   {

      this->insert_at(i, p);

      return true;

   }

   if (iFind < i)
   {

      this->erase_at(iFind);

      this->insert_at(i - 1, p);

   }
   else if(iFind > i)
   {

      this->erase_at(iFind);

      this->insert_at(i, p);

   }

   return false;

}




template < class T >
template < typename OBJECT >
::raw::count pointer_array < T > ::set_size_create(OBJECT * pparticle, ::raw::count nNewSize, ::raw::count nGrowBy)
{

   ::raw::index i = this->get_size();

   BASE_ARRAY::set_size(nNewSize);

   ::raw::count c = this->get_size();

   for (; i < c; i++)
   {

      pparticle->__construct(this->element_at(i));

   }

   return c;

}



