// Created by camilo on 2021-11-07 11:35 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "application_incoming_socket.h"
#include "application_socket.h"
#include "application.h"
////#include "acme/exception/exception.h"
#include "acme/primitive/primitive/url.h"
#include "acme/primitive/datetime/datetime.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/networking/netserver/incoming_socket_thread.h"
#include "apex/platform/application.h"
#include "apex/platform/system.h"


namespace networking
{


   application::application()
   {

   }


   application::~application()
   {


   }


   void application::initialize(::particle * pparticle)
   {

      //auto estatus =

      ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void application::create_networking_application()
   {

      //      auto

      factory()->add_factory_item < ::networking::application_socket>();
      factory()->add_factory_item < ::networking::application_incoming_socket>();

      m_psocketthread = __create_new< ::netserver::incoming_socket_thread >();

      //m_psocketthread->m_typeIncomingSocket = ::type<::networking::application_socket>();

      m_psocketthread->m_typeIncomingSocket = ::type<::networking::application_incoming_socket>();

      m_psocketthread->m_strIp = "127.0.0.1";

      if (m_strHostname.has_char())
      {

         m_psocketthread->m_strCat = "matter://certificate/" + m_strHostname + ".cat";

      }

      m_psocketthread->m_iPortMinimum = m_iPortStart;

      m_psocketthread->m_iPortMaximum = m_iPortEnd;

      auto pfolder = file()->resource_folder();

      m_psocketthread->branch();

   }


   i32 application::get_current_port()
   {

      auto iConnectPort = m_psocketthread->m_iConnectPort;

      return iConnectPort;

   }



   i32 application::wait_get_current_port(const class time & time)
   {

      class ::time timeStart;

      timeStart.Now();

      while (get_current_port() <= 0 && timeStart.elapsed() < time)
      {

         preempt(300_ms);

      }

      return get_current_port();

   }


   void application::add_handler(const ::string& strPrefix, ::networking::application_handler* phandler)
   {

      if (::is_null(phandler))
      {

         throw ::exception(error_failed);

      }

      auto& phandlerMapped = m_maphandler[strPrefix];

      phandlerMapped = phandler;

      //return ::success;

   }


   ::e_status application::on_html_response(::networking::application_socket * psocket, ::string & strHtml, const ::string& strUrl, const ::property_set& setPost)
   {

      string strRequestScript = system()->url()->get_script(strUrl);

      string strServer = system()->url()->get_server(strUrl);

      if (strServer.is_empty())
      {

         auto iFind = strUrl.find_index(":/");

         if (iFind > 0)
         {

            strRequestScript = strUrl(iFind + 1);

         }

      }

      for (auto& assoc : m_maphandler)
      {

         auto & strFolder = assoc.m_element1;

         auto & phandler = assoc.m_element2;

         if (strFolder.has_char() && phandler)
         {

            string strScript = "/" + strFolder;

            if (strRequestScript == strScript
               || strRequestScript.case_insensitive_begins(strScript + "/")
               || strRequestScript.case_insensitive_begins(strScript + "?"))
            {

               auto estatus = phandler->on_html_response(psocket, strHtml, strUrl, setPost);

               if (estatus.succeeded())
               {

                  return estatus;

               }

            }

         }

      }

      auto psystem = system();

      auto pdatetime = psystem->datetime();

      strHtml += "<html>";
      strHtml += "<head>";
      strHtml += "<meta charset=\"UTF-8\">";
      // <from https://thomasbs.com/ <3tbs!!>
      strHtml += "<link href=\"https://fonts.googleapis.com/css?family=Fira+Code&display=swap\" rel=\"stylesheet\">";
      // </from https://thomasbs.com/ <3tbs!!>
      strHtml += "</head>";
      strHtml += "<body style=\"font-family:'Fira Code', monospace;\">";
      strHtml += "<h1>";
      strHtml += "🌌 🌍 [ ca2/C++/Windows ] Creating Simple Local Webserver";
      strHtml += "</h1>";
      strHtml += "<h4><a href=\"https://ca2.software/camilo\">cs</a><a href=\"https://ca2.io\">&lt;3</a><a href=\"https://thomasbs.com/\">tbs</a>!!</h4>";
      strHtml += "&lt;3TBS - InfinityUnicodeCharacter - " + pdatetime->international().get_date_time() + "- +InfinityUnicodeCharacter - CA2(THWOASONE)";
      strHtml += "</body>";
      strHtml += "</html>";

      return ::success;

   }


} // namespace networking



