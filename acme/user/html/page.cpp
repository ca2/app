// Created by camilo on 2026-10-28 18:40:53 BRT <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
#include "platform.h"
#include "page.h"


namespace user::html
{


   string page::escape(const ::scoped_string & scopedstrText)
   {

      ::string strText(scopedstrText);
      ::string strEscaped;

      for (::i32 i = 0; i < strText.length(); ++i)
      {

         switch (strText[i])
         {
         case '&':
            strEscaped += "&amp;";
            break;
         case '<':
            strEscaped += "&lt;";
            break;
         case '>':
            strEscaped += "&gt;";
            break;
         case '"':
            strEscaped += "&quot;";
            break;
         case '\'':
            strEscaped += "&#39;";
            break;
         default:
            strEscaped += strText.substr(i, 1);
            break;
         }

      }

      return strEscaped;

   }


   void page::append_styles(string & strHtml)
   {
      styling::append_styles(strHtml);
   }


   void page::append_document_start(
      string & strHtml,
      const ::scoped_string & scopedstrTitle,
      const ::scoped_string & scopedstrBrand,
      enum_color_scheme ecolorscheme)
   {

      strHtml += "<!doctype html><html lang=\"en\"";
      styling::append_color_scheme(strHtml, ecolorscheme);
      strHtml += "><head>";
      strHtml += "<meta charset=\"UTF-8\">";
      strHtml += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
      strHtml += "<meta name=\"color-scheme\" content=\"light dark\">";
      strHtml += "<title>" + escape(scopedstrTitle) + "</title>";
      append_styles(strHtml);
      strHtml += "</head><body><header class=\"site-header\"><div class=\"brand\"><span class=\"brand-mark\" aria-hidden=\"true\">ca2</span><span>";
      strHtml += escape(scopedstrBrand);
      strHtml += "</span></div></header><main class=\"page\"><section class=\"card\" aria-live=\"polite\">";

   }


   void page::append_title(
      string & strHtml,
      const ::scoped_string & scopedstrEyebrow,
      const ::scoped_string & scopedstrHeading,
      const ::scoped_string & scopedstrSubtitle)
   {

      strHtml += "<header class=\"card-head\"><p class=\"eyebrow\">";
      strHtml += escape(scopedstrEyebrow);
      strHtml += "</p><h1>";
      strHtml += escape(scopedstrHeading);
      strHtml += "</h1>";
      if (scopedstrSubtitle.has_character())
      {
         strHtml += "<p class=\"subtitle\">";
         strHtml += escape(scopedstrSubtitle);
         strHtml += "</p>";
      }
      strHtml += "</header>";

   }


   void page::append_paragraph(string & strHtml, const ::scoped_string & scopedstrText)
   {

      strHtml += "<div class=\"card-body\"><p class=\"message\">";
      strHtml += escape(scopedstrText);
      strHtml += "</p></div>";

   }


   void page::append_status(
      string & strHtml,
      const ::scoped_string & scopedstrLabel,
      bool bSuccess)
   {

      strHtml += "<div class=\"card-body\"><p class=\"status";
      if (!bSuccess)
      {
         strHtml += " status-failure";
      }
      strHtml += "\"><span class=\"status-dot\" aria-hidden=\"true\"></span>";
      strHtml += escape(scopedstrLabel);
      strHtml += "</p></div>";

   }


   void page::append_footer(string & strHtml, const ::scoped_string & scopedstrText)
   {

      strHtml += "<footer class=\"card-foot\">";
      strHtml += escape(scopedstrText);
      strHtml += "</footer>";

   }


   void page::append_document_end(string & strHtml)
   {

      strHtml += "</section></main></body></html>";

   }


   string page::message_page(
      const ::scoped_string & scopedstrTitle,
      const ::scoped_string & scopedstrEyebrow,
      const ::scoped_string & scopedstrHeading,
      const ::scoped_string & scopedstrMessage,
      const ::scoped_string & scopedstrDetail,
      bool bSuccess,
      enum_color_scheme ecolorscheme)
   {

      ::string strHtml;
      append_document_start(strHtml, scopedstrTitle, "ca2", ecolorscheme);
      append_title(strHtml, scopedstrEyebrow, scopedstrHeading);
      append_status(strHtml, bSuccess ? "Completed" : "Needs attention", bSuccess);
      append_paragraph(strHtml, scopedstrMessage);
      if (scopedstrDetail.has_character())
      {
         append_paragraph(strHtml, scopedstrDetail);
      }
      append_footer(strHtml, "You may close this page and return to the application.");
      append_document_end(strHtml);
      return strHtml;

   }


} // namespace user::html
