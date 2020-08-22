#pragma once


template < typename TYPE >
inline TYPE & xxf_zerop(TYPE * p) { ::zero(p, sizeof(TYPE)); return *p; }

template < typename TYPE >
inline TYPE & xxf_zero(TYPE & t) { ::zero(&t, sizeof(TYPE)); return t; }

template < typename TYPE >
inline bool xxf_is_zerop(TYPE * p) { return ::is_zero(p, sizeof(TYPE)); }

template < typename TYPE >
inline bool xxf_is_zero(TYPE & t) { return ::is_zero(&t, sizeof(TYPE)); }

template < typename TYPE >
inline void __copy(TYPE * p, const TYPE * pSrc) { ::copy(p, pSrc); }

template < typename TYPE >
inline void __copy(TYPE & t, const TYPE & tSrc) { ::copy(&t, &tSrc); }

template < typename TYPE >
inline void __copy(TYPE * p, const TYPE & tSrc) { ::copy(p, &tSrc); }

template < typename TYPE >
inline void __copy(TYPE & t, const TYPE * pSrc) { ::copy(&t, pSrc); }



