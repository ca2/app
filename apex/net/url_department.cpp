#include "framework.h"
#include "apex/id.h"
#include "apex/astr.h"

#ifdef WINDOWS_DESKTOP
#include "idn/idna.h"
#elif defined(ANDROID)
#include "idn/idna.h"
#elif defined(__APPLE__)
#include <idn/idna.h>
#elif defined(LINUX)
// at Ubuntu - libidn11-dev
#include <idna.h>
#endif


namespace url
{


   department::department()
   {

   }

   department::~department()
   {

   }


   string department::get_protocol(const char * psz)
   {
      string str(psz);
      index iPos = str.find(":");
      if(iPos == -1)
         return "";
      return str.Mid(0, iPos);
   }


   string department::get_root(const char * psz)
   {
      string str(psz);
      index iPos = str.find(":");
      if(iPos == -1)
         return psz;
      iPos++;
      while(iPos < str.get_length() && str[iPos] == '/')
      {
         iPos++;
      }
      index iStart = iPos;
      index iEnd = str.find("/", iStart);
      if(iEnd < 0)
         return str.Mid(iStart);
      else
         return str.Mid(iStart, iEnd - iStart);
   }

   string department::get_server(const char * psz)
   {

      string strRoot = get_root(psz);

      strsize iPos = strRoot.find(":");

      if(iPos < 0)
         return strRoot;

      return strRoot.Left(iPos);

   }

   i32 department::get_port(const char * psz, i32 iDefault)
   {

      string strRoot = get_root(psz);

      strsize iPos = strRoot.find(":");

      if(iPos < 0)
      {

         if(iDefault == -1)
         {

            string strProtocol = get_protocol(psz);

            if(strProtocol == "http")
               return 80;
            else if(strProtocol == "https")
               return 443;
            else if(strProtocol == "ftp")
               return 21;

         }

         return iDefault;

      }

      return atoi(strRoot.Mid(iPos + 1));

   }

   string department::get_object(const char * psz)
   {

      string str(psz);

      strsize iPos = str.find("://");

      if(iPos < 0)
         return psz;

      iPos += 3;

      strsize iStart = str.find("/", iPos);

      if(iStart < 0)
         return "/";
      else
         return str.Mid(iStart);

   }

   string department::object_get_script(const char * psz) // page
   {

      string str(psz);

      strsize iFind = str.find('?');

      if(iFind < 0)
         return url_decode(str);
      else
         return url_decode(str.Left(iFind));

   }

   string department::object_get_query(const char * psz) // id=1
   {

      string str(psz);

      strsize iFind = str.find('?');

      if(iFind < 0)
         return "";
      else
         return str.Mid(iFind + 1);

   }

   string department::object_set(const char * pszObject, const char * pszKey, payload payload)
   {

      string strQuery = object_get_query(pszObject);

      return object_get_script(pszObject) + ::str::has_char(query_set(strQuery, pszKey, payload), "?");

   }


   string department::get_script(const char * psz) // page
   {

      return object_get_script(get_object(psz));

   }

   string department::get_query(const char * psz) // id=1
   {

      return object_get_query(get_object(psz));

   }

   string department::object(const char * pszScript, const char * pszQuery)
   {

      string strScript(pszScript);

      string strQuery(pszQuery);

      if(strQuery.has_char())
         return strScript + "?" + strQuery;
      else
         return strScript;

   }


   string department::path(const char * psz1, const char * psz2)
   {

      if(psz2 == nullptr)
         return psz1;

      string str1(psz1);

      string str2(psz2);

      if(str1.Right(1) == "/")
         str1 = str1.Left(str1.get_length() - 1);

      if(str2.Left(1) == "/")
         str2 = str2.Right(str2.get_length() - 1);

      return str1 + "/" + str2;

   }

   string department::path(const char * psz1, const char * psz2, const char * psz3)
   {

      return path(path(psz1, psz2), psz3);

   }

   string department::name(const char * psz)
   {

      string str(psz);

      strsize iQueryStart = str.find('?');

      if(iQueryStart < 0)
         iQueryStart = str.get_length();

      str = str.Left(iQueryStart);

      strsize iLastSlash = str.reverse_find('/');

      if(iLastSlash < 0)
         return "";
      else
         return str.Left(iLastSlash);

   }


   string department::url_encode(const char * psz)
   {

      return ::url_encode(psz);

   }


   string department::url_decode(const char * psz)
   {

      return ::url_decode(psz);

   }


   string department::url_decode(const char * pszUrl, strsize iLen)

   {

      return ::url_decode(pszUrl,iLen);


   }

   string department::query_append(const char * pszUrl, const char * pszQuery)
   {

      string strUrl(pszUrl);

      strsize iStart = strUrl.find("://");

      if(iStart > 0)
      {

         iStart = strUrl.find("/", iStart + 4);

         if(iStart < 0)
         {

//xxx            TRACE("invalid url %s", pszUrl);

            iStart = 0;

         }
      }
      else
      {

         iStart = 0;

      }

      if(strUrl.find("?", iStart) > 0)
      {

         return strUrl + "&" + pszQuery;

      }
      else
      {

         return strUrl + "?" + pszQuery;

      }

   }


   bool department::is_url(const char * pszCandidate)
   {

      string strCandidate(pszCandidate);

      strsize iLen = strCandidate.get_length();

      strsize i = 0;

      char ch;

      while(i < iLen)
      {

         ch = strCandidate[i];

         if(isalpha((uchar) ch))
            i++;
         else if(ch == '.')
            i++;
         else if(ch == ':' && (((i + 1) == iLen) ||
                               (iLen > (i + 3)
                                && strCandidate[i + 1] == '/'
                                && strCandidate[i + 2] == '/')))
            return true;
         else
            return false;

      }

      return false;

   }


   payload & department::var_set(payload & varUrl, const char * pszKey, payload payload)
   {

      return varUrl = set_key(varUrl, pszKey, payload);

   }


   property & department::property_set(property & propUrl, const char * pszKey, payload payload)
   {

      propUrl = set_key(propUrl, pszKey, payload);

      return propUrl;

   }


   string department::string_set(string & strUrl, const char * pszKey, payload payload)
   {

      return strUrl = set_key(strUrl, pszKey, payload);

   }


   string department::string_set_if_not_empty(string& strUrl, const char* pszKey, payload payload)
   {

      if (payload.is_empty())
      {

         return strUrl;

      }

      return string_set(strUrl, pszKey, payload);

   }

   string department::set_key(const char * pszUrl, const char * pszKey, payload payload)
   {

      string strUrl(pszUrl);

      strsize iPos = strUrl.find("?");

      if(iPos < 0)
         iPos = strUrl.get_length();

      return strUrl.Left(iPos)
             + "?" +
             query_set(strUrl.Mid(iPos + 1), pszKey, payload);

   }

   void department::set_key(string & strUrl, const char * pszUrl, const char * pszKey, payload payload)
   {

      strUrl = pszUrl;

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         iPos = strUrl.get_length();

      strUrl = strUrl.Left(iPos) + "?" + query_set(strUrl.Mid(iPos + 1), pszKey, payload);

   }


   void department::set_param(string & strUrlParam, const char * pszKey, const char * strParam)
   {

      string strUrl(strUrlParam);

      set_param(strUrlParam, strUrl, pszKey, strParam);

   }


   void department::set_param(string & strUrl, const char * pszUrl, const char * pszKey, const char * strParam)
   {

      const char * pszQuery = strchr(pszUrl, '?');

      string strKey = url_encode(pszKey);
      string strValue = url_encode(strParam);

      strsize iLenUrl = strlen(pszUrl);
      strsize iLenKey = strKey.length();

      string str;

      char * psz = str.get_string_buffer(iLenUrl + iLenKey + strValue.get_length() + 2);

      if(pszQuery == nullptr)
      {
         strcpy(psz, pszUrl);
         psz[iLenUrl] = '?';
         strcpy(&psz[iLenUrl + 1], strKey);
         psz[iLenUrl + 1 + iLenKey] = '=';
         strcpy(&psz[iLenUrl + 1 + iLenKey + 1], strValue);
         str.release_string_buffer(iLenUrl + iLenKey + strValue.get_length() + 2);
      }
      else
      {
         strsize iFinalLen = pszQuery - pszUrl;
//         i32 iPos = 0;
         ansi_count_copy(psz, pszUrl, iFinalLen);
         psz[iFinalLen] = '?';
         iFinalLen++;
         pszQuery++;
         bool bRemove = false;
         bool bAlreadyInsertedFirstParam = false;
         const char * pszQueryEnd;
         bool bInserted = false;
         while(true)
         {
            pszQueryEnd = strchr(pszQuery + 1, '&');
            if(ansi_count_compare(pszQuery, pszKey, iLenKey) == 0 && pszQuery[iLenKey] == '=')
            {
               if(!bRemove)
               {
                  if(bAlreadyInsertedFirstParam)
                  {
                     psz[iFinalLen] = '&';
                     iFinalLen++;
                  }
                  ansi_count_copy(&psz[iFinalLen], strKey, iLenKey);
                  iFinalLen += iLenKey;
                  psz[iFinalLen] = '=';
                  iFinalLen++;
                  ansi_count_copy(&psz[iFinalLen], strValue, strValue.get_length());
                  iFinalLen += strValue.get_length();
                  bRemove = true;
                  bAlreadyInsertedFirstParam = true;
                  bInserted = true;
               }
            }
            else
            {
               if(bAlreadyInsertedFirstParam)
               {
                  psz[iFinalLen] = '&';
                  iFinalLen++;
               }
               if(pszQueryEnd == nullptr)
               {
                  ansi_count_copy(&psz[iFinalLen], pszQuery, iLenUrl - (pszQuery - pszUrl));
                  iFinalLen += iLenUrl - (pszQuery - pszUrl);
                  bAlreadyInsertedFirstParam = true;
                  break;
               }
               else
               {
                  ansi_count_copy(&psz[iFinalLen], pszQuery, pszQueryEnd - pszQuery);
                  iFinalLen += pszQueryEnd - pszQuery;
                  bAlreadyInsertedFirstParam = true;
               }
            }
            pszQuery = pszQueryEnd;
            if(pszQuery == nullptr)
               break;
            pszQuery++;
         }
         if(!bInserted)
         {
            if(bAlreadyInsertedFirstParam)
            {
               psz[iFinalLen] = '&';
               iFinalLen++;
            }
            ansi_count_copy(&psz[iFinalLen], strKey, iLenKey);
            iFinalLen += iLenKey;
            psz[iFinalLen] = '=';
            iFinalLen++;
            ansi_count_copy(&psz[iFinalLen], strValue, strValue.get_length());
            iFinalLen += strValue.get_length();
            bRemove = true;
            bAlreadyInsertedFirstParam = true;
            bInserted = true;
         }

         str.release_string_buffer(iFinalLen);

      }

      strUrl = str;


   }

   payload & department::var_remove(payload & varUrl, const char * pszKey)
   {

      return varUrl = remove_key(varUrl, pszKey);

   }

   property & department::property_remove(property & propUrl, const char * pszKey)
   {

      propUrl = remove_key(propUrl, pszKey);

      return propUrl;

   }

   string department::string_remove(string & strUrl, const char * pszKey)
   {

      return strUrl = remove_key(strUrl, pszKey);

   }

   string department::remove_key(const char * pszUrl, const char * pszKey)
   {

      string strUrl(pszUrl);

      strsize iPos = strUrl.find("?");

      if(iPos < 0)
         return strUrl;

      return strUrl.Left(iPos) + ::str::has_char(query_remove(strUrl.Mid(iPos + 1), pszKey), "?");

   }

   payload department::get_var(const char * pszUrl, const char * pszKey)
   {

      string strUrl(pszUrl);

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return payload(::type_empty);
      else
         return query_get_var(strUrl.Mid(iPos + 1), pszKey);

   }

   string department::get_param(const char * pszUrl, const char * pszKey)
   {

      string strUrl(pszUrl);

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return payload(::type_empty);
      else
         return url_decode(query_get_param(strUrl.Mid(iPos + 1), pszKey));

   }

   bool department::get_param(string & strValue, const string & strUrl, const string & strKey)
   {

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return false;
      else
         return query_get_param(strValue, strUrl.Mid(iPos + 1), strKey);

   }

   bool department::has_param(const string & strUrl, const string & strKey)
   {

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return false;
      else
         return query_has_param(strUrl.Mid(iPos + 1), strKey);

   }

   bool department::param_has_char(const string & strUrl, const string & strKey)
   {

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return false;
      else
         return query_param_has_char(strUrl.Mid(iPos + 1), strKey);
   }

   bool department::has_param_replace(string & strUrl, const char * strKey, const char * strValue)
   {

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return false;
      else
      {

         string strQuery = strUrl.Mid(iPos + 1);

         if(!query_has_param_replace(strQuery, strKey, strValue))
            return false;

         strUrl = strUrl.Left(iPos + 1) + strQuery;

         return true;
      }
   }

   string department::query_set(const char * pszQuery, const char * pszKey, payload payload)
   {

      string strQuery(pszQuery);

      string strKey(url_encode(pszKey));

      string strKeyEqual = strKey + "=";

      string strAndKeyEqual = "&" + strKeyEqual;

      string strKey2(url_encode(pszKey));

      string strKeyEqual2 = strKey + "=";

      string strAndKeyEqual2 = "&" + strKeyEqual;

      string strValue = url_encode(payload.get_string());

      if(::str::begins(strQuery, strKeyEqual))
      {
         strsize iPos = strQuery.find("&");
         if(iPos < 0)
         {
            strQuery = strKeyEqual2 + strValue;
         }
         else
         {
            strQuery = strKeyEqual2 + strValue + __query_remove(strQuery.Mid(iPos), strAndKeyEqual);
         }
      }
      else if(::str::begins(strQuery, strKeyEqual2))
      {
         strsize iPos = strQuery.find("&");
         if(iPos < 0)
         {
            strQuery = strKeyEqual2 + strValue;
         }
         else
         {
            strQuery = strKeyEqual2 + strValue + __query_remove(strQuery.Mid(iPos), strAndKeyEqual);
         }
      }
      else
      {
         strsize iPos = strQuery.find(strAndKeyEqual);
         if(iPos < 0)
         {
            if(strQuery.has_char())
            {
               strQuery += strAndKeyEqual2 + strValue;
            }
            else
            {
               strQuery = strKeyEqual2 + strValue;
            }
         }
         else
         {
            iPos = strQuery.find(strAndKeyEqual2);
            if(iPos < 0)
            {
               if(strQuery.has_char())
               {
                  strQuery += strAndKeyEqual2 + strValue;
               }
               else
               {
                  strQuery = strKeyEqual2 + strValue;
               }
            }
            else
            {
               strQuery = strQuery.Left(iPos) + strAndKeyEqual2 + strValue + __query_remove(strQuery.Mid(iPos), strAndKeyEqual);
            }
         }
      }


      return strQuery;

   }

   string department::query_set_param(const char * pszQuery, const char * pszKey, const string & strParam)
   {

      string strQuery(pszQuery);

      string strKey(pszKey);

      string strKeyEqual = strKey + "=";

      string strAndKeyEqual = "&" + strKeyEqual;

      if(::str::begins(strQuery, strKeyEqual))
      {
         strsize iPos = strQuery.find("&");
         if(iPos < 0)
         {
            strQuery = strKey + strParam;
         }
         else
         {
            strQuery = strKey + strParam + __query_remove(strQuery.Mid(iPos), strAndKeyEqual);
         }
      }
      else
      {
         strsize iPos = strQuery.find(strAndKeyEqual);
         if(iPos < 0)
         {
            if(strQuery.has_char())
            {
               strQuery += strAndKeyEqual + strParam;
            }
            else
            {
               strQuery = strKeyEqual + strParam;
            }
         }
         else
         {
            strQuery = strKey + strParam + __query_remove(strQuery.Mid(iPos), strAndKeyEqual);
         }
      }


      return strQuery;

   }

   string department::query_remove(const char * pszQuery, const char * pszKey)
   {

      ::property_set set;

      set.parse_url_query(pszQuery);

      set.remove_by_name(pszKey);

      string str;

      set.get_http_post(str);

      return str;

   }

   string department::__query_remove(const char * pszQuery, const char * pszAndKeyEqual)
   {

      string strQuery(pszQuery);

      while(true)
      {
         strsize iFind = strQuery.find(pszAndKeyEqual);
         if(iFind < 0)
            break;
         strsize iNextParam = strQuery.find("&", iFind + 1);
         if(iNextParam < 0)
         {
            strQuery = strQuery.Left(iFind);
         }
         else
         {
            strQuery = strQuery.Left(iFind) + strQuery.Mid(iNextParam);
         }
      }

      return strQuery;

   }

   string department::query_remove(const char * pszQuery, string_array & straKey)
   {

      ::property_set set;

      set.parse_url_query(pszQuery);

      set.remove_by_name(straKey);

      string str;

      set.get_http_post(str);

      return str;

   }


   payload department::query_get_var(const char * pszQuery, const char * pszKey)
   {

      string strQuery(pszQuery);

      string strKey(pszKey);

      string strKeyEqual = strKey + "=";

      string strAndKeyEqual = "&" + strKeyEqual;

      payload varValue;

      strsize iPos = 0;

      if(::str::begins(strQuery, strKeyEqual))
      {
         iPos = strQuery.find('&');
         if(iPos < 0)
         {
            varValue = strQuery.Mid(strKeyEqual.get_length());
            return varValue;
         }
         else
         {
            varValue = strQuery.Mid(strKeyEqual.get_length(), iPos - strKeyEqual.get_length());
         }
      }

      while(true)
      {
         iPos = strQuery.find(strAndKeyEqual, iPos);
         if(iPos < 0)
            break;
         strsize iEnd = strQuery.find('&', iPos + 1);
         if(iEnd < 0)
         {
            if(varValue.is_new())
            {
               varValue = strQuery.Mid(iPos + strKeyEqual.get_length());
            }
            else
            {
               varValue.vara().add(strQuery.Mid(iPos + strKeyEqual.get_length()));
            }
            return varValue;
         }
         else
         {
            if(varValue.is_new())
            {
               varValue = strQuery.Mid(iPos + strKeyEqual.get_length(), iEnd - (iPos + strKeyEqual.get_length()));
            }
            else
            {
               varValue.vara().add(strQuery.Mid(iPos + strKeyEqual.get_length(), iEnd - (iPos + strKeyEqual.get_length())));
            }
         }
         iPos++;
      }


      return varValue;

   }

   string department::query_get_param(const string & strQuery, const string & strKey)
   {

      string strValue;

      if(!query_get_param(strValue, strQuery, strKey))
         return "";

      return strValue;

   }

   bool department::query_get_param(string & strValue, const string & strQuery, const string & strKey)
   {

      strsize iCmp = strQuery.length() - strKey.length();
      if(iCmp < 0)
         return false;

      if(ansi_count_compare(strQuery, strKey, strKey.length()) == 0)
      {
         if(iCmp == 0)
         {
            strValue = "";
            return true;
         }
         else if(strQuery[strKey.length()] == '=')
         {
            strsize iFind2 = strQuery.find('&', strKey.length() + 1);
            if(iFind2 > 0)
            {
               strValue = strQuery.Mid(strKey.length() + 1, iFind2 - (strKey.length() + 1));
            }
            else
            {
               strValue = strQuery.Mid(strKey.length() + 1);
            }
            return true;
         }

      }

      strsize iStart = 1;

      strsize iFind;

      while((iFind = strQuery.find(strKey, iStart)) >= 0)
      {
         if(strQuery[iFind - 1] == '&')
         {
            if(strQuery.length() == (iFind + strKey.length()))
            {
               strValue = "";
               return true;
            }
            else if(strQuery[iFind + strKey.length()] == '=')
            {
               strsize iFind2 = strQuery.find('&', iFind + strKey.length() + 1);
               if(iFind2 > 0)
               {
                  strValue = strQuery.Mid(iFind + strKey.length() + 1, iFind2 - (iFind + strKey.length() + 1));
               }
               else
               {
                  strValue = strQuery.Mid(iFind + strKey.length() + 1);
               }
               return true;
            }
         }
         iStart = iFind + strKey.length() + 1;
      }

      return false;

   }

   bool department::query_has_param(const string & strQuery, const string & strKey)
   {

      strsize iCmp = strQuery.length() - strKey.length();
      if(iCmp < 0)
         return false;

      if(ansi_count_compare(strQuery, strKey, strKey.length()) == 0)
      {
         if(iCmp == 0)
         {
            return true;
         }
         else if(strQuery[strKey.length()] == '=')
         {
            return true;
         }

      }

      strsize iStart = strKey.length();

      strsize iFind;

      while((iFind = strQuery.find(strKey, iStart)) >= 0)
      {
         if(strQuery[iFind - 1] == '&')
         {
            if(strQuery.length() == (iFind + strKey.length()))
            {
               return true;
            }
            else if(strQuery[iFind + strKey.length()] == '=')
            {
               return true;
            }
         }
         iStart = iFind + strKey.length() + 1;
      }

      return false;
   }

   bool department::query_param_has_char(const string & strQuery, const string & strKey)
   {

      strsize iCmp = strQuery.length() - strKey.length();
      if(iCmp < 0)
         return false;

      if(ansi_count_compare(strQuery, strKey, strKey.length()) == 0)
      {
         if(iCmp == 0)
         {
            return false;
         }
         else if(strQuery[strKey.length()] == '=')
         {
            strsize iFind2 = strQuery.find('&', strKey.length() + 1);
            if(iFind2 > 0)
            {
               return (iFind2 - (strKey.length() + 1)) > 0;
            }
            else
            {
               return (strQuery.length() - (strKey.length() + 1)) > 0;
            }

         }

      }

      strsize iStart = strKey.length();

      strsize iFind;

      while((iFind = strQuery.find(strKey, iStart)) >= 0)
      {
         if(strQuery[iFind - 1] == '&')
         {
            if(strQuery.length() == (iFind + strKey.length()))
            {
               return false;
            }
            else if(strQuery[iFind + strKey.length()] == '=')
            {
               strsize iFind2 = strQuery.find('&', iFind + strKey.length() + 1);
               if(iFind2 > 0)
               {
                  return (iFind2 - (iFind + strKey.length() + 1)) > 0;
               }
               else
               {
                  return (strQuery.length() - (iFind + strKey.length() + 1)) > 0;
               }
            }
         }
         iStart = iFind + strKey.length() + 1;
      }

      return false;

   }

   bool department::query_has_param_replace(string & strQuery, const string & strKey, const string & strValue)
   {

      strsize iCmp = strQuery.length() - strKey.length();
      if(iCmp < 0)
         return false;

      if(ansi_count_compare(strQuery, strKey, strKey.length()) == 0)
      {
         if(iCmp == 0)
         {
            strQuery += "=" + strValue;
            return true;
         }
         else if(strQuery[strKey.length()] == '=')
         {
            strsize iFind2 = strQuery.find('&', strKey.length() + 1);
            if(iFind2 > 0)
            {
               strQuery = strQuery.Left(strKey.length() + 1) + strValue + strQuery.Mid(iFind2);
            }
            else
            {
               strQuery = strQuery.Left(strKey.length() + 1) + strValue;
            }
            return true;
         }

      }

      strsize iStart = strKey.length();

      strsize iFind;

      while((iFind = strQuery.find(strKey, iStart)) >= 0)
      {
         if(strQuery[iFind - 1] == '&')
         {
            if(strQuery.length() == (iFind + strKey.length()))
            {
               strQuery += "=" + strValue;
               return true;
            }
            else if(strQuery[iFind + strKey.length()] == '=')
            {
               strsize iFind2 = strQuery.find('&', iFind + strKey.length() + 1);
               if(iFind2 > 0)
               {
                  strQuery = strQuery.Left(iFind + strKey.length() + 1) + strValue + strQuery.Mid(iFind2);
               }
               else
               {
                  strQuery = strQuery.Left(iFind + strKey.length() + 1) + strValue;
               }
               return true;
            }
         }
         iStart = iFind + strKey.length() + 1;
      }

      return false;

   }

   bool department::locale_is_eu(id idLocale)
   {


      if(
      idLocale == __id(eu)
      || idLocale == __id(se)
      || idLocale == __id(at)
      || idLocale == __id(dk)
      || idLocale == __id(en_uk)
      || idLocale == __id(uk)
      || idLocale == __id(fi)
      || idLocale == __id(gr)
      || idLocale == __id(de)
      || idLocale == __id(nl)
      || idLocale == __id(be)
      || idLocale == __id(fr)
      || idLocale == __id(it)
      || idLocale == __id(pt)
      || idLocale == __id(cz)
      || idLocale == __id(lu)
      || idLocale == __id(ie)
      || idLocale == __id(no)
      || idLocale == __id(cy)
      || idLocale == __id(su)
      || idLocale == __id(lv)
      || idLocale == __id(li)
      || idLocale == __id(hu)
      || idLocale == __id(es)
      || idLocale == __id(sk)
      || idLocale == __id(cz)
      || idLocale == __id(si)
      || idLocale == __id(ro)
      || idLocale == __id(kz)
      || idLocale == __id(ru)
      || idLocale == __id(pl)
      || idLocale == __id(tr)
      || idLocale == __id(ee))
      {
         return true;
      }

      return false;

   }

   bool department::locale_is_asia(id idLocale)
   {

      if(idLocale == __id(asia)
            || idLocale == __id(cn)
            || idLocale == __id(tw)
            || idLocale == __id(vn)
            || idLocale == __id(in)
            || idLocale == __id(kg)
            || idLocale == __id(kz)
            || idLocale == __id(kr)
            || idLocale == __id(my)
            || idLocale == __id(ph)
            || idLocale == __id(sg)
            || idLocale == __id(su)
            || idLocale == __id(ru)
            || idLocale == __id(zh)
            || idLocale == __id(hk)
            || idLocale == __id(ja)
            || idLocale == __id(jp)
            || idLocale == __id(tr))
      {
         return true;
      }

      return false;

   }

   bool department::locale_is_middle_east(id idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == __id(sy)
            || idLocale == __id(tr)
            || idLocale == __id(il)
            || idLocale == __id(ps))
      {
         return true;
      }

      return false;

   }



   bool department::locale_is_south_america(id idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == __id(ar)
            || idLocale == __id(bo)
            || idLocale == __id(br)
            || idLocale == __id(cl)
            || idLocale == __id(co)
            || idLocale == __id(ec)
            || idLocale == __id(gs)
            || idLocale == __id(pe)
            || idLocale == __id(py)
            || idLocale == __id(uy)
            || idLocale == __id(ve)
            || idLocale == __id(amdesur))
      {
         return true;
      }

      return false;

   }

   bool department::locale_is_oceania(id idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == __id(au)
            || idLocale == __id(oceania)
            || idLocale == __id(nz)
            || idLocale == __id(tl))
      {
         return true;
      }

      return false;

   }


   bool department::locale_is_africa(id idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == __id(ug)
            || idLocale == __id(sc)
            || idLocale == __id(cm)
            || idLocale == __id(za)
            || idLocale == __id(africa) )
      {
         return true;
      }

      return false;

   }

   bool department::locale_is_latin_america(id idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == __id(mx))
      {
         return true;
      }

      return locale_is_caribe(idLocale) || locale_is_central_america(idLocale) || locale_is_south_america(idLocale);

   }

   bool department::locale_is_north_america(id idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == __id(mx)
            || idLocale == __id(us)
            || idLocale == __id(ca))
      {
         return true;
      }

      return false;

   }

   bool department::locale_is_caribe(id idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == __id(caribe))
         return true;

      if(idLocale == __id(ht)
            || idLocale == __id(cu)
            || idLocale == __id(tc))
      {
         return true;
      }

      return false;

   }


   bool department::locale_is_central_america(id idLocale)
   {

      string strLocale(idLocale);

      if(strLocale == "central_america")
         return true;

      if(idLocale == __id(centralam))
         return true;

      if(idLocale == __id(bz))
      {
         return true;
      }

      return false;

   }

   bool department::locale_is_america(id idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == __id(america))
         return true;

      return
      locale_is_central_america(idLocale)
      || locale_is_caribe(idLocale)
      || locale_is_south_america(idLocale)
      || locale_is_north_america(idLocale);

   }


   bool department::server_ends(string strUrl, string strRoot)
   {

      string strServer = get_server(strUrl);

      if(strServer.compare_ci(strRoot) == 0)
      {

         return true;

      }

      if(::str::ends_ci(strServer, "." + strRoot))
      {

         return true;

      }

      return false;

   }



   string department::set_script(const char * pszUrl, const char * pszScript)
   {

      return get_protocol(pszUrl) + "://" + get_root(pszUrl) + string(pszScript) + ::str::has_char(get_query(pszUrl), "?");

   }

   string department::override_if_empty(const char * pszDst, const char * pszSrc, bool bOverrideQuery)
   {

      string strProtocol = get_protocol(pszDst);
      string strProtocolOver = get_protocol(pszSrc);
      string strRoot = get_root(pszDst);
      string strRootOver = get_root(pszSrc);
      string strScript = get_script(pszDst);
      string strScriptOver = get_script(pszSrc);
      string strQuery = get_query(pszDst);
      string strQueryOver = get_query(pszSrc);

      if(strProtocol.is_empty())
         strProtocol = strProtocolOver;

      if(strRoot.is_empty())
         strRoot = strRootOver;

      if(strScript.is_empty())
         strScript = strScriptOver;

      if(bOverrideQuery && strQuery.is_empty())
         strQuery = strQueryOver;

      if(!::str::begins(strScript,astr.Slash))
         strScript = "/" + strScript;

      return strProtocol + "://" + strRoot + strScript + ::str::has_char(strQuery, "?");
   }


   string department::override_if_set_at_source(const char * pszDst, const char * pszSrc)
   {

      string strProtocol = get_protocol(pszDst);
      string strProtocolOver = get_protocol(pszSrc);
      string strRoot = get_root(pszDst);
      string strRootOver = get_root(pszSrc);
      string strScript = get_script(pszDst);
      string strScriptOver = get_script(pszSrc);
      string strQuery = get_query(pszDst);
      string strQueryOver = get_query(pszSrc);

      if(strProtocolOver.has_char())
         strProtocol = strProtocolOver;

      if(strRootOver.has_char())
         strRoot = strRootOver;

      if(strScriptOver.has_char())
         strScript = strScriptOver;

      if(strQueryOver.has_char())
         strQuery = strQueryOver;

      if(!::str::begins(strScript, astr.Slash))
         strScript = "/" + strScript;

      return strProtocol + "://" + strRoot + strScript + ::str::has_char(strQuery, "?");
   }


   string department::to_punycode(const char * psz)
   {

#ifdef WINDOWS

      wstring wstr(psz);

      int iSize = IdnToAscii(IDN_RAW_PUNYCODE, wstr, (int) wstr.get_length(), nullptr, 0);

      WCHAR * pwsz = new WCHAR[iSize + 1];

      IdnToAscii(IDN_RAW_PUNYCODE, wstr, (int) wstr.get_length(), pwsz, iSize + 1);

      string str = pwsz;

      delete pwsz;

      return str;

#else

      char * point = nullptr;

      Idna_rc rc = (Idna_rc) idna_to_ascii_8z(psz, &point, IDNA_ALLOW_UNASSIGNED);

      if (rc != IDNA_SUCCESS)
      {

         __throw(::exception::exception(idna_strerror(rc)));

      }

      string str(point);

      free(point);

      return str;

#endif

   }

   string department::from_punycode(const char * psz)
   {

#ifdef WINDOWS

      wstring wstr(psz);

      int iSize = IdnToUnicode(IDN_RAW_PUNYCODE, wstr, (int)wstr.get_length(), nullptr, 0);

      WCHAR * pwsz = new WCHAR[iSize + 1];

      IdnToUnicode(IDN_RAW_PUNYCODE, wstr, (int) wstr.get_length(), pwsz, iSize + 1);

      string str = pwsz;

      delete pwsz;

      return str;

#else


      if(psz == nullptr || *psz == '\0')
         return "";

      {

         string str(psz);

         str.trim();

         if(str.is_empty())
            return "";

      }

      char * point = nullptr;

      Idna_rc rc = (Idna_rc)idna_to_unicode_8z8z(psz, &point, IDNA_ALLOW_UNASSIGNED);

      if (rc != IDNA_SUCCESS)
      {

         __throw(::exception::exception(idna_strerror(rc)));

      }

      string str(point);

      free(point);

      return str;

#endif

   }


   inline bool ansi_char_is_alphanumeric(i32 i)
   {

      return (i >= '0' && i <= '9') || (i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z');

   }


   bool department::is_valid_public_domain(const string& strDomain)
   {

      cslock lock(&m_csPublicDomainExtension);

      if (m_straPublicDomainExtension.isEmpty())
      {

         ::file::path pathPublicDomainExtensionList = "https://server.ca2.cc/public_internet_domain_extension_list.txt";

         Context.file().load_lines(m_straPublicDomainExtension, pathPublicDomainExtensionList);

         m_straPublicDomainExtension.trim();

         m_straPublicDomainExtension.remove_empty();

         TRACE("m_straPublicDomainExtension");

         for (auto& str : m_straPublicDomainExtension)
         {

            TRACE("%s", str.c_str());

         }

      }

      bool bPublicDomainExtensionListSuffixesDomain = m_straPublicDomainExtension.suffix_find_first_ci(strDomain) >= 0;

      return bPublicDomainExtensionListSuffixesDomain;

   }


   string department::os_fs(string strUrl, bool bPath)
   {

      strUrl.replace("<","_lt_");
      strUrl.replace(">","_gt_");
      strUrl.replace(":","_cl_");
      strUrl.replace(".","_dot_");

      if(bPath)
      {

         strUrl.replace("\\","/");

      }
      else
      {

         strUrl.replace("/","_sl_");
         strUrl.replace("\\","_bsl_");

      }

      strUrl.replace(" ","_");

      return strUrl;

   }


   string department::os_fspath(string strUrl)
   {

      return os_fs(strUrl, true);

   }


   string department::os_fsname(string strUrl)
   {

      return os_fs(strUrl, false);

   }


} // namespace url



