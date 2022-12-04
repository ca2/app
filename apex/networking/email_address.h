#pragma once


#include "acme/primitive/string/string.h"


namespace networking
{


   class CLASS_DECL_APEX email_address
   {
   public:


      string      m_strName;
      string      m_strDomain;
      string      m_strTop;
      string      m_strSub;


      email_address();
      email_address(const ::string & strEmail);
      email_address(const email_address & addr);


      string get_name()          const { return m_strName; }
      string get_domain()        const { return m_strDomain; }
      string get_top_domain()    const { return m_strTop; }
      string get_sub_domain()    const { return m_strSub; }


      string to_string() const { return m_strName + "@" + m_strDomain; }


      void set_email_address(const ::string & strEmail);


      email_address & operator = (const email_address & addr);


   };



} // namespace net



