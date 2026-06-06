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
#include <string.h>

namespace subsystem_bsd_sockets
{


::i32 subsystem::get_last_socket_error() { return errno; }


bool subsystem::socket_would_block()
{
   int iError = get_last_socket_error();

   return socket_would_block(iError);
}


bool subsystem::socket_would_block(int iError)
{
return iError == EAGAIN || iError == EWOULDBLOCK;
}


   string subsystem::get_socket_error_message_text(::i32 iError)
   {

      if (iError <= 0)
      {

         return {};
      }
      
      auto pszError = ::strerror(iError);
      
      return pszError;

   }


} // namespace subsystem_bsd_sockets



