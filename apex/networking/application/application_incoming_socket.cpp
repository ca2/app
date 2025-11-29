// cs<3tbs!! 2023-12-16 04:19 20-11-28 21:16 BRT
#include "framework.h"
#include "application_incoming_socket.h"
#include "application_socket.h"
#include "acme/parallelization/happening.h"
#include "acme/filesystem/file/memory_file.h"
#include "apex/platform/application.h"


namespace networking
{


   application_incoming_socket::application_incoming_socket()
   {

   }


   application_incoming_socket::~application_incoming_socket()
   {

   }
   
   
   void application_incoming_socket::on_initialize_particle()
   {

      ::netserver::incoming_socket::on_initialize_particle();

      m_typeAttendSocket = typeid(::networking::application_socket );

   }


   //void application_socket::on_send_response()
   //{

   //   auto papp = get_app();

   //   string strUrl;

   //   strUrl = request().a_url();

   //   ::property_set setPost;

   //   setPost = request().form().post();

   //   string strHtml;

   //   auto estatus = papp->on_html_response(strHtml, strUrl, setPost);

   //   response().file()->write(strHtml);

   //}


} // namespace networking



