#pragma once


#include "acme/primitive/string/string.h"


class CLASS_DECL_ACME url_domain_base
{
public:


   string         m_strOriginalName;


   const char *   m_pszRadix;
   strsize        m_iLenRadix;
   const char *   m_pszSuffix;
   strsize        m_iLenSuffix;
   const char *   m_pszDomain;
   strsize        m_iLenDomain;
   const char *   m_pszPrefix;
   strsize        m_iLenPrefix;
   const char *   m_pszTopLevel;
   strsize        m_iLenTopLevel;
   const char *   m_pszName;
   strsize        m_iLenName;

   ::count        m_iCount;
   bool           m_bHasWww;


   url_domain_base();


   void create(const scoped_string & strServerName);


   static string get_name(const scoped_string & strServerName);


};


class CLASS_DECL_ACME url_domain :
   public url_domain_base
{
public:


   string      m_strRadix;
   string      m_strSuffix;
   string      m_strDomain;
   string      m_strPrefix;
   string      m_strTopLevel;
   string      m_strName;

   string      m_strTextRadix;
   string      m_strTextSuffix;
   string      m_strTextDomain;
   string      m_strTextPrefix;
   string      m_strTextTopLevel;
   string      m_strTextName;

   void create(const scoped_string & strServerName);


};



bool CLASS_DECL_ACME server_is_top_domain(const scoped_string & strTop1, strsize iLen1, const scoped_string & strTop2, strsize iLen2);

inline bool CLASS_DECL_ACME server_is_top_domain(string strTop1, string strTop2)
{

   return server_is_top_domain(strTop1, strTop1.get_length(), strTop2, strTop2.get_length());

}


