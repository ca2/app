#include "framework.h"
//#include "tokenizer.h"
#include <stdio.h>
//#include "acme/memory/_memory.h"
//#include "acme/prototype/collection/string_array.h"

//
//tokenizer::tokenizer()
//{
//
//   Restart();
//
//}
//
//
//tokenizer::~tokenizer()
//{
//
//}
//
//
//tokenizer::tokenizer(const ::block & block) :
//   m_block(block)
//{
//
//   Restart();
//
//}
//

//tokenizer::tokenizer(const ::scoped_string & scopedstrSrc) :
//   m_str(strSrc)
//{
//
//   Restart();
//
//}


//character_count tokenizer::find(const ::block& blockSeparator) const
//{
//
//   return m_block.find(blockSeparator, m_nCurrentIndex);
//
//}


bool tokenizer::get_next_token(::string & strToken, const ::scoped_string & scopedstrSeparator, bool bWithSeparator)
{

   const_iterator iterator;

   if((iterator = find(scopedstrSeparator)) != nullptr)
   {

      if (bWithSeparator)
      {
       
         substring(strToken, iterator + scopedstrSeparator.size());

      }
      else
      {
       
         substring(strToken, iterator);

      }

      m_iterator = iterator + scopedstrSeparator.size();

      return true;

   }
   else
   {

      if(m_iterator <= this->end() - 1)
      {
         
         substring(strToken);
         
         m_iterator = end();

         return true;

      }
      else
      {

         return false;

      }

   }

}


//bool tokenizer::get_line(string& strLine)
//{
//
//   if (::is_end(m_iterator, this->end()))
//   {
//
//      return false;
//
//   }
//
//   const_iterator iteratorR = find("\r");
//
//   const_iterator iteratorN = find("\n");
//
//   const_iterator iterator;
//
//   if (::is_ok(iteratorR, this->end()))
//   {
//
//      if (::is_ok(iteratorN, this->end()))
//      {
//
//         if (iteratorR < iteratorN)
//         {
//
//            if (iteratorR + 1 == iteratorN)
//            {
//
//               substring(strLine, iteratorR);
//
//               m_iterator = iteratorN + 1;
//
//            }
//            else
//            {
//
//               substring(strLine, iteratorR);
//
//               m_iterator = iteratorR + 1;
//
//            }
//
//         }
//         else
//         {
//
//            // '\n' < '\r'
//
//            substring(strLine, iteratorN);
//
//            m_iterator = iteratorN + 1;
//
//         }
//
//      }
//      else
//      {
//
//         substring(strLine, iteratorR);
//
//         m_iterator = iteratorR + 1;
//
//
//      }
//
//   }
//   else if (::is_ok(iteratorN, this->end()))
//   {
//
//      substring(strLine, iteratorN);
//
//      m_iterator = iteratorN + 1;
//
//   }
//   else
//   {
//
//      substring(strLine);
//
//      m_iterator = end();
//
//      return true;
//
//   }
//
//}
//
//
//bool tokenizer::get_line(string& strLine)
//{
//
//   if (::is_end(m_iterator, this->end()))
//   {
//
//      return false;
//
//   }
//
//   const_iterator iteratorR = find("\r");
//
//   const_iterator iteratorN = find("\n");
//
//   const_iterator iterator;
//
//   if (::is_ok(iteratorR, this->end()))
//   {
//
//      if (::is_ok(iteratorN, this->end()))
//      {
//
//         if (iteratorR < iteratorN)
//         {
//
//            if (iteratorR + 1 == iteratorN)
//            {
//
//               substring(strLine, iteratorR);
//
//               m_iterator = iteratorN + 1;
//
//            }
//            else
//            {
//
//               substring(strLine, iteratorR);
//
//               m_iterator = iteratorR + 1;
//
//            }
//
//         }
//         else
//         {
//
//            // '\n' < '\r'
//
//            substring(strLine, iteratorN);
//
//            m_iterator = iteratorN + 1;
//
//         }
//
//      }
//      else
//      {
//
//         substring(strLine, iteratorR);
//
//         m_iterator = iteratorR + 1;
//
//
//      }
//
//   }
//   else if (::is_ok(iteratorN, this->end()))
//   {
//
//      substring(strLine, iteratorN);
//
//      m_iterator = iteratorN + 1;
//
//   }
//   else
//   {
//
//      substring(strLine);
//
//      m_iterator = end();
//
//      return true;
//
//   }
//
//}


bool tokenizer::get_next_smallest_token(string & strToken, const string_array & straSeparator, bool bWithSeparator)
{

   const_iterator iteratorMinPos = m_end;

   if(m_iterator >= iteratorMinPos)
   {

      return false;

   }

   character_count iMaxSepLen = 0;

   const_iterator iterator;

   for(int j = 0; j < straSeparator.get_size(); j++)
   {

      iterator = find(straSeparator[j]);

      if(iterator >= this->begin() && iterator < iteratorMinPos)
      {

         if(iteratorMinPos == iterator)
         {

            if(straSeparator[j].size() > iMaxSepLen)
            {

               iMaxSepLen = straSeparator[j].size();

            }

         }
         else
         {

            iteratorMinPos = iterator;

            iMaxSepLen = straSeparator[j].size();

         }

      }

   }

   if (bWithSeparator)
   {

      substring(strToken, iteratorMinPos + iMaxSepLen);

   }
   else
   {

      substring(strToken, iteratorMinPos);

   }

   m_iterator = iteratorMinPos + iMaxSepLen;

   return true;

}


bool tokenizer::get_next_token_ex(string &strToken, const ::scoped_string & scopedstrSeparator, bool bWithSeparator, bool bSkipAdjacent)
{

   character_count i;

   string strMid;
   
   substring(strMid);

   if(found(i = strMid.find_first_character_in_index(scopedstrSeparator)))
   {

      if (bWithSeparator)
      {

         strToken = strMid.left(i + 1);

      }
      else
      {

         strToken = strMid.left(i);

      }

      m_iterator += i + 1;

      if(bSkipAdjacent)
      {

         m_iterator = (*this)(m_iterator).skip_any_character_in(scopedstrSeparator);

      }

      return true;

   }
   else
   {

      if (m_iterator <= this->end() - 1)
      {

         substring(strToken);

         m_iterator = this->end();

         return true;

      }
      else
      {

         return false;

      }

   }

}


bool tokenizer::ExtractFolderPath(const ::scoped_string & scopedstrFilePath)
{

   string strFilePath(scopedstrFilePath);

   character_count i = strFilePath.length();

   bool b = false;

   while(i > 0)
   {

      i--;

      if(strFilePath[i] == '/' || strFilePath[i] == '\\')
      {

         b = true;

         break;

      }

   }

   operator=(strFilePath.left(i));

   return b;

}


bool tokenizer::_01Read(string &str)
{

   if (!get_next_token_ex(str, "\n\r\t ", false, true))
   {

      return false;

   }

   if (str.is_empty())
   {

      if (!get_next_token_ex(str, "\n\r\t ", false, true))
      {

         return false;

      }

   }

   return true;

}


bool tokenizer::_01Read(unsigned int & user)
{

   int i;

   if (!_01Read(i))
   {

      return false;

   }

   user = (unsigned int) i;

   return true;

}


bool tokenizer::_01Read(int &i)
{

   string str;

   if (!_01Read(str))
   {

      return false;

   }

   i = atoi(str);

   return true;

}


bool tokenizer::_01ReadHex(unsigned int & user)
{

   int i;

   if (!_01ReadHex(i))
   {

      return false;

   }

   user = (unsigned int) i;

   return true;

}


bool tokenizer::_01ReadHex(int &i)
{

   string str;

   if (!_01Read(str))
   {

      return false;

   }

#ifdef WINDOWS

   sscanf_s(str, "%x", &i);

#else

   sscanf(str, "%x", &i);

#endif

   return true;

}


bool tokenizer::ReadLine(string &strToken, bool bWithSeparator)
{

   auto p1 = find("\r\n");

   auto p2 = find("\n");

   if(::is_set(p1) && (p1 < p2 || ::is_null(p2)))
   {

      if (bWithSeparator)
      {
          
         substring(strToken, p1 + 2);

      }
      else
      {

         substring(strToken, p1);

      }

      m_iterator = p1 + 2;

      return true;

   }
   else if(::is_set(p2))
   {

      if (bWithSeparator)
      {

         substring(strToken, p2 + 1);

      }
      else
      {

         substring(strToken, p2);

      }

      m_iterator = p2 + 1;

      return true;

   }
   else
   {

      if(m_iterator < this->end() - 1)
      {

         substring(strToken);

         m_iterator = this->end();

         return true;

      }
      else
      {

         return false;

      }

   }

}
   
   
::collection::count tokenizer::skip_word(::collection::count c)
{
      
   string strToken;
      
   ::collection::count cSkip = 0;
      
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


bool tokenizer::get_word(::string & strWord)
{

   return _001GetNextToken(strWord);

}


bool tokenizer::_001GetNextToken(string & strToken)
{
      
   return get_next_word(&strToken);
      
}
   

bool tokenizer::get_next_word(string * pstrToken)
{

   const_char_pointer psz = m_iterator;

   const_char_pointer pszEnd = this->end();

   const_char_pointer pszStart = nullptr;

   while(psz < pszEnd)
   {

      if(unicode_is_whitespace(psz))
      {

         if(pszStart != nullptr)
         {

            if(::is_set(pstrToken))
            {

               pstrToken->assign(pszStart, psz);
                  
            }

            m_iterator = psz;

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
                  
               pstrToken->assign(pszStart + 1, psz - 1);
                  
            }

            m_iterator = psz + 1;

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

      unicode_increment(psz);

   }

   if(pszStart != nullptr)
   {

      if(*pszStart == '\"' || *pszStart == '\'')
      {

         if(::is_set(pstrToken))
         {
            
            pstrToken->assign(pszStart + 1, psz);
               
         }

         m_iterator = psz;

      }
      else
      {

         if(::is_set(pstrToken))
         {
               
            pstrToken->assign(pszStart, psz);
               
         }

         m_iterator = psz;

      }

      return true;

   }

   return false;

}




