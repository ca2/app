// From url_department.h by camilo on 2022-11-19 04:24 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "url.h"
//#include "as_string.h"
#include "acme/constant/id.h"
#include "acme/constant/idpool.h"
//#include "acme/primitive/primitive/payload.h"
#include "acme/primitive/string/str.h"
#include "acme/platform/system.h"


::string idn_to_punycode(const ::string & str);
::string idn_from_punycode(const ::string & str);


namespace url
{


   url::url()
   {


   }


   url::~url()
   {


   }


   string url::get_protocol(const ::string & strParam)
   {

      string str(strParam);

      auto pPos = str.find(":");

      if(::is_null(pPos))
      {

         return "";

      }

      return (*this)(0, pPos);

   }


   string url::get_root(const ::string & strParam)
   {

      string str(strParam);

      auto pPos = str.find(":");
      if (::is_null(pPos))
         return strParam;
      pPos++;
      while (pPos < str.end() && *pPos == '/')
      {
         pPos++;
      }
      auto pStart = pPos;
      auto pEnd = str(pStart).find("/");
      auto pArgumentsStart = str(pStart).find("?");

      if (::is_null(pEnd) || (::is_set(pArgumentsStart) && pEnd > pArgumentsStart))
      {

         return {};

      }

      return { pStart, pEnd };

   }


   string url::get_server(const ::string & strParam)
   {

      string strRoot = get_root(strParam);

      auto pPos = strRoot.find(":");

      if (::is_null(pPos))
      {

         return strRoot;

      }

      return strRoot.left(pPos);

   }


   i32 url::get_port(const ::string & strParam, i32 iDefault)
   {

      string strRoot = get_root(strParam);

      auto pPos = strRoot.find(":");

      if(not_found(pPos))
      {

         if(iDefault == -1)
         {

            string strProtocol = get_protocol(strParam);

            if (strProtocol == "http")
            {

               return 80;

            }
            else if (strProtocol == "https")
            {

               return 443;

            }
            else if (strProtocol == "ftp")
            {

               return 21;

            }

         }

         return iDefault;

      }

      return atoi(strRoot.substr(pPos + 1));

   }


   string url::get_object(const ::string & strParam)
   {

      string str(strParam);

      auto pPos1 = str.find("://");

      auto pPos2 = str.find(":/");

      string::const_iterator pPos;

      if(not_found(pPos1))
      {

         if (::not_found(pPos2))
         {

            return strParam;

         }
         else
         {

            pPos = pPos2 + 2;

         }

      }
      else if(not_found(pPos2))
      {

         pPos = pPos1 + 3;

      }
      else if(pPos1 <= pPos2)
      {

         pPos = pPos1 + 3;

      }
      else
      {

         pPos = pPos2 + 2;         

      }

      auto pStart = str(pPos).find("/");

      if (not_found(pStart))
      {

         return "/";

      }
      else
      {

         return str.substr(pStart);

      }

   }


   string url::object_get_script(const ::string & strParam) // page
   {

      string str(strParam);

      auto pFind = str.find('?');

      if (::is_null(pFind))
      {

         return ::url::decode(str);

      }
      else
      {

         return ::url::decode(str(0, pFind));

      }

   }


   string url::object_get_query(const ::string & strParam) // id=1
   {

      string str(strParam);

      auto pFind = str.find('?');

      if (::is_null(pFind))
      {

         return "";

      }
      else
      {

         return str(pFind + 1);

      }

   }


   string url::object_set(const ::string & strObject, const ::string & strKeyParam, ::payload payload)
   {

      string strQuery = object_get_query(strObject);

      return object_get_script(strObject) + ::str().has_char(query_set(strQuery, strKeyParam, payload), "?");

   }


   string url::get_script(const ::string & strParam) // page
   {

      return object_get_script(get_object(strParam));

   }


   string url::get_query(const ::string & strParam) // id=1
   {

      return object_get_query(get_object(strParam));

   }


   string url::object(const ::string & strScriptParam, const ::string & strQueryParam)
   {

      string strScript(strScriptParam);

      string strQuery(strQueryParam);

      if (strQuery.has_char())
      {

         return strScript + "?" + strQuery;

      }
      else
      {

         return strScript;

      }

   }


   string url::path(const ::string & str1Param, const ::string & str2Param)
   {

      if (str2Param.is_empty())
      {

         return str1Param;

      }

      string str1(str1Param);

      string str2(str2Param);

      if (str1.right(1) == "/")
      {

         str1 = str1.left(str1.length() - 1);

      }

      if (str2.left(1) == "/")
      {

         str2 = str2.right(str2.length() - 1);

      }

      return str1 + "/" + str2;

   }


   string url::path(const ::string & str1, const ::string & str2, const ::string & str3)
   {

      return path(path(str1, str2), str3);

   }


   string url::name(const ::string & strParam)
   {

      string str(strParam);

      auto pQueryStart = str.find('?');

      if (not_found(pQueryStart))
      {

         pQueryStart = str.end();

      }

      str = str.left(pQueryStart);

      auto pLastSlash = str.rear_find('/');

      if (not_found(pLastSlash))
      {
         
         return "";

      }

      return str.left(pLastSlash);

   }


   //string url::url::encode(const ::string & strParam)
   //{

   //   return ::url::encode(strParam);

   //}


   //string url::url::decode(const ::string & strParam)
   //{

   //   return ::url::decode(strParam);

   //}


   //string url::url::decode(const ::string & strUrl, strsize iLen)
   //{

   //   return ::url::decode(strUrl,iLen);

   //}


   string url::query_append(const ::string & strUrlParam, const ::string & strQuery)
   {

      string strUrl(strUrlParam);

      auto pStart = strUrl.find("://");

      if(pStart > strUrl.begin())
      {

         pStart = strUrl(pStart + 4).find("/");

         if(not_found(pStart))
         {

//xxx            FORMATTED_TRACE("invalid url %s", pszUrl);

            pStart = strUrl.begin();

         }

      }
      else
      {

         pStart = strUrl.begin();

      }

      if(strUrl(pStart).find("?") > strUrl.begin())
      {

         return strUrl + "&" + strQuery;

      }
      else
      {

         return strUrl + "?" + strQuery;

      }

   }


   bool url::is_url(const ::string & strCandidateParam)
   {

      string strCandidate(strCandidateParam);

      strsize iLen = strCandidate.length();

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


   ::payload & url::var_set(::payload & varUrl, const ::string & strKeyParam, ::payload payload)
   {

      return varUrl = set_key(varUrl, strKeyParam, payload);

   }


   property & url::property_set(property & propUrl, const ::string & strKeyParam, ::payload payload)
   {

      propUrl = set_key(propUrl, strKeyParam, payload);

      return propUrl;

   }


   string url::string_set(string & strUrl, const ::string & strKeyParam, ::payload payload)
   {

      return strUrl = set_key(strUrl, strKeyParam, payload);

   }


   string url::string_set_if_not_empty(string& strUrl, const ::string & strKey, ::payload payload)
   {

      if (payload.is_empty())
      {

         return strUrl;

      }

      return string_set(strUrl, strKey, payload);

   }


   string url::set_key(const ::string & strUrlParam, const ::string & strKeyParam, ::payload payload)
   {

      string strUrl(strUrlParam);

      auto pPos = strUrl.find("?");

      if (not_found(pPos))
      {

         pPos = strUrl.end();

      }

      return strUrl.left(pPos)
             + "?" +
             query_set(strUrl.substr(pPos + 1), strKeyParam, payload);

   }


   void url::set_key(string & strUrl, const ::string & strUrlParam, const ::string & strKeyParam, ::payload payload)
   {

      strUrl = strUrlParam;

      auto pPos = strUrl.find('?');

      if (not_found(pPos))
      {

         pPos = strUrl.end();

      }

      strUrl = strUrl.left(pPos) + "?" + query_set(strUrl.substr(pPos + 1), strKeyParam, payload);

   }


   void url::set_param(string & strUrlParam, const ::string & strKeyParam, const ::string & strParam)
   {

      string strUrl(strUrlParam);

      set_param(strUrlParam, strUrl, strKeyParam, strParam);

   }


   void url::set_param(string & strUrl, const ::string & strUrlParam, const ::string & strKeyParam, const ::string & strParam)
   {

      const ::ansi_character * pszQuery = strchr(strUrlParam, '?');

      string strKey = ::url::encode(strKeyParam);
      string strValue = ::url::encode(strParam);

      strsize iLenUrl = strlen(strUrlParam);
      strsize iLenKey = strKey.length();

      string str;

      char * psz = str.get_string_buffer(iLenUrl + iLenKey + strValue.length() + 2);

      if(pszQuery == nullptr)
      {
         strcpy(psz, strUrlParam);
         psz[iLenUrl] = '?';
         strcpy(&psz[iLenUrl + 1], strKey);
         psz[iLenUrl + 1 + iLenKey] = '=';
         strcpy(&psz[iLenUrl + 1 + iLenKey + 1], strValue);
         str.release_string_buffer(iLenUrl + iLenKey + strValue.length() + 2);
      }
      else
      {
         strsize iFinalLen = pszQuery - strUrlParam;
//         i32 pPos = 0;
         ansi_count_copy(psz, strUrlParam, iFinalLen);
         psz[iFinalLen] = '?';
         iFinalLen++;
         pszQuery++;
         bool bRemove = false;
         bool bAlreadyInsertedFirstParam = false;
         const ::ansi_character * pszQueryEnd;
         bool bInserted = false;
         while(true)
         {
            pszQueryEnd = strchr(pszQuery + 1, '&');
            if(ansi_count_compare(pszQuery, strKeyParam, iLenKey) == 0 && pszQuery[iLenKey] == '=')
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
                  ansi_count_copy(&psz[iFinalLen], strValue, strValue.length());
                  iFinalLen += strValue.length();
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
                  ansi_count_copy(&psz[iFinalLen], pszQuery, iLenUrl - (pszQuery - strUrlParam));
                  iFinalLen += iLenUrl - (pszQuery - strUrlParam);
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
            ansi_count_copy(&psz[iFinalLen], strValue, strValue.length());
            iFinalLen += strValue.length();
            bRemove = true;
            bAlreadyInsertedFirstParam = true;
            bInserted = true;
         }

         str.release_string_buffer(iFinalLen);

      }

      strUrl = str;


   }

   ::payload & url::var_erase(::payload & varUrl, const ::string & strKeyParam)
   {

      return varUrl = erase_key(varUrl, strKeyParam);

   }

   property & url::property_erase(property & propUrl, const ::string & strKeyParam)
   {

      propUrl = erase_key(propUrl, strKeyParam);

      return propUrl;

   }

   string url::string_erase(string & strUrl, const ::string & strKeyParam)
   {

      return strUrl = erase_key(strUrl, strKeyParam);

   }

   string url::erase_key(const ::string & strUrlParam, const ::string & strKeyParam)
   {

      string strUrl(strUrlParam);

      auto pPos = strUrl.find("?");

      if(not_found(pPos))
         return strUrl;

      return strUrl.left(pPos) + ::str().has_char(query_erase(strUrl.substr(pPos + 1), strKeyParam), "?");

   }

   ::payload url::get_var(const ::string & strUrlParam, const ::string & strKeyParam)
   {

      string strUrl(strUrlParam);

      auto pPos = strUrl.find('?');

      if(not_found(pPos))
         return payload(::e_type_empty);
      else
         return query_get_var(strUrl.substr(pPos + 1), strKeyParam);

   }

   string url::get_param(const ::string & strUrlParam, const ::string & strKeyParam)
   {

      string strUrl(strUrlParam);

      auto pPos = strUrl.find('?');

      if(not_found(pPos))
         return payload(::e_type_empty);
      else
         return ::url::decode(query_get_param(strUrl.substr(pPos + 1), strKeyParam));

   }

   bool url::get_param(string & strValue, const ::string & strUrl, const ::string & strKey)
   {

      auto pPos = strUrl.find('?');

      if(not_found(pPos))
         return false;
      else
         return query_get_param(strValue, strUrl.substr(pPos + 1), strKey);

   }

   bool url::has_param(const ::string & strUrl, const ::string & strKey)
   {

      auto pPos = strUrl.find('?');

      if(not_found(pPos))
         return false;
      else
         return query_has_param(strUrl.substr(pPos + 1), strKey);

   }

   bool url::param_has_char(const ::string & strUrl, const ::string & strKey)
   {

      auto pPos = strUrl.find('?');

      if(not_found(pPos))
         return false;
      else
         return query_param_has_char(strUrl.substr(pPos + 1), strKey);
   }


   bool url::has_param_replace(string & strUrl, const ::string & strKeyParam, const ::string & strValueParam)
   {

      auto pPos = strUrl.find('?');

      if(not_found(pPos))
         return false;
      else
      {

         string strQuery = strUrl.substr(pPos + 1);

         if(!query_has_param_replace(strQuery, strKeyParam, strValueParam))
            return false;

         strUrl = strUrl.left(pPos + 1) + strQuery;

         return true;

      }

   }


   string url::query_set(const ::string & strQueryParam, const ::string & strKeyParam, ::payload payload)
   {

      string strQuery(strQueryParam);

      string strKey(::url::encode(strKeyParam));

      string strKeyEqual = strKey + "=";

      string strAndKeyEqual = "&" + strKeyEqual;

      string strKey2(::url::encode(strKeyParam));

      string strKeyEqual2 = strKey + "=";

      string strAndKeyEqual2 = "&" + strKeyEqual;

      string strValue = ::url::encode(payload);

      if(string_begins(strQuery, strKeyEqual))
      {
         auto pPos = strQuery.find("&");
         if(not_found(pPos))
         {
            strQuery = strKeyEqual2 + strValue;
         }
         else
         {
            strQuery = strKeyEqual2 + strValue + __query_erase(strQuery.substr(pPos), strAndKeyEqual);
         }
      }
      else if(string_begins(strQuery, strKeyEqual2))
      {
         auto pPos = strQuery.find("&");
         if(not_found(pPos))
         {
            strQuery = strKeyEqual2 + strValue;
         }
         else
         {
            strQuery = strKeyEqual2 + strValue + __query_erase(strQuery.substr(pPos), strAndKeyEqual);
         }
      }
      else
      {
         auto pPos = strQuery.find(strAndKeyEqual);
         if(not_found(pPos))
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
            pPos = strQuery.find(strAndKeyEqual2);
            if(not_found(pPos))
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
               strQuery = strQuery.left(pPos) + strAndKeyEqual2 + strValue + __query_erase(strQuery.substr(pPos), strAndKeyEqual);
            }
         }
      }


      return strQuery;

   }


   string url::query_set_param(const ::string & strQueryParam, const ::string & strKeyParam, const ::string & strParam)
   {

      string strQuery(strQueryParam);

      string strKey(strKeyParam);

      string strKeyEqual = strKey + "=";

      string strAndKeyEqual = "&" + strKeyEqual;

      if(string_begins(strQuery, strKeyEqual))
      {
         auto pPos = strQuery.find("&");
         if(not_found(pPos))
         {
            strQuery = strKey + strParam;
         }
         else
         {
            strQuery = strKey + strParam + __query_erase(strQuery.substr(pPos), strAndKeyEqual);
         }
      }
      else
      {
         auto pPos = strQuery.find(strAndKeyEqual);
         if(not_found(pPos))
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
            strQuery = strKey + strParam + __query_erase(strQuery.substr(pPos), strAndKeyEqual);
         }
      }


      return strQuery;

   }


   string url::query_erase(const ::string & strQueryParam, const ::string & strKeyParam)
   {

      ::property_set set;

      set.parse_network_arguments(strQueryParam);

      set.erase_by_name(strKeyParam);

      string str;

      set.get_network_arguments(str);

      return str;

   }


   string url::__query_erase(const ::string & strQueryParam, const ::string & strAndKeyEqual)
   {

      string strQuery(strQueryParam);

      while(true)
      {
         
         auto pFind = strQuery.find(strAndKeyEqual);
         
         if(::is_null(pFind))
         {
            
            break;
            
         }
         
         auto pNextParam = strQuery(pFind+1).find("&");
         
         if(not_found(pNextParam))
         {
            
            strQuery = strQuery(0, pFind);
            
         }
         else
         {
            
            strQuery = strQuery(0, pFind) + strQuery.substr(pNextParam);
            
         }
         
      }

      return strQuery;

   }


   string url::query_erase(const ::string & strQueryParam, string_array & straKey)
   {

      ::property_set set;

      set.parse_network_arguments(strQueryParam);

      set.erase_by_name(straKey);

      string str;

      set.get_network_arguments(str);

      return str;

   }


   ::payload url::query_get_var(const ::string & strQueryParam, const ::string & strKeyParam)
   {

      string strQuery(strQueryParam);

      string strKey(strKeyParam);

      string strKeyEqual = strKey + "=";

      string strAndKeyEqual = "&" + strKeyEqual;

      ::payload payload;

      string::const_iterator pPos = strQuery.begin();

      if(string_begins(strQuery, strKeyEqual))
      {
         
         pPos = strQuery.find('&');
         
         if(not_found(pPos))
         {
            
            payload = strQuery.substr(strKeyEqual.length());
            
            return payload;
            
         }
         else
         {
            
            payload = strQuery.substr(strKeyEqual.length(), pPos - strKeyEqual.length());
            
         }
         
      }

      while(true)
      {
         
         pPos = strQuery(pPos).find(strAndKeyEqual);
         
         if(not_found(pPos))
         {
            
            break;
            
         }
         
         auto pEnd = strQuery(pPos + 1).find('&');
         
         if(not_found(pEnd))
         {
            
            if(payload.is_new())
            {
               
               payload = strQuery.substr(pPos + strKeyEqual.length());
               
            }
            else
            {
               
               payload.payloada().add(strQuery.substr(pPos + strKeyEqual.length()));
               
            }
            
            return payload;
            
         }
         else
         {
            
            if(payload.is_new())
            {
               
               payload = strQuery.substr(pPos + strKeyEqual.length(), pEnd - (pPos + strKeyEqual.length()));
               
            }
            else
            {
               
               payload.payloada().add(strQuery.substr(pPos + strKeyEqual.length(), pEnd - (pPos + strKeyEqual.length())));
               
            }
            
         }
         
         pPos++;
         
      }

      return payload;

   }


   string url::query_get_param(const ::string & strQuery, const ::string & strKey)
   {

      string strValue;

      if(!query_get_param(strValue, strQuery, strKey))
      {
         
         return "";
         
      }

      return strValue;

   }


   bool url::query_get_param(string & strValue, const ::string & strQuery, const ::string & strKey)
   {

      strsize iCmp = strQuery.length() - strKey.length();
      
      if(iCmp < 0)
      {
         
         return false;
         
      }

      if(ansi_count_compare(strQuery, strKey, strKey.length()) == 0)
      {
         
         if(iCmp == 0)
         {
            
            strValue = "";
            
            return true;
            
         }
         else if(strQuery[strKey.length()] == '=')
         {
            
            auto pFind2 = strQuery(strKey.length() + 1).find('&');
            
            if(pFind2 > strQuery.begin())
            {
               
               strValue = strQuery.substr(strKey.length() + 1, pFind2 - (strKey.length() + 1));
               
            }
            else
            {
               
               strValue = strQuery.substr(strKey.length() + 1);
               
            }
            
            return true;
            
         }

      }

      ::string::const_iterator pStart = strQuery.begin() + 1;

      ::string::const_iterator pFind;

      while(found(pFind = strQuery(pStart).find(strKey)))
      {
         
         if (*(pFind - 1) == '&')
         {
            
            if(strQuery.end() == (pFind + strKey.length()))
            {
               
               strValue = "";
               
               return true;
               
            }
            else if(*(pFind + strKey.length()) == '=')
            {
               
               auto pFind2 = strQuery(pFind + strKey.length() + 1).find('&');
               
               if(pFind2 > strQuery.begin())
               {
                  
                  strValue = strQuery.substr(pFind + strKey.length() + 1, pFind2 - (pFind + strKey.length() + 1));
                  
               }
               else
               {
                  
                  strValue = strQuery.substr(pFind + strKey.length() + 1);
                  
               }
               
               return true;
               
            }
            
         }
         
         pStart = pFind + strKey.length() + 1;
         
      }

      return false;

   }


   bool url::query_has_param(const ::string & strQuery, const ::string & strKey)
   {

      strsize iCmp = strQuery.length() - strKey.length();
      
      if(iCmp < 0)
      {
         
         return false;
         
      }

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

      auto iStart = strKey.length();

      ::string::const_iterator pFind;

      while(found(pFind = strQuery(iStart).find(strKey)))
      {
         
         if(*(pFind - 1) == '&')
         {
            
            if(strQuery.end() == (pFind + strKey.length()))
            {
               
               return true;
               
            }
            else if(*(pFind + strKey.length()) == '=')
            {
               
               return true;
               
            }
            
         }
         
         iStart = strQuery.offset_of(pFind + strKey.length() + 1);
         
      }

      return false;
      
   }


   bool url::query_param_has_char(const ::string & strQuery, const ::string & strKey)
   {

      strsize iCmp = strQuery.length() - strKey.length();
      
      if(iCmp < 0)
      {
         
         return false;
         
      }

      if(ansi_count_compare(strQuery, strKey, strKey.length()) == 0)
      {
         
         if(iCmp == 0)
         {
            
            return false;
            
         }
         else if(strQuery[strKey.length()] == '=')
         {
            
            auto pFind2 = strQuery(strKey.length() + 1).find('&');
            
            if(pFind2 > strQuery.begin())
            {
               
               return (strQuery.offset_of(pFind2) - (strKey.length() + 1)) > 0;
               
            }
            else
            {
               
               return (strQuery.length() - (strKey.length() + 1)) > 0;
               
            }

         }

      }

      auto iStart = strKey.length();

      ::string::const_iterator pFind;

      while(found(pFind = strQuery(iStart).find(strKey)))
      {
         
         if(*(pFind - 1) == '&')
         {
            
            if(strQuery.end() == (pFind + strKey.length()))
            {
               
               return false;
               
            }
            else if(*(pFind + strKey.length()) == '=')
            {
               
               auto pFind2 = strQuery(pFind + strKey.length() + 1).find('&');
               
               if(found(pFind2))
               {
                  
                  return (pFind2 - (pFind + strKey.length() + 1)) > 0;
                  
               }
               else
               {
                  
                  return (strQuery.length() - (strQuery.offset_of(pFind) + strKey.length() + 1)) > 0;
                  
               }
               
            }
            
         }
         
         iStart = strQuery.offset_of(pFind + strKey.length() + 1);
         
      }

      return false;

   }


   bool url::query_has_param_replace(string & strQuery, const ::string & strKey, const ::string & strValue)
   {

      strsize iCmp = strQuery.length() - strKey.length();
      
      if(iCmp < 0)
      {

         return false;
         
      }

      if(ansi_count_compare(strQuery, strKey, strKey.length()) == 0)
      {
         
         if(iCmp == 0)
         {
            
            strQuery += "=" + strValue;
            
            return true;
            
         }
         else if(strQuery[strKey.length()] == '=')
         {
            
            auto pFind2 = strQuery(strKey.length() + 1).find('&');
            
            if(pFind2 > strQuery.begin())
            {
               
               strQuery = strQuery.left(strKey.length() + 1) + strValue + strQuery.substr(pFind2);
               
            }
            else
            {
               
               strQuery = strQuery.left(strKey.length() + 1) + strValue;
               
            }
            
            return true;
            
         }

      }

      strsize iStart = strKey.length();

      ::string::const_iterator pFind;

      while(found(pFind = strQuery(iStart).find(strKey)))
      {
         
         if(*(pFind - 1) == '&')
         {
            
            if(strQuery.end() == (pFind + strKey.length()))
            {
               
               strQuery += "=" + strValue;
               
               return true;
               
            }
            else if(*(pFind + strKey.length()) == '=')
            {
               
               auto pFind2 = strQuery(pFind + strKey.length() + 1).find('&');
               
               if(pFind2 > strQuery.begin())
               {
                  
                  strQuery = strQuery.left(pFind + strKey.length() + 1) + strValue + strQuery.substr(pFind2);
                  
               }
               else
               {
                  
                  strQuery = strQuery.left(pFind + strKey.length() + 1) + strValue;
                  
               }
               
               return true;
               
            }
            
         }
         
         iStart = strQuery.offset_of(pFind + strKey.length() + 1);
         
      }

      return false;

   }


   bool url::locale_is_eu(const ::atom & idLocale)
   {

      if(
         idLocale == "eu"
      || idLocale == "se"
      || idLocale == "at"
      || idLocale == "dk"
      || idLocale == "en_uk"
      || idLocale == "uk"
      || idLocale == "fi"
      || idLocale == "gr"
      || idLocale == "de"
      || idLocale == "nl"
      || idLocale == "be"
      || idLocale == "fr"
      || idLocale == "it"
      || idLocale == "pt"
      || idLocale == "cz"
      || idLocale == "lu"
      || idLocale == "ie"
      || idLocale == "no"
      || idLocale == "cy"
      || idLocale == "su"
      || idLocale == "lv"
      || idLocale == "li"
      || idLocale == "hu"
      || idLocale == "es"
      || idLocale == "sk"
      || idLocale == "cz"
      || idLocale == "si"
      || idLocale == "ro"
      || idLocale == "kz"
      || idLocale == "ru"
      || idLocale == "pl"
      || idLocale == "tr"
      || idLocale == "ee")
      {
         return true;
      }

      return false;

   }

   bool url::locale_is_asia(const ::atom & idLocale)
   {

      if(idLocale == "asia"
            || idLocale == "cn"
            || idLocale == "tw"
            || idLocale == "vn"
            || idLocale == "in"
            || idLocale == "kg"
            || idLocale == "kz"
            || idLocale == "kr"
            || idLocale == "my"
            || idLocale == "ph"
            || idLocale == "sg"
            || idLocale == "su"
            || idLocale == "ru"
            || idLocale == "zh"
            || idLocale == "hk"
            || idLocale == "ja"
            || idLocale == "jp"
            || idLocale == "tr")
      {
         return true;
      }

      return false;

   }

   bool url::locale_is_middle_east(const ::atom & idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == "sy"
            || idLocale == "tr"
            || idLocale == "il"
            || idLocale == "ps")
      {
         return true;
      }

      return false;

   }



   bool url::locale_is_south_america(const ::atom & idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == "ar"
            || idLocale == "bo"
            || idLocale == "br"
            || idLocale == "cl"
            || idLocale == "co"
            || idLocale == "ec"
            || idLocale == "gs"
            || idLocale == "pe"
            || idLocale == "py"
            || idLocale == "uy"
            || idLocale == "ve"
            || idLocale == "amdesur")
      {
         return true;
      }

      return false;

   }

   bool url::locale_is_oceania(const ::atom & idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == "au"
            || idLocale == "oceania"
            || idLocale == "nz"
            || idLocale == "tl")
      {
         return true;
      }

      return false;

   }


   bool url::locale_is_africa(const ::atom & idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == "ug"
            || idLocale == "sc"
            || idLocale == "cm"
            || idLocale == "za"
            || idLocale == "africa" )
      {
         return true;
      }

      return false;

   }

   bool url::locale_is_latin_america(const ::atom & idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == "mx")
      {
         return true;
      }

      return locale_is_caribe(idLocale) || locale_is_central_america(idLocale) || locale_is_south_america(idLocale);

   }

   bool url::locale_is_north_america(const ::atom & idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == "mx"
            || idLocale == "us"
            || idLocale == "ca")
      {
         return true;
      }

      return false;

   }

   bool url::locale_is_caribe(const ::atom & idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == "caribe")
         return true;

      if(idLocale == "ht"
            || idLocale == "cu"
            || idLocale == "tc")
      {
         return true;
      }

      return false;

   }


   bool url::locale_is_central_america(const ::atom & idLocale)
   {

      string strLocale(idLocale);

      if(strLocale == "central_america")
         return true;

      if(idLocale == "centralam")
         return true;

      if(idLocale == "bz")
      {
         return true;
      }

      return false;

   }

   bool url::locale_is_america(const ::atom & idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == "america")
         return true;

      return
      locale_is_central_america(idLocale)
      || locale_is_caribe(idLocale)
      || locale_is_south_america(idLocale)
      || locale_is_north_america(idLocale);

   }


   bool url::server_ends(string strUrl, string strRoot)
   {

      string strServer = get_server(strUrl);

      if(strServer.case_insensitive_order(strRoot) == 0)
      {

         return true;

      }

      if(string_ends_ci(strServer, "." + strRoot))
      {

         return true;

      }

      return false;

   }



   string url::set_script(const ::string & strUrl, const ::string & strScript)
   {

      return get_protocol(strUrl) + "://" + get_root(strUrl) + string(strScript) + ::str().has_char(get_query(strUrl), "?");

   }


   string url::override_if_empty(const ::string & strDst, const ::string & strSrc, bool bOverrideQuery)
   {

      string strProtocol = get_protocol(strDst);
      string strProtocolOver = get_protocol(strSrc);
      string strRoot = get_root(strDst);
      string strRootOver = get_root(strSrc);
      string strScript = get_script(strDst);
      string strScriptOver = get_script(strSrc);
      string strQuery = get_query(strDst);
      string strQueryOver = get_query(strSrc);

      if(strProtocol.is_empty())
         strProtocol = strProtocolOver;

      if(strRoot.is_empty())
         strRoot = strRootOver;

      if(strScript.is_empty())
         strScript = strScriptOver;

      if(bOverrideQuery && strQuery.is_empty())
         strQuery = strQueryOver;

      if (!string_begins(strScript, "/"))
         strScript = "/" + strScript;

      return strProtocol + "://" + strRoot + strScript + ::str().has_char(strQuery, "?");

   }


   string url::override_if_set_at_source(const ::string & strDst, const ::string & strSrc)
   {

      string strProtocol = get_protocol(strDst);
      string strProtocolOver = get_protocol(strSrc);
      string strRoot = get_root(strDst);
      string strRootOver = get_root(strSrc);
      string strScript = get_script(strDst);
      string strScriptOver = get_script(strSrc);
      string strQuery = get_query(strDst);
      string strQueryOver = get_query(strSrc);

      if(strProtocolOver.has_char())
         strProtocol = strProtocolOver;

      if(strRootOver.has_char())
         strRoot = strRootOver;

      if(strScriptOver.has_char())
         strScript = strScriptOver;

      if(strQueryOver.has_char())
         strQuery = strQueryOver;

      if (!string_begins(strScript, "/"))
         strScript = "/" + strScript;

      return strProtocol + "://" + strRoot + strScript + ::str().has_char(strQuery, "?");
   }


   string url::to_punycode(const ::string & str)
   {

      return ::idn_to_punycode(str);

   }

   string url::from_punycode(const ::string & str)
   {

      return ::idn_from_punycode(str);

   }


   inline bool character_isalnum(i32 i)
   {

      return (i >= '0' && i <= '9') || (i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z');

   }


   bool url::is_valid_public_domain(const string& strDomain)
   {

      critical_section_lock lock(&m_csPublicDomainExtension);

      if (m_straPublicDomainExtension.is_empty())
      {

         acmesystem()->get_public_internet_domain_extension_list(m_straPublicDomainExtension);

      }

      bool bPublicDomainExtensionListSuffixesDomain = m_straPublicDomainExtension.suffix_find_first_ci(strDomain) >= 0;

      return bPublicDomainExtensionListSuffixesDomain;

   }


   string url::os_fs(string strUrl, bool bPath)
   {

      strUrl.replace_with("_lt_", "<");
      strUrl.replace_with("_gt_", ">");
      strUrl.replace_with("_cl_", ":");
      strUrl.replace_with("_dot_", ".");

      if(bPath)
      {

         strUrl.replace_with("/", "\\");

      }
      else
      {

         strUrl.replace_with("_sl_","/");
         strUrl.replace_with("_bsl_","\\");

      }

      strUrl.replace_with("_", " ");

      return strUrl;

   }


   string url::os_fspath(string strUrl)
   {

      return os_fs(strUrl, true);

   }


   string url::os_fsname(string strUrl)
   {

      return os_fs(strUrl, false);

   }


} // namespace url






#include "framework.h"
#include "acme/primitive/string/hex.h"
// #include "acme/primitive/string/string.h"


char* string_append_character(char* psz, ::ansi_character ch)
{

   *psz = ch;

   psz++;

   *psz = '\0';

   return psz;

}


bool is_url(const ::scoped_string & scopedstrCandidate, const char** ppszRequest)
{

   const ::ansi_character * psz = scopedstrCandidate;

   while (*psz != '\0' && (*psz == '.' || *psz == '_' || *psz == '-' || character_isalnum(*psz)))
   {
      psz++;
   }
   if (psz == scopedstrCandidate.begin())
      return false;
   if (psz == scopedstrCandidate.begin() + 1)
      return false;
   if (*psz != ':')
      return false;
   psz++;
   if (*psz != '/' && *psz != '\\')
      return false;
   psz++;
   if (*psz == '/' || *psz == '\\')
   {
      psz++;
   }
   /*if(*psz != '/' && *psz != '\\')
      return false;
   psz++;*/
   while (*psz != '\0' && (*psz == '.' || *psz == ':' || *psz == '@' || *psz == '_' || *psz == '-' || character_isalnum(*psz)))
   {
      psz++;
   }
   if (*psz != '\0' && *psz != '/' && *psz != '\\')
      return false;
   if (ppszRequest != nullptr)
   {
      *ppszRequest = psz;
   }
   return true;

}


CLASS_DECL_ACME bool is_like_url_protocol(const ::scoped_string & scopedstr)
{

   if (scopedstr.is_empty())
   {

      return false;

   }

   auto psz = scopedstr.begin();

   if (character_isalpha(*psz))
   {

      psz++;

   }

   if (*psz == ':' && (psz[1] == '\0' || (psz[1] == '/' && psz[2] == '/' && psz[3] == '\0')))
   {

      return true;

   }

   while (character_isalnum(*psz) || *psz == '-' || *psz == '_' || *psz == '.')
   {

      psz++;

   }

   if (*psz == ':' && (psz[1] == '\0' || (psz[1] == '/' && psz[2] == '/' && psz[3] == '\0')))
   {

      return true;

   }

   return false;

}




//#include "framework.h"
//#include "net.h"
//#include "as_string.h"
//#include "acme/exception/parsing.h"
//#include "acme/primitive/string/hex.h"
////#include "acme/operating_system.h"


//CLASS_DECL_ACME string ::url::decode(const & strParam)
//{
//
//   return ::url::decode(strParam, strParam.length());
//
//   /*string str(strParam);
//
//   string strDecode;
//
//   str.replace_with(" ", "+");
//
//   strsize iStart = 0;
//
//   while(true)
//   {
//
//      auto pFind = str.find("%",iStart);
//
//      if(iFind == -1)
//      {
//         strDecode += str.substr(iStart);
//         break;
//      }
//
//      strDecode += str.substr(iStart,iFind - iStart);
//
//      if(str[iFind + 1] == '%')
//      {
//
//         strDecode += "%";
//         iStart = iFind + 2;
//
//      }
//      else
//      {
//
//         char ch = (char)strtol(str.substr(iFind + 1,2),nullptr,16);
//
//         if(ch != 0)
//         {
//            strDecode += ch;
//         }
//
//         iStart = iFind + 3;
//
//      }
//
//
//   }
//
//   return strDecode;*/
//
//
//}
//


namespace url
{


   string decode(const ::block& block)
   {

      auto sizeLen = block.size();

      string strDecode;

      char* pszStart = strDecode.get_string_buffer(sizeLen * 4);

      auto pszDecode = pszStart;

      strsize i = 0;

      const ::ansi_character * pszEncoded = (const char*)block.begin();

      while (*pszEncoded != '\0' && i < sizeLen)
      {

         if (*pszEncoded == '+')
         {

            i++;

            *pszDecode = ' ';

            pszDecode++;

            pszEncoded++;

         }
         else if (*pszEncoded == '%')
         {

            sizeLen--;

            pszEncoded++;

            if (*pszEncoded == '%')
            {

               i++;

               *pszDecode = '%';

               pszDecode++;

               pszEncoded++;

            }
            else
            {

               i++;

               sizeLen--;

               auto nibble1 = hex::to_nibble(*pszEncoded++);

               if (nibble1 < 0)
               {

                  throw_parsing_exception("url decode: % first nibble non hex");

               }

               auto nibble2 = hex::to_nibble(*pszEncoded++);

               if (nibble2 < 0)
               {

                  throw_parsing_exception("url decode: % second nibble non hex");

               }

               *pszDecode = (char)(uchar)(((nibble1 << 4) & 0xf0) | (nibble2 & 0xf));

               pszDecode++;

            }

         }
         else
         {

            i++;

            *pszDecode = *pszEncoded;

            pszDecode++;

            pszEncoded++;

         }

      }

      strDecode.release_string_buffer(sizeLen);

      return ::move(strDecode);

   }



   CLASS_DECL_ACME bool query_get_param(string& strParam, const ::ansi_character * pszKey, const ::ansi_character * pszUrl)
   {

      const ::ansi_character * pszBeg;
      const ::ansi_character * pszEnd;

      {

         string strKey;

         strKey = "?";
         strKey += pszKey;
         strKey += "=";

         pszBeg = ansi_find_string(pszUrl, strKey);

         if (pszBeg != nullptr)
         {

            pszBeg += strKey.length();

            goto success;

         }

      }

      {

         string strKey;

         strKey = "&";
         strKey += pszKey;
         strKey += "=";

         pszBeg = ansi_find_string(pszUrl, strKey);

         if (pszBeg != nullptr)
         {

            pszBeg += strKey.length();

            goto success;

         }

      }

      {

         string strKey;

         strKey = "?";
         strKey += pszKey;
         strKey += "&";

         pszBeg = ansi_find_string(pszUrl, strKey);

         if (pszBeg != nullptr)
         {

            strParam = "";

            return true;

         }

      }

      {

         string strKey;

         strKey = "&";
         strKey += pszKey;
         strKey += "&";

         pszBeg = ansi_find_string(pszUrl, strKey);

         if (pszBeg != nullptr)
         {

            strParam = "";

            return true;

         }

      }

      return false;

   success:

      pszEnd = ansi_find_string(pszBeg, "&");

      if (pszEnd == nullptr)
      {
         strParam = pszBeg;
      }
      else
      {
         strParam = string(pszBeg, pszEnd - pszBeg);
      }

      return true;

   }


   string encode(const ::block& block)
   {

      string strEncoded;

      auto pszEncodedStart = strEncoded.get_string_buffer(block.size() * 5);

      auto pszEncoded = pszEncodedStart;

      auto pszInput = (const char*)block.begin();

      memset(pszEncoded, 0, block.size() * 5);

      while (*pszInput != '\0')
      {

         char ch = *pszInput;

         if (ansi_char_isalnum(ch)
            || ch == '.'
            || ch == '-'
            || ch == '_')
         {

            pszEncoded = string_append_character(pszEncoded, ch);

         }
         else if (ch == ' ')
         {

            pszEncoded = string_append_character(pszEncoded, '+');

         }
         else
         {

            pszEncoded = string_append_character(pszEncoded, '%');

            pszEncoded = string_append_character(pszEncoded, ::hex::nibble_upper_from((ch >> 4) & 0xf));

            pszEncoded = string_append_character(pszEncoded, ::hex::nibble_upper_from(ch & 0xf));

         }

         pszInput++;

      }

      strEncoded.release_string_buffer(pszEncoded - pszEncodedStart);

      return ::move(strEncoded);

   }


} // namespace urls



//string str;
//
//string strChar;
//
//while (*psz != '\0')
//{
//
//   if (ansi_char_isdigit(*psz)
//      || ansi_char_isalpha(*psz)
//      || *psz == '.'
//      || *psz == '-'
//      || *psz == '_')
//   {
//      str += *psz;
//   }
//   else if (*psz == ' ')
//   {
//      str += "+";
//   }
//   else
//   {
//      strChar.format("%02X", *psz);
//      str += "%" + strChar.right(2);
//   }
//
//   psz++;
//}
//
//return str;






















#if defined(MACOS)
#elif defined(APPLE_IOS)

void openURL(const string& url_str);

int ui_open_url(const ::ansi_character * psz);

void openURL(const string& url_str)
{
   //   throw ::exception(todo);
   //   CFURLRef url = CFURLCreateWithBytes(
   //      nullptr,                        // allocator
   //      (::u328*)url_str.c_str(),     // URLBytes
   //      url_str.length(),            // length
   //      kCFStringEncodingASCII,      // encoding
   //      nullptr                         // baseURL
   //      );
   //       LSOpenCFURLRef(url,0);

   ui_open_url(url_str);

   //   CFRelease(url);
}


#endif











//#ifdef WINDOWS
//#define strdup _strdup
//#endif
//
//CLASS_DECL_ACME int_bool freerdp_get_credentials(void * instance, char** username,char** password,char** domain, const ::ansi_character * pszServerName, int bInteractive)
//{
//
//   ::acme::application * papp = (::acme::application *) instance;
//
//   ::account::user user;
//
//   user.initialize(papp);
//
//   ::account::credentials credentials;
//
//   credentials.initialize_account_credentials(&user, Sess(papp).account()->storage());
//
//   //string strUsername;
//
//   //string strUser;
//
//   //string strDomain;
//
//   //string strPassword;
//
//   //string strToken;
//
//   credentials.m_strToken = Sys(papp).crypto_md5_text(pszServerName);
//
//   //string strTitle;
//
//   credentials.m_strTitle = "Enter Credentials for : " + string(pszServerName);
//
//   credentials.m_bInteractive = bInteractive;
//
//   //strUsername = acmefile()->as_string(         auto psystem = acmesystem();
//
//         auto pacmedirectory = psystem->m_pacmedirectory;
//
//pacmedirectory->system() / "config\\user.txt");
////
////   //strPassword = acmefile()->as_string(         auto psystem = acmesystem();
//
//         auto pacmedirectory = psystem->m_pacmedirectory;
//
//pacmedirectory->system() / "config\\pass.txt");
////
//   //if(strUsername.has_char() && strPassword.has_char())
//   //{
//
//   //}
//   //else
//   //{
//
//   if(credentials.get_credentials() != ::success_credentials)
//   {
//
//      return false;
//
//   }
//
//   string strUser;
//
//   string strPassword(credentials.m_strPassword);
//
//   string strDomain;
//
//   auto pFind = user.m_strLogin.find('/');
//
//   if(iFind > 0)
//   {
//
//      strUser = user.m_strLogin(pFind + 1);
//
//      strDomain = user.m_strLogin(0, pFind);
//
//   }
//   else
//   {
//
//      strUser = user.m_strLogin;
//
//   }
//
//   if(username != nullptr)
//   {
//
//      *username = strdup(strUser);
//
//   }
//
//   if(domain != nullptr && strDomain.has_char())
//   {
//
//      *domain = strdup(strDomain);
//
//   }
//
//   if(password != nullptr)
//   {
//
//      *password = strdup(strPassword);
//
//   }
//
//   return true;
//
//}







//CLASS_DECL_ACME bool is_url(const ::ansi_character * pszCandidate)
//{
//
//   string strCandidate(pszCandidate);
//
//   strsize iLen = strCandidate.length();
//
//   strsize i = 0;
//
//   char ch;
//
//   while (i < iLen)
//   {
//
//      ch = strCandidate[i];
//
//      if (isalpha((uchar)ch))
//         i++;
//      else if (ch == '.')
//         i++;
//      else if (ch == ':' && (((i + 1) == iLen) ||
//         (iLen > (i + 3)
//            && strCandidate[i + 1] == '/'
//            && strCandidate[i + 2] == '/')))
//         return true;
//      else
//         return false;
//
//   }
//
//   return false;
//
//}





//CLASS_DECL_ACME string ::url::decode(const ::ansi_character * psz)
//{
//
//   string str(psz);
//
//   string strDecode;
//
//   str.replace_with(" ", "+");
//
//   strsize iStart = 0;
//
//   while (true)
//   {
//
//      auto pFind = str.find("%", iStart);
//
//      if (iFind == -1)
//      {
//         strDecode += str.substr(iStart);
//         break;
//      }
//
//      strDecode += str.substr(iStart, iFind - iStart);
//
//      if (str[iFind + 1] == '%')
//      {
//
//         strDecode += "%";
//         iStart = iFind + 2;
//
//      }
//      else
//      {
//
//         char ch = (char)strtol(str.substr(iFind + 1, 2), nullptr, 16);
//
//         if (ch != 0)
//         {
//            strDecode += ch;
//         }
//
//         iStart = iFind + 3;
//
//      }
//
//
//   }
//
//   return ::move(strDecode);
//
//
//}



//string ::url::decode(const ::ansi_character * pszUrl, strsize iLen)
//
//{
//
//   string strDecode;
//
//   char* psz = strDecode.get_string_buffer(iLen * 4);
//
//   strsize i = 0;
//
//   while (*pszUrl != '\0' && i < iLen)
//
//   {
//      if (*pszUrl == '+')
//
//      {
//         i++;
//         *psz = ' ';
//         psz++;
//         pszUrl++;
//
//      }
//      else if (*pszUrl == '%')
//
//      {
//         iLen--;
//         pszUrl++;
//
//         if (*pszUrl == '%')
//
//         {
//            i++;
//            *psz = '%';
//            psz++;
//            pszUrl++;
//
//         }
//         else
//         {
//            i++;
//            iLen--;
//            *psz = (char)(uchar)(hex::to(*pszUrl) * 16 + hex::to(*(pszUrl + 1)));
//
//            psz++;
//            pszUrl += 2;
//
//         }
//      }
//      else
//      {
//         i++;
//         *psz = *pszUrl;
//
//         psz++;
//         pszUrl++;
//
//      }
//   }
//
//   strDecode.release_string_buffer(iLen);
//
//   return strDecode;
//
//}
//
//




//CLASS_DECL_ACME bool url_query_get_param(string& strParam, const ::ansi_character * pszKey, const ::ansi_character * pszUrl)
//{
//
//   const ::ansi_character * pszBeg;
//   const ::ansi_character * pszEnd;
//
//   {
//
//      string strKey;
//
//      strKey = "?";
//      strKey += pszKey;
//      strKey += "=";
//
//      pszBeg = ansi_find_string(pszUrl, strKey);
//
//      if (pszBeg != nullptr)
//      {
//
//         pszBeg += strKey.length();
//
//         goto success;
//
//      }
//
//   }
//
//   {
//
//      string strKey;
//
//      strKey = "&";
//      strKey += pszKey;
//      strKey += "=";
//
//      pszBeg = ansi_find_string(pszUrl, strKey);
//
//      if (pszBeg != nullptr)
//      {
//
//         pszBeg += strKey.length();
//
//         goto success;
//
//      }
//
//   }
//
//   {
//
//      string strKey;
//
//      strKey = "?";
//      strKey += pszKey;
//      strKey += "&";
//
//      pszBeg = ansi_find_string(pszUrl, strKey);
//
//      if (pszBeg != nullptr)
//      {
//
//         strParam = "";
//
//         return true;
//
//      }
//
//   }
//
//   {
//
//      string strKey;
//
//      strKey = "&";
//      strKey += pszKey;
//      strKey += "&";
//
//      pszBeg = ansi_find_string(pszUrl, strKey);
//
//      if (pszBeg != nullptr)
//      {
//
//         strParam = "";
//
//         return true;
//
//      }
//
//   }
//
//   return false;
//
//success:
//
//   pszEnd = ansi_find_string(pszBeg, "&");
//
//   if (pszEnd == nullptr)
//   {
//      strParam = pszBeg;
//   }
//   else
//   {
//      strParam = string(pszBeg, pszEnd - pszBeg);
//   }
//
//   return true;
//
//}








//CLASS_DECL_ACME string ::url::encode(const ::ansi_character * psz)
//{
//
//   string str;
//
//   char sz[256];
//
//   while (*psz != '\0')
//   {
//
//      char uch = *psz;
//
//      if (ansi_char_isdigit(uch)
//         || ansi_char_isalpha(uch)
//         || uch == '.'
//         || uch == '-'
//         || uch == '_')
//      {
//
//         str += uch;
//
//      }
//      else if (uch == ' ')
//      {
//
//         str += "+";
//
//      }
//      else
//      {
//
//         ansi_from_i64(sz, uch, 16);
//
//         ansi_upper(sz);
//
//         if (ansi_length(sz) == 0)
//         {
//
//            str += "%00";
//
//         }
//         else if (ansi_length(sz) == 1)
//         {
//
//            str += "%0";
//
//            str += sz;
//
//         }
//         else if (ansi_length(sz) == 2)
//         {
//
//            str += "%";
//
//            str += sz;
//
//         }
//
//      }
//
//      psz++;
//
//   }
//
//   return str;
//
//}


//string str;
//
//string strChar;
//
//while (*psz != '\0')
//{
//
//   if (ansi_char_isdigit(*psz)
//      || ansi_char_isalpha(*psz)
//      || *psz == '.'
//      || *psz == '-'
//      || *psz == '_')
//   {
//      str += *psz;
//   }
//   else if (*psz == ' ')
//   {
//      str += "+";
//   }
//   else
//   {
//      strChar.format("%02X", *psz);
//      str += "%" + strChar.right(2);
//   }
//
//   psz++;
//}
//
//return str;






















#if defined(MACOS)

//void openURL(const string& url_str);
//
//
//void openURL(const string& url_str)
//{
//   CFURLRef url = CFURLCreateWithBytes(
//      nullptr,                        // allocator
//      (::u328*)url_str.c_str(),     // URLBytes
//      url_str.length(),            // length
//      kCFStringEncodingASCII,      // encoding
//      nullptr                         // baseURL
//   );
//   LSOpenCFURLRef(url, 0);
//   CFRelease(url);
//}

#elif defined(APPLE_IOS)

void openURL(const string& url_str);

int ui_open_url(const ::ansi_character * psz);

//void openURL(const string& url_str)
//{
//   //   throw ::exception(todo);
//   //   CFURLRef url = CFURLCreateWithBytes(
//   //      nullptr,                        // allocator
//   //      (::u328*)url_str.c_str(),     // URLBytes
//   //      url_str.length(),            // length
//   //      kCFStringEncodingASCII,      // encoding
//   //      nullptr                         // baseURL
//   //      );
//   //       LSOpenCFURLRef(url,0);
//
//   ui_open_url(url_str);
//
//   //   CFRelease(url);
//}


#endif











//#ifdef WINDOWS
//#define strdup _strdup
//#endif
//
//CLASS_DECL_ACME int_bool freerdp_get_credentials(void * instance, char** username,char** password,char** domain, const ::ansi_character * pszServerName, int bInteractive)
//{
//
//   ::application * papp = (::apex::application *) instance;
//
//   ::account::user user;
//
//   user.initialize(papp);
//
//   ::account::credentials credentials;
//
//   credentials.initialize_account_credentials(&user, Sess(papp).account()->storage());
//
//   //string strUsername;
//
//   //string strUser;
//
//   //string strDomain;
//
//   //string strPassword;
//
//   //string strToken;
//
//   credentials.m_strToken = Sys(papp).crypto_md5_text(pszServerName);
//
//   //string strTitle;
//
//   credentials.m_strTitle = "Enter Credentials for : " + string(pszServerName);
//
//   credentials.m_bInteractive = bInteractive;
//
//   //strUsername = acmefile()->as_string(         auto psystem = acmesystem();

   /*      auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "config\\user.txt")*/;
//
//   //strPassword = acmefile()->as_string(         auto psystem = acmesystem();
//
//         auto pacmedirectory = psystem->m_pacmedirectory;
//
//pacmedirectory->system() / "config\\pass.txt");
//
//   //if(strUsername.has_char() && strPassword.has_char())
//   //{
//
//   //}
//   //else
//   //{
//
//   if(credentials.get_credentials() != ::success_credentials)
//   {
//
//      return false;
//
//   }
//
//   string strUser;
//
//   string strPassword(credentials.m_strPassword);
//
//   string strDomain;
//
//   auto pFind = user.m_strLogin.find('/');
//
//   if(iFind > 0)
//   {
//
//      strUser = user.m_strLogin(pFind + 1);
//
//      strDomain = user.m_strLogin(0, pFind);
//
//   }
//   else
//   {
//
//      strUser = user.m_strLogin;
//
//   }
//
//   if(username != nullptr)
//   {
//
//      *username = strdup(strUser);
//
//   }
//
//   if(domain != nullptr && strDomain.has_char())
//   {
//
//      *domain = strdup(strDomain);
//
//   }
//
//   if(password != nullptr)
//   {
//
//      *password = strdup(strPassword);
//
//   }
//
//   return true;
//
//}











