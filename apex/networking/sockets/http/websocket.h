#pragma once


#include "apex/networking/sockets/http/http_socket.h"


namespace sockets
{


   class http_socket;


   class CLASS_DECL_APEX websocket :
      virtual public ::particle
   {
   public:

      enum e_ping
      {

         ping_none,
         ping_sent_ping,
         ping_pong_received,

      };

      bool        m_bServer;
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
      memory      m_memoryPing;
      memory      m_memPong;

      class ::time  m_timeClientPingTimeout;
      class ::time m_timeServerPingInterval;

      int         m_fin;
      int         m_opcode;
      int         m_mask;
      int         m_n0;
      memsize         m_header_size;
      memsize         m_iN;
      int         m_i;
      unsigned char        m_maskingkey[4];
      int         m_iLastPos;
      ::pointer < ::mutex >       m_pmutexWebsocketWrite;
      string            m_strOrigin;
      
      ::pointer < ::sockets::http_socket > m_phttpsocket;

      websocket();
      
      //websocket_client(const ::scoped_string & scopedstrHost, ::networking::port_t port, const string & url);
      ~websocket() override;


      virtual void initialize_websocket(::sockets::http_socket * phttpsocket);

      //virtual void InitSSLClient() override;

      virtual bool http_request_step();
      
      
      virtual void defer_negotiate_incoming_request();

      //void OnLine(const ::scoped_string & scopedstrLine);

      void OnHeaderComplete();

      long cert_common_name_check(const ::string & common_name);

      virtual void OnDataComplete();

      //virtual void on_websocket_text(const ::scoped_string & scopedstrText);

      //virtual void on_websocket_data2(const ::block & blockData);
      
      virtual void on_select_idle();
      
      virtual void write(const void * p, ::memsize s);


      virtual bool send_network_payload(::payload varNetworkPayload);
      virtual bool send_memory(memory & memory);

      virtual void OnRawData(char *buf, memsize len);

      virtual void _call_on_websocket_text(const ::scoped_string& scopedstrText);
      virtual void _call_on_websocket_data2(const ::block & blockData);

      virtual void _on_websocket_text(const ::scoped_string& scopedstrText);
      virtual void _on_websocket_data2(const ::block & blockData);
      
      virtual void server_ping();

      virtual bool client_ping_pong_ok();
      
      
      virtual memory get_server_send(int fin, memory & memory);
      virtual memory get_server_send(int fin, const_char_pointer src);
      
      
      virtual memory get_client_send(int fin, memory & memory);
      virtual memory get_client_send(int fin, const_char_pointer src);

      
      virtual memory get_frame_send(int fin, memory & memory, bool useMask);
      virtual memory get_frame_send(int fin, const_char_pointer src, bool useMask);

      
      virtual memory get_client_send_text(const_char_pointer src);
      //virtual memory get_client_send_text(const_char_pointer src);
      virtual memory get_client_send_binary(memory & memory);


   };


} // namespace sockets


CLASS_DECL_APEX void websocket_prefix_varuint32(memory & m, unsigned int u);



