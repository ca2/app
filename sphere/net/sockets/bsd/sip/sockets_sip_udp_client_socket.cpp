#include "framework.h" // #include "axis/net/sockets/bsd/sockets.h"
#include "aura/net/net_sockets.h"


namespace sockets
{


   sip_udp_client_socket::sip_udp_client_socket() :
      object(h.get_application()),
      base_socket(h),
      socket(h),
      udp_socket(h),
      sip_base_client_socket(h)
   {

   }


   void sip_udp_client_socket::OnRawData(char *buf,size_t len,struct sockaddr *sa,socklen_t sa_len)
   {

      __UNREFERENCED_PARAMETER(sa);
      __UNREFERENCED_PARAMETER(sa_len);
      // TODO: should validate sa and sa_len
      sip_base_client_socket::OnRawData(buf, len);

   }


   void sip_udp_client_socket::OnRawData(char *buf,size_t len,struct sockaddr *sa,socklen_t sa_len,struct timeval *ts)
   {
      
      __UNREFERENCED_PARAMETER(sa);
      __UNREFERENCED_PARAMETER(sa_len);
      __UNREFERENCED_PARAMETER(ts);
      // TODO: should validate sa, sa_len and organize using ts
      sip_base_client_socket::OnRawData(buf, len);

   }


} // namespace sockets






