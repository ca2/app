#pragma once


#include "aura/primitive/primitive/var.h"
#include "aura/primitive/primitive/property_set.h"
//#include "aura/primitive/primitive/application_bias.h"
//#include "aura/primitive/primitive/create.h"
#include "aura/primitive/primitive/edit.h"
#include "aura/primitive/primitive/factory.h"
#include "aura/primitive/primitive/id.h"
#include "aura/primitive/primitive/id_space.h"
#include "aura/primitive/primitive/interlocked_long.h"
#include "aura/primitive/primitive/interlocked_long_pulse.h"
//#include "aura/primitive/primitive/job.h"
#include "aura/primitive/primitive/memory_container.h"
//#include "aura/primitive/primitive/relation_set.h"
//#include "aura/primitive/primitive/request_signal.h"
#include "aura/primitive/primitive/shared_memory.h"
#include "aura/primitive/primitive/virtual_memory.h"


#include "aura/primitive/primitive/property_set_papaya.h"


// class CLASS_DECL_AURA parents :
//    virtual public ::context_object
// {
// public:


//    __pointer_array(object)            m_ptra;

//    parents();
//    ~parents();


// };


// class CLASS_DECL_AURA children :
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

   CLASS_DECL_AURA void transfer_to(::file::file * pfileOut, memory_base & mem, memsize uiBufferSize = 1024 * 1024);

   CLASS_DECL_AURA void transfer_from_begin(::file::file * pfileIn, memory_base & mem, memsize uiBufferSize = 1024 * 1024);

   CLASS_DECL_AURA void transfer_from(::file::file * pfileIn, memory_base & mem, memsize uiBufferSize = 1024 * 1024);


} // namespace papaya



inline stream & operator << (stream & s, const memory_container & memcontainer);


CLASS_DECL_AURA stream & operator >> (stream & s, memory_container & memcontainer);


inline stream & operator << (stream & s, const memory_base & mem);


inline stream & operator >> (stream & s, memory_base & mem);



