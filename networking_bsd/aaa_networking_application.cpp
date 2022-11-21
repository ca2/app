// Created by camilo on 2021-11-07 11:35 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "netserver/_netserver.h"
#include "_networking.h"
#include "networking_application_socket.h"


networking_application::networking_application()
{

}


networking_application::~networking_application()
{


}


void networking_application::initialize(::particle * pparticle)
{

   //auto estatus = 
   
   ::object::initialize(pparticle);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


void networking_application::create_networking_application()
{

   //auto estatus = 
   
   __construct(m_psocketthread, __new(::netserver::socket_thread < networking_application_socket >()));

   //if (!estatus)
   //{

   //   return estatus;

   //}

   m_psocketthread->m_strIp = "127.0.0.1";
   
   //auto pfolder = file()->resource_folder();

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


   //      m_psocketthread->m_strCat = "cat://"+acmefile()->as_string("C:\\sensitive\\sensitive\\certificate\\localwebserver.app\\localwebserver.cat");
     //    m_psocketthread->m_strCipherList = "ECDHE-RSA-AES256-SHA384:ECDHE-RSA-AES256-SHA:ECDHE-RSA-AES128-SHA:ECDHE-RSA-RC4-SHA:DHE-RSA-AES256-SHA:DHE-RSA-AES128-SHA:RSA:SHA:3DES:!aNULL:!eNULL:!EXP:!LOW:!MD5:@STRENGTH";
       //  m_psocketthread->m_iSsl = 1;

   //if (!
   
   m_psocketthread->branch();

   //{

   //   return ::error_failed;

   //}

   //fork([this]()
     // {

         //::hyperlink::open_link("http://" + m_psocketthread->m_strIp + ":" + as_string(m_psocketthread->m_iPort) + "/");

   //return estatus;

}


i32 networking_application::get_current_port()
{

   return m_psocketthread->m_iConnectPort;

}



i32 networking_application::wait_get_current_port(const ::duration& duration)
{

   ::duration durationStart;

   durationStart.Now();

   while (get_current_port() < 0 && durationStart.elapsed() < duration)
   {

      preempt(300_ms);

   }

   return get_current_port();

}


void networking_application::add_handler(const ::string& strPrefix, networking_application_handler* phandler)
{

   if (::is_null(phandler))
   {

      throw ::exception(error_failed);

   }

   auto& phandlerMapped = m_maphandler[strPrefix];

   phandlerMapped = phandler;

   //return ::success;

}


::e_status networking_application::on_html_response(::string & strHtml, const ::string& strUrl, const ::property_set& setPost)
{

   string strRequestScript = acmesystem()->url()->get_script(strUrl);

   for (auto& assoc : m_maphandler)
   {

      auto & strFolder = assoc.m_element1;

      auto & phandler = assoc.m_element2;

      if (strFolder.has_char() && phandler)
      {

         string strScript = "/" + strFolder;

         if (strRequestScript == strScript || strRequestScript.begins_ci(strScript + "/"))
         {

            auto estatus = phandler->on_html_response(strHtml, strUrl, setPost);

            if (estatus.succeeded())
            {

               return estatus;

            }

         }

      }

   }

   auto psystem = acmesystem();

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



