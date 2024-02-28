// Created by Camilo on 2021-01-12 ~10:00 <3TBS
#pragma once


template < typename TYPE, std::size_t SIZE >
inline array_reference < TYPE, SIZE > & zero(TYPE (& array)[ SIZE ] ) { ::zero((void *) array, sizeof(array)); return array; }


template < typename TYPE, std::size_t SIZE >
inline bool __is_zero(array_reference < TYPE, SIZE > & array) { return ::is_zero((const void *) array, sizeof(array)); }


template < typename TYPE >
inline TYPE& zero(TYPE& type) { ::zero(&type, sizeof(type)); return type; }



