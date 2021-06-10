#pragma once



template < class TYPE,class ARG_TYPE = TYPE const &,class ARRAY_TYPE = comparable_eq_array < TYPE,ARG_TYPE > >
class comparable_array :
   public ARRAY_TYPE
{
public:


   typedef ARRAY_TYPE BASE_ARRAY;

   using BASE_ARRAY::operator &=;
   using BASE_ARRAY::operator -=;
   using BASE_ARRAY::operator |=;
   using BASE_ARRAY::operator -;
   //using BASE_ARRAY::operator ==;
   //using BASE_ARRAY::operator !=;

   using BASE_ARRAY::operator +=;

   comparable_array() { }
   explicit comparable_array(::matter * pobject) : BASE_ARRAY(pobject) { }
   comparable_array(::std::initializer_list < TYPE > l) : BASE_ARRAY(l) {   }
   comparable_array(const comparable_array & array) : BASE_ARRAY(array) {}
   comparable_array(comparable_array && array) : BASE_ARRAY(::move(array)) {}

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



template < class TYPE,class ARG_TYPE = TYPE const &,class ARRAY_TYPE = comparable_array < TYPE,ARG_TYPE > >
class full_comparable_array:
   virtual public ARRAY_TYPE
{
public:
   full_comparable_array();
   full_comparable_array(const full_comparable_array & array);


};



template < class TYPE,class ARG_TYPE,class ARRAY_TYPE >
full_comparable_array<  TYPE,ARG_TYPE,ARRAY_TYPE >::
full_comparable_array()
{
}
template < class TYPE,class ARG_TYPE,class ARRAY_TYPE >
full_comparable_array<  TYPE,ARG_TYPE,ARRAY_TYPE >::
full_comparable_array(const full_comparable_array<  TYPE,ARG_TYPE,ARRAY_TYPE > & a):
   ARRAY_TYPE(a)
{
   this->operator = (a);
}


