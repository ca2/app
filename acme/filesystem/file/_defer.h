#pragma once


#ifndef __cplusplus_winrt


template < typename TYPE >
inline stream & operator >> (stream & stream, TYPE & t) { stream.defer_set_loading(); stream.stream_exchange(::id::e_type_null, t); return stream; }


template < typename TYPE >
inline stream & operator << (stream & stream, const TYPE & t) { stream.defer_set_storing(); stream.stream_exchange(::id::e_type_null, (TYPE &)t); return stream; }


template < typename TYPE >
inline void stream::default_exchange(TYPE & t) { is_loading() ? read(t) : write(t); }


template < typename TYPE >
inline void stream::write_only(TYPE & t) { is_loading() ? throw_status(error_io) : write(t); }


template < typename TYPE >
inline void stream::stream_exchange(const ::id & id, TYPE & t) { ::__exchange(*this, t); }


#include "_defer_payload_stream.h"


#endif // __cplusplus_winrt



