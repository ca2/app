#include "framework.h"
#include <stdio.h>


namespace str
{


   tokenizer::tokenizer()
   {
      Restart();
   }

   tokenizer::~tokenizer()
   {

   }

   tokenizer::tokenizer(const char * pch, i32 nLength) :

      string(pch, nLength)

   {
      Restart();
   }

   tokenizer::tokenizer(const string & strSrc) :
      string(strSrc)
   {
      Restart();
   }



   bool tokenizer::GetNextToken(string &strToken, const char * pSeparator, bool bWithSeparator)

   {

      strsize i;

      if((i = find(pSeparator, m_nCurrentIndex)) >= 0)

      {
         if(bWithSeparator)
            strToken = Mid(m_nCurrentIndex, i - m_nCurrentIndex + strlen(pSeparator));

         else
            strToken = Mid(m_nCurrentIndex, i - m_nCurrentIndex);
         m_nCurrentIndex = i + strlen(pSeparator);

         return TRUE;
      }
      else
      {
         if(m_nCurrentIndex <= get_length())
         {
            strToken = Mid(m_nCurrentIndex);
            m_nCurrentIndex = get_length() + 1;
            return TRUE;
         }
         else
            return FALSE;
      }

   }

   bool tokenizer::GetNextSmallestToken(string & strToken, const string_array & straSeparator, bool bWithSeparator)
   {
      if(m_nCurrentIndex >= get_length())
      {
         return FALSE;
      }
      strsize iMinPos = get_length();
      strsize iMaxSepLen = 0;
      strsize iPos;
      for(i32 j = 0; j < straSeparator.get_size(); j++)
      {
         iPos = find(straSeparator[j], m_nCurrentIndex);
         if(iPos >= 0 && iPos <= iMinPos)
         {
            if(iMinPos == iPos)
            {
               if(straSeparator[j].get_length() > iMaxSepLen)
               {
                  iMaxSepLen = straSeparator[j].get_length();
               }
            }
            else
            {
               iMinPos = iPos;
               iMaxSepLen = straSeparator[j].get_length();
            }
         }
      }
      if(bWithSeparator)
         strToken = Mid(m_nCurrentIndex, iMinPos - m_nCurrentIndex + iMaxSepLen);
      else
         strToken = Mid(m_nCurrentIndex, iMinPos - m_nCurrentIndex);
      m_nCurrentIndex = iMinPos + iMaxSepLen;
      return TRUE;
   }

   bool tokenizer::GetNextTokenEx(string &strToken, const char * pSeparator, bool bWithSeparator, bool bSkipAdjacent)

   {
      strsize i;
      string strMid = Mid(m_nCurrentIndex);
      if((i = strMid.FindOneOf(pSeparator)) >= 0)

      {
         if(bWithSeparator)
            strToken = strMid.Left(i + 1);
         else
            strToken = strMid.Left(i);
         m_nCurrentIndex += i + 1;
         if(bSkipAdjacent)
         {
            strMid = strMid.Mid(i + 1);
            while(strMid.get_length() > 1)
            {
               if(strMid.FindOneOf(pSeparator) == 0)

               {
                  m_nCurrentIndex++;
               }
               else
               {
                  break;
               }
               strMid = strMid.Mid(1);
            }
         }
         return true;
      }
      else
      {
         if(m_nCurrentIndex < get_length())
         {
            strToken = Mid(m_nCurrentIndex);
            m_nCurrentIndex = get_length();
            return TRUE;
         }
         else
            return FALSE;
      }

   }

   void tokenizer::Restart()
   {
      m_nCurrentIndex = 0;
   }

   void tokenizer::Restart(string &strNew)
   {
      operator =(strNew);
      m_nCurrentIndex = 0;
   }

   bool tokenizer::ExtractFolderPath(const char * pcszFilePath)

   {
      string strFilePath(pcszFilePath);

      strsize i = strFilePath.get_length();
      bool b = false;
      while(i > 0)
      {
         i--;
         if(strFilePath[i] == '/' ||
               strFilePath[i] == '\\')
         {
            b = true;
            break;
         }
      }
      operator=(strFilePath.Left(i));
      return b;
   }

   bool tokenizer::_01Read(string &str)
   {
      if(!GetNextTokenEx(str, "\n\r\t ", false, true))
         return false;
      if(str.is_empty())
         if(!GetNextTokenEx(str, "\n\r\t ", false, true))
            return false;
      return true;
   }

   bool tokenizer::_01Read(::u32 & user)
   {
      i32 i;
      if(!_01Read(i))
         return false;
      user = (::u32) i;
      return true;
   }

   bool tokenizer::_01Read(i32 &i)
   {
      string str;
      if(!_01Read(str))
         return false;
      i = atoi(str);
      return true;
   }

   bool tokenizer::_01ReadHex(::u32 & user)
   {
      i32 i;
      if(!_01ReadHex(i))
         return false;
      user = (::u32) i;
      return true;
   }

   bool tokenizer::_01ReadHex(i32 &i)
   {
      string str;
      if(!_01Read(str))
         return false;
#ifdef WINDOWS
      sscanf_s(str, "%x", &i);
#else
      sscanf(str, "%x", &i);
#endif
      return true;
   }

   /*bool  tokenizer::_01Read(LPTSTR psz)

   {
   string str;
   if(!_01Read(str))
   return false;
   _tcscpy(psz, str);

   return true;
   }*/

   bool tokenizer::ReadLine(string &strToken,
                            bool bWithSeparator)
   {
      strsize i1 = find("\r\n", m_nCurrentIndex);
      strsize i2 = find("\n", m_nCurrentIndex);
      if(i1 >= 0 && (i1 < i2 || i2 < 0))
      {
         if(bWithSeparator)
            strToken = Mid(m_nCurrentIndex, i1 - m_nCurrentIndex + 2);
         else
            strToken = Mid(m_nCurrentIndex, i1 - m_nCurrentIndex);
         m_nCurrentIndex = i1 + 2;
         return TRUE;
      }
      else if(i2 >= 0)
      {
         if(bWithSeparator)
            strToken = Mid(m_nCurrentIndex, i2 - m_nCurrentIndex + 2);
         else
            strToken = Mid(m_nCurrentIndex, i2 - m_nCurrentIndex);
         m_nCurrentIndex = i2 + 2;
         return TRUE;
      }
      else
      {
         if(m_nCurrentIndex < get_length())
         {
            strToken = Mid(m_nCurrentIndex);
            m_nCurrentIndex = get_length();
            return TRUE;
         }
         else
            return FALSE;
      }
   }
   
   
   ::count tokenizer::skip_word(::count c)
   {
      
      string strToken;
      
      ::count cSkip = 0;
      
      while(c > 0)
      {
         
         if(!get_next_word())
         {
            
            break;
            
         }
         
         cSkip++;
         
         c--;
         
      }
      
      return cSkip;
      
   }
   
   
   string tokenizer::get_word()
   {
      
      string strToken;
      
      if(!_001GetNextToken(strToken))
      {
         
         return "";
         
      }

      return strToken;
      
   }

   
   bool tokenizer::_001GetNextToken(string & strToken)
   {
      
      return get_next_word(&strToken);
      
   }
   

   bool tokenizer::get_next_word(string * pstrToken)
   {

      const char * psz = &c_str()[m_nCurrentIndex];

      const char * pszEnd = psz + strlen(psz);

      const char * pszStart = nullptr;

      strsize iLen;

      while(psz < pszEnd)
      {

         if(::str::ch::is_whitespace(psz))
         {

            if(pszStart != nullptr)
            {

               if(::is_set(pstrToken))
               {

                  iLen = psz - pszStart;

                  pstrToken->assign(pszStart, iLen);
                  
               }

               m_nCurrentIndex = psz - c_str();

               return true;

            }

         }
         else if(*psz == '\"' || *psz == '\'')
         {

            if(pszStart == nullptr)
            {

               pszStart = psz;

            }
            else if(*psz == *pszStart)
            {

               if(::is_set(pstrToken))
               {
                  
                  iLen = psz - pszStart;

                  pstrToken->assign(pszStart + 1, iLen-1);
                  
               }

               m_nCurrentIndex = psz - c_str() + 1;

               return true;

            }

         }
         else
         {

            if(pszStart == NULL)
            {
             
               pszStart = psz;
               
            }
            
         }

         psz = ::str::utf8_inc(psz);

      }

      if(pszStart != nullptr)
      {

         if(*pszStart == '\"' || *pszStart == '\'')
         {

            if(::is_set(pstrToken))
            {
            
               iLen = psz - pszStart;

               pstrToken->assign(pszStart + 1, iLen);
               
            }

            m_nCurrentIndex = psz - c_str();

         }
         else
         {

            if(::is_set(pstrToken))
            {
               
               iLen = psz - pszStart;
               
               pstrToken->assign(pszStart + 1, iLen);
               
            }

            m_nCurrentIndex = psz - c_str();

         }

         return true;

      }

      return false;

   }


} // namespace str




