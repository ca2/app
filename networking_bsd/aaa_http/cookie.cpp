#include "framework.h"
#include <time.h>


namespace http
{


   cookie::cookie()
   {

      m_bSecure = false;

   }


   cookie::cookie(const cookie & cookie)
   {

      operator = (cookie);

   }


   string cookie::get_string() const
   {

      return m_varValue.get_string();

   }


   cookie::~cookie()
   {

   }


   cookie & cookie::operator = (const cookie & cookie)
   {

      if(&cookie != this)
      {

         m_strName      = cookie.m_strName;
         m_strNameLow   = cookie.m_strNameLow;
         m_varValue     = cookie.m_varValue;
         m_strExpire    = cookie.m_strExpire;
         m_strPath      = cookie.m_strPath;
         m_strDomain    = cookie.m_strDomain;
         m_bSecure      = cookie.m_bSecure;

      }

      return *this;

   }


   string cookie::get_cookie_string()
   {
      string str;
      str = m_strName;
      str += "=";
      str += m_varValue.string();
      if(m_strExpire.has_char())
      {
         str += "; expires=";
         str += m_strExpire;
      }
      if(m_strPath.has_char())
      {
         str += "; path=";
         str += m_strPath;
      }
      if(m_strDomain.has_char())
      {
         str += "; domain=";
         str += m_strDomain;
      }
      if(m_bSecure)
      {
         str += "; secure";
      }
      return str;
   }

   cookies::cookies()
   {

   }

   cookies::~cookies()
   {

   }



   index cookies::find_cookie(const char * name)
   {

      string strNameLow(name);

      strNameLow.make_lower();

      for(i32 i = 0; i < this->get_size(); i++)
      {

         if(this->element_at(i)->m_strNameLow == strNameLow)
         {

            return i;

         }

      }

      return -1;

   }

   index cookies::lowfind_cookie(const char * name)
   {
      for(i32 i = 0; i < this->get_size(); i++)
      {
         if(this->element_at(i)->m_strNameLow == name)
         {
            return i;
         }
      }
      return -1;
   }

   http::cookie & cookies::cookie(const char * name)
   {

      index iFind = find_cookie(name);

      if(iFind < 0)
      {

         auto pcookie = __new(class cookie);

         pcookie->m_strName = name;

         pcookie->m_strNameLow = pcookie->m_strName.lowered();

         iFind = add(pcookie);

      }

      return *this->element_at(iFind);

   }


   http::cookie & cookies::lowcookie(const char * name)
   {

      index iFind = lowfind_cookie(name);

      if(iFind < 0)
      {

         class cookie ca;

         ca.m_strName = name;

         ca.m_strNameLow = name;

         add(__new(class cookie(ca)));

         iFind = find_cookie(name);

         ASSERT(iFind >= 0);

      }

      return *this->element_at(iFind);

   }


   void cookies::add(const char * psz)
   {
      ::pointer<class cookie> cookie(__new(class cookie));
      cookie->m_bSecure = false;
      //string_array stra;
      //stra.add_tokens(psz, ";", true);
      bool bRun = true;
      i32 i = 0;
      while(bRun)
      {
         const char * pszEnd = strchr(psz, ';');
         bRun = pszEnd != nullptr;
         if(!bRun)
            pszEnd = psz + strlen(psz);

         const char * pszEqual = strchr(psz, '=');
         if(pszEqual > pszEnd)
            pszEqual = nullptr;
         if(i == 0)
         {
            if(pszEqual != nullptr)
            {
               cookie->m_strName = string(psz, pszEqual - psz);
               cookie->m_strNameLow = cookie->m_strName;
               cookie->m_strNameLow.make_lower();
               cookie->m_varValue = string(pszEqual + 1, pszEnd - pszEqual - 1);
            }
            else
            {
               return;
            }
         }
         else if(pszEqual != nullptr)
         {
            string strKey = string(psz, pszEqual - psz);
            string strValue = string(pszEqual + 1, pszEnd - pszEqual - 1);
            if(strKey == "expires")
            {
               cookie->m_strExpire = strValue;
            }
            else if(strKey == "domain")
            {
               cookie->m_strDomain = strValue;
            }
            else if(strKey == "path")
            {
               cookie->m_strPath = strValue;
            }
         }
         else
         {
            if(string(psz, pszEnd - psz) == "secure")
            {
               cookie->m_bSecure = true;
            }
         }
         i++;
         psz = pszEnd + 1;
      }
      index iFind = find_cookie(cookie->m_strName);
      if(iFind < 0)
      {
         add(cookie);
         return;
      }
      this->element_at(iFind) = cookie;
      return;
   }


   string cookies::get_cookie_header()
   {
      string strCookie;
      for(index i = 0; i < this->get_size(); i++)
      {
         strCookie += (const char *) (this->element_at(i)->m_strName + "=" + this->element_at(i)->m_varValue.string());
         strCookie += ";";
      }
      return strCookie;
   }


   strsize cookies::get_length( const char * name)
   {
      return cookie(name).m_varValue.string().get_length();
   }


   bool cookies::set_cookie(const char * name, const ::payload & payload, const ::duration & duration, const char * path, const char * domain, bool bSecure)
   {

      auto & cookie = this->cookie(name);

      cookie.m_varValue = payload;

      if (duration)
      {

         cookie.m_strExpire = expire(duration);

      }

      cookie.m_strPath = path;

      cookie.m_strDomain = domain;

      cookie.m_bSecure = bSecure;

      return true;

   }


   string cookies::expire(const duration & duration)
   {

      auto time = ::time(nullptr);

      time += duration.integral_second().m_i;

      struct tm tmstruct;

#ifdef _WIN32

      ::memcpy_dup(&tmstruct, gmtime(&time), sizeof(tmstruct));

#else

      gmtime_r(&time, &tmstruct);

#endif

      const char *days[7] = {"Sunday", "Monday",
                             "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
                            };
      const char *months[12] = {"Jan", "Feb", "Mar", "Apr", "May",
                                "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
                               };
      string strDateTime;

      strDateTime.format("%s, %02d-%s-%04d %02d:%02d:%02d GMT",
         days[tmstruct.tm_wday],
         tmstruct.tm_mday,
         months[tmstruct.tm_mon],
         tmstruct.tm_year + 1900,
         tmstruct.tm_hour,
         tmstruct.tm_min,
         tmstruct.tm_sec);

      return strDateTime;
   }




   void cookies::parse_header(const char * psz)
   {

      if(psz == nullptr)
         return;

      string_array stra;
      const char * pszParam = psz;
      const char * pszParamEnd;
      const char * pszKeyEnd;
      class cookie ca;
      while(true)
      {
         while(*pszParam != '\0' && isspace((uchar ) *pszParam))
         {
            pszParam++;
         }
         if(*pszParam == '\0')
            break;
         pszParamEnd = strchr(pszParam, ';');
         pszKeyEnd = strchr(pszParam, '=');
         if(pszParamEnd == nullptr)
         {

            if(pszKeyEnd == nullptr)
            {

               auto & cookie = this->cookie(pszParam);

               cookie.m_varValue.set_type(::e_type_empty);

            }
            else
            {

               auto& cookie = this->cookie(string(pszParam, pszKeyEnd - pszParam));

               cookie.m_varValue = string(pszKeyEnd + 1);

            }

            return;

         }
         else
         {

            if(pszKeyEnd == nullptr || pszKeyEnd > pszParamEnd)
            {

               auto& cookie = this->cookie(string(pszParam, pszParamEnd - pszParam));

               cookie.m_varValue.set_type(::e_type_empty);

            }
            else
            {

               auto& cookie = this->cookie(string(pszParam, pszKeyEnd - pszParam));

               cookie.m_varValue = string(pszKeyEnd + 1, pszParamEnd - (pszKeyEnd + 1));

            }

         }

         pszParam = pszParamEnd + 1;

      }

   }

   http::cookie & cookies::operator [](const char * name)
   {
      return cookie(name);
   }
   cookies & cookies::operator = (const cookies & cookies)
   {

      if(this != &cookies)
      {

         pointer_array < ::http::cookie >::operator =((pointer_array < ::http::cookie > &) cookies);

      }

      return *this;

   }


} // namespace http
