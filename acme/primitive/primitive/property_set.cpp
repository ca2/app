#include "framework.h"
#include "payload.h"
#include "acme/exception/parsing.h"
////#include "acme/exception/exception.h"
//#include "acme/filesystem/file/file.h"
//#include "acme/networking/as_string.h"
#include "acme/platform/acme.h"
#include "acme/platform/sub_system.h"
//#include "acme/primitive/primitive/payload.h"
#include "acme/primitive/string/command_line.h"
#include "acme/primitive/string/str.h"


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

   ::atom atom;

   index i = 0;

   for (auto & item : list)
   {

      if (i % 2 == 0)
      {

         atom = item;

      }
      else if (i % 2 == 1)
      {

         operator[](atom) = item;

      }

      i++;

   }

   if (i % 2 == 1)
   {

      operator[](atom) = ::e_type_empty;

   }

}


property_set::~property_set()
{

}


//atom property_set::get_new_id()
//{
//
//   index iMax = -1;
//
//   for(iterator it = begin(); it != end(); it++)
//   {
//
//      if(it->element1().m_etype == atom::type_integer)
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
//property & property_set::defer_auto_add(atom idName)
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

   for (auto & pproperty : *this)
   {

      if (pproperty->case_insensitive_order(payload) == 0)
      {

         return pproperty;

      }

   }

   return nullptr;

}


property * property_set::find_value_ci(const ::scoped_string & scopedstr) const
{

   for (auto & pproperty : *this)
   {

      if (pproperty->case_insensitive_equals(scopedstr))
      {

         return pproperty;

      }

   }

   return nullptr;

}




property * property_set::find_payload(const ::payload & payload) const
{

   for (auto & pproperty : *this)
   {

      if (*pproperty == payload)
      {

         return pproperty;

      }

   }

   return nullptr;

}


property * property_set::find_payload(const ::scoped_string & scopedstr) const
{

   for (auto & pproperty : *this)
   {

      if (*pproperty == scopedstr)
      {

         return pproperty;

      }

   }

   return nullptr;

}


bool property_set::contains_value_ci(const ::payload & payload, ::count countMin, ::count countMax) const
{
   ::count count = 0;
   while ((count < countMin || (countMax >= 0 && count <= countMax)) && find_value_ci(payload) != nullptr)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}




bool property_set::contains_value_ci(const ::scoped_string & scopedstr, ::count countMin, ::count countMax) const
{
   ::count count = 0;
   while ((count < countMin || (countMax >= 0 && count <= countMax)) && find_value_ci(scopedstr) != nullptr)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}


bool property_set::contains_payload(const ::payload & payload, ::count countMin, ::count countMax) const
{
   ::count count = 0;
   while ((count < countMin || (countMax >= 0 && count <= countMax)) && (find_payload(payload)) != nullptr)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}


bool property_set::contains_payload(const ::scoped_string & scopedstr, ::count countMin, ::count countMax) const
{
   ::count count = 0;
   while ((count < countMin || (countMax >= 0 && count <= countMax)) && find_payload(scopedstr) != nullptr)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}


bool property_set::erase_first_value_ci(const ::payload & payload)
{

   property * pproperty = find_value_ci(payload);

   if (pproperty != nullptr)
   {

      return erase_by_name(pproperty->m_atom);

   }

   return false;

}


bool property_set::erase_first_value_ci(const ::scoped_string & scopedstr)
{

   property * pproperty = find_value_ci(scopedstr);

   if (pproperty != nullptr)
   {

      return erase_by_name(pproperty->m_atom);

   }

   return false;

}


bool property_set::erase_first_value(const ::payload & payload)
{

   property * pproperty = find_payload(payload);

   if (pproperty != nullptr)
   {

      return erase_by_name(pproperty->m_atom);

   }

   return false;

}


bool property_set::erase_first_value(const ::scoped_string & scopedstr)
{

   property * pproperty = find_payload(scopedstr);

   if (pproperty != nullptr)
   {

      return erase_by_name(pproperty->m_atom);

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


::count property_set::erase_value_ci(const ::scoped_string & scopedstr, ::count countMin, ::count countMax)
{

   ::count count = 0;

   if (contains_value_ci(scopedstr, countMin, countMax))
   {

      while (conditional(countMax >= 0, count < countMax) && erase_first_value_ci(scopedstr))
      {

         count++;

      }

   }

   return count;

}


::count property_set::erase_value(const ::payload & payload, ::count countMin, ::count countMax)
{

   ::count count = 0;

   if (contains_payload(payload, countMin, countMax))
   {

      while (conditional(countMax >= 0, count < countMax && erase_first_value(payload)))
      {

         count++;

      }

   }

   return count;

}


::count property_set::erase_value(const ::scoped_string & scopedstr, ::count countMin, ::count countMax)
{

   ::count count = 0;

   if (contains_payload(scopedstr, countMin, countMax))
   {

      while (conditional(countMax >= 0, count < countMax) && erase_first_value(scopedstr))
      {

         count++;

      }

   }

   return count;

}


::count property_set::unset(const atom & idName)
{

   ::count c = 0;

   ::index iFind = 0;

   while (true)
   {

      iFind = index_of(idName, iFind);

      if (iFind < 0)
      {

         return c;

      }

      erase_at(iFind);

      c++;

   }

}


bool property_set::is_new(const atom & idName) const
{

   const property * pproperty = find(idName);

   if (pproperty == nullptr)
   {

      return true;

   }

   return pproperty->is_new();

}


bool property_set::is_null(const atom & idName) const
{

   const property * pproperty = find(idName);

   if (pproperty == nullptr)
   {

      return true;

   }

   return pproperty->is_null();

}


bool property_set::is_new_or_null(const atom & idName) const
{

   const property * pproperty = find(idName);

   if (pproperty == nullptr)
   {

      return true;

   }

   return pproperty->is_new_or_null();

}


bool property_set::is_empty(const atom & idName) const
{

   const property * pproperty = find(idName);

   if (pproperty == nullptr)
   {

      return true;

   }

   return pproperty->is_empty();

}


void property_set::_008ParseCommandLine(const ::scoped_string & scopedstrCmdLineParam, ::payload & payloadFile)
{

   string strApp;

   _008Parse(false, scopedstrCmdLineParam, payloadFile, strApp);

}


void property_set::_008ParseCommandFork(const ::scoped_string & scopedstrCmdLineParam, ::payload & payloadFile, string & strApp)
{

   _008Parse(true, scopedstrCmdLineParam, payloadFile, strApp);

}


void property_set::_008ParseCommandArguments(string_array & straArguments, ::payload & payloadFile, string & strApp)
{

   _008ParseArguments(true, straArguments, payloadFile, strApp);

}


void property_set::_008AddArgumentPairs(::string_array & straArguments)
{

   for (::index i = 0; i < straArguments.get_size() - 1; i++)
   {

      string strThisArgument = straArguments[i];

      string strNextArgument = straArguments[i + 1];

      if (strThisArgument.begins_eat("-"))
      {

         if (strThisArgument.has_char())
         {

            if (strNextArgument.case_insensitive_order("YES") == 0)
            {

               _008Add(strThisArgument, "true");

               straArguments.erase(i, 2);

               i--;

            }
            else if (strNextArgument.case_insensitive_order("NO") == 0)
            {

               _008Add(strThisArgument, "false");

               straArguments.erase(i, 2);

               i--;

            }
            else if (strNextArgument.case_insensitive_order("TRUE") == 0)
            {

               _008Add(strThisArgument, "true");

               straArguments.erase(i, 2);

               i--;

            }
            else if (strNextArgument.case_insensitive_order("FALSE") == 0)
            {

               _008Add(strThisArgument, "false");

               straArguments.erase(i, 2);

               i--;

            }

         }

      }

   }

}


void property_set::_008AddArgumentOrFile(bool & bColon, ::payload & payloadFile, const ::string & strArgument)
{

   if (strArgument == ":")
   {

      bColon = true;

      return;

   }

   if (strArgument.case_insensitive_begins("-"))
   {

      _008AddArgument(strArgument.substr(1));

   }
   else if (bColon)
   {

      _008AddArgument(strArgument);

   }
   else
   {

      auto iQuote = strArgument.offset_of(strArgument.find_first_character_in("\"'"));
      
      auto iEqual = strArgument.offset_of(strArgument.find_first_character_in("="));

      if (iEqual > 0 && (iQuote < 0 || iQuote > iEqual))
      {

         _008AddArgument(strArgument);

      }
      else if (payloadFile.is_empty())
      {

         payloadFile = strArgument;

      }
      else
      {

         payloadFile.stra().add(strArgument);

      }

   }

}


void property_set::_008AddArgument(const ::string & strArg)
{

   auto pFindEqual = strArg.find('=');

   auto pFindQuote = strArg.find('\"');

   if (::is_set(pFindEqual))
   {

      string strValue;

      strValue = strArg(pFindEqual + 1);

      if (pFindEqual + 1 == pFindQuote)
      {

         auto range = strValue();

         strValue = range.consume_quoted_value();

      }

      string strKey = strArg(0, pFindEqual);

      _008Add(strKey, strValue);

   }
   else
   {

      _008Add(strArg, nullptr);

   }

}


void property_set::_008Add(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrValue)
{

   string_array straKey;

   straKey.explode(".", scopedstrKey);

   if (straKey.is_empty())
   {

      return;

   }

   property_set * pset = this;

   i32 i = 0;

   while (i < straKey.get_upper_bound())
   {

      pset = &(*pset)[straKey[i]].property_set_reference();

      i++;

   }

   if (::is_null(scopedstrValue))
   {

      pset->operator[](straKey[i]).set_type(::e_type_key_exists, false);

   }
   else if (pset->has_property(straKey[i]) && pset->operator[](straKey[i]) != scopedstrValue)
   {

      pset->operator[](straKey[i]).stra().add(scopedstrValue);

   }
   else
   {

      pset->operator[](straKey[i]) = scopedstrValue;

   }

}


void property_set::_008Parse(bool bApp, const ::scoped_string & scopedstrCmdLine, ::payload & payloadFile, string & strApp)
{

   if (scopedstrCmdLine.is_empty())
   {

      return;

   }

   //string_array stra = get_c_args_for_c(pszCmdLine);
   //string_array stra = get_c_args_from_c(pszCmdLine);

   auto range = scopedstrCmdLine();

   auto straArguments = get_c_args_from_string(range);

   int i = 0;

   if (bApp && straArguments.get_count() > 0)
   {

      strApp = straArguments[0];

      i++;

   }

   _008AddArgumentPairs(straArguments);

   bool bColon = false;

   for (; i < straArguments.get_size(); i++)
   {

      string strArgument = straArguments[i];

      _008AddArgumentOrFile(bColon, payloadFile, strArgument);

   }

}


void property_set::_008ParseArguments(bool bApp, ::string_array & straArguments, ::payload & payloadFile, string & strApp)
{

   int i = 0;

   if (bApp && straArguments.has_element())
   {

      strApp = straArguments.first();

      i++;

   }

   _008AddArgumentPairs(straArguments);

   bool bColon = false;

   for (; i < straArguments.get_size(); i++)
   {

      string strArgument = straArguments[i];

      _008AddArgumentOrFile(bColon, payloadFile, strArgument);

   }

}


//void property_set_skip_network_payload(const char *& pszJson)
//{
//
//   property_set_skip_network_payload(pszJson, pszJson + strlen(pszJson) - 1);
//
//}


void property_set_skip_network_payload(::const_ansi_range & range)
{

   ::str::consume_spaces(range, 0);

   if (*range.m_begin == '\0')
   {

      return;

   }

   ::str::consume(range, "{");

   ::str::consume_spaces(range, 0);

   if (*range.m_begin == '}')
   {

      range.m_begin++;

      return;

   }

   while (true)
   {

      ::atom atom;

      property_skip_network_payload_id(range);

      property_skip_network_payload_value(range);

      ::str::consume_spaces(range, 0);

      if (*range.m_begin == ',')
      {

         range.m_begin++;

         continue;

      }
      else if (*range.m_begin == '}')
      {

         range.m_begin++;

         return;

      }
      else
      {

         string str = "not expected character : ";

         str += range.m_begin;

         throw ::exception(error_failed, str);

      }

   }

}


void property_set::parse_ini(const ::string & strIni)
{

   string_array stra;

   stra.add_lines(strIni);

   property_set * pset = this;

   for (auto & strLine : stra)
   {

      strLine.trim();

      if (strLine.is_empty())
      {

         continue;

      }

      if (strLine.begins_eat("["))
      {

         strLine.trim_right("]");

         pset = &(property_set &)operator[](strLine);

      }
      else
      {

         string strKey;

         strKey = ::str::token(strLine, "=");

         if (strKey.has_char())
         {

            strKey.trim();

            strLine.trim();

            pset->operator[](strKey) = strLine;

         }

      }

   }

}


void property_set::parse_network_payload(const ::string & strNetworkPayload)
{

#ifdef LINUX

   uselocale(::acme::acme::g_p->m_psubsystem->m_localeC);

#endif

   auto range = strNetworkPayload();

   parse_network_payload(range);

}


//void property_set::parse_network_payload(::const_ansi_range & range)
//{
//
//#ifdef LINUX
//   uselocale(::acme::acme::g_p->m_psubsystem->m_localeC);
//#endif
//
//   parse_network_payload(pszJson, pszJson + strlen(pszJson) - 1);
//
//}


void property_set::parse_network_payload(::const_ansi_range & range)
{


#ifdef LINUX
   uselocale(::acme::acme::g_p->m_psubsystem->m_localeC);
#endif

   ::str::consume_spaces(range, 0);

   if (*range.m_begin == '\0')
   {

      return;

   }

   ::str::consume(range, "{");

   ::str::consume_spaces(range, 0);

   if (*range.m_begin == '}')
   {
      
      range.m_begin++;

      return;

   }

   while (true)
   {

      ::atom atom;

      ::property_parse_network_payload_id(atom, range);

      auto & property = operator[](atom);

      ::property_parse_network_payload_value(property, range);

      ::str::consume_spaces(range, 0);

      if (*range.m_begin == ',')
      {

         range.m_begin++;

         continue;

      }
      else if (*range.m_begin == '}')
      {

         range.m_begin++;

         return;

      }
      else
      {

         string str = "not expected character : ";

         str += range.m_begin;

         throw ::parsing_exception(str);

      }

   }

}


string & property_set::get_network_payload(string & str, bool bNewLine) const
{

   str += "{";

   auto p = begin();

   if (p)
   {

      while (true)
      {

         (*p)->get_network_payload(str, bNewLine);

         p++;

         if (p >= end())
         {

            break;

         }

         if (bNewLine)
         {

            str += ", \r\n";

         }
         else
         {

            str += ", ";

         }

      }

   }

   if (bNewLine)
   {

      str += "\r\n";

   }

   str += "}";


   return str;

}


void property_set::parse_network_arguments(const ::scoped_string & scopedstrUriOrNetworkArguments)
{

   if (scopedstrUriOrNetworkArguments.is_empty())
   {

      return;

   }

   const char * pszNetworkArguments = strchr(scopedstrUriOrNetworkArguments.begin(), '?');

   if (::is_empty(pszNetworkArguments))
   {

      return _parse_network_arguments(scopedstrUriOrNetworkArguments);

   }
   else
   {

      return _parse_network_arguments(pszNetworkArguments + 1);

   }

}


void property_set::_parse_network_arguments(const ::scoped_string & scopedstrNetworkArguments)
{

   if (scopedstrNetworkArguments.is_empty())
   {

      return;

   }

   const ::ansi_character * pszArgument = scopedstrNetworkArguments.begin();

   const ::ansi_character * pszArgumentEnd;

   const ::ansi_character * pszKeyEnd;

   string strKey;

   while (true)
   {

      pszArgumentEnd = strchr(pszArgument, '&');

      pszKeyEnd = strchr(pszArgument, '=');

      if (pszArgumentEnd == nullptr)
      {

         if (pszKeyEnd == nullptr)
         {

            strKey = ::url::decode({ pszArgument, scopedstrNetworkArguments.size() - (pszArgument - scopedstrNetworkArguments.begin()) });

            _008Add(strKey, "");

         }
         else
         {

            string strKey = ::url::decode({ pszArgument, pszKeyEnd - pszArgument });

            string strValue = ::url::decode({ pszKeyEnd + 1, scopedstrNetworkArguments.size() - (pszKeyEnd + 1 - scopedstrNetworkArguments.begin()) });

            _008Add(strKey, strValue);

         }

         return;

      }

      if (pszKeyEnd == nullptr || pszKeyEnd > pszArgumentEnd)
      {

         strKey = ::url::decode({ pszArgument, pszArgumentEnd - pszArgument });

         _008Add(strKey, "");

      }
      else
      {

         string strKey = ::url::decode({ pszArgument, pszKeyEnd - pszArgument });

         string strValue = ::url::decode({ pszKeyEnd + 1, pszArgumentEnd - (pszKeyEnd + 1) });

         _008Add(strKey, strValue);

      }

      pszArgument = pszArgumentEnd + 1;

   }

}


void property_set::parse_network_headers(const ::scoped_string & scopedstrHeaders)
{

   string_array stra;

   stra.add_tokens(scopedstrHeaders, "\r\n", true);

   string strName;

   for (i32 i = 0; i < stra.get_size(); i++)
   {

      auto pPos = stra[i].find(":");

      if (::is_null(pPos))
      {

         strName = stra[i].make_lower();

         set_at(strName, ::e_type_empty);

      }
      else
      {

         strName = stra[i].substr(0, pPos).make_lower();

         set_at(strName, stra[i](0, pPos + 2));

      }

   }

}


string property_set::_001Replace(const ::string & str) const
{

   return evaluate(str);

}


::particle * property_set::source_channel()
{

   return set("source_channel").cast < ::particle >();

}


::count property_set::erase_by_name(const atom & idName)
{

   return unset(idName);

}


::count property_set::erase_by_name(string_array & stra)
{

   ::count count = 0;

   for (i32 i = 0; i < stra.get_count(); i++)
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


string property_set::implode(const ::scoped_string & scopedstrGlue) const
{

   string str;

   auto p = begin();

   if (p)
   {

      while (true)
      {

         str += **p;

         p++;

         if (!p)
         {

            break;

         }

         str += scopedstrGlue;

      }

   }

   return str;

}


//property * property_set::find_payload(const ::scoped_string & scopedstr) const
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

//property * property_set::find_value_ci(const ::scoped_string & scopedstr) const
//{
//
//   for(const_iterator it = begin(); it != end(); it++)
//   {
//
//      if(it->string().case_insensitive_order(psz) == 0)
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
   property_ptra(::transfer(set))
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


property_set & property_set::operator = (const ::payload & payload)
{

   if (payload.m_etype == e_type_property_set)
   {

      //if (::element::has(e_flag_data_struct))
      //{

      //   for (auto & pproperty : *this)
      //   {

      //      auto ppropertySource = payload.m_ppropertyset->find(pproperty->m_atom);

      //      if (::is_set(ppropertySource))
      //      {

      //         ((::payload &)*pproperty) = ((const ::payload &)*ppropertySource);

      //      }

      //   }

      //}
      //else
      //{

      ::acme::copy((property_ptra &)*this, (const property_ptra &)*payload.m_ppropertyset);

      //      }

   }
   else if (payload.m_etype == e_type_property)
   {

      erase_all();

      set_at(payload.m_pproperty->m_atom, *payload.m_pproperty);

   }
   else
   {

      throw ::exception(error_wrong_type);

   }

   return *this;

}


property_set & property_set::operator = (const property_set & set)
{

   if (&set != this)
   {

      ::acme::copy((property_ptra &)*this, (const property_ptra &)set);

   }

   return *this;

}


property_set & property_set::append(const property_set & set)
{

   if (&set != this)
   {

      for (auto & pproperty : set)
      {

         add_item(memory_new property(*pproperty));

      }

   }

   return *this;

}


property_set & property_set::merge(const property_set & set)
{

   if (::is_reference_set(set) && &set != this)
   {

      for (auto & pproperty : set)
      {

         atom idName = pproperty->name();

         auto ppropertyThis = find(idName);

         if (!pproperty->is_new())
         {

            if (ppropertyThis != nullptr)
            {

               if (ppropertyThis->get_type() == ::e_type_element || pproperty->get_type() == ::e_type_element)
               {

                  operator[](pproperty->name()) = *pproperty;

               }
               else if (ppropertyThis->get_type() == ::e_type_property_set)
               {

                  if (pproperty->get_type() == ::e_type_property_set)
                  {

                     ppropertyThis->propset().merge(pproperty->propset());

                  }
                  else
                  {

                     index i = 0;

                     while (true)
                     {

                        if (!has_property(::as_string(i)))
                        {

                           operator[](::as_string(i)) = *pproperty;

                           break;

                        }

                        i++;

                     }

                  }

               }
               else if (operator[](pproperty->name()).is_empty())
               {

                  operator[](pproperty->name()) = *pproperty;

               }
               else
               {

                  try
                  {

                     if (operator[](pproperty->name()) == *pproperty)
                     {

                        continue;

                     }

                  }
                  catch (...)
                  {

                  }

                  operator[](pproperty->name()).payloada().append_unique(operator[](pproperty->name()).payloada());

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


property_set & property_set::merge(const property & property)
{

   if (property.get_type() == e_type_property_set)
   {

      merge(*property.m_ppropertyset);

   }
   else
   {

      set_at(property.m_atom, property);

   }

   return *this;

}


property_set & property_set::operator += (const property_set & set)
{

   return append(set);

}


property_set & property_set::operator |= (const property_set & set)
{

   return merge(set);

}


bool property_set::contains_value_ci(const ::payload & payload) const { return find_value_ci(payload) != nullptr; }
bool property_set::contains_value_ci(const ::scoped_string & scopedstr) const { return find_value_ci(scopedstr) != nullptr; }

bool property_set::contains_payload(const ::payload & payload) const { return find_payload(payload) != nullptr; }
bool property_set::contains_payload(const ::scoped_string & scopedstr) const { return find_payload(scopedstr) != nullptr; }




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

   for (auto & p : *this)
   {

      if (*ptraMatch[offset_of(&p)] != *p)
      {

         return false;

      }

   }

   return true;

}


string & property_set::get_network_arguments(string & strNetworkArguments) const
{

   auto p = begin();

   while (!is_end(p))
   {

      if (strNetworkArguments.has_char())
      {

         strNetworkArguments += "&";

      }

      (*p)->get_network_arguments(strNetworkArguments);

      p++;

   }

   return strNetworkArguments;

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
//bool stable_property_set::is_new_or_null(atom atom)
//{
//
//   auto pFind = find(atom);
//
//   if (::is_null(pFind))
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
//bool stable_property_set::has_property(atom atom)
//{
//
//   auto pFind = find(atom);
//
//   if (::is_null(pFind))
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
//index stable_property_set::find(atom atom)
//{
//
//   for (index i = 0; i < m_propertyptra.get_size(); i++)
//   {
//
//      if (m_propertyptra[i]->m_atom == atom)
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
//property & stable_property_set::set_at(const atom & atom, const ::payload & payload)
//{
//
//   auto pFind = find(atom);
//
//   if (::is_null(pFind))
//   {
//
//      auto pproperty = __new(property(nullptr));
//
//      m_propertyptra.add(pproperty);
//
//      pproperty->m_atom = atom;
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
//property & stable_property_set::operator [](const atom & atom)
//{
//
//   index iFind;
//
//   if (atom.is_integer())
//   {
//
//      iFind = (index) (atom.i64());
//
//      if (::is_null(pFind) || iFind >= m_propertyptra.get_count())
//      {
//
//         throw ::exception(error_index_out_of_bounds);
//
//      }
//
//   }
//   else
//   {
//
//      iFind = find(atom);
//
//      if (::is_null(pFind))
//      {
//
//         return set_at(atom, ::e_type_new);
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

   for (auto & strKey : straKeys)
   {

      property * pproperty = find(strKey);

      if (pproperty == nullptr)
      {

         continue;

      }

      if (str.has_char())
      {

         str += " ";

      }

      string strItem = pproperty->m_atom;

      if (strItem.contains(" ") || strItem.contains("\'"))
      {

         strItem.replace_with("\\\"", "\"");

         str = "\"" + strItem + "\"";

      }
      else if (strItem.contains("\""))
      {

         strItem.replace_with("\\\'", "\'");

         str = "\'" + strItem + "\'";

      }
      else
      {

         str += strItem;

      }

      if (pproperty->is_empty())
      {

         continue;

      }

      str += "=";

      strItem = *pproperty;

      if (strItem.contains(" ") || strItem.contains("\'"))
      {

         strItem.replace_with("\\\"", "\"");

         str = "\"" + strItem + "\"";

      }
      else if (strItem.contains("\""))
      {

         strItem.replace_with("\\\'", "\'");

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

   for (auto & pproperty : *this)
   {

      if (str.has_char())
      {

         str += " ";

      }

      string strItem(pproperty->m_atom);

      if (strItem.contains(" ") || strItem.contains("\'"))
      {

         strItem.replace_with("\\\"", "\"");

         str = "\"" + strItem + "\"";

      }
      else if (strItem.contains("\""))
      {

         strItem.replace_with("\\\'", "\'");

         str = "\'" + strItem + "\'";

      }
      else
      {

         str += strItem;

      }

      if (pproperty->is_empty())
      {

         continue;

      }

      str += "=";

      strItem = *pproperty;

      if (strItem.contains(" ") || strItem.contains("\'"))
      {

         strItem.replace_with("\\\"", "\"");

         str = "\"" + strItem + "\"";

      }
      else if (strItem.contains("\""))
      {

         strItem.replace_with("\\\'", "\'");

         str = "\'" + strItem + "\'";

      }
      else
      {

         str += strItem;

      }

   }

   return str;

}




void property_set::parse_environment_variable(const string_array & straEnvironment)
{

   for (auto & strEnvironment : straEnvironment)
   {

      auto pFind = strEnvironment.find("=");

      if (pFind <= strEnvironment.begin())
      {

         continue;

      }

      // get the left hand side (LHS) of "=" in the string
      string strItem = strEnvironment(0, pFind);

      string strPayload = strEnvironment(pFind + 1);

      auto pszItem = strItem.c_str();
      
      auto pszPayload = strPayload.c_str();

      (*this)[strItem] = strPayload;

   }

}



bool property_set::payload_bool(const atom & atom, bool bDefault) const
{

   auto pproperty = find(atom);

   if (::is_null(pproperty))
   {

      return bDefault;

   }

   return pproperty->get_bool(bDefault);

}


::string property_set::payload_string(const atom & atom, const ::string & strDefault) const
{

   auto pproperty = find(atom);

   if (::is_null(pproperty))
   {

      return strDefault;

   }

   return *pproperty;

}



::file::path property_set::payload_file_path(const atom & atom, const ::file::path & pathDefault) const
{

   auto pproperty = find(atom);

   if (::is_null(pproperty))
   {

      return pathDefault;

   }

   return *pproperty;

}




//::payload matter::topic(const ::atom & atom)
//{
//
//   auto pproperty = fetch_property(atom);
//
//   if (!pproperty)
//   {
//
//      throw ::exception(error_resource);
//
//   }
//
//   return pproperty;
//
//}


string property_set::as_string(const ::scoped_string& scopedstrSeparator1, const ::scoped_string& scopedstrSeparator2)
{

   ::string str;

   for (auto & pproperty : *this)
   {
      
      str += pproperty->m_atom.as_string();

      str += scopedstrSeparator1;

      str += pproperty->as_string();

      str += scopedstrSeparator2;

   }

   return str;

}


::index property_set::index_of(const ::atom & atom, ::index i) const
{

   auto p = this->m_begin + i;

   for (; p < this->m_end; p++)
   {

      if (p[i]->m_atom == atom)
      {

         return i;

      }

   }

   return -1;

}


::property * property_set::find(const ::atom & atom, ::index iStart) const
{

   auto p = this->m_begin + iStart;

   for (; p < this->m_end; p++)
   {

      if ((*p)->m_atom == atom)
      {

         return *p;

      }

   }

   return nullptr;

}


property & property_set::get(const ::atom & atom, ::index iStart)
{

   auto pproperty = find(atom, iStart);

   if (!pproperty)
   {

      pproperty = memory_new property(atom);

      add_item(pproperty);

   }

   return *pproperty;

}


//::property * property_set::find_index(::iptr i) const
//{
//
//   auto p = this->m_begin;
//
//   for (; p < this->m_end; p++)
//   {
//
//      if ((*p)->m_atom.as_iptr() == i)
//      {
//
//         return *p;
//
//      }
//
//   }
//
//   return nullptr;
//
//}


//property & property_set::get_index(::iptr i)
//{
//
//   while (i >= this->size())
//   {
//
//      auto pproperty = memory_new property(::as_string(this->size()));
//
//      add_item(pproperty);
//
//   }
//
//   return *(const_cast <property_set *> (this))->m_begin[i];
//
//}


::payload property_set::operator()(const ::atom & atom, const ::payload & varDefault) const
{

   auto pproperty = find(atom);

   if (!pproperty)
   {

      return varDefault;

   }

   return pproperty;

}


::payload & property_set::topic(const atom & atom)
{

   return set(atom);

}


::payload & property_set::set(const ::atom & atom)
{

   auto pproperty = find(atom);

   if (!pproperty)
   {

      pproperty = memory_new property(atom);

      add_item(pproperty);

   }

   return *pproperty;

}






//CLASS_DECL_ACME string atom::operator + (const atom & atom) const
//{
//
//   if (is_integer())
//   {
//
//      if (atom.is_integer())
//      {
//
//         return (iptr)(m_i + atom.m_i);
//
//      }
//      else if (atom.is_text())
//      {
//
//         return as_string(m_i) + "." + string(atom.m_psz);
//
//      }
//      else
//      {
//
//         return *this;
//
//      }
//
//   }
//   else if (atom.is_integer())
//   {
//
//      if (is_text())
//      {
//
//         return string(m_psz) + "." + as_string(atom.m_i);
//
//      }
//      else
//      {
//
//         return atom;
//
//      }
//
//   }
//   else if (is_text())
//   {
//
//      if (atom.is_text())
//      {
//
//         return string(m_psz) + string(atom.m_psz);
//
//      }
//      else
//      {
//
//         return *this;
//
//      }
//
//   }
//   else if (atom.is_text())
//   {
//
//      return atom;
//
//   }
//   else
//   {
//
//      return ::atom();
//
//   }
//
//}


bool property_set::has_property(atom idName) const
{

   if (::is_null(this))
   {

      return false;

   }

   const property * pproperty = find(idName);

   return pproperty != nullptr && pproperty->m_etype != ::e_type_new;

}


bool property_set::is_true(atom idName, bool bDefault) const
{

   const property * pproperty = find(idName);

   if (pproperty == nullptr)
   {

      return bDefault;

   }

   return pproperty->is_true(bDefault);

}


::payload property_set::value(const atom & idName) const
{

   property * pproperty = find(idName);

   if (pproperty == nullptr)
   {

      return ::error_not_found;

   }

   return *pproperty;

}


::payload property_set::value(const atom & idName, ::payload varDefault) const
{

   property * pproperty = find(idName);

   if (pproperty == nullptr)
   {

      return varDefault;

   }

   return *pproperty;

}



// ::property_set set;
//
// set["var5"] = "searching value";
//
// str = "SELECT field1, field2, field3 FROM table1 WHERE table1.field5 = '$var5'"
//
// real-ization: "SELECT field1, field2, field3 FROM table1 WHERE table1.field5 = 'searching value'"
string property_set::evaluate(const ::string & strSource) const
{

   string str(strSource);

   char ch;

   char chNext;

   for (auto pPos = str.c_str(); pPos < str.end(); pPos++)
   {

      ch = *pPos;

      if (pPos + 1 < str.end())
      {

         chNext = *(pPos + 1);

      }
      else
      {

         chNext = '\0';

      }

      if (ch == '\\')
      {

         pPos++;

         continue;

      }
      else if (ch == '{' && chNext == '$')
      {

         auto pEnd = str(pPos + 1).find('}');

         if (::is_null(pEnd))
         {

            //error

            break;

         }

         string strKey(pPos + 2, pEnd - pPos - 2);

         string strEval;

         if (get_string(strEval, strKey))
         {

            str = str(0, pPos) + strEval + str(0, pEnd + 1);

            pPos += strEval.length() - 1;

         }
         else
         {

            pPos = pEnd;

         }


      }
      else if (ch == '$')
      {

         if (!(ansi_char_isalpha(chNext) || chNext == '_'))
         {

            // error

            break;

         }

         auto pStart = pPos;

         auto pEnd = pStart + 2;

         for (; pEnd < str.end(); pEnd++)
         {

            ch = *pEnd;

            if (!(ansi_char_isalpha(ch) || ch == '_' || ansi_char_isdigit(ch)))
            {

               break;

            }

         }

         string strExpression(pStart, pEnd - pStart);

         string strEval;

         if (get_evaluation(strEval, strExpression))
         {

            str = str(0, pPos) + strEval + str(pEnd);

            pPos += strEval.length() - 1;

         }
         else
         {

            pPos = pEnd;

         }

      }

   }

   return str;

}


bool property_set::get_evaluation(::string & str, const ::string & strExpression) const
{

   return get_string(str, strExpression);

}


