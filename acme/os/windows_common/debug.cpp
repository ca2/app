#include "framework.h"



string get_system_error_message(u32 dwError)
{
   wstring wstr;
   unichar* p = wstr.get_string_buffer(64 * 1024 / sizeof(unichar));
   DWORD dw = FormatMessageW(
      FORMAT_MESSAGE_FROM_SYSTEM,
      nullptr,
      dwError,
      0,
      p,
      (DWORD) (wstr.get_length() / sizeof(unichar)),
      nullptr);
   p[dw] = L'\0';
   wstr.release_string_buffer();
   string str(wstr);
   return str;
}


int __node_is_debugger_attached()
{

   return ::IsDebuggerPresent();

}


CLASS_DECL_ACME DWORD get_last_error()
{

   return GetLastError();

}


CLASS_DECL_ACME void set_last_error(DWORD dw)
{

   SetLastError(dw);

}





