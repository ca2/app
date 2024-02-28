#include "framework.h"
#include "email_address.h"


namespace networking
{


   email_address::email_address()
   {

   }


   email_address::email_address(const ::scoped_string& scopedstrEmail)
   {

      set_email_address(scopedstrEmail);

   }


   email_address::email_address(const email_address & addr)
   {

      operator = (addr);

   }


   void email_address::set_email_address(const ::scoped_string& scopedstrEmail)
   {
      string str_in(scopedstrEmail);
      string str = str_in;
      auto i = str.find_index("<");
      if (i != -1)
         str = str.substr(i + 1);
      i = str.find_index("@");
      if (i != -1)
      {
         m_strName = str.substr(0, i);
         str = str.substr(i + 1);
         i = str.find_index(">");
         if (i != -1)
            str = str.substr(0, i);
         m_strDomain = str;
      }
      while (m_strName.length() && m_strName[m_strName.length() - 1] == ' ')
         m_strName = m_strName.substr(0, m_strName.length() - 1);
      while (m_strDomain.length() && m_strDomain[m_strDomain.length() - 1] == ' ')
         m_strDomain = m_strDomain.substr(0, m_strDomain.length() - 1);
      while (m_strName.length() && m_strName[0] == ' ')
         m_strName = m_strName.substr(1);
      while (m_strDomain.length() && m_strDomain[0] == ' ')
         m_strDomain = m_strDomain.substr(1);
      m_strTop = m_strDomain;
      {
         for (i32 i = 0; i < m_strDomain.length(); i++)
         {
            if (m_strDomain[i] == '.')
            {
               m_strSub = m_strTop;
               m_strTop = m_strDomain.substr(i + 1);
            }
         }
      }
      //return *this;
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



