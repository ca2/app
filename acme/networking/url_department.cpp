﻿#include "framework.h"
#include "url_department.h"
#include "__string.h"
#include "acme/constant/id.h"
#include "acme/constant/idpool.h"
#include "acme/primitive/primitive/payload.h"
#include "acme/primitive/string/str.h"
#include "acme/platform/system.h"


::string idn_to_punycode(const ::string & str);
::string idn_from_punycode(const ::string & str);


namespace url
{


   department::department()
   {


   }


   department::~department()
   {


   }


   string department::get_protocol(const ::string & strParam)
   {

      string str(strParam);

      index iPos = str.find(":");

      if(iPos == -1)
      {

         return "";

      }

      return str.Mid(0, iPos);

   }


   string department::get_root(const ::string & strParam)
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


   string department::get_server(const ::string & strParam)
   {

      string strRoot = get_root(strParam);

      strsize iPos = strRoot.find(":");

      if(iPos < 0)
         return strRoot;

      return strRoot.Left(iPos);

   }


   i32 department::get_port(const ::string & strParam, i32 iDefault)
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


   string department::get_object(const ::string & strParam)
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


   string department::object_get_script(const ::string & strParam) // page
   {

      string str(strParam);

      strsize iFind = str.find('?');

      if (iFind < 0)
      {

         return url_decode(str);

      }
      else
      {

         return url_decode(str.Left(iFind));

      }

   }


   string department::object_get_query(const ::string & strParam) // id=1
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


   string department::object_set(const ::string & strObject, const ::string & strKeyParam, ::payload payload)
   {

      string strQuery = object_get_query(strObject);

      return object_get_script(strObject) + ::str().has_char(query_set(strQuery, strKeyParam, payload), "?");

   }


   string department::get_script(const ::string & strParam) // page
   {

      return object_get_script(get_object(strParam));

   }


   string department::get_query(const ::string & strParam) // id=1
   {

      return object_get_query(get_object(strParam));

   }


   string department::object(const ::string & strScriptParam, const ::string & strQueryParam)
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


   string department::path(const ::string & str1Param, const ::string & str2Param)
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


   string department::path(const ::string & str1, const ::string & str2, const ::string & str3)
   {

      return path(path(str1, str2), str3);

   }


   string department::name(const ::string & strParam)
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


   string department::url_encode(const ::string & strParam)
   {

      return ::url_encode(strParam);

   }


   string department::url_decode(const ::string & strParam)
   {

      return ::url_decode(strParam);

   }


   string department::url_decode(const ::string & strUrl, strsize iLen)
   {

      return ::url_decode(strUrl,iLen);

   }


   string department::query_append(const ::string & strUrlParam, const ::string & strQuery)
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


   bool department::is_url(const ::string & strCandidateParam)
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


   ::payload & department::var_set(::payload & varUrl, const ::string & strKeyParam, ::payload payload)
   {

      return varUrl = set_key(varUrl, strKeyParam, payload);

   }


   property & department::property_set(property & propUrl, const ::string & strKeyParam, ::payload payload)
   {

      propUrl = set_key(propUrl, strKeyParam, payload);

      return propUrl;

   }


   string department::string_set(string & strUrl, const ::string & strKeyParam, ::payload payload)
   {

      return strUrl = set_key(strUrl, strKeyParam, payload);

   }


   string department::string_set_if_not_empty(string& strUrl, const ::string & strKey, ::payload payload)
   {

      if (payload.is_empty())
      {

         return strUrl;

      }

      return string_set(strUrl, strKey, payload);

   }


   string department::set_key(const ::string & strUrlParam, const ::string & strKeyParam, ::payload payload)
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


   void department::set_key(string & strUrl, const ::string & strUrlParam, const ::string & strKeyParam, ::payload payload)
   {

      strUrl = strUrlParam;

      strsize iPos = strUrl.find('?');

      if (iPos < 0)
      {

         iPos = strUrl.get_length();

      }

      strUrl = strUrl.Left(iPos) + "?" + query_set(strUrl.Mid(iPos + 1), strKeyParam, payload);

   }


   void department::set_param(string & strUrlParam, const ::string & strKeyParam, const ::string & strParam)
   {

      string strUrl(strUrlParam);

      set_param(strUrlParam, strUrl, strKeyParam, strParam);

   }


   void department::set_param(string & strUrl, const ::string & strUrlParam, const ::string & strKeyParam, const ::string & strParam)
   {

      const char * pszQuery = strchr(strUrlParam, '?');

      string strKey = url_encode(strKeyParam);
      string strValue = url_encode(strParam);

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

   ::payload & department::var_erase(::payload & varUrl, const ::string & strKeyParam)
   {

      return varUrl = erase_key(varUrl, strKeyParam);

   }

   property & department::property_erase(property & propUrl, const ::string & strKeyParam)
   {

      propUrl = erase_key(propUrl, strKeyParam);

      return propUrl;

   }

   string department::string_erase(string & strUrl, const ::string & strKeyParam)
   {

      return strUrl = erase_key(strUrl, strKeyParam);

   }

   string department::erase_key(const ::string & strUrlParam, const ::string & strKeyParam)
   {

      string strUrl(strUrlParam);

      strsize iPos = strUrl.find("?");

      if(iPos < 0)
         return strUrl;

      return strUrl.Left(iPos) + ::str().has_char(query_erase(strUrl.Mid(iPos + 1), strKeyParam), "?");

   }

   ::payload department::get_var(const ::string & strUrlParam, const ::string & strKeyParam)
   {

      string strUrl(strUrlParam);

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return payload(::e_type_empty);
      else
         return query_get_var(strUrl.Mid(iPos + 1), strKeyParam);

   }

   string department::get_param(const ::string & strUrlParam, const ::string & strKeyParam)
   {

      string strUrl(strUrlParam);

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return payload(::e_type_empty);
      else
         return url_decode(query_get_param(strUrl.Mid(iPos + 1), strKeyParam));

   }

   bool department::get_param(string & strValue, const ::string & strUrl, const ::string & strKey)
   {

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return false;
      else
         return query_get_param(strValue, strUrl.Mid(iPos + 1), strKey);

   }

   bool department::has_param(const ::string & strUrl, const ::string & strKey)
   {

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return false;
      else
         return query_has_param(strUrl.Mid(iPos + 1), strKey);

   }

   bool department::param_has_char(const ::string & strUrl, const ::string & strKey)
   {

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return false;
      else
         return query_param_has_char(strUrl.Mid(iPos + 1), strKey);
   }


   bool department::has_param_replace(string & strUrl, const ::string & strKeyParam, const ::string & strValueParam)
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


   string department::query_set(const ::string & strQueryParam, const ::string & strKeyParam, ::payload payload)
   {

      string strQuery(strQueryParam);

      string strKey(url_encode(strKeyParam));

      string strKeyEqual = strKey + "=";

      string strAndKeyEqual = "&" + strKeyEqual;

      string strKey2(url_encode(strKeyParam));

      string strKeyEqual2 = strKey + "=";

      string strAndKeyEqual2 = "&" + strKeyEqual;

      string strValue = url_encode(payload.string());

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


   string department::query_set_param(const ::string & strQueryParam, const ::string & strKeyParam, const ::string & strParam)
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


   string department::query_erase(const ::string & strQueryParam, const ::string & strKeyParam)
   {

      ::property_set set;

      set.parse_network_arguments(strQueryParam);

      set.erase_by_name(strKeyParam);

      string str;

      set.get_network_arguments(str);

      return str;

   }


   string department::__query_erase(const ::string & strQueryParam, const ::string & strAndKeyEqual)
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


   string department::query_erase(const ::string & strQueryParam, string_array & straKey)
   {

      ::property_set set;

      set.parse_network_arguments(strQueryParam);

      set.erase_by_name(straKey);

      string str;

      set.get_network_arguments(str);

      return str;

   }


   ::payload department::query_get_var(const ::string & strQueryParam, const ::string & strKeyParam)
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


   string department::query_get_param(const ::string & strQuery, const ::string & strKey)
   {

      string strValue;

      if(!query_get_param(strValue, strQuery, strKey))
      {
         
         return "";
         
      }

      return strValue;

   }


   bool department::query_get_param(string & strValue, const ::string & strQuery, const ::string & strKey)
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


   bool department::query_has_param(const ::string & strQuery, const ::string & strKey)
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


   bool department::query_param_has_char(const ::string & strQuery, const ::string & strKey)
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


   bool department::query_has_param_replace(string & strQuery, const ::string & strKey, const ::string & strValue)
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


   bool department::locale_is_eu(const ::atom & idLocale)
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

   bool department::locale_is_asia(const ::atom & idLocale)
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

   bool department::locale_is_middle_east(const ::atom & idLocale)
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



   bool department::locale_is_south_america(const ::atom & idLocale)
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

   bool department::locale_is_oceania(const ::atom & idLocale)
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


   bool department::locale_is_africa(const ::atom & idLocale)
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

   bool department::locale_is_latin_america(const ::atom & idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == "mx")
      {
         return true;
      }

      return locale_is_caribe(idLocale) || locale_is_central_america(idLocale) || locale_is_south_america(idLocale);

   }

   bool department::locale_is_north_america(const ::atom & idLocale)
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

   bool department::locale_is_caribe(const ::atom & idLocale)
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


   bool department::locale_is_central_america(const ::atom & idLocale)
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

   bool department::locale_is_america(const ::atom & idLocale)
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


   bool department::server_ends(string strUrl, string strRoot)
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



   string department::set_script(const ::string & strUrl, const ::string & strScript)
   {

      return get_protocol(strUrl) + "://" + get_root(strUrl) + string(strScript) + ::str().has_char(get_query(strUrl), "?");

   }


   string department::override_if_empty(const ::string & strDst, const ::string & strSrc, bool bOverrideQuery)
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


   string department::override_if_set_at_source(const ::string & strDst, const ::string & strSrc)
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


   string department::to_punycode(const ::string & str)
   {

      return ::idn_to_punycode(str);

   }

   string department::from_punycode(const ::string & str)
   {

      return ::idn_from_punycode(str);

   }


   inline bool ansi_char_is_alnum(i32 i)
   {

      return (i >= '0' && i <= '9') || (i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z');

   }


   bool department::is_valid_public_domain(const string& strDomain)
   {

      critical_section_lock lock(&m_csPublicDomainExtension);

      if (m_straPublicDomainExtension.is_empty())
      {

         acmesystem()->get_public_internet_domain_extension_list(m_straPublicDomainExtension);

      }

      bool bPublicDomainExtensionListSuffixesDomain = m_straPublicDomainExtension.suffix_find_first_ci(strDomain) >= 0;

      return bPublicDomainExtensionListSuffixesDomain;

   }


   string department::os_fs(string strUrl, bool bPath)
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


   string department::os_fspath(string strUrl)
   {

      return os_fs(strUrl, true);

   }


   string department::os_fsname(string strUrl)
   {

      return os_fs(strUrl, false);

   }


} // namespace url



