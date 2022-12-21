#include "framework.h"
//#include "apex/networking/sockets/_sockets.h"


namespace sockets
{


   sync_socket_handler::sync_socket_handler(::particle * pparticle, ::apex::log * plog) :
      ::object(pparticle),
      m_handler(pparticle, plog)
   {

      m_psocket            = nullptr;
      m_iDefaultTimeout    = 60;

   }

   sync_socket_handler::~sync_socket_handler()
   {
   }

   void sync_socket_handler::handle(socket * psocket)
   {
      if(m_psocket != nullptr)
         throw ::exception(::exception()); // busy
      m_psocket = psocket;
      m_psocket->m_pcallback = this;
      m_handler.add(m_psocket);
   }


   void sync_socket_handler::OnRawData(socket * psocket, void * pdata, memsize len)
   {
      if(m_psocket == psocket)
      {
         m_file.write(pdata, len);
      }
   }

   
   void sync_socket_handler::write(string &str)
   {
      
      m_psocket->write(str, str.length());

   }


   void sync_socket_handler::write(void * pdata, memsize len)
   {
      m_psocket->write((char *) pdata, len);
   }

   memsize sync_socket_handler::read(void * pdata, memsize len)
   {
      while(m_file.get_size() < len && m_handler.get_count() > 0)
      {
         m_handler.select(8, 0);
      }
      return m_file.erase_begin(pdata, len);
   }

   string sync_socket_handler::read_string()
   {
      string str;
      m_file.to_string(str);
      return str;
   }

   string sync_socket_handler::read_line()
   {
      string str;
      char ch;
      while(m_file.read(&ch, 1) > 0)
      {
         if(ch == '\0')
         {
            return str;
         }
         str += ch;
         if(ch == '\r' || ch == '\n')
         {
            if(m_file.read(&ch, 1) <= 0)
               break;
            if(ch == '\r' || ch == '\n')
            {
               str += ch;
               return str;
            }
            else
            {
               m_file.seek(-1, ::e_seek_current);
               return str;
            }
         }
      }
      return str;
   }

   void sync_socket_handler::read_payload_v1(string & xml_payload, int iTimeout)
   {
      __UNREFERENCED_PARAMETER(xml_payload);
      if(iTimeout < 0)
         iTimeout = m_iDefaultTimeout;
      memsize uiLen = 0;
      if(read(&uiLen, 4) != 4)
         throw ::exception(::exception());
      ntohl((u_long) uiLen);
      memory memory;
      memory.set_size(uiLen);
      if(read(memory, uiLen) != uiLen)
         throw ::exception(::exception());
   }

   void sync_socket_handler::write_payload_v1(const char * xml_payload, int iTimeout)
   {
      if(iTimeout < 0)
         iTimeout = m_iDefaultTimeout;
      strsize uiLen = strlen(xml_payload);
      u32 wf_total_length = htonl((u_long) uiLen);
      write(&wf_total_length, 4);
      write( (char *) xml_payload, uiLen);
   }

} // namespace sockets
