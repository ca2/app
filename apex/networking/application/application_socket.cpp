// cs<3tbs!! 2020-11-28 21:16 BRT
#include "framework.h"
#include "application_socket.h"
#include "acme/parallelization/happening.h"
#include "application_incoming_socket.h"
#include "acme/filesystem/file/memory_file.h"
#include "apex/platform/application.h"
#include "apex/networking/application/application.h"


namespace networking
{


   application_socket::application_socket()
   {

   }


   application_socket::~application_socket()
   {

   }


   void application_socket::on_set_parent_socket()
   {

      ::cast < ::networking::application_incoming_socket > papplicationincomingsocket = get_parent_socket()->base_socket_interface();

      if(papplicationincomingsocket)
      {

         m_pnetworkingapplication = papplicationincomingsocket->m_pnetworkingapplication;

      }

   }


   void application_socket::on_send_response()
   {

      auto pnetworkingapplication = m_pnetworkingapplication;

      string strUrl;

      strUrl = request().a_url();

      ::property_set setPost;

      setPost = request().form().post();

      string strHtml;

      auto estatus = pnetworkingapplication->on_html_response(this, strHtml, strUrl, setPost);

      response().file()->write(strHtml);

   }


} // namespace networking



