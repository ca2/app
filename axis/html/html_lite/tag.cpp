#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "axis/html/html_lite/_.h"
#endif


lite_html_tag::lite_html_tag(lite_html_tag &rSource, bool bCopy)
   :m_pcollAttr(nullptr)
{
   m_strTagName = rSource.m_strTagName;
   if (!bCopy)
   {
      m_pcollAttr = rSource.m_pcollAttr;
      rSource.m_pcollAttr = nullptr;
   }
   else if (rSource.m_pcollAttr != nullptr)
   {

      /** DEEP COPY BEGIN */

      try
      {

         m_pcollAttr = new LiteHTMLAttributes(*(rSource.m_pcollAttr), true);

      }
      catch(const ::exception::exception & e)
      {

         __rethrow(e);

      }

      /** DEEP COPY END */

   }

}

lite_html_tag::~lite_html_tag()
{
   SAFE_DELETE_POINTER(m_pcollAttr);
}

/**
 * lite_html_tag::parseFromStr
 *
 * @lparam rStr - string to parse
 * @lparam bIsOpeningTag - receives true if the tag parsed
 *        is a opening tag, false otherwise.
 * @lparam bIsClosingTag - receives true if the tag parsed
 *        is a closing tag, false otherwise.
 * @lparam bParseAttrib - determines whether attribute/value
 *        pairs should be parsed. Default is true.
 *
 * @return number of characters successfully parsed
 * @since 1.0
 * @author Gurmeet S. Kochar
 */
::u32 lite_html_tag::parseFromStr(::lite_html_reader * preader, const ::string & strString, strsize iPos,
                                 bool &bIsOpeningTag,
                                 bool &bIsClosingTag,
                                 bool bParseAttrib /* = true */)
{


   bool            bClosingTag = false;
   bool            bOpeningTag = false;
   LiteHTMLAttributes   *pcollAttr = nullptr;
   string            strTagName;
   ::u32            nRetVal = 0U,
                   nTemp = 0U;
   const char *            pszBegin = &strString[iPos];

   const char *            pszEnd = nullptr;


   // skip leading white-space characters
   while (::isspace(*pszBegin))

      pszBegin++;


   // HTML tags always begin with a less-than symbol
   if (*pszBegin != '<')

      return (0U);

   // skip tag's opening delimeter '<'
   pszBegin++;


   // optimization for is_empty opening tags
   if (*pszBegin == '>')

   {
      ASSERT(strTagName.is_empty());
      ASSERT(pcollAttr == nullptr);
      ASSERT(!bClosingTag);
      nRetVal = (::u32) (pszBegin - &strString[iPos]);

      goto LUpdateAndExit;
   }

   // tag names always begin with an alphabet
   if (!::ansi_char_is_alphabetic(*pszBegin))

   {
      bClosingTag = (*pszBegin == '/');

      if (bClosingTag)
         pszBegin++;

      else
         return (0U);
   }

   bOpeningTag = !bClosingTag;
   pszEnd = pszBegin;

   do
   {
      // tag name may contain letters (a-z, A-Z), digits (0-9),
      // underscores '_', hyphen '-', colons ':', and periods '.'
      if ((!(*pszEnd >= 0 && ::ansi_char_is_alphanumeric(*pszEnd))) &&

            (*pszEnd != '-') && (*pszEnd != ':') &&

            (*pszEnd != '_') && (*pszEnd != '.') )

      {

         if(pszEnd == pszBegin)

            return 0;

         // only white-space characters, a nullptr-character, a
         // greater-than symbol, or a forward-slash can break
         // a tag name
         if (*pszEnd == '\0' || ::isspace(*pszEnd) ||

               *pszEnd == '>' ||

               (*pszEnd == '/' && (!bClosingTag)) )

         {
            break;
         }

         return (0U);   // any other character will fail parsing process
      }

      pszEnd++;

   }
   while(true);

   // store tag name for later use
   strTagName = string(pszBegin, pszEnd - pszBegin);


   // is this a closing tag?
   if (bClosingTag)
   {
      // in a closing tag, there can be only one symbol after
      // tag name, i.e., the tag end delimeter '>'. Anything
      // else will result in parsing failure
      if (*pszEnd != '>')

         return (0U);

      // skip tag's ending delimeter
      pszEnd++;


      ASSERT(strTagName.get_length());
      ASSERT(pcollAttr == nullptr);
      nRetVal = (::u32) (pszEnd - &strString[iPos]);

      goto LUpdateAndExit;
   }

   while (::isspace(*pszEnd))

      pszEnd++;


   // tag contains attribute/value pairs?
   if (*pszEnd != '>')

   {
      pszBegin = pszEnd;

      pszEnd = nullptr;


      // skip white-space characters after tag name

      nTemp = 0U;
      if (bParseAttrib)   // parse attribute/value pairs?
      {
         ASSERT(pcollAttr == nullptr);
         // instantiate collection ...
         if ((pcollAttr = new LiteHTMLAttributes) == nullptr)
         {
//            TRACE0("(Error) lite_html_tag::parseFromStr: Out of memory.\n");
            __throw(error_no_memory);
            return (0U);
         }

         // ... and delegate parsing process
         nTemp = (::u32) pcollAttr->parseFromStr(preader, pszBegin, strString.get_length() - (pszBegin - (const ::string &) strString));

      }

      if (nTemp == 0)   // attribute/value pair parsing is disabled?
         //   - OR -
         // attribute/value pairs could not be parsed?
      {
         SAFE_DELETE_POINTER(pcollAttr);
         if ((pszEnd = ::strstr(pszBegin, "/>")) == nullptr)

         {
            if ((pszEnd = ::strchr(pszBegin, '>')) == nullptr)

               return (0U);
         }
      }
      else
      {
         pszEnd = pszBegin + nTemp;


         // skip white-space after attribute/value pairs
         while (::isspace((uchar) *pszEnd))

            pszEnd++;


         // tag's ending delimeter could not be found?
         if (*pszEnd == '\0')

         {
            SAFE_DELETE_POINTER(pcollAttr);
            return (0U);
         }
      }

      // a tag like this one: <BR/>
      if (*pszEnd == '/')

      {
         ASSERT(bOpeningTag);
         bClosingTag = true;
         pszEnd++;

      }
   }

   // HTML tags always end with a greater-than '>' symbol
   if (*pszEnd != '>')

   {
      SAFE_DELETE_POINTER(pcollAttr);
      return (0U);
   }
   else
      pszEnd++;


   nRetVal = (::u32) (pszEnd - &strString[iPos]);

   goto LUpdateAndExit;   // just to show the flow-of-control

LUpdateAndExit:
   m_strTagName = strTagName;
   if(strTagName.compare_ci("BR") == 0)
   {
      bIsClosingTag = true;
      bIsOpeningTag = true;
   }
   else
   {
      bIsClosingTag = bClosingTag;
      bIsOpeningTag = bOpeningTag;
   }
   m_strTagName.trim_left();   m_strTagName.trim_right();   // just-in-case!
   SAFE_DELETE_POINTER(m_pcollAttr);
   m_pcollAttr = pcollAttr;
   pcollAttr = nullptr;

   return (nRetVal);
}

