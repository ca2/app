#pragma once


#include "acme/primitive/primitive/var.h"
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


#include "acme/primitive/primitive/update.h"


#include "acme/primitive/primitive/promise.h"


// class CLASS_DECL_ACME parents :
//    virtual public ::element
// {
// public:


//    __pointer_array(element)            m_ptra;

//    parents();
//    ~parents();


// };


// class CLASS_DECL_ACME children :
//    virtual public ::element
// {
// public:


//    __pointer_array(element)            m_ptra;
//    duration                      m_durationWait;


//    children();
//    ~children();


//    // after posting quit to a child, the PARENT shouldn't element it
//    virtual void set_finish(::element * pobjectParent);

//    virtual ::count wait_quit(::element * pobjectParent, const duration & duration);
//    virtual ::count _wait_quit(::element * pobjectParent);


//    virtual __pointer(::element) running(const char * pszTag) const;
//    virtual bool running(::element * pobject) const;


//    friend class element;

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



