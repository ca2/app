#pragma once


template <  typename PAIR >
class map_association :
   public PAIR
{
public:


   typedef PAIR                        pair;
   typedef typename PAIR::TYPE1        TYPE1;
   typedef typename PAIR::ARG_TYPE1    ARG_TYPE1;
   typedef typename PAIR::TYPE2        TYPE2;
   typedef typename PAIR::ARG_TYPE2    ARG_TYPE2;


   map_association *                   m_pprev;
   map_association *                   m_pnext;
   map_association *                   m_pnextHash;
   map_association **                  m_ppprevHash;


   map_association()
   {

   }


   map_association(ARG_TYPE1 element1) :
      pair(element1)
   {

   }


   map_association(ARG_TYPE1 element1, ARG_TYPE2 element2):
      pair(element1, element2)
   {

   }

#ifdef CPP17
   template<std::size_t N>
   auto & get() const
   {
      if constexpr (N == 0) return this->element1();
      else if constexpr (N == 1) return this->element2();
   }

   template<std::size_t N>
   auto& get()
   {
      if constexpr (N == 0) return this->element1();
      else if constexpr (N == 1) return this->element2();
   }
#endif

};


template <  typename PAIR >
inline typename PAIR::TYPE2& __value(const map_association<PAIR>& pair)
{

   return (typename PAIR::TYPE2 &) pair.element2();

}



template <  typename TYPE >
inline __pointer(TYPE) & __value(const __pointer(TYPE) & p)
{

   return (__pointer(TYPE) &) p;

}


namespace std
{


   template < typename PAIR >
   ALIENATED_ANDROID_ANARCHY tuple_size< ::map_association < PAIR > > : integral_constant<size_t, 2> {};

   template < typename PAIR >
   ALIENATED_ANDROID_ANARCHY tuple_element< 0, map_association < PAIR > >
   {
      using type = typename ::map_association < PAIR >::TYPE1;
   };

   template < typename PAIR >
   ALIENATED_ANDROID_ANARCHY tuple_element< 1, map_association < PAIR > >
   {
      using type = typename ::map_association < PAIR >::TYPE2;
   };


} // namespace std
