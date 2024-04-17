#pragma once


#ifndef WINDOWS
using errno_t = int;
#endif



#include "acme/operating_system/shared_posix/c_error_number.h"


//CLASS_DECL_ACME errno_t c_runtime_error_check(errno_t error);
//CLASS_DECL_ACME void __cdecl __clearerr_s(FILE * stream);

#define C_RUNTIME_ERROR_CHECK(expr) ::c_error_number::s_throw_exception(expr)


#if defined(LINUX) || defined(__APPLE__)
#include <wchar.h>
#endif


namespace acme
{


   inline void __cdecl safe_memory_copy(void * _S1, strsize _S1max, const void * _S2, strsize N)
   {
      ::memory_copy(_S1, _S2, N);
   }

   inline void __cdecl safe_wmemory_copy(::wide_character * _S1, strsize _N1, const ::wide_character * _S2, strsize N)
   {
      ::memory_copy(_S1, _S2, N * sizeof(::wide_character));
   }

   inline void __cdecl safe_memory_transfer(void * _S1, strsize _S1max, const void * _S2, strsize N)
   {
      memory_transfer(_S1, _S2, N);
   }


   CLASS_DECL_ACME i32 get_errno();
   CLASS_DECL_ACME void set_errno(i32 _Value);


} // namespace acme



