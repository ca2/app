////////////////////////////////////////////////////////////////////////////////
//
// From David J. Kruglinski (Inside Visual C++).
// Modifications by Thomas Oswald (make compatible to BSD sockets) //+#
//
////////////////////////////////////////////////////////////////////////////////

// transfer_socket_exception, transfer_socket, http_transfer_socket

#include "framework.h"
#include "apex/networking/sockets/_sockets.h"

#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

#define TIMEVAL timeval

#endif




namespace sockets
{


   int get_error()
   {

#ifdef WINDOWS

      return WSAGetLastError();

#else

      return errno;

#endif

   }


   ///////////////////////////////////////////////////////////////////////////////////////
   //************************* Class transfer_socket_exception **************************//
   ///////////////////////////////////////////////////////////////////////////////////////

   transfer_socket_exception::transfer_socket_exception(const char * pszMessage) :
      m_nError(get_error()),
      ::exception::exception(pszMessage)
   {
   }

   transfer_socket_exception::~transfer_socket_exception()
   {
   }


   //bool transfer_socket_exception::GetErrorMessage(string & strError, P::u32 /*pnHelpContext = nullptr*/)
   //{
   //   if (m_nError == 0)
   //   {
   //      strError.Format("%s error", m_strMessage);
   //   }
   //   else
   //   {
   //      strError.Format("%s error 0x%08x", m_strMessage, m_nError);
   //   }
   //   return true;
   //}

   //string transfer_socket_exception::GetErrorMessage(P::u32 /*pnHelpContext = nullptr*/)
   //{
   //   string str;
   //   GetErrorMessage(str);
   //   return str;
   //}

   ///////////////////////////////////////////////////////////////////////////////////////
   //******************************** Class transfer_socket ****************************//
   ///////////////////////////////////////////////////////////////////////////////////////


   transfer_socket::transfer_socket()
      //:
      //::object(&handler),
      //base_socket(handler),
      //socket(handler),
      //stream_socket(handler),
      //tcp_socket(handler)
   {

      defer_create_mutex();

      //defer_initialize_winsock();

   }

   transfer_socket::~transfer_socket()
   {

   }

   //void transfer_socket::cleanup()
   //{
   //   // doesn't __throw( an exception because it's called in a catch block
   //   if (m_hSocket == INVALID_SOCKET)
   //      return;

   //   VERIFY(closesocket(m_hSocket) != SOCKET_ERROR);

   //   m_hSocket = INVALID_SOCKET;
   //}

   //void transfer_socket::create(int nType /* = SOCK_STREAM */)
   //{
   //   ASSERT(m_hSocket == INVALID_SOCKET);
   //   if ((m_hSocket = socket(AF_INET, nType, 0)) == INVALID_SOCKET)
   //   {
   //      __throw(transfer_socket_exception(_T("Create")));
   //   }
   //}

   //void transfer_socket::bind(LPCSOCKADDR psa) // const
   //{
   //   ASSERT(psa != nullptr);
   //   ASSERT(m_hSocket != INVALID_SOCKET);
   //   if (::bind(m_hSocket, psa, sizeof(SOCKADDR)) == SOCKET_ERROR)
   //   {
   //      __throw(transfer_socket_exception(_T("Bind")));
   //   }
   //}

   //void transfer_socket::listen() // const
   //{
   //   ASSERT(m_hSocket != INVALID_SOCKET);
   //   if (::listen(m_hSocket, 5) == SOCKET_ERROR)
   //   {
   //      __throw(transfer_socket_exception(_T("Listen")));
   //   }
   //}

   //bool transfer_socket::accept(itransfer_socket& sConnect, LPSOCKADDR psa) // const
   //{
   //   ASSERT(psa != nullptr);
   //   ASSERT(m_hSocket != INVALID_SOCKET);
   //   ASSERT(sConnect.operator SOCKET() == INVALID_SOCKET);

   //   // ATTENTION: dynamic_cast would be better (and then checking against nullptr)
   //   //            RTTI must be enabled to use dynamic_cast //+#
   //   transfer_socket* pConnect = dynamic_cast<transfer_socket*>(&sConnect);

   //   socklen_t nLengthAddr = sizeof(SOCKADDR);
   //   pConnect->m_hSocket = ::accept(m_hSocket, psa, &nLengthAddr);

   //   if (pConnect->operator SOCKET() == INVALID_SOCKET)
   //   {
   //      // no exception if the listen was canceled
   //      if (WSAGetLastError() != WSAEINTR)
   //      {
   //         __throw(transfer_socket_exception(_T("Accept")));
   //      }
   //      return false;
   //   }
   //   return true;
   //}

   //void transfer_socket::close()
   //{
   //   if (m_hSocket != INVALID_SOCKET && closesocket(m_hSocket) == SOCKET_ERROR)
   //   {
   //      // should be OK to close if closed already
   //      __throw(transfer_socket_exception(_T("Close")));
   //   }
   //   m_hSocket = INVALID_SOCKET;
   //}

   //void transfer_socket::connect(LPCSOCKADDR psa) // const
   //{
   //   ASSERT(psa != nullptr);
   //   ASSERT(m_hSocket != INVALID_SOCKET);
   //   // should timeout by itself
   //   if (::connect(m_hSocket, psa, sizeof(SOCKADDR)) == SOCKET_ERROR)
   //   {
   //      __throw(transfer_socket_exception(_T("Connect")));
   //   }
   //}

   //int transfer_socket::write(const void* pch, int nSize, int nSecs) // const
   //{

   //   ::sockets::tcp_socket::write(pch, nSize);

   //   return nSize;

   //}

   //int transfer_socket::send(const char * pch, int nSize, int nSecs) // const
   //{
   //   //ASSERT(pch != nullptr);
   //   //ASSERT(m_hSocket != INVALID_SOCKET);

   //   // returned value will be less than nSize if client cancels the reading
   //   /*fd_set fd;
   //   FD_ZERO(&fd);
   //   FD_SET(m_hSocket, &fd);
   //   TIMEVAL tv = { nSecs, 0 };*/

   //   m_handler.select();
   //   //if (_select(m_hSocket + 1, nullptr, &fd, nullptr, &tv) == 0)
   //   //{
   //   //   __throw(transfer_socket_exception(_T("Send timeout")));
   //   //}

   //   const int nBytesSent = send(pch, nSize);
   //   if (nBytesSent == SOCKET_ERROR)
   //   {
   //      __throw(transfer_socket_exception(_T("Send")));
   //   }

   //   return nBytesSent;
   //}

   bool transfer_socket::check_readability(int nSecsPatience) // const
   {

      fd_set fd;
      FD_ZERO(&fd);
      FD_SET(GetSocket(), &fd);
      TIMEVAL tv = { nSecsPatience, 0 };

      // static_cast is necessary to avoid compiler warning under WIN32;
      // This is no problem because the first parameter is included only
      // for compatibility with Berkeley sockets.
      const int iRet = ::select((int) (GetSocket() + 1), &fd, nullptr, nullptr, &tv);

      if (iRet == SOCKET_ERROR)
      {
         __throw(transfer_socket_exception("Socket Error"));
      }

      return iRet == 1;
   }

   bool transfer_socket::check_writability(int nSecsPatience) // const
   {

      fd_set fd;
      FD_ZERO(&fd);
      FD_SET(GetSocket(), &fd);
      TIMEVAL tv = { nSecsPatience, 0 };

      // static_cast is necessary to avoid compiler warning under WIN32;
      // This is no problem because the first parameter is included only
      // for compatibility with Berkeley sockets.
      const int iRet = ::select((int) (GetSocket() + 1), nullptr, &fd, nullptr, &tv);

      if (iRet == SOCKET_ERROR)
      {
         __throw(transfer_socket_exception("Socket Error"));
      }

      return iRet == 1;
   }




































   read_socket::read_socket() //:
      //::object(&handler),
      //base_socket(handler),
      //socket(handler),
      //stream_socket(handler),
      //tcp_socket(handler),
      //transfer_socket(handler)
   {

      //defer_initialize_winsock();

   }

   read_socket::~read_socket()
   {

   }


   void read_socket::on_read(const void * pdata, iptr n)
   {

      synchronous_lock synchronouslock(mutex());

      u8 * pbuf = (u8 *) pdata;

      m_file.seek_to_end();

      m_file.write(pbuf, n);

   }


   //int transfer_socket::receive(void * pch, int nSize, int nSecs) // const
   //{

   //   u8 * point = (u8 *)pch;

   //   int nBytesReceived = 0;

   //   ::u32 tickStart= ::millis::now();

   //   int iRead = 0;

   //   while (nSize - nBytesReceived > 0)
   //   {

   //      if (tickStart.elapsed() > nSecs * 1000)
   //      {

   //         break;

   //      }

   //      {

   //         synchronous_lock synchronouslock(mutex());

   //         iRead = m_file.erase_begin(&point[nBytesReceived], nSize - nBytesReceived);

   //      }

   //      nBytesReceived += iRead;

   //      if (nBytesReceived > 0)
   //      {

   //         break;

   //      }

   //      if (!IsDetached())
   //      {

   //         if (!m_handler.contains(this))
   //         {

   //            break;

   //         }

   //         m_handler.select(1, 0);

   //      }

   //   }

   //   return nBytesReceived;

   //}














   write_socket::write_socket() 
      //:
      //::object(&handler),
      //base_socket(handler),
      //socket(handler),
      //stream_socket(handler),
      //tcp_socket(handler),
      //transfer_socket(handler)
   {

      //defer_initialize_winsock();

   }

   write_socket::~write_socket()
   {
      //      cleanup();
      //#ifdef WIN32
      //      WSACleanup();
      //#endif
   }


   void write_socket::OnWrite()
   {

      synchronous_lock synchronouslock(mutex());

      write(m_file.get_data(), (memsize)m_file.get_size());

   }


   int transfer_socket::receive_datagram(char* pch, int nSize, SOCKADDR * psa, int nSecs) // const
   {

      if (!check_readability(nSecs))
      {

         __throw(transfer_socket_exception("Receive timeout"));

      }

      // input buffer should be big enough for the entire datagram
      socklen_t nFromSize = sizeof(SOCKADDR);
      const int nBytesReceived = (int) (::recvfrom(GetSocket(), pch, nSize, 0, psa, &nFromSize));

      if (nBytesReceived == SOCKET_ERROR)
      {
         __throw(transfer_socket_exception("ReceiveDatagram"));
      }

      return nBytesReceived;
   }

   int transfer_socket::send_datagram(const char* pch, int nSize, const SOCKADDR * psa, int nSecs) // const
   {

      if (!check_writability(nSecs))
      {

         __throw(transfer_socket_exception("Send timeout"));
      }

      const int nBytesSent = (int) (::sendto(GetSocket(), pch, nSize, 0, psa, sizeof(SOCKADDR)));
      if (nBytesSent == SOCKET_ERROR)
      {
         __throw(transfer_socket_exception("SendDatagram"));
      }

      return nBytesSent;
   }



   /////////////////////////////////////////////////////////////////////////////////////////
   ////**************************** Class http_transfer_socket ****************************//
   /////////////////////////////////////////////////////////////////////////////////////////

   //http_transfer_socket::http_transfer_socket() :
   //   ::object(handler.get_application()),
   //   base_socket(handler),
   //   socket(handler),
   //   stream_socket(handler),
   //   tcp_socket(handler),
   //   transfer_socket(handler)
   //{
   //   m_pReadBuf = new char[nSizeRecv];
   //   m_nReadBuf = 0;
   //}

   //http_transfer_socket::~http_transfer_socket()
   //{
   //   delete[] m_pReadBuf;
   //}

   //int http_transfer_socket::read_http_header_line(char* pch, int nSize, int nSecs)
   //   // reads an entire header line through CRLF (or socket close)
   //   // inserts zero string terminator, object maintains a buffer
   //{
   //   int       nBytesThisTime = m_nReadBuf;
   //   ptrdiff_t nLineLength = 0;
   //   char*     pch1 = m_pReadBuf;
   //   char*     pch2 = nullptr;

   //   do
   //   {
   //      // look for lf (assume preceded by color32)
   //      if ((pch2 = (char *)memchr(pch1, '\n', nBytesThisTime)) != nullptr)
   //      {
   //         ASSERT((pch2) > m_pReadBuf);
   //         ASSERT(*(pch2 - 1) == '\r');
   //         nLineLength = (pch2 - m_pReadBuf) + 1;
   //         if (nLineLength >= nSize)
   //            nLineLength = nSize - 1;
   //         ::memcpy_dup(pch, m_pReadBuf, nLineLength); // copy the line to caller
   //         m_nReadBuf -= static_cast<unsigned int>(nLineLength);
   //         __memmov(m_pReadBuf, pch2 + 1, m_nReadBuf); // shift remaining characters left
   //         break;
   //      }
   //      pch1 += nBytesThisTime;
   //      nBytesThisTime = receive(m_pReadBuf + m_nReadBuf, nSizeRecv - m_nReadBuf, nSecs);
   //      if (nBytesThisTime <= 0)
   //      { // sender closed socket or line longer than buffer
   //         __throw(transfer_socket_exception(_T("ReadHeaderLine")));
   //      }
   //      m_nReadBuf += nBytesThisTime;
   //   } while (true);

   //   *(pch + nLineLength) = _T('\0');

   //   return static_cast<unsigned int>(nLineLength);
   //}

   //// reads remainder of a transmission through buffer full or socket close
   //// (assume headers have been read already)
   //int http_transfer_socket::read_http_response(char* pch, int nSize, int nSecs)
   //{
   //   int nBytesToRead, nBytesThisTime, nBytesRead = 0;

   //   if (m_nReadBuf > 0)
   //   { // copy anything already in the recv buffer
   //      ::memcpy_dup(pch, m_pReadBuf, m_nReadBuf);
   //      pch += m_nReadBuf;
   //      nBytesRead = m_nReadBuf;
   //      m_nReadBuf = 0;
   //   }
   //   do
   //   { // now pass the rest of the data directly to the caller
   //      nBytesToRead = std::minimum(static_cast<int>(nSizeRecv), nSize - nBytesRead);
   //      nBytesThisTime = receive(pch, nBytesToRead, nSecs);
   //      if (nBytesThisTime <= 0)
   //         break; // sender closed the socket
   //      pch += nBytesThisTime;
   //      nBytesRead += nBytesThisTime;
   //   } while (nBytesRead <= nSize);

   //   return nBytesRead;
   //}


   //__pointer(transfer_socket) create_default_transfer_socket()
   //{

   //   return new transfer_socket(handler);

   //}


} // namespace sockets2





