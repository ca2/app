#pragma once


#include "http_socket.h"


namespace sockets
{


   class CLASS_DECL_APEX http_tunnel :
      virtual public http_socket
   {
   public:


      enum enum_state
      {
         e_state_initial,
         state_connect_sent,
         state_proxy_ok,
         state_init_ssl

      };
      bool        m_bSslTunnel;
      bool        m_bOk;
      //string m_host; ///< Hostname from url_in
      //::networking::port_t m_port; ///< Port from url_in
      string_array   m_straProxy;
      enum_state      m_estate;
      string      m_strRequest;
      //memory      m_memoryBody;
      //memory      m_memoryBuf;
      ::memory_file_pointer m_pfileBody;
      int         m_iContentLength;
      bool        m_bHeaders;
      bool        m_bDirect;
      string      m_strPasswordFile;
      string      m_strUserNameFile;


      http_tunnel();
      ~http_tunnel() override;

      void initialize(::particle * pparticle) override;

      virtual ::string GetUrlHost();
      /** get port from url. */
      virtual ::networking::port_t GetUrlPort();


      using ::sockets::http_socket::open;
      virtual bool open(bool bConfigProxy = true);
      virtual bool proxy_open(const string &host, ::networking::port_t port);


      void OnConnect() override;

      void OnLine(const ::string & strParam) override;

      virtual bool http_request_step();

      virtual void OnFirst() override;
      virtual void OnHeader(atom idKey, const string &) override;
      virtual void OnHeaderComplete() override;
      virtual void OnData(const char * psz, memsize size) override;


   };


} // namespace sockets




