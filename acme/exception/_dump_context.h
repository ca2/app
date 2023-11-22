#pragma once


void __dump_stack(u32 dwFlags = __stack_dump_TARGET_DEFAULT);

#include "dump_context.h"

#ifdef NNDEBUG
extern CLASS_DECL_ACME bool g_bTraceEnabled;
#endif //NNDEBUG

#ifdef NNDEBUG
#define _DUMP( exp ) (void)(*system()->m_pdumpcontext<<exp)
#else //NNDEBUG
#define _DUMP( exp )
#endif //!NNDEBUG



