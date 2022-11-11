#pragma once


namespace sockets
{


   class CLASS_DECL_APEX sync_socket_handler :
      virtual public ::object,
      public socket::callback
   {
      public:


         socket *                      m_psocket;
         ::memory_file         m_file;
         socket_handler                m_handler;
         int                           m_iDefaultTimeout;


         sync_socket_handler(::particle * pparticle, ::apex::log *log = nullptr);
         virtual ~sync_socket_handler();



         virtual void OnRawData(socket * psocket, void * pdata, memsize len);

         void handle(socket * psocket);

         virtual void write(string & str);
         virtual void write(void * pdata, memsize len);
         virtual memsize read(void * pdata, memsize len);
         virtual string read_line();
         virtual string read_string();


         virtual void read_payload_v1(string & strPayload, int timeout = -1);
         virtual void write_payload_v1(const char * szPayload, int timeout = -1);

   };


} // namespace sockets






