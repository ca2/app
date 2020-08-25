#include "framework.h"
#include "aura/node/windows/_windows.h"
//#include <stdio.h>
//#include <stdarg.h>


int __node_is_debugger_attached()
{

   return ::IsDebuggerPresent();

}


// Twitter Automator and Denis Lakic and UpWork contribution
// enzymes: Liveedu.tv, Twitch.tv and Mixer.com streamers and viewers
// Mummi and bilbo!!
// create call to :
CLASS_DECL_AURA void windows_install_crash_dump_reporting(::object * pobject)
{

   ::windows::registry::key k;

   auto pcontext = pobject->get_context();

   string m = pcontext->file().module().name();

   string strKey = "SOFTWARE\\Microsoft\\Windows\\Windows Error Reporting\\LocalDumps\\" + m;

   if (k._open(HKEY_LOCAL_MACHINE, strKey, true))
   {
      ::file::path str = dir::system() / "CrashDumps" / m;
      wstring wstr = str;
      RegSetValueExW(k.m_hkey, L"DumpFolder", 0, REG_EXPAND_SZ, (byte *)wstr.c_str(),  DWORD ((wcslen(wstr) + 1) * sizeof(wchar_t)));
      DWORD dw = 10;
      RegSetValueExW(k.m_hkey, L"DumpCount", 0, REG_DWORD, (byte *)&dw, sizeof(dw));
      dw = 2;
      RegSetValueExW(k.m_hkey, L"DumpType", 0, REG_DWORD, (byte *)&dw, sizeof(dw));

   }

   output_debug_string("test01");

}


