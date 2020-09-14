#pragma once


#include "update.h"


//#include "apex/primitive/primitive/var.h"
//#include "apex/primitive/primitive/property_set.h"
////#include "apex/primitive/primitive/application_bias.h"
////#include "apex/primitive/primitive/create.h"
//#include "apex/primitive/primitive/edit.h"
//#include "apex/primitive/primitive/factory.h"
//#include "apex/primitive/primitive/id.h"
//#include "apex/primitive/primitive/id_space.h"
//#include "apex/primitive/primitive/interlocked_long.h"
//#include "apex/primitive/primitive/interlocked_long_pulse.h"
////#include "apex/primitive/primitive/job.h"
//#include "apex/primitive/primitive/memory_container.h"
////#include "apex/primitive/primitive/relation_set.h"
////#include "apex/primitive/primitive/request_signal.h"
//#include "apex/primitive/primitive/shared_memory.h"
//#include "apex/primitive/primitive/virtual_memory.h"
//
//
#include "apex/primitive/primitive/property_set_papaya.h"
//
//
//// class CLASS_DECL_APEX parents :
////    virtual public ::context_object
//// {
//// public:
//
//
////    __pointer_array(object)            m_ptra;
//
////    parents();
////    ~parents();
//
//
//// };
//
//
//// class CLASS_DECL_APEX children :
////    virtual public ::context_object
//// {
//// public:
//
//
////    __pointer_array(object)            m_ptra;
////    duration                      m_durationWait;
//
//
////    children();
////    ~children();
//
//
////    // after posting quit to a child, the PARENT shouldn't context_object it
////    virtual void set_finish(::object * pobjectParent);
//
////    virtual ::count wait_quit(::object * pobjectParent, const duration & duration);
////    virtual ::count _wait_quit(::object * pobjectParent);
//
//
////    virtual __pointer(::object) running(const char * pszTag) const;
////    virtual bool running(::layered * pobjectContext) const;
//
//
////    friend class object;
//
//// };
//
//
//namespace papaya
//{
//
//   CLASS_DECL_APEX void transfer_to(::file::file * pfileOut, memory_base & mem, memsize uiBufferSize = 1024 * 1024);
//
//   CLASS_DECL_APEX void transfer_from_begin(::file::file * pfileIn, memory_base & mem, memsize uiBufferSize = 1024 * 1024);
//
//   CLASS_DECL_APEX void transfer_from(::file::file * pfileIn, memory_base & mem, memsize uiBufferSize = 1024 * 1024);
//
//
//} // namespace papaya
//
//
//
//inline stream & operator << (stream & s, const memory_container & memcontainer);
//
//
//CLASS_DECL_APEX stream & operator >> (stream & s, memory_container & memcontainer);
//
//
//inline stream & operator << (stream & s, const memory_base & mem);
//
//
//inline stream & operator >> (stream & s, memory_base & mem);
//
//
//
