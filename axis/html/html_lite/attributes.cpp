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
#include "axis/html/html_lite/_.h"
#endif


/**
* LiteHTMLElemAttr::parseFromStr
*
* @lparam pszString - string to parse

*
* @return number of TCHARs successfully parsed
* @since 1.0
* @author Gurmeet S. Kochar
*/
strsize LiteHTMLElemAttr::parseFromStr(::lite_html_reader * preader, const char * pszString)

{
   ASSERT(__is_valid_string(pszString));


   const char *   pszBegin = pszString;

   const char *   pszEnd;

   //   char   ch = 0;

   // skip leading white-space characters
   while(::isspace((uchar) *pszBegin))

      pszBegin++;


   // name doesn't begin with an alphabet?
   if (!::isalpha((uchar) *pszBegin))

      return (0U);

   pszEnd = pszBegin;

   do
   {
      // attribute name may contain letters (a-z, A-Z), digits (0-9),
      // underscores '_', hyphen '-', colons ':', and periods '.'
      if ( (!::ansi_char_is_alphanumeric((uchar) *pszEnd)) &&

            (*pszEnd != '-') && (*pszEnd != ':') &&

            (*pszEnd != '_') && (*pszEnd != '.') )

      {
         ASSERT(pszEnd != pszBegin);


         // only white-space characters, a nullptr-character, an
         // equal-sign, a greater-than symbol, or a forward-slash
         // can act as the separator between an attribute and its
         // value
         if (*pszEnd =='\0' || ::isspace((uchar) *pszEnd) ||

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
   string   strAttrName(pszBegin, i32(pszEnd - pszBegin));


   // skip leading white-space characters
   while (::isspace((uchar)*pszEnd))

      pszEnd++;



   if (*pszEnd != '=')

   {
      m_strName = strAttrName;
      m_strValue.Empty();
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
      while (::isspace((uchar) *pszEnd));


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
         pszBegin += strChar.get_length();   // skip quote symbol

         do
         {
            pszEnd++;

         }
         // Loop until we find the same quote character that
         // was used at the starting of the attribute value.
         // Anything within these quotes is considered valid!
         // NOTE that the entity references are resolved later.
         while (*pszEnd != '\0' && !::str::begins_ci(pszEnd, strChar));

      }

      // open attribute value i.e. not wrapped in quotes?
      else
      {
         strChar.Empty();
         do
         {
            pszEnd++;

         }
         // loop until we find a tag ending delimeter or any
         // white-space character, or until we reach at the
         // end of the string buffer
         while (*pszEnd != '\0' && !::isspace((uchar) *pszEnd) &&

                *pszEnd != '/' && *pszEnd != '>');

      }

      m_strName = strAttrName;
      if (pszEnd == pszBegin)   // is_empty attribute value?

         m_strValue.Empty();
      else
         // use putValue() instead of direct assignment;
         // this will automatically normalize data before
         // assigning according to the specs and will
         // also resolve entity references!!!
         putValue(preader, string(pszBegin,i32(pszEnd - pszBegin)));


      // calculate and return the ::count of characters successfully parsed
      return (pszEnd - pszString) + strChar.get_length();

   }

   return (0U);
}



/**
* LiteHTMLAttributes::parseFromStr
*
* @lparam pszString - string to parse. It can contain pairs such as:

*
*          1. NAME
*          2. NAME=VALUE
*          3. NAME='VALUE'
*          4. NAME="VALUE"
*
*        NAME consist of letters, digits, underscores,
*        colons, hyphens, and periods
*
*        NOTE that white-spaces between NAME and equal-sign AND
*        equal-sign and VALUE is allowed.
*
* @return number of TCHARs successfully parsed
* @since 1.0
* @author Gurmeet S. Kochar
*/
strsize LiteHTMLAttributes::parseFromStr(::lite_html_reader * preader, const char * pszString, strsize iLen)

{

   CElemAttrArray      *pcoll = nullptr;
   LiteHTMLElemAttr   oElemAttr;
   const strsize         nStrLen = iLen;
   strsize            nRetVal = 0U,
                       nTemp = 0U;

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
         if ((pcoll = new CElemAttrArray) == nullptr)
            // out of memory?
         {
            //            TRACE0("(Error) LiteHTMLAttributes::parseFromStr: Out of memory.\n");
            goto LError;
         }
      }

      // add attribute/value pair to collection
      if (pcoll->add(new LiteHTMLElemAttr(oElemAttr)) < 0)
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
   if (!removeAll())
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

LiteHTMLElemAttr* LiteHTMLAttributes::addAttribute(const char * lpszName, const char * pszValue)

{

   ASSERT(__is_valid_string(lpszName));

   ASSERT(__is_valid_string(pszValue));


   LiteHTMLElemAttr   *pItem = new LiteHTMLElemAttr(lpszName, pszValue);

   if (pItem != nullptr)
   {
      if (m_parrAttrib == nullptr)
      {
         if ((m_parrAttrib = new CElemAttrArray) == nullptr)
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


void LiteHTMLElemAttr::putValue(::lite_html_reader * preader, const char * pszValue)

{

   ASSERT(__is_valid_string(pszValue));


   m_strValue = pszValue;


   // ignore leading white-spaces
   m_strValue.trim_left();

   // ignore trailing white-spaces
   m_strValue.trim_right();

   // ignore line feeds
   m_strValue.remove('\n');

   // replace tab and carriage-return with a single space
   m_strValue.replace('\r', ' ');

   m_strValue.replace('\t', ' ');

   /** resolve entity context_object(s) */
   strsize iCurPos = -1, iParseLen = 0;

   string strChar;

   do
   {

      if ((iCurPos = m_strValue.find('&', ++iCurPos)) == -1)
         break;

      iParseLen = System.m_phtml->resolve_entity(m_strValue.Mid(iCurPos), strChar);

      if (iParseLen)
      {

         m_strValue.replace(m_strValue.Mid(iCurPos, iParseLen), strChar);

      }

   }
   while (true);

}


bool LiteHTMLElemAttr::isNamedColorValue(::lite_html_reader * preader) const
{

   if((m_strValue.get_length()) && (::isalpha(m_strValue[0])))
   {

      if (System.m_phtml->m_namedColors.contains(m_strValue.lowered()))
      {

          return true;

      }

   }

   return false;

}

bool LiteHTMLElemAttr::isSysColorValue(::lite_html_reader * preader) const
{

   if((m_strValue.get_length()) && (::isalpha(m_strValue[0])))
   {

      ::color::color color;

      string      strKey(m_strValue);

      strKey.make_lower();

      if(System.m_phtml->m_namedColors.lookup(strKey, color))
         return color.m_flags == -2;

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

      if (m_strValue.get_length() > 1)
      {

         for (i32 i = 1; i < m_strValue.get_length(); i++)
         {

            if (!::isdigit((uchar) m_strValue[i]))
               return false;

         }

         return true;

      }

   }

   return false;

}



color32_t LiteHTMLElemAttr::getColorValue(::lite_html_reader * preader) const
{

   ::color::color color;

   if(isNamedColorValue(preader))
   {

      string   strKey(m_strValue);

      strKey.make_lower();

      if(System.m_phtml->m_namedColors.lookup(strKey, color))
      {

         // is this a system named color value?
         if (color.m_flags == -2)
         {
            color = Sess(preader->get_context_session())->get_default_color(color.red);

         }
      }

   }
   else if (isHexColorValue())
   {

      color = (u32) ::strtoul(m_strValue.Mid(1), nullptr, 16);

   }

   return color;

}

string LiteHTMLElemAttr::getColorHexValue(::lite_html_reader * preader) const
{

   string   strColorHex;

   if(isHexColorValue())
   {

      strColorHex = m_strValue.Mid(1);

   }
   else
   {

      color32_t crTemp = getColorValue(preader);

      if (crTemp != 0xffffffff)
         strColorHex.Format("#%06x", crTemp);

   }

   return strColorHex;

}

void LiteHTMLElemAttr::Init()
{
}



