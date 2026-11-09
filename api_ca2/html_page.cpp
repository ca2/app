#include "platform.h"
#include "html_page.h"

namespace api_ca2
{

   void html_page::append_styles(string & strHtml)
   {
      ::user::html::page::append_styles(strHtml);
   }

   void html_page::append_document_start(
      string & strHtml,
      const ::scoped_string & scopedstrTitle,
      const ::scoped_string & scopedstrBrand)
   {
      ::user::html::page::append_document_start(strHtml, scopedstrTitle, scopedstrBrand);
   }

   void html_page::append_title(
      string & strHtml,
      const ::scoped_string & scopedstrEyebrow,
      const ::scoped_string & scopedstrHeading,
      const ::scoped_string & scopedstrSubtitle)
   {
      ::user::html::page::append_title(strHtml, scopedstrEyebrow, scopedstrHeading, scopedstrSubtitle);
   }

   void html_page::append_paragraph(string & strHtml, const ::scoped_string & scopedstrText)
   {
      ::user::html::page::append_paragraph(strHtml, scopedstrText);
   }

   void html_page::append_status(
      string & strHtml, const ::scoped_string & scopedstrLabel, bool bSuccess)
   {
      ::user::html::page::append_status(strHtml, scopedstrLabel, bSuccess);
   }

   void html_page::append_footer(string & strHtml)
   {
      ::user::html::page::append_footer(strHtml, "You may close this page and return to the application.");
   }

   void html_page::append_document_end(string & strHtml)
   {
      ::user::html::page::append_document_end(strHtml);
   }

   string html_page::message_page(
      const ::scoped_string & scopedstrTitle,
      const ::scoped_string & scopedstrEyebrow,
      const ::scoped_string & scopedstrHeading,
      const ::scoped_string & scopedstrMessage,
      const ::scoped_string & scopedstrDetail,
      bool bSuccess,
      const ::scoped_string & scopedstrAppId,
      const ::scoped_string & scopedstrAppName,
      const ::scoped_string & scopedstrIcon)
   {
      string strHtml;
      append_document_start(strHtml, scopedstrTitle);
      strHtml += "<div class=\"application-header\">";
      if (scopedstrIcon.has_character())
      {
         strHtml += "<img width=\"48\" height=\"48\" alt=\"\" src=\"data:image/png;base64,";
         strHtml += escape(scopedstrIcon);
         strHtml += "\">";
      }
      strHtml += "<span class=\"application-id\">" + escape(scopedstrAppId) + "</span>";
      strHtml += "<span class=\"application-name\">" + escape(scopedstrAppName) + "</span></div>";
      append_title(strHtml, scopedstrEyebrow, scopedstrHeading);
      append_status(strHtml, bSuccess ? "Completed" : "Needs attention", bSuccess);
      append_paragraph(strHtml, scopedstrMessage);
      if (scopedstrDetail.has_character())
      {
         append_paragraph(strHtml, scopedstrDetail);
      }
      append_footer(strHtml);
      append_document_end(strHtml);
      return strHtml;
   }

} // namespace api_ca2