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


} // namespace user::html
