////////////////////////////////////////////////////////////////////////////////
//
// From David J. Kruglinski (Inside Visual C++).
//
////////////////////////////////////////////////////////////////////////////////

// erased baseclass CObject
// erased baseclass CException
// erased all LPCTSTR char_pointer 
// _select only defined to avoid compiler warning in WIN32
// make it run on linux

#pragma once


////#include "acme/exception/exception.h"
#include "apex/networking/sockets/basic/tcp_socket.h"
//#ifdef WIN32
//#ifdef _WINSOCKAPI_
//#ifndef _WINSOCK2API_
//// NOTICE: In Microsoft Visual Studio you can add the header 'winsock2.h" to
////         "Configuration --> Properties --> C/C++ --> Advanced --> Forced Include File"
//#pragma message("\nIt is recommended to include 'winsock2.h' instead of 'winsock.h'\n")
//#endif
//#else
//#include <winsock2.h>
//#endif
//#elif defined(unix)
//#include <sys/socket.h>
//#include <arpa/inet.h>   // needed for inet_ntoa and inet_addr
//#include <netdb.h>       // needed for gethostbyname and gethostbyaddr
//#include <errno.h>
//#endif


#if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__) || defined(FREEBSD) || defined(OPENBSD) || defined(OPENBSD)

#define SOCKADDR sockaddr

#endif


namespace sockets
{


   class CLASS_DECL_APEX transfer_socket_exception :
      public ::exception
   {
   public:

      ::i32     m_nError;



      transfer_socket_exception(const ::scoped_string & scopedstrMessage);
      virtual ~transfer_socket_exception();

   };

   class CLASS_DECL_APEX transfer_socket :
      virtual public tcp_socket
   {
   public:


      memory_file_pointer    m_pmemoryfile;


      transfer_socket();
      ~transfer_socket() override;

      //::i32  send_datagram(const_char_pointer pch, ::i32 nSize, const SOCKADDR * psa, ::i32 nSecs);
      //::i32  receive_datagram(char_pointer pch, ::i32 nSize, SOCKADDR * psa, ::i32 nSecs);
      bool check_readability(::i32 nSecsPatience); // const
      bool check_writability(::i32 nSecsPatience); // const


   };

   class CLASS_DECL_APEX read_socket :
      virtual public transfer_socket
   {
   public:


      read_socket();
      virtual ~read_socket();



      virtual void on_read(const void * pdata, iptr n);



   };


   class CLASS_DECL_APEX write_socket :
      virtual public transfer_socket
   {
   public:


      write_socket();
      virtual ~write_socket();

      virtual void OnWrite();

   };


   //class CLASS_DECL_APEX http_transfer_socket :
   //   virtual public transfer_socket
   //{
   //public:

   //   enum { nSizeRecv = 1000 }; // maximum receive buffer i32_size (> hdr line length)


   //   char_pointer m_pReadBuf; // read buffer
   //   ::i32    m_nReadBuf; // number of bytes in the read buffer


   //   http_transfer_socket();
   //   ~http_transfer_socket();

   //   ::i32 read_http_header_line(char_pointer pch, ::i32 nSize, ::i32 nSecs);
   //   ::i32 read_http_response(char_pointer pch, ::i32 nSize, ::i32 nSecs);


   //};


} // namespace sockets2





