// cs<3tbs!! 2020-11-28 21:16 BRT
#include "framework.h"
#include "source/app/apex/networking/netserver/_netserver.h"
#include "source/app/apex/networking/_networking.h"
#include "networking_application_socket.h"
#include "acme/filesystem/file/memory_file.h"
#include "apex/platform/application.h"


networking_application_socket::networking_application_socket()
{

}


networking_application_socket::~networking_application_socket()
{

}


void networking_application_socket::on_send_response()
{

   auto papp = get_app()->m_papexapplication;

   string strUrl;

   strUrl = request().a_url();

   property_set setPost;

   setPost = request().form().post();

   string strHtml;
      
   auto estatus = papp->on_html_response(strHtml, strUrl, setPost);

   response().file()->write(strHtml);

}


