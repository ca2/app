// Reusable, dependency-free HTML pages for ca2's small browser responses.
#pragma once

#include "_.h"
#include "acme/user/html/page.h"


namespace api_ca2
{


   class CLASS_DECL_API_CA2 html_page :
      public ::user::html::page
   {
   public:


      static void append_styles(string & strHtml);

      static void append_document_start(
         string & strHtml,
         const ::scoped_string & scopedstrTitle,
         const ::scoped_string & scopedstrBrand = "ca2");

      static void append_title(
         string & strHtml,
         const ::scoped_string & scopedstrEyebrow,
         const ::scoped_string & scopedstrHeading,
         const ::scoped_string & scopedstrSubtitle = {});

      static void append_paragraph(
         string & strHtml,
         const ::scoped_string & scopedstrText);

      static void append_status(
         string & strHtml,
         const ::scoped_string & scopedstrLabel,
         bool bSuccess);

      static void append_footer(string & strHtml);
      static void append_document_end(string & strHtml);

      static string message_page(
         const ::scoped_string & scopedstrTitle,
         const ::scoped_string & scopedstrEyebrow,
         const ::scoped_string & scopedstrHeading,
         const ::scoped_string & scopedstrMessage,
         const ::scoped_string & scopedstrDetail,
         bool bSuccess);


   };


} // namespace api_ca2
