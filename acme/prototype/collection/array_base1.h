#pragma once


#include "base_array_quantum.h"
#include "acme/prototype/prototype/particle.h"

//
// template < class TYPE, class ARG_TYPE, class TYPED, class MEMORY, ::enum_type t_etypeContainer >
// class base_array :
//    virtual public ::particle,
//    public base_array_quantum < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >
// {
// public:
//
//
//    using BASE_ARRAY = base_array_quantum < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >;
//
//
//    //base_array() : base_array_quantum< TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >() {}
//    //template < typename ...Args >
//    //base_array(Args&&... args) :
//    //   base_array_quantum< TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer >(::std::forward < Args >(args)...)
//    //{
//    //}
//
//    base_array() {}
//    base_array(std::initializer_list < TYPE > initializer_list) :BASE_ARRAY(initializer_list) {}
//    base_array(const BASE_ARRAY & a) :BASE_ARRAY(a) {}
//    base_array(BASE_ARRAY && a) noexcept :BASE_ARRAY(a) {}
//    base_array(const TYPE * p, ::collection::count c) :BASE_ARRAY(p, c) {}
//    base_array(::range < typename BASE_ARRAY::const_iterator > constrange) :
//       BASE_ARRAY(constrange.begin(), constrange.end()) {}
//    template < primitive_integral INTEGRAL >
//    base_array(typename BASE_ARRAY::const_iterator begin, INTEGRAL count) :
//       BASE_ARRAY(begin, begin + count) {}
//    base_array(typename BASE_ARRAY::const_iterator begin, typename BASE_ARRAY::const_iterator end)
//    {
//       auto p = this->begin();
//       while (p != end) add(*p);
//    }
//
//
//    void destroy()
//    {
//
//       particle::destroy();
//
//       BASE_ARRAY::destroy();
//
//    }
//
//
// };
//


