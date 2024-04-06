#pragma once


class CLASS_DECL_ACME not_licensed :
   public ::exception
{
public:


   string      m_strRealm;    // license realm
   string      m_strUrl;      // licensing url


   not_licensed(const ::scoped_string & scopedstrRealm, const ::scoped_string & scopedstrUrl);
   virtual ~not_licensed();


};
