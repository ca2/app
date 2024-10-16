#pragma once



//
//
//template < typename ARG_TYPE >
//class default_less :
//   public less_predicate_base < ARG_TYPE >
//{
//public:
//
//   virtual bool less(ARG_TYPE a1, ARG_TYPE a2);
//
//};
//
//template < typename ARG_TYPE >
//class sort_data :
//   virtual public ::matter
//{
//public:
//
//
//   bool                                            m_bSorted;
//   ::pointer<index_array>                         m_pindexa;
//   pointer< less_predicate_base < ARG_TYPE > >          m_pless;
//
//   sort_data()
//   {
//
//      m_bSorted = false;
//
//   }
//
//   template < typename ARRAY >
//   void sort(ARRAY * parray);
//
//   void mark_dirty() { m_bSorted = false; }
//
//};
//
//template < typename ARG_TYPE >
//class sort_map :
//   virtual public atom_map < pointer< sort_data < ARG_TYPE > > >
//{
//public:
//
//
//   inline void mark_dirty();
//
//
//};
//
//
//template < class TYPE, class ARG_TYPE = const TYPE &, class BASE_ARRAY_TYPE = array < TYPE,ARG_TYPE > >
//class sort_array :
//   virtual public matter
//{
//public:
//
//   typedef TYPE BASE_TYPE;
//   typedef ARG_TYPE BASE_ARG_TYPE;
//   typedef BASE_ARRAY_TYPE BASE_ARRAY;
//   using sort_data = ::sort_data < ARG_TYPE >;
//   using sort_map = ::sort_map < ARG_TYPE >;
//
//
//   sort_map                      m_map;
//   ::pointer<BASE_ARRAY_TYPE>   m_parray;
//   ::pointer<sort_data>         m_psortdata; // from last get_sort call
//
//
//   sort_array() { m_parray = __allocate BASE_ARRAY_TYPE(); }
//
//
//   sort_array(BASE_ARRAY_TYPE * parray) : m_parray(parray) { }
//
//   sort_array(const sort_array & a) :
//      m_map(a.m_map),
//      m_parray(a.m_parray)
//   {
//
//   }
//
//
//   template < typename PRED >
//   void add_sort(const ::atom & atom, PRED predLess)
//   {
//
//      auto& psortmap = m_map[atom];
//
//      __defer_construct_new(psortmap);
//
//      psortmap->m_pless = __allocate less_predicate < ARG_TYPE, PRED > (predLess);
//
//   }
//
//
//   index add(ARG_TYPE t)
//   {
//
//      auto iIndex = m_parray->add(t);
//
//      m_map.mark_dirty();
//
//      return iIndex;
//
//   }
//
//
//   template < typename ARRAY >
//   ::collection::count add_array(const ARRAY & a)
//   {
//
//      auto c = m_parray->add(a);
//
//      m_map.mark_dirty();
//
//      return c;
//
//   }
//
//
//   sort_data * get_sort(const ::atom & atom) const
//   {
//
//      auto ppair = m_map.plookup(atom);
//
//      if (!ppair) return nullptr;
//
//      ((sort_array*)this)->m_psortdata = ppair->m_element2;
//
//      return m_psortdata;
//
//   }
//
//
//   sort_data * get_sorted(const ::atom & atom) const
//   {
//
//      auto pdata = get_sort(atom);
//
//      // sort information is considered a const sorting property, i.e.,
//      // a mutable cache;
//      pdata->sort(((sort_array *) this)->m_parray.m_p);
//
//      return pdata;
//
//   }
//
//
//   bool find(ARG_TYPE t, ::collection::index & iIndex, const ::atom & atom) const;
//
//   bool contains(ARG_TYPE t, const ::atom & atom) const;
//
//   bool add_unique(ARG_TYPE t, const ::atom & atom);
//
//   void sort(const ::atom & atom);
//
//   void set_size(::collection::count ca);
//
//   ::collection::count get_count() const { return m_parray->get_count(); }
//
//   ::collection::index get_upper_bound() const { return m_parray->get_upper_bound(); }
//
//   ::collection::index get_size() const { return m_parray->get_size(); }
//
//   const TYPE & element_at (::collection::index i, const ::atom & atom) const;
//
//   TYPE & element_at (::collection::index i, const ::atom & atom);
//
//   const TYPE & operator [] (::collection::index i) const;
//
//   TYPE & operator [] (::collection::index i);
//
//   //bool operator == (const sort_array & a) const;
//
//   //bool operator != (const sort_array & a) const;
//
//   void copy(const BASE_ARRAY & src);
//
//
//   sort_array & operator = (const sort_array & a)
//   {
//
//      return copy(a);
//
//   }
//
//
//   sort_array & copy (const sort_array & a)
//   {
//
//      if (&a != this)
//      {
//
//         m_parray = a.m_parray;
//
//         ::acme::map::copy(m_map, a.m_map);
//
//      }
//
//      return *this;
//
//   }
//
//   virtual void on_after_read();
//
//};
//
//
//template < class TYPE, class ARG_TYPE, class BASE_ARRAY >
//bool sort_array < TYPE, ARG_TYPE, BASE_ARRAY >::
//find(ARG_TYPE t, ::collection::index & iIndex, const ::atom & atom) const
//{
//
//   if(m_parray->is_empty())
//   {
//
//      return false;
//
//   }
//
//   auto psort = get_sorted(atom);
//
//   return ::acme::array::binary_search(
//      *m_parray,
//      t,
//      iIndex,
//      psort->m_pless,
//      *psort->m_pindexa);
//
//}
//
//
//template < class TYPE, class ARG_TYPE, class BASE_ARRAY >
//bool sort_array < TYPE, ARG_TYPE, BASE_ARRAY >::
//contains(ARG_TYPE t, const ::atom & atom) const
//{
//
//   index iIndex = 0;
//
//   return find(t, iIndex, atom);
//
//}
//
//
//template < class TYPE, class ARG_TYPE, class BASE_ARRAY >
//bool sort_array < TYPE, ARG_TYPE, BASE_ARRAY >::
//add_unique(ARG_TYPE t, const ::atom & atom)
//{
//
//   if (contains(t, atom))
//   {
//
//      return false;
//
//   }
//
//   add(t);
//
//   return true;
//
//}
//
//
//template < class TYPE, class ARG_TYPE, class BASE_ARRAY >
//void sort_array < TYPE, ARG_TYPE, BASE_ARRAY >::
//sort(const ::atom & atom)
//{
//
//   ((const sort_array *)this)->get_sorted(atom);
//
//}
//
//
//template < class TYPE, class ARG_TYPE, class BASE_ARRAY >
//void sort_array < TYPE, ARG_TYPE, BASE_ARRAY >::
//set_size(::collection::count n)
//{
//
//   m_parray->set_size(n);
//
//   m_map.mark_dirty();
//
//}
//
//
//template < class TYPE, class ARG_TYPE, class BASE_ARRAY >
//TYPE & sort_array < TYPE, ARG_TYPE, BASE_ARRAY >::
//element_at(::collection::index i, const ::atom & atom)
//{
//
//   return m_parray->element_at(get_sort(atom)->m_pindexa->element_at(i));
//
//}
//
//
//template < class TYPE, class ARG_TYPE, class BASE_ARRAY >
//const TYPE & sort_array < TYPE, ARG_TYPE, BASE_ARRAY >::
//element_at(::collection::index i, const ::atom & atom) const
//{
//
//   return ((sort_array *) this)->element_at(i, atom);
//
//}
//
//
//template < class TYPE, class ARG_TYPE, class BASE_ARRAY >
//TYPE & sort_array < TYPE, ARG_TYPE, BASE_ARRAY >::
//operator [](::collection::index i)
//{
//
//   i = ::is_set(m_psortdata) && m_psortdata->m_bSorted ? m_psortdata->m_pindexa->element_at(i) : i;
//
//   return m_parray->element_at(i);
//
//}
//
//
//template < class TYPE, class ARG_TYPE, class BASE_ARRAY >
//const TYPE & sort_array < TYPE, ARG_TYPE, BASE_ARRAY >::
//operator [](::collection::index i) const
//{
//
//   return ((sort_array *) this)->operator [](i);
//
//}
//
////template < class TYPE, class ARG_TYPE, class BASE_ARRAY >
////bool sort_array < TYPE, ARG_TYPE, BASE_ARRAY >::
////operator == (const sort_array & a) const
////{
////
////   if(&a == this)
////      return true;
////
////   if(get_size() != a.get_size())
////      return false;
////
////   index_array & ia1 = ((sort_array *) this)->defer_update();
////
////   index_array & ia2 = ((sort_array *) &a)->defer_update();
////
////   for(::collection::index i = 0; i < get_size(); i++)
////   {
////      if(DEFAULT_COMPARE(((sort_array *) this)->BASE_ARRAY::element_at(ia1[i]), ((sort_array *) &a)->BASE_ARRAY::element_at(ia2[i])) != 0)
////         return false;
////   }
////
////   return true;
////
////}
//
////template < class TYPE, class ARG_TYPE, class BASE_ARRAY >
////bool sort_array < TYPE, ARG_TYPE, BASE_ARRAY >::
////operator != (const sort_array & a) const
////{
////
////   return !this->operator == (a);
////
////}
//
//template < class TYPE, class ARG_TYPE, class BASE_ARRAY >
//void sort_array < TYPE, ARG_TYPE, BASE_ARRAY >::on_after_read()
//{
//
//   m_map.mark_dirty();
//
//}
//
//
//// smart_pointer_sort_array
//#define spsa(T) sort_array < pointer < T >, const pointer < T > &, pointer_array < T > >
//
//
//using sort_int_ptr_array = sort_array < ::collection::index  > ;
//
//
//
//
//template < typename TYPE >
//using sort_pointer_array = sort_array < ::pointer<TYPE> const ::pointer<TYPE>, pointer_array < TYPE > >;
