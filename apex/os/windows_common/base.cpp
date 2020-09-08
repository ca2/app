#include "framework.h"
#include "apex/platform/static_start.h"


VOID
WINAPI
output_debug_string_a(
_In_opt_ LPCSTR pOutputString

)
{

   ::output_debug_string(wstring(pOutputString));


}

VOID
WINAPI
output_debug_string_w(
_In_opt_ LPCWSTR pOutputString

)
{

   ::output_debug_string(pOutputString);


}

typedef WINBASEAPI
VOID
WINAPI
FN_OutputDebugStringA(
_In_opt_ LPCSTR pOutputString

);

typedef WINBASEAPI
VOID
WINAPI
FN_OutputDebugStringW(
_In_opt_ LPCWSTR pOutputString

);

typedef FN_OutputDebugStringA * PFN_OutputDebugStringA;

typedef FN_OutputDebugStringW * PFN_OutputDebugStringW;

PFN_OutputDebugStringA g_pfnOutputDebugStringA = ::OutputDebugStringA;

PFN_OutputDebugStringW g_pfnOutputDebugStringW = ::OutputDebugStringW;


namespace apex
{


   void set_simple_output_debug_string_a()
   {
      g_pfnOutputDebugStringA = ::OutputDebugStringA;
   }

   void set_extended_output_debug_string_a()
   {
      g_pfnOutputDebugStringA = ::output_debug_string_a;
   }

   void set_simple_output_debug_string_w()
   {
      g_pfnOutputDebugStringW = ::OutputDebugStringW;
   }

   void set_extended_output_debug_string_w()
   {
      g_pfnOutputDebugStringW = ::OutputDebugStringW;
   }


} // namespace apex



void output_debug_string(const char * psz)
{

   g_pfnOutputDebugStringA(psz);

}


void w_output_debug_string(const unichar * pwsz)
{

   g_pfnOutputDebugStringW(pwsz);

}


void output_debug_string(const unichar * pwsz)
{

   g_pfnOutputDebugStringW(pwsz);

}



namespace process
{


   bool set_priority(::e_priority epriority)
   {

      return (::SetPriorityClass(::GetCurrentProcess(), get_os_priority_class(epriority)) != 0);


   }


} // namespace process



::file::path __node_full_file_path(file::path path)
{

   WCHAR wszPath[8192];

   DWORD dw = GetFullPathNameW(L"\\\\?\\"+wstring(path), sizeof(wszPath) / sizeof(WCHAR), wszPath, nullptr);

   return wszPath;

}



CLASS_DECL_APEX DWORD get_current_process_id()
{

   return ::GetCurrentProcessId();

}



//LARGE_INTEGER g_largeintegerFrequency;

//extern "C"
CLASS_DECL_APEX i64 get_nanos()
{

   LARGE_INTEGER largeinteger = {};

   QueryPerformanceCounter(&largeinteger);

   return muldiv64(largeinteger.QuadPart, 1'000'000'000, ::apex::g_largeintegerFrequency.QuadPart);

}
