#include "framework.h"
#include "aura/platform/static_start.h"


VOID
WINAPI
output_debug_string_a(
_In_opt_ const char * pOutputString

)
{

   ::infomration(wstring(pOutputString));


}

VOID
WINAPI
output_debug_string_w(
_In_opt_ const ::wide_character * pOutputString

)
{

   ::infomration(pOutputString);


}


namespace aura
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


} // namespace aura



namespace process
{


   bool set_priority(::enum_priority epriority)
   {

      return (::SetPriorityClass(::GetCurrentProcess(), get_os_priority_class(epriority)) != 0);


   }


} // namespace process



::file::path __xxxnode_full_file_path(file::path path)
{

   WCHAR wszPath[8192];

   ::u32 dw = GetFullPathNameW(L"\\\\?\\"+wstring(path), sizeof(wszPath) / sizeof(WCHAR), wszPath, nullptr);

   return wszPath;

}



CLASS_DECL_AURA ::u32 get_current_process_id()
{

   return ::GetCurrentProcessId();

}



//LARGE_INTEGER g_largeintegerFrequency;

//extern "C"
CLASS_DECL_AURA i64 get_nanos()
{

   LARGE_INTEGER largeinteger = {};

   QueryPerformanceCounter(&largeinteger);

   return muldiv64(largeinteger.QuadPart, 1'000'000'000, ::aura::g_largeintegerFrequency.QuadPart);

}
