#pragma once


//#include "sockets_http_tunnel.h"

//#include "apex/networking/sockets/bsd/basic/socket_handler.h"


namespace sockets
{


   enum e_http_method
   {
      http_method_none,
      http_method_get,
      http_method_post,
      http_method_put

   };


   CLASS_DECL_APEX string http_method_string(e_http_method emethod);
   CLASS_DECL_APEX e_http_method string_http_method(const ::scoped_string & scopedstr);


   /** get http response to file or memory.
   \ingroup http */
   class CLASS_DECL_APEX http_client_socket :
      virtual public http_tunnel,
      virtual public int_scalar_source
   {
   public:


#ifdef UNIVERSAL_WINDOWS

      //string m_strTlsHostName;

#endif

      ::pointer < ::mutex >                          m_pmutexData;
      ::memory_file                    m_memoryfile;
      ::file::file *                   m_pfile;
      long long                              m_iFinalSize;
      ::progress::integer              m_progressinteger;
      e_http_method                    m_emethod;


      //memory    m_memoryData; ///< Ptr to buffer where to store response
      //memsize m_data_size; ///< Max int_size of data buffer
      memsize m_content_length; ///< Content-length header received from remote
      string m_content; ///< Received http headers
      //bool m_data_ptr_set; ///< buffer set from outside, do not delete
      memsize m_content_ptr; ///< Number of bytes received from body
      bool m_b_complete; ///< The entire content-length number of bytes has been received
      bool m_b_close_when_complete; ///< close when the full response has been received
      string m_protocol; ///< Protocol part of url_in
      string m_url_filename; ///< Filename from url_in
      string m_content_type; ///< Content-type: header from response



      http_client_socket();
      http_client_socket(const string & url_in);
      virtual ~http_client_socket();


      virtual void OnConnect() override;

      /** Parse url to protocol,host,port,url and spfile-> */
      void Url(const string & url_in,string & host,port_t& port);

      void OnFirst() override;
      void OnHeader(atom,const string &) override;
      void OnHeaderComplete() override;
      void OnData(const_char_pointer ,memsize) override;
      void OnDelete() override;

      virtual void OnDataArrived(const_char_pointer ,memsize);

      /** New callback method fires when all data is received. */
      virtual void OnContent();

      /** get response headers. */
      const string & GetContent();

      /** get int_size of response body. */
      memsize GetContentLength();

      /** get content type from response header. */
      const string & GetContentType();

      /** get int_size of received response body. */
      memsize GetContentPtr();

      /** get int_size of received response body. */
      memsize GetPos();

      /** Complete response has been received. */
      bool Complete();

      /** get ptr to response data buffer. */
      const unsigned char *GetDataPtr() const;

      /** get length of response data buffer. */
      memsize GetDataLength() const;

      /** close socket when response received. */
      virtual void SetCloseOnComplete(bool = true);

      /** get protocol used from url. */
      const string & GetUrlProtocol();

      /** get filename part of url. */
      const string & GetUrlFilename();

      virtual void OnDataComplete() override;


      virtual void request_url(const ::scoped_string & scopedstrUrlParam);


      virtual void on_set_scalar(enum_scalar escalar,long long iValue,int iFlags) override;
      virtual void get_scalar_minimum(enum_scalar escalar, long long & i) override;
      virtual void get_scalar(enum_scalar escalar, long long & i) override;
      virtual void get_scalar_maximum(enum_scalar escalar, long long & i) override;

      virtual string MyUseragent() override;


   };


} // namespace sockets




namespace http
{


   class CLASS_DECL_APEX session :
      virtual public ::object
   {
   public:


      ::pointer<::sockets::socket_handler>        m_phandler;
      ::pointer<::sockets::http_client_socket>    m_psocket;


      // session(::object* pparticle);
      session();
      virtual ~session();


   };


} // namespace http

