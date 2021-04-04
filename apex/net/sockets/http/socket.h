#pragma once


namespace sockets
{


   /** \defgroup http HTTP Sockets */
   /** HTTP request/response axis class.
   \ingroup http */
   class CLASS_DECL_APEX http_socket :
      virtual public tcp_socket
   {
   public:


      string               m_strProxy;
      i32                  m_iProxyPort;


      ::http::request      m_request;
      ::http::response     m_response;

      bool                 m_b_http_1_1;
      bool                 m_b_keepalive;

      bool                 m_bFirst;
      bool                 m_bHeader;
      string               m_strLine;
      bool                 m_bRequest;
      bool                 m_bResponse;
      memsize               m_body_size_left;
      memsize               m_body_size_downloaded;
      double_scalar_source m_scalarsourceDownloadedRate;
      int_scalar_source    m_scalarsourceDownloaded;
      memsize               m_chunk_size;
      int                  m_chunk_state;
      string               m_chunk_line;

      i64              m_iFirstTime;

      bool                 m_bOnlyHeaders;
      bool                 m_bNoClose;
      http::listener *     m_plistener;






      http_socket();
      virtual ~http_socket();


      virtual ::e_status on_initialize_object() override;


      virtual void OnEndChunk();

      virtual void OnRawData(char *buf,memsize len) override;
      virtual void OnLine(const string & line) override;

      /** Callback executes when first line has been received.
      GetMethod, GetUrl/GetUri, and GetHttpVersion are valid when this callback is executed. */
      virtual void OnFirst();
      /** For each header line this callback is executed.
      \lparam key Http header name
      \lparam value Http header value */
      virtual void OnHeader(id key, const string & value);
      /** Callback fires when all http headers have been received. */
      virtual void OnHeaderComplete();
      /** Chunk of http body data recevied. */
      virtual void OnData(const char *, memsize);
      /** The full request/response body has been received. */
      virtual void OnDataComplete();

      bool IsRequest();

      bool IsResponse();

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
      void url_this(string strUrl, string & strProtocol, string & strHost, port_t & port, string & strRequestUri, string & strFile);

      /** Transfer coding 'chunked' */
      bool IsChunked() { return m_b_chunked; }

      property & inattr(const char * lpszName);
      property_set & inattrs();

      property & inheader(const char * lpszName);
      property_set & inheaders();

      property & outattr(const char * lpszName);
      property_set & outattrs();

      property & outheader(const char * lpszName);
      property_set & outheaders();

      ::http::request & request();
      ::http::response & response();


      /** Reset state of socket to sucessfully implement keep-alive. */
      virtual void Reset();

      virtual bool http_filter_response_header(string & strKey, string_array & straValue);

      virtual void client_to_server(http_socket * psocket);


   };



   inline ::http::request & http_socket::request()
   {
      return m_request;
   }

   inline ::http::response & http_socket::response()
   {
      return m_response;
   }

   inline property & http_socket::inattr(const char * lpszName)
   {
      return m_request.attr(lpszName);
   }

   inline property_set & http_socket::inattrs()
   {
      return m_request.attrs();
   }

   inline property & http_socket::outattr(const char * lpszName)
   {
      return m_response.attr(lpszName);
   }

   inline property_set & http_socket::outattrs()
   {
      return m_response.attrs();
   }

   inline property & http_socket::inheader(const char * lpszName)
   {
      return m_request.header(lpszName);
   }

   inline property_set & http_socket::inheaders()
   {
      return m_request.headers();
   }

   inline property & http_socket::outheader(const char * lpszName)
   {
      return m_response.header(lpszName);
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


