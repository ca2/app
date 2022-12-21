#pragma once


#include "string.h"


class CLASS_DECL_ACME tokenizer :
   public ::const_ansi_range
{
public:

   using RANGE = ::const_ansi_range;
   using const_iterator = RANGE::const_iterator;


   //RANGE                         m_range;
   const_iterator      m_iterator;


   tokenizer():m_iterator(nullptr) {}
   tokenizer(const tokenizer & range) : const_ansi_range(range) {}
   tokenizer(tokenizer && range) : const_ansi_range(::move(range)) { }
   tokenizer(const ::string & str) : RANGE(str), m_iterator(str.begin()) {}
   ~tokenizer() {}


   tokenizer & operator = (const tokenizer & tokenizer) { ::const_ansi_range::operator=(tokenizer); return *this; }
   tokenizer & operator = (tokenizer && tokenizer) { ::const_ansi_range::operator=(::move(tokenizer)); return *this; }


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

   ::count skip_word(::count c);
      
   ::string get_word();

};


