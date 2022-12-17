#pragma once


template < class TYPE, class ARG_TYPE, class ARRAY_TYPE >
class comparable_array :
   public comparable_range < ARRAY_TYPE >
{
public:


   using BASE_ARRAY = comparable_range < ARRAY_TYPE >;

   using CONST_RAW_RANGE = typename BASE_ARRAY::CONST_RAW_RANGE;

   using BASE_ARRAY::operator &=;
   using BASE_ARRAY::operator -=;
   using BASE_ARRAY::operator |=;
   using BASE_ARRAY::operator -;
   //using BASE_ARRAY::operator ==;
   //using BASE_ARRAY::operator !=;

   using BASE_ARRAY::operator +=;

   using comparable_range < ARRAY_TYPE >::comparable_range;

   using iterator = typename BASE_ARRAY::iterator;
   using const_iterator = typename BASE_ARRAY::const_iterator;

   comparable_array() { }
   comparable_array(::std::initializer_list < TYPE > initializer_list) { this->add_initializer_list(initializer_list); }
   comparable_array(const comparable_array & array) : comparable_range < ARRAY_TYPE >(array) {}
   comparable_array(comparable_array && array) : comparable_range < ARRAY_TYPE >(::move(array)) {}
   template < primitive_integral INTEGRAL >
   comparable_array(const_iterator begin, INTEGRAL count) : BASE_ARRAY(begin, count) {}
   comparable_array(const_iterator begin, const_iterator end) : BASE_ARRAY(begin, end) {}
   comparable_array(const_iterator begin) : BASE_ARRAY(begin, span_zero_item(begin)) {}


   using ARRAY_TYPE::operator =;

   comparable_array & operator = (const comparable_array & array)
   {
      BASE_ARRAY::operator = (array);
      return *this;
   }


   comparable_array & operator = (comparable_array && array)
   {

      BASE_ARRAY::operator = (::move(array));

      return *this;

   }




};



//template < class TYPE,class ARG_TYPE,class ARRAY_TYPE >
//full_comparable_array<  TYPE,ARG_TYPE,ARRAY_TYPE >::
//full_comparable_array()
//{
//}
//template < class TYPE,class ARG_TYPE,class ARRAY_TYPE >
//full_comparable_array<  TYPE,ARG_TYPE,ARRAY_TYPE >::
//full_comparable_array(const full_comparable_array<  TYPE,ARG_TYPE,ARRAY_TYPE > & a):
//   ARRAY_TYPE(a)
//{
//   this->operator = (a);
//}
//
//
