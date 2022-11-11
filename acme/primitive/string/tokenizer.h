#pragma once


#include "string.h"


class CLASS_DECL_ACME tokenizer
{
public:

   ::string       m_str;
   strsize        m_nCurrentIndex;


   tokenizer();
   tokenizer(const ::string & strSrc);
   tokenizer(const char * pch, i32 nLength );
   ~tokenizer();


   bool ReadLine(string & str,
                  bool bWithSeparator = false);
   // _01Read read a token if find one of \n\r\t or space
   bool _01Read(i32 & i);
   bool _01Read(::u32 & user);
   bool _01ReadHex(i32 & i);
   bool _01ReadHex(::u32 & user);
   //bool _01Read(char * psz);

   bool _01Read(string & str);
   bool ExtractFolderPath(const char * pcszFilePath);

   void Restart();
   void Restart(string &strNew);
   bool GetNextToken(string &strToken, const char * pSeparator, bool bWithSeparator = false);

   bool GetNextSmallestToken(string &strToken, const ::string_array & straSeparator, bool bWithSeparator = false);
   // Any of separator character
   bool GetNextTokenEx(string &strToken, const char * pSeparator, bool bWithSeparator = false, bool bSkipAdjacent = false);

   bool _001GetNextToken(string & strToken);

   bool get_next_word(string * pstrToken = nullptr);

   ::count skip_word(::count c);
      
   string get_word();

};


