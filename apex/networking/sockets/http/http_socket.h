#pragma once


#include "acme/prototype/mathematics/scalar.h"
#include "apex/networking/sockets/basic/tcp_socket.h"
#include "apex/networking/http/request.h"
#include "apex/networking/http/response.h"
#include "apex/networking/http/listener.h"


namespace sockets
{


   /** \defgroup http HTTP Sockets */
   /** HTTP request/response axis class.
   \ingroup http */
   class CLASS_DECL_APEX http_socket :
      virtual public tcp_socket,
      virtual public scalar_source
   {
   public:


      ::url::parts         m_urlparts;
      string               m_strProxy;
      i32                  m_iProxyPort;

      ::string m_strResponseLogMessage;
      ::http::request      m_request;
      ::http::response     m_response;

      bool                 m_b_http_1_1;
      bool                 m_b_keepalive;
      bool                 m_bChunked;
      bool                 m_bFirst;
      bool                 m_bHeader;
      string               m_strLine;
      bool                 m_bRequest;
      bool                 m_bResponse;
      ::collection::index              m_iRequestIndex;
      //bool               m_bExpectRequest;
      memsize              m_body_size_left;
      memsize              m_body_size_downloaded;
      ::f64                m_dDownloadRate;
      ::i64                m_iDownloaded;
      memsize              m_chunk_size;
      int                  m_chunk_state;
      string               m_chunk_line;

      class ::time              m_timeFirstTime;

      bool                 m_bOnlyHeaders;
      bool                 m_bNoClose;
      ::pointer<::http::listener>    m_plistener;
      ::i64                m_iHttpSocketRequestSerial;

      http_socket();
      ~http_socket() override;


      void initialize(::particle * pparticle) override;

      virtual ::i64 get_request_serial();
      ::string get_request_url_string() override;

      virtual void OnEndChunk();

      void OnRawData(char *buf,memsize len) override;
      void OnLine(const string & line) override;

      /** Callback executes when first line has been received.
      GetMethod, GetUrl/GetUri, and GetHttpVersion are valid when this callback is executed. */
      virtual void OnFirst();
      /** For each header line this callback is executed.
      \lparam key Http header name
      \lparam value Http header value */
      virtual void OnHeader(atom key, const string & value);
      /** Callback fires when all http headers have been received. */
      virtual void OnHeaderComplete();
      /** Chunk of http body data recevied. */
      virtual void OnData(const char *, memsize);
      /** The full request/response body has been received. */
      virtual void OnDataComplete();

      bool IsRequest();

      bool IsResponse();

      //virtual ::collection::index http_request_index();


      /** Send response prepared with calls to methods SetHttpVersion, SetStatus, SetStatusText,
      and AddResponseHeader. */
      void SendResponse();
      /** Send request prepared with calls to methods SetMethod, SetUrl, SetHttpVersion,
      and AddResponseHeader. */
      void SendRequest();

      void SendResponseBody();

      /** Implement this to return your own User-agent string. */
      virtual string MyUseragent();

      /** Parse url. If protocol is https, EnableSSL() will be called. */
      void set_url(const ::url::url & url);


      /** Transfer coding 'chunked' */
      inline bool IsChunked()
      {

         return m_bChunked;

      }

      property & inattr(const ::atom & atom);
      property_set & inattrs();

      property & inheader(const ::atom& atom);
      property_set & inheaders();

      property & outattr(const ::atom& atom);
      property_set & outattrs();

      property & outheader(const ::atom& atom);
      property_set & outheaders();

      ::http::request & request();
      ::http::response & response();


      /** Reset state of socket to sucessfully implement keep-alive. */
      virtual void Reset();

      virtual bool http_filter_response_header(::property & property);

      virtual void client_to_server(http_socket * psocket);

      void finalize() override;


   };


   inline ::http::request & http_socket::request()
   {
      
      return m_request;

   }


   inline ::http::response & http_socket::response()
   {

      return m_response;

   }


   inline property & http_socket::inattr(const ::atom& atom)
   {

      return m_request.attr(atom);

   }


   inline property_set & http_socket::inattrs()
   {

      return m_request.attrs();

   }


   inline property & http_socket::outattr(const ::atom& atom)
   {

      return m_response.attr(atom);

   }


   inline property_set & http_socket::outattrs()
   {

      return m_response.attrs();

   }


   inline property & http_socket::inheader(const ::atom& atom)
   {

      return m_request.header(atom);

   }


   inline property_set & http_socket::inheaders()
   {

      return m_request.headers();

   }


   inline property & http_socket::outheader(const ::atom& atom)
   {

      return m_response.header(atom);

   }


   inline property_set & http_socket::outheaders()
   {

      return m_response.headers();

   }


   inline bool http_socket::IsRequest()
   {

      return m_bRequest;

   }


   inline bool http_socket::IsResponse()
   {

      return m_bResponse;

   }


} // namespace sockets



