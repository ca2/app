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
      bool bSuccess)
   {
      return ::user::html::page::message_page(
         scopedstrTitle, scopedstrEyebrow, scopedstrHeading,
         scopedstrMessage, scopedstrDetail, bSuccess);
   }

} // namespace api_ca2