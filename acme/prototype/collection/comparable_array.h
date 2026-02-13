#pragma once



template < class TYPE, class ARG_TYPE, class ARRAY_TYPE >
class comparable_array_base :
   public ARRAY_TYPE
   //public comparable_range < ARRAY_TYPE >
{
public:


   //using BASE_ARRAY = comparable_range < ARRAY_TYPE >;

   using BASE_ARRAY = ARRAY_TYPE;
   using RAW_BASE_ARRAY = typename BASE_ARRAY::RAW_BASE_ARRAY;

   using BASE_RANGE = typename BASE_ARRAY::BASE_RANGE;
   
   using BASE_RAW_RANGE = typename BASE_ARRAY::BASE_RAW_RANGE;

   using CONST_RAW_RANGE = typename BASE_ARRAY::CONST_RAW_RANGE;

   //using BASE_ARRAY::operator &=;
   //using BASE_ARRAY::operator -=;
   //using BASE_ARRAY::operator |=;
   //using BASE_ARRAY::operator -;
   //using BASE_ARRAY::operator ==;
   //using BASE_ARRAY::operator !=;

   //using comparable_range < ARRAY_TYPE >::comparable_range;

   using BASE_ARRAY::BASE_ARRAY;
   using BASE_ARRAY::operator =;
   using BASE_ARRAY::operator +=;
   using BASE_ARRAY::operator -=;

   comparable_array_base(const RAW_BASE_ARRAY& a) : BASE_ARRAY(a) { }
   using iterator = typename BASE_ARRAY::iterator;
   using const_iterator = typename BASE_ARRAY::const_iterator;

   using this_iterator = typename BASE_ARRAY::this_iterator;
   //using ARRAY_TYPE::ARRAY_TYPE;

   // comparable_array_base() { }
   // comparable_array_base(::std::initializer_list < TYPE > initializer_list) { this->add_initializer_list(initializer_list); }
   // comparable_array_base(const comparable_array_base & array) : BASE_ARRAY(array) {}
   // comparable_array_base(comparable_array_base && array) : BASE_ARRAY(::transfer(array)) {}
   // template < prototype_integral INTEGRAL >
   // comparable_array_base(const_iterator begin, INTEGRAL count) : BASE_ARRAY(begin, count) {}
   // comparable_array_base(const_iterator begin, const_iterator end) : BASE_ARRAY(begin, end) {}
   // comparable_array_base(const_iterator begin) : BASE_ARRAY(begin, find_first_null_character(begin)) {}


   // using ARRAY_TYPE::operator =;
   //
   // comparable_array_base & operator = (const comparable_array_base & array)
   // {
   //    BASE_ARRAY::operator = (array);
   //    return *this;
   // }
   // comparable_array_base & operator = (comparable_array_base && array)
   // {
   //    BASE_ARRAY::operator = (::transfer(array));
   //    return *this;
   // }
   //


      using BASE_RANGE::_order;
   
      constexpr auto _order(const BASE_RAW_RANGE & range) const
      {
   
         return _order(range, ::comparison::comparison < TYPE >());
   
      }
   
   
      using BASE_RANGE::order;
   
      constexpr auto order(const BASE_RAW_RANGE & range) const
      {
   
         return BASE_RANGE::order(range, ::comparison::comparison < TYPE >());
   
      }



   
      constexpr auto operator<=>(const comparable_array_base & array) const
      {
   
         return this->order(array);
   
      }
   

//
//   comparable_array_base & operator = (comparable_array_base && array)
//   {
//
//      BASE_ARRAY::operator = (::transfer(array));
//
//      return *this;
//
//   }



      // template < prototype_container CONTAINER >
      // inline comparable_array_base & operator += (const CONTAINER & container)
      // {
      //
      //    if (&container == this)
      //    {
      //
      //       auto aCopy(container);
      //
      //       this->append_container(aCopy);
      //
      //    }
      //    else
      //    {
      //
      //       this->append_container(container);
      //
      //    }
      //
      //    return *this;
      //
      // }


      // inline comparable_array_base & operator += (const TYPE & t)
      // {
      //
      //    this->add_item(t);
      //
      //    return *this;
      //
      // }

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
