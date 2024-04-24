#include "framework.h"


not_licensed::not_licensed(const ::scoped_string & scopedstrRealm, const ::scoped_string & scopedstrUrl)
{

   string str;

   m_strRealm     = pszRealm;
   str += "realm=" + m_strRealm + ";";
   m_strUrl       = pszUrl;
   str += "url=" + m_strUrl + ";";

}


not_licensed::~not_licensed()
{

}




