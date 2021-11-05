#include "framework.h"


namespace net
{


   email_address::email_address()
   {

   }


   email_address::email_address(const char * psz)
   {

      operator = (psz);

   }


   email_address::email_address(const email_address & addr)
   {

      operator = (addr);

   }


   email_address & email_address::operator = (const char * psz)
   {
      string str_in(psz);
      string str = str_in;
      auto i = str.find("<");
      if (i != -1)
         str = str.Mid(i + 1);
      i = str.find("@");
      if (i != -1)
      {
         m_strName = str.Mid(0, i);
         str = str.Mid(i + 1);
         i = str.find(">");
         if (i != -1)
            str = str.Mid(0, i);
         m_strDomain = str;
      }
      while (m_strName.get_length() && m_strName[m_strName.get_length() - 1] == ' ')
         m_strName = m_strName.Mid(0, m_strName.get_length() - 1);
      while (m_strDomain.get_length() && m_strDomain[m_strDomain.get_length() - 1] == ' ')
         m_strDomain = m_strDomain.Mid(0, m_strDomain.get_length() - 1);
      while (m_strName.get_length() && m_strName[0] == ' ')
         m_strName = m_strName.Mid(1);
      while (m_strDomain.get_length() && m_strDomain[0] == ' ')
         m_strDomain = m_strDomain.Mid(1);
      m_strTop = m_strDomain;
      {
         for (i32 i = 0; i < m_strDomain.get_length(); i++)
         {
            if (m_strDomain[i] == '.')
            {
               m_strSub = m_strTop;
               m_strTop = m_strDomain.Mid(i + 1);
            }
         }
      }
      return *this;
   }


   email_address & email_address::operator = (const email_address & addr)
   {

      if (this != &addr)
      {

         m_strName = addr.m_strName;
         m_strDomain = addr.m_strDomain;
         m_strTop = addr.m_strTop;
         m_strSub = addr.m_strSub;

      }

      return *this;

   }


} // namespace net



