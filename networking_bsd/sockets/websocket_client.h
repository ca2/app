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
      ::duration m_durationLastPing;
      ::duration m_durationLastPong;
      ::duration m_durationLastSpontaneousPong;
      e_ping      m_eping;
      memory      m_memPong;

      ::duration  m_durationClientPingTimeout;

      int         m_fin;
      int         m_opcode;
      int         m_mask;
      int         m_n0;
      memsize         m_header_size;
      memsize         m_iN;
      int         m_i;
      byte        m_maskingkey[4];
      int         m_iLastPos;
      ::mutex       m_mutexWebsocketWrite;
      string            m_strOrigin;


      websocket_client();
      websocket_client(const string & url, const ::string & strProtocol);
      //websocket_client(const string & host, port_t port, const string & url);
      ~websocket_client() override;

      virtual void InitSSLClient() override;

      bool step() override;

      void OnLine(const string &) override;

      void OnHeaderComplete() override;

      long cert_common_name_check(const ::string & common_name) override;

      virtual void OnDataComplete() override;

      virtual void write(const void *buf, memsize c) override;

      virtual bool send_network_payload(::payload varNetworkPayload);
      virtual bool send_memory(memory & memory);

      virtual void OnRawData(char *buf, memsize len) override;

      virtual void on_websocket_data(u8 * pdata, int len);
      virtual void on_websocket_data(string str);

      virtual bool client_ping_pong_ok();


   };


} // namespace networking_bsd


CLASS_DECL_NETWORKING_BSD void websocket_prefix_varuint32(memory & m, unsigned int u);



