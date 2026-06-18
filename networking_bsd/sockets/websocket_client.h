#pragma once


namespace networking_bsd
{


   class CLASS_DECL_NETWORKING_BSD websocket_client :
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

      ::i32         m_fin;
      ::i32         m_opcode;
      ::i32         m_mask;
      ::i32         m_n0;
      memsize         m_header_size;
      memsize         m_iN;
      ::i32         m_i32;
      ::u8        m_maskingkey[4];
      ::i32         m_iLastPos;
      ::pointer < ::mutex >       m_pmutexWebsocketWrite;
      string            m_strOrigin;


      websocket_client();
      websocket_client(const string & url, const ::scoped_string & scopedstrProtocol);
      //websocket_client(const ::scoped_string & scopedstrHost, ::networking::port_t port, const string & url);
      ~websocket_client() override;

      virtual void InitSSLClient() override;

      bool step() override;

      void OnLine(const ::scoped_string & scopedstrLine) override;

      void OnHeaderComplete() override;

      long cert_common_name_check(const ::string & common_name) override;

      virtual void OnDataComplete() override;

      virtual void write(const void *buf, memsize c) override;

      virtual bool send_network_payload(::payload varNetworkPayload);
      virtual bool send_memory(memory & memory);

      virtual void OnRawData(char_pointer buf, memsize len) override;

      virtual void on_websocket_data(::u8 * pdata, ::i32 len);
      virtual void on_websocket_data(const ::scoped_string & scopedstr);

      virtual bool client_ping_pong_ok();


   };


} // namespace networking_bsd


CLASS_DECL_NETWORKING_BSD void websocket_prefix_varuint32(memory & m, ::u32 u);



