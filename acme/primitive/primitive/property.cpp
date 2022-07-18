#include "framework.h"
//#include "acme/xml/_.h"


void prop_id_debug(::matter * pobject);


//property::property(property_set * pset) :
//   m_ppropertyset(pset)
//{
//
//
//}


//property::property(const property & property) :
//   m_atom(property.m_atom),
//   m_var(property)
//{
//
//}


//void property::get_value(::payload & value)
//{
//
//   value = get_value();
//
//}


//void property::get(::payload & value)
//{
//
//   value = get_value();
//
//}

//::payload & property::get()
//{
//   return get_value();
//}
//
//void property::set(const ::payload & payload)
//{
//   set_value(payload);
//}
//
//void property::unset()
//{
//   unset();
//}

//
//::payload property::operator + (const char * psz) const
//{
//
//   return get_value() + payload(psz);
//
//}
//
//
//::payload property::operator + (const ::string & str) const
//{
//
//   return get_value() + payload(str);
//
//}
//
//
//
//property & property::operator = (const property & property)
//{
//
//   if(&property != this)
//   {
//
////      m_iIndex = prop.m_iIndex;
//
//      if(m_atom.is_empty())
//      {
//
//         output_debug_string("\nHI!! Shouldn't you use a matter find this by use matter and set a breakpoint here!!!\n");
//         m_atom = property.m_atom;
//
//      }
//
//      m_var = property;
//
//   }
//
//   return *this;
//
//}
//
//
////property::property(::index iIndex)
////{
////
////   m_iIndex = iIndex;
////
////}
////
//
////property::property(const property & property) :
////   m_ppropertyset(property.m_ppropertyset),
////   m_var(property)
////{
////
////   m_atom = property.m_atom;
////
////}
//
//
////property::property(property_set * pset, const atom & atom) :
////   m_ppropertyset(pset)
////{
////
////   m_atom = atom;
////
////   if (m_ppropertyset)
////   {
////
////      m_ppropertyset->find(atom, m_var);
////
////   }
////
////}
//
//
////property::property(property_set * pset, const atom & atom, const ::payload &  ::payload, ::matter * pobject) :
////   m_ppropertyset(pset),
////   m_var(payload)
////{
////
////   m_atom = atom;
////
////   if(::is_set(pobject))
////   {
////
////      ASSERT(m_pointer.is_null());
////
////      m_pointer = pobject;
////
////   }
////
////}
//
//bool property::is_set() const
//{
//   return is_set();
//}
//
//bool property::is_new() const
//{
//   return is_new();
//}
//
//bool property::is_null() const
//{
//   return is_null();
//}
//
//bool property::is_new_or_null() const
//{
//   return is_new_or_null();
//}
//
//bool property::is_empty() const
//{
//   return is_empty();
//}
//
//
//bool property::is_true() const
//{
//
//   return is_true();
//
//}
//
//
//string property::implode(const char * pszGlue) const
//{
//   return implode(pszGlue);
//}
//
//void property::parse_network_payload(const ::string & str)
//{
//   const char * pszJson = str;
//   parse_network_payload(pszJson, str.get_length());
//}
//
//void property::parse_network_payload(const char * & pszJson, strsize length)
//{
//   parse_network_payload(pszJson, pszJson + length - 1);
//}
//
//void property::parse_network_payload(const char * & pszJson,const char * pszEnd)
//{
//   ::property_parse_network_payload_id(m_atom, pszJson, pszEnd);
//   ::property_parse_network_payload_value(m_var,pszJson,pszEnd);
//}
//
//
void property_parse_network_payload_id(atom & atom, const char *& pszJson, const char * pszEnd)
{

   ::str().consume_spaces(pszJson, 0, pszEnd);

   char sz[1024];

   char * psz = sz;

   strsize iBuffer = sizeof(sz);

   ::str().no_escape_consume_quoted_value(pszJson, pszEnd, &psz, iBuffer);

   atom = psz;

   if (iBuffer > sizeof(sz))
   {

      ::memory_free(psz);

   }

}


void property_parse_network_payload_value(::payload & payload, const char *& pszJson, const char * pszEnd)
{
   ::str().consume_spaces(pszJson, 0, pszEnd);
   ::str().consume(pszJson, ":", 1, pszEnd);
   payload.parse_network_payload(pszJson, pszEnd);
}


void property_skip_network_payload_id(const char *& pszJson, const char * pszEnd)
{

   ::str().consume_spaces(pszJson, 0, pszEnd);

   ::str().skip_quoted_value_ex2(pszJson, pszEnd);

}


void property_skip_network_payload_value(const char *& pszJson, const char * pszEnd)
{

   ::str().consume_spaces(pszJson, 0, pszEnd);

   ::str().consume(pszJson, ":", 1, pszEnd);

   var_skip_network_payload(pszJson, pszEnd);

}


string & property::get_network_arguments(::string & str) const
{

   str += url_encode(m_atom.str());

   str += "=";

   str += url_encode(this->string());

   return str;

}


//string_array & property::stra()
//{
//   return stra();
//}
//
//int_array & property::inta()
//{
//   return inta();
//}
//
//payload_array & property::payloada()
//{
//   return payloada();
//}
//
//property_set & property::propset()
//{
//   return propset();
//}
//
//const string_array & property::stra() const
//{
//   return stra();
//}
//
//const int_array & property::inta() const
//{
//   return inta();
//}
//
//const payload_array & property::payloada() const
//{
//   return payloada();
//}
//
//const property_set & property::propset() const
//{
//   return propset();
//}
//
//
//bool property::is_false() const
//{
//
//   return m_atom.is_empty() && is_false();
//
//}
//
//
//bool property::is_bool_false() const
//{
//
//   return is_bool_false();
//
//}
//
//
//bool property::is_set_false() const
//{
//
//   return is_set_false();
//
//}
//
//
//strsize property::get_length() const
//{
//   return get_length();
//}
//
//void property::string(char * psz) const
//{
//   string(psz);
//}
//
//::payload property::element_at(index iIndex) const
//{
//   switch(m_etype)
//   {
//   case ::e_type_string_array:
//      return const_cast<property *>(this)->stra().operator [](iIndex);
//   case ::e_type_i32_array:
//      return const_cast<property *>(this)->inta().operator [](iIndex);
//   case ::type_vara:
//      return const_cast<property *>(this)->payloada().operator [](iIndex);
//   case ::e_type_property_set:
//      return const_cast<property *>(this)->propset().at(iIndex);
//   default:
//      if(const_cast<property *>(this)->get_count() == 1)
//         return const_cast<property *>(this)->get_value();
//      throw ::exception(::exception("unsuported!!"));
//   }
//}
//
//::payload property::at(index iIndex) const
//{
//   return this->element_at(iIndex);
//}
//
//
////void property::io(::stream & stream)
////{
////
////   stream(m_atom);
////   stream(m_var);
////
////}
//
//
//::count property::get_count() const
//{
//   return get_count();
//}
//
//::count property::array_get_count() const
//{
//   return array_get_count();
//}
//
//bool property::array_contains(const char * psz, index first, index last) const
//{
//   return array_contains(psz, first, last);
//}
//
//bool property::array_contains_ci(const char * psz, index first, index last) const
//{
//   return array_contains_ci(psz, first, last);
//}
//
//
//::payload property::equals_ci_get(const char * pszCompare, ::payload varOnEqual, ::payload varOnDifferent) const
//{
//   if(compare_value_ci(pszCompare) == 0)
//   {
//      return varOnEqual;
//   }
//   else
//   {
//      return varOnDifferent;
//   }
//}
//
//::payload property::equals_ci_get(const char * pszCompare, ::payload varOnEqual) const
//{
//   if(compare_value_ci(pszCompare) == 0)
//   {
//      return varOnEqual;
//   }
//   else
//   {
//      return payload();
//   }
//}
//
//
////void property::notify_changed(const ::action_context & context)
////{
////
////   auto pchannel = source_channel();
////
////   if(pchannel)
////   {
////
////      pchannel->send_update((::enum_id) m_atom.i64(), context);
////
////   }
////
////}
//
//
//::i32 property::compare_value_ci(const char * psz) const
//{
//   return compare_ci(psz);
//}
//
//::comparison::var_strict property::strict_compare() const
//{
//   return ((const ::payload &)((property *) (this))->get_value());
//}
//

::i32 payload::str_compare(const ::property & property) const
{

   return string().compare(property.string());

}

//
//bool property::strict_equal(const property & prop) const
//{
//   return strict_equal(prop);
//}
//
//bool property::strict_equal(const ::payload & payload) const
//{
//   return strict_equal(payload);
//}
//
//bool property::strict_equal(const char * psz) const
//{
//   return strict_equal(psz);
//}
//
//bool property::strict_equal(const ::string & str) const
//{
//   return strict_equal(str);
//}
//
//bool property::strict_equal(double d) const
//{
//   return strict_equal(d);
//}
//
//bool property::strict_equal(::i32 i) const
//{
//   return strict_equal(i);
//}
//
//bool property::strict_equal(bool b) const
//{
//   return strict_equal(b);
//}
//
//
//bool property::strict_different(const property & prop) const
//{
//   return strict_different(const_cast < property & > (prop));
//}
//
//bool property::strict_different(const ::payload & payload) const
//{
//   return strict_different(payload);
//}
//
//bool property::strict_different(const char * psz) const
//{
//   return strict_different(psz);
//}
//
//bool property::strict_different(const ::string & str) const
//{
//   return strict_different(str);
//}
//
//bool property::strict_different(double d) const
//{
//   return strict_different(d);
//}
//
//bool property::strict_different(::i32 i) const
//{
//   return strict_different(i);
//}
//
//bool property::strict_different(bool b) const
//{
//   return strict_different(b);
//}
//
//
//bool property::operator == (const property & prop) const
//{
//   return get_value() == prop;
//}
//
//bool property::operator == (const ::payload & payload) const
//{
//   return get_value() == payload;
//}
//
//bool property::operator == (const char * psz) const
//{
//   return get_value() == psz;
//}
//
//bool property::operator == (const ::string & str) const
//{
//   return get_value() == str;
//}
//
//bool property::operator == (::i32 i) const
//{
//   return get_value() == i;
//}
//
//bool property::operator == (bool b) const
//{
//   return get_value() == b;
//}
//
//
//bool property::operator != (const property & prop) const
//{
//   return get_value() != prop;
//}
//
//bool property::operator != (const ::payload & payload) const
//{
//   return get_value() != payload;
//}
//
//bool property::operator != (const char * psz) const
//{
//   return get_value() != psz;
//}
//
//bool property::operator != (const ::string & str) const
//{
//   return get_value() != str;
//}
//
//bool property::operator != (::i32 i) const
//{
//   return get_value() != i;
//}
//
//bool property::operator != (bool b) const
//{
//   return get_value() != b;
//}
//
//::payload property::explode(const char * pszSeparator, bool bAddEmpty) const
//{
//   return explode(pszSeparator, bAddEmpty);
//}
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
//bool property::operator < (const property & prop) const
//{
//   return get_value() < prop;
//}
//
//bool property::operator < (const ::payload & payload) const
//{
//   return get_value() < ::payload;
//}
//
//bool property::operator < (const char * psz) const
//{
//   return get_value() < psz;
//}
//
//bool property::operator < (const ::string & str) const
//{
//   return get_value() < str;
//}
//
//bool property::operator < (::i32 i) const
//{
//   return get_value() < i;
//}
//
//bool property::operator < (bool b) const
//{
//   return get_value() < b;
//}
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
//
//
//
//bool property::operator <= (const property & prop) const
//{
//   return get_value() <= prop;
//}
//
//bool property::operator <= (const ::payload & payload) const
//{
//   return get_value() <= payload;
//}
//
//bool property::operator <= (const char * psz) const
//{
//   return get_value() <= psz;
//}
//
//bool property::operator <= (const ::string & str) const
//{
//   return get_value() <= str;
//}
//
//bool property::operator <= (::i32 i) const
//{
//   return get_value() <= i;
//}
//
//bool property::operator <= (bool b) const
//{
//   return get_value() <= b;
//}
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
//
//
//bool property::operator >= (const property & prop) const
//{
//   return get_value() >= prop;
//}
//
//bool property::operator >= (const ::payload & payload) const
//{
//   return get_value() >= payload;
//}
//
//bool property::operator >= (const char * psz) const
//{
//   return get_value() >= psz;
//}
//
//bool property::operator >= (const ::string & str) const
//{
//   return get_value() >= str;
//}
//
//bool property::operator >= (::i32 i) const
//{
//   return get_value() >= i;
//}
//
//bool property::operator >= (bool b) const
//{
//   return get_value() >= b;
//}
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
//
//
//bool property::operator > (const property & prop) const
//{
//   return get_value() > prop;
//}
//
//bool property::operator > (const ::payload & payload) const
//{
//   return get_value() > ::payload;
//}
//
//bool property::operator > (const char * psz) const
//{
//   return get_value() > psz;
//}
//
//bool property::operator > (const ::string & str) const
//{
//   return get_value() > str;
//}
//
//bool property::operator > (::i32 i) const
//{
//   return get_value() > i;
//}
//
//bool property::operator > (bool b) const
//{
//   return get_value() > b;
//}
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
//bool property::operator == (::i64 i) const
//{
//   return payload::operator == (i);
//}
//bool property::operator != (::i64 i) const
//{
//   return payload::operator != (i);
//}
//bool property::operator < (::i64 i) const
//{
//   return payload::operator < (i);
//}
//bool property::operator <= (::i64 i) const
//{
//   return payload::operator <= (i);
//}
//bool property::operator >= (::i64 i) const
//{
//   return payload::operator >= (i);
//}
//bool property::operator > (::i64 i) const
//{
//   return payload::operator > (i);
//}
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
//::payload property::operator - (::i32 i) const
//{
//   return get_value() - i;
//}
//
//::payload property::operator - (::u32 user) const
//{
//   return get_value() - user;
//}
//
//::payload property::operator - (::i64 i) const
//{
//   return get_value() - i;
//}
//
//::payload property::operator - (::u64 user) const
//{
//   return get_value() - user;
//}
//
//::payload property::operator - (double d) const
//{
//   return get_value() - d;
//}
//
//::payload property::operator - (const ::payload & payload) const
//{
//   return get_value() - payload;
//}
//
//
//
//
//::payload property::operator + (::i32 i) const
//{
//   return get_value() + i;
//}
//
//::payload property::operator + (::u32 user) const
//{
//   return get_value() + user;
//}
//
//::payload property::operator + (::i64 i) const
//{
//   return get_value() + i;
//}
//
//::payload property::operator + (::u64 user) const
//{
//   return get_value() + user;
//}
//
//::payload property::operator + (double d) const
//{
//   return get_value() + d;
//}
//
//::payload property::operator + (const ::payload & payload) const
//{
//   return get_value() + payload;
//}
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
//
//
//
//::payload property::operator / (::i32 i) const
//{
//   return get_value() / i;
//}
//
//::payload property::operator / (::u32 user) const
//{
//   return get_value() / user;
//}
//
//::payload property::operator / (::i64 i) const
//{
//   return get_value() / i;
//}
//
//::payload property::operator / (::u64 user) const
//{
//   return get_value() / user;
//}
//
//::payload property::operator / (double d) const
//{
//   return get_value() / d;
//}
//
//::payload property::operator / (const ::payload & payload) const
//{
//   return get_value() / payload;
//}
//
//
//
//
//::payload property::operator * (::i32 i) const
//{
//   return get_value() * i;
//}
//
//::payload property::operator * (::u32 user) const
//{
//   return get_value() * user;
//}
//
//::payload property::operator * (::i64 i) const
//{
//   return get_value() * i;
//}
//
//::payload property::operator * (::u64 user) const
//{
//   return get_value() * user;
//}
//
//::payload property::operator * (double d) const
//{
//   return get_value() * d;
//}
//
//::payload property::operator * (const ::payload & payload) const
//{
//   return get_value() * payload;
//}
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
//
//
//
//
//
//property & property::operator -= (::i32 i)
//{
//   operator=(*this - i);
//   return *this;
//}
//
//property & property::operator -= (::u32 user)
//{
//   operator=(*this - user);
//   return *this;
//}
//
//property & property::operator -= (::i64 i)
//{
//   operator=(*this - i);
//   return *this;
//}
//
//property & property::operator -= (::u64 user)
//{
//   operator=(*this - user);
//   return *this;
//}
//
//property & property::operator -= (double d)
//{
//   operator=(*this - d);
//   return *this;
//}
//
//property & property::operator -= (const ::payload & payload)
//{
//   operator=(*this - payload);
//   return *this;
//}
//
//property & property::operator -= (const property & prop)
//{
//   operator=(get_value() - prop);
//   return *this;
//}
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
//property & property::operator += (::i32 i)
//{
//   operator=(*this + i);
//   return *this;
//}
//
//property & property::operator += (::u32 user)
//{
//   operator=(*this + user);
//   return *this;
//}
//
//property & property::operator += (::i64 i)
//{
//   operator=(*this + i);
//   return *this;
//}
//
//property & property::operator += (::u64 user)
//{
//   operator=(*this + user);
//   return *this;
//}
//
//property & property::operator += (double d)
//{
//   operator=(*this + d);
//   return *this;
//}
//
//property & property::operator += (const ::payload & payload)
//{
//   operator=(*this + payload);
//   return *this;
//}
//
//property & property::operator += (const property & prop)
//{
//   operator=(get_value() + prop);
//   return *this;
//}
//
//property & property::operator += (const char * psz)
//{
//   operator=(*this + psz);
//   return *this;
//}
//
//property & property::operator += (const ::string & str)
//{
//   operator=(*this + str);
//   return *this;
//}
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
//
//
//
//property & property::operator /= (::i32 i)
//{
//   operator=(*this / i);
//   return *this;
//}
//
//property & property::operator /= (::u32 user)
//{
//   operator=(*this / user);
//   return *this;
//}
//
//property & property::operator /= (::i64 i)
//{
//   operator=(*this / i);
//   return *this;
//}
//
//property & property::operator /= (::u64 user)
//{
//   operator=(*this / user);
//   return *this;
//}
//
//property & property::operator /= (double d)
//{
//   operator=(*this / d);
//   return *this;
//}
//
//property & property::operator /= (const ::payload & payload)
//{
//   operator=(*this / payload);
//   return *this;
//}
//
//property & property::operator /= (const property & prop)
//{
//   operator=(get_value() / prop);
//   return *this;
//}
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
//
//
//
//property & property::operator *= (::i32 i)
//{
//   operator=(*this * i);
//   return *this;
//}
//
//property & property::operator *= (::u32 user)
//{
//   operator=(*this * user);
//   return *this;
//}
//
//property & property::operator *= (::i64 i)
//{
//   operator=(*this * i);
//   return *this;
//}
//
//property & property::operator *= (::u64 user)
//{
//   operator=(*this * user);
//   return *this;
//}
//
//property & property::operator *= (double d)
//{
//   operator=(*this * d);
//   return *this;
//}
//
//property & property::operator *= (const ::payload & payload)
//{
//   operator=(*this * payload);
//   return *this;
//}
//
//property & property::operator *= (const property & prop)
//{
//   operator=(get_value() * prop);
//   return *this;
//}
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
////property_ptra::property_ptra(::matter * pobject):
////   ::matter(pobject)
////{
////   set_size(0, 64);
////}
//
//
//
//
////PropertySignalObject::PropertySignalObject()
////{
////}
//
//
//
//





//string property::get_xml(::xml::disp_option * opt /*= &optDefault*/ )
//{
//  //   ::text_stream ostring;
//  //   //ostring << (const char *)m_strName << "='" << (const char *)m_strValue << "' ";
//
//  //   ostring << (const char *)m_strName << L"=" << (char)opt->value_quotation_mark
//  //      << (const char *)(opt->reference_value&&opt->m_pentities?opt->m_pentities->entity_to_ref(m_strValue):m_strValue)
//  //      << (char)opt->value_quotation_mark << L" ";
//  //   return ostring.str();
//
//  if(opt == ((::xml::disp_option *) 1))
//  {
//
//     opt = get_system()->xml().m_poptionDefault;
//
//  }
//
//  string str;
//
//  str = name();
//  str += "=";
//  str += opt->m_chQuote;
//  string strValue;
//  if(opt->m_bReferenceValue && opt->m_pentities)
//     strValue = opt->m_pentities->entity_to_ref(string());
//  else
//     strValue = string();
//
//  strValue.replace("\\", "\\\\"); // should be first
//  strValue.replace("\n", "\\n");
//  strValue.replace("\t", "\\t");
//  strValue.replace("\r", "\\r");
//  strValue.replace("'", "\\'");
//  strValue.replace("\"", "\\\"");
//
//  str += strValue;
//  str += opt->m_chQuote;
//
//  return str;
//}





//
//
//
//void prop_id_debug(::matter * pobject)
//{
//
//   comparable_array < ::atom > idaSchema;
//
//   property_set set;
//
//   idaSchema.add(set["prop1"]);
//
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
//
//
//
//
//
//
//string  operator + (const ::string & str, const property & prop)
//{
//
//   return str +  (const ::payload &) prop;
//
//}
//
//
//string operator + (const char * psz, const property & prop)
//{
//
//   return string(psz) + (const ::payload &)prop;
//
//}















//
//
//::payload  operator - (::i32 i, const property & prop)
//{
//   return i - (const ::payload &)prop;
//}
//
//
//::payload  operator - (::u32 user, const property & prop)
//{
//   return user - (const ::payload &) prop;
//}
//
//
//::payload  operator - (::i64 l, const property & prop)
//{
//   return l - (const & payload) prop;
//}
//
//
//::payload  operator - (::u64 ul, const property & prop)
//{
//   return ul - (const & payload) prop;
//}
//
//
//::payload  operator - (double d, const property & prop)
//{
//   return d - (const & payload) prop;
//}
//
//
//::payload  operator - (const ::payload & payload, const property & prop)
//{
//   return payload - (const & payload) prop;
//}

//
//property operator - (const property & prop, const ::payload & payload)
//{
//
//   auto property = prop;
//
//   property -= payload;
//
//   return property;
//
//}

//
//
//property operator - (const property & prop1, const property & prop2)
//{
//
//   auto property = prop1;
//
//   property -= (const ::payload &)prop2;
//
//   return property;
//
//}
//












//
//
//
//::payload  operator + (::i32 i, const property & prop)
//{
//   return i + prop;
//}
//
//
//::payload  operator + (::u32 user, const property & prop)
//{
//   return user + prop;
//}
//
//
//::payload  operator + (::i64 l, const property & prop)
//{
//   return l + prop;
//}
//
//
//::payload  operator + (::u64 ul, const property & prop)
//{
//   return ul + prop;
//}
//
//
//::payload  operator + (double d, const property & prop)
//{
//   return d + prop;
//}
//
//
//::payload  operator + (const ::payload & payload, const property & prop)
//{
//   return payload + prop;
//}


//property operator + (const property & prop, const ::payload & payload)
//{
//
//   auto property = prop;
//
//   property += payload;
//
//   return property;
//
//}
//
//
//property operator + (const property & prop1, const property & prop2)
//{
//
//   auto property = prop1;
//
//   property += (const ::payload &)prop2;
//
//   return property;
//
//}














//
//
//
//::payload  operator / (::i32 i, const property & prop)
//{
//   return i / prop;
//}
//
//
//::payload  operator / (::u32 user, const property & prop)
//{
//   return user / prop;
//}
//
//
//::payload  operator / (::i64 l, const property & prop)
//{
//   return l / prop;
//}
//
//
//::payload  operator / (::u64 ul, const property & prop)
//{
//   return ul / prop;
//}
//
//
//::payload  operator / (double d, const property & prop)
//{
//   return d / prop;
//}
//
//
//::payload  operator / (const ::payload & payload, const property & prop)
//{
//   return payload / prop;
//}
//
//
//property operator / (const property & prop, const ::payload & payload)
//{
//
//   auto property = prop;
//
//   property /= payload;
//
//   return property;
//
//}
//
//
//property operator / (const property & prop1, const property & prop2)
//{
//
//   auto property = prop1;
//
//   property /= (const ::payload &) prop2;
//
//   return property;
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
//
//
//
//::payload  operator * (::i32 i, const property & prop)
//{
//   return i * prop;
//}
//
//
//::payload  operator * (::u32 user, const property & prop)
//{
//   return user * prop;
//}
//
//
//::payload  operator * (::i64 l, const property & prop)
//{
//   return l * prop;
//}
//
//
//::payload  operator * (::u64 ul, const property & prop)
//{
//   return ul * prop;
//}
//
//
//::payload  operator * (double d, const property & prop)
//{
//   return d * prop;
//}
//
//
//::payload  operator * (const ::payload & payload, const property & prop)
//{
//   return payload * prop;
//}
//
//
//
//property operator * (const property & prop, const ::payload & payload)
//{
//
//   auto property = prop;
//
//   property *= payload;
//
//   return property;
//
//}
//
//
//
//property operator * (const property & prop1, const property & prop2)
//{
//
//   auto property = prop1;
//
//   property *= (const ::payload &) prop2;
//
//   return property;
//
//}
//
//
//



payload & payload::operator += (const ::string & str)
{
   
   operator=(*this + str);

   return *this;

}


::interlocked_count g_interlockedcountProperty;


void on_property_construct2()
{


}


void on_property_destruct2()
{


}


#define DEBUG_PROPERTY_COUNT 0

#if DEBUG_PROPERTY_COUNT
critical_section g_criticalsectionProperty;
ptr_array < property > g_propertya;
#endif

void on_property_construct(property * pproperty)
{

   g_interlockedcountProperty++;

#if DEBUG_PROPERTY_COUNT

   output_debug_string("prop" + __string(g_interlockedcountProperty.operator i64()) + "\n");

   on_property_construct2();

   critical_section_lock l(&g_criticalsectionProperty);

   g_propertya.add(pproperty);

#endif

}

void on_property_destruct(property* pproperty)
{

   g_interlockedcountProperty--;

#if DEBUG_PROPERTY_COUNT

   on_property_destruct2();

   critical_section_lock l(&g_criticalsectionProperty);

   g_propertya.erase_first(pproperty);

   if (g_propertya.get_size() % 100 == 0)
   {

      output_debug_string("PROPS("+__string(g_propertya.get_size())+")\n");

      int iCount = 250;

      for (auto p : g_propertya)
      {

         output_debug_string("prop(\"" + p->m_atom.to_string() + "\")=\""+p->to_string()+"\";\n");

         iCount--;

         if (iCount <= 0)
         {

            break;

         }

      }

   }

#endif

}



