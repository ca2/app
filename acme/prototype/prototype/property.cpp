#include "framework.h"
#include "payload.h"
//#include "acme/networking/as_string.h"
#include "acme/prototype/string/str.h"


void prop_id_debug(::particle * pparticle);


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
//::payload property::operator + (const ::scoped_string & scopedstr) const
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
//         informationf("\nHI!! Shouldn't you use a matter find this by use matter and set a breakpoint here!!!\n");
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
////property::property(::collection::index iIndex)
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
////property::property(property_set * pset, const atom & atom, const ::payload &  ::payload, ::particle * pparticle) :
////   m_ppropertyset(pset),
////   m_var(payload)
////{
////
////   m_atom = atom;
////
////   if(::is_set(pparticle))
////   {
////
////      ASSERT(m_pointer.is_null());
////
////      m_pointer = pparticle;
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
//string property::implode(const ::scoped_string & scopedstrGlue) const
//{
//   return implode(pszGlue);
//}
//
//void property::parse_network_payload(const ::string & str)
//{
//   const ::ansi_character * pszJson = str;
//   parse_network_payload(pszJson, str.length());
//}
//
//void property::parse_network_payload(const char * & pszJson, strsize length)
//{
//   parse_network_payload(pszJson, pszJson + length - 1);
//}
//
//void property::parse_network_payload(const char * & pszJson,const ::ansi_character * pszEnd)
//{
//   ::property_parse_network_payload_id(m_atom, pszJson, pszEnd);
//   ::property_parse_network_payload_value(m_var,pszJson,pszEnd);
//}


void property_parse_network_payload_item(atom & atom, ::ansi_range & range)
{

   range.consume_spaces(0);

   atom = range.no_escape_consume_quoted_value();

}


void property_parse_network_payload_payload(::payload & payload, ::ansi_range & range)
{
   
   range.consume_spaces(0);

   range.consume(":");

   payload.parse_network_payload(range);

}


void property_skip_network_payload_item(::ansi_range & range)
{

   range.consume_spaces(0);

   range.no_escape_skip_quoted_value();

}


void property_skip_network_payload_payload(::ansi_range & range)
{

   range.consume_spaces(0);

   range.consume(":");

   payload_skip_network_payload(range);

}


string & property::get_network_arguments(::string & str) const
{

   str += ::url::encode(m_atom);

   str += "=";

   str += ::url::encode(as_string());

   return str;

}


//string_array & property::stra()
//{
//   return stra();
//}
//
//::int_array & property::inta()
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
//const ::int_array & property::inta() const
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
//::payload property::element_at(::collection::index iIndex) const
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
//::payload property::at(::collection::index iIndex) const
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
//::collection::count property::get_count() const
//{
//   return get_count();
//}
//
//::collection::count property::array_get_count() const
//{
//   return array_get_count();
//}
//
//bool property::array_contains(const ::scoped_string & scopedstr, index first, ::collection::index last) const
//{
//   return array_contains(psz, first, last);
//}
//
//bool property::case_insensitive_array_contains(const ::scoped_string & scopedstr, index first, ::collection::index last) const
//{
//   return case_insensitive_array_contains(psz, first, last);
//}
//
//
//::payload property::equals_ci_get(const ::scoped_string & scopedstrCompare, ::payload varOnEqual, ::payload varOnDifferent) const
//{
//   if(case_insensitive_compare_value(pszCompare) == 0)
//   {
//      return varOnEqual;
//   }
//   else
//   {
//      return varOnDifferent;
//   }
//}
//
//::payload property::equals_ci_get(const ::scoped_string & scopedstrCompare, ::payload varOnEqual) const
//{
//   if(case_insensitive_compare_value(pszCompare) == 0)
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
//int property::case_insensitive_compare_value(const ::scoped_string & scopedstr) const
//{
//   return case_insensitive_order(psz);
//}
//
//::comparison::var_strict property::strict_compare() const
//{
//   return ((const ::payload &)((property *) (this))->get_value());
//}
//

::std::strong_ordering payload::str_compare(const ::property & property) const
{

   return as_string() <=> property;

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
//bool property::strict_equal(const ::scoped_string & scopedstr) const
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
//bool property::strict_equal(int i) const
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
//bool property::strict_different(const ::scoped_string & scopedstr) const
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
//bool property::strict_different(int i) const
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
//bool property::operator == (const ::scoped_string & scopedstr) const
//{
//   return get_value() == psz;
//}
//
//bool property::operator == (const ::string & str) const
//{
//   return get_value() == str;
//}
//
//bool property::operator == (int i) const
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
//bool property::operator != (const ::scoped_string & scopedstr) const
//{
//   return get_value() != psz;
//}
//
//bool property::operator != (const ::string & str) const
//{
//   return get_value() != str;
//}
//
//bool property::operator != (int i) const
//{
//   return get_value() != i;
//}
//
//bool property::operator != (bool b) const
//{
//   return get_value() != b;
//}
//
//::payload property::explode(const ::scoped_string & scopedstrSeparator, bool bAddEmpty) const
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
//bool property::operator < (const ::scoped_string & scopedstr) const
//{
//   return get_value() < psz;
//}
//
//bool property::operator < (const ::string & str) const
//{
//   return get_value() < str;
//}
//
//bool property::operator < (int i) const
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
//bool property::operator <= (const ::scoped_string & scopedstr) const
//{
//   return get_value() <= psz;
//}
//
//bool property::operator <= (const ::string & str) const
//{
//   return get_value() <= str;
//}
//
//bool property::operator <= (int i) const
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
//bool property::operator >= (const ::scoped_string & scopedstr) const
//{
//   return get_value() >= psz;
//}
//
//bool property::operator >= (const ::string & str) const
//{
//   return get_value() >= str;
//}
//
//bool property::operator >= (int i) const
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
//bool property::operator > (const ::scoped_string & scopedstr) const
//{
//   return get_value() > psz;
//}
//
//bool property::operator > (const ::string & str) const
//{
//   return get_value() > str;
//}
//
//bool property::operator > (int i) const
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
//::payload property::operator - (int i) const
//{
//   return get_value() - i;
//}
//
//::payload property::operator - (unsigned int user) const
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
//::payload property::operator + (int i) const
//{
//   return get_value() + i;
//}
//
//::payload property::operator + (unsigned int user) const
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
//::payload property::operator / (int i) const
//{
//   return get_value() / i;
//}
//
//::payload property::operator / (unsigned int user) const
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
//::payload property::operator * (int i) const
//{
//   return get_value() * i;
//}
//
//::payload property::operator * (unsigned int user) const
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
//property & property::operator -= (int i)
//{
//   operator=(*this - i);
//   return *this;
//}
//
//property & property::operator -= (unsigned int user)
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
//property & property::operator += (int i)
//{
//   operator=(*this + i);
//   return *this;
//}
//
//property & property::operator += (unsigned int user)
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
//property & property::operator += (const ::scoped_string & scopedstr)
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
//property & property::operator /= (int i)
//{
//   operator=(*this / i);
//   return *this;
//}
//
//property & property::operator /= (unsigned int user)
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
//property & property::operator *= (int i)
//{
//   operator=(*this * i);
//   return *this;
//}
//
//property & property::operator *= (unsigned int user)
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
////property_ptra::property_ptra(::particle * pparticle):
////   ::matter(pparticle)
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
//     opt = system()->xml().m_poptionDefault;
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
//void prop_id_debug(::particle * pparticle)
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
//string operator + (const ::scoped_string & scopedstr, const property & prop)
//{
//
//   return string(psz) + (const ::payload &)prop;
//
//}















//
//
//::payload  operator - (int i, const property & prop)
//{
//   return i - (const ::payload &)prop;
//}
//
//
//::payload  operator - (unsigned int user, const property & prop)
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
//::payload  operator + (int i, const property & prop)
//{
//   return i + prop;
//}
//
//
//::payload  operator + (unsigned int user, const property & prop)
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
//::payload  operator / (int i, const property & prop)
//{
//   return i / prop;
//}
//
//
//::payload  operator / (unsigned int user, const property & prop)
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
//::payload  operator * (int i, const property & prop)
//{
//   return i * prop;
//}
//
//
//::payload  operator * (unsigned int user, const property & prop)
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


//
//payload & payload::operator += (const ::string & str)
//{
//
//   operator=(*this + str);
//
//   return *this;
//
//}


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

   informationf("prop" + as_string(g_interlockedcountProperty.operator i64()) + "\n");

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

      informationf("PROPS("+as_string(g_propertya.get_size())+")\n");

      int iCount = 250;

      for (auto p : g_propertya)
      {

         informationf("prop(\"" + p->m_atom.to_string() + "\")=\""+p->to_string()+"\";\n");

         iCount--;

         if (iCount <= 0)
         {

            break;

         }

      }

   }

#endif

}


CLASS_DECL_ACME binary_stream& binary_stream_write_property(::binary_stream& stream, const property& property)
{

   stream << property.m_atom;

   stream << (::payload&)property;

   return stream;

}


CLASS_DECL_ACME binary_stream& binary_stream_read_property(::binary_stream& stream, property& property)
{

   stream >> property.m_atom;

   stream >> (::payload&)property;

   return stream;

}



::binary_stream& operator << (::binary_stream& stream, const property & property)
{

   return binary_stream_write_property(stream, property);

}


::binary_stream & operator >>(::binary_stream & stream, property & property)
{

   return binary_stream_read_property(stream, property);

}


//::binary_stream& operator << (::binary_stream& stream, const property_particle & property)
//{
//
//   stream << property.object();
//
//   return stream;
//
//}


//::binary_stream& operator >>(::binary_stream& stream, property_particle& property)
//{
//
//   stream >> property.object();
//
//   return stream;
//
//}


