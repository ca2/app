#pragma once


template<class TYPE>
struct add_const
{
   typedef const TYPE type;
};


template<class TYPE>
struct add_volatile
{
   typedef volatile TYPE type;
};

template<class TYPE>
struct add_cv
{
   typedef const volatile TYPE type;
};


template<class TYPE>
struct add_reference
{
   typedef TYPE& type;
};

template<class TYPE>
struct add_lvalue_reference
{
   typedef typename add_reference<TYPE>::type type;
};


template<class TYPE>
struct add_rvalue_reference
{
   // add rvalue matter
   typedef TYPE&& type;
};



// CLASS _Unrefwrap
template<class TYPE>
class reference_wrapper;




template < typename TYPE >
void __swap(TYPE & t1,TYPE & t2)
{

   TYPE t = t1;

   t1 = t2;

   t2 = t;

}
//
//
//template<class... TYPES>
//class tuple;
//
//template<>
//class tuple<>
//{
//public:
//   typedef tuple<> TUPLE_TYPE;
//
//   tuple()
//   {
//   }
//
//   tuple(const tuple&) noexcept
//   {
//   }
//
//   void swap(TUPLE_TYPE&) noexcept
//   {
//   }
//
//   bool equals(const TUPLE_TYPE&) noexcept
//   {
//      return true;
//   }
//
//   bool less(const TUPLE_TYPE&)noexcept
//   {
//      return false;
//   }
//
//
//
//   template< class... TYPES2>
//   inline bool operator==(const tuple<TYPES2...>& right)
//   {
//      return equals(right);
//   }
//
//   template< class... TYPES2>
//   inline bool operator!=( const tuple<TYPES2...>& right)
//   {
//      return !(*this == right);
//   }
//
//   template< class... TYPES2>
//   inline bool operator<( const tuple<TYPES2...>& right)
//   {
//      return less(right);
//   }
//
//   template< class... TYPES2>
//   inline bool operator>=( const tuple<TYPES2...>& right)
//   {
//      return !(less(right));
//   }
//
//   template< class... TYPES2>
//   inline bool operator>( const tuple<TYPES2...>& right)
//   {
//      return right.less(*this);
//   }
//
//   template< class... TYPES2>
//   inline bool operator<=(const tuple<TYPES2...>& right)
//   {
//      return !(right.less(*this));
//   }
//
//};
//
//
//
//template<class TYPE,
//         class... REST>
//class tuple<TYPE,REST...>
//   : public tuple<REST...>
//{
//public:
//   typedef TYPE THIS_TYPE;
//   typedef tuple<TYPE,REST...> TUPLE_TYPE;
//   typedef tuple<REST...> BASE_TYPE;
//   static const size_t TYPE_SIZE = 1 + sizeof...(REST);
//
//   TYPE     m_val;
//
//
//   tuple()
//   {
//   }
//
//   template < class... OTHER >
//   tuple(const tuple<OTHER...>& right)
//      : BASE_TYPE(right.get_rest()),m_val(right.m_val)
//   {
//   }
//
//   template < class... OTHER >
//   tuple(tuple<OTHER...>&& right)
//      : BASE_TYPE(::transfer(right.get_rest())),m_val(::transfer(right.m_val))
//   {
//   }
//
//   explicit tuple(const TYPE& val,const REST&... rest)
//      : BASE_TYPE(rest...),
//        m_val(val)
//   {
//   }
//
//   explicit tuple(TYPE && val,const REST &&... rest)
//      : BASE_TYPE(::transfer(rest...)),m_val(::transfer(val))
//   {
//   }
//
//
//   template<class... OTHER>
//   TUPLE_TYPE& operator=(const tuple<OTHER...>& right)
//   {
//      m_val = right.m_val;
//      (BASE_TYPE&)*this = right.get_rest();
//      return (*this);
//   }
//
//   template<class... OTHER>
//   TUPLE_TYPE& operator=(tuple<OTHER...>&& right)
//   {
//      m_val = ::transfer(right.m_val);
//      BASE_TYPE::operator = (::transfer(right.get_rest()));
//      return *this;
//   }
//
//   template<class... OTHER>
//   bool equals(const tuple<OTHER...>& right) const
//   {
//      return m_val == right.m_val && BASE_TYPE::equals(right.get_rest());
//   }
//
//   template<class... OTHER>
//   bool less(const tuple<OTHER...>& right) const
//   {
//      return m_val < right.m_val || (!(right.m_val < m_val) && BASE_TYPE::less(right.get_rest()));
//   }
//
//   template < class TYPE1, class TYPE2>
//   tuple(const pair < TYPE1, TYPE2 > & right) :
//      BASE_TYPE( tuple < TYPE2 > ( right.element2() ) ),
//      m_val(right.element1())
//   {
//
//   }
//
//
//   TUPLE_TYPE & operator=(const TUPLE_TYPE & right)
//   {
//
//      m_val = right.m_val;
//
//      BASE_TYPE::operator =(right.get_rest());
//
//      return *this;
//
//   }
//
//
//   template < class TYPE1, class TYPE2>
//   TUPLE_TYPE & operator=(const pair < TYPE1, TYPE2 >& right)
//   {
//
//      m_val = right.first;
//
//      BASE_TYPE::operator =(tuple<TYPE2>(right.element2()));
//
//      return *this;
//
//   }
//
//
//   template < class TYPE1, class TYPE2 >
//   tuple(pair < TYPE1, TYPE2 > && right) :
//      BASE_TYPE(tuple<TYPE2>(::transfer(right.second))),
//      m_val(::transfer(right.first))
//   {
//
//   }
//
//
//   TUPLE_TYPE & operator=(TUPLE_TYPE&& right)
//   {
//
//      m_val = ::transfer(right.m_val);
//
//      BASE_TYPE::operator = (::transfer(right.get_rest()));
//
//      return (*this);
//
//   }
//
//
//   template < class TYPE1, class TYPE2>
//   TUPLE_TYPE& operator=(pair<TYPE1,TYPE2>&& right)
//   {
//
//      m_val = ::transfer(right.element1());
//
//      BASE_TYPE::operator = (tuple<TYPE2>(::transfer(right.second)));
//
//      return *this;
//
//   }
//
//
//   BASE_TYPE & get_rest()
//   {
//
//      return *this;
//
//   }
//
//   const BASE_TYPE & get_rest() const
//   {
//
//      return *this;
//
//   }
//
//
//   void swap(tuple& right)
//   {
//
//      swap(m_val,right.m_val);
//
//      BASE_TYPE::swap((BASE_TYPE&)right);
//
//   }
//
//};
//
//template<class... TYPES>
//inline void swap(tuple<TYPES...>& left, tuple<TYPES...>& right)
//{
//   return left.swap(right);
//}
//
//
//template<size_t m_iIndex, class TUPLE>
//struct tuple_element;
//
//template<class TYPE1, class... REST1>
//struct tuple_element<0,tuple<TYPE1,REST1...> >
//{
//   typedef TYPE1 type;
//   typedef typename add_lvalue_reference<const TYPE1>::type _Ctype;
//   typedef typename add_lvalue_reference<TYPE1>::type _Rtype;
//   //typedef typename add_rvalue_reference<TYPE1>::type _RRtype;
//   typedef tuple<TYPE1,REST1...> TUPLE_TYPE;
//};
//
//template<size_t m_iIndex, class TYPE1, class... REST1>
//struct tuple_element<m_iIndex,tuple<TYPE1,REST1...> >
//   : public tuple_element<m_iIndex - 1,tuple<REST1...> >
//{
//};
//
//
//template<size_t m_iIndex, class TUPLE>
//struct tuple_element<m_iIndex,const TUPLE>
//      : public tuple_element<m_iIndex,TUPLE>
//{
//   typedef tuple_element<m_iIndex,TUPLE> BASE_TYPE;
//   typedef typename add_const<typename BASE_TYPE::type>::type type;
//};
//
//template<size_t m_iIndex, class TUPLE>
//struct tuple_element<m_iIndex,volatile TUPLE>
//      : public tuple_element<m_iIndex,TUPLE>
//{
//   typedef tuple_element<m_iIndex,TUPLE> BASE_TYPE;
//   typedef typename add_volatile<typename BASE_TYPE::type>::type type;
//};
//
//template<size_t m_iIndex,
//         class TUPLE>
//struct tuple_element<m_iIndex,const volatile TUPLE>
//      : public tuple_element<m_iIndex,TUPLE>
//{
//   typedef tuple_element<m_iIndex,TUPLE> BASE_TYPE;
//   typedef typename add_cv<typename BASE_TYPE::type>::type type;
//};
//
//
//template<size_t m_iIndex, class... TYPES>
//inline typename tuple_element<m_iIndex,tuple<TYPES...> >::_Rtype  get(tuple<TYPES...>& TUPLE)
//{
//   typedef typename tuple_element<m_iIndex,tuple<TYPES...> >::TUPLE_TYPE     TUPLE_TYPE;
//   return (((TUPLE_TYPE&)TUPLE).m_val);
//}
//
//template<size_t m_iIndex, class... TYPES>
//inline typename tuple_element<m_iIndex,tuple<TYPES...> >::_Ctype get(const tuple<TYPES...>& TUPLE)
//{
//   typedef typename tuple_element<m_iIndex,tuple<TYPES...> >::TUPLE_TYPE TUPLE_TYPE;
//   return (((TUPLE_TYPE&)TUPLE).m_val);
//}
//
//
//template<size_t m_iIndex, class... TYPES>
//inline  typename tuple_element<m_iIndex,tuple<TYPES...> >::_RRtype  get(tuple<TYPES...>&& TUPLE)
//{
//
//   typedef typename tuple_element<m_iIndex,tuple<TYPES...> >::TUPLE_TYPE TUPLE_TYPE;
//   //typedef typename tuple_element<m_iIndex,tuple<TYPES...> >::_RRtype  _RRtype;
//   return (::transfer(((TUPLE_TYPE&)TUPLE).m_val));
//
//}
//
//
//template<class... TYPES> inline
//tuple < TYPES&&... > make_tuple(TYPES&&... args)
//{
//
//   return ::transfer(args...);
//
//}
//
//
//template<class... TYPES> inline
//tuple<TYPES&...>
//tie(TYPES&... args) noexcept
//{
//
//   typedef tuple<TYPES&...> TUPLE_TYPE;
//
//   return (TUPLE_TYPE(args...));
//
//}












template < typename TYPE1, typename TYPE2 >
inline int cmp(const TYPE1 & t1,const TYPE2 & t2)
{
   return (t1 < t2) ? -1 : (t1 < t2) ? 1 : 0;
}


template < typename TYPE1,typename TYPE2 >
inline int icmp(const TYPE1 & t1,const TYPE2 & t2)
{
   return cmp(t1, t2);
}

template < >
inline int cmp(const ::string & str1, const ::string & str2)
{
   return str1.compare(str2);
}


template < >
inline int icmp(const ::string & str1,const ::string & str2)
{
   return str1.case_insensitive_order(str2);
}

template<size_t TUPLE_SIZE> struct cmp_tuple
{
   template < typename T1, typename T2>
   int operator()(const T1 & t1,const T2 & t2) const
   {
      int r = cmp_tuple<TUPLE_SIZE - 1>()(t1,t2);
      return (r != 0) ? r : cmp(get<TUPLE_SIZE - 1>(t1),get<TUPLE_SIZE - 1>(t2));
   }
};


template<size_t TUPLE_SIZE> struct icmp_tuple
{
   template < typename T1,typename T2>
   int operator()(const T1 & t1,const T2 & t2) const
   {
      int r = icmp_tuple<TUPLE_SIZE - 1>()(t1,t2);
      return (r != 0) ? r : icmp(get<TUPLE_SIZE - 1>(t1),get<TUPLE_SIZE - 1>(t2));
   }
};

template<> struct cmp_tuple<0>
{
   template < typename T1,typename T2>
   int operator()(const T1&,const T2&) const
   {
      return 0;
   }
};

template<> struct icmp_tuple<0>
{
   template < typename T1,typename T2>
   int operator()(const T1&,const T2&) const
   {
      return 0;
   }
};






template <  >
inline int cmp(const int & i1,const int & i2)
{
   return i1 - i2;
}


template <  >
inline  int cmp(const short & sh1,const short & sh2)
{
   return sh1 - sh2;
}


template <  >
inline int cmp(const char & ch1,const char & ch2)
{
   return ch1 - ch2;
}

template <  >
inline int cmp(const unsigned int & i1,const unsigned int & i2)
{
   return i1 - i2;
}

template <  >
inline  int cmp(const unsigned short & sh1,const short & sh2)
{
   return sh1 - sh2;
}


template <  >
inline  int cmp(const unsigned char & ch1,const unsigned char & ch2)
{
   return ch1 - ch2;
}


template <  >
inline  int cmp(const double & d1,const double & d2)
{
   return ::acme::sgn(d1 - d2);
}


template <  >
inline  int cmp(const float & f1,const float & f2)
{
   return ::acme::sgn(f1 - f2);
}



template < >
inline int cmp(const int & t1,const unsigned int & t2)
{
   return (t1 < 0) ? -1 : ((unsigned int) t1 < t2) ? 1 : 0;
}
