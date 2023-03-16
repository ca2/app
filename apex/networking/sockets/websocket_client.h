#pragma once


#include "apex/networking/sockets/http/client_socket.h"


namespace sockets
{


   class CLASS_DECL_APEX websocket_client :
      virtual public http_client_socket
   {
   public:

      enum e_ping
      {

         ping_none,
         ping_sent_ping,
         ping_pong_received,

      };

      bool        m_bTls;
      string      m_strBase64;
      bool        m_bRequestSent;
      bool        m_bWebSocket;
      string      m_strWebSocketProtocol;
      memory      m_memResponse;
      memory      m_memReceivedData;
      bool        m_bUseMask;
      class ::time m_timeLastPing;
      class ::time m_timeLastPong;
      class ::time m_timeLastSpontaneousPong;
      e_ping      m_eping;
      memory      m_memPong;

      class ::time  m_timeClientPingTimeout;

      int         m_fin;
      int         m_opcode;
      int         m_mask;
      int         m_n0;
      memsize         m_header_size;
      memsize         m_iN;
      int         m_i;
      byte        m_maskingkey[4];
      int         m_iLastPos;
      ::pointer < ::mutex >       m_pmutexWebsocketWrite;
      string            m_strOrigin;


      websocket_client();
      
      //websocket_client(const string & host, ::networking::port_t port, const string & url);
      ~websocket_client() override;


      virtual void initialize_websocket_client(const string & url, const ::string & strProtocol);

      virtual void InitSSLClient() override;

      bool step() override;

      void OnLine(const string &) override;

      void OnHeaderComplete() override;

      long cert_common_name_check(const ::string & common_name) override;

      virtual void OnDataComplete() override;

      
      using http_client_socket::write;
      virtual void write(const void * p, ::memsize s) override;


      virtual bool send_network_payload(::payload varNetworkPayload);
      virtual bool send_memory(memory & memory);

      virtual void OnRawData(char *buf, memsize len) override;

      virtual void on_websocket_data(u8 * pdata, int len);
      virtual void on_websocket_data(string str);

      virtual bool client_ping_pong_ok();

      virtual memory get_client_send(int fin, memory & memory, bool useMask);
      virtual memory get_client_send(int fin, const char * src);

      virtual memory get_client_send_text(const char * src);
      virtual memory get_client_send_text(const char * src, bool bMasked);
      virtual memory get_client_send_binary(memory & memory);


   };


} // namespace sockets


CLASS_DECL_APEX void websocket_prefix_varuint32(memory & m, unsigned int u);



