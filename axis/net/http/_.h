#pragma once


namespace account
{
   
   
   class user;

   
} // namespace account


namespace http
{

   
   class session;


} // namespace http


typedef LPVOID HINTERNET;


class tinyjs;

//class tinyjs;


#define PRhttpget PRId64

#define __prhttpget "http_get_%" PRhttpget "> "

namespace account
{

   class user;

} // namespace account


namespace sockets
{

   class http_socket;
   class http_client_socket;
   class http_session;
   class http_tunnel;


} // namespace sockets


#include "cookie.h"


#include "form.h"
#include "transaction.h"
#include "request.h"
#include "response.h"



#include "cookie.h"

#include "status.h"

#include "signal.h"

#include "listener.h"

#include "context.h"

//#include "application.h"

//#include "system.h"



