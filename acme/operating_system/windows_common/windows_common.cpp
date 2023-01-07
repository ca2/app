#include "framework.h"
#include "acme/operating_system/error_code.h"
#include "acme/primitive/primitive/memory.h"
//#include "acme/primitive/primitive/function.h"
#include "acme/_operating_system.h"
#include "acme/operating_system/windows_common/_string.h"


int __node_is_debugger_attached()
{

   return ::IsDebuggerPresent();

}


#ifdef WINDOWS

extern LARGE_INTEGER g_largeintegerFrequency;

#endif


CLASS_DECL_ACME ::i64 integral_nanosecond()
{

   return ::time::now().integral_nanosecond();

   //LARGE_INTEGER largeinteger = {};

   //QueryPerformanceCounter(&largeinteger);

   //return integral_nanosecond(muldiv64(largeinteger.QuadPart, 1'000'000'000, ::g_largeintegerFrequency.QuadPart));

}


//void output_debug_string(const ::ansi_character * psz)
//{
//
//#ifdef WINDOWS
//
//   auto len = utf8_to_unichar_len(psz);
//
//   memory memory;
//
//   memory.set_size((len + 1) * sizeof(wchar_t));
//
//   auto pwsz = (wchar_t *)memory.data();
//
//   utf8_to_unichar(pwsz, psz, len);
//
//   ::OutputDebugStringW(pwsz);
//
//#else
//
//   printf("%s", psz);
//
//#endif
//
//}
//

void output_debug_string(const ::scoped_string & str)
{

   ::wstring wstr(str);

   ::OutputDebugStringW(wstr);

}


CLASS_DECL_ACME htask_t get_current_htask()
{

   return ::GetCurrentThread();

}


CLASS_DECL_ACME itask_t get_current_itask()
{

   return ::GetCurrentThreadId();

}


CLASS_DECL_ACME void TRACELASTERROR()
{

   auto dwLastError = ::GetLastError();

   if (!dwLastError)
   {

      return;

   }

   string strErrorMessage = ::windows::last_error_message(dwLastError);

   string strError;

   strError.format("\nError Message:\n%s\n\n", strErrorMessage.c_str());

   ::output_debug_string(strError);

}


void CLASS_DECL_ACME __cdecl _ca2_purecall()
{

   throw_exception(error_pure_call);

}


namespace color
{


   ::u32 color::get_COLORREF() const
   {

      return RGB(red, green, blue);
   
   }


} // namespace color


namespace windows
{


   ::enum_status _hresult_status(HRESULT hr)
   {

      if (SUCCEEDED(hr))
      {

         return ::success;

      }
      else
      {

         return ::error_failed;

      }

   }


   string last_error_message(u32 dwError)
   {
   
      wstring wstr;
   
      unichar* p = nullptr;
   
      ::u32 dw = FormatMessageW(
         FORMAT_MESSAGE_FROM_SYSTEM 
         | FORMAT_MESSAGE_ALLOCATE_BUFFER,
         nullptr,
         dwError,
         0,
         (LPWSTR) & p,
         64,
         nullptr);

      wstr = p;

      ::LocalFree(p);
   
      string str(wstr);

      return str;

   }


   CLASS_DECL_ACME error_code last_error_error_code(DWORD dwLastError)
   {

      return { e_error_code_type_last_error, dwLastError };

   }


   CLASS_DECL_ACME error_code last_error_error_code()
   {

      return last_error_error_code(::GetLastError());

   }


   CLASS_DECL_ACME::e_status wait_result_status(int iResult)
   {

      if (iResult >= WAIT_ABANDONED_0 && iResult < (WAIT_ABANDONED_0 + MAXIMUM_WAIT_OBJECTS))
      {

         return (::e_status)((::i64)abandoned_base + (iResult - WAIT_ABANDONED_0));

      }
      else if (iResult == WAIT_IO_COMPLETION)
      {

         return error_wait_io_completion;

      }
      else if (iResult == WAIT_FAILED)
      {

         return error_wait_failed;

      }
      else if (iResult == WAIT_TIMEOUT)
      {

         return error_wait_timeout;

      }
      else if (iResult >= WAIT_OBJECT_0 && iResult < (WAIT_OBJECT_0 + MAXIMUM_WAIT_OBJECTS))
      {

         return (::e_status)((::i64)signaled_base + (iResult - WAIT_OBJECT_0));

      }
      else
      {

         return error_failed;

      }

   }


} // namespace windows



