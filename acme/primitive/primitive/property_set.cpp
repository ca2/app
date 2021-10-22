#include "framework.h"
#include "acme/platform/static_start.h"
#include "acme/platform/static_start_internal.h"


#undef new


#ifdef LINUX
#include <locale.h>
#endif

#ifdef WINDOWS
extern _locale_t g_localeC;
#else
extern locale_t g_localeC;
#endif


property_set::property_set(::std::initializer_list < ::payload > list)
{

   ::id id;

   index i = 0;

   for (auto & item : list)
   {

      if (i % 2 == 0)
      {

         id = item;

      }
      else if (i % 2 == 1)
      {

         operator[](id) = item;

      }

      i++;

   }

   if (i % 2 == 1)
   {

      operator[](id) = ::e_type_empty;

   }

}


property_set::~property_set()
{

}


//id property_set::get_new_id()
//{
//
//   index iMax = -1;
//
//   for(iterator it = begin(); it != end(); it++)
//   {
//
//      if(it->element1().m_etype == id::type_integer)
//      {
//
//         if(it->element1().m_i > iMax)
//         {
//
//            iMax = (index)it->element1().m_i;
//
//         }
//
//      }
//
//   }
//
//   return iMax + 1;
//
//}
//




//
//property & property_set::defer_auto_add(id idName)
//{
//
//   return *add(idName);
//
//}


bool property_set::is_set_empty(::count countMinimum) const
{
   return get_count() < countMinimum;
}

bool property_set::has_properties(::count countMinimum) const
{
   return get_count() >= countMinimum;
}


property * property_set::find_value_ci(const ::payload & payload) const
{

   for(auto & pproperty : *this)
   {

      if (pproperty->compare_ci(payload) == 0)
      {

         return pproperty;

      }

   }

   return nullptr;

}


property * property_set::find_value_ci(const char * psz) const
{

   for (auto & pproperty : *this)
   {

      if (pproperty->compare_ci(psz) == 0)
      {

         return pproperty;

      }

   }

   return nullptr;

}




property * property_set::find_value(const ::payload & payload) const
{

   for(auto & pproperty : *this)
   {

      if (*pproperty == payload)
      {

         return pproperty;

      }

   }

   return nullptr;

}


property * property_set::find_value(const char * psz) const
{

   for (auto & pproperty : *this)
   {

      if (*pproperty == psz)
      {

         return pproperty;

      }

   }

   return nullptr;

}


bool property_set::contains_value_ci(const ::payload & payload, ::count countMin, ::count countMax) const
{
   ::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax)) && find_value_ci(payload) != nullptr)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}




bool property_set::contains_value_ci(const char * psz, ::count countMin, ::count countMax) const
{
   ::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax)) && find_value_ci(psz) != nullptr)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}


bool property_set::contains_value(const ::payload & payload, ::count countMin, ::count countMax) const
{
   ::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax)) && (find_value(payload)) != nullptr)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}


bool property_set::contains_value(const char * psz, ::count countMin, ::count countMax) const
{
   ::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax)) && find_value(psz) != nullptr)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}


bool property_set::erase_first_value_ci(const ::payload & payload)
{

   property * pproperty = find_value_ci(payload);

   if(pproperty != nullptr)
   {

      return erase_by_name(pproperty->m_id);

   }

   return false;

}


bool property_set::erase_first_value_ci(const char * pcsz)
{

   property * pproperty = find_value_ci(pcsz);

   if(pproperty != nullptr)
   {

      return erase_by_name(pproperty->m_id);

   }

   return false;

}


bool property_set::erase_first_value(const ::payload & payload)
{

   property * pproperty = find_value(payload);

   if(pproperty != nullptr)
   {

      return erase_by_name(pproperty->m_id);

   }

   return false;

}


bool property_set::erase_first_value(const char * pcsz)
{

   property * pproperty = find_value(pcsz);

   if(pproperty != nullptr)
   {

      return erase_by_name(pproperty->m_id);

   }

   return false;

}


::count property_set::erase_value_ci(const ::payload & payload, ::count countMin, ::count countMax)
{

   ::count count = 0;

   if (contains_value_ci(payload, countMin, countMax))
   {

      while (conditional(countMax >= 0, count < countMax) && (erase_first_value_ci(payload)))
      {

         count++;

      }

   }

   return count;

}


::count property_set::erase_value_ci(const char * psz, ::count countMin, ::count countMax)
{

   ::count count = 0;

   if(contains_value_ci(psz,countMin,countMax))
   {

      while(conditional(countMax >= 0,count < countMax) && erase_first_value_ci(psz))
      {

         count++;

      }

   }

   return count;

}


::count property_set::erase_value(const ::payload & payload, ::count countMin, ::count countMax)
{

   ::count count = 0;

   if(contains_value(payload,countMin,countMax))
   {

      while(conditional(countMax >= 0,count < countMax && erase_first_value(payload)))
      {

         count++;

      }

   }

   return count;

}


::count property_set::erase_value(const char * psz, ::count countMin, ::count countMax)
{

   ::count count = 0;

   if(contains_value(psz,countMin,countMax))
   {

      while(conditional(countMax >= 0,count < countMax) && erase_first_value(psz))
      {

         count++;

      }

   }

   return count;

}


::count property_set::unset(const id & idName)
{

   ::count c = 0;

   ::index iFind = 0;

   while (true)
   {

      iFind = find_index(idName, iFind);

      if (__not_found(iFind))
      {

         return c;

      }

      erase_at(iFind);

      c++;

   }

}


bool property_set::is_new(const id & idName) const
{

   const property * pproperty = find(idName);

   if (pproperty == nullptr)
   {

      return true;

   }

   return pproperty->is_new();

}


bool property_set::is_null(const id & idName) const
{

   const property * pproperty = find(idName);

   if (pproperty == nullptr)
   {

      return true;

   }

   return pproperty->is_null();

}


bool property_set::is_new_or_null(const id & idName) const
{

   const property * pproperty = find(idName);

   if (pproperty == nullptr)
   {

      return true;

   }

   return pproperty->is_new_or_null();

}


bool property_set::is_empty(const id & idName) const
{

   const property * pproperty = find(idName);

   if (pproperty == nullptr)
   {

      return true;

   }

   return pproperty->is_empty();

}


void property_set::_008ParseCommandLine(const char * pszCmdLineParam, ::payload & varFile)
{

   string strApp;

   _008Parse(false, pszCmdLineParam, varFile, strApp);

}


void property_set::_008ParseCommandFork(const char * pszCmdLineParam, ::payload & varFile, string & strApp)
{

   _008Parse(true, pszCmdLineParam, varFile, strApp);

}


void property_set::_008Add(const char * pszKey, const char * pszValue)
{

   string_array straKey;

   straKey.explode(".", pszKey);

   if (straKey.is_empty())
   {

      return;

   }

   property_set * pset = this;

   i32 i = 0;

   while(i  < straKey.get_upper_bound())
   {

      pset = &(*pset)[straKey[i]].as_propset();

      i++;

   }

   if (::is_null(pszValue))
   {

      pset->operator[](straKey[i]).set_type(::e_type_key_exists, false);

   }
   else if(pset->has_property(straKey[i]) && pset->operator[](straKey[i]) != pszValue)
   {

      pset->operator[](straKey[i]).stra().add(pszValue);

   }
   else
   {

      pset->operator[](straKey[i])= payload(pszValue);

   }

}


void property_set::_008Parse(bool bApp, const char * pszCmdLine, ::payload & varFile, string & strApp)
{

   if(pszCmdLine == nullptr)
      return;

   //string_array stra = get_c_args_for_c(pszCmdLine);
   //string_array stra = get_c_args_from_c(pszCmdLine);
   auto stra = get_c_args_from_string(pszCmdLine);

   int i = 0;

   if(bApp && stra.get_count() > 0)
   {

      strApp = stra[0];

      i++;

   }

   index iFindColon = stra.find_first(":");

   if(iFindColon < 0)
   {

      iFindColon = stra.get_size();

   }

   if(iFindColon > i)
   {

      if(iFindColon - i > 1)
      {

         for(; i < iFindColon; i++)
         {

            varFile.stra().add(stra[i]);

         }

      }
      else
      {

         varFile = stra[i];

         i++;

      }

      i++;

   }

   for(; i < stra.get_size(); i++)
   {

      string str = stra[i];

      index iFindEqual = str.find('=');

      index iFindQuote = str.find('\"');

      if(iFindEqual >= 0)
      {

         string strValue;

         strValue = str.Mid(iFindEqual + 1);

         if(iFindEqual + 1 == iFindQuote)
         {

            const char * pszValue = strValue;

            strValue = ::str::consume_quoted_value(pszValue);

         }

         _008Add(str.Left(iFindEqual), strValue);

      }
      else
      {

         _008Add(str, nullptr);

      }

   }

}


void property_set_skip_json(const char *& pszJson)
{

   property_set_skip_json(pszJson, pszJson + strlen(pszJson) - 1);

}


void property_set_skip_json(const char *& pszJson, const char * pszEnd)
{

   ::str::consume_spaces(pszJson, 0, pszEnd);

   if (*pszJson == '\0')
   {

      return;

   }

   ::str::consume(pszJson, "{", 1, pszEnd);

   ::str::consume_spaces(pszJson, 0, pszEnd);

   if (*pszJson == '}')
   {

      pszJson++;

      return;

   }

   while (true)
   {

      ::id id;

      property_skip_json_id(pszJson, pszEnd);

      property_skip_json_value(pszJson, pszEnd);

      ::str::consume_spaces(pszJson, 0, pszEnd);

      if (*pszJson == ',')
      {

         pszJson++;

         continue;

      }
      else if (*pszJson == '}')
      {

         pszJson++;

         return;

      }
      else
      {

         string str = "not expected character : ";

         str += pszJson;

         __throw(error_failed, str);

      }

   }

}


void property_set::parse_ini(const ::string & strIni)
{

   string_array stra;

   stra.add_lines(strIni);

   property_set * pset = this;

   for(auto & strLine : stra)
   {

      strLine.trim();

      if(strLine.is_empty())
      {

         continue;

      }

      if(::str::begins_eat(strLine, "["))
      {

         strLine.trim_right("]");

         pset = &operator[](strLine).as_propset();

      }
      else
      {

         string strKey;

         strKey = ::str::token(strLine, "=");

         if(strKey.has_char())
         {

            strKey.trim();

            strLine.trim();

            pset->operator[](strKey) = strLine;

         }

      }

   }

}


void property_set::parse_json(const ::string & strJson)
{

#ifdef LINUX

   uselocale(::acme::g_localeC);

#endif

   const char * pszJson = strJson;

   parse_json(pszJson, pszJson + strJson.get_length() - 1);

}


void property_set::parse_json(const char * & pszJson)
{

#ifdef LINUX
   uselocale(::acme::g_localeC);
#endif

   parse_json(pszJson, pszJson + strlen(pszJson) - 1);

}


void property_set::parse_json(const char * & pszJson, const char * pszEnd)
{
   ::str::consume_spaces(pszJson, 0, pszEnd);
   if (*pszJson == '\0')
   {
      return;
   }
   ::str::consume(pszJson, "{", 1, pszEnd);
   ::str::consume_spaces(pszJson, 0, pszEnd);
   if (*pszJson == '}')
   {
      pszJson++;
      return;
   }
   while(true)
   {

      ::id id;

      ::property_parse_json_id(id, pszJson,pszEnd);

      auto & property = operator[](id);

      ::property_parse_json_value(property,pszJson,pszEnd);

      ::str::consume_spaces(pszJson, 0, pszEnd);

      if(*pszJson == ',')
      {

         pszJson++;

         continue;

      }
      else if(*pszJson == '}')
      {

         pszJson++;

         return;

      }
      else
      {

         string str = "not expected character : ";

         str += pszJson;

         __throw(error_parsing, str);

      }

   }

}


string & property_set::get_json(string & str, bool bNewLine) const
{

   str += "{";

   auto p = values();

   if(p)
   {

      p->get_json(str, bNewLine);

      p++;

   }

   for(; p; p++)
   {

      if (bNewLine)
      {

         str += ", \r\n";

      }
      else
      {

         str += ", ";

      }

      p->get_json(str, bNewLine);

   }

   if (bNewLine)
   {

      str += "\r\n";

   }

   str += "}";


   return str;

}


void property_set::parse_url_query(const char * pszUrl)
{
   if(pszUrl == nullptr)
      return;
   const char * pszUrlQuery = strchr(pszUrl, '?');
   if(pszUrlQuery == nullptr)
      return _parse_url_query(pszUrl);
   else
      return _parse_url_query(pszUrlQuery + 1);
}

void property_set::_parse_url_query(const char * pszUrlQuery)
{
   if(pszUrlQuery == nullptr)
      return;
   const char * pszParam = pszUrlQuery;
   const char * pszParamEnd;
   const char * pszKeyEnd;
   string strKey;
   while(true)
   {
      pszParamEnd = strchr(pszParam, '&');
      pszKeyEnd   = strchr(pszParam, '=');
      if(pszParamEnd == nullptr)
      {
         if(pszKeyEnd == nullptr)
         {
            strKey = url_decode(pszParam, strlen(pszUrlQuery) - (pszParam - pszUrlQuery));
            _008Add(strKey, "");
         }
         else
         {
            string strKey = url_decode(pszParam, pszKeyEnd - pszParam);
            string strValue = url_decode(pszKeyEnd + 1, strlen(pszUrlQuery) - (pszKeyEnd + 1 - pszUrlQuery));
            _008Add(strKey, strValue);
         }
         return;
      }
      else
      {
         if(pszKeyEnd == nullptr || pszKeyEnd > pszParamEnd)
         {
            strKey = url_decode(pszParam, pszParamEnd - pszParam);
            _008Add(strKey, "");
         }
         else
         {
            string strKey = url_decode(pszParam, pszKeyEnd - pszParam);
            string strValue = url_decode(pszKeyEnd + 1, pszParamEnd - (pszKeyEnd + 1));
            _008Add(strKey, strValue);
         }
      }
      pszParam = pszParamEnd + 1;
   }

}

void property_set::parse_http_headers(const char * pszHeaders)
{
   string_array stra;
   stra.add_tokens(pszHeaders, "\r\n", true);
   string strName;
   for(i32 i = 0; i < stra.get_size(); i++)
   {
      strsize iPos = stra[i].find(":");
      if(iPos < 0)
      {

         strName = stra[i].make_lower();

         set_at(strName, ::e_type_empty);

      }
      else
      {

         strName = stra[i].Left(iPos).make_lower();

         set_at(strName, stra[i].Mid(iPos + 2));

      }

   }

}

string property_set::_001Replace(const ::string & str) const
{

   return ::papaya::property_set::evaluate(*this, str);

}

::matter * property_set::source_channel()
{

   return set("source_channel").cast < ::matter >();

}

::count property_set::erase_by_name(const id & idName)
{
   return unset(idName);
}

::count property_set::erase_by_name(string_array & stra)
{
   ::count count = 0;
   for(i32 i = 0; i < stra.get_count(); i++)
   {
      count += erase_by_name(stra[i]);
   }
   return count;
}



//
//
//string property_set::eval(const ::string & strParam)
//{
//
//   return property_ptra::eval(strParam);
//
//}
//
//
//string property_set::gen_eval(const ::string & str)
//{
//
//   ASSERT(str[0] == '$' && str.length() >= 2);
//
//   return operator[](&str[1]);
//
//}
//
//
//string property_set::gen_string(const string& str)
//{
//
//   return operator[](str);
//
//}


void property_set::clear()
{

   erase_all();

}


string property_set::implode(const char * pszGlue) const
{

   string str;

   auto p = values();

   if(p)
   {

      str = p->string();

      p++;

   }

   for(; p; p++)
   {

      str += pszGlue;

      str += p->string();

   }

   return str;

}


//property * property_set::find_value(const char * psz) const
//{
//
//   for(const_iterator it = begin(); it != end(); it++)
//   {
//
//      if(it->string() == psz)
//      {
//
//         return (property *) &it->m_var;
//
//      }
//
//   }
//
//   return nullptr;
//
//}
//

//property * property_set::find_value_ci(const char * psz) const
//{
//
//   for(const_iterator it = begin(); it != end(); it++)
//   {
//
//      if(it->string().compare_ci(psz) == 0)
//      {
//
//         return (property *) &it->m_var;
//
//      }
//   }
//
//   return nullptr;
//
//}


property_set::property_set(const property_set & set)
{

   operator = (set);

}


property_set::property_set(property_set && set) :
   property_ptra(::move(set))
{

}


//property_set::property_set(const pair_set_interface & set)
//{
//
//   m_iIndex = 0;
//
//   operator = (set);
//
//}
//
//
//property_set::property_set(const str_str_interface & set)
//{
//
//   m_iIndex = 0;
//
//   operator = (set);
//
//}


property & property_set::at(index iIndex)
{

   return operator[](iIndex);

}


::payload property_set::at(index iIndex) const
{

   return operator[](iIndex);

}


property_set& property_set::operator = (const ::payload & payload)
{

   if (payload.m_etype == e_type_property_set)
   {

      if (is(e_flag_data_struct))
      {

         for (auto & pproperty : *this)
         {

            auto ppropertySource = payload.m_ppropertyset->find(pproperty->m_id);

            if (::is_set(ppropertySource))
            {

               ((::payload &)*pproperty) = ((const ::payload &)*ppropertySource);

            }

         }

      }
      else
      {

         ::papaya::copy((property_ptra &)*this, (const property_ptra &)payload.m_ppropertyset);

      }

   }
   else if (payload.m_etype == e_type_property)
   {

      erase_all();

      set_at(payload.m_pproperty->m_id, *payload.m_pproperty);

   }
   else
   {

      __throw(error_wrong_type);

   }

   return *this;

}


property_set & property_set::operator = (const property_set & set)
{

   if (&set != this)
   {

      ::papaya::copy((property_ptra & )*this, (const property_ptra & ) set);

   }

   return *this;

}


property_set & property_set::add(const property_set & set)
{

   if (&set != this)
   {

      for(auto & pproperty : set)
      {

         add_item(new property(*pproperty));

      }

   }

   return *this;

}


property_set & property_set::merge(const property_set & set)
{

   if (::is_set(set) && &set != this)
   {

      for(auto & pproperty : set)
      {

         id idName = pproperty->name();

         auto ppropertyThis = find(idName);

         if(!pproperty->is_new())
         {

            if(ppropertyThis != nullptr)
            {

               if(ppropertyThis->get_type() == ::e_type_element || pproperty->get_type() == ::e_type_element)
               {

                  operator[](pproperty->name()) = *pproperty;

               }
               else if(ppropertyThis->get_type() == ::e_type_property_set)
               {

                  if(pproperty->get_type() == ::e_type_property_set)
                  {

                     ppropertyThis->propset().merge(pproperty->propset());

                  }
                  else
                  {

                     index i = 0;

                     while(true)
                     {

                        if(!has_property(__string(i)))
                        {

                           operator[](__string(i)) = *pproperty;

                           break;

                        }

                        i++;

                     }

                  }

               }
               else if(operator[](pproperty->name()).is_empty())
               {

                  operator[](pproperty->name()) = *pproperty;

               }
               else
               {

                  try
                  {

                     if(operator[](pproperty->name()) == *pproperty)
                     {

                        continue;

                     }

                  }
                  catch(...)
                  {

                  }

                  operator[](pproperty->name()).payloada().add_unique(operator[](pproperty->name()).payloada());

               }

            }
            else
            {

               operator[](pproperty->name()) = *pproperty;

            }

         }

      }

   }

   return *this;

}


property_set & property_set::operator += (const property_set & set)
{

   return add(set);

}


property_set & property_set::operator |= (const property_set & set)
{

   return merge(set);

}


//property_set & property_set::operator = (const pair_set_interface & set)
//{
//
//   erase_all();
//
//   i32 iCount = set.pair_set_interface_get_count();
//
//   for (i32 i = 0; i < iCount; i++)
//   {
//
//      string strKey = set.pair_set_interface_get_key(i);
//
//      class ::payload payload = set.pair_set_interface_get_value(i);
//
//      set_at(strKey, payload);
//   }
//
//   return *this;
//
//}
//
//
//
//
//
//
//
//
//property_set & property_set::operator = (const str_str_interface & set)
//{
//
//   erase_all();
//
//   i32 iCount = set.str_str_interface_get_count();
//
//   for (i32 i = 0; i < iCount; i++)
//   {
//
//      string strKey = set.str_str_interface_get_key(i);
//
//      class ::payload payload = set.str_str_interface_get_value(i);
//
//      set_at(strKey, payload);
//   }
//
//   return *this;
//
//}


property * property_set::str_find(const property & property) const
{

   for (auto & pproperty : *this)
   {

      if (pproperty->str_compare(property) == 0)
      {

         return pproperty;

      }

   }

   return nullptr;

}


bool property_set::str_contains(const property_set & set) const
{

   for (auto & pproperty : set)
   {

      if (str_find(*pproperty) == nullptr)
      {

         return false;

      }

   }

   return true;

}


bool property_set::contains(const property_set & set) const
{

   property_ptra ptraMatch;

   for (auto & pproperty : set)
   {

      auto ppropertyHere = find(pproperty->name());

      if (!ppropertyHere)
      {

         return false;

      }

      ptraMatch.add(ppropertyHere);

   }

   for(index i = 0; i < set.m_nSize; i++)
   {

      if (*ptraMatch[i] != *set.m_pData[i])
      {

         return false;

      }

   }

   return true;

}


string & property_set::get_http_post(string & strPost) const
{

   auto p = values();

   if(p)
   {

      p->get_http_post(strPost);

      p++;

   }

   for(; p; p++)
   {

      strPost += "&";

      p->get_http_post(strPost);

   }

   return strPost;

}













//stable_property_set::stable_property_set/*()
//{
//
//}
//
//
//stable_property_set::~stable_property_set()
//{
//
//
//}
//
//
//bool stable_property_set::is_new_or_null(id id)
//{
//
//   index iFind = find(id);
//
//   if (iFind < 0)
//   {
//
//      return true;
//
//   }
//
//   if (m_propertyptra[iFind]->is_new())
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
//bool stable_property_set::has_property(id id)
//{
//
//   index iFind = find(id);
//
//   if (iFind < 0)
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}
//
//
//index stable_property_set::find(id id)
//{
//
//   for (index i = 0; i < m_propertyptra.get_size(); i++)
//   {
//
//      if (m_propertyptra[i]->m_id == id)
//      {
//
//         return i;
//
//      }
//
//   }
//
//   return -1;
//
//}
//
//
//property & stable_property_set::set_at(const id & id, const ::payload & payload)
//{
//
//   index iFind = find(id);
//
//   if (iFind < 0)
//   {
//
//      auto pproperty = __new(property(nullptr));
//
//      m_propertyptra.add(pproperty);
//
//      pproperty->m_id = id;
//
//      return *pproperty;
//
//   }
//   else
//   {
//
//      m_propertyptra[iFind]->m_var = payload;
//
//      return *m_propertyptra[iFind];
//
//   }
//
//}
//
//
//property & stable_property_set::operator [](const id & id)
//{
//
//   index iFind;
//
//   if (id.is_integer())
//   {
//
//      iFind = (index) (id.i64());
//
//      if (iFind < 0 || iFind >= m_propertyptra.get_count())
//      {
//
//         __throw(error_index_out_of_bounds);
//
//      }
//
//   }
//   else
//   {
//
//      iFind = find(id);
//
//      if (iFind < 0)
//      {
//
//         return set_at(id, ::e_type_new);
//
//      }
//
//   }
//
//   return *m_propertyptra[iFind];
//
//}


string property_set::get_command_line(const string_array & straKeys) const
{

   string str;

   for(auto & strKey : straKeys)
   {

      property * pproperty = find(strKey);

      if(pproperty == nullptr)
      {

         continue;

      }

      if(str.has_char())
      {

         str += " ";

      }

      string strItem = pproperty->m_id;

      if(strItem.find(" ") >= 0 || strItem.find("\'") >= 0)
      {

         strItem.replace("\"", "\\\"");

         str = "\"" + strItem + "\"";

      }
      else if(strItem.find("\"") >= 0)
      {

         strItem.replace("\'", "\\\'");

         str = "\'" + strItem + "\'";

      }
      else
      {

         str += strItem;

      }

      if(pproperty->is_empty())
      {

         continue;

      }

      str += "=";

      strItem = pproperty->string();

      if(strItem.find(" ") >= 0 || strItem.find("\'") >= 0)
      {

         strItem.replace("\"", "\\\"");

         str = "\"" + strItem + "\"";

      }
      else if(strItem.find("\"") >= 0)
      {

         strItem.replace("\'", "\\\'");

         str = "\'" + strItem + "\'";

      }
      else
      {

         str += strItem;

      }

   }

   return str;

}


string property_set::get_command_line() const
{

   string str;

   for(auto & pproperty : *this)
   {

      if(str.has_char())
      {

         str += " ";

      }

      string strItem(pproperty->m_id);

      if(strItem.find(" ") >= 0 || strItem.find("\'") >= 0)
      {

         strItem.replace("\"", "\\\"");

         str = "\"" + strItem + "\"";

      }
      else if(strItem.find("\"") >= 0)
      {

         strItem.replace("\'", "\\\'");

         str = "\'" + strItem + "\'";

      }
      else
      {

         str += strItem;

      }

      if(pproperty->is_empty())
      {

         continue;

      }

      str += "=";

      strItem = pproperty->string();

      if(strItem.find(" ") >= 0 || strItem.find("\'") >= 0)
      {

         strItem.replace("\"", "\\\"");

         str = "\"" + strItem + "\"";

      }
      else if(strItem.find("\"") >= 0)
      {

         strItem.replace("\'", "\\\'");

         str = "\'" + strItem + "\'";

      }
      else
      {

         str += strItem;

      }

   }

   return str;

}


namespace handle
{


   ini::ini(const ::string & str)
   {

      parse_ini(str);

   }


   ini::ini(::file::file * pfile)
   {

      string str;

      pfile->full_read_string(str);

      parse_ini(str);

   }


   //ini::ini(::acme::application * papp)
   //{

   //   auto preader = Ctx(papp).file().get_reader(papp->get_app_localconfig_folder());

   //   if (preader)
   //   {

   //      string str;

   //      preader->full_read_string(str);

   //      parse_ini(str);

   //   }

   //}


   //localini::localini(::matter * pobject)
   //{

   //   auto preader = Ctx(pobject).file().get_reader(         auto psystem = m_psystem;

//         auto pacmedir = psystem->m_pacmedir;
//
//pacmedir->localconfig() / "this.ini");

   //   if (preader)
   //   {

   //      string str;

   //      preader->full_read_string(str);

   //      parse_ini(str);

   //   }

   //}


} // namespace handle


void property_set::parse_environment_variable(const string_array & straEnvironment)
{

   for (auto & strEnvironment : straEnvironment)
   {

      auto find = strEnvironment.find("=");

      if (find <= 0)
      {

         continue;

      }

      // get the left hand side (LHS) of "=" in the string
      string strKey = strEnvironment.Left(find);

      string strValue = strEnvironment.Mid(find + 1);

      (*this)[strKey] = strValue;

   }

}



