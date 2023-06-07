#pragma once


CLASS_DECL_APEX string get_file_extension_mime_type(const ::string & strExtension);



namespace networking
{


   using port_t = u16;


   class address;

   
   using address_pointer = ::pointer<address>;


   class application;
   class application_handler;
   class application_socket;


   class email;
   class networking;

   class email_address;


} // namespace networking


namespace netserver
{


   class socket_thread_base;


} // namespace netserver


//inline void __exchange(::stream & s, ::networking::address & address);


//CLASS_DECL_APEX u32 c_inet_addr(const char * src);
//CLASS_DECL_APEX i32 c_inet_pton(i32 af, const char * src, void * dst);
//CLASS_DECL_APEX const char * c_inet_ntop(i32 af, const void * src, char * dst, i32 cnt);
//CLASS_DECL_APEX string c_inet_ntop(i32 af, const void * src);



//CLASS_DECL_APEX string c_gethostbyname(const char * hostname);
//
//CLASS_DECL_APEX string get_file_extension_mime_type(const ::string & strExtension);

//
//#include "byte_order.h"
//



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





