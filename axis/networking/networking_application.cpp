// Created by camilo on 2021-11-07 11:35 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "netserver/_netserver.h"
#include "_networking.h"


networking_application::networking_application()
{

   m_iPort = 10009;

}


networking_application::~networking_application()
{


}


::e_status networking_application::initialize(::object* pobject)
{

   auto estatus = ::object::initialize(pobject);

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}


::e_status networking_application::create_networking_application()
{

   auto estatus = __compose(m_psocketthread, __new(::netserver::socket_thread < networking_application_socket >()));

   if (!estatus)
   {

      return estatus;

   }

   m_psocketthread->m_strIp = "127.0.0.1";
   m_psocketthread->m_iPort = m_iPort;
   //      m_psocketthread->m_strCat = "cat://"+m_psystem->m_pacmefile->as_string("C:\\sensitive\\sensitive\\certificate\\localwebserver.app\\localwebserver.cat");
     //    m_psocketthread->m_strCipherList = "ECDHE-RSA-AES256-SHA384:ECDHE-RSA-AES256-SHA:ECDHE-RSA-AES128-SHA:ECDHE-RSA-RC4-SHA:DHE-RSA-AES256-SHA:DHE-RSA-AES128-SHA:RSA:SHA:3DES:!aNULL:!eNULL:!EXP:!LOW:!MD5:@STRENGTH";
       //  m_psocketthread->m_iSsl = 1;

   if (!m_psocketthread->branch())
   {

      return ::error_failed;

   }

   //fork([this]()
     // {

         //::hyperlink::open_link("http://" + m_psocketthread->m_strIp + ":" + __string(m_psocketthread->m_iPort) + "/");

   return estatus;

}


string networking_application::on_html_response(const ::string& strUrl, const ::property_set& setPost)
{

   string strRequestScript = m_psystem->url()->get_script(strUrl);

   for (auto& assoc : m_mapnetworkingapplicationhandler)
   {

      auto strFolder = assoc.m_element1;

      auto phandler = assoc.m_element2;

      if (phandler && strFolder.has_char())
      {

         string strScript = "/" + strFolder;

         string strScriptPrefix = strScript + "/";

         if (strRequestScript == strScript || strRequestScript.begins(strScriptPrefix))
         {

            return phandler->on_html_response(strUrl, setPost);

         }

      }

   }

   string strHtml;

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

   return strHtml;

}



