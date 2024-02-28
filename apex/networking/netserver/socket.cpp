#include "framework.h"
#include "socket.h"
#include "acme/platform/system.h"
#include "acme/primitive/time/_text_stream.h"


namespace netserver
{


   static ::count s_countNetnodeSocket = 0;


   socket::socket()
   {

      m_bSetCookie = true;

      s_countNetnodeSocket++;

   }


   socket::~socket()
   {
      s_countNetnodeSocket--;
   }


} // namespace netserver




