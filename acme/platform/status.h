#pragma once


//#

//CLASS_DECL_ACME bool thread_get_flag(e_thread_flag eflag);


#define __defer_throw_estatus(xxx) \
auto estatus ## __LINE__ = (xxx); if(::failed(estatus ## __LINE__) && !avoid_bad_status_exception()) throw estatus ## __LINE__;

// class estatus :
//    public cflag < ::estatus    >
// {
// public:

//    using cflag <::estatus    >::cflag;

//    operator bool() { return ::succeeded(m_i); }

// };
