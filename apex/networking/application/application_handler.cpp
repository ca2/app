// Created by camilo on 2021-11-07 13:37 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "application_handler.h"
#include "acme/platform/system.h"
#include "acme/primitive/datetime/datetime.h"


namespace networking
{


   application_handler::application_handler()
   {

   }


   application_handler::~application_handler()
   {


   }


   ::e_status application_handler::on_html_response(string & strHtml, const ::string& strUrl, const ::property_set& setPost)
   {

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


} // namespace networking



