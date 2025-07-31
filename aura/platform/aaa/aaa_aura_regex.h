#pragma once


class CLASS_DECL_AURA regex :
   virtual public object
{
public:


   virtual int matches(const ::scoped_string & scopedstr) = 0;

   virtual int matches(const ::scoped_string & scopedstr, character_count len) = 0;

   virtual void matches(strsize_array& ia, const ::scoped_string & scopedstr) = 0;

   virtual void matches(strsize_array& ia, const ::scoped_string & scopedstr, character_count len) = 0;

   virtual bool replace(string& str, const ::scoped_string & scopedstrPrefix, string& strRet) = 0;

   //virtual int matches(const ::scoped_string & scopedstr, regex_context* pcreContext = nullptr) = 0;

   //virtual int matches(const ::scoped_string & scopedstr, character_count len, regex_context* pcreContext = nullptr) = 0;

   //virtual void matches(strsize_array& ia, const ::scoped_string & scopedstr, regex_context* pcreContext = nullptr) = 0;

   //virtual void matches(strsize_array& ia, const ::scoped_string & scopedstr, character_count len, regex_context* pcreContext = nullptr) = 0;

   //virtual bool replace(string& str, const ::scoped_string & scopedstrPrefix, string& strRet, regex_context* pcreContext = nullptr) = 0;


};

class CLASS_DECL_AURA regex_context :
   virtual public ::object
{
public:

   virtual ::pointer<regex>compile(const ::scoped_string & scopedstr) = 0;

};

