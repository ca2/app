#pragma once


namespace sockets
{


   class CLASS_DECL_AURA sip_udp_client_socket :
      virtual public udp_socket,
      virtual public sip_base_client_socket
   {
   public:

      sip_udp_client_socket();


      /** Called when incoming data has been received.
         \param buf Pointer to data
         \param len Length of data
         \param sa Pointer to sockaddr struct of sender
         \param sa_len Length of sockaddr struct */
      using ::sockets::udp_socket::OnRawData;
      virtual void OnRawData(char *buf,size_t len,struct sockaddr *sa,socklen_t sa_len);

      /** Called when incoming data has been received and read timestamp is enabled.
         \param buf Pointer to data
         \param len Length of data
         \param sa Pointer to sockaddr struct of sender
         \param sa_len Length of sockaddr struct
         \param ts Timestamp from message */
      virtual void OnRawData(char *buf,size_t len,struct sockaddr *sa,socklen_t sa_len,struct timeval *ts);

   };

} // namespace sockets



