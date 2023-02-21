#pragma once


//#include "string.h"


class CLASS_DECL_ACME tokenizer :
   public ::ansi_range
{
public:


   using RANGE = ::ansi_range;
   using const_iterator = RANGE::const_iterator;


   //RANGE                         m_range;
   const_iterator      m_iterator;


   tokenizer():m_iterator(nullptr) {}
   tokenizer(const tokenizer & range) : ansi_range(range) {}
   tokenizer(tokenizer && range) : ansi_range(::transfer(range)) { }
   tokenizer(const ::string & str) : RANGE(str), m_iterator(str.begin()) {}
   ~tokenizer() {}


   tokenizer & operator = (const tokenizer & tokenizer) { ::ansi_range::operator=(tokenizer); return *this; }
   tokenizer & operator = (tokenizer && tokenizer) { ::ansi_range::operator=(::transfer(tokenizer)); return *this; }


   //strsize size() const { return m_range.size(); }

   const_iterator find(const ::const_ansi_range & range) const 
   { 
      
      return ::const_ansi_range(m_iterator, this->m_end).find(range, ::comparison::comparison < ::ansi_character >()); 
   
   }

   ::string& substring(::string& str, strsize count)
   {

      str.assign(m_iterator, count);

      return str;

   }


   ::string & substring(::string & str, const_iterator iterator)
   {

      str.assign(m_iterator, iterator);

      return str;

   }


   ::string& substring(::string& str)
   {

      str.assign(m_iterator, m_end - m_iterator);

      return str;

   }


   ::const_ansi_range & substring(::const_ansi_range& range, strsize count)
   {

      range.begin() = m_iterator;
      range.end() = range.begin() + count;

      return range;

   }


   ::const_ansi_range& substring(::const_ansi_range & range, const_iterator iterator)
   {

      range.begin() = m_iterator;
      range.end() = iterator;

      return range;

   }

   
   ::const_ansi_range& substring(::const_ansi_range& range)
   {

      range.begin() = m_iterator;
      range.end() = this->end();

      return range;

   }


   bool ReadLine(::string & str,
                  bool bWithSeparator = false);
   // _01Read read a token if find one of \n\r\t or space
   bool _01Read(i32 & i);
   bool _01Read(::u32 & user);
   bool _01ReadHex(i32 & i);
   bool _01ReadHex(::u32 & user);
   //bool _01Read(char * psz);

   bool _01Read(::string & str);
   bool ExtractFolderPath(const ::scoped_string & scopedstrFilePath);

   void reset() { m_iterator = this->begin(); };
   void reset(const ::string & str) { RANGE::operator= (str); reset(); }
   bool get_next_token(::string &strToken, const ::string & strSeparator, bool bWithSeparator = false);

   bool get_next_smallest_token(::string &strToken, const ::string_array & straSeparator, bool bWithSeparator = false);
   // Any of separator character
   bool get_next_token_ex(::string &strToken, const ::string & strSeparator, bool bWithSeparator = false, bool bSkipAdjacent = false);

   bool _001GetNextToken(::string & strToken);

   bool get_next_word(::string * pstrToken = nullptr);

   strsize read(void* p, strsize s)
   {

      auto iRead = minimum(s, this->m_end - m_iterator);

      ::memcpy(p, m_iterator, iRead);

      m_iterator += iRead;

      return iRead;



   }

   //bool get_line(::string & strLine);

   //bool get_line(::const_ansi_range & strLine);

   template < primitive_range RANGE >
   bool get_line(RANGE & rangeLine)
   {

      if (::is_end(m_iterator, this->end()))
      {

         return false;

      }

      const_iterator iteratorR = find("\r");

      const_iterator iteratorN = find("\n");

      if (::is_ok(iteratorR, this->end()))
      {

         if (::is_ok(iteratorN, this->end()))
         {

            if (iteratorR < iteratorN)
            {

               if (iteratorR + 1 == iteratorN)
               {

                  substring(rangeLine, iteratorR);

                  m_iterator = iteratorN + 1;

               }
               else
               {

                  substring(rangeLine, iteratorR);

                  m_iterator = iteratorR + 1;

               }

            }
            else
            {

               // '\n' < '\r'

               substring(rangeLine, iteratorN);

               m_iterator = iteratorN + 1;

            }

         }
         else
         {

            substring(rangeLine, iteratorR);

            m_iterator = iteratorR + 1;


         }

      }
      else if (::is_ok(iteratorN, this->end()))
      {

         substring(rangeLine, iteratorN);

         m_iterator = iteratorN + 1;

      }
      else
      {

         substring(rangeLine);

         m_iterator = end();

      }

      return true;

   }


   ::count skip_word(::count c);
      
   ::string get_word();

};


