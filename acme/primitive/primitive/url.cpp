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

      index iPos = str.find(":");

      if(iPos == -1)
      {

         return "";

      }

      return str.Mid(0, iPos);

   }


   string url::get_root(const ::string & strParam)
   {

      string str(strParam);

      index iPos = str.find(":");
      if (iPos == -1)
         return strParam;
      iPos++;
      while (iPos < str.get_length() && str[iPos] == '/')
      {
         iPos++;
      }
      index iStart = iPos;
      index iEnd = str.find("/", iStart);
      index iArgumentsStart = str.find("?", iStart);

      if (iEnd < 0 || (iArgumentsStart > 0 && iEnd > iArgumentsStart))
      {

         return {};

      }

      return str.Mid(iStart, iEnd - iStart);

   }


   string url::get_server(const ::string & strParam)
   {

      string strRoot = get_root(strParam);

      strsize iPos = strRoot.find(":");

      if(iPos < 0)
         return strRoot;

      return strRoot.Left(iPos);

   }


   i32 url::get_port(const ::string & strParam, i32 iDefault)
   {

      string strRoot = get_root(strParam);

      strsize iPos = strRoot.find(":");

      if(iPos < 0)
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

      return atoi(strRoot.Mid(iPos + 1));

   }


   string url::get_object(const ::string & strParam)
   {

      string str(strParam);

      strsize iPos1 = str.find("://");

      strsize iPos2 = str.find(":/");

      strsize iPos;

      if(iPos1 < 0)
      {

         if (iPos2 < 0)
         {

            return strParam;

         }
         else
         {

            iPos = iPos2 + 2;

         }

      }
      else if(iPos2 < 0)
      {

         iPos = iPos1 + 3;

      }
      else if(iPos1 <= iPos2)
      {

         iPos = iPos1 + 3;

      }
      else
      {

         iPos = iPos2 + 2;         

      }

      strsize iStart = str.find("/", iPos);

      if (iStart < 0)
      {

         return "/";

      }
      else
      {

         return str.Mid(iStart);

      }

   }


   string url::object_get_script(const ::string & strParam) // page
   {

      string str(strParam);

      strsize iFind = str.find('?');

      if (iFind < 0)
      {

         return ::url::decode(str);

      }
      else
      {

         return ::url::decode(str.Left(iFind));

      }

   }


   string url::object_get_query(const ::string & strParam) // id=1
   {

      string str(strParam);

      strsize iFind = str.find('?');

      if (iFind < 0)
      {

         return "";

      }
      else
      {

         return str.Mid(iFind + 1);

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

      if (str1.Right(1) == "/")
      {

         str1 = str1.Left(str1.get_length() - 1);

      }

      if (str2.Left(1) == "/")
      {

         str2 = str2.Right(str2.get_length() - 1);

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

      strsize iQueryStart = str.find('?');

      if (iQueryStart < 0)
      {

         iQueryStart = str.get_length();

      }

      str = str.Left(iQueryStart);

      strsize iLastSlash = str.reverse_find('/');

      if (iLastSlash < 0)
      {
         
         return "";

      }

      return str.Left(iLastSlash);

   }


   //string url::::url::encode(const ::string & strParam)
   //{

   //   return ::::url::encode(strParam);

   //}


   //string url::::url::decode(const ::string & strParam)
   //{

   //   return ::::url::decode(strParam);

   //}


   //string url::::url::decode(const ::string & strUrl, strsize iLen)
   //{

   //   return ::::url::decode(strUrl,iLen);

   //}


   string url::query_append(const ::string & strUrlParam, const ::string & strQuery)
   {

      string strUrl(strUrlParam);

      strsize iStart = strUrl.find("://");

      if(iStart > 0)
      {

         iStart = strUrl.find("/", iStart + 4);

         if(iStart < 0)
         {

//xxx            FORMATTED_TRACE("invalid url %s", pszUrl);

            iStart = 0;

         }

      }
      else
      {

         iStart = 0;

      }

      if(strUrl.find("?", iStart) > 0)
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


   ::payload & url::var_set(::payload & varUrl, const ::string & strKeyParam, ::payload payload)
   {

      return varUrl = set_key(varUrl.as_string(), strKeyParam, payload);

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

      strsize iPos = strUrl.find("?");

      if (iPos < 0)
      {

         iPos = strUrl.get_length();

      }

      return strUrl.Left(iPos)
             + "?" +
             query_set(strUrl.Mid(iPos + 1), strKeyParam, payload);

   }


   void url::set_key(string & strUrl, const ::string & strUrlParam, const ::string & strKeyParam, ::payload payload)
   {

      strUrl = strUrlParam;

      strsize iPos = strUrl.find('?');

      if (iPos < 0)
      {

         iPos = strUrl.get_length();

      }

      strUrl = strUrl.Left(iPos) + "?" + query_set(strUrl.Mid(iPos + 1), strKeyParam, payload);

   }


   void url::set_param(string & strUrlParam, const ::string & strKeyParam, const ::string & strParam)
   {

      string strUrl(strUrlParam);

      set_param(strUrlParam, strUrl, strKeyParam, strParam);

   }


   void url::set_param(string & strUrl, const ::string & strUrlParam, const ::string & strKeyParam, const ::string & strParam)
   {

      const char * pszQuery = strchr(strUrlParam, '?');

      string strKey = ::url::encode(strKeyParam);
      string strValue = ::url::encode(strParam);

      strsize iLenUrl = strlen(strUrlParam);
      strsize iLenKey = strKey.length();

      string str;

      char * psz = str.get_string_buffer(iLenUrl + iLenKey + strValue.get_length() + 2);

      if(pszQuery == nullptr)
      {
         strcpy(psz, strUrlParam);
         psz[iLenUrl] = '?';
         strcpy(&psz[iLenUrl + 1], strKey);
         psz[iLenUrl + 1 + iLenKey] = '=';
         strcpy(&psz[iLenUrl + 1 + iLenKey + 1], strValue);
         str.release_string_buffer(iLenUrl + iLenKey + strValue.get_length() + 2);
      }
      else
      {
         strsize iFinalLen = pszQuery - strUrlParam;
//         i32 iPos = 0;
         ansi_count_copy(psz, strUrlParam, iFinalLen);
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

      strsize iPos = strUrl.find("?");

      if(iPos < 0)
         return strUrl;

      return strUrl.Left(iPos) + ::str().has_char(query_erase(strUrl.Mid(iPos + 1), strKeyParam), "?");

   }

   ::payload url::get_var(const ::string & strUrlParam, const ::string & strKeyParam)
   {

      string strUrl(strUrlParam);

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return payload(::e_type_empty);
      else
         return query_get_var(strUrl.Mid(iPos + 1), strKeyParam);

   }

   string url::get_param(const ::string & strUrlParam, const ::string & strKeyParam)
   {

      string strUrl(strUrlParam);

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return payload(::e_type_empty);
      else
         return ::url::decode(query_get_param(strUrl.Mid(iPos + 1), strKeyParam));

   }

   bool url::get_param(string & strValue, const ::string & strUrl, const ::string & strKey)
   {

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return false;
      else
         return query_get_param(strValue, strUrl.Mid(iPos + 1), strKey);

   }

   bool url::has_param(const ::string & strUrl, const ::string & strKey)
   {

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return false;
      else
         return query_has_param(strUrl.Mid(iPos + 1), strKey);

   }

   bool url::param_has_char(const ::string & strUrl, const ::string & strKey)
   {

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return false;
      else
         return query_param_has_char(strUrl.Mid(iPos + 1), strKey);
   }


   bool url::has_param_replace(string & strUrl, const ::string & strKeyParam, const ::string & strValueParam)
   {

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return false;
      else
      {

         string strQuery = strUrl.Mid(iPos + 1);

         if(!query_has_param_replace(strQuery, strKeyParam, strValueParam))
            return false;

         strUrl = strUrl.Left(iPos + 1) + strQuery;

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

      string strValue = ::url::encode(payload.as_string());

      if(string_begins(strQuery, strKeyEqual))
      {
         strsize iPos = strQuery.find("&");
         if(iPos < 0)
         {
            strQuery = strKeyEqual2 + strValue;
         }
         else
         {
            strQuery = strKeyEqual2 + strValue + __query_erase(strQuery.Mid(iPos), strAndKeyEqual);
         }
      }
      else if(string_begins(strQuery, strKeyEqual2))
      {
         strsize iPos = strQuery.find("&");
         if(iPos < 0)
         {
            strQuery = strKeyEqual2 + strValue;
         }
         else
         {
            strQuery = strKeyEqual2 + strValue + __query_erase(strQuery.Mid(iPos), strAndKeyEqual);
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
               strQuery = strQuery.Left(iPos) + strAndKeyEqual2 + strValue + __query_erase(strQuery.Mid(iPos), strAndKeyEqual);
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
         strsize iPos = strQuery.find("&");
         if(iPos < 0)
         {
            strQuery = strKey + strParam;
         }
         else
         {
            strQuery = strKey + strParam + __query_erase(strQuery.Mid(iPos), strAndKeyEqual);
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
            strQuery = strKey + strParam + __query_erase(strQuery.Mid(iPos), strAndKeyEqual);
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
         
         strsize iFind = strQuery.find(strAndKeyEqual);
         
         if(iFind < 0)
         {
            
            break;
            
         }
         
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

      strsize iPos = 0;

      if(string_begins(strQuery, strKeyEqual))
      {
         
         iPos = strQuery.find('&');
         
         if(iPos < 0)
         {
            
            payload = strQuery.Mid(strKeyEqual.get_length());
            
            return payload;
            
         }
         else
         {
            
            payload = strQuery.Mid(strKeyEqual.get_length(), iPos - strKeyEqual.get_length());
            
         }
         
      }

      while(true)
      {
         
         iPos = strQuery.find(strAndKeyEqual, iPos);
         
         if(iPos < 0)
         {
            
            break;
            
         }
         
         strsize iEnd = strQuery.find('&', iPos + 1);
         
         if(iEnd < 0)
         {
            
            if(payload.is_new())
            {
               
               payload = strQuery.Mid(iPos + strKeyEqual.get_length());
               
            }
            else
            {
               
               payload.payloada().add(strQuery.Mid(iPos + strKeyEqual.get_length()));
               
            }
            
            return payload;
            
         }
         else
         {
            
            if(payload.is_new())
            {
               
               payload = strQuery.Mid(iPos + strKeyEqual.get_length(), iEnd - (iPos + strKeyEqual.get_length()));
               
            }
            else
            {
               
               payload.payloada().add(strQuery.Mid(iPos + strKeyEqual.get_length(), iEnd - (iPos + strKeyEqual.get_length())));
               
            }
            
         }
         
         iPos++;
         
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

      if(strServer.compare_ci(strRoot) == 0)
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
#include "acme/primitive/string/string.h"


char* string_append_character(char* psz, ansichar ch)
{

   *psz = ch;

   psz++;

   *psz = '\0';

   return psz;

}

bool is_url(const char* pszCandidate, const char** ppszRequest)
{

   const char* psz = pszCandidate;
   while (*psz != '\0' && (*psz == '.' || *psz == '_' || *psz == '-' || character_isalnum(*psz)))
   {
      psz++;
   }
   if (psz == pszCandidate)
      return false;
   if (psz == pszCandidate + 1)
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


CLASS_DECL_ACME bool is_like_url_protocol(const char* psz)
{

   if (is_empty(psz))
   {

      return false;

   }

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
//   return ::url::decode(strParam, strParam.get_length());
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
//      strsize iFind = str.find("%",iStart);
//
//      if(iFind == -1)
//      {
//         strDecode += str.Mid(iStart);
//         break;
//      }
//
//      strDecode += str.Mid(iStart,iFind - iStart);
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
//         char ch = (char)strtol(str.Mid(iFind + 1,2),nullptr,16);
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

      auto sizeLen = block.get_size();

      string strDecode;

      char* pszStart = strDecode.get_string_buffer(sizeLen * 4);

      auto pszDecode = pszStart;

      strsize i = 0;

      const char* pszEncoded = (const char*)block.get_data();

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



   CLASS_DECL_ACME bool query_get_param(string& strParam, const char* pszKey, const char* pszUrl)
   {

      const char* pszBeg;
      const char* pszEnd;

      {

         string strKey;

         strKey = "?";
         strKey += pszKey;
         strKey += "=";

         pszBeg = ansi_find_string(pszUrl, strKey);

         if (pszBeg != nullptr)
         {

            pszBeg += strKey.get_length();

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

            pszBeg += strKey.get_length();

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

      auto pszEncodedStart = strEncoded.get_string_buffer(block.get_size() * 5);

      auto pszEncoded = pszEncodedStart;

      auto pszInput = (const char*)block.get_data();

      memset(pszEncoded, 0, block.get_size() * 5);

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
//      str += "%" + strChar.Right(2);
//   }
//
//   psz++;
//}
//
//return str;






















#if defined(MACOS)
#elif defined(APPLE_IOS)

void openURL(const string& url_str);

int ui_open_url(const char* psz);

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
//CLASS_DECL_ACME int_bool freerdp_get_credentials(void * instance, char** username,char** password,char** domain, const char * pszServerName, int bInteractive)
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
//   index iFind = user.m_strLogin.find('/');
//
//   if(iFind > 0)
//   {
//
//      strUser = user.m_strLogin.Mid(iFind + 1);
//
//      strDomain = user.m_strLogin.Left(iFind);
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







//CLASS_DECL_ACME bool is_url(const char* pszCandidate)
//{
//
//   string strCandidate(pszCandidate);
//
//   strsize iLen = strCandidate.get_length();
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





//CLASS_DECL_ACME string ::url::decode(const char* psz)
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
//      strsize iFind = str.find("%", iStart);
//
//      if (iFind == -1)
//      {
//         strDecode += str.Mid(iStart);
//         break;
//      }
//
//      strDecode += str.Mid(iStart, iFind - iStart);
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
//         char ch = (char)strtol(str.Mid(iFind + 1, 2), nullptr, 16);
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



//string ::url::decode(const char* pszUrl, strsize iLen)
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




//CLASS_DECL_ACME bool url_query_get_param(string& strParam, const char* pszKey, const char* pszUrl)
//{
//
//   const char* pszBeg;
//   const char* pszEnd;
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
//         pszBeg += strKey.get_length();
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
//         pszBeg += strKey.get_length();
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








//CLASS_DECL_ACME string ::url::encode(const char* psz)
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
//      str += "%" + strChar.Right(2);
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

int ui_open_url(const char* psz);

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
//CLASS_DECL_ACME int_bool freerdp_get_credentials(void * instance, char** username,char** password,char** domain, const char * pszServerName, int bInteractive)
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
//   index iFind = user.m_strLogin.find('/');
//
//   if(iFind > 0)
//   {
//
//      strUser = user.m_strLogin.Mid(iFind + 1);
//
//      strDomain = user.m_strLogin.Left(iFind);
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











