#pragma once


namespace sockets_bsd
{


   class CLASS_DECL_NETWORKING_BSD sync_socket_handler :
      virtual public ::object,
      public socket::callback
   {
      public:


         socket *                         m_psocket;
         ::memory_file                    m_file;
         ::pointer<socket_handler>       m_phandler;
         int                              m_iDefaultTimeout;


         sync_socket_handler(::apex::log *log = nullptr);
         ~sync_socket_handler() override;


         using ::sockets::socket::callback::OnRawData;
         virtual void OnRawData(base_socket * psocket, void * pdata, memsize len) override;

         virtual void transfer(socket_map::association * passociation, socket_map * psocketmap = nullptr);

         virtual void write(string & str);
         virtual void write(const void * pdata, int len);
         virtual int read(void * pdata, int len);
         virtual string read_line();
         virtual void read_full_string(string & str);


         virtual void read_payload_v1(string & strPayload, int timeout = -1);
         virtual void write_payload_v1(const char * szPayload, int timeout = -1);

   };


} // namespace sockets_bsd






