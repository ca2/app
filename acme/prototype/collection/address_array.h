#pragma once


#include "acme/prototype/collection/raw_array.h"
#include "acme/prototype/collection/comparable_eq_array.h"
#include "acme/prototype/collection/comparable_array.h"


template < typename POINTER, class ARRAY_TYPE >
class address_array_base :
   public ARRAY_TYPE
{
public:


   inline address_array_base() {}
   inline address_array_base(const address_array_base & a) { this->operator = (a); }
   inline address_array_base(address_array_base && a) { this->operator = (::transfer(a)); }


   inline address_array_base & operator = (const address_array_base & a) { this->ARRAY_TYPE::operator = (a); return *this; }
   inline address_array_base & operator = (address_array_base && a) { this->ARRAY_TYPE::operator = (::transfer(a)); return *this; }


   ::collection::index add(POINTER newElement) { return ARRAY_TYPE::add(newElement); }
   ::collection::index append(const address_array_base & src) { return ARRAY_TYPE::append(src); }


   inline POINTER & element_at(::collection::index i) { return (POINTER &)ARRAY_TYPE::element_at(i); }
   inline POINTER element_at(::collection::index i) const { return (POINTER)ARRAY_TYPE::element_at(i); }

   
   inline POINTER & element_at_grow(::collection::index i) { return (POINTER &)ARRAY_TYPE::element_at_grow(i); }


   inline POINTER & first(::collection::index i = 0) { return (POINTER &)ARRAY_TYPE::first(i); }
   inline POINTER first(::collection::index i = 0) const { return (POINTER)ARRAY_TYPE::first(i); }

   
   inline POINTER & last(::collection::index i = -1) { return (POINTER &)ARRAY_TYPE::last(i); }
   inline POINTER last(::collection::index i = 0) const { return (POINTER)ARRAY_TYPE::last(i); }

   
   inline POINTER* get_data() { return (POINTER*)ARRAY_TYPE::get_data(); }
   inline POINTER* get_data() const { return (POINTER*)ARRAY_TYPE::get_data(); }

   
};



//class CLASS_DECL_ACME object_ptra :
//   virtual public ::address_array_base < matter * >
//{
//public:
//
//   typedef ::address_array_base < matter * > BASE_TYPE;
//
//   inline object_ptra() {}
//   inline object_ptra(::particle * pparticle) : ::matter(pparticle) { }
//   inline object_ptra(const object_ptra & a) : ::matter(a), BASE_TYPE(a) { }
//   inline object_ptra(const BASE_TYPE & a) : ::matter((const ::matter & )a), BASE_TYPE(a) { }
//   inline object_ptra(object_ptra && a): ::matter(a), BASE_TYPE(::transfer(a)) { }
//
//   inline object_ptra & operator = (const object_ptra & a) { this->BASE_TYPE::operator = (a); return *this; }
//   inline object_ptra & operator = (const BASE_TYPE & a) { this->BASE_TYPE::operator = (a); return *this; }
//   inline object_ptra & operator = (object_ptra && a) { this->BASE_TYPE::operator = (::transfer(a)); return *this; }
//
//
//};









