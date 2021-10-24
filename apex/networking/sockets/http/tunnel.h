﻿#pragma once


//#include "sockets_http_socket.h"


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


      http_tunnel();
      bool        m_bSslTunnel;
      bool        m_bOk ;
      string m_host; ///< Hostname from url_in
      port_t m_port; ///< Port from url_in
      string_array   m_straProxy;
      enum_state      m_estate;
      string      m_strRequest;
      //memory      m_memoryBody;
      //memory      m_memoryBuf;
      ::memory_file m_fileBody;
      i32         m_iContentLength;
      bool        m_bHeaders;
      bool        m_bDirect;
      string      m_strPasswordFile;
      string      m_strUserNameFile;

      virtual const string & GetUrlHost();
      /** get port from url. */
      virtual port_t GetUrlPort();


      using ::sockets::http_socket::open;
      virtual bool open(bool bConfigProxy = true);
      virtual bool proxy_open(const string &host, port_t port);


      void OnConnect() override;

      void OnLine(const ::string & strParam) override;

      virtual ::e_status step() override;

      virtual void OnFirst() override;
      virtual void OnHeader(id idKey, const string &) override;
      virtual void OnHeaderComplete() override;
      virtual void OnData(const char * psz, memsize size) override;


   };


} // namespace sockets




