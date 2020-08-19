#pragma once


namespace sockets
{


   class CLASS_DECL_AURA websocket_client :
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
      tick m_tickLastPing;
      tick m_tickLastPong;
      tick m_tickLastSpontaneousPong;
      e_ping      m_eping;
      memory      m_memPong;

      int         m_iClientPingTimeout;

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


      websocket_client(base_socket_handler&);
      websocket_client(base_socket_handler&, const string & url, const string & strProtocol);
      //websocket_client(base_socket_handler&, const string & host, port_t port, const string & url);
      virtual ~websocket_client();

      virtual void InitSSLClient() override;

      virtual void step() override;

      virtual void OnLine(const string &) override;

      virtual void OnHeaderComplete() override;

      virtual long cert_common_name_check(const char * common_name) override;

      virtual void OnDataComplete() override;

      virtual void write(const void *buf, memsize c) override;

      virtual bool send_json(var varJson);
      virtual bool send_memory(memory & memory);

      virtual void OnRawData(char *buf, memsize len) override;

      virtual void on_websocket_data(u8 * pdata, int len);
      virtual void on_websocket_data(string str);

      virtual bool client_ping_pong_ok();


   };


} // namespace sockets


CLASS_DECL_AURA void websocket_prefix_varuint(memory & m, unsigned int ui);



