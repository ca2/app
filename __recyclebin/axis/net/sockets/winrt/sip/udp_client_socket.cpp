#include "framework.h"


namespace sockets
{


   sip_udp_client_socket::sip_udp_client_socket(base_socket_handler & h) :
      ::object(h.get_context_application()),
      base_socket(h),
      socket(h),
      udp_socket(h),
      sip_base_client_socket(h)
   {
   }




   void sip_udp_client_socket::OnRawData(char *buf,memsize len,struct sockaddr *sa,socklen_t sa_len)
   {
      UNREFERENCED_PARAMETER(sa);
      UNREFERENCED_PARAMETER(sa_len);
      // TODO: should validate sa and sa_len
      sip_base_client_socket::OnRawData(buf, len);
   }

   void sip_udp_client_socket::OnRawData(char *buf,memsize len,struct sockaddr *sa,socklen_t sa_len,struct timeval *ts)
   {
      UNREFERENCED_PARAMETER(sa);
      UNREFERENCED_PARAMETER(sa_len);
      UNREFERENCED_PARAMETER(ts);
      // TODO: should validate sa, sa_len and organize using ts
      sip_base_client_socket::OnRawData(buf, len);
   }


} // namespace sockets



