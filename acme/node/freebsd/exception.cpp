#include "framework.h"
#include "_freebsd.h"



namespace gen
{

#if defined( _CUSTOM_THROW )  // You can define your own __throw( hresult_exception to __throw( a custom exception.

CLASS_DECL_ACME void WINAPI atl_throw_impl( HRESULT hr )
{
   TRACE(atlTraceException, 0, "__throw(hresult_exception: hr = 0x%x\n", hr ));
#ifdef _AFX
   if( hr == E_OUTOFMEMORY )
   {
      __throw(error_no_memory);
   }
   else
   {
//      ::ca2::ThrowOleException( hr );
   }
#else
   __throw(atl_exception( hr ));
#endif
};

#endif


// Throw a atl_exception with th given HRESULT
#if !defined( _CUSTOM_THROW )  // You can define your own __throw( hresult_exception

//CLASS_DECL_ACME void WINAPI atl_throw_impl(HRESULT hr)
//{
//   TRACE("__throw(hresult_exception: hr = 0x%x\n", hr));
 //  __throw(hresult_exception(hr));
/*   ::output_debug_string("__throw(hresult_exception"));
   char sz[200];
   sprintf(sz, "0x%s", hr);
   ::output_debug_string(sz);
   ::output_debug_string("\n");
   //TRACE(trace::category_Exception, 0, "__throw(hresult_exception: hr = 0x%x\n", hr ));
   ASSERT( false );
   ::u32 dwExceptionCode;
   switch(hr)
   {
   case E_OUTOFMEMORY:
      dwExceptionCode = STATUS_NO_MEMORY;
      break;
   default:
      dwExceptionCode = EXCEPTION_ILLEGAL_INSTRUCTION;
   }
   atl_raise_exception((::u32)dwExceptionCode);*/
//}
#endif


} // namespace gen
