#pragma once


#include "array_base_quantum.h"
#include "acme/prototype/prototype/particle.h"


template < class TYPE, class ARG_TYPE, class TYPED, class MEMORY, ::enum_type t_etypeContainer >
class array_base :
   virtual public ::particle,
   public array_base_quantum < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >
{
public:


   using BASE_ARRAY = array_base_quantum < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >;


   //array_base() : array_base_quantum< TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >() {}
   //template < typename ...Args >
   //array_base(Args&&... args) : 
   //   array_base_quantum< TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >(::std::forward < Args >(args)...)
   //{
   //}

   array_base() {}
   array_base(std::initializer_list < TYPE > initializer_list) :BASE_ARRAY(initializer_list) {}
   array_base(const BASE_ARRAY & a) :BASE_ARRAY(a) {}
   array_base(BASE_ARRAY && a) noexcept :BASE_ARRAY(a) {}
   array_base(const TYPE * p, ::collection::count c) :BASE_ARRAY(p, c) {}
   array_base(::range < typename BASE_ARRAY::const_iterator > constrange) :
      BASE_ARRAY(constrange.begin(), constrange.end()) {}
   template < primitive_integral INTEGRAL >
   array_base(typename BASE_ARRAY::const_iterator begin, INTEGRAL count) :
      BASE_ARRAY(begin, begin + count) {}
   array_base(typename BASE_ARRAY::const_iterator begin, typename BASE_ARRAY::const_iterator end)
   {
      auto p = this->begin();
      while (p != end) add(*p);
   }


   void destroy()
   {

      particle::destroy();

      BASE_ARRAY::destroy();

   }


};



