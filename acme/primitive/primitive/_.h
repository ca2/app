#pragma once


#include "acme/primitive/primitive/payload.h"
#include "acme/primitive/primitive/property_set.h"
//#include "acme/primitive/primitive/application_bias.h"
//#include "acme/primitive/primitive/create.h"
#include "acme/primitive/primitive/edit.h"
#include "acme/primitive/primitive/factory.h"
#include "acme/primitive/primitive/id.h"
#include "acme/primitive/primitive/id_space.h"
#include "acme/primitive/primitive/interlocked_long.h"
#include "acme/primitive/primitive/interlocked_long_pulse.h"
//#include "acme/primitive/primitive/job.h"
#include "acme/primitive/primitive/memory_container.h"
//#include "acme/primitive/primitive/relation_set.h"
//#include "acme/primitive/primitive/request_signal.h"
#include "acme/primitive/primitive/shared_memory.h"
#include "acme/primitive/primitive/virtual_memory.h"


#include "acme/primitive/primitive/property_set_papaya.h"


#include "acme/user/_const_key.h"


#include "acme/primitive/primitive/context_object.h"


#if OBJ_REF_DBG


template < typename TYPE, typename T >
void ___assign(__pointer(TYPE) & ptr, T * p OBJ_REF_DBG_COMMA_PARAMS);

template < typename TYPE >
void ___release(__pointer(TYPE) & ptr OBJ_REF_DBG_COMMA_PARAMS);

template < typename TYPE >
void ___release(TYPE *& p OBJ_REF_DBG_COMMA_PARAMS);


#endif


//#include "acme/platform/update_item.h"


//#include "acme/platform/update.h"


//CLASS_DECL_ACME ::e_status __fork(
//   matter* pmatter,
//   ::e_priority epriority = priority_normal,
//   u32 nStackSize = 0,
//   u32 dwCreateFlags = 0,
//   ithread_t* pithread = nullptr,
//   hthread_t* phthread = nullptr);


//CLASS_DECL_ACME void launch_action(action* psubject);


#include "acme/primitive/promise/_.h"


// class CLASS_DECL_ACME parents :
//    virtual public ::matter
// {
// public:


//    __pointer_array(matter)            m_ptra;

//    parents();
//    ~parents();


// };


// class CLASS_DECL_ACME children :
//    virtual public ::matter
// {
// public:


//    __pointer_array(matter)            m_ptra;
//    duration                      m_durationWait;


//    children();
//    ~children();


//    // after posting quit to a child, the PARENT shouldn't matter it
//    virtual void finish(::matter * pobjectParent);

//    virtual ::count wait_quit(::matter * pobjectParent, const duration & duration);
//    virtual ::count _wait_quit(::matter * pobjectParent);


//    virtual __pointer(::matter) running(const char * pszTag) const;
//    virtual bool running(::matter * pobject) const;


//    friend class matter;

// };


namespace papaya
{

   CLASS_DECL_ACME void transfer_to(::file::file * pfileOut, memory_base & mem, memsize uiBufferSize = 1024 * 1024);

   CLASS_DECL_ACME void transfer_from_begin(::file::file * pfileIn, memory_base & mem, memsize uiBufferSize = 1024 * 1024);

   CLASS_DECL_ACME void transfer_from(::file::file * pfileIn, memory_base & mem, memsize uiBufferSize = 1024 * 1024);


} // namespace papaya



inline stream & operator << (stream & s, const memory_container & memcontainer);


CLASS_DECL_ACME stream & operator >> (stream & s, memory_container & memcontainer);


inline stream & operator << (stream & s, const memory_base & mem);


inline stream & operator >> (stream & s, memory_base & mem);


CLASS_DECL_ACME string __str(const ::e_status & estatus);
