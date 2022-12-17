#include "framework.h"
#include "payload.h"
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

   for(auto & pproperty : *this)
   {

      if (pproperty->case_insensitive_order(payload) == 0)
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

      if (pproperty->case_insensitive_order(psz) == 0)
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

      return erase_by_name(pproperty->m_atom);

   }

   return false;

}


bool property_set::erase_first_value_ci(const char * pcsz)
{

   property * pproperty = find_value_ci(pcsz);

   if(pproperty != nullptr)
   {

      return erase_by_name(pproperty->m_atom);

   }

   return false;

}


bool property_set::erase_first_value(const ::payload & payload)
{

   property * pproperty = find_value(payload);

   if(pproperty != nullptr)
   {

      return erase_by_name(pproperty->m_atom);

   }

   return false;

}


bool property_set::erase_first_value(const char * pcsz)
{

   property * pproperty = find_value(pcsz);

   if(pproperty != nullptr)
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


::count property_set::unset(const atom & idName)
{

   ::count c = 0;

   ::index iFind = 0;

   while (true)
   {

      iFind = find_index(idName, iFind);

      if (not_found(iFind))
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


void property_set::_008ParseCommandLine(const char * pszCmdLineParam, ::payload & payloadFile)
{

   string strApp;

   _008Parse(false, pszCmdLineParam, payloadFile, strApp);

}


void property_set::_008ParseCommandFork(const char * pszCmdLineParam, ::payload & payloadFile, string & strApp)
{

   _008Parse(true, pszCmdLineParam, payloadFile, strApp);

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
      
      if(strThisArgument.begins_eat("-"))
      {
         
         if(strThisArgument.has_char())
         {
         
            if(strNextArgument.case_insensitive_order("YES") == 0)
            {
       
               _008Add(strThisArgument, "true");
               
               straArguments.erase(i, 2);
               
               i--;
               
            }
            else if(strNextArgument.case_insensitive_order("NO") == 0)
            {
       
               _008Add(strThisArgument, "false");
               
               straArguments.erase(i, 2);
               
               i--;

            }
            else if(strNextArgument.case_insensitive_order("TRUE") == 0)
            {
       
               _008Add(strThisArgument, "true");
               
               straArguments.erase(i, 2);
               
               i--;
               
            }
            else if(strNextArgument.case_insensitive_order("FALSE") == 0)
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

   if(strArgument.case_insensitive_begins("-"))
   {

      _008AddArgument(strArgument.Mid(1));

   }
   else if (bColon)
   {

      _008AddArgument(strArgument);

   }
   else
   {
      
      if (payloadFile.is_empty())
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

   index iFindEqual = strArg.find('=');

   index iFindQuote = strArg.find('\"');

   if(iFindEqual >= 0)
   {

      string strValue;

      strValue = strArg.Mid(iFindEqual + 1);

      if(iFindEqual + 1 == iFindQuote)
      {

         const char * pszValue = strValue;

         strValue = ::str().consume_quoted_value(pszValue);

      }

      string strKey = strArg.Left(iFindEqual);

      _008Add(strKey, strValue);

   }
   else
   {

      _008Add(strArg, nullptr);

   }

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

      pset = &(*pset)[straKey[i]].property_set_reference();

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

      pset->operator[](straKey[i])= pszValue;

   }

}


void property_set::_008Parse(bool bApp, const char * pszCmdLine, ::payload & payloadFile, string & strApp)
{

   if (pszCmdLine == nullptr)
   {

      return;

   }

   //string_array stra = get_c_args_for_c(pszCmdLine);
   //string_array stra = get_c_args_from_c(pszCmdLine);
   auto straArguments = get_c_args_from_string(pszCmdLine);

   int i = 0;

   if(bApp && straArguments.get_count() > 0)
   {

      strApp = straArguments[0];

      i++;

   }
   
   _008AddArgumentPairs(straArguments);
   
   bool bColon = false;

   for(; i < straArguments.get_size(); i++)
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


void property_set_skip_network_payload(const char *& pszJson)
{

   property_set_skip_network_payload(pszJson, pszJson + strlen(pszJson) - 1);

}


void property_set_skip_network_payload(const char *& pszJson, const char * pszEnd)
{

   ::str().consume_spaces(pszJson, 0, pszEnd);

   if (*pszJson == '\0')
   {

      return;

   }

   ::str().consume(pszJson, "{", 1, pszEnd);

   ::str().consume_spaces(pszJson, 0, pszEnd);

   if (*pszJson == '}')
   {

      pszJson++;

      return;

   }

   while (true)
   {

      ::atom atom;

      property_skip_network_payload_id(pszJson, pszEnd);

      property_skip_network_payload_value(pszJson, pszEnd);

      ::str().consume_spaces(pszJson, 0, pszEnd);

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

         throw ::exception(error_failed, str);

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

      if(strLine.begins_eat("["))
      {

         strLine.trim_right("]");

         pset = &(property_set &)operator[](strLine);

      }
      else
      {

         string strKey;

         strKey = ::str().token(strLine, "=");

         if(strKey.has_char())
         {

            strKey.trim();

            strLine.trim();

            pset->operator[](strKey) = strLine;

         }

      }

   }

}


void property_set::parse_network_payload(const ::string & strJson)
{

#ifdef LINUX

   uselocale(::acme::g_p->m_psubsystem->m_localeC);

#endif

   const char * pszJson = strJson;

   parse_network_payload(pszJson, pszJson + strJson.get_length() - 1);

}


void property_set::parse_network_payload(const char * & pszJson)
{

#ifdef LINUX
   uselocale(::acme::g_p->m_psubsystem->m_localeC);
#endif

   parse_network_payload(pszJson, pszJson + strlen(pszJson) - 1);

}


void property_set::parse_network_payload(const char * & pszJson, const char * pszEnd)
{
   ::str().consume_spaces(pszJson, 0, pszEnd);
   if (*pszJson == '\0')
   {
      return;
   }
   ::str().consume(pszJson, "{", 1, pszEnd);
   ::str().consume_spaces(pszJson, 0, pszEnd);
   if (*pszJson == '}')
   {
      pszJson++;
      return;
   }
   while(true)
   {

      ::atom atom;

      ::property_parse_network_payload_id(atom, pszJson,pszEnd);

      auto & property = operator[](atom);

      ::property_parse_network_payload_value(property,pszJson,pszEnd);

      ::str().consume_spaces(pszJson, 0, pszEnd);

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

         throw ::exception(error_parsing, str);

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

         if (!p)
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


void property_set::parse_network_arguments(const char * pszUriOrNetworkArguments)
{
   
   if(::is_empty(pszUriOrNetworkArguments))
   {
      
      return;
   
   }
   
   const char * pszNetworkArguments = strchr(pszUriOrNetworkArguments, '?');
   
   if(::is_empty(pszNetworkArguments))
   {
      
      return _parse_network_arguments(pszUriOrNetworkArguments);
      
   }
   else
   {

      return _parse_network_arguments(pszNetworkArguments + 1);
      
   }
   
}


void property_set::_parse_network_arguments(const char * pszNetworkArguments)
{
   
   if(::is_empty(pszNetworkArguments))
   {
    
      return;
      
   }
   
   const char * pszArgument = pszNetworkArguments;
   
   const char * pszArgumentEnd;
   
   const char * pszKeyEnd;
   
   string strKey;
   
   while(true)
   {
      
      pszArgumentEnd = strchr(pszArgument, '&');
      
      pszKeyEnd   = strchr(pszArgument, '=');
      
      if(pszArgumentEnd == nullptr)
      {
         
         if(pszKeyEnd == nullptr)
         {
            
            strKey = ::url::decode({ pszArgument, strlen(pszNetworkArguments) - (pszArgument - pszNetworkArguments) });
            
            _008Add(strKey, "");
            
         }
         else
         {
            
            string strKey = ::url::decode({ pszArgument, pszKeyEnd - pszArgument });
            
            string strValue = ::url::decode({ pszKeyEnd + 1, strlen(pszNetworkArguments) - (pszKeyEnd + 1 - pszNetworkArguments) });
            
            _008Add(strKey, strValue);
            
         }
         
         return;
         
      }

      if(pszKeyEnd == nullptr || pszKeyEnd > pszArgumentEnd)
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


void property_set::parse_network_headers(const char * pszHeaders)
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

   auto p = begin();

   if(p)
   {

      while(true)
      {

         str += **p;

         p++;

         if (!p)
         {

            break;

         }

         str += pszGlue;

      }

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

      ::acme::copy((property_ptra & )*this, (const property_ptra & ) set);

   }

   return *this;

}


property_set & property_set::append(const property_set & set)
{

   if (&set != this)
   {

      for(auto & pproperty : set)
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

      for(auto & pproperty : set)
      {

         atom idName = pproperty->name();

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

                        if(!has_property(::as_string(i)))
                        {

                           operator[](::as_string(i)) = *pproperty;

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

   for(auto & p : *this)
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

   if(p)
   {

      while (p)
      {

         (*p)->get_network_arguments(strNetworkArguments);

         p++;

         if (!p)
         {

            break;

         }

         strNetworkArguments += "&";

      }

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
//   index iFind = find(atom);
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
//bool stable_property_set::has_property(atom atom)
//{
//
//   index iFind = find(atom);
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
//   index iFind = find(atom);
//
//   if (iFind < 0)
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
//      if (iFind < 0 || iFind >= m_propertyptra.get_count())
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
//      if (iFind < 0)
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

      string strItem = pproperty->m_atom;

      if(strItem.find(" ") >= 0 || strItem.find("\'") >= 0)
      {

         strItem.replace_with("\\\"", "\"");

         str = "\"" + strItem + "\"";

      }
      else if(strItem.find("\"") >= 0)
      {

         strItem.replace_with("\\\'", "\'");

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

      strItem = *pproperty;

      if(strItem.find(" ") >= 0 || strItem.find("\'") >= 0)
      {

         strItem.replace_with("\\\"", "\"");

         str = "\"" + strItem + "\"";

      }
      else if(strItem.find("\"") >= 0)
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

   for(auto & pproperty : *this)
   {

      if(str.has_char())
      {

         str += " ";

      }

      string strItem(pproperty->m_atom);

      if(strItem.find(" ") >= 0 || strItem.find("\'") >= 0)
      {

         strItem.replace_with("\\\"", "\"");

         str = "\"" + strItem + "\"";

      }
      else if(strItem.find("\"") >= 0)
      {

         strItem.replace_with("\\\'", "\'");

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

      strItem = *pproperty;

      if(strItem.find(" ") >= 0 || strItem.find("\'") >= 0)
      {

         strItem.replace_with("\\\"", "\"");

         str = "\"" + strItem + "\"";

      }
      else if(strItem.find("\"") >= 0)
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


::index property_set::find_index(const ::atom & atom, ::index i) const
{

   auto p = this->m_begin + i;

   for(; p < this->m_end; p++)
   {

      if (p[i]->m_atom == atom)
      {

         return i;

      }

   }

   return -1;

}



property & property_set::get(const ::atom & atom)
{

   auto pproperty = find(atom);

   if (!pproperty)
   {

      pproperty = memory_new property(atom);

      add_item(pproperty);

   }

   return *pproperty;

}

//#define memory_new ACME_NEW

::property * property_set::find(const ::atom & atom) const
{

   auto iFind = find_index(atom);

   if(not_found(iFind))
   {

      return nullptr;

   }

   return (const_cast < property_set * > (this))->m_begin[iFind];

}


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


//#define memory_new ACME_NEW

//property * payload::find_property(const ::atom & atom) const
//{
//
//   if (!casts_to(e_type_property_set))
//   {
//
//      return nullptr;
//
//   }
//
//   return propset().find(atom);
//
//}


//property & payload::get_property(const ::atom & atom)
//{
//
//   return propset().get(atom);
//
//}



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

   strsize iPos;

   char ch;

   char chNext;

   for (iPos = 0; iPos < str.get_length(); iPos++)
   {

      ch = str[iPos];

      if (iPos + 1 < str.get_length())
      {

         chNext = str[iPos + 1];

      }
      else
      {

         chNext = '\0';

      }

      if (ch == '\\')
      {

         iPos++;

         continue;

      }
      else if (ch == '{' && chNext == '$')
      {

         strsize iEnd = str.find('}', iPos + 1);

         if (iEnd < 0)
         {

            //error

            break;

         }

         string strKey = str.Mid(iPos + 2, iEnd - iPos - 2);

         string strEval;

         if (get_string(strEval, strKey))
         {

            str = str.Left(iPos) + strEval + str.Mid(iEnd + 1);

            iPos += strEval.get_length() - 1;

         }
         else
         {

            iPos = iEnd;

         }


      }
      else if (ch == '$')
      {

         if (!(ansi_char_isalpha(chNext) || chNext == '_'))
         {

            // error

            break;

         }

         strsize iStart = iPos;

         strsize iEnd = iStart + 2;

         for (; iEnd < str.get_length(); iEnd++)
         {

            ch = str[iEnd];

            if (!(ansi_char_isalpha(ch) || ch == '_' || ansi_char_isdigit(ch)))
            {

               break;

            }

         }

         string strExpression = str.Mid(iStart, iEnd - iStart);

         string strEval;

         if (get_evaluation(strEval, strExpression))
         {

            str = str.Left(iPos) + strEval + str.Mid(iEnd);

            iPos += strEval.get_length() - 1;

         }
         else
         {

            iPos = iEnd;

         }

      }

   }

   return str;

}


bool property_set::get_evaluation(::string & str, const ::string & strExpression) const
{

   return get_string(str, strExpression);

}


