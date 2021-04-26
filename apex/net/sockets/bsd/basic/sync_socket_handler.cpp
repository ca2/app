#include "framework.h"
#include "apex/net/sockets/_sockets.h"


namespace sockets
{


   sync_socket_handler::sync_socket_handler(::apex::log * plog) //:
      //::object(pobject),
      //m_handler(pobject, plog)
      //m_handler(plog)
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
      {

         __throw(error_socket); // busy

      }

      m_psocket = psocket;

      m_psocket->m_pcallback = this;

      m_phandler->add(m_psocket);

   }


   void sync_socket_handler::OnRawData(base_socket * psocket, void * pdata, memsize len)
   {

      if(m_psocket == psocket)
      {

         m_file.write(pdata, len);

      }

   }

   void sync_socket_handler::write(string &str)
   {

      m_psocket->print(str);

   }


   void sync_socket_handler::write(const void * pdata, i32 len)
   {

      m_psocket->write(pdata, len);

   }


   i32 sync_socket_handler::read(void * pdata, i32 len)
   {

      while(less_than(m_file.get_size(), len) && m_phandler->get_count() > 0)
      {

         m_phandler->select(8, 0);

      }

      return (i32) m_file.erase_begin(pdata, len);

   }


   void sync_socket_handler::read_full_string(string & str)
   {

      return ((::file::file &)m_file).to_string(str);

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
               m_file.seek(-1, ::file::seek_current);
               return str;
            }
         }
      }
      return str;
   }


   void sync_socket_handler::read_payload_v1(string & xml_payload, i32 iTimeout)
   {

      if (iTimeout < 0)
      {

         iTimeout = m_iDefaultTimeout;

      }

      u32 uLen = 0;

      if (read(&uLen, 4) != 4)
      {

         __throw(error_socket);

      }

      uLen = ntohl((u_long) uLen);

      memory memory;

      memory.set_size(uLen);

      if (read(memory, uLen) != uLen)
      {

         __throw(error_socket);

      }

      memory.to_string(xml_payload);

   }


   void sync_socket_handler::write_payload_v1(const char * xml_payload, i32 iTimeout)
   {
      if(iTimeout < 0)
         iTimeout = m_iDefaultTimeout;
      strsize uLen = strlen(xml_payload);
      u32 wf_total_length = htonl((u_long) uLen);
      write(&wf_total_length, 4);
      write( (char *) xml_payload, (i32) uLen);
   }

} // namespace sockets
