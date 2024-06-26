#pragma once


template < class TYPE, class ARG_TYPE, class ARRAY_TYPE >
class comparable_array :
   public ARRAY_TYPE
   //public comparable_range < ARRAY_TYPE >
{
public:


   //using BASE_ARRAY = comparable_range < ARRAY_TYPE >;

   using BASE_ARRAY = ARRAY_TYPE;

   using BASE_RANGE = ARRAY_TYPE;
   
   using RAW_RANGE = typename ARRAY_TYPE::RAW_RANGE;

   using CONST_RAW_RANGE = typename BASE_ARRAY::CONST_RAW_RANGE;

   //using BASE_ARRAY::operator &=;
   //using BASE_ARRAY::operator -=;
   //using BASE_ARRAY::operator |=;
   //using BASE_ARRAY::operator -;
   //using BASE_ARRAY::operator ==;
   //using BASE_ARRAY::operator !=;

   using BASE_ARRAY::operator +=;

   //using comparable_range < ARRAY_TYPE >::comparable_range;

   using ARRAY_TYPE::ARRAY_TYPE;

   using iterator = typename BASE_ARRAY::iterator;
   using const_iterator = typename BASE_ARRAY::const_iterator;

   comparable_array() { }
   comparable_array(::std::initializer_list < TYPE > initializer_list) { this->add_initializer_list(initializer_list); }
   comparable_array(const comparable_array & array) : BASE_ARRAY(array) {}
   comparable_array(comparable_array && array) : BASE_ARRAY(::transfer(array)) {}
   template < primitive_integral INTEGRAL >
   comparable_array(const_iterator begin, INTEGRAL count) : BASE_ARRAY(begin, count) {}
   comparable_array(const_iterator begin, const_iterator end) : BASE_ARRAY(begin, end) {}
   comparable_array(const_iterator begin) : BASE_ARRAY(begin, find_first_null_character(begin)) {}


   using ARRAY_TYPE::operator =;

   comparable_array & operator = (const comparable_array & array)
   {
      BASE_ARRAY::operator = (array);
      return *this;
   }
   comparable_array & operator = (comparable_array && array)
   {
      BASE_ARRAY::operator = (::transfer(array));
      return *this;
   }



      using BASE_RANGE::_order;
   
      constexpr ::std::strong_ordering _order(const RAW_RANGE & range) const
      {
   
         return _order(range, ::comparison::comparison < TYPE >());
   
      }
   
   
      using BASE_RANGE::order;
   
      constexpr ::std::strong_ordering order(const RAW_RANGE & range) const
      {
   
         return BASE_RANGE::order(range, ::comparison::comparison < TYPE >());
   
      }
   
      constexpr ::std::strong_ordering operator<=>(const comparable_array & array) const
      {
   
         return this->order(array);
   
      }
   

//
//   comparable_array & operator = (comparable_array && array)
//   {
//
//      BASE_ARRAY::operator = (::transfer(array));
//
//      return *this;
//
//   }



      template < primitive_container CONTAINER >
      inline comparable_array & operator += (const CONTAINER & container)
      {

         if (&container == this)
         {

            auto aCopy(container);

            this->append_container(aCopy);

         }
         else
         {

            this->append_container(container);

         }

         return *this;

      }


      inline comparable_array & operator += (const TYPE & t)
      {

         this->add_item(t);

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
