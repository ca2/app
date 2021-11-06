#pragma once


class CLASS_DECL_ACME assert_exception :
   public ::exception
{
public:


   string m_strFile;
   long m_lLine;


   assert_exception(const char * pszFile, long lLine);
   virtual ~assert_exception();


};
