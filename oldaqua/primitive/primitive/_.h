#pragma once


#include "aqua/primitive/primitive/var.h"
#include "aqua/primitive/primitive/property_set.h"
//#include "aqua/primitive/primitive/application_bias.h"
//#include "aqua/primitive/primitive/create.h"
#include "aqua/primitive/primitive/edit.h"
#include "aqua/primitive/primitive/factory.h"
#include "aqua/primitive/primitive/id.h"
#include "aqua/primitive/primitive/id_space.h"
#include "aqua/primitive/primitive/interlocked_long.h"
#include "aqua/primitive/primitive/interlocked_long_pulse.h"
//#include "aqua/primitive/primitive/job.h"
#include "aqua/primitive/primitive/memory_container.h"
//#include "aqua/primitive/primitive/relation_set.h"
//#include "aqua/primitive/primitive/request_signal.h"
#include "aqua/primitive/primitive/shared_memory.h"
#include "aqua/primitive/primitive/virtual_memory.h"


#include "aqua/primitive/primitive/property_set_papaya.h"


// class CLASS_DECL_AQUA parents :
//    virtual public ::context_object
// {
// public:


//    __pointer_array(object)            m_ptra;

//    parents();
//    ~parents();


// };


// class CLASS_DECL_AQUA children :
//    virtual public ::context_object
// {
// public:


//    __pointer_array(object)            m_ptra;
//    duration                      m_durationWait;


//    children();
//    ~children();


//    // after posting quit to a child, the PARENT shouldn't context_object it
//    virtual void set_finish(::object * pobjectParent);

//    virtual ::count wait_quit(::object * pobjectParent, const duration & duration);
//    virtual ::count _wait_quit(::object * pobjectParent);


//    virtual __pointer(::object) running(const char * pszTag) const;
//    virtual bool running(::object * pobject) const;


//    friend class object;

// };


namespace papaya
{

   CLASS_DECL_AQUA void transfer_to(::file::file * pfileOut, memory_base & mem, memsize uiBufferSize = 1024 * 1024);

   CLASS_DECL_AQUA void transfer_from_begin(::file::file * pfileIn, memory_base & mem, memsize uiBufferSize = 1024 * 1024);

   CLASS_DECL_AQUA void transfer_from(::file::file * pfileIn, memory_base & mem, memsize uiBufferSize = 1024 * 1024);


} // namespace papaya



inline stream & operator << (stream & s, const memory_container & memcontainer);


CLASS_DECL_AQUA stream & operator >> (stream & s, memory_container & memcontainer);


inline stream & operator << (stream & s, const memory_base & mem);


inline stream & operator >> (stream & s, memory_base & mem);



