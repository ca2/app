#pragma once


namespace regular_expression_pcre2
{


   class CLASS_DECL_AXIS regular_expression :
      virtual public ::regular_expression::regular_expression
   {
   public:


      regular_expression();
      virtual ~regular_expression();




      //virtual int matches(const string& str, regex_context* pcreContext = nullptr) = 0;

      //virtual int matches(const char* psz, strsize len, regex_context* pcreContext = nullptr) = 0;

      //virtual void matches(strsize_array& ia, const string& str, regex_context* pcreContext = nullptr) = 0;

      //virtual void matches(strsize_array& ia, const char* psz, strsize len, regex_context* pcreContext = nullptr) = 0;

      //virtual bool replace(string& str, const string& strPrefix, string& strRet, regex_context* pcreContext = nullptr) = 0;



   /*   virtual int matches(const string& str) = 0;

      virtual int matches(const char* psz, strsize len) = 0;

      virtual int matches(strsize_array& ia, const string& str) = 0;

      virtual int matches(strsize_array& ia, const char* psz, strsize len) = 0;

      virtual bool replace(string& str, const string& strPrefix, string& strRet) = 0;*/

   };


} // namespace regular_expression



