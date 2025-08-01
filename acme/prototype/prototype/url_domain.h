// url_domain_base based on particle for once upon a time globals by
// camilo on 204-06-03 17:50 <3ThomasBorregaardSorensen!!
#pragma once


class CLASS_DECL_ACME url_domain_base :
   virtual public ::particle
{
public:


   string         m_strOriginalName;


   const_char_pointer  m_pszRadix;
   character_count        m_iLenRadix;
   const_char_pointer  m_pszSuffix;
   character_count        m_iLenSuffix;
   const_char_pointer  m_pszDomain;
   character_count        m_iLenDomain;
   const_char_pointer  m_pszPrefix;
   character_count        m_iLenPrefix;
   const_char_pointer  m_pszTopLevel;
   character_count        m_iLenTopLevel;
   const_char_pointer  m_pszName;
   character_count        m_iLenName;

   ::collection::count        m_iCount;
   bool           m_bHasWww;


   url_domain_base();


   void create(const ::scoped_string & scopedstrServerName);


   virtual string get_name(const ::scoped_string & scopedstrServerName);


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

   void create(const ::scoped_string & scopedstrServerName);


};



bool CLASS_DECL_ACME server_is_top_domain(const_char_pointer  pszTop1, character_count iLen1, const_char_pointer  pszTop2, character_count iLen2);

inline bool CLASS_DECL_ACME server_is_top_domain(string strTop1, string strTop2)
{

   return server_is_top_domain(strTop1, strTop1.length(), strTop2, strTop2.length());

}


