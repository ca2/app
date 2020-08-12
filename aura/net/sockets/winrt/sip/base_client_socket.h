#pragma once

namespace sockets
{

   class CLASS_DECL_AURA sip_base_client_socket :
      virtual public sip_base,
      virtual public socket
   {
   public:

      enum e_error
      {
         error_none,
         error_wrong_state,
      };

      enum e_state
      {
         state_free, // caller/receiver
         state_waiting_call_trying, // caller/server
         state_waiting_call_ringing, // caller/server
         state_waiting_call_ok, // caller/server
         state_ringing, // receiver/server/caller
         state_waiting_bye_ok,
      };

      e_error        m_eerrorLast;
      e_state        m_estate;
      string         m_strTo;
      string         m_strFrom;

      i64 m_iFirstTime;

      sip::request   m_request;
      sip::response  m_response;

      bool m_b_http_1_1;
      bool m_b_keepalive;

      bool     m_bFirst;
      bool     m_bHeader;
      string   m_strLine;
      bool     m_bRequest;
      bool     m_bResponse;
      memsize m_body_size_left;
      bool m_b_chunked;
      memsize m_chunk_size;
      int m_chunk_state;
      string m_chunk_line;

      sip_base_client_socket(base_socket_handler& );
      ~sip_base_client_socket();

      void OnRawData(char *buf,memsize len);
      void OnLine(const string & line);

      /** Callback executes when first line has been received.
         GetMethod, GetUrl/GetUri, and GetHttpVersion are valid when this callback is executed. */
      virtual void OnFirst();
      /** For each header line this callback is executed.
         \param key Http header name
         \param value Http header value */
      virtual void OnHeader(const string & key,const string & value, const string & lowvalue);
      /** Callback fires when all http headers have been received. */
      virtual void OnHeaderComplete();
      /** Chunk of http body data recevied. */
      virtual void OnData(const char *,memsize);
      /** The full request/response body has been received. */
      virtual void OnDataComplete() {}

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
      void url_this(const string & url_in,string & protocol,string & host,port_t& port,string & url,string & file);

      /** Transfer coding 'chunked' */
      bool IsChunked() { return m_b_chunked; }

      property & inattr(const char * pszName);
      property_set & inattrs();

      property & inheader(const char * pszName);
      property_set & inheaders();

      property & outattr(const char * pszName);
      property_set & outattrs();

      property & outheader(const char * pszName);
      property_set & outheaders();

      sip::request & request();
      sip::response & response();

      /** Reset state of socket to sucessfully implement keep-alive. */
      virtual void Reset();

   };


} // namespace sockets


