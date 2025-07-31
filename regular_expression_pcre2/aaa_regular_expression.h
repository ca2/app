#pragma once


namespace regular_expression_pcre2
{


   class CLASS_DECL_AXIS regular_expression :
      virtual public ::regular_expression::regular_expression
   {
   public:


      regular_expression();
      virtual ~regular_expression();




      //virtual int matches(const ::scoped_string & scopedstr, regex_context* pcreContext = nullptr) = 0;

      //virtual int matches(const ::scoped_string & scopedstr, character_count len, regex_context* pcreContext = nullptr) = 0;

      //virtual void matches(strsize_array& ia, const ::scoped_string & scopedstr, regex_context* pcreContext = nullptr) = 0;

      //virtual void matches(strsize_array& ia, const ::scoped_string & scopedstr, character_count len, regex_context* pcreContext = nullptr) = 0;

      //virtual bool replace(string& str, const ::scoped_string & scopedstrPrefix, string& strRet, regex_context* pcreContext = nullptr) = 0;



   /*   virtual int matches(const ::scoped_string & scopedstr) = 0;

      virtual int matches(const ::scoped_string & scopedstr, character_count len) = 0;

      virtual int matches(strsize_array& ia, const ::scoped_string & scopedstr) = 0;

      virtual int matches(strsize_array& ia, const ::scoped_string & scopedstr, character_count len) = 0;

      virtual bool replace(string& str, const ::scoped_string & scopedstrPrefix, string& strRet) = 0;*/

   };


} // namespace regular_expression



