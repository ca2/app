////////////////////////////////////////////////////////////////////////////////
//
// From David J. Kruglinski (Inside Visual C++).
//
////////////////////////////////////////////////////////////////////////////////

// removed baseclass CObject
// removed baseclass CException
// removed all LPCTSTR char *
// _select only defined to avoid compiler warning in WIN32
// make it run on linux

#pragma once


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


#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

#define SOCKADDR sockaddr

#endif


namespace sockets
{


   class CLASS_DECL_APEX transfer_socket_exception :
      public ::exception::exception
   {
   public:

      int     m_nError;



      transfer_socket_exception(const char * pszMessage);
      virtual ~transfer_socket_exception();

   };

   class CLASS_DECL_APEX transfer_socket :
      virtual public tcp_socket
   {
   public:


      memory_file                   m_file;


      transfer_socket(::sockets::base_socket_handler & handler);
      virtual ~transfer_socket();

      int  send_datagram(const char* pch, int nSize, const SOCKADDR * psa, int nSecs);
      int  receive_datagram(char* pch, int nSize, SOCKADDR * psa, int nSecs);
      bool check_readability(int nSecsPatience); // const
      bool check_writability(int nSecsPatience); // const


   };

   class CLASS_DECL_APEX read_socket :
      virtual public transfer_socket
   {
   public:


      read_socket(::sockets::base_socket_handler & handler);
      virtual ~read_socket();



      virtual void on_read(const void * pdata, iptr n);



   };


   class CLASS_DECL_APEX write_socket :
      virtual public transfer_socket
   {
   public:


      write_socket(::sockets::base_socket_handler & handler);
      virtual ~write_socket();

      virtual void OnWrite();

   };


   //class CLASS_DECL_APEX http_transfer_socket :
   //   virtual public transfer_socket
   //{
   //public:

   //   enum { nSizeRecv = 1000 }; // max receive buffer size_i32 (> hdr line length)


   //   char*  m_pReadBuf; // read buffer
   //   int    m_nReadBuf; // number of bytes in the read buffer


   //   http_transfer_socket(base_socket_handler & handler);
   //   ~http_transfer_socket();

   //   int read_http_header_line(char* pch, int nSize, int nSecs);
   //   int read_http_response(char* pch, int nSize, int nSecs);


   //};


} // namespace sockets2





