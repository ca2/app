// Created by camilo on 2026-10-28 18:40:53 BRT <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
#pragma once

#include "styling.h"


namespace user::html
{


   class CLASS_DECL_ACME page :
      virtual public ::particle
   {
   public:


      // Text arguments are escaped. Automatic mode follows the browser's live
      // color preference; applications can explicitly select light or dark.
      static void append_styles(string & strHtml);

      static void append_document_start(
         string & strHtml,
         const ::scoped_string & scopedstrTitle,
         const ::scoped_string & scopedstrBrand = "ca2",
         enum_color_scheme ecolorscheme = e_color_scheme_automatic);

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

      static void append_footer(string & strHtml, const ::scoped_string & scopedstrText = {});
      static void append_document_end(string & strHtml);

      static string message_page(
         const ::scoped_string & scopedstrTitle,
         const ::scoped_string & scopedstrEyebrow,
         const ::scoped_string & scopedstrHeading,
         const ::scoped_string & scopedstrMessage,
         const ::scoped_string & scopedstrDetail,
         bool bSuccess,
         enum_color_scheme ecolorscheme = e_color_scheme_automatic);


      static string escape(const ::scoped_string & scopedstrText);


   };


} // namespace user::html
