#include "framework.h"
#include "websocket_client.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/mathematics/mathematics.h"
#include "acme/prototype/string/base64.h"
#include "acme/crypto/crypto.h"
//#include "apex/id.h"
#include "apex/platform/application.h"
#include "apex/platform/system.h"

//
//#ifdef PARALLELIZATION_PTHREAD
//
//
//#include "acme/operating_system/ansi/_pthread.h"
//
//
//#endif
//
//
//#include <openssl/ssl.h>
//
//#define DEEP_DATA_DEBUG 0
//
///**
//* Return the number of bytes required to store a variable-length unsigned
//* 32-bit integer in base-128 varint encoding.
//*
//* \lparam v
//*      Value to encode.
//* \return
//*      Number of bytes required.
//*/
//static inline memsize u32_size(unsigned int v)
//{
//   if (v < (1UL << 7))
//   {
//      return 1;
//   }
//   else if (v < (1UL << 14))
//   {
//      return 2;
//   }
//   else if (v < (1UL << 21))
//   {
//      return 3;
//   }
//   else if (v < (1UL << 28))
//   {
//      return 4;
//   }
//   else
//   {
//      return 5;
//   }
//}
//
//
///**
//* Pack an unsigned 32-bit integer in base-128 varint encoding and return the
//* number of bytes written, which must be 5 or less.
//*
//* \lparam value
//*      Value to encode.
//* \lparam[out] out
//*      Packed value.
//* \return
//*      Number of bytes written to `out`.
//*/
//static inline memsize u32_pack(unsigned int value, unsigned char *out)
//{
//   unsigned rv = 0;
//
//   if (value >= 0x80)
//   {
//      out[rv++] = value | 0x80;
//      value >>= 7;
//      if (value >= 0x80)
//      {
//         out[rv++] = value | 0x80;
//         value >>= 7;
//         if (value >= 0x80)
//         {
//            out[rv++] = value | 0x80;
//            value >>= 7;
//            if (value >= 0x80)
//            {
//               out[rv++] = value | 0x80;
//               value >>= 7;
//            }
//         }
//      }
//   }
//   /* assert: value<128 */
//   out[rv++] = value;
//   return rv;
//}
//
//
//CLASS_DECL_APEX void websocket_prefix_varuint32(memory & m, unsigned int u)
//{
//
//   auto iSize = ::u32_size(u);
//
//   m.allocate_add_up(iSize);
//
//   m.transfer(iSize);
//
//   //auto iSize2 = ::u32_pack(u, m.data());
//   
//   ::u32_pack(u, m.data());
//
//}
//
//
//int client_send(memory & m, int fin, memory & memory, bool useMask)
//{
//
//   long long message_size = memory.size();
//
//   int length = (int) ( 2 + message_size);
//
//   if (message_size >= 65536)
//   {
//
//      length += 8;
//
//   }
//   else if (message_size >= 126)
//   {
//
//      length += 2;
//
//   }
//
//   unsigned char masking_key[4];
//
//   if (useMask)
//   {
//
//      length += 4;
//
//      __random_bytes(masking_key, 4);
//
//   }
//
//   m.set_size(length);
//
//   unsigned char * frame = (unsigned char*)m.data();
//
//   frame[0] = 0x80 | fin;
//
//   int iOffset = -1;
//
//   if (message_size < 126)
//   {
//
//      frame[1] = (message_size & 0xff) | (useMask ? 0x80 : 0);
//
//      iOffset = 2;
//
//   }
//   else if (message_size < 65536)
//   {
//
//      frame[1] = 126 | (useMask ? 0x80 : 0);
//      frame[2] = (message_size >> 8) & 0xff;
//      frame[3] = (message_size >> 0) & 0xff;
//
//      iOffset = 4;
//
//   }
//   else
//   {
//
//      frame[1] = 127 | (useMask ? 0x80 : 0);
//      frame[2] = (message_size >> 56) & 0xff;
//      frame[3] = (message_size >> 48) & 0xff;
//      frame[4] = (message_size >> 40) & 0xff;
//      frame[5] = (message_size >> 32) & 0xff;
//      frame[6] = (message_size >> 24) & 0xff;
//      frame[7] = (message_size >> 16) & 0xff;
//      frame[8] = (message_size >> 8) & 0xff;
//      frame[9] = (message_size >> 0) & 0xff;
//
//      iOffset = 10;
//
//   }
//
//   if (useMask)
//   {
//
//      frame[iOffset + 0] = masking_key[0];
//      frame[iOffset + 1] = masking_key[1];
//      frame[iOffset + 2] = masking_key[2];
//      frame[iOffset + 3] = masking_key[3];
//
//      iOffset += 4;
//
//   }
//
//   ::memory_copy(&frame[iOffset], memory.data(), memory.get_length());
//
//   if (useMask)
//   {
//
//      for (memsize i = 0; i < memory.get_length(); i++)
//      {
//
//         frame[iOffset + i] ^= masking_key[i & 3];
//
//      }
//
//   }
//
//   return (int) (m.size());
//
//}
//
//int client_send_binary(memory & m, memory & memory)
//{
//
//   return client_send(m, 0x82, memory, true);
//
//}
//
//int client_send(memory & m, int fin, const_char_pointer src)
//{
//
//   memsize len = 0;
//
//   if (src != nullptr)
//   {
//
//      len = strlen(src);
//
//   }
//
//   auto length = len
//                 + 1   //0x00
//                 + 1;  //0xFF
//
//   if (len >= 126)
//   {
//
//      if (len >= 65536)
//      {
//
//         length += 8;
//
//      }
//      else
//      {
//
//         length += 2;
//
//      }
//
//   }
//
//   m.set_size(length);
//
//   char* frame = (char*)m.data();
//
//   frame[0] = (char)fin;
//
//   int iOffset;
//
//   if (len >= 126)
//   {
//
//      if (len >= 65536)
//      {
//
//         iOffset = 10;
//
//         frame[1] = 127;
//         
//         *((long long*)&frame[2]) = HTONLL(len);
//         
//      }
//      else
//      {
//
//         iOffset = 4;
//
//         frame[1] = 126;
//
//         *((short*)&frame[2]) = htons((unsigned short) (len));
//
//      }
//
//   }
//   else
//   {
//
//      iOffset = 2;
//
//      frame[1] = (char) (len);
//
//   }
//
//   for (memsize i = 0; i < len; i++)
//   {
//
//      frame[iOffset + i] = src[i];//read src into frame
//
//   }
//
//   return (int) (m.size());
//
//}
//
//
//int client_send_text(memory & m, const_char_pointer src)
//{
//
//   return client_send(m, 0x81, src);
//
//}
//
//
//int client_send_text(memory & m, const_char_pointer src, bool bMasked)
//{
//
//   memory m2(src, strlen(src));
//
//   return client_send(m, 0x81, m2, bMasked);
//
//}

namespace sockets
{

   enum e_opcode
   {
      CONTINUATION = 0x0,
      TEXT_FRAME = 0x1,
      BINARY_FRAME = 0x2,
      CLOSE = 8,
      PING = 9,
      PONG = 0xa,
   };

   websocket_client::websocket_client() //:
      //::object(&h),
      //base_socket(h),
      //socket(h),
      //stream_socket(h),
      //tcp_socket(h),
      //http_socket(h),
      //http_tunnel(h),
      //http_client_socket(h)
   {

      //      m_timeLastSpontaneousPong = 0;
      m_memPong.set_size(2);
      m_memPong.data()[0] = 0x8a;
      m_memPong.data()[1] = 0;

      m_bUseMask = false;

      m_bRequestSent = false;

      m_bWebSocket = false;

      m_bTls = true;

#ifdef WINRT_SOCKETS

      m_bExpectRequest = true;

#endif

      m_eping = ping_none;

      m_timeLastPing.Now();

   }


   //websocket_client::websocket_client(const string & url_in, const ::scoped_string & scopedstrProtocol) :
   //   //::object(&h),
   //   //base_socket(h),
   //   //socket(h),
   //   //stream_socket(h),
   //   //tcp_socket(h),
   //   //http_socket(h),
   //   //http_tunnel(h),
   //   //http_client_socket(h, url_in)
   //   http_client_socket(url_in)
   //{

   //  

   //}


   //websocket_client::websocket_client(const ::scoped_string & scopedstrHost, ::networking::port_t port, const string & url_in) :
   //   object(h.get_app()),
   //   base_socket(h),
   //   socket(h),
   //   stream_socket(h),
   //   tcp_socket(h),
   //   http_socket(h),
   //   http_tunnel(h),
   //   http_client_socket(h, url_in)
   //{

   //   m_bRequestSent = false;

   //   m_bWebSocket = false;

   //   m_bTls = true;

   //   m_bExpectRequest = true;

   //   m_emethod = http_method_get;

   //   __UNREFERENCED_PARAMETER(host);

   //   __UNREFERENCED_PARAMETER(port);

   //}


   websocket_client::~websocket_client()
   {

   }


   void websocket_client::initialize_websocket_client(const string & url_in, const ::scoped_string & scopedstrProtocol)
   {

      initialize_http_client_socket(url_in);

      m_memPong.set_size(2);
      m_memPong.data()[0] = 0x8a;
      m_memPong.data()[1] = 0;

      m_timeLastPing.Now();

      m_bUseMask = false;

      m_strWebSocketProtocol = scopedstrProtocol;

      m_bRequestSent = false;

      m_bWebSocket = false;

      m_bTls = true;

#ifdef WINRT_SOCKETS

      m_bExpectRequest = true;

#endif

      m_emethod = http_method_get;

      m_timeLastPing.Now();

   }


   bool websocket_client::client_ping_pong_ok()
   {

      if (!m_bWebSocket)
      {

         if (m_timeLastPing.elapsed() > 60_s)
         {

            SetCloseAndDelete();

            return true;

         }

         m_timeLastPong.Now();

         return true;

      }

      if (m_timeClientPingTimeout <= 0_s)
      {

         return true;

      }

      if (m_eping == ping_sent_ping && m_timeLastPing.elapsed() > m_timeClientPingTimeout)
      {

         information() << "PING TIMEOUT!!";

         SetCloseAndDelete();

         return true;

      }

      if ((m_eping == ping_none || m_eping == ping_pong_received) && m_timeLastPong.elapsed() > m_timeClientPingTimeout)
      {

         m_timeLastPing.Now();

         m_eping = ping_sent_ping;

         //if (mask)
         //{

         //   for (memsize i = 0; i < n; i++)
         //   {

         //      data[i + header_size] ^= masking_key[i & 0x3];

         //   }

         //}

//         memory m1(&data[header_size], n);

         memory m1;

         //memory m;

         // bool bUseMask = m_bUseMask;
         bool bUseMask = false;

         //         client_send(m, e_opcode::PONG, m1, m_bUseMask);
         
         auto memory = get_client_send(e_opcode::PING, m1, bUseMask);

         write(memory);

         //m_memResponse.erase(0, n + header_size);


      }

      return true;

   }


   bool websocket_client::http_request_step()
   {

      if (!m_bWebSocket)
      {

         inheader("Host") = m_urlparts.connect().host();


         //      if (!(bool)inattr("minimal_headers"))
         {
            //inheader("Accept") = "text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,video/x-mng,image/png,image/jpeg,image/gif;q=0.2,*/*;q=0.1";
            //inheader("Accept-Language") = "en-us,en;q=0.5";
            //if (m_pfile == nullptr) // by the time, inline gzip decompression not yet implemented
            //{
            //   inheader("accept-encoding") = "gzip,deflate";
            //}
            //inheader("Accept-Charset") = "ISO-8859-1,utf-8;q=0.7,*;q=0.7";
            string strUserAgent = MyUseragent();
            inheader("user_agent") = strUserAgent;
         }
         //inheader("Content-Length") = 0;
         inheader("Upgrade") = "websocket";
         inheader("Connection") = "Upgrade";

         memory m;

         m.set_size(16);

         mathematics()->random(m);

         auto psystem = system();

         auto pbase64 = psystem->base64();

         m_strBase64 = pbase64->encode(m);

         //int iLen;

         //iLen = (int)(m_strBase64.length());

         inheader("Sec-WebSocket-Key") = m_strBase64;
         if (m_strWebSocketProtocol.has_character())
         {
            inheader("Sec-WebSocket-Protocol") = m_strWebSocketProtocol;

         }
         inheader("Sec-WebSocket-Version") = "13";

         if (m_strOrigin.has_character())
         {

            inheader("Origin") = m_strOrigin;

         }


         /*      if (GetUrlPort() != 80 && GetUrlPort() != 443)
         inheader("host") = GetUrlHost() + ":" + as_string(GetUrlPort());
         else
         inheader("host") = GetUrlHost();*/

#ifdef WINRT_SOCKETS

         m_bExpectResponse = true;

         m_bExpectRequest = false;

#endif

         m_bRequestSent = true;
         SendRequest();
      }
      else
      {
         //if (m_memPong.size() > 0 && (m_timeLastSpontaneousPong.elapsed()) > 10000)
         //{
         //
         //   write(m_memPong.data(), m_memPong.size());

         //   m_memPong.set_size(2);

         //   m_memPong.data()[1] = 0;

         //   m_timeLastSpontaneousPong= ::time::now();

         //}

      }

      return ::success;

   }


   void websocket_client::OnLine(const ::scoped_string & scopedstrLine)
   {


      http_client_socket::OnLine(scopedstrLine);

   }


   void websocket_client::OnHeaderComplete()
   {

      int iHttpStatusCode;

      iHttpStatusCode = outattr("http_status_code").as_int();

      string strStatus;

      strStatus = outattr("http_status");

      if (iHttpStatusCode == 101 && strStatus == "Switching Protocols")
      {

         string strUpgrade;

         strUpgrade = outheader("upgrade");

         if (strUpgrade.case_insensitive_order("websocket") == 0)
         {

            string strConnection;

            strConnection = outheader("connection");

            if (strConnection.case_insensitive_order("Upgrade") == 0)
            {

               m_timeLastPing.Now();

               string strAccept;

               strAccept = outheader("sec-websocket-accept");

               string strKey = m_strBase64;

               strKey.trim();

               strKey += "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

               memory mem;

               mem.assign(strKey);

               memory mem2;

               auto psystem = system();

               auto pbase64 = psystem->base64();

               auto pcrypto = psystem->crypto();

               pcrypto->sha1(mem2, mem);

               strKey = pbase64->encode(mem2);

               if (strAccept == strKey)
               {

                  m_bWebSocket = true;

                  m_strWebSocketProtocol = outheader("sec-websocket-protocol");

                  informationf("\n\nnow : websocket\n");

                  if (m_strWebSocketProtocol.has_character())
                  {

                     information("Sec-WebSocket-Protocol: " + m_strWebSocketProtocol + "\n");

                  }

               }

            }

         }

      }

   }

   void websocket_client::OnDataComplete()
   {

   }


   void websocket_client::write(const void * p, ::memsize s)
   {

      synchronous_lock synchronouslock(m_pmutexWebsocketWrite);

      http_client_socket::write(p, s);

   }


   void websocket_client::InitSSLClient()
   {
      //#if defined(HAVE_OPENSSL)
      //      if(m_bTls)
      //      {
      //         InitializeContext("",TLS_client_method());
      //         //m_strTlsHostName = m_host;
      //      }
      //      else
      //      {
      //         InitializeContext("", TLS_client_method());
      //      }
      //#endif
   }



   long websocket_client::cert_common_name_check(const ::string & common_name)
   {

      //#ifdef BSD_STYLE_SOCKETS
      //
      //      int iResult = (int) SSL_get_verify_result(m_psslcontext->m_ssl);
      //
      //#else

      int iResult = 0;

      //#endif


      return iResult;

      //return X509_V_ERR_APPLICATION_VERIFICATION;


   }


   bool websocket_client::send_network_payload(::payload varNetworkPayload)
   {

      string strNetworkPayload;

      varNetworkPayload.get_network_payload(strNetworkPayload, true);

      auto memory = get_client_send_text(strNetworkPayload, true);

      write(memory);

      return !Lost();

   }


   bool websocket_client::send_memory(memory & memoryParameter)
   {

      auto memory = get_client_send_binary(memoryParameter);

      write(memory);

      return !Lost();

   }


   void websocket_client::OnRawData(char * buf, memsize len)
   {

      if (m_bWebSocket)
      {

         //string strLine;

         //strLine.formatf("OnRawData len %d", (uptr)len);

         //str += strLine + "\r\n";

         //informationf("%s", strLine);

         m_memResponse.append(buf, len);

         //unsigned long long uLen = 0;

         //int iOffset = 2;

         while (m_memResponse.size() >= 2)
         {

            // From
            // https://github.com/dhbaird/easywsclient/blob/master/easywsclient.cpp

            unsigned char * data = (unsigned char *)m_memResponse.data(); // peek, but don't consume


#if DEEP_DATA_DEBUG

            string strOut1;

            string strHexa;

            string strChar;

            for (::collection::index i = 0; i < m_memResponse.size(); i++)
            {

               strHexa += ::hex::lower_from(&data[i], 1) + " ";
               if (data[i] == 0)
               {
                  strChar += "NL ";
               }
               else if (data[i] < 10)
               {
                  strChar += "0";
                  strChar += as_string((int)data[i]);
                  strChar += " ";
               }
               else if (data[i] < 32)
               {
                  strChar += as_string((int)data[i]);
                  strChar += " ";
               }
               else if (data[i] >= 128)
               {
                  strChar += "UP ";
               }
               else
               {
                  strChar += string((const_char_pointer )&data[i], 1);
                  strChar += "  ";
               }

            }

            strOut1 += "\n";
            strOut1 += "wsdata:   " + strHexa + "   <--\n";
            strOut1 += "wschar:   " + strChar + "   <--\n..\n.\n";

            information(strOut1);

#endif

            m_fin = (data[0] & 0x80) == 0x80;

            m_opcode = (data[0] & 0x0f);

            m_mask = data[1] & 0x80;

            m_n0 = (data[1] & 0x7f);

            m_header_size = 2;

            if (m_n0 == 126)
            {

               m_header_size += 2;

            }
            else if (m_n0 == 127)
            {

               m_header_size += 8;

            }

            if (m_mask)
            {

               m_header_size += 4;

            }

            zero(m_maskingkey);

            if (m_memResponse.size() < m_header_size)
            {

               return;

            }

            m_i = 0;

            m_iN = -1;

            if (m_n0 < 126)
            {

               m_iN = m_n0;
               m_i = 2;

            }
            else if (m_n0 == 126)
            {

               m_iN = 0;
               m_iN |= ((unsigned long long)data[2]) << 8;
               m_iN |= ((unsigned long long)data[3]) << 0;
               m_i = 4;

            }
            else if (m_n0 == 127)
            {

               m_iN = 0;
               m_iN |= ((unsigned long long)data[2]) << 56;
               m_iN |= ((unsigned long long)data[3]) << 48;
               m_iN |= ((unsigned long long)data[4]) << 40;
               m_iN |= ((unsigned long long)data[5]) << 32;
               m_iN |= ((unsigned long long)data[6]) << 24;
               m_iN |= ((unsigned long long)data[7]) << 16;
               m_iN |= ((unsigned long long)data[8]) << 8;
               m_iN |= ((unsigned long long)data[9]) << 0;
               m_i = 10;

            }

            if (m_mask)
            {

               m_maskingkey[0] = ((unsigned char)data[m_i + 0]);
               m_maskingkey[1] = ((unsigned char)data[m_i + 1]);
               m_maskingkey[2] = ((unsigned char)data[m_i + 2]);
               m_maskingkey[3] = ((unsigned char)data[m_i + 3]);

            }

            memsize iBufSize = m_memResponse.size();

            if (iBufSize < m_header_size + m_iN)
            {

               return; /* Need: ws.header_size+ws.N - rxbuf.size() */

            }

            auto iStart = m_header_size;

            // We got a whole message, now do something with it:
            if (m_opcode == e_opcode::TEXT_FRAME || m_opcode == e_opcode::BINARY_FRAME || m_opcode == e_opcode::CONTINUATION)
            {

               if (m_opcode == e_opcode::CONTINUATION)
               {

                  informationf("test03");

               }

               if (m_mask)
               {

                  for (memsize i = 0; i < m_iN; i++)
                  {

                     data[i + iStart] ^= m_maskingkey[i & 0x3];

                  }

               }

               m_memReceivedData.append(&data[iStart], m_iN);// just feed

               if (m_fin)
               {

                  on_websocket_data(m_memReceivedData.data(), (int)(m_memReceivedData.size()));

                  m_memReceivedData.set_size(0);

               }
               else
               {

                  informationf("ws_buffering");

               }

            }
            else if (m_opcode == e_opcode::PING)
            {

               m_timeLastPing.Now();

               m_eping = ping_sent_ping;

               if (m_mask)
               {

                  for (memsize i = 0; i < m_iN; i++)
                  {

                     //data[m_i + m_header_size] ^= m_maskingkey[m_i & 0x3];
                     data[m_i + i + m_header_size] ^= m_maskingkey[(m_i + i) & 0x3];

                  }

               }

               memory m1(&data[m_header_size], m_iN);

               m_memPong = get_client_send( e_opcode::PONG, m1, true);

               write(m_memPong);

            }
            else if (m_opcode == e_opcode::PONG)
            {

               m_timeLastPong.Now();

               m_eping = ping_pong_received;

            }
            else if (m_opcode == e_opcode::CLOSE)
            {

               SetCloseAndDelete();

            }
            else
            {

               informationf("ERR: Got unexpected WebSocket message.\n");

               SetCloseAndDelete();

            }

            m_memResponse.erase(0, m_iN + m_header_size);

         }

         m_iN = 0;

      }
      else
      {

         http_client_socket::OnRawData(buf, len);

      }

   }


   void websocket_client::on_websocket_data(unsigned char * pdata, int len)
   {

      m_timeLastPong.Now();

      string str((const_char_pointer )pdata, len);

      //::fork(get_app(), [=]()
      //{

      // DO FORK if necessary only in inner loops,
      // taking care of only writing to websocket when it is proper.
      on_websocket_data(str);

      //});



   }

   void websocket_client::on_websocket_data(const ::scoped_string & scopedstr)
   {

   }


   ::memory websocket_client::get_client_send(int fin, memory & memory, bool useMask)
   {

      throw interface_only();

      return {};

   }


   ::memory websocket_client::get_client_send(int fin, const_char_pointer src)
   {
      
      throw interface_only();

      return {};

   }


   ::memory websocket_client::get_client_send_text(const_char_pointer src)
   {

      return get_client_send(0x81, src);

   }


   ::memory websocket_client::get_client_send_binary(memory & memory)
   {

      return get_client_send(0x82, memory, true);

   }
   

   ::memory websocket_client::get_client_send_text(const_char_pointer src, bool bMasked)
   {

      memory m2(src, ansi_len(src));

      return get_client_send(0x81, m2, bMasked);

   }
   

} // namespace sockets



