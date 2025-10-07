/**
*   PROJECT - HTML Reader Class Library
*
*   LiteHTMLAttributes.cpp
*
*   Written By Gurmeet S. Kochar <gomzygotit@hotmail.com>
*   Copyright (ca) 2004.
*
*   This code may be used in compiled form in any way you desire
*   (including commercial use). The code may be redistributed
*   unmodified by any means PROVIDING it is not sold for profit
*   without the authors written consent, and providing that this
*   notice and the authors name and all copyright notices remains
*   intact. However, this file and the accompanying source code may
*   not be hosted on a website or bulletin board without the authors
*   written permission.
*
*   This file is provided "AS IS" with no expressed or implied warranty.
*   The author accepts no liability for any damage/loss of business that
*   this product may cause.
*
*   Although it is not necessary, but if you use this code in any of
*   your application (commercial or non-commercial), please INFORM me
*   so that I may know how useful this library is. This will encourage
*   me to keep updating it.
*/
#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
//#include "axis/html/html_lite/_.h"
#endif
#include "common.h"
#include "acme/prototype/string/str.h"
#include "axis/platform/session.h"
#include "axis/platform/system.h"
#include "attributes.h"
#include "reader.h"
#include "axis/html/html/html.h"


/**
* LiteHTMLElemAttr::parseFromStr
*
* @lparam pszString - string to parse

*
* @return number of TCHARs successfully parsed
* @since 1.0
* @author Gurmeet S. Kochar
*/
character_count LiteHTMLElemAttr::parseFromStr(::lite_html_reader * preader, const ::scoped_string & scopedstrString)

{
   ASSERT(is_string_ok(scopedstrString));

   ::string str(scopedstrString);

   const_char_pointer pszString = str;

   const_char_pointer pszBegin = pszString;

   const_char_pointer pszEnd;

   //   char   ch = 0;

   // skip leading white-space characters
   while(::character_isspace(*pszBegin))

      pszBegin++;


   // name doesn't begin with an alphabet?
   if (!::character_isalpha(*pszBegin))

      return (0U);

   pszEnd = pszBegin;

   do
   {
      // attribute name may contain letters (a-z, A-Z), digits (0-9),
      // underscores '_', hyphen '-', colons ':', and periods '.'
      if ( (!::character_isalnum(*pszEnd)) &&

            (*pszEnd != '-') && (*pszEnd != ':') &&

            (*pszEnd != '_') && (*pszEnd != '.') )

      {
         ASSERT(pszEnd != pszBegin);


         // only white-space characters, a nullptr-character, an
         // equal-sign, a greater-than symbol, or a forward-slash
         // can act as the separator between an attribute and its
         // value
         if (*pszEnd =='\0' || ::character_isspace(*pszEnd) ||

               *pszEnd == '=' ||

               *pszEnd == '>' || *pszEnd == '/')

         {
            break;
         }

         return (0U);   // any other character will fail parsing process
      }

      pszEnd++;

   }
   while (true);

   // extract attribute name
   string   strAttrName(pszBegin, int(pszEnd - pszBegin));


   // skip leading white-space characters
   while (::character_isspace(*pszEnd))

      pszEnd++;



   if (*pszEnd != '=')

   {
      m_strName = strAttrName;
      m_strValue.empty();
      return (pszEnd - pszString);

   }
   else
   {
      // skip white-space characters after equal-sign
      // and the equal-sign itself
      do
      {
         pszEnd++;

      }
      while (::character_isspace(*pszEnd));


      pszBegin = pszEnd;

      string strChar = string(*pszEnd);


      if(strChar == "&")
      {
         if(string(pszEnd, 6) == "&#039;")

         {
            strChar = "&#039;";
         }
      }

      // is attribute value wrapped in quotes?
      if(strChar == "\'" || strChar == "\"" || strChar == "&#039;")
      {
         pszBegin += strChar.length();   // skip quote symbol

         do
         {
            pszEnd++;

         }
         // Loop until we find the same quote character that
         // was used at the starting of the attribute value.
         // Anything within these quotes is considered valid!
         // NOTE that the entity references are resolved later.
         while (*pszEnd != '\0' && !case_insensitive_string_begins(pszEnd, strChar));

      }

      // open attribute value i.e. not wrapped in quotes?
      else
      {
         strChar.empty();
         do
         {
            pszEnd++;

         }
         // loop until we find a tag ending delimeter or any
         // white-space character, or until we reach at the
         // end of the string buffer
         while (*pszEnd != '\0' && !::character_isspace(*pszEnd) &&

                *pszEnd != '/' && *pszEnd != '>');

      }

      m_strName = strAttrName;
      if (pszEnd == pszBegin)   // is_empty attribute value?

         m_strValue.empty();
      else
         // use putValue() instead of direct assignment;
         // this will automatically normalize data before
         // assigning according to the specs and will
         // also resolve entity references!!!
         putValue(preader, string(pszBegin,int(pszEnd - pszBegin)));


      // calculate and return the ::collection::count of characters successfully parsed
      return (pszEnd - pszString) + strChar.length();

   }

   return (0U);
}



/**
* LiteHTMLAttributes::parseFromStr
*
* @lparam pszString - string to parse. It can contain pairs such as:

*
*          1. NAME
*          2. NAME=PAYLOAD
*          3. NAME='PAYLOAD'
*          4. NAME="PAYLOAD"
*
*        NAME consist of letters, digits, underscores,
*        colons, hyphens, and periods
*
*        NOTE that white-spaces between NAME and equal-sign AND
*        equal-sign and PAYLOAD is allowed.
*
* @return number of TCHARs successfully parsed
* @since 1.0
* @author Gurmeet S. Kochar
*/
character_count LiteHTMLAttributes::parseFromStr(::lite_html_reader * preader, const ::scoped_string & scopedstrString, character_count iLen)

{

   CElemAttrArray      *pcoll = nullptr;
   LiteHTMLElemAttr   oElemAttr;
   const character_count         nStrLen = iLen;
   character_count            nRetVal = 0U,
                       nTemp = 0U;

   ::string str(scopedstrString);

   const_char_pointer pszString = str;

   do
   {
      // try to parse an attribute/value
      // pair from the rest of the string
      if (!(nTemp = oElemAttr.parseFromStr(preader, &pszString[nRetVal])))

      {
         if (!nRetVal)
            goto LError;
         break;
      }

      // collection has not been instantiated until now?
      if (pcoll == nullptr)
      {
         // instantiate now
         if ((pcoll = ___new CElemAttrArray()) == nullptr)
            // out of memory?
         {
            //            TRACE0("(Error) LiteHTMLAttributes::parseFromStr: Out of memory.\n");
            goto LError;
         }
      }

      // add attribute/value pair to collection
      if (pcoll->add(øraw_new LiteHTMLElemAttr(oElemAttr)) < 0)
         goto LError;

      // advance seek pointer
      nRetVal += nTemp;
   }

   // do we still have something in the buffer to parse?
   while (nRetVal < nStrLen);

   // collection was never instantiated?
   if (pcoll == nullptr)
      goto LError;
   // collection is is_empty?
   if (pcoll->get_upper_bound() == -1)
      goto LError;
   // current collection could not be emptied?
   if (!eraseAll())
      goto LError;

   m_parrAttrib = pcoll;
   pcoll = nullptr;
   goto LCleanExit;   // success!

LError:
   SAFE_DELETE_POINTER(pcoll);
   nRetVal = 0U;

LCleanExit:
   return (nRetVal);
}

LiteHTMLElemAttr* LiteHTMLAttributes::addAttribute(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrValue)

{

   ASSERT(is_string_ok(scopedstrName));

   ASSERT(is_string_ok(scopedstrValue));


   LiteHTMLElemAttr   *pItem = øraw_new LiteHTMLElemAttr(scopedstrName, scopedstrValue);

   if (pItem != nullptr)
   {
      if (m_parrAttrib == nullptr)
      {
         if ((m_parrAttrib = øraw_new CElemAttrArray()) == nullptr)
         {
            SAFE_DELETE_POINTER(pItem);
            //               TRACE0("(Error) LiteHTMLAttributes::addAttribute: Out of memory.\n");
            return (nullptr);
         }
      }

      m_parrAttrib->add(pItem);

   }

   return (pItem);

}


void LiteHTMLElemAttr::putValue(::lite_html_reader * preader, const ::scoped_string & scopedstrValue)

{

   ASSERT(is_string_ok(scopedstrValue));


   m_strValue = scopedstrValue;


   // ignore leading white-spaces
   m_strValue.trim_left();

   // ignore trailing white-spaces
   m_strValue.trim_right();

   // ignore line feeds
   m_strValue.erase_character('\n');

   // replace tab and carriage-return with a single space
   m_strValue.replace_with(' ', '\r');

   m_strValue.replace_with(' ', '\t');

   /** resolve entity object(s) */
   character_count iCurPos = -1, iParseLen = 0;

   string strChar;

   ::pointer<::axis::system>psystem = preader->system();

   do
   {

      if ((iCurPos = m_strValue.find_index('&', ++iCurPos)) == -1)
         break;

      iParseLen = preader->m_phtml->resolve_entity(m_strValue.substr(iCurPos), strChar);

      if (iParseLen)
      {

         m_strValue.replace_with(strChar, m_strValue.substr(iCurPos, iParseLen));

      }

   }
   while (true);

}


bool LiteHTMLElemAttr::isNamedColorValue(::lite_html_reader * preader) const
{

   if((m_strValue.length()) && (::character_isalpha(m_strValue[0])))
   {

      if (preader->m_phtml->m_namedcolor.contains(m_strValue.lowered()))
      {

          return true;

      }

   }

   return false;

}

bool LiteHTMLElemAttr::isSysColorValue(::lite_html_reader * preader) const
{

   if((m_strValue.length()) && (::character_isalpha(m_strValue[0])))
   {

      status < ::color::color > color;

      string strKey(m_strValue);

      strKey.make_lower();

      if (preader->m_phtml->m_namedcolor.find(strKey, color))
      {

         return color.m_estatus == ::success_color_index;

      }

   }

   return false;

}

bool LiteHTMLElemAttr::isHexColorValue() const
{

   // zero-length attribute value?
   if (m_strValue.is_empty())
      return false;

   if (m_strValue[0] == '#')
   {

      if (m_strValue.length() > 1)
      {

         for (int i = 1; i < m_strValue.length(); i++)
         {

            if (!::character_isdigit(m_strValue[i]))
               return false;

         }

         return true;

      }

   }

   return false;

}



::color::color LiteHTMLElemAttr::getColorValue(::lite_html_reader * preader) const
{

   status < ::color::color > color;

   if(isNamedColorValue(preader))
   {

      string   strKey(m_strValue);

      strKey.make_lower();

      if(preader->m_phtml->m_namedcolor.find(strKey, color))
      {

         // is this a system named color value?
         if (color.m_estatus == ::success_color_index)
         {

            color = preader->m_psession->get_default_color(::color::red);

         }
      }

   }
   else if (isHexColorValue())
   {

      color.m_ui = (unsigned int) ::strtoul(m_strValue.substr(1), nullptr, 16);

      color.m_estatus = ::success;

   }

   return color;

}


string LiteHTMLElemAttr::getColorHexValue(::lite_html_reader * preader) const
{

   string   strColorHex;

   if(isHexColorValue())
   {

      strColorHex = m_strValue.substr(1);

   }
   else
   {

      ::color::color crTemp = getColorValue(preader);

      if (crTemp != 0xffffffff)
         strColorHex.formatf("#%06x", crTemp.m_ui);

   }

   return strColorHex;

}

void LiteHTMLElemAttr::Init()
{
}



