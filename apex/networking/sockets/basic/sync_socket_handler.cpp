#include "framework.h"
#include "sync_socket_handler.h"
#include "socket.h"
#include "acme/filesystem/file/memory_file.h"


namespace sockets
{


   sync_socket_handler::sync_socket_handler(::apex::log * plog) //:
      //::object(pparticle),
      //m_handler(pparticle, plog)
      //m_handler(plog)
   {

      m_psocket            = nullptr;

      m_iDefaultTimeout    = 60;

   }


   sync_socket_handler::~sync_socket_handler()
   {

   }


   //void sync_socket_handler::transfer(socket_map::association * passociation, socket_map * psocketmap)
   //{

   //   if(m_psocket != nullptr)
   //   {

   //      throw ::exception(error_socket); // busy

   //   }

   //   m_psocket = dynamic_cast < socket * > (passociation->m_psocket.m_p);

   //   m_psocket->m_pcallback = this;

   //   m_phandler->transfer(passociation, psocketmap);

   //}


   void sync_socket_handler::OnRawData(base_socket * psocket, void * pdata, memsize len)
   {

      if(m_psocket == psocket)
      {

         m_pmemoryfile->write({ pdata, len });

      }

   }


   void sync_socket_handler::write(string &str)
   {

      m_psocket->print(str);

   }


   void sync_socket_handler::write(const void * pdata, int len)
   {

      m_psocket->write({ pdata, len });

   }


   int sync_socket_handler::read(void * pdata, int len)
   {

      return -1;

      //while(less_than(m_pmemoryfile->get_size(), len) && m_phandler->get_count() > 0)
      //{

      //   m_phandler->select(8, 0);

      //}

      //return (int) m_pmemoryfile->erase_begin(pdata, len);

   }


   void sync_socket_handler::read_full_string(string & str)
   {

      str = m_pmemoryfile->as_string();

   }


   string sync_socket_handler::read_line()
   {
      string str;
      char ch;
      while(m_pmemoryfile->read(&ch))
      {
         if(ch == '\0')
         {
            return str;
         }
         str += ch;
         if(ch == '\r' || ch == '\n')
         {
            if(!m_pmemoryfile->read(&ch))
               break;
            if(ch == '\r' || ch == '\n')
            {
               str += ch;
               return str;
            }
            else
            {
               --m_pmemoryfile->position();
               return str;
            }
         }
      }
      return str;
   }


   void sync_socket_handler::read_payload_v1(string & xml_payload, int iTimeout)
   {

      //if (iTimeout < 0)
      //{

      //   iTimeout = m_iDefaultTimeout;

      //}

      //unsigned int uLen = 0;

      //if (read(&uLen, 4) != 4)
      //{

      //   throw ::exception(error_socket);

      //}

      //uLen = ntohl((u_long) uLen);

      //memory memory;

      //memory.set_size(uLen);

      //if (read(memory, uLen) != uLen)
      //{

      //   throw ::exception(error_socket);

      //}

      //xml_payload = memory.get_string();

   }


   void sync_socket_handler::write_payload_v1(const char * xml_payload, int iTimeout)
   {
      //if(iTimeout < 0)
      //   iTimeout = m_iDefaultTimeout;
      //character_count uLen = strlen(xml_payload);
      //unsigned int wf_total_length = htonl((u_long) uLen);
      //write(&wf_total_length, 4);
      //write( (char *) xml_payload, (int) uLen);
   }

} // namespace sockets
