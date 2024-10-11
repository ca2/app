// Created by camilo on 2024-08-29 12:18 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "url_context.h"
#include "acme/prototype/string/_str.h"


namespace url
{

   
   url_context::url_context()
   {


   }


   url_context::~url_context()
   {


   }


   void path_set_href(::string& strPath, const ::scoped_string& scopedstrHref)
   {

      if (scopedstrHref.begins("/"))
      {

         strPath = scopedstrHref;

      }
      else if (strPath.ends("/"))
      {

         strPath += scopedstrHref;

      }
      else
      {

         strPath = file_path_folder(strPath) + "/" + scopedstrHref;

      }

   }


   ::string parameter_set(const ::scoped_string& scopedstrUrl, const ::scoped_string& scopedstrKey, const ::scoped_string& scopedstr)
   {

      ::url::parts url(scopedstrUrl);

      if (!url.m_requestpart.m_psetArguments)
      {

         url.m_requestpart.m_psetArguments = __allocate ::property_set ();

      }

      url.arguments()[scopedstrKey] = scopedstr;

      ::string strUrl = url.as_string();

      return strUrl;

   }

   
   void erase_parameter(::string& str, const ::scoped_string& scopedstrKey)
   {

      str = parameter_erased(str, scopedstrKey);

   }
   
   
   void set_parameter(::string& str, const ::scoped_string& scopedstrKey, const ::scoped_string& scopedstr)
   {

      str = parameter_set(str, scopedstrKey, scopedstr);

   }


   ::string path_join_query(const ::scoped_string& scopedstrPath, const ::scoped_string& scopedstrQuery)
   {

      if (scopedstrQuery.is_empty())
      {

         return scopedstrPath;

      }

      return scopedstrPath + "?" + scopedstrQuery;

   }


   string __parameter_erased(const ::scoped_string& scopedstr, strsize iStartParam, const ::scoped_string& scopedstrKey)
   {

      auto iStart = iStartParam;

      string str(scopedstr);

      while (true)
      {

         auto iFind = str.find_index(scopedstrKey, iStart);

         if (not_found(iFind))
         {

            break;

         }

         if (iFind > 0 && str[iFind - 1] != '&')
         {

            iStart++;

            continue;

         }

         if (str[iFind + scopedstrKey.size()] == '&')
         {

            str = str(0, iFind) + str(iFind + scopedstrKey.size() + 1);

            continue;

         }

         if (str[iFind + scopedstrKey.size()] != '=')
         {

            iStart++;

            continue;

         }

         auto iNextParam = str.find_index("&", iFind + 1);

         if (not_found(iNextParam))
         {

            str = str(0, maximum(iFind - 1, iStartParam));

            break;

         }

         str = str(0, iFind) + str(iNextParam + 1);

      }

      return str;

   }


   bool __get_parameter(::string& strParameter, const ::scoped_string& scopedstr, ::strsize iStartParam, const ::scoped_string& scopedstrKey)
   {

      if (scopedstrKey.size() > scopedstr.size())
      {

         return false;

      }

      //if(ansi_count_compare(scopedstrQuery, scopedstKey, scopedstKey.size()) == 0)
      //{
      //   
      //   if(iCmp == 0)
      //   {
      //      
      //      strParameter = "";
      //      
      //      return true;
      //      
      //   }
      //   else if(scopedstrQuery[scopedstKey.size()] == '=')
      //   {
      //      
      //      auto pFind2 = strParameter(scopedstKey.size() + 1).find('&');
      //      
      //      if(pFind2 > scopedstKey.begin())
      //      {
      //         
      //         strParameter = scopedstrQuery(scopedstKey.size() + 1, pFind2);
      //         
      //      }
      //      else
      //      {
      //         
      //         strParameter = scopedstrQuery.substr(size.length() + 1);
      //         
      //      }
      //      
      //      return true;
      //      
      //   }

      //}

      ::strsize iStart = iStartParam;

      ::strsize iFind;

      while (found(iFind = scopedstr.find_index(scopedstrKey, iStart)))
      {

         if (iFind == iStartParam || scopedstr[iFind - 1] == '&')
         {

            if ((iFind + scopedstrKey.size()) == scopedstr.size()
               || scopedstr[iFind + scopedstrKey.size()] == '&')
            {

               strParameter = "";

               return true;

            }
            else if (scopedstr[iFind + scopedstrKey.size()] == '=')
            {

               auto iFind2 = scopedstr.find_index('&', iFind + scopedstrKey.size() + 1);

               if (found(iFind2))
               {

                  strParameter = scopedstr(iFind + scopedstrKey.size() + 1, iFind2 - (iFind + scopedstrKey.size() + 1));

               }
               else
               {

                  strParameter = scopedstr(iFind + scopedstrKey.size() + 1);

               }

               return true;

            }

         }

         iStart = iFind + scopedstrKey.size() + 1;

      }

      return false;

   }


   bool __has_parameter_replace(::string& str, const ::scoped_string& scopedstr, ::strsize iStartParam, const ::scoped_string& scopedstrKey, const ::scoped_string& scopedstrParameter)
   {

      if (scopedstrKey.size() > scopedstr.size())
      {

         return false;

      }

      //if(ansi_count_compare(scopedstrQuery, scopedstKey, scopedstKey.size()) == 0)
      //{
      //   
      //   if(iCmp == 0)
      //   {
      //      
      //      strParameter = "";
      //      
      //      return true;
      //      
      //   }
      //   else if(scopedstrQuery[scopedstKey.size()] == '=')
      //   {
      //      
      //      auto pFind2 = strParameter(scopedstKey.size() + 1).find('&');
      //      
      //      if(pFind2 > scopedstKey.begin())
      //      {
      //         
      //         strParameter = scopedstrQuery(scopedstKey.size() + 1, pFind2);
      //         
      //      }
      //      else
      //      {
      //         
      //         strParameter = scopedstrQuery.substr(size.length() + 1);
      //         
      //      }
      //      
      //      return true;
      //      
      //   }

      //}

      auto iStart = iStartParam;

      ::strsize iFind;

      while (found(iFind = scopedstr.find_index(scopedstrKey, iStart)))
      {

         if (iFind == iStartParam || scopedstr[iFind - 1] == '&')
         {

            if ((iFind + scopedstrKey.size()) == scopedstr.size())
            {

               str = scopedstr(0, iFind + scopedstrKey.size()) + "=" + scopedstrParameter;

               return true;

            }
            else if (scopedstr[iFind + scopedstrKey.size()] == '&')
            {

               str = scopedstr(0, iFind + scopedstrKey.size()) + "=" + scopedstrParameter + scopedstr(iFind + scopedstrKey.size());

               return true;

            }
            else if (scopedstr[iFind + scopedstrKey.size()] == '=')
            {

               auto iFind2 = scopedstr.find_index('&', iFind + scopedstrKey.size() + 1);

               if (found(iFind2))
               {

                  str = scopedstr(0, iFind + scopedstrKey.size() + 1) + scopedstrParameter + scopedstr(iFind2);

               }
               else
               {

                  str = scopedstr(0, iFind + scopedstrKey.size() + 1) + scopedstrParameter;

               }

               return true;

            }

         }

         iStart = iFind + scopedstrKey.size() + 1;

      }

      return false;

   }


   ::string parameter_erased(const ::scoped_string& scopedstr, const ::scoped_string& scopedstrKey)
   {

      strsize iStart = scopedstr.find_index('?');

      if (iStart < 0)
      {

         iStart = 0;

      }

      return __parameter_erased(scopedstr, iStart, scopedstrKey);


   }


   ::string get_request_path(const ::scoped_string& scopedstr)
   {

      return ::url::decode(get_raw_request_path(scopedstr));

   }

   
   ::string set_request_path(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrScript)
   {

      return get_protocol(scopedstrUrl) + "://" + get_root(scopedstrUrl) + ::url::encode_path(scopedstrScript) + ::str::has_char(get_query(scopedstrUrl), "?");

   }


   ::string get_protocol(const ::scoped_string & scopedstr)
   {

      auto p = scopedstr.find(":");

      if(::is_null(p))
      {

         return {};

      }

      return scopedstr(0, p);

   }


   ::string get_raw_request_path(const ::scoped_string& scopedstr)
   {

      string str(scopedstr);

      auto p = str.find(":");

      if (not_found(p))
      {

         return ::string(str(p + 1)).get_word("?");

      }

      p++;

      if (*p != '/')
      {

         return ::string(str(p)).get_word("?");

      }

      p++;

      if (*p == '/')
      {

         p++;

      }

      auto start = p;

      auto path = str(start).find("/");

      auto query = str(start).find("?");

      if (found(path))
      {

         if (found(query))
         {

            if (query < path)
            {

               // https://website.com?object/param

               return {};

            }

            // https://website.com/object?param

            return { path, query };

         }

         // https://website.com/object

         return { path, str.m_end };

      }
      //else
      //{

      //   if (found(query))
      //   {

      //      // https://website.com?object

      //   }
      //   else
      //   {

      //      // https://website.com

      //   }


      //}

      return {};

   }


   string get_root(const ::scoped_string& scopedstr)
   {

      string str(scopedstr);

      auto p = str.find(":");

      if (not_found(p))
      {

         return {};

      }

      p++;

      if (*p != '/')
      {

         return {};

      }

      p++;

      if (*p == '/')
      {

         p++;

      }

      auto start = p;

      auto end = str(start).find("/");

      auto query = str(start).find("?");

      end = minimum_non_null(end, query);

      if (not_found(end))
      {

         return str(start);

      }

      return { start, end };

   }


   ::string get_query(const ::scoped_string& scopedstr)
   {

      string str(scopedstr);

      auto query = str.find('?');

      if (not_found(query))
      {

         return {};

      }

      return str(query + 1);

   }


   ::string get_object(const ::scoped_string & scopedstr)
   {

      auto p1 = scopedstr.find("://");

      auto p2 = scopedstr.find(":/");

      string::const_iterator p;

      if(not_found(p1))
      {

         if (not_found(p2))
         {

            return scopedstr;

         }
         else
         {

            p = p2 + 2;

         }

      }
      else if(not_found(p2))
      {

         p = p1 + 3;

      }
      else if(p1 <= p2)
      {

         p = p1 + 3;

      }
      else
      {

         p = p2 + 2;         

      }

      auto object = scopedstr(p).find("/");

      if (not_found(object))
      {

         return "";

      }
      else
      {

         return scopedstr(object);

      }

   }




   ::string get_host(const ::scoped_string& scopedstr)
   {

      auto root = get_root(scopedstr);

      auto p = root.find(":");

      if (not_found(p))
      {

         return root;

      }

      return root(0, p);

   }


   bool has_parameter_replace(::string& str, const ::scoped_string& scopedstr, const ::scoped_string& scopedstrKey, const ::scoped_string& scopedstrParameter)
   {

      strsize iStart = scopedstr.find_index('?');

      if (iStart < 0)
      {

         iStart = 0;

      }

      return __has_parameter_replace(str, scopedstr, iStart, scopedstrKey, scopedstrParameter);

   }


   bool get_parameter(::string& strParameter, const ::scoped_string& scopedstr, const ::scoped_string& scopedstrKey)
   {

      strsize iStart = scopedstr.find_index('?');

      if (iStart < 0)
      {

         iStart = 0;

      }
      else
      {

         iStart++;

      }

      return __get_parameter(strParameter, scopedstr, iStart, scopedstrKey);

   }


   ::string get_parameter(const ::scoped_string& scopedstr, const ::scoped_string& scopedstrKey)
   {

      string strValue;

      if (!get_parameter(strValue, scopedstr, scopedstrKey))
      {

         return "";

      }

      return strValue;


   }


   ::string has_parameter_replace(const ::scoped_string& scopedstr, const ::scoped_string& scopedstrKey, const ::scoped_string& scopedstrParameter)
   {

      string strValue;

      if (!has_parameter_replace(strValue, scopedstr, scopedstrKey, scopedstrParameter))
      {

         return "";

      }

      return strValue;

   }


   //string url::protocol(const ::string & strParam)
   //{

   //   string str(strParam);

   //   auto pPos = str.find(":");

   //   if(::is_null(pPos))
   //   {

   //      return "";

   //   }

   //   return str(0, pPos);

   //}


   //string url::get_root(const ::string & strParam)
   //{

   //   string str(strParam);

   //   auto pPos = str.find(":");
   //   if (::is_null(pPos))
   //      return strParam;
   //   pPos++;
   //   while (pPos < str.end() && *pPos == '/')
   //   {
   //      pPos++;
   //   }
   //   auto pStart = pPos;
   //   auto pEnd = str(pStart).find("/");
   //   auto pArgumentsStart = str(pStart).find("?");

   //   if (::is_null(pEnd))
   //   {

   //      if (::is_set(pArgumentsStart))
   //      {

   //         return {};

   //      }

   //      pEnd = str.end();

   //   }
   //   else if (::is_set(pArgumentsStart) && pEnd > pArgumentsStart)
   //   {

   //      return {};

   //   }

   //   return { pStart, pEnd };

   //}


   //string url::get_server(const ::string & strParam)
   //{

   //   string strRoot = get_root(strParam);

   //   auto pPos = strRoot.find(":");

   //   if (::is_null(pPos))
   //   {

   //      return strRoot;

   //   }

   //   return strRoot.left(pPos);

   //}


   //i32 url::get_port(const ::string & strParam, i32 iDefault)
   //{

   //   string strRoot = get_root(strParam);

   //   auto pPos = strRoot.find(":");

   //   if(not_found(pPos))
   //   {

   //      if(iDefault == -1)
   //      {

   //         string strProtocol = get_protocol(strParam);

   //         if (strProtocol == "http")
   //         {

   //            return 80;

   //         }
   //         else if (strProtocol == "https")
   //         {

   //            return 443;

   //         }
   //         else if (strProtocol == "ftp")
   //         {

   //            return 21;

   //         }

   //      }

   //      return iDefault;

   //   }

   //   return atoi(strRoot.substr(pPos + 1));

   //}


   //string url::get_object(const ::string & strParam)
   //{

   //   string str(strParam);

   //   auto pPos1 = str.find("://");

   //   auto pPos2 = str.find(":/");

   //   string::const_iterator pPos;

   //   if(not_found(pPos1))
   //   {

   //      if (::not_found(pPos2))
   //      {

   //         return strParam;

   //      }
   //      else
   //      {

   //         pPos = pPos2 + 2;

   //      }

   //   }
   //   else if(not_found(pPos2))
   //   {

   //      pPos = pPos1 + 3;

   //   }
   //   else if(pPos1 <= pPos2)
   //   {

   //      pPos = pPos1 + 3;

   //   }
   //   else
   //   {

   //      pPos = pPos2 + 2;         

   //   }

   //   auto pStart = str(pPos).find("/");

   //   if (not_found(pStart))
   //   {

   //      return "/";

   //   }
   //   else
   //   {

   //      return str.substr(pStart);

   //   }

   //}


   //string url::object_get_script(const ::string & strParam) // page
   //{

   //   string str(strParam);

   //   auto pFind = str.find('?');

   //   if (::is_null(pFind))
   //   {

   //      return ::url::decode(str);

   //   }
   //   else
   //   {

   //      return ::url::decode(str(0, pFind));

   //   }

   //}


   //string url::object_get_query(const ::string & strParam) // id=1
   //{

   //   string str(strParam);

   //   auto pFind = str.find('?');

   //   if (::is_null(pFind))
   //   {

   //      return "";

   //   }
   //   else
   //   {

   //      return str(pFind + 1);

   //   }

   //}


   //string url::object_set(const ::string & strObject, const ::string & strKeyParam, ::payload payload)
   //{

   //   string strQuery = object_get_query(strObject);

   //   return object_get_script(strObject) + ::str::has_char(__query_set(strQuery, strKeyParam, payload), "?");

   //}


   //string url::get_script(const ::string & strParam) // page
   //{

   //   return object_get_script(get_object(strParam));

   //}


   //string url::get_query(const ::string & strParam) // id=1
   //{

   //   return object_get_query(get_object(strParam));

   //}

//
//   string url::object(const ::string & strScriptParam, const ::string & strQueryParam)
//   {
//
//      string strScript(strScriptParam);
//
//      string strQuery(strQueryParam);
//
//      if (strQuery.has_char())
//      {
//
//         return strScript + "?" + strQuery;
//
//      }
//      else
//      {
//
//         return strScript;
//
//      }
//
//   }
//
//
//   string url::path(const ::string & str1Param, const ::string & str2Param)
//   {
//
//      if (str2Param.is_empty())
//      {
//
//         return str1Param;
//
//      }
//
//      string str1(str1Param);
//
//      string str2(str2Param);
//
//      if (str1.right(1) == "/")
//      {
//
//         str1 = str1.left(str1.length() - 1);
//
//      }
//
//      if (str2.left(1) == "/")
//      {
//
//         str2 = str2.right(str2.length() - 1);
//
//      }
//
//      return str1 + "/" + str2;
//
//   }
//
//
//   string url::path(const ::string & str1, const ::string & str2, const ::string & str3)
//   {
//
//      return path(path(str1, str2), str3);
//
//   }
//
//
//   string url::name(const ::string & strParam)
//   {
//
//      string str(strParam);
//
//      auto pQueryStart = str.find('?');
//
//      if (not_found(pQueryStart))
//      {
//
//         pQueryStart = str.end();
//
//      }
//
//      str = str.left(pQueryStart);
//
//      auto pLastSlash = str.rear_find('/');
//
//      if (not_found(pLastSlash))
//      {
//         
//         return "";
//
//      }
//
//      return str.left(pLastSlash);
//
//   }
//
//
//   //string url::url::encode(const ::string & strParam)
//   //{
//
//   //   return ::url::encode(strParam);
//
//   //}
//
//
//   //string url::url::decode(const ::string & strParam)
//   //{
//
//   //   return ::url::decode(strParam);
//
//   //}
//
//
//   //string url::url::decode(const ::string & strUrl, strsize iLen)
//   //{
//
//   //   return ::url::decode(strUrl,iLen);
//
//   //}
//
//
//   string url::query_append(const ::string & strUrlParam, const ::string & strQuery)
//   {
//
//      string strUrl(strUrlParam);
//
//      auto pStart = strUrl.find("://");
//
//      if(pStart > strUrl.begin())
//      {
//
//         pStart = strUrl(pStart + 4).find("/");
//
//         if(not_found(pStart))
//         {
//
////xxx            informationf("invalid url %s", pszUrl);
//
//            pStart = strUrl.begin();
//
//         }
//
//      }
//      else
//      {
//
//         pStart = strUrl.begin();
//
//      }
//
//      if(strUrl(pStart).find("?") > strUrl.begin())
//      {
//
//         return strUrl + "&" + strQuery;
//
//      }
//      else
//      {
//
//         return strUrl + "?" + strQuery;
//
//      }
//
//   }
//
//
//   bool url::is_url(const ::string & strCandidateParam)
//   {
//
//      string strCandidate(strCandidateParam);
//
//      strsize iLen = strCandidate.length();
//
//      strsize i = 0;
//
//      char ch;
//
//      while(i < iLen)
//      {
//
//         ch = strCandidate[i];
//
//         if(__ansicharisalpha((uchar) ch))
//            i++;
//         else if(ch == '.')
//            i++;
//         else if(ch == ':' && (((i + 1) == iLen) ||
//                               (iLen > (i + 3)
//                                && strCandidate[i + 1] == '/'
//                                && strCandidate[i + 2] == '/')))
//            return true;
//         else
//            return false;
//
//      }
//
//      return false;
//
//   }
//
//
//   //::payload & url::var_set(::payload & payloadUrl, const ::string & strKeyParam, ::payload payload)
//   //{
//
//   //   return payloadUrl = set_key(payloadUrl.as_string(), strKeyParam, payload);
//
//   //}
//
//
//   //property & url::property_set(property & propUrl, const ::string & strKeyParam, ::payload payload)
//   //{
//
//   //   propUrl = set_key(propUrl.as_string(), strKeyParam, payload);
//
//   //   return propUrl;
//
//   //}
//
//
//   //string url::string_set(string & strUrl, const ::string & strKeyParam, ::payload payload)
//   //{
//
//   //   return strUrl = set_key(strUrl, strKeyParam, payload);
//
//   //}
//
//
//   //string url::parameters_set_if_empty_at_target(string& strUrl, const ::string & strKey, ::payload payload)
//   //{
//
//   //   if (payload.is_empty())
//   //   {
//
//   //      return strUrl;
//
//   //   }
//
//   //   return string_set(strUrl, strKey, payload);
//
//   //}
//
//
//   string url::parameter_set(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrPayload)
//   {
//
//      part part(scopedstr);
//
//      switch (part.e_type_query)
//      {
//      case part::e_type_query:
//
//         return __query_set(scopedstr, scopedstrKey, scopedstrPayload);
//
//      case part::e_type_strict_object_with_query:
//      {
//
//         ::string str(scopedstr.m_begin, part.m_pszLastQuestionMarkAfterLastSlash);
//
//         return  str + "?" + __query_set(
//            { part.m_pszLastQuestionMarkAfterLastSlash,
//            scopedstr.m_end },
//            scopedstrKey,
//            scopedstrPayload);
//
//      }
//      case part::e_type_strict_object_no_query:
//      {
//
//         ::string str(scopedstr.m_begin, part.m_pszLastQuestionMarkAfterLastSlash);
//
//         ::string strQuery(::url::encode(scopedstrKey));
//
//         if (scopedstrPayload.has_char())
//         {
//
//            strQuery += "=" + ::url::encode(scopedstrPayload);
//
//         }
//
//         return str + "?" + strQuery;
//
//      }
//      default:
//      {
//
//         ::string strStrictFolder(scopedstr.m_begin, part.m_pszLastSlash);
//
//         ::string str(part.m_pszLastSlash + 1, part.m_pszLastQuestionMarkAfterLastSlash);
//
//         return  strStrictFolder + "/" + str + "?" + __query_set(
//            { part.m_pszLastQuestionMarkAfterLastSlash,
//            scopedstr.m_end },
//            scopedstrKey,
//            scopedstrPayload);
//
//      }
//
//      };
//
//   }
//
//
//   //void url::set_key(string & strUrl, const ::string & strUrlParam, const ::string & strKeyParam, ::payload payload)
//   //{
//
//   //   strUrl = strUrlParam;
//
//   //   auto pPos = strUrl.find('?');
//
//   //   if (not_found(pPos))
//   //   {
//
//   //      pPos = strUrl.end();
//
//   //   }
//
//   //   strUrl = strUrl.left(pPos) + "?" + query_set(strUrl.substr(pPos + 1), strKeyParam, payload);
//
//   //}
//
//
//  /* void url::set_param(string & strUrlParam, const ::string & strKeyParam, const ::string & strParam)
//   {
//
//      string strUrl(strUrlParam);
//
//      set_param(strUrlParam, strUrl, strKeyParam, strParam);
//
//   }*/
//
////
////   void url::set_param(string & strUrl, const ::string & strUrlParam, const ::string & strKeyParam, const ::string & strParam)
////   {
////
////      auto pszQuery = strUrlParam.find('?');
////
////      string strKey = ::url::encode(strKeyParam);
////      string strValue = ::url::encode(strParam);
////
////      strsize iLenUrl = ansi_len(strUrlParam);
////      strsize iLenKey = strKey.length();
////
////      string str;
////
////      char * psz = str.get_buffer(iLenUrl + iLenKey + strValue.length() + 2);
////
////      if(pszQuery == nullptr)
////      {
////         ansi_cpy(psz, strUrlParam);
////         psz[iLenUrl] = '?';
////         ansi_cpy(&psz[iLenUrl + 1], strKey);
////         psz[iLenUrl + 1 + iLenKey] = '=';
////         ansi_cpy(&psz[iLenUrl + 1 + iLenKey + 1], strValue);
////         str.release_buffer(iLenUrl + iLenKey + strValue.length() + 2);
////      }
////      else
////      {
////         strsize iFinalLen = pszQuery - strUrlParam;
//////         i32 pPos = 0;
////         ansi_count_copy(psz, strUrlParam, iFinalLen);
////         psz[iFinalLen] = '?';
////         iFinalLen++;
////         pszQuery++;
////         bool bRemove = false;
////         bool bAlreadyInsertedFirstParam = false;
////         const ::ansi_character * pszQueryEnd;
////         bool bInserted = false;
////         while(true)
////         {
////            pszQueryEnd = ansi_chr(pszQuery + 1, '&');
////            if(ansi_count_compare(pszQuery, strKeyParam, iLenKey) == 0 && pszQuery[iLenKey] == '=')
////            {
////               if(!bRemove)
////               {
////                  if(bAlreadyInsertedFirstParam)
////                  {
////                     psz[iFinalLen] = '&';
////                     iFinalLen++;
////                  }
////                  ansi_count_copy(&psz[iFinalLen], strKey, iLenKey);
////                  iFinalLen += iLenKey;
////                  psz[iFinalLen] = '=';
////                  iFinalLen++;
////                  ansi_count_copy(&psz[iFinalLen], strValue, strValue.length());
////                  iFinalLen += strValue.length();
////                  bRemove = true;
////                  bAlreadyInsertedFirstParam = true;
////                  bInserted = true;
////               }
////            }
////            else
////            {
////               if(bAlreadyInsertedFirstParam)
////               {
////                  psz[iFinalLen] = '&';
////                  iFinalLen++;
////               }
////               if(pszQueryEnd == nullptr)
////               {
////                  ansi_count_copy(&psz[iFinalLen], pszQuery, iLenUrl - (pszQuery - strUrlParam));
////                  iFinalLen += iLenUrl - (pszQuery - strUrlParam);
////                  bAlreadyInsertedFirstParam = true;
////                  break;
////               }
////               else
////               {
////                  ansi_count_copy(&psz[iFinalLen], pszQuery, pszQueryEnd - pszQuery);
////                  iFinalLen += pszQueryEnd - pszQuery;
////                  bAlreadyInsertedFirstParam = true;
////               }
////            }
////            pszQuery = pszQueryEnd;
////            if(pszQuery == nullptr)
////               break;
////            pszQuery++;
////         }
////         if(!bInserted)
////         {
////            if(bAlreadyInsertedFirstParam)
////            {
////               psz[iFinalLen] = '&';
////               iFinalLen++;
////            }
////            ansi_count_copy(&psz[iFinalLen], strKey, iLenKey);
////            iFinalLen += iLenKey;
////            psz[iFinalLen] = '=';
////            iFinalLen++;
////            ansi_count_copy(&psz[iFinalLen], strValue, strValue.length());
////            iFinalLen += strValue.length();
////            bRemove = true;
////            bAlreadyInsertedFirstParam = true;
////            bInserted = true;
////         }
////
////         str.release_buffer(iFinalLen);
////
////      }
////
////      strUrl = str;
////
////
////   }
//
//
//   //::payload & url::erase_key(::payload & payloadUrl, const ::string & strKeyParam)
//   //{
//
//   //   return payloadUrl = erased_key(payloadUrl.as_string(), strKeyParam);
//
//   //}
//
//
//   //property & url::erase_key(property & propUrl, const ::string & strKeyParam)
//   //{
//
//   //   propUrl = erase_key((::payload &) propUrl, strKeyParam);
//
//   //   return propUrl;
//
//   //}
//
//
//   //string & url::erase_key(string & strUrl, const ::string & strKeyParam)
//   //{
//
//   //   return strUrl = erased_key(strUrl, strKeyParam);
//
//   //}
//
//
//   string url::parameter_erased(const ::string & strUrlParam, const ::string & strKeyParam)
//   {
//
//      string strUrl(strUrlParam);
//
//      auto pPos = strUrl.find("?");
//
//      if(not_found(pPos))
//         return strUrl;
//
//      return strUrl.left(pPos) + ::str::has_char(query_erase(strUrl.substr(pPos + 1), strKeyParam), "?");
//
//   }
//
//
//   //::string url::erased_key(const ::string & strUrlParam, const ::string & strKeyParam)
//   //{
//
//   //   string strUrl(strUrlParam);
//
//   //   auto pPos = strUrl.find('?');
//
//   //   if(not_found(pPos))
//   //      return ::payload(::e_type_empty);
//   //   else
//   //      return query_get_var(strUrl.substr(pPos + 1), strKeyParam);
//
//   //}
//
//
//   ::payload url::get_parameter(const ::string & strUrlParam, const ::string & strKeyParam)
//   {
//
//      string strUrl(strUrlParam);
//
//      auto pPos = strUrl.find('?');
//
//      if (not_found(pPos))
//      {
//
//         return false;
//
//      }
//
//      return ::url::decode(query_get_parameter(strUrl.substr(pPos + 1), strKeyParam));
//
//   }
//
//
//   bool url::get_parameter(string & strValue, const ::string & strUrl, const ::string & strKey)
//   {
//
//      auto pPos = strUrl.find('?');
//
//      if(not_found(pPos))
//         return false;
//      else
//         return query_get_param(strValue, strUrl.substr(pPos + 1), strKey);
//
//   }
//
//   bool url::has_param(const ::string & strUrl, const ::string & strKey)
//   {
//
//      auto pPos = strUrl.find('?');
//
//      if(not_found(pPos))
//         return false;
//      else
//         return query_has_param(strUrl.substr(pPos + 1), strKey);
//
//   }
//
//   bool url::param_has_char(const ::string & strUrl, const ::string & strKey)
//   {
//
//      auto pPos = strUrl.find('?');
//
//      if(not_found(pPos))
//         return false;
//      else
//         return query_param_has_char(strUrl.substr(pPos + 1), strKey);
//   }
//
//
//   bool url::has_param_replace(string & strUrl, const ::string & strKeyParam, const ::string & strValueParam)
//   {
//
//      auto pPos = strUrl.find('?');
//
//      if(not_found(pPos))
//         return false;
//      else
//      {
//
//         string strQuery = strUrl.substr(pPos + 1);
//
//         if(!query_has_param_replace(strQuery, strKeyParam, strValueParam))
//            return false;
//
//         strUrl = strUrl.left(pPos + 1) + strQuery;
//
//         return true;
//
//      }
//
//   }
//
//
//   string url::query_set(const ::string & strQueryParam, const ::string & strKeyParam, ::payload payload)
//   {
//
//      string strQuery(strQueryParam);
//
//      string strKey(::url::encode(strKeyParam));
//
//      string strKeyEqual = strKey + "=";
//
//      string strAndKeyEqual = "&" + strKeyEqual;
//
//      string strKey2(::url::encode(strKeyParam));
//
//      string strKeyEqual2 = strKey + "=";
//
//      string strAndKeyEqual2 = "&" + strKeyEqual;
//
//      string strValue = ::url::encode(payload);
//
//      if(string_begins(strQuery, strKeyEqual))
//      {
//         auto pPos = strQuery.find("&");
//         if(not_found(pPos))
//         {
//            strQuery = strKeyEqual2 + strValue;
//         }
//         else
//         {
//            strQuery = strKeyEqual2 + strValue + __query_erase(strQuery.substr(pPos), strAndKeyEqual);
//         }
//      }
//      else if(string_begins(strQuery, strKeyEqual2))
//      {
//         auto pPos = strQuery.find("&");
//         if(not_found(pPos))
//         {
//            strQuery = strKeyEqual2 + strValue;
//         }
//         else
//         {
//            strQuery = strKeyEqual2 + strValue + __query_erase(strQuery.substr(pPos), strAndKeyEqual);
//         }
//      }
//      else
//      {
//         auto pPos = strQuery.find(strAndKeyEqual);
//         if(not_found(pPos))
//         {
//            if(strQuery.has_char())
//            {
//               strQuery += strAndKeyEqual2 + strValue;
//            }
//            else
//            {
//               strQuery = strKeyEqual2 + strValue;
//            }
//         }
//         else
//         {
//            pPos = strQuery.find(strAndKeyEqual2);
//            if(not_found(pPos))
//            {
//               if(strQuery.has_char())
//               {
//                  strQuery += strAndKeyEqual2 + strValue;
//               }
//               else
//               {
//                  strQuery = strKeyEqual2 + strValue;
//               }
//            }
//            else
//            {
//               strQuery = strQuery.left(pPos) + strAndKeyEqual2 + strValue + __query_erase(strQuery.substr(pPos), strAndKeyEqual);
//            }
//         }
//      }
//
//
//      return strQuery;
//
//   }
//
//
//   string url::query_set_param(const ::string & strQueryParam, const ::string & strKeyParam, const ::string & strParam)
//   {
//
//      string strQuery(strQueryParam);
//
//      string strKey(strKeyParam);
//
//      string strKeyEqual = strKey + "=";
//
//      string strAndKeyEqual = "&" + strKeyEqual;
//
//      if(string_begins(strQuery, strKeyEqual))
//      {
//         auto pPos = strQuery.find("&");
//         if(not_found(pPos))
//         {
//            strQuery = strKey + strParam;
//         }
//         else
//         {
//            strQuery = strKey + strParam + __query_erase(strQuery.substr(pPos), strAndKeyEqual);
//         }
//      }
//      else
//      {
//         auto pPos = strQuery.find(strAndKeyEqual);
//         if(not_found(pPos))
//         {
//            if(strQuery.has_char())
//            {
//               strQuery += strAndKeyEqual + strParam;
//            }
//            else
//            {
//               strQuery = strKeyEqual + strParam;
//            }
//         }
//         else
//         {
//            strQuery = strKey + strParam + __query_erase(strQuery.substr(pPos), strAndKeyEqual);
//         }
//      }
//
//
//      return strQuery;
//
//   }
//
//
//   string url::query_erase(const ::string & strQueryParam, const ::string & strKeyParam)
//   {
//
//      ::property_set set;
//
//      set.parse_network_arguments(strQueryParam);
//
//      set.erase_by_name(strKeyParam);
//
//      string str;
//
//      set.get_network_arguments(str);
//
//      return str;
//
//   }
//
//
//   string url::__query_erase(const ::string & strQueryParam, const ::string & strAndKeyEqual)
//   {
//
//      string strQuery(strQueryParam);
//
//      while(true)
//      {
//         
//         auto pFind = strQuery.find(strAndKeyEqual);
//         
//         if(::is_null(pFind))
//         {
//            
//            break;
//            
//         }
//         
//         auto pNextParam = strQuery(pFind+1).find("&");
//         
//         if(not_found(pNextParam))
//         {
//            
//            strQuery = strQuery(0, pFind);
//            
//         }
//         else
//         {
//            
//            strQuery = strQuery(0, pFind) + strQuery.substr(pNextParam);
//            
//         }
//         
//      }
//
//      return strQuery;
//
//   }
//
//
//   string url::query_erase(const ::string & strQueryParam, string_array & straKey)
//   {
//
//      ::property_set set;
//
//      set.parse_network_arguments(strQueryParam);
//
//      set.erase_by_name(straKey);
//
//      string str;
//
//      set.get_network_arguments(str);
//
//      return str;
//
//   }
//
//
//   ::payload url::query_get_var(const ::string & strQueryParam, const ::string & strKeyParam)
//   {
//
//      string strQuery(strQueryParam);
//
//      string strKey(strKeyParam);
//
//      string strKeyEqual = strKey + "=";
//
//      string strAndKeyEqual = "&" + strKeyEqual;
//
//      ::payload payload;
//
//      string::const_iterator pPos = strQuery.begin();
//
//      if(string_begins(strQuery, strKeyEqual))
//      {
//         
//         pPos = strQuery.find('&');
//         
//         if(not_found(pPos))
//         {
//            
//            payload = strQuery.substr(strKeyEqual.length());
//            
//            return payload;
//            
//         }
//         else
//         {
//            
//            payload = strQuery.substr(strKeyEqual.length(), pPos - strKeyEqual.length());
//            
//         }
//         
//      }
//
//      while(true)
//      {
//         
//         pPos = strQuery(pPos).find(strAndKeyEqual);
//         
//         if(not_found(pPos))
//         {
//            
//            break;
//            
//         }
//         
//         auto pEnd = strQuery(pPos + 1).find('&');
//         
//         if(not_found(pEnd))
//         {
//            
//            if(payload.is_new())
//            {
//               
//               payload = strQuery.substr(pPos + strKeyEqual.length());
//               
//            }
//            else
//            {
//               
//               payload.as_payload_array().add(strQuery.substr(pPos + strKeyEqual.length()));
//               
//            }
//            
//            return payload;
//            
//         }
//         else
//         {
//            
//            if(payload.is_new())
//            {
//               
//               payload = strQuery.substr(pPos + strKeyEqual.length(), pEnd - (pPos + strKeyEqual.length()));
//               
//            }
//            else
//            {
//               
//               payload.as_payload_array().add(strQuery.substr(pPos + strKeyEqual.length(), pEnd - (pPos + strKeyEqual.length())));
//               
//            }
//            
//         }
//         
//         pPos++;
//         
//      }
//
//      return payload;
//
//   }
//
//
//   string url::query_get_param(const ::string & strQuery, const ::string & strKey)
//   {
//
//      string strValue;
//
//      if(!query_get_param(strValue, strQuery, strKey))
//      {
//         
//         return "";
//         
//      }
//
//      return strValue;
//
//   }
//
//
//   bool url::query_get_param(string & strValue, const ::string & strQuery, const ::string & strKey)
//   {
//
//      strsize iCmp = strQuery.length() - strKey.length();
//      
//      if(iCmp < 0)
//      {
//         
//         return false;
//         
//      }
//
//      if(ansi_count_compare(strQuery, strKey, strKey.length()) == 0)
//      {
//         
//         if(iCmp == 0)
//         {
//            
//            strValue = "";
//            
//            return true;
//            
//         }
//         else if(strQuery[strKey.length()] == '=')
//         {
//            
//            auto pFind2 = strQuery(strKey.length() + 1).find('&');
//            
//            if(pFind2 > strQuery.begin())
//            {
//               
//               strValue = strQuery(strKey.length() + 1, pFind2);
//               
//            }
//            else
//            {
//               
//               strValue = strQuery.substr(strKey.length() + 1);
//               
//            }
//            
//            return true;
//            
//         }
//
//      }
//
//      ::string::const_iterator pStart = strQuery.begin() + 1;
//
//      ::string::const_iterator pFind;
//
//      while(found(pFind = strQuery(pStart).find(strKey)))
//      {
//         
//         if (*(pFind - 1) == '&')
//         {
//            
//            if(strQuery.end() == (pFind + strKey.length()))
//            {
//               
//               strValue = "";
//               
//               return true;
//               
//            }
//            else if(*(pFind + strKey.length()) == '=')
//            {
//               
//               auto pFind2 = strQuery(pFind + strKey.length() + 1).find('&');
//               
//               if(pFind2 > strQuery.begin())
//               {
//                  
//                  strValue = strQuery.substr(pFind + strKey.length() + 1, pFind2 - (pFind + strKey.length() + 1));
//                  
//               }
//               else
//               {
//                  
//                  strValue = strQuery.substr(pFind + strKey.length() + 1);
//                  
//               }
//               
//               return true;
//               
//            }
//            
//         }
//         
//         pStart = pFind + strKey.length() + 1;
//         
//      }
//
//      return false;
//
//   }
//
//
//   bool url::query_has_param(const ::string & strQuery, const ::string & strKey)
//   {
//
//      strsize iCmp = strQuery.length() - strKey.length();
//      
//      if(iCmp < 0)
//      {
//         
//         return false;
//         
//      }
//
//      if(ansi_count_compare(strQuery, strKey, strKey.length()) == 0)
//      {
//         
//         if(iCmp == 0)
//         {
//            
//            return true;
//            
//         }
//         else if(strQuery[strKey.length()] == '=')
//         {
//            
//            return true;
//            
//         }
//
//      }
//
//      auto iStart = strKey.length();
//
//      ::string::const_iterator pFind;
//
//      while(found(pFind = strQuery(iStart).find(strKey)))
//      {
//         
//         if(*(pFind - 1) == '&')
//         {
//            
//            if(strQuery.end() == (pFind + strKey.length()))
//            {
//               
//               return true;
//               
//            }
//            else if(*(pFind + strKey.length()) == '=')
//            {
//               
//               return true;
//               
//            }
//            
//         }
//         
//         iStart = strQuery.index_of(pFind + strKey.length() + 1);
//         
//      }
//
//      return false;
//      
//   }
//
//
//   bool url::query_param_has_char(const ::string & strQuery, const ::string & strKey)
//   {
//
//      strsize iCmp = strQuery.length() - strKey.length();
//      
//      if(iCmp < 0)
//      {
//         
//         return false;
//         
//      }
//
//      if(ansi_count_compare(strQuery, strKey, strKey.length()) == 0)
//      {
//         
//         if(iCmp == 0)
//         {
//            
//            return false;
//            
//         }
//         else if(strQuery[strKey.length()] == '=')
//         {
//            
//            auto pFind2 = strQuery(strKey.length() + 1).find('&');
//            
//            if(pFind2 > strQuery.begin())
//            {
//               
//               return (strQuery.index_of(pFind2) - (strKey.length() + 1)) > 0;
//               
//            }
//            else
//            {
//               
//               return (strQuery.length() - (strKey.length() + 1)) > 0;
//               
//            }
//
//         }
//
//      }
//
//      auto iStart = strKey.length();
//
//      ::string::const_iterator pFind;
//
//      while(found(pFind = strQuery(iStart).find(strKey)))
//      {
//         
//         if(*(pFind - 1) == '&')
//         {
//            
//            if(strQuery.end() == (pFind + strKey.length()))
//            {
//               
//               return false;
//               
//            }
//            else if(*(pFind + strKey.length()) == '=')
//            {
//               
//               auto pFind2 = strQuery(pFind + strKey.length() + 1).find('&');
//               
//               if(found(pFind2))
//               {
//                  
//                  return (pFind2 - (pFind + strKey.length() + 1)) > 0;
//                  
//               }
//               else
//               {
//                  
//                  return (strQuery.length() - (strQuery.index_of(pFind) + strKey.length() + 1)) > 0;
//                  
//               }
//               
//            }
//            
//         }
//         
//         iStart = strQuery.index_of(pFind + strKey.length() + 1);
//         
//      }
//
//      return false;
//
//   }
//
//
//   bool url::query_has_param_replace(string & strQuery, const ::string & strKey, const ::string & strValue)
//   {
//
//      strsize iCmp = strQuery.length() - strKey.length();
//      
//      if(iCmp < 0)
//      {
//
//         return false;
//         
//      }
//
//      if(ansi_count_compare(strQuery, strKey, strKey.length()) == 0)
//      {
//         
//         if(iCmp == 0)
//         {
//            
//            strQuery += "=" + strValue;
//            
//            return true;
//            
//         }
//         else if(strQuery[strKey.length()] == '=')
//         {
//            
//            auto pFind2 = strQuery(strKey.length() + 1).find('&');
//            
//            if(pFind2 > strQuery.begin())
//            {
//               
//               strQuery = strQuery.left(strKey.length() + 1) + strValue + strQuery.substr(pFind2);
//               
//            }
//            else
//            {
//               
//               strQuery = strQuery.left(strKey.length() + 1) + strValue;
//               
//            }
//            
//            return true;
//            
//         }
//
//      }
//
//      strsize iStart = strKey.length();
//
//      ::string::const_iterator pFind;
//
//      while(found(pFind = strQuery(iStart).find(strKey)))
//      {
//         
//         if(*(pFind - 1) == '&')
//         {
//            
//            if(strQuery.end() == (pFind + strKey.length()))
//            {
//               
//               strQuery += "=" + strValue;
//               
//               return true;
//               
//            }
//            else if(*(pFind + strKey.length()) == '=')
//            {
//               
//               auto pFind2 = strQuery(pFind + strKey.length() + 1).find('&');
//               
//               if(pFind2 > strQuery.begin())
//               {
//                  
//                  strQuery = strQuery.left(pFind + strKey.length() + 1) + strValue + strQuery.substr(pFind2);
//                  
//               }
//               else
//               {
//                  
//                  strQuery = strQuery.left(pFind + strKey.length() + 1) + strValue;
//                  
//               }
//               
//               return true;
//               
//            }
//            
//         }
//         
//         iStart = strQuery.index_of(pFind + strKey.length() + 1);
//         
//      }
//
//      return false;
//
//   }
//
//
//
//   bool url::server_ends(string strUrl, string strRoot)
//   {
//
//      string strServer = get_server(strUrl);
//
//      if(strServer.case_insensitive_order(strRoot) == 0)
//      {
//
//         return true;
//
//      }
//
//      if(case_insensitive_string_ends(strServer, "." + strRoot))
//      {
//
//         return true;
//
//      }
//
//      return false;
//
//   }
//
//
//
//   string url::set_script(const ::string & strUrl, const ::string & strScript)
//   {
//
//      return get_protocol(strUrl) + "://" + get_root(strUrl) + string(strScript) + ::str::has_char(get_query(strUrl), "?");
//
//   }
//
//
//   string url::override_if_empty(const ::string & strDst, const ::string & strSrc, bool bOverrideQuery)
//   {
//
//      string strProtocol = get_protocol(strDst);
//      string strProtocolOver = get_protocol(strSrc);
//      string strRoot = get_root(strDst);
//      string strRootOver = get_root(strSrc);
//      string strScript = get_script(strDst);
//      string strScriptOver = get_script(strSrc);
//      string strQuery = get_query(strDst);
//      string strQueryOver = get_query(strSrc);
//
//      if(strProtocol.is_empty())
//         strProtocol = strProtocolOver;
//
//      if(strRoot.is_empty())
//         strRoot = strRootOver;
//
//      if(strScript.is_empty())
//         strScript = strScriptOver;
//
//      if(bOverrideQuery && strQuery.is_empty())
//         strQuery = strQueryOver;
//
//      if (!string_begins(strScript, "/"))
//         strScript = "/" + strScript;
//
//      return strProtocol + "://" + strRoot + strScript + ::str::has_char(strQuery, "?");
//
//   }
//
//
//   string url::override_if_set_at_source(const ::string & strDst, const ::string & strSrc)
//   {
//
//      string strProtocol = get_protocol(strDst);
//      string strProtocolOver = get_protocol(strSrc);
//      string strRoot = get_root(strDst);
//      string strRootOver = get_root(strSrc);
//      string strScript = get_script(strDst);
//      string strScriptOver = get_script(strSrc);
//      string strQuery = get_query(strDst);
//      string strQueryOver = get_query(strSrc);
//
//      if(strProtocolOver.has_char())
//         strProtocol = strProtocolOver;
//
//      if(strRootOver.has_char())
//         strRoot = strRootOver;
//
//      if(strScriptOver.has_char())
//         strScript = strScriptOver;
//
//      if(strQueryOver.has_char())
//         strQuery = strQueryOver;
//
//      if (!string_begins(strScript, "/"))
//         strScript = "/" + strScript;
//
//      return strProtocol + "://" + strRoot + strScript + ::str::has_char(strQuery, "?");
//   }
//
//
//   string url::to_punycode(const ::string & str)
//   {
//
//      return nano()->idn()->idn_to_punycode(str);
//
//   }
//
//   string url::from_punycode(const ::string & str)
//   {
//
//      return nano()->idn()->idn_from_punycode(str);
//
//   }
//
//
//   inline bool character_isalnum(i32 i)
//   {
//
//      return (i >= '0' && i <= '9') || (i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z');
//
//   }


//   string url::os_fs(string strUrl, bool bPath)
//   {
//
//      strUrl.replace_with("_lt_", "<");
//      strUrl.replace_with("_gt_", ">");
//      strUrl.replace_with("_cl_", ":");
//      strUrl.replace_with("_dot_", ".");
//
//      if(bPath)
//      {
//
//         strUrl.replace_with("/", "\\");
//
//      }
//      else
//      {
//
//         strUrl.replace_with("_sl_","/");
//         strUrl.replace_with("_bsl_","\\");
//
//      }
//
//      strUrl.replace_with("_", " ");
//
//      return strUrl;
//
//   }
//
//
//   string url::os_fspath(string strUrl)
//   {
//
//      return os_fs(strUrl, true);
//
//   }
//
//
//   string url::os_fsname(string strUrl)
//   {
//
//      return os_fs(strUrl, false);
//
//   }
//
//
//} // namespace url
//
//
//
//
//
//
//#include "framework.h"
////#include "acme/prototype/string/hex.h"
//
//
//

//
//
//bool is_url(const ::scoped_string & scopedstrCandidate, const char** ppszRequest)
//{
//
//   const ::ansi_character * psz = scopedstrCandidate;
//
//   while (*psz != '\0' && (*psz == '.' || *psz == '_' || *psz == '-' || character_isalnum(*psz)))
//   {
//      psz++;
//   }
//   if (psz == scopedstrCandidate.begin())
//      return false;
//   if (psz == scopedstrCandidate.begin() + 1)
//      return false;
//   if (*psz != ':')
//      return false;
//   psz++;
//   if (*psz != '/' && *psz != '\\')
//      return false;
//   psz++;
//   if (*psz == '/' || *psz == '\\')
//   {
//      psz++;
//   }
//   /*if(*psz != '/' && *psz != '\\')
//      return false;
//   psz++;*/
//   while (*psz != '\0' && (*psz == '.' || *psz == ':' || *psz == '@' || *psz == '_' || *psz == '-' || character_isalnum(*psz)))
//   {
//      psz++;
//   }
//   if (*psz != '\0' && *psz != '/' && *psz != '\\')
//      return false;
//   if (ppszRequest != nullptr)
//   {
//      *ppszRequest = psz;
//   }
//   return true;
//
//}
//
//
//CLASS_DECL_ACME bool is_like_url_protocol(const ::scoped_string & scopedstr)
//{
//
//   if (scopedstr.is_empty())
//   {
//
//      return false;
//
//   }
//
//   auto psz = scopedstr.begin();
//
//   if (character_isalpha(*psz))
//   {
//
//      psz++;
//
//   }
//
//   if (*psz == ':' && (psz[1] == '\0' || (psz[1] == '/' && psz[2] == '/' && psz[3] == '\0')))
//   {
//
//      return true;
//
//   }
//
//   while (character_isalnum(*psz) || *psz == '-' || *psz == '_' || *psz == '.')
//   {
//
//      psz++;
//
//   }
//
//   if (*psz == ':' && (psz[1] == '\0' || (psz[1] == '/' && psz[2] == '/' && psz[3] == '\0')))
//   {
//
//      return true;
//
//   }
//
//   return false;
//
//}
//
//
//
//
////#include "framework.h"
////#include "net.h"
////#include "as_string.h"
////#include "acme/exception/parsing.h"
////#include "acme/prototype/string/hex.h"
//////#include "acme/operating_system.h"
//
//
//string url::decode(const ::scoped_string & strParam)
//{
//
//   //return ::url::decode(strParam, strParam.size());
//
//   string str(strParam);
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
//      auto iFind = str.find_index("%",iStart);
//
//      if(iFind == -1)
//      {
//
//         strDecode += str.substr(iStart);
//
//         break;
//
//      }
//
//      strDecode += str.substr(iStart, iFind - iStart);
//
//      if(str[iFind + 1] == '%')
//      {
//
//         strDecode += "%";
//
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
//
//            strDecode += ch;
//
//         }
//
//         iStart = iFind + 3;
//
//      }
//
//
//   }
//
//   return strDecode;
//
//}
//
//
//namespace url
//{
   //
   //   CLASS_DECL_ACME bool query_get_param(string& strParam, const ::ansi_character * pszKey, const ::ansi_character * pszUrl)
   //   {
   //
   //      const ::ansi_character * pszBeg;
   //      const ::ansi_character * pszEnd;
   //
   //      {
   //
   //         string strKey;
   //
   //         strKey = "?";
   //         strKey += pszKey;
   //         strKey += "=";
   //
   //         pszBeg = ansi_find_string(pszUrl, strKey);
   //
   //         if (pszBeg != nullptr)
   //         {
   //
   //            pszBeg += strKey.length();
   //
   //            goto success;
   //
   //         }
   //
   //      }
   //
   //      {
   //
   //         string strKey;
   //
   //         strKey = "&";
   //         strKey += pszKey;
   //         strKey += "=";
   //
   //         pszBeg = ansi_find_string(pszUrl, strKey);
   //
   //         if (pszBeg != nullptr)
   //         {
   //
   //            pszBeg += strKey.length();
   //
   //            goto success;
   //
   //         }
   //
   //      }
   //
   //      {
   //
   //         string strKey;
   //
   //         strKey = "?";
   //         strKey += pszKey;
   //         strKey += "&";
   //
   //         pszBeg = ansi_find_string(pszUrl, strKey);
   //
   //         if (pszBeg != nullptr)
   //         {
   //
   //            strParam = "";
   //
   //            return true;
   //
   //         }
   //
   //      }
   //
   //      {
   //
   //         string strKey;
   //
   //         strKey = "&";
   //         strKey += pszKey;
   //         strKey += "&";
   //
   //         pszBeg = ansi_find_string(pszUrl, strKey);
   //
   //         if (pszBeg != nullptr)
   //         {
   //
   //            strParam = "";
   //
   //            return true;
   //
   //         }
   //
   //      }
   //
   //      return false;
   //
   //   success:
   //
   //      pszEnd = ansi_find_string(pszBeg, "&");
   //
   //      if (pszEnd == nullptr)
   //      {
   //         strParam = pszBeg;
   //      }
   //      else
   //      {
   //         strParam = string(pszBeg, pszEnd - pszBeg);
   //      }
   //
   //      return true;
   //
   //   }
   //
   //

   //
   //   void url::defer_raw_http(::property_set & set, const ::payload & payloadUrl)
   //   {
   //
   //      auto strServer = get_server(payloadUrl);
   //
   //      bool bCa2Server = ::str::find_wwci(strServer, "ca2") >= 0;
   //
   //      string strQuery = get_query(payloadUrl);
   //
   //      string strSessid = query_get_param(strQuery, "sessid");
   //
   //      set["http_set"]["raw_http"] = !bCa2Server || strSessid == "noauth";
   //
   //   }
   //
   //
   //
   //   void url::defer_raw_http(::property_set & set)
   //   {
   //
   //      defer_raw_http(set, set["url"]);
   //
   //   }
   //
   //
   //   bool url::case_insensitive_is_protocol(const ::string & strUrl, const ::string & strProtocolCompare)
   //   {
   //
   //      auto strProtocol = get_protocol(strUrl);
   //
   //      return strProtocol.case_insensitive_equals(strProtocolCompare);
   //
   //   }
   //
   //   
   //   bool url::is_http(const ::string & strUrl)
   //   {
   //
   //      return case_insensitive_is_protocol(strUrl, "http");
   //
   //   }
   //
   //
   //   bool url::is_https(const ::string & strUrl)
   //   {
   //
   //      return case_insensitive_is_protocol(strUrl, "https");
   //
   //   }
   //
   //
   //   bool url::is_http_or_https(const ::string & strUrl)
   //   {
   //
   //      return is_http(strUrl) || is_https(strUrl);
   //
   //   }
   //
   //
   //   bool url::is_ftp(const ::string & strUrl)
   //   {
   //
   //      return case_insensitive_is_protocol(strUrl, "ftp");
   //
   //   }
   //
   //
   //   bool url::is_ftps(const ::string & strUrl)
   //   {
   //
   //      return case_insensitive_is_protocol(strUrl, "ftps");
   //
   //   }
   //
   //
   //   bool url::is_ftp_or_ftps(const ::string & strUrl)
   //   {
   //
   //      return is_ftp(strUrl) || is_ftps(strUrl);
   //
   //   }
   //
   //
   //   bool url::is_common_internet_protocol(const ::string & strUrl)
   //   {
   //
   //      return is_http_or_https(strUrl) || is_ftp_or_ftps(strUrl);
   //
   //   }
   //
   //
   //   string url::__part_set(enum_part epart, const ::scoped_string& scopedstrPart, const ::scoped_string& scopedstrKey, const ::scoped_string& scopedstr)
   //   {
   //
   //      switch (epart)
   //      {
   //      case e_part_query:
   //         return __query_set(scopedstrPart, scopedstrKey, scopedstr);
   //      case e_part_object:
   //         return __object_set(scopedstrPart, scopedstrKey, scopedstr);
   //      default:
   //         return parameter_set(scopedstrPart, scopedstrKey, scopedstr);
   //
   //      }
   //
   //   }
   //
   //
   //   part::part(const char* psz)
   //   {
   //
   //      m_pszLastSlash = strrchr(psz, '/');
   //
   //      m_pszLastQuestionMarkAfterLastSlash = strrchr(psz, '?');
   //
   //      if (m_pszLastSlash &&
   //         m_pszLastQuestionMarkAfterLastSlash &&
   //         m_pszLastQuestionMarkAfterLastSlash < m_pszLastSlash)
   //      {
   //
   //         m_pszLastQuestionMarkAfterLastSlash = nullptr;
   //
   //      }
   //
   //      if (m_pszLastQuestionMarkAfterLastSlash)
   //      {
   //
   //         if (m_pszLastSlash)
   //         {
   //
   //            m_etype = e_type_mixed;
   //
   //         }
   //         else
   //         {
   //
   //            m_etype = e_type_strict_object_with_query;
   //
   //         }
   //
   //      }
   //      else
   //      {
   //
   //         if (m_pszLastSlash)
   //         {
   //
   //            m_etype = e_type_strict_object_no_query;
   //
   //         }
   //         else
   //         {
   //
   //            m_etype = e_type_query;
   //
   //         }
   //
   //      }
   //
   //   }
   //
   //
   //
//
//} // namespace url
//
//
//
//
////string str;
////
////string strChar;
////
////while (*psz != '\0')
////{
////
////   if (ansi_char_isdigit(*psz)
////      || ansi_char_isalpha(*psz)
////      || *psz == '.'
////      || *psz == '-'
////      || *psz == '_')
////   {
////      str += *psz;
////   }
////   else if (*psz == ' ')
////   {
////      str += "+";
////   }
////   else
////   {
////      strChar.formatf("%02X", *psz);
////      str += "%" + strChar.right(2);
////   }
////
////   psz++;
////}
////
////return str;
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//#if defined(MACOS)
//#elif defined(APPLE_IOS)
//
//void openURL(const string& url_str);
//
//int ui_open_url(const ::ansi_character * psz);
//
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
//
//
//#endif
//
//
//
//
//
//
//
//
//
//
//
////#ifdef WINDOWS
////#define strdup _strdup
////#endif
////
////CLASS_DECL_ACME int_bool freerdp_get_credentials(void * instance, char** username,char** password,char** domain, const ::ansi_character * pszServerName, int bInteractive)
////{
////
////   ::acme::application * papp = (::acme::application *) instance;
////
////   ::account::user user;
////
////   user.initialize(papp);
////
////   ::account::credentials credentials;
////
////   credentials.initialize_account_credentials(&user, Sess(papp).account()->storage());
////
////   //string strUsername;
////
////   //string strUser;
////
////   //string strDomain;
////
////   //string strPassword;
////
////   //string strToken;
////
////   credentials.m_strToken = Sys(papp).crypto_md5_text(pszServerName);
////
////   //string strTitle;
////
////   credentials.m_strTitle = "Enter Credentials for : " + string(pszServerName);
////
////   credentials.m_bInteractive = bInteractive;
////
////   //strUsername = acmefile()->as_string(         auto psystem = system();
////
////         auto pacmedirectory = psystem->m_pacmedirectory;
////
////pacmedirectory->system() / "config\\user.txt");
//////
//////   //strPassword = acmefile()->as_string(         auto psystem = system();
////
////         auto pacmedirectory = psystem->m_pacmedirectory;
////
////pacmedirectory->system() / "config\\pass.txt");
//////
////   //if(strUsername.has_char() && strPassword.has_char())
////   //{
////
////   //}
////   //else
////   //{
////
////   if(credentials.get_credentials() != ::success_credentials)
////   {
////
////      return false;
////
////   }
////
////   string strUser;
////
////   string strPassword(credentials.m_strPassword);
////
////   string strDomain;
////
////   auto pFind = user.m_strLogin.find('/');
////
////   if(iFind > 0)
////   {
////
////      strUser = user.m_strLogin(pFind + 1);
////
////      strDomain = user.m_strLogin(0, pFind);
////
////   }
////   else
////   {
////
////      strUser = user.m_strLogin;
////
////   }
////
////   if(username != nullptr)
////   {
////
////      *username = strdup(strUser);
////
////   }
////
////   if(domain != nullptr && strDomain.has_char())
////   {
////
////      *domain = strdup(strDomain);
////
////   }
////
////   if(password != nullptr)
////   {
////
////      *password = strdup(strPassword);
////
////   }
////
////   return true;
////
////}
//
//
//
//
//
//
//
////CLASS_DECL_ACME bool is_url(const ::ansi_character * pszCandidate)
////{
////
////   string strCandidate(pszCandidate);
////
////   strsize iLen = strCandidate.length();
////
////   strsize i = 0;
////
////   char ch;
////
////   while (i < iLen)
////   {
////
////      ch = strCandidate[i];
////
////      if (isalpha((uchar)ch))
////         i++;
////      else if (ch == '.')
////         i++;
////      else if (ch == ':' && (((i + 1) == iLen) ||
////         (iLen > (i + 3)
////            && strCandidate[i + 1] == '/'
////            && strCandidate[i + 2] == '/')))
////         return true;
////      else
////         return false;
////
////   }
////
////   return false;
////
////}
//
//
//
//
//
////CLASS_DECL_ACME string ::url::decode(const ::ansi_character * psz)
////{
////
////   string str(psz);
////
////   string strDecode;
////
////   str.replace_with(" ", "+");
////
////   strsize iStart = 0;
////
////   while (true)
////   {
////
////      auto pFind = str.find("%", iStart);
////
////      if (iFind == -1)
////      {
////         strDecode += str.substr(iStart);
////         break;
////      }
////
////      strDecode += str.substr(iStart, iFind - iStart);
////
////      if (str[iFind + 1] == '%')
////      {
////
////         strDecode += "%";
////         iStart = iFind + 2;
////
////      }
////      else
////      {
////
////         char ch = (char)strtol(str.substr(iFind + 1, 2), nullptr, 16);
////
////         if (ch != 0)
////         {
////            strDecode += ch;
////         }
////
////         iStart = iFind + 3;
////
////      }
////
////
////   }
////
////   return ::transfer(strDecode);
////
////
////}
//
//
//
////string ::url::decode(const ::ansi_character * pszUrl, strsize iLen)
////
////{
////
////   string strDecode;
////
////   char* psz = strDecode.get_buffer(iLen * 4);
////
////   strsize i = 0;
////
////   while (*pszUrl != '\0' && i < iLen)
////
////   {
////      if (*pszUrl == '+')
////
////      {
////         i++;
////         *psz = ' ';
////         psz++;
////         pszUrl++;
////
////      }
////      else if (*pszUrl == '%')
////
////      {
////         iLen--;
////         pszUrl++;
////
////         if (*pszUrl == '%')
////
////         {
////            i++;
////            *psz = '%';
////            psz++;
////            pszUrl++;
////
////         }
////         else
////         {
////            i++;
////            iLen--;
////            *psz = (char)(uchar)(hex::to(*pszUrl) * 16 + hex::to(*(pszUrl + 1)));
////
////            psz++;
////            pszUrl += 2;
////
////         }
////      }
////      else
////      {
////         i++;
////         *psz = *pszUrl;
////
////         psz++;
////         pszUrl++;
////
////      }
////   }
////
////   strDecode.release_buffer(iLen);
////
////   return strDecode;
////
////}
////
////
//
//
//
//
////CLASS_DECL_ACME bool url_query_get_param(string& strParam, const ::ansi_character * pszKey, const ::ansi_character * pszUrl)
////{
////
////   const ::ansi_character * pszBeg;
////   const ::ansi_character * pszEnd;
////
////   {
////
////      string strKey;
////
////      strKey = "?";
////      strKey += pszKey;
////      strKey += "=";
////
////      pszBeg = ansi_find_string(pszUrl, strKey);
////
////      if (pszBeg != nullptr)
////      {
////
////         pszBeg += strKey.length();
////
////         goto success;
////
////      }
////
////   }
////
////   {
////
////      string strKey;
////
////      strKey = "&";
////      strKey += pszKey;
////      strKey += "=";
////
////      pszBeg = ansi_find_string(pszUrl, strKey);
////
////      if (pszBeg != nullptr)
////      {
////
////         pszBeg += strKey.length();
////
////         goto success;
////
////      }
////
////   }
////
////   {
////
////      string strKey;
////
////      strKey = "?";
////      strKey += pszKey;
////      strKey += "&";
////
////      pszBeg = ansi_find_string(pszUrl, strKey);
////
////      if (pszBeg != nullptr)
////      {
////
////         strParam = "";
////
////         return true;
////
////      }
////
////   }
////
////   {
////
////      string strKey;
////
////      strKey = "&";
////      strKey += pszKey;
////      strKey += "&";
////
////      pszBeg = ansi_find_string(pszUrl, strKey);
////
////      if (pszBeg != nullptr)
////      {
////
////         strParam = "";
////
////         return true;
////
////      }
////
////   }
////
////   return false;
////
////success:
////
////   pszEnd = ansi_find_string(pszBeg, "&");
////
////   if (pszEnd == nullptr)
////   {
////      strParam = pszBeg;
////   }
////   else
////   {
////      strParam = string(pszBeg, pszEnd - pszBeg);
////   }
////
////   return true;
////
////}
//
//
//
//
//
//
//
//
//CLASS_DECL_ACME string url::encode(const ::scoped_string & scopedstr)
//{
//
//   string str;
//
//   //char sz[256];
//
//   auto psz = scopedstr.m_begin;
//
//   auto pszEnd = scopedstr.m_end;
//
//   ::i32 len = 0;
//
//   while (psz < pszEnd)
//   {
//
//      auto iCharacter = ::unicode_index_length(psz, len);
//
//      if (psz + len > pszEnd)
//      {
//
//         break;
//
//      }
//
//      if (ansi_char_isdigit(iCharacter)
//         || ansi_char_isalpha(iCharacter)
//         || iCharacter == '.'
//         || iCharacter == '-'
//         || iCharacter == '_')
//      {
//
//         str += (char)iCharacter;
//
//      }
//      else if (iCharacter == ' ')
//      {
//
//         str += "+";
//
//      }
//      else
//      {
//
//         for (int i = 0; i < len; i++)
//         {
//
//            ::i32 iChar = ((::i32)psz[i]) & 0x000000ff;
//
//            str.append_formatf("%%%02X", iChar);
//
//         }
//         //psz + len
//
//         //ansi_from_i64(sz, uch, 16);
//
//         //ansi_upper(sz);
//
//         //if (ansi_length(sz) == 0)
//         //{
//
//         //   str += "%00";
//
//         //}
//         //else if (ansi_length(sz) == 1)
//         //{
//
//         //   str += "%0";
//
//         //   str += sz;
//
//         //}
//         //else if (ansi_length(sz) == 2)
//         //{
//
//         //   str += "%";
//
//         //   str += sz;
//
//         //}
//
//      }
//
//      psz+=len;
//
//   }
//
//   return str;
//
//}
//
//
////string str;
////
////string strChar;
////
////while (*psz != '\0')
////{
////
////   if (ansi_char_isdigit(*psz)
////      || ansi_char_isalpha(*psz)
////      || *psz == '.'
////      || *psz == '-'
////      || *psz == '_')
////   {
////      str += *psz;
////   }
////   else if (*psz == ' ')
////   {
////      str += "+";
////   }
////   else
////   {
////      strChar.formatf("%02X", *psz);
////      str += "%" + strChar.right(2);
////   }
////
////   psz++;
////}
////
////return str;
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//#if defined(MACOS)
//
////void openURL(const string& url_str);
////
////
////void openURL(const string& url_str)
////{
////   CFURLRef url = CFURLCreateWithBytes(
////      nullptr,                        // allocator
////      (::u328*)url_str.c_str(),     // URLBytes
////      url_str.length(),            // length
////      kCFStringEncodingASCII,      // encoding
////      nullptr                         // baseURL
////   );
////   LSOpenCFURLRef(url, 0);
////   CFRelease(url);
////}
//
//#elif defined(APPLE_IOS)
//
//void openURL(const string& url_str);
//
//int ui_open_url(const ::ansi_character * psz);
//
////void openURL(const string& url_str)
////{
////   //   throw ::exception(todo);
////   //   CFURLRef url = CFURLCreateWithBytes(
////   //      nullptr,                        // allocator
////   //      (::u328*)url_str.c_str(),     // URLBytes
////   //      url_str.length(),            // length
////   //      kCFStringEncodingASCII,      // encoding
////   //      nullptr                         // baseURL
////   //      );
////   //       LSOpenCFURLRef(url,0);
////
////   ui_open_url(url_str);
////
////   //   CFRelease(url);
////}
//
//
//#endif
//
//
//
//
//
//
//
//
//
//
//
////#ifdef WINDOWS
////#define strdup _strdup
////#endif
////
////CLASS_DECL_ACME int_bool freerdp_get_credentials(void * instance, char** username,char** password,char** domain, const ::ansi_character * pszServerName, int bInteractive)
////{
////
////   ::application * papp = (::apex::application *) instance;
////
////   ::account::user user;
////
////   user.initialize(papp);
////
////   ::account::credentials credentials;
////
////   credentials.initialize_account_credentials(&user, Sess(papp).account()->storage());
////
////   //string strUsername;
////
////   //string strUser;
////
////   //string strDomain;
////
////   //string strPassword;
////
////   //string strToken;
////
////   credentials.m_strToken = Sys(papp).crypto_md5_text(pszServerName);
////
////   //string strTitle;
////
////   credentials.m_strTitle = "Enter Credentials for : " + string(pszServerName);
////
////   credentials.m_bInteractive = bInteractive;
////
////   //strUsername = acmefile()->as_string(         auto psystem = system();
//
//   /*      auto pacmedirectory = psystem->m_pacmedirectory;
//
//pacmedirectory->system() / "config\\user.txt")*/;
////
////   //strPassword = acmefile()->as_string(         auto psystem = system();
////
////         auto pacmedirectory = psystem->m_pacmedirectory;
////
////pacmedirectory->system() / "config\\pass.txt");
////
////   //if(strUsername.has_char() && strPassword.has_char())
////   //{
////
////   //}
////   //else
////   //{
////
////   if(credentials.get_credentials() != ::success_credentials)
////   {
////
////      return false;
////
////   }
////
////   string strUser;
////
////   string strPassword(credentials.m_strPassword);
////
////   string strDomain;
////
////   auto pFind = user.m_strLogin.find('/');
////
////   if(iFind > 0)
////   {
////
////      strUser = user.m_strLogin(pFind + 1);
////
////      strDomain = user.m_strLogin(0, pFind);
////
////   }
////   else
////   {
////
////      strUser = user.m_strLogin;
////
////   }
////
////   if(username != nullptr)
////   {
////
////      *username = strdup(strUser);
////
////   }
////
////   if(domain != nullptr && strDomain.has_char())
////   {
////
////      *domain = strdup(strDomain);
////
////   }
////
////   if(password != nullptr)
////   {
////
////      *password = strdup(strPassword);
////
////   }
////
////   return true;
////
////}
//
//
//
//
//
//
//
//
//
//
//


} // namespace url



