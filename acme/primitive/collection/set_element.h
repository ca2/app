#pragma once


template <  typename ELEMENT >
class set_element_item
{
public:


   ELEMENT                                m_element;
   set_element_item *                     m_pprev;
   set_element_item *                     m_pnext;
   set_element_item *                     m_pnextHash;
   set_element_item **                    m_ppprevHash;


   set_element_item()
   {

   }


   set_element_item(const ELEMENT & element) :
      m_element(element)
   {

   }


   ELEMENT & element() { return m_element; }
   const ELEMENT & element() const { return m_element; }


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


template <  typename ELEMENT >
inline typename ELEMENT::TYPE2& __value(const set_element_item<ELEMENT>& pair)
{

   return (typename ELEMENT::TYPE2 &) pair.element2();

}



//template <  typename TYPE >
//inline __pointer(TYPE) & __value(const __pointer(TYPE) & p)
//{
//
//   return (__pointer(TYPE) &) p;
//
//}


namespace std
{


   template < typename ELEMENT >
   ALIENATED_ANDROID_ANARCHY tuple_size< ::set_element_item < ELEMENT > > : integral_constant<size_t, 2> {};

   template < typename ELEMENT >
   ALIENATED_ANDROID_ANARCHY tuple_element< 0, set_element_item < ELEMENT > >
   {
      using type = typename ::set_element_item < ELEMENT >::TYPE1;
   };

   template < typename ELEMENT >
   ALIENATED_ANDROID_ANARCHY tuple_element< 1, set_element_item < ELEMENT > >
   {
      using type = typename ::set_element_item < ELEMENT >::TYPE2;
   };


} // namespace std
