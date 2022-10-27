#pragma once




template < class TYPE, class ARG_TYPE = const TYPE &, typename ALLOCATOR = ::allocator::nodef < TYPE >, ::enum_type m_etypeContainer = e_type_element >
using comparable_eq_raw_array = comparable_eq_array < TYPE, ARG_TYPE, raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > >;

template < class TYPE, class ARG_TYPE = const TYPE &, typename ALLOCATOR = ::allocator::nodef < TYPE >, ::enum_type m_etypeContainer = e_type_element >
using comparable_raw_array = comparable_array < TYPE, ARG_TYPE, comparable_eq_raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > >;

