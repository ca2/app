#pragma once




template < class TYPE, class ARG_TYPE = const TYPE &, typename ALLOCATOR = ::allocator::nodef < TYPE >, enum_type t_etypePayload = e_type_element >
using comparable_eq_raw_array = comparable_eq_array < TYPE, ARG_TYPE, raw_array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > >;

template < class TYPE, class ARG_TYPE = const TYPE &, typename ALLOCATOR = ::allocator::nodef < TYPE >, enum_type t_etypePayload = e_type_element >
using comparable_raw_array = comparable_array < TYPE, ARG_TYPE, comparable_eq_raw_array < TYPE, ARG_TYPE, ALLOCATOR, t_etypePayload > >;

