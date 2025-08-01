#pragma once


namespace str
{
   

   class CLASS_DECL_ACME tokenizer : public string
   {
   protected:


      character_count      m_nCurrentIndex;


   public:


      tokenizer(const ::scoped_string & scopedstrSrc);
      tokenizer(const char * pch, int nLength );

      tokenizer();
      virtual ~tokenizer();


      bool ReadLine(string & str,
                    bool bWithSeparator = false);
      // _01Read read a token if find one of \n\r\t or space
      bool _01Read(int & i);
      bool _01Read(unsigned int & user);
      bool _01ReadHex(int & i);
      bool _01ReadHex(unsigned int & user);
      //bool _01Read(char * psz);

      bool _01Read(string & str);
      bool ExtractFolderPath(const ::scoped_string & scopedstrFilePath);

      void Restart();
      void Restart(string &strNew);
      bool GetNextToken(string &strToken, const char * pSeparator, bool bWithSeparator = false);

      bool GetNextSmallestToken(string &strToken, const string_array & straSeparator, bool bWithSeparator = false);
      // Any of separator character
      bool GetNextTokenEx(string &strToken, const char * pSeparator, bool bWithSeparator = false, bool bSkipAdjacent = false);

      bool _001GetNextToken(string & strToken);

      bool get_next_word(string * pstrToken = nullptr);

      ::collection::count skip_word(::collection::count c);
      
      string get_word();

   };



} // namespace string



