#pragma once


#include "http_tunnel.h"
//#include "acme/prototype/prototype/matter.h"
#include "apex/progress/integer.h"
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
      virtual public http_tunnel
   {
   public:


#ifdef UNIVERSAL_WINDOWS

      //string m_strTlsHostName;

#endif

      ::pointer < ::mutex >                          m_pmutexData;
      ::memory_file_pointer            m_pmemoryfile;
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
      //string m_protocol; ///< Protocol part of url_in
      //string m_url_filename; ///< Filename from url_in
      string m_content_type; ///< Content-type: header from response
      //::url::parts      m_url;


      http_client_socket();
      // http_client_socket(const string & url_in);
      ~http_client_socket() override;


      virtual void initialize_http_client_socket(const ::url::url & url);

      virtual void OnConnect() override;

      /** Parse url to protocol,host,port,url and spfile-> */
      //void Url(const string & url_in,string & host,::networking::port_t& port);

      void set_url(const ::url::url& url);

      void OnFirst() override;
      void OnHeader(const ::atom & atom,const ::scoped_string & scopedstr) override;
      void OnHeaderComplete() override;
      void OnData(const_char_pointer ,memsize) override;
      void OnDelete() override;

      virtual void OnDataArrived(const_char_pointer ,memsize);

      /** New callback method fires when all data is received. */
      virtual void OnContent();

      /** get response headers. */
      ::string GetContent();

      /** get int_size of response body. */
      memsize GetContentLength();

      /** get content type from response header. */
      ::string GetContentType();

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
      ::string GetUrlProtocol();

      /** get filename part of url. */
      ::string GetUrlFilename();

      virtual void OnDataComplete() override;


      virtual void request_url(const ::url::url & url);


      bool on_set_scalar(enum_scalar escalar,::number number,int iFlags) override;
      ::number get_scalar_minimum(enum_scalar escalar) override;
      ::number get_scalar(enum_scalar escalar) override;
      ::number get_scalar_maximum(enum_scalar escalar) override;

      virtual string MyUseragent() override;


      bool http_request_step() override;


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

