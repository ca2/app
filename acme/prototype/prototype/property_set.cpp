#include "framework.h"
#include "payload.h"
#include "acme/exception/parsing.h"
////#include "acme/exception/exception.h"
//#include "acme/filesystem/file/file.h"
//#include "acme/networking/as_string.h"
#include "acme/platform/acme.h"
#include "acme/platform/platform.h"
#include "acme/platform/system.h"
//#include "acme/prototype/prototype/payload.h"
#include "acme/prototype/string/command_line.h"
#include "acme/prototype/string/str.h"


#if defined(LINUX) || defined(FREEBSD) || defined(OPENBSD)
#include <locale.h>
#elif defined(__APPLE__)
#include <xlocale.h>
#endif

#ifdef WINDOWS
extern _locale_t g_localeC;
#else
extern locale_t g_localeC;
#endif


property_set::property_set(::std::initializer_list < ::payload > list)
{

   ::atom atom;

   ::collection::index i = 0;

   for (auto & item : list)
   {

      if (i % 2 == 0)
      {

         atom = item.as_atom();

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
//property & property_set::defer_auto_add(atom atom)
//{
//
//   return *add(atom);
//
//}


bool property_set::is_set_empty(::collection::count countMinimum) const
{
   return property_count() < countMinimum;
}

bool property_set::has_properties(::collection::count countMinimum) const
{
   return property_count() >= countMinimum;
}


::collection::index property_set::index_of_case_insensitive_payload(const ::payload & payload, ::collection::index iStart) const
{

   for (::collection::index iIndex = iStart; iIndex < this->size(); iIndex++)
   {

      auto pproperty = this->element_at(iIndex);

      if (pproperty->case_insensitive_order(payload) == 0)
      {

         return iIndex;

      }

   }

   return -1;

}


::collection::index property_set::index_of_case_insensitive_string(const ::scoped_string & scopedstr, ::collection::index iStart) const
{

   for (::collection::index iIndex = iStart; iIndex < this->size(); iIndex++)
   {

      auto pproperty = this->element_at(iIndex);

      if (pproperty->case_insensitive_equals(scopedstr))
      {

         return iIndex;

      }

   }

   return -1;

}


::collection::index property_set::index_of_payload(const ::payload & payload, ::collection::index iStart) const
{

   for (::collection::index iIndex = iStart; iIndex < this->size(); iIndex++)
   {

      auto pproperty = this->element_at(iIndex);

      if (*pproperty == payload)
      {

         return iIndex;

      }

   }

   return -1;

}


::collection::index property_set::index_of_string(const ::scoped_string & scopedstr, ::collection::index iStart) const
{

   for (::collection::index iIndex = iStart; iIndex < this->size(); iIndex++)
   {

      auto pproperty = this->element_at(iIndex);

      if (*pproperty == scopedstr)
      {

         return iIndex;

      }

   }

   return -1;

}


bool property_set::case_insensitive_contains_payload_count(const ::payload & payload, ::collection::count countMin, ::collection::count countMax) const
{
   ::collection::count count = 0;
   ::collection::index iIndex = -1;
   while ((count < countMin || (countMax >= 0 && count <= countMax)) && (iIndex = index_of_case_insensitive_payload(payload, iIndex + 1)>= 0))
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}




bool property_set::case_insensitive_contains_string_count(const ::scoped_string & scopedstr, ::collection::count countMin, ::collection::count countMax) const
{
   ::collection::count count = 0;
   ::collection::index iIndex = -1;
   while ((count < countMin || (countMax >= 0 && count <= countMax)) && (iIndex = index_of_case_insensitive_string(scopedstr, iIndex + 1) >= 0))
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}


bool property_set::contains_payload_count(const ::payload & payload, ::collection::count countMin, ::collection::count countMax) const
{
   ::collection::count count = 0;
   ::collection::index iIndex = -1;
   while ((count < countMin || (countMax >= 0 && count <= countMax)) && (iIndex = index_of_payload(payload, iIndex + 1))>= 0)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}


bool property_set::contains_string_count(const ::scoped_string & scopedstr, ::collection::count countMin, ::collection::count countMax) const
{
   ::collection::count count = 0;
   ::collection::index iIndex = -1;
   while ((count < countMin || (countMax >= 0 && count <= countMax)) && (iIndex= index_of_string(scopedstr))>= 0)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}


bool property_set::case_insensitive_erase_first_payload(const ::payload & payload, ::collection::index iStart)
{

   auto iIndex = index_of_case_insensitive_payload(payload, iStart);

   if (iIndex < 0)
   {

      return false;

   }

   this->erase_at(iIndex);

   return true;

}


bool property_set::case_insensitive_erase_first_string(const ::scoped_string & scopedstr, ::collection::index iStart)
{

   auto iIndex = index_of_case_insensitive_string(scopedstr, iStart);

   if (iIndex < 0)
   {

      return false;

   }

   this->erase_at(iIndex);

   return true;

}


bool property_set::erase_first_payload(const ::payload & payload, ::collection::index iStart)
{

   auto iIndex = index_of_payload(payload, iStart);

   if (iIndex < 0)
   {

      return false;

   }

   this->erase_at(iIndex);

   return true;

}


bool property_set::erase_first_string(const ::scoped_string & scopedstr, ::collection::index iStart)
{

   auto iIndex = index_of_string(scopedstr, iStart);

   if (iIndex < 0)
   {

      return false;

   }

   this->erase_at(iIndex);

   return true;

}


::collection::count property_set::case_insensitive_erase_payload_count(const ::payload & payload, ::collection::count countMin, ::collection::count countMax)
{

   ::collection::count count = 0;

   if (case_insensitive_contains_payload_count(payload, countMin, countMax))
   {

      while (conditional(countMax >= 0, count < countMax) && (case_insensitive_erase_first_payload(payload)))
      {

         count++;

      }

   }

   return count;

}


::collection::count property_set::case_insensitive_erase_string_count(const ::scoped_string & scopedstr, ::collection::count countMin, ::collection::count countMax)
{

   ::collection::count count = 0;

   if (case_insensitive_contains_string_count(scopedstr, countMin, countMax))
   {

      while (conditional(countMax >= 0, count < countMax) && case_insensitive_erase_first_string(scopedstr))
      {

         count++;

      }

   }

   return count;

}


::collection::count property_set::erase_payload_count(const ::payload & payload, ::collection::count countMin, ::collection::count countMax)
{

   ::collection::count count = 0;

   if (contains_payload_count(payload, countMin, countMax))
   {

      while (conditional(countMax >= 0, count < countMax && erase_first_payload(payload)))
      {

         count++;

      }

   }

   return count;

}


::collection::count property_set::erase_string_count(const ::scoped_string & scopedstr, ::collection::count countMin, ::collection::count countMax)
{

   ::collection::count count = 0;

   if (contains_string_count(scopedstr, countMin, countMax))
   {

      while (conditional(countMax >= 0, count < countMax) && erase_first_string(scopedstr))
      {

         count++;

      }

   }

   return count;

}


::collection::count property_set::unset(const ::atom & atom)
{

   ::collection::count c = 0;

   ::collection::index iFind = 0;

   while (true)
   {

      iFind = index_of(atom, iFind);

      if (iFind < 0)
      {

         return c;

      }

      erase_property_at(iFind);

      c++;

   }

}


bool property_set::is_new(const ::atom & atom) const
{

   auto pproperty = lookup(atom);

   if (::is_null(pproperty))
   {

      return true;

   }

   return pproperty->is_new();

}


bool property_set::is_null(const ::atom & atom) const
{

   auto pproperty = lookup(atom);

   if (::is_null(pproperty))
   {

      return true;

   }

   return pproperty->is_null();

}


bool property_set::is_new_or_null(const ::atom & atom) const
{

   auto pproperty = lookup(atom);

   if (::is_null(pproperty))
   {

      return true;

   }

   return pproperty->is_new_or_null();

}


bool property_set::is_empty(const ::atom & atom) const
{

   auto pproperty = lookup(atom);

   if (::is_null(pproperty))
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

   for (::collection::index i = 0; i < straArguments.get_size() - 1; i++)
   {

      string strThisArgument = straArguments[i];

      string strNextArgument = straArguments[i + 1];

      if (strThisArgument.begins_eat("--") || strThisArgument.begins_eat("-"))
      {

         if (strThisArgument.has_character())
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


void property_set::_008AddArgumentOrFile(::payload & payloadFile, const ::string & strArgument)
{

   auto range = strArgument();

   if (range.begins_eat("--") || range.begins_eat("-"))
   {

      _008AddArgument(range);

   }
   else
   {

      auto quote = strArgument.find_first_character_in("\"'");
      
      auto equal = strArgument.find_first_character_in("=");

      if (::found(equal) && (::not_found(quote) || quote > equal))
      {

         _008AddArgument(strArgument);

      }
      else if (payloadFile.is_empty())
      {

         payloadFile = strArgument;

      }
      else
      {

         payloadFile.as_string_array().add(strArgument);

      }

   }

}


void property_set::_008AddArgument(const ::string & strArg)
{

   auto range = strArg();

   if(!range.begins_eat("--"))
   {

      range.begins_eat("-");

   }

   auto pFindEqual = range.find('=');

   auto pFindQuote = range.find('\"');

   if (::is_set(pFindEqual))
   {

      string strValue;

      strValue = range(pFindEqual + 1);

      if (pFindEqual + 1 == pFindQuote)
      {

         auto rangeValue = strValue();

         strValue = rangeValue.consume_quoted_value();

      }

      string strKey = range(0, pFindEqual);

      _008Add(strKey, strValue);

   }
   else
   {

      _008Add(range, nullptr);

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

   ::property_set * pset = this;

   int i = 0;

   while (i < straKey.get_upper_bound())
   {

      pset = &(*pset)[straKey[i]].property_set_reference();

      i++;

   }

   if (scopedstrValue.is_empty())
   {

      pset->operator[](straKey[i]).set_type(::e_type_key_exists, false);

   }
   else if (pset->has_property(straKey[i]) && pset->operator[](straKey[i]) != scopedstrValue)
   {

      pset->operator[](straKey[i]).as_string_array().add(scopedstrValue);

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

   for (; i < straArguments.get_size(); i++)
   {

      string strArgument = straArguments[i];

      _008AddArgumentOrFile(payloadFile, strArgument);

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

      _008AddArgumentOrFile(payloadFile, strArgument);

   }

}


//void property_set_skip_network_payload(const char *& pszJson)
//{
//
//   property_set_skip_network_payload(pszJson, pszJson + strlen(pszJson) - 1);
//
//}


void property_set_skip_network_payload(::ansi_range & range)
{

   range.consume_spaces(0);

   if (*range.m_begin == '\0')
   {

      return;

   }

   range.consume("{");

   range.consume_spaces(0);

   if (*range.m_begin == '}')
   {

      range.m_begin++;

      return;

   }

   while (true)
   {

      ::atom atom;

      property_skip_network_payload_item(range);

      property_skip_network_payload_payload(range);

      range.consume_spaces(0);

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

   ::property_set * pset = this;

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

         pset = &operator[](strLine).property_set_reference();

      }
      else
      {

         string strKey;

         strKey = ::str::token(strLine, "=");

         if (strKey.has_character())
         {

            strKey.trim();

            strLine.trim();

            pset->operator[](strKey) = strLine;

         }

      }

   }

}


::string_array property_set::get_ini_lines() const
{

   ::string_array stra;

   for (auto& pprop : *this)
   {

      if (pprop->get_type() == e_type_property_set)
      {

         auto straInner = ::transfer(pprop->as_property_set().get_ini_lines());

         for (auto& str : straInner)
         {

            stra.add(pprop->name().as_string() + "." + str);

         }

      }
      else
      {

         stra.add(pprop->get_ini_line());

      }

   }

   return ::transfer(stra);

}


::string property_set::get_ini() const
{

   ::string_array stra = get_ini_lines();

   return stra.implode("\n");

}

/// Example of Standard Configuration (/etc/os-release from Ubuntu 22.10)
/// PRETTY_NAME="Ubuntu 22.10"
/// NAME="Ubuntu"
/// VERSION_ID="22.10"
/// VERSION="22.10 (Kinetic Kudu)"
/// VERSION_CODENAME=kinetic
/// ID=ubuntu
/// ID_LIKE=debian
/// HOME_URL="https://www.ubuntu.com/"
/// SUPPORT_URL="https://help.ubuntu.com/"
/// BUG_REPORT_URL="https://bugs.launchpad.net/ubuntu/"
/// PRIVACY_POLICY_URL="https://www.ubuntu.com/legal/terms-and-policies/privacy-policy"
/// UBUNTU_CODENAME=kinetic
/// LOGO=ubuntu-logo
void property_set::parse_standard_configuration(const ::string & strStandardConfiguration)
{

   ::string_array straLines;

   straLines.add_lines(strStandardConfiguration);

   for(auto & strLine : straLines)
   {

      auto range = strLine();

      string strKey;

      strKey = range.consume_word("=");

      strKey.trim();

      range.trim();

      range.paired_trim('\'', '\'');

      range.paired_trim('\"', '\"');

      this->operator[](strKey) = range;

   }

}


void property_set::parse_network_payload(const ::string & strNetworkPayload)
{

// #ifdef LINUX
//
//    uselocale(this->::system()->m_localeC);
//
// #endif

   __check_refdbg

   auto range = strNetworkPayload();

   __check_refdbg

   parse_network_payload(range);

   __check_refdbg

}


//void property_set::parse_network_payload(::const_ansi_range & range)
//{
//
//#ifdef LINUX
//   uselocale(this->::system()->m_localeC);
//#endif
//
//   parse_network_payload(pszJson, pszJson + strlen(pszJson) - 1);
//
//}


void property_set::parse_network_payload(::ansi_range & range)
{


// #ifdef LINUX
//    uselocale(this->::system()->m_localeC);
// #endif
   __check_refdbg
   range.consume_spaces(0);
   __check_refdbg
   if (*range.m_begin == '\0')
   {

      return;

   }

   range.consume("{");

   range.consume_spaces(0);

   if (*range.m_begin == '}')
   {
      
      range.m_begin++;

      return;

   }

   while (true)
   {

      ::atom atom;
      __check_refdbg
      ::property_parse_network_payload_item(atom, range);
      __check_refdbg
      auto & property = operator[](atom);
      __check_refdbg
      ::property_parse_network_payload_payload(property, range);
      __check_refdbg
      range.consume_spaces(0);

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

   auto p = this->begin();

   if (p)
   {

      while (true)
      {

         (*p)->get_network_payload(str, bNewLine);

         p++;

         if (p >= this->end())
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

   auto pszNetworkArguments = scopedstrUriOrNetworkArguments.find('?');

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

   const ::ansi_character * pszArgumentEnd1;

   const ::ansi_character * pszArgumentEnd2;

   const ::ansi_character * pszArgumentEnd;

   const ::ansi_character * pszKeyEnd;

   string strKey;

   while (true)
   {

      pszArgumentEnd1 = ansi_chr(pszArgument, '&');

      pszArgumentEnd2 = ansi_chr(pszArgument, '?');

      pszArgumentEnd = ::minimum_non_null(pszArgumentEnd1, pszArgumentEnd2);

      pszKeyEnd = ansi_chr(pszArgument, '=');

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

   stra.add_lines(scopedstrHeaders, true);

   string strName;

   for (auto & str : stra)
   {

      auto pPos = str.find(":");

      if (::is_null(pPos))
      {

         strName = str.make_lower();

         set_at(strName, ::e_type_empty);

      }
      else
      {

         strName = str.substr(0, pPos);

         strName.trim();

         strName.make_lower();

         ::string strPayload = str.substr(pPos + 1);

         strPayload.trim();

         set_at(strName, strPayload);

      }

   }

}


string property_set::_001Replace(const ::string & str) const
{

   return evaluate(str);

}


::particle * property_set::source_channel()
{

   return cast < ::particle >("source_channel");

}


::collection::count property_set::erase_by_name(const ::atom & atom)
{

   return unset(atom);

}


::collection::count property_set::erase_by_name(string_array & stra)
{

   ::collection::count count = 0;

   for (int i = 0; i < stra.get_count(); i++)
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

   erase_all_properties();

}


string property_set::implode(const ::scoped_string & scopedstrGlue) const
{

   string str;

   auto p = this->begin();

   if (p)
   {

      while (true)
      {

         str += *(*p);

         p++;

         if (p >= this->end())
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

//property * property_set::case_insensitive_find_value(const ::scoped_string & scopedstr) const
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


property_set::property_set(const ::property_set & set)
{

   operator = (set);

}


property_set::property_set(::property_set && set) :
   property_holder_array(::transfer(set))
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


//property & property_set::at(::collection::index iIndex)
//{
//
//   return operator[](iIndex);
//
//}


//::payload property_set::at(::collection::index iIndex) const
//{
//
//   return operator[](iIndex);
//
//}


//::property & property_set::property(const ::atom_array& atoma)
//{
//
//   auto iIndex = index_of(atoma);
//   
//   if (iIndex < 0)
//   {
//
//      iIndex = add_property(atoma);
//
//   }
//
//   return this->element_at(iIndex);
//
//}

//
//::property & property_set::property(const ::atom& atom)
//{
//
//   auto pproperty = lookup(atom);
//
//   if (!pproperty)
//   {
//
//      auto iIndex = add_property(atom);
//
//      pproperty = element_at(iIndex);
//
//   }
//
//   return *pproperty;
//
//}

::property * property_set::add_property(const ::atom_array & atoma)
{

   return &property(atoma);

}



::property_set & property_set::operator = (const ::payload & payload)
{

   if (payload.m_etype == e_type_property_set)
   {

      //if (::element::has(e_flag_data_struct))
      //{

      //   for (auto & pproperty : this->propertyptra())
      //   {

      //      auto ppropertySource = payload.m_ppropertyset->find(pproperty->id());

      //      if (::is_set(ppropertySource))
      //      {

      //         ((::payload &)*pproperty) = ((const ::payload &)*ppropertySource);

      //      }

      //   }

      //}
      //else
      //{

      (property_holder_array &)*this = (const property_holder_array &)*payload.m_ppropertyset;

      //      }

   }
   //else if (payload.m_etype == e_type_property)
   //{

   //   erase_all_properties();

   //   set_at(payload.m_pproperty->id(), *payload.m_pproperty);

   //}
   //else
   {

      throw ::exception(error_wrong_type);

   }

   return *this;

}


::property_set & property_set::operator = (const ::property_set & set)
{

   if (&set != this)
   {

      ::property_holder_array::operator=(set);

   }

   return *this;

}


::property_set & property_set::append(const ::property_set & set)
{

   if (&set != this)
   {

      for (auto & pproperty : *this)
      {

         add_property(*pproperty);

      }

   }

   return *this;

}


::property_set & property_set::merge(const ::property_set & set)
{

   if (::is_reference_set(set) && &set != this)
   {

      for (auto & pproperty : set)
      {

         atom atom = pproperty->name();

         auto &propertyHere = property(atom);

         if (pproperty->is_new())
         {

            propertyHere.set_type(e_type_new);

         }
         else
         {

            if (!propertyHere.is_null())
            {

               if (propertyHere.get_type() == ::e_type_element || pproperty->get_type() == ::e_type_element)
               {

                  operator[](pproperty->name()) = *pproperty;

               }
               else if (propertyHere.get_type() == ::e_type_property_set)
               {

                  if (pproperty->get_type() == ::e_type_property_set)
                  {

                     propertyHere.property_set_reference().merge(pproperty->as_property_set());

                  }
                  else
                  {

                     ::collection::index i = 0;

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
               else if (propertyHere.is_empty())
               {

                  propertyHere = *pproperty;

               }
               else
               {

                  try
                  {

                     if (propertyHere == *pproperty)
                     {

                        continue;

                     }

                  }
                  catch (...)
                  {

                  }

                  propertyHere.payload_array_reference().append_unique(pproperty->as_payload_array());

               }

            }
            else
            {

               propertyHere = *pproperty;

            }

         }

      }

   }

   return *this;

}


::property_set & property_set::merge(const ::property & property)
{

   if (property.get_type() == e_type_property_set)
   {

      merge(*property.m_ppropertyset);

   }
   else
   {

      set_at(property.name(), property);

   }

   return *this;

}


::property_set & property_set::operator += (const ::property_set & set)
{

   return append(set);

}


::property_set & property_set::operator |= (const ::property_set & set)
{

   return merge(set);

}


//bool property_set::case_insensitive_contains_value(const ::payload & payload) const { return case_insensitive_find_value(payload) != nullptr; }
//bool property_set::case_insensitive_contains_value(const ::scoped_string & scopedstr) const { return case_insensitive_find_value(scopedstr) != nullptr; }
//
//bool property_set::contains_payload(const ::payload & payload) const { return find_payload(payload) != nullptr; }
//bool property_set::contains_payload(const ::scoped_string & scopedstr) const { return find_payload(scopedstr) != nullptr; }




//::property_set & property_set::operator = (const pair_set_interface & set)
//{
//
//   erase_all();
//
//   int iCount = set.pair_set_interface_get_count();
//
//   for (int i = 0; i < iCount; i++)
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
//::property_set & property_set::operator = (const str_str_interface & set)
//{
//
//   erase_all();
//
//   int iCount = set.str_str_interface_get_count();
//
//   for (int i = 0; i < iCount; i++)
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


//property * property_set::str_find(const property & property) const
//{
//
//   for (auto & pproperty : *this)
//   {
//
//      if (pproperty->str_compare(property) == 0)
//      {
//
//         return (::property *) (::holder < ::property > &)pproperty;
//
//      }
//
//   }
//
//   return nullptr;
//
//}


bool property_set::payload_contains(const ::property_set & set) const
{

   for (auto & pproperty : set)
   {

      if (!contains_payload(*pproperty))
      {

         return false;

      }

   }

   return true;

}


bool property_set::string_contains(const ::property_set & set) const
{

   for (auto & pproperty : set)
   {

      if (!contains_string(*pproperty))
      {

         return false;

      }

   }

   return true;

}


bool property_set::contains_keys(const ::property_set & set) const
{

   for (auto & pproperty : set)
   {

      auto iIndex = index_of(pproperty->name());

      if (iIndex < 0)
      {

         return false;

      }

   }

   return true;

}



bool property_set::contains(const ::property_set & set) const
{

   for (auto & pproperty : set)
   {

      auto ppropertyHere = lookup(pproperty->name());

      if (::is_null(ppropertyHere))
      {

         return false;

      }

      if (*ppropertyHere != *pproperty)
      {

         return false;

      }

   }

   return true;

}


string & property_set::get_network_arguments(string & strNetworkArguments) const
{

   auto p = this->begin();

   while (!this->is_end(p))
   {

      if (strNetworkArguments.has_character())
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
//   for (::collection::index i = 0; i < this->get_size(); i++)
//   {
//
//      if (m_propertyptra[i]->id() == atom)
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
//      auto pproperty = __allocate property(nullptr);
//
//      this->add(pproperty);
//
//      pproperty->id() = atom;
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
//      iFind = (index) (atom.long_long);
//
//      if (::is_null(pFind) || iFind >= this->get_count())
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

      auto pproperty = lookup(strKey);

      if (::is_null(pproperty))
      {

         continue;

      }

      if (str.has_character())
      {

         str += " ";

      }

      string strItem = pproperty->name().as_string();

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

      if (str.has_character())
      {

         str += " ";

      }

      string strItem(pproperty->name().as_string());

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

      strItem = pproperty->as_string();

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


bool property_set::get_bool(const atom & atom, bool bDefault) const
{

   auto pproperty = lookup(atom);

   if (::is_null(pproperty))
   {

      return bDefault;

   }

   if(pproperty->is_empty())
   {

      return bDefault;

   }

   return pproperty->get_bool();

}


int property_set::get_int(const atom & atom, int iDefault) const
{

   auto pproperty = lookup(atom);

   if (::is_null(pproperty))
   {

      return iDefault;

   }

   if (pproperty->is_empty())
   {

      return iDefault;

   }

   return pproperty->as_int();

}


unsigned int property_set::get_unsigned_int(const atom & atom, unsigned int uDefault) const
{

   auto pproperty = lookup(atom);

   if (::is_null(pproperty))
   {

      return uDefault;

   }

   if (pproperty->is_empty())
   {

      return uDefault;

   }

   return pproperty->as_unsigned_int();

}



::string property_set::get_string(const atom & atom, const ::string & strDefault) const
{

   auto pproperty = lookup(atom);

   if (::is_null(pproperty))
   {

      return strDefault;

   }

   return pproperty->as_string();

}


::file::path property_set::get_file_path(const atom & atom, const ::file::path & pathDefault) const
{

   auto pproperty = lookup(atom);

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
      
      str += pproperty->name().as_string();

      str += scopedstrSeparator1;

      str += pproperty->as_string();

      str += scopedstrSeparator2;

   }

   return str;

}


::collection::index property_set::index_of(const ::atom & atom, ::collection::index i) const
{

   for (; i < this->get_count(); i++)
   {

      if (this->element_at(i)->name() == atom)
      {

         return i;

      }

   }

   return -1;

}


::property * property_set::lookup(const ::atom & atom, ::collection::index iStart) const
{

   auto iIndex = index_of(atom, iStart);

   if (iIndex < 0)
   {

      return nullptr;

   }

   return (::property*)this->element_at(iIndex).operator const ::property *();


}


//property* property_set::find_by_text(const ::scoped_string & scopedstr, ::collection::index iStart) const
//{
//
//   auto p = this->begin() + iStart;
//
//   for (; !this->is_end(p); p++)
//   {
//
//      if ((*p)->name() == scopedstr)
//      {
//
//         return (::property*)(::holder < ::property > &) (*p);
//
//      }
//
//   }
//
//   return nullptr;
//
//}


//::collection::index property_set::index_of(const ::atom & atom, ::collection::index iStart) const
//{
//
//   for(::collection::index iIndex = iStart; iIndex < this->size(); iIndex++)
//   {
//
//      if (this->element_at(iIndex)->name() == atom)
//      {
//
//         return iIndex;
//
//      }
//
//   }
//
//   return -1;
//
//}


property & property_set::property(const ::atom & atom)
{

   auto iIndex = index_of(atom);

   if (iIndex < 0)
   {

      iIndex = add_property(atom);

   }

   return *this->element_at(iIndex);

}


property & property_set::property(const ::atom_array & atoma)
{

   if (atoma.is_empty())
   {

      throw ::exception(error_bad_argument);

   }

   auto pset = this;

   for (int i = 0; i < atoma.get_upper_bound(); i++)
   {

      pset = &pset->property(atoma[i]).property_set_reference();

   }

   return pset->property(atoma.last());
}


//property & property_set::get(const ::atom_array & atoma)
//{
//
//   ::property_set * pset = this;
//
//   ::property * pproperty = nullptr;
//
//   for(auto & atom : atoma)
//   {
//
//      if(::is_set(pproperty))
//      {
//
//         pset = &pproperty->property_set_reference();
//
//      }
//
//      pproperty = &pset->get(atom);
//
//   }
//
//   return *pproperty;
//
//}




//::property * property_set::find_index(::iptr i) const
//{
//
//   auto p = this->m_begin;
//
//   for (; p < this->m_end; p++)
//   {
//
//      if ((*p)->id().as_iptr() == i)
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
//      auto pproperty = __allocate< property(::as_string(this->size >()));
//
//      add_item(pproperty);
//
//   }
//
//   return *(const_cast <::property_set *> (this))->m_begin[i];
//
//}


//::payload property_set::operator()(const ::atom & atom, const ::payload & payloadDefault) const
//{
//
//   auto pproperty = find(atom);
//
//   if (!pproperty)
//   {
//
//      return payloadDefault;
//
//   }
//
//   return *pproperty;
//
//}


//::payload & property_set::topic(const atom & atom)
//{
//
//   return set(atom);
//
//}


::payload_reference property_set::reference(const ::atom & atom)
{

   return property(atom);

}



::payload_reference property_set::reference(const ::atom_array & atoma)
{

   return property(atoma);

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


bool property_set::has_property(const atom & atom) const
{

   if (::is_null(this))
   {

      return false;

   }

   auto pproperty = lookup(atom);

   return ::is_set(pproperty) && 
      !(pproperty->is_new_or_null() || pproperty->get_type() == e_type_not_found);

}


bool property_set::is_true(const atom & atom) const
{

   auto pproperty = lookup(atom);

   if (::is_null(pproperty))
   {

      return false;

   }

   return pproperty->is_true();

}


bool property_set::is_true_or_empty(const atom & atom) const
{

   auto pproperty = lookup(atom);

   if (::is_null(pproperty))
   {

      return true;

   }

   return pproperty->is_true_or_empty();

}


//::payload property_set::value(const ::atom & atom) const
//{
//
//   auto pproperty = lookup(atom);
//
//   if (::is_null(pproperty))
//   {
//
//      return ::error_not_found;
//
//   }
//
//   return *pproperty;
//
//}
//
//
//::payload property_set::value(const ::atom & atom, ::payload payloadDefault) const
//{
//
//   property * pproperty = find(atom);
//
//   if (pproperty == nullptr)
//   {
//
//      return payloadDefault;
//
//   }
//
//   return *pproperty;
//
//}
//


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

         if (_get_string(strEval, strKey))
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




CLASS_DECL_ACME ::pointer < ::property_set > create_network_arguments_property_set(const ::scoped_string& scopedstrNetworkArguments)
{
   
   if (scopedstrNetworkArguments.is_trimmed_empty())
   {

      return {};

   }


   auto ppropertysetNetworkArguments = system()->__create_new<::property_set>();

   ppropertysetNetworkArguments->parse_network_arguments(scopedstrNetworkArguments);

   return ppropertysetNetworkArguments;

}