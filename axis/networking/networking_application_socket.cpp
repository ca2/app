// cs<3tbs!! 2020-11-28 21:16 BRT
#include "framework.h"
#include "netserver/_netserver.h"
#include "_networking.h"


networking_application_socket::networking_application_socket()
{

}


networking_application_socket::~networking_application_socket()
{

}


void networking_application_socket::on_send_response()
{

   auto papplication = get_application()->m_paxisapplication;

   string strUrl;

   strUrl = request().a_url();

   property_set setPost;

   setPost = request().form().post();

   string strHtml;
      
   auto estatus = papplication->on_html_response(strHtml, strUrl, setPost);

   response().file()->write(strHtml);

}


