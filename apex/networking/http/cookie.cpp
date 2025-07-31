#include "framework.h"
#include "cookie.h"
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


   string cookie::as_string() const
   {

      return m_payload.as_string();

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
         m_payload     = cookie.m_payload;
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
      str += m_payload;
      if(m_strExpire.has_character())
      {
         str += "; expires=";
         str += m_strExpire;
      }
      if(m_strPath.has_character())
      {
         str += "; path=";
         str += m_strPath;
      }
      if(m_strDomain.has_character())
      {
         str += "; domain=";
         str += m_strDomain;
      }
      if (m_strSameSite.has_character())
      {
         str += "; SameSite=";
         str += m_strSameSite;
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



   ::collection::index cookies::find_cookie(const char * name)
   {

      string strNameLow(name);

      strNameLow.make_lower();

      for(int i = 0; i < this->get_size(); i++)
      {

         if(this->element_at(i)->m_strNameLow == strNameLow)
         {

            return i;

         }

      }

      return -1;

   }

   ::collection::index cookies::lowfind_cookie(const char * name)
   {
      for(int i = 0; i < this->get_size(); i++)
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

      auto iFind = find_cookie(name);

      if(not_found(iFind))
      {

         auto pcookie = __allocate class cookie ();

         pcookie->m_strName = name;

         pcookie->m_strNameLow = pcookie->m_strName.lowered();

         iFind = add(pcookie);

      }

      return *this->element_at(iFind);

   }


   http::cookie & cookies::lowcookie(const char * name)
   {

      auto iFind = lowfind_cookie(name);

      if(::not_found(iFind))
      {

         class cookie ca;

         ca.m_strName = name;

         ca.m_strNameLow = name;

         add(__allocate class cookie (ca));

         iFind = find_cookie(name);

         ASSERT(::found(iFind));

      }

      return *this->element_at(iFind);

   }


   void cookies::add(const ::scoped_string & scopedstr)
   {
      ::pointer<class cookie> cookie(__allocate class cookie ());
      cookie->m_bSecure = false;
      //string_array stra;
      //stra.add_tokens(scopedstr, ";", true);
      auto psz = scopedstr.begin();
      bool bRun = true;
      int i = 0;
      while(bRun)
      {
         const ::ansi_character * pszEnd = ansi_chr(scopedstr, ';');
         bRun = pszEnd != nullptr;
         if(!bRun)
            pszEnd = psz + ansi_len(scopedstr);

         const ::ansi_character * pszEqual = ansi_chr(scopedstr, '=');
         if(scopedstrEqual > pszEnd)
            pszEqual = nullptr;
         if(i == 0)
         {
            if(scopedstrEqual != nullptr)
            { 
               cookie->m_strName = string(scopedstr, pszEqual - psz);
               cookie->m_strNameLow = cookie->m_strName;
               cookie->m_strNameLow.make_lower();
               cookie->m_payload = string(scopedstrEqual + 1, pszEnd - pszEqual - 1);
            }
            else
            {
               return;
            }
         }
         else if(scopedstrEqual != nullptr)
         {
            string strKey = string(scopedstr, pszEqual - psz);
            string strValue = string(scopedstrEqual + 1, pszEnd - pszEqual - 1);
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
            if(string(scopedstr, pszEnd - psz) == "secure")
            {
               cookie->m_bSecure = true;
            }
         }
         i++;
         psz = pszEnd + 1;
      }
      auto iFind = find_cookie(cookie->m_strName);
      if(::not_found(iFind))
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

      for(::collection::index i = 0; i < this->get_size(); i++)
      {

         strCookie += (this->element_at(i)->m_strName + "=" + this->element_at(i)->m_payload);

         strCookie += ";";

      }

      return strCookie;

   }


   character_count cookies::get_length( const char * name)
   {

      return cookie(name).m_payload.as_string().length();

   }


   bool cookies::set_cookie(const ::scoped_string & scopedstrName, const ::payload & payload, const class time & time, const ::scoped_string& scopedstrPath, const ::scoped_string & scopedstrDomain, const ::scoped_string& scopedstrSameSite, bool bSecure)
   {

      auto & cookie = this->cookie(scopedstrName);

      cookie.m_payload = payload;

      if (time > 0_s)
      {

         cookie.m_strExpire = expire(time);

      }

      cookie.m_strPath = scopedstrPath;

      cookie.m_strDomain = scopedstrDomain;

      cookie.m_strSameSite = scopedstrSameSite;

      cookie.m_bSecure = bSecure;

      return true;

   }


   string cookies::expire(const class time & timeExpire)
   {

      auto time = ::time(nullptr);

      time += timeExpire.m_iSecond;

      struct tm tmstruct;

#ifdef _WIN32

      ::memory_copy(&tmstruct, gmtime(&time), sizeof(tmstruct));

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

      strDateTime.formatf("%s, %02d-%s-%04d %02d:%02d:%02d GMT",
         days[tmstruct.tm_wday],
         tmstruct.tm_mday,
         months[tmstruct.tm_mon],
         tmstruct.tm_year + 1900,
         tmstruct.tm_hour,
         tmstruct.tm_min,
         tmstruct.tm_sec);

      return strDateTime;
   }




   void cookies::parse_header(const ::scoped_string & scopedstr)
   {

      if(scopedstr.is_empty())
         return;

      string_array stra;
      const char * pszParam = scopedstr.begin();
      const char * pszParamEnd;
      const char * pszKeyEnd;
      class cookie ca;
      while(true)
      {
         while(*pszParam != '\0' && character_isspace(*pszParam))
         {
            pszParam++;
         }
         if(*pszParam == '\0')
            break;
         pszParamEnd = ansi_chr(scopedstrParam, ';');
         pszKeyEnd = ansi_chr(scopedstrParam, '=');
         if(scopedstrParamEnd == nullptr)
         {

            if(scopedstrKeyEnd == nullptr)
            {

               auto & cookie = this->cookie(scopedstrParam);

               cookie.m_payload.set_type(::e_type_empty);

            }
            else
            {

               auto& cookie = this->cookie(string(scopedstrParam, pszKeyEnd - pszParam));

               cookie.m_payload = string(scopedstrKeyEnd + 1);

            }

            return;

         }
         else
         {

            if(scopedstrKeyEnd == nullptr || pszKeyEnd > pszParamEnd)
            {

               auto& cookie = this->cookie(string(scopedstrParam, pszParamEnd - pszParam));

               cookie.m_payload.set_type(::e_type_empty);

            }
            else
            {

               auto& cookie = this->cookie(string(scopedstrParam, pszKeyEnd - pszParam));

               cookie.m_payload = string(scopedstrKeyEnd + 1, pszParamEnd - (scopedstrKeyEnd + 1));

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
