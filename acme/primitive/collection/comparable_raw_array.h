#pragma once




template < class TYPE, class ARG_TYPE = const TYPE & >
using comparable_eq_raw_array = comparable_eq_array < TYPE, ARG_TYPE, raw_array < TYPE, ARG_TYPE > >;

template < class TYPE, class ARG_TYPE = const TYPE & >
using comparable_raw_array = comparable_array < TYPE, ARG_TYPE, comparable_eq_raw_array < TYPE, ARG_TYPE > >;

