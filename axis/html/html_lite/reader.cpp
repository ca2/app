/**
*   PROJECT - HTML Reader Class Library
*
*   lite_html_reader.cpp - lite_html_reader implementation
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
#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)
#include <sys/mman.h>
#include <unistd.h>
#endif


void ILiteHTMLReaderEvents::BeginParse(uptr dwAppData, bool &bAbort)
{
   __UNREFERENCED_PARAMETER(dwAppData);
   bAbort = false;
}

void ILiteHTMLReaderEvents::StartTag(lite_html_tag *pTag, uptr dwAppData, bool &bAbort)
{
   __UNREFERENCED_PARAMETER(pTag);
   __UNREFERENCED_PARAMETER(dwAppData);
   bAbort = false;
}

void ILiteHTMLReaderEvents::EndTag(lite_html_tag *pTag, uptr dwAppData, bool &bAbort)
{
   __UNREFERENCED_PARAMETER(pTag);
   __UNREFERENCED_PARAMETER(dwAppData);
   bAbort = false;
}

void ILiteHTMLReaderEvents::Characters(const string &rText, uptr dwAppData, bool &bAbort)
{
   __UNREFERENCED_PARAMETER(rText);
   __UNREFERENCED_PARAMETER(dwAppData);
   bAbort = false;
}

void ILiteHTMLReaderEvents::Comment(const string &rComment, uptr dwAppData, bool &bAbort)
{
   __UNREFERENCED_PARAMETER(rComment);
   __UNREFERENCED_PARAMETER(dwAppData);
   bAbort = false;
}

void ILiteHTMLReaderEvents::EndParse(uptr dwAppData, bool bIsAborted)
{
   __UNREFERENCED_PARAMETER(dwAppData);
   __UNREFERENCED_PARAMETER(bIsAborted);
}

ILiteHTMLReaderEvents::~ILiteHTMLReaderEvents()
{

}


lite_html_reader::lite_html_reader()
{
   m_bResolveEntities = true;   // entities are resolved, by default
   m_dwAppData = 0L;   // reasonable default!
   m_dwBufPos = 0L;   // start from the very beginning
   //m_dwBufLen = 0L;   // buffer length is unknown yet

   // default is to raise all of the events
   m_eventMask = (EventMaskEnum)(notifyStartStop |
                                 notifyTagStart |
                                 notifyTagEnd |
                                 notifyCharacters |
                                 notifyComment);

   m_pEventHandler = nullptr;   // no event handler is associated
}


lite_html_reader::EventMaskEnum lite_html_reader::setEventMask(u32 dwNewEventMask)
{
   EventMaskEnum   oldMask = m_eventMask;
   m_eventMask = (EventMaskEnum)dwNewEventMask;
   return (oldMask);
}


lite_html_reader::EventMaskEnum lite_html_reader::setEventMask(u32 addFlags, u32 eraseFlags)
{
   u32   dwOldMask = (u32)m_eventMask;
   u32   dwNewMask = (dwOldMask | addFlags) & ~eraseFlags;
   m_eventMask = (EventMaskEnum)dwNewMask;
   return ((EventMaskEnum)dwOldMask);
}

strsize lite_html_reader::setAppData(u32 dwNewAppData)
{
   strsize   dwOldAppData = m_dwAppData;
   m_dwAppData = dwNewAppData;
   return (dwOldAppData);
}


ILiteHTMLReaderEvents* lite_html_reader::setEventHandler(ILiteHTMLReaderEvents* pNewHandler)
{
   ILiteHTMLReaderEvents *pOldHandler = m_pEventHandler;
   m_pEventHandler = pNewHandler;
   return (pOldHandler);
}


strsize lite_html_reader::parseDocument()
{
   bool   bAbort = false;         // continue parsing or abort?
   bool   bIsClosingTag = false;   // tag parsed is a closing tag?
   bool   bIsOpeningTag = false;   // tag parsed is an opening tag?
   string   strCharacters;         // character data
   string   strComment;            // comment data
   string   strT;               // temporary storage
   strsize   dwCharDataStart = 0L;   // starting position of character data
   strsize   dwCharDataLen = 0L;      // length of character data
   ::i32   lTemp = 0L;            // temporary storage
   char   ch = 0;               // character at current buffer position
   lite_html_tag   oTag;         // tag information

   if(m_strBuffer.is_empty())
      return 0U;

   // reset seek pointer to beginning
   ResetSeekPointer();

   // notify event handler about parsing startup
   if (getEventNotify(notifyStartStop))
   {
      bAbort = false;
      m_pEventHandler->BeginParse(m_dwAppData, bAbort);
      if (bAbort)   goto LEndParse;
   }

   // skip leading white-space characters
   while (isWhiteSpace(ReadChar()))
      ;

   ch = UngetChar();
   while ((ch = ReadChar()) != '\0')
   {
      switch (ch)
      {

      // tag starting delimeter?
      case '<':
      {
         UngetChar();

         strComment.Empty();
         if (!parseComment(strComment))
         {
            bIsOpeningTag = false;
            bIsClosingTag = false;
            if (!parseTag(oTag, bIsOpeningTag, bIsClosingTag))
            {
               ++dwCharDataLen;

               // manually advance buffer position
               // because the last call to UngetChar()
               // moved it back one character
               ch = ReadChar();

               break;
            }
         }

         // clear pending notifications
         if ( (dwCharDataLen) || (strCharacters.get_length()) )
         {
            strCharacters += string(&m_strBuffer[dwCharDataStart], dwCharDataLen);
            NormalizeCharacters(strCharacters);

            if ( (strCharacters.get_length()) &&
                  (getEventNotify(notifyCharacters)) )
            {
               bAbort = false;
               m_pEventHandler->Characters(strCharacters, m_dwAppData, bAbort);
               if (bAbort)   goto LEndParse;
            }

            strCharacters.Empty();
         }

         dwCharDataLen = 0L;
         dwCharDataStart = m_dwBufPos;

         if (strComment.get_length())
         {
            if (getEventNotify(notifyComment))
            {
               bAbort = false;
               m_pEventHandler->Comment(strComment, m_dwAppData, bAbort);
               if (bAbort)   goto LEndParse;
            }
         }
         else
         {
            if ( (bIsOpeningTag) && (getEventNotify(notifyTagStart)) )
            {
               bAbort = false;
               m_pEventHandler->StartTag(&oTag, m_dwAppData, bAbort);
               if (bAbort)   goto LEndParse;
            }

            if ( (bIsClosingTag) && (getEventNotify(notifyTagEnd)) )
            {
               bAbort = false;
               m_pEventHandler->EndTag(&oTag, m_dwAppData, bAbort);
               if (bAbort)   goto LEndParse;
            }
         }

         break;
      }

      // entity object beginning delimeter?
      case '&':
      {
         UngetChar();

         lTemp = 0;
         string strChar;
         if (m_bResolveEntities)
            lTemp = m_phtml->resolve_entity(&m_strBuffer[m_dwBufPos], strChar);

         if (lTemp)
         {
            strCharacters += string(&m_strBuffer[dwCharDataStart], dwCharDataLen) + strChar;
            m_dwBufPos += lTemp;
            dwCharDataStart = m_dwBufPos;
            dwCharDataLen = 0L;
         }
         else
         {
            ch = ReadChar();
            ++dwCharDataLen;
         }

         break;
      }

      // any other character
      default:
      {
         ++dwCharDataLen;
         break;
      }
      }
   }

   // clear pending notifications
   if ( (dwCharDataLen) || (strCharacters.get_length()) )
   {
      strCharacters += string(&m_strBuffer[dwCharDataStart], dwCharDataLen) + ch;
      NormalizeCharacters(strCharacters);
      strCharacters.trim_right();   // explicit trailing white-space removal

      if ( (strCharacters.get_length()) &&
            (getEventNotify(notifyCharacters)) )
      {
         bAbort = false;
         m_pEventHandler->Characters(strCharacters, m_dwAppData, bAbort);
         if (bAbort)   goto LEndParse;
      }
   }

LEndParse:
   // notify event handler about parsing completion
   if (getEventNotify(notifyStartStop))
      m_pEventHandler->EndParse(m_dwAppData, bAbort);

   m_strBuffer.Empty();
   return (m_dwBufPos);
}

/**
* lite_html_reader::read
* The read method parses an HTML document from an
* in-memory string buffer and raises events defined
* in ILiteHTMLReaderEvents to notify about variours
* elements.
*
* @lparam pszString - string containing HTML text to parse

*
* @return number of TCHARs successfully parsed
* @since 1.0
* @author Gurmeet S. Kochar
*/
strsize lite_html_reader::read_form_document(const ::string & str)
{

   m_strBuffer    = str;

   return parseDocument();

}



char lite_html_reader::UngetChar()
{
   if(m_strBuffer.is_empty())
      return '\0';
   return m_strBuffer[--m_dwBufPos];
}


bool lite_html_reader::getEventNotify(u32 dwEvent) const
{
   ASSERT(dwEvent == notifyStartStop  ||
          dwEvent == notifyTagStart   ||
          dwEvent == notifyTagEnd     ||
          dwEvent == notifyCharacters ||
          dwEvent == notifyComment);
   if (m_pEventHandler == nullptr)
      return (false);
   return ((m_eventMask & dwEvent) == dwEvent);
}

bool lite_html_reader::isWhiteSpace(char ch) const
{
   return ::isspace(static_cast < unsigned char > (ch)) ? true : false;
}


/**
* Parses an HTML tag starting from the current buffer position.
*
* @lparam rTag - this will receive tag information (along with its attributes)
* @lparam bIsOpeningTag - receives true if the tag parsed is a opening tag.
* @lparam bIsClosingTag - receives true if the tag parsed is a closing tag.
*
* @return true if successful, false otherwise
* @since 1.0
* @author Gurmeet S. Kochar
*/
bool lite_html_reader::parseTag(lite_html_tag &rTag, bool &bIsOpeningTag, bool &bIsClosingTag)
{

   ::u32 nRetVal = rTag.parseFromStr(this, m_strBuffer, m_dwBufPos, bIsOpeningTag, bIsClosingTag);

   if(!nRetVal)
      return false;

   m_dwBufPos += nRetVal;

   return true;

}


/**
* Returns the current value for the specified option.
*
* @lparam option - option to inquire
* @lparam bCurVal - this will receive the current value for the option.
*
* @return true if value was retrieved successfully; otherwise false.
* @since 1.0
* @author Gurmeet S. Kochar
*/
bool lite_html_reader::getBoolOption(ReaderOptionsEnum option, bool& bCurVal) const
{
   bool bSuccess = false;

   switch (option)
   {
   case resolveEntities:
   {
      bCurVal = m_bResolveEntities;
      bSuccess = true;
      break;
   }
   default:
   {
      bSuccess = false;
      break;
   }
   }
   return (bSuccess);
}

/**
* Changes the value of an option and returns
* true/false indicating if the specified option
* was set successfully.
*
* @lparam option - option to machine
*                 (one of the ReaderOptionsEnum constants)
* @lparam bNewVal - value to set
*
* @return true if option was set successfully; otherwise false.
* @since 1.0
* @author Gurmeet S. Kochar
*/
bool lite_html_reader::setBoolOption(ReaderOptionsEnum option, bool bNewVal)
{
   bool bSuccess = false;

   switch (option)
   {
   case resolveEntities:
   {
      m_bResolveEntities = bNewVal;
      bSuccess = true;
      break;
   }
   default:
   {
      bSuccess = false;
      break;
   }
   }
   return (bSuccess);
}

/**
* Parses an HTML comment starting from the current buffer position.
*
* @lparam rComment - this will receive the comment (without delimeters)
*
* @return true if successful, false otherwise
* @since 1.0
* @author Gurmeet S. Kochar
*/
bool lite_html_reader::parseComment(string &rComment)
{

   // HTML comments begin with '<!' delimeter and
   // are immediately followed by two hyphens '--'
   if (::ansi_count_compare(&m_strBuffer[m_dwBufPos], "<!--", 4))
      return (false);

   const char *   pszBegin = &m_strBuffer[m_dwBufPos + 4];

   // HTML comments end with two hyphen symbols '--'
   const char *   pszEnd = ::strstr(pszBegin, "--");


   // comment ending delimeter could not be found?
   if (pszEnd == nullptr)

      // consider everything after current buffer position a comment
   {
      rComment = pszBegin;

      m_dwBufPos += (4 + rComment.get_length());
      return (true);
   }

   string   strComment(pszBegin, i32(pszEnd - pszBegin));


   // end of buffer?
   if (pszEnd + (sizeof(char) * 2) >= &m_strBuffer[0] + m_strBuffer.size())

      return (false);

   // skip white-space characters after comment ending delimeter '--'
   pszEnd += (sizeof(char) * 2);

   while (::isspace(*pszEnd))

      pszEnd++;


   // comment has not been terminated properly
   if (*pszEnd != '>')

      return (false);

   pszEnd++;

   m_dwBufPos += (pszEnd - &m_strBuffer[m_dwBufPos]);

   rComment = strComment;
   return (true);
}

