#pragma once




template < class TYPE, class ARG_TYPE = const TYPE &, class TYPED = ::typed::def < TYPE  >, class MEMORY = ::heap::typed_memory < TYPE, ::heap::e_memory_array >, ::enum_type t_etypeContainer = e_type_element >
using comparable_eq_raw_array = comparable_eq_array < TYPE, ARG_TYPE, raw_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > >;

template < class TYPE, class ARG_TYPE = const TYPE &, class TYPED = ::typed::def < TYPE  >, class MEMORY = ::heap::typed_memory < TYPE, ::heap::e_memory_array >, ::enum_type t_etypeContainer = e_type_element >
using comparable_raw_array = comparable_array < TYPE, ARG_TYPE, comparable_eq_raw_array < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > >;

