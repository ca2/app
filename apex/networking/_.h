#pragma once


namespace networking
{

   using port_t = unsigned short;

   class address;

   
   using address_pointer = ::pointer<address>;


   class application;
   class application_handler;
   class application_socket;
   class application_incoming_socket_thread;


   class email;
   class networking;

   class email_address;


} // namespace networking


namespace netserver
{


   class socket_thread;


} // namespace netserver


//inline void __exchange(::stream & s, ::networking::address & address);


//CLASS_DECL_APEX unsigned int c_inet_addr(const char * src);
//CLASS_DECL_APEX int c_inet_pton(int af, const char * src, void * dst);
//CLASS_DECL_APEX const char * c_inet_ntop(int af, const void * src, char * dst, int cnt);
//CLASS_DECL_APEX string c_inet_ntop(int af, const void * src);



//CLASS_DECL_APEX string c_gethostbyname(const char * hostname);
//
//CLASS_DECL_APEX string get_file_extension_mime_type(const ::scoped_string & scopedstrExtension);

//
//#include "byte_order.h"
//


#ifdef WINDOWS
using socket_id = ::uptr; 
#else
using socket_id = int;
#endif


#include "http/_.h"


#include "sockets/_.h"






//#include "ip_enum.h"
//#include "url_domain.h"


//#include "email_address.h"
//#include "email.h"


//#include "port_forward.h"


//#include "url.h"
//#include "url_department.h"
//#include "email_department.h"




//class networking_application_socket;


//#include "apex/networking/netserver/_.h"


//#include "networking_application_handler.h"


///#include "networking_application.h"





