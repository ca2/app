// Created by Camilo on 2021-01-12 ~10:00 <3TBS
#pragma once


// namespace str
// {


template < typename POINTER >
inline ::string __string(const ::acme::memory_allocate < POINTER > & memoryallocpointer)
{

   to_string(str, memoryallocpointer.m_p);

}


// } // namespace str


template < typename TYPE, std::size_t SIZE >
inline array_reference < TYPE, SIZE > & __zero(TYPE (& array)[ SIZE ] ) { ::zero((void *) array, sizeof(array)); return array; }

template < a_pointer POINTER >
inline typename std::remove_pointer<POINTER>::type & __zero(POINTER p) { ::zero((void *) p, sizeof(*p)); return *p; }

template < non_pointer NON_POINTER >
inline NON_POINTER & __zero(NON_POINTER & t) { ::zero((void *) &t, sizeof(t)); return t; }

template < typename TYPE, std::size_t SIZE >
inline bool __is_zero(array_reference < TYPE, SIZE > & array) { return ::is_zero((const void *) array, sizeof(array)); }

template < a_pointer POINTER >
inline bool __is_zero(const POINTER p) { return ::is_zero((const void *) p, sizeof(*p)); }

template < non_pointer NON_POINTER >
inline bool __is_zero(const NON_POINTER & t) { return ::is_zero((const void *) &t, sizeof(t)); }



