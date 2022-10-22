// Created by camilo on 2021-11-07 11:35 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "application_socket.h"
#include "application.h"
#include "source/app/apex/networking/_networking.h"
#include "source/app/apex/networking/netserver/_netserver.h"
#include "apex/filesystem/filesystem/file_context.h"
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


   void application::initialize(::object* pobject)
   {

      //auto estatus =

      ::object::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void application::create_networking_application()
   {

      //auto estatus =

      __construct(m_psocketthread, __new(::netserver::socket_thread < ::networking::application_socket >()));

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_psocketthread->m_strIp = "127.0.0.1";

      auto pfolder = m_psystem->m_papexsystem->file().resource_folder();

      //if (pfolder)
      //{

      //   auto pfile = pfolder->get_file("sensitive/sensitive/api/localwebserver.cat");

      //   if (pfile)
      //   {

      //      string strCat;

      //      pfile->full_read_string(strCat);

      //      if (strCat)
      //      {

      //         m_psocketthread->m_strCat = "cat://"+strCat;
      //         m_psocketthread->m_strCipherList = "ECDHE-RSA-AES256-SHA384:ECDHE-RSA-AES256-SHA:ECDHE-RSA-AES128-SHA:ECDHE-RSA-RC4-SHA:DHE-RSA-AES256-SHA:DHE-RSA-AES128-SHA:RSA:SHA:3DES:!aNULL:!eNULL:!EXP:!LOW:!MD5:@STRENGTH";
      //         m_psocketthread->m_iSsl = 1;

      //      }


      //   }

      //}


      //      m_psocketthread->m_strCat = "cat://"+m_psystem->m_pacmefile->as_string("C:\\sensitive\\sensitive\\certificate\\localwebserver.app\\localwebserver.cat");
        //    m_psocketthread->m_strCipherList = "ECDHE-RSA-AES256-SHA384:ECDHE-RSA-AES256-SHA:ECDHE-RSA-AES128-SHA:ECDHE-RSA-RC4-SHA:DHE-RSA-AES256-SHA:DHE-RSA-AES128-SHA:RSA:SHA:3DES:!aNULL:!eNULL:!EXP:!LOW:!MD5:@STRENGTH";
          //  m_psocketthread->m_iSsl = 1;

      //if (!

      m_psocketthread->branch();

      //{

      //   return ::error_failed;

      //}

      //fork([this]()
        // {

            //::hyperlink::open_link("http://" + m_psocketthread->m_strIp + ":" + __string(m_psocketthread->m_iPort) + "/");

      //return estatus;

   }


   i32 application::get_current_port()
   {

      return m_psocketthread->m_iConnectPort;

   }



   i32 application::wait_get_current_port(const ::duration& duration)
   {

      ::duration durationStart;

      durationStart.Now();

      while (get_current_port() < 0 && durationStart.elapsed() < duration)
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


   ::e_status application::on_html_response(::string & strHtml, const ::string& strUrl, const ::property_set& setPost)
   {

      string strRequestScript = m_psystem->url()->get_script(strUrl);

      string strServer = m_psystem->url()->get_server(strUrl);

      if (strServer.is_empty())
      {

         auto iFind = strUrl.find(":/");

         if (iFind > 0)
         {

            strRequestScript = strUrl.Mid(iFind + 1);

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
               || strRequestScript.begins_ci(strScript + "/")
               || strRequestScript.begins_ci(strScript + "?"))
            {

               auto estatus = phandler->on_html_response(strHtml, strUrl, setPost);

               if (estatus.succeeded())
               {

                  return estatus;

               }

            }

         }

      }

      auto psystem = m_psystem;

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
      strHtml += "&lt;3TBS - ∞ - " + pdatetime->international().get_date_time() + "- +∞ - CA2(THWOASONE)";
      strHtml += "</body>";
      strHtml += "</html>";

      return ::success;

   }


} // namespace networking



