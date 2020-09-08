#pragma once

CLASS_DECL_AQUA errno_t c_runtime_error_check(errno_t error);
CLASS_DECL_AQUA void __cdecl __clearerr_s(FILE * stream);

#define C_RUNTIME_ERROR_CHECK(expr) ::c_runtime_error_check(expr)


#if defined(LINUX) || defined(APPLEOS)
#include <wchar.h>
#endif


namespace aqua
{


   inline void __cdecl memcpy_s(void * _S1, strsize _S1max, const void * _S2, strsize N)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::memcpy_s(_S1, (rsize_t)_S1max, _S2, (rsize_t)N));
#else
      ::memcpy_dup(_S1, _S2, N);
#endif
   }

   inline void __cdecl wmemcpy_s(widechar * _S1, strsize _N1, const widechar * _S2, strsize N)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::wmemcpy_s(_S1, (rsize_t)_N1, _S2, (rsize_t)N));
#else
      ::memcpy_dup(_S1, _S2, N * sizeof(widechar));
#endif
   }

   inline void __cdecl memmove_s(void * _S1, strsize _S1max, const void * _S2, strsize N)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::memmove_s(_S1, (rsize_t)_S1max, _S2, (rsize_t)N));
#else
      __memmov(_S1, _S2, N);
#endif
   }


   CLASS_DECL_AQUA i32 get_errno();
   CLASS_DECL_AQUA void set_errno(i32 _Value);


} // namespace aqua



