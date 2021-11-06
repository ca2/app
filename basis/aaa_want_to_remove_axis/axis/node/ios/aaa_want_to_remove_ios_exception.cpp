#include "framework.h"




namespace gen
{
   
#if defined( _CUSTOM_THROW )  // You can define your own throw hresult_exception to throw a custom exception.
   
   CLASS_DECL_BOOT void WINAPI atl_throw_impl( HRESULT hr )
   {
      TRACE(atlTraceException, 0, "throw hresult_exception: hr = 0x%x\n", hr );
#ifdef _AFX
      if( hr == E_OUTOFMEMORY )
      {
         throw memory_exception();
      }
      else
      {
         //      ::ca2::ThrowOleException( hr );
      }
#else
      throw atl_exception( hr );
#endif
   };
   
#endif
   
   
   // Throw a atl_exception with th given HRESULT
#if !defined( _CUSTOM_THROW )  // You can define your own throw hresult_exception
   
   //CLASS_DECL_BOOT void WINAPI atl_throw_impl(HRESULT hr)
   //{
   //   TRACE("throw hresult_exception: hr = 0x%x\n", hr);
   //  throw hresult_exception(hr);
   /*   ::output_debug_string("throw hresult_exception");
    char sz[200];
    sprintf(sz, "0x%s", hr);
    ::output_debug_string(sz);
    ::output_debug_string("\n");
    //TRACE(trace::category_Exception, 0, "throw hresult_exception: hr = 0x%x\n", hr );
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




