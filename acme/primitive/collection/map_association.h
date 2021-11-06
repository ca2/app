#pragma once


template <  typename PAYLOAD >
class map_association :
   public PAYLOAD
{
public:


   typedef PAYLOAD                     payload;


   map_association *                   m_pprev;
   map_association *                   m_pnext;
   map_association *                   m_pnextHash;
   map_association **                  m_ppprevHash;


   using PAYLOAD::PAYLOAD;

   //map_association()
   //{

   //}


   //map_association(ARG_TYPE1 element1) :
   //   pair(element1)
   //{

   //}


   //map_association(ARG_TYPE1 element1, ARG_TYPE2 element2):
   //   pair(element1, element2)
   //{

   //}


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
