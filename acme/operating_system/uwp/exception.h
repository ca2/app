#pragma once


namespace gen
{


#ifndef _NO_EXCEPTIONS


   // Throw a atl_exception corresponding to the result of ::get_last_error
   NOINLINE DECLSPEC_NO_RETURN inline void WINAPI gen_ThrowLastWin32()
   {
      unsigned int dwError = ::GetLastError();
      throw ::exception(hresult_exception(HRESULT_FROM_WIN32( dwError ) ));
   }

#else  // no exception handling

   // Throw a atl_exception corresponding to the result of ::get_last_error
   NOINLINE inline void WINAPI gen_ThrowLastWin32()
   {
      unsigned int dwError = ::get_last_error();
      throw ::exception(hresult_exception(HRESULT_FROM_WIN32( dwError ) ));
   }

#endif  // no exception handling

}  // namespace gen
