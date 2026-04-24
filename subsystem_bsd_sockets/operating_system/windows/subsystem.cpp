//
// From subsystem_windows by camilo on 2026-04-12 17:10 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "subsystem_bsd_sockets/platform/subsystem.h"
//#include <wincrypt.h>
//#include "node/PipeServer.h"
//#include "node/Shell.h"
//#include "node/WTS.h"
//
//#pragma comment(lib, "Crypt32.lib")


namespace subsystem_bsd_sockets
{


   int subsystem::get_last_socket_error() { return WSAGetLastError(); }


   string subsystem::get_socket_error_message_text(int iError)
   {

      if (iError <= 0)
      {

         return {};
      }

      LPWSTR buffer = nullptr;

      DWORD size =
         FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
                        nullptr, iError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&buffer, 0, nullptr);

      ::wstring wstr;

      if (size && buffer)
      {

         wstr.assign(buffer, size);
      }

      LocalFree(buffer); // always safe (even if buffer == nullptr)

      return wstr;
   }


} // namespace subsystem_bsd_sockets



