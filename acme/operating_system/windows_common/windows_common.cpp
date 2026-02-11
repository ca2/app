#include "framework.h"
#include "acme/operating_system/error_code.h"
#include "acme/prototype/prototype/memory.h"
//#include "acme/prototype/prototype/function.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"
#include "acme/operating_system/windows_common/_string.h"
#include "acme/operating_system/windows_common/handle.h"


int __node_is_debugger_attached()
{

   return ::IsDebuggerPresent();

}


#ifdef WINDOWS

extern LARGE_INTEGER g_largeintegerFrequency;

#endif


CLASS_DECL_ACME long long long_long_nanosecond()
{

   return ::time::now().integral_nanosecond();

   //LARGE_INTEGER largeinteger = {};

   //QueryPerformanceCounter(&largeinteger);

   //return integral_nanosecond(muldiv64(largeinteger.QuadPart, 1'000'000'000, ::g_largeintegerFrequency.QuadPart));

}


//void information(const_char_pointer psz)
//{
//
//#ifdef WINDOWS
//
//   auto len = utf8_to_unichar_len(scopedstr);
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


void output_debug_string(const ::scoped_string& str)
{

   ::wstring wstr(str);

   ::OutputDebugStringW(wstr);

}


void output_debug_line(const ::scoped_string& str)
{

   ::wstring wstr(str);

   wstr += "\r\n";

   ::OutputDebugStringW(wstr);

}


void ansi_output_debug_line(const ::scoped_string& str)
{

   if (str.m_end[0] == '\0')
   {

      ::OutputDebugStringA(str);

      ::OutputDebugStringA("\r\n");

   }
   else
   {

      auto len = str.length_in_bytes();

      if (len < 16_KiB - 3)
      {

         char sz[16_KiB];

         memcpy(sz, str.m_begin, len);

         sz[len] = '\r';

         sz[len + 1] = '\n';

         sz[len + 2] = '\0';

         ::OutputDebugStringA(sz);

      }
      else
      {

         ::string strLine(str);

         strLine += "\r\n";

         ::OutputDebugStringA(strLine);

      }

   }

}


void output_debug_string_flush()
{

}


CLASS_DECL_ACME htask current_htask()
{

   return (::uptr) ::GetCurrentThread();

}


CLASS_DECL_ACME itask current_itask()
{

   return ::GetCurrentThreadId();

}


CLASS_DECL_ACME itask as_itask(htask htask)
{

   return ::GetThreadId((HANDLE) htask.m_h);

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

   strError.formatf("\nError Message:\n%s\n\n", strErrorMessage.c_str());

   ::output_debug_string(strError);

}


void CLASS_DECL_ACME __cdecl _ca2_purecall()
{

   throw_exception(error_pure_call);

}

//
//namespace color
//{
//
//
//   unsigned int color::u32_COLORREF() const
//   {
//
//      return RGB(red, green, blue);
//   
//   }
//
//
//} // namespace color


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


   string last_error_message(unsigned int dwError)
   {

      wstring wstr;

      unichar* p = nullptr;

      unsigned int dw = FormatMessageW(
         FORMAT_MESSAGE_FROM_SYSTEM
         | FORMAT_MESSAGE_ALLOCATE_BUFFER,
         nullptr,
         dwError,
         0,
         (LPWSTR)&p,
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


   CLASS_DECL_ACME::e_status wait_result_status(int iResult, int nCount)
   {

      if (iResult >= WAIT_ABANDONED_0 && iResult < (WAIT_ABANDONED_0 + MAXIMUM_WAIT_OBJECTS))
      {

         return (::e_status)(::enum_status)((long long)abandoned_base + (iResult - WAIT_ABANDONED_0));

      }
      else if (iResult == WAIT_IO_COMPLETION)
      {

         return success_io_completion;

      }
      else if (iResult == WAIT_FAILED)
      {

         return error_wait_failed;

      }
      else if (iResult == WAIT_TIMEOUT)
      {

         return error_wait_timeout;

      }
      else if (iResult == WAIT_OBJECT_0 + nCount)
      {

         return success_messages;

      }
      else if (iResult >= WAIT_OBJECT_0 && iResult < (WAIT_OBJECT_0 + MAXIMUM_WAIT_OBJECTS))
      {

         return (::e_status)(::enum_status)((long long)signaled_base + (iResult - WAIT_OBJECT_0));

      }
      else
      {

         return error_failed;

      }

   }


} // namespace windows


//
//
// CLASS_DECL_ACME bool is_wayland()
// {
//
//    return false;
//
// }
//
//
//
// CLASS_DECL_ACME bool is_x11()
// {
//
//    return false;
//
// }
//


