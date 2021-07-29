#pragma once




template < class TYPE, class ARG_TYPE = const TYPE &, enum_type t_etypePayload = e_type_element >
using comparable_eq_raw_array = comparable_eq_array < TYPE, ARG_TYPE, raw_array < TYPE, ARG_TYPE, t_etypePayload > >;

template < class TYPE, class ARG_TYPE = const TYPE &, enum_type etypePayload = e_type_element >
using comparable_raw_array = comparable_array < TYPE, ARG_TYPE, comparable_eq_raw_array < TYPE, ARG_TYPE, t_etypePayload > >;

