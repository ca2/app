#pragma once


namespace sockets
{


   class CLASS_DECL_AURA sync_socket_handler :
      virtual public ::object,
      public socket::callback
   {
      public:


         socket *                m_psocket;
         ::memory_file   m_file;
         socket_handler          m_handler;
         i32                 m_iDefaultTimeout;

         sync_socket_handler(::object * pobject, ::aura::log *log = nullptr);
         virtual ~sync_socket_handler();


         using ::sockets::socket::callback::OnRawData;
         virtual void OnRawData(base_socket * psocket, void * pdata, memsize len) override;

         void handle(socket * psocket);

         virtual void write(string & str);
         virtual void write(const void * pdata, i32 len);
         virtual i32 read(void * pdata, i32 len);
         virtual string read_line();
         virtual void read_full_string(string & str);


         virtual void read_payload_v1(string & strPayload, i32 timeout = -1);
         virtual void write_payload_v1(const char * szPayload, i32 timeout = -1);

   };


} // namespace sockets






