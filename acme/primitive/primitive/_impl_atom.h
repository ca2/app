//
// Created by camilo on 23/12/2022 <3ThomasBorregaardSørensen!!!
//
#pragma once


inline atom::atom()
{

   m_etype = e_type_null;

   m_u = 0;

}


inline atom::atom(enum_type etype)
{

   m_etype = etype;

   m_u = 0;

}


inline atom::atom(enum_id eid) :
        m_etype(e_type_atom),
        m_i((::iptr) eid) // used m_i to reset 64-bit field
{

}


inline atom::atom(const ::e_command & ecommand) :
        m_etype(e_type_command),
        m_i((::iptr) ecommand) // used m_i to reset 64-bit field
{

}


inline atom::atom(ENUM_ID EID) :
        atom((::enum_id)EID) // used m_i to reset 64-bit field
{

}


inline atom::atom(enum_message emessage) :
        m_etype(e_type_message),
        m_i((::iptr)emessage) // used m_i to reset 64-bit field
{

}


inline atom::atom(ENUM_MESSAGE EMESSAGE) :
        atom((::enum_message)EMESSAGE)
{

}


inline atom::atom(enum_impact eimpact) :
        m_etype(e_type_impact),
        m_i((::iptr)eimpact) // used m_i to reset 64-bit field
{

}


inline atom::atom(ENUM_IMPACT EIMPACT) :
        atom((::enum_impact) EIMPACT)
{

}


inline atom::atom(enum_property eproperty) :
        m_etype(e_type_property),
        m_i((::iptr)eproperty) // used m_i to reset 64-bit field
{

}


inline atom::atom(enum_factory efactory) :
        m_etype(e_type_factory),
        m_i((::i64)efactory) // used m_i to reset 64-bit field
{

}


inline atom::atom(enum_task_tool etasktool) :
        m_etype(e_type_task_tool),
        m_i((::iptr)etasktool) // used m_i to reset 64-bit field
{

}


inline atom::atom(enum_timer etimer) :
        m_etype(e_type_timer),
        m_i((::iptr)etimer) // used m_i to reset 64-bit field
{

}


//inline atom::atom(enum_topic etopic) :
//   m_etype(e_type_subject),
//   m_etopic(etopic)
//{
//
//}


inline atom::atom(enum_dialog_result edialogresult) :
        m_etype(e_type_dialog_result),
        m_i((::iptr)edialogresult) // used m_i to reset 64-bit field
{

}


inline atom::atom(enum_happening eevent) :
        m_etype(e_type_happening),
        m_i((::iptr)eevent) // used m_i to reset 64-bit field
{

}


// This constructor shouldn't change the primitive type of
// the atom argument.
inline atom::atom(enum_type etypeAdd, const ::atom & atom)
{

   if (atom.is_text())
   {

      m_etype = (enum_type) (etypeAdd | e_type_text);

      ::new(&m_str) ::string(atom.m_str);

   }
   else if (atom.is_integer())
   {

      m_etype = etypeAdd;

      m_iBody = atom.m_iBody;

   }
   else
   {

      m_etype = etypeAdd;

      m_iBody = 0;

   }

}


inline atom::atom(const atom & atom)
{

   if (atom.is_text())
   {

      m_etype = atom.m_etype;

      new(&m_str) ::string(atom.m_str);

   }
   else
   {

      m_u = atom.m_u;
      m_etype = atom.m_etype;

   }

}


inline atom::atom(const ::ansi_character * psz) :
   m_str(psz)
{

   m_etype = e_type_text;

}


inline atom::atom(const ::string & str) :
   m_str(str)
{

   m_etype = e_type_text;

}


inline atom::atom(const ::inline_number_string & inline_number_string) :
   m_str(inline_number_string)
{

   m_etype = e_type_text;

}


template < character_range RANGE >
atom::atom(const RANGE & range) :
   m_str(range)
{

   m_etype = e_type_text;

}


template < has_as_string_not_payload HAS_AS_STRING_NOT_PAYLOAD >
atom::atom(const HAS_AS_STRING_NOT_PAYLOAD& has_as_string_not_payload) :
   m_str(has_as_string_not_payload)
{

   m_etype = e_type_text;

}



template < primitive_signed SIGNED >
inline atom::atom(SIGNED i)
{

   m_etype = e_type_integer;

   m_i = (::iptr) i;

}


template < primitive_unsigned UNSIGNED >
inline atom::atom(UNSIGNED u)
{

   m_etype = e_type_integer;

   m_u = u;

}


template < primitive_enum ENUM >
inline atom::atom(ENUM e)
{

   m_etype = e_type_integer;

   m_i = ::as_i64(e);

}


inline bool atom::operator == (const atom & atom) const
{

   return ::comparison::tuple
           (
                   [&]() { return m_etype == atom.m_etype; },
                   [&]() { return is_text() ? (m_str == atom.m_str) : (m_iBody == atom.m_iBody); }
           );

}


inline ::std::strong_ordering atom::operator <=>(const atom & atom) const
{

   return ::comparison::tuple
           (
                   [&]() { return m_etype <=> atom.m_etype; },
                   [&]() { return is_text() ? (m_str <=> atom.m_str) : (m_iBody <=> atom.m_iBody); }
           );

}


//inline bool atom::operator != (const atom & atom) const
//{
//
//   return order(atom) != 0;
//
//}
//
//
//inline bool atom::operator < (const atom & atom) const
//{
//
//   return order(atom) < 0;
//
//}
//
//
//inline bool atom::operator >(const atom & atom) const
//{
//
//   return order(atom) > 0;
//
//}
//
//
//inline bool atom::operator <= (const atom & atom) const
//{
//
//   return order(atom) <= 0;
//
//}
//
//
//inline bool atom::operator >= (const atom & atom) const
//{
//
//   return order(atom) >= 0;
//
//}
//

inline atom & atom::operator = (const atom & atom)
{

   _defer_free();

   if (atom.is_range())
   {

      m_range = atom.m_range;

   }
   else if (atom.is_text())
   {

      ::new(&m_str) ::string(atom.m_str);

   }
   else
   {

      m_u = atom.m_u;

   }

   m_etype = atom.m_etype;

   return *this;

}


inline bool atom::operator == (const ::string & str) const
{

   return is_text() ? m_str == str : false;

}


//inline ::std::strong_ordering atom::operator <=>(const ::string & str) const
//{
//
//   return is_text() ? m_str <=> str : m_etype <=> e_type_text;
//
//}



//inline ::std::strong_ordering atom::operator <=> (const ::string & str) const
//{
//
//   return order(str);
//
//}
//
//
//inline bool atom::operator < (const ::string & str) const
//{
//
//   return order(str) < 0;
//
//}
//
//
//inline bool atom::operator <= (const ::string & str) const
//{
//
//   return order(str) <= 0;
//
//}
//
//
//inline bool atom::operator > (const ::string & str) const
//{
//
//   return order(str) > 0;
//
//}
//
//
//inline bool atom::operator >= (const ::string & str) const
//{
//
//   return order(str) >= 0;
//
//}


inline ::string atom::operator +(const ::ansi_character * psz) const
{

   return this->as_string() + psz;

}


inline ::string atom::operator +(const ::string & str) const
{

   return this->as_string() + str;

}


//inline void atom::as(::string & str) const
//{
//
//   str = this->string();
//
//}


//#endif


//inline atom::operator const char *() const
//{
//
//   return is_text() ? m_str.c_str() : nullptr;
//
//}
//


//inline string atom::as_string() const
//{
//
//   return str();
//
//}


inline bool atom::is_empty() const
{

   return is_null() || m_etype == e_type_empty || (is_text() && m_str.is_empty());

}

//
//inline CLASS_DECL_ACME::std::strong_ordering atom_order(const atom * pid1,const atom * pid2)
//{
//
//   return pid1->m_str.order(pid2->m_str);
//
//}


inline bool atom::operator == (const scoped_string & scopedstr) const
{

   return is_text() ? m_str == scopedstr : false;

}



inline ::std::strong_ordering atom::operator<=>(const scoped_string & scopedstr) const
{

   return is_text() ? m_range <=> scopedstr : m_etype <=> e_type_text;

}




//inline bool atom::operator != (const ::scoped_string & scopedstr) const
//{
//
//   return order(psz) != 0;
//
//
//}
//
//inline bool atom::operator < (const ::scoped_string & scopedstr) const
//{
//
//   return order(psz) < 0;
//
//}
//
//
//inline bool atom::operator > (const ::scoped_string & scopedstr) const
//{
//
//   return order(psz) > 0;
//
//}
//
//
//
//inline bool atom::operator <= (const ::scoped_string & scopedstr) const
//{
//
//   return order(psz) <= 0;
//
//}
//
//
//inline bool atom::operator >= (const ::scoped_string & scopedstr) const
//{
//
//   return order(psz) >= 0;
//
//}


template < primitive_integral INTEGRAL >
inline bool atom::operator == (INTEGRAL i) const
{

return ::comparison::tuple
(
[&]() { return m_etype == e_type_integer; },
[&]() { return m_i == i; }
);

}


template < primitive_integral INTEGRAL >
inline ::std::strong_ordering atom::operator <=>(INTEGRAL i) const
{

return ::comparison::tuple
(
[&]() { return m_etype <=> e_type_integer; },
[&]() { return m_i <=> i; }
);

}


//template < primitive_integral INTEGRAL >
//inline bool atom::operator != (INTEGRAL i) const
//{
//
//   return order(i) != 0;
//
//}
//
//
//template < primitive_integral INTEGRAL >
//inline bool atom::operator < (INTEGRAL i) const
//{
//
//   return order(i) < 0;
//
//}
//
//
//template < primitive_integral INTEGRAL >
//inline bool atom::operator <= (INTEGRAL i) const
//{
//
//   return order(i) <= 0;
//
//}
//
//
//template < primitive_integral INTEGRAL >
//inline bool atom::operator > (INTEGRAL i) const
//{
//
//   return order(i) > 0;
//
//}
//
//
//template < primitive_integral INTEGRAL >
//inline bool atom::operator >= (INTEGRAL i) const
//{
//
//   return order(i) >= 0;
//
//}


//#endif


inline bool atom::operator == (::enum_id eid) const
{

   return ::comparison::tuple
           (
                   [&]() { return m_etype == e_type_atom; },
                   [&]() { return m_eid == eid; }
           );

}


inline ::std::strong_ordering atom::operator <=>(::enum_id eid) const
{

   return ::comparison::tuple
           (
                   [&]() { return m_etype <=> e_type_atom; },
                   [&]() { return m_eid <=> eid; }
           );

}


inline bool atom::operator == (::enum_command ecommand) const
{

   return ::comparison::tuple
           (
                   [&]() { return m_etype == e_type_command; },
                   [&]() { return m_ecommand == ecommand; }
           );

}


inline ::std::strong_ordering atom::operator <=>(::enum_command ecommand) const
{

   return ::comparison::tuple
           (
                   [&]() { return m_etype <=> e_type_command; },
                   [&]() { return m_ecommand <=> ecommand; }
           );

}


inline bool atom::operator == (::enum_impact eimpact) const
{

   return ::comparison::tuple
           (
                   [&]() { return m_etype == e_type_impact; },
                   [&]() { return m_eimpact == eimpact; }
           );

}


inline ::std::strong_ordering atom::operator <=>(::enum_impact eimpact) const
{

   return ::comparison::tuple
           (
                   [&]() { return m_etype <=> e_type_impact; },
                   [&]() { return m_eimpact <=> eimpact; }
           );

}


//inline bool atom::operator != (::enum_id eid) const
//{
//
//   return order(eid) != 0;
//
//}
//
//
//inline bool atom::operator < (::enum_id eid) const
//{
//
//   return order(eid) < 0;
//
//}
//
//
//inline bool atom::operator <= (::enum_id eid) const
//{
//
//   return order(eid) <= 0;
//
//}
//
//
//inline bool atom::operator > (::enum_id eid) const
//{
//
//   return order(eid) > 0;
//
//}
//
//
//inline bool atom::operator >= (::enum_id eid) const
//{
//
//   return order(eid) >= 0;
//
//}
//

inline bool atom::operator == (::enum_message emessage) const
{

   return ::comparison::tuple
           (
                   [&]() { return m_etype == e_type_message; },
                   [&]() { return m_emessage == emessage; }
           );

}



inline ::std::strong_ordering atom::operator <=>(::enum_message emessage) const
{

   return ::comparison::tuple
           (
                   [&]() { return m_etype <=> e_type_message; },
                   [&]() { return m_emessage <=> emessage; }
           );

}



//inline bool atom::operator != (::enum_message emessage) const
//{
//
//   return order(emessage) != 0;
//
//}
//
//
//inline bool atom::operator < (::enum_message emessage) const
//{
//
//   return order(emessage) < 0;
//
//}
//
//
//inline bool atom::operator <= (::enum_message emessage) const
//{
//
//   return order(emessage) <= 0;
//
//}
//
//
//inline bool atom::operator > (::enum_message emessage) const
//{
//
//   return order(emessage) > 0;
//
//}
//
//
//inline bool atom::operator >= (::enum_message emessage) const
//{
//
//   return order(emessage) >= 0;
//
//}
//

//inline int atom::order(::enum_topic etopic) const
//{
//
//   return __atom_compare_square(m_etype - e_type_subject, m_etopic - etopic);
//
//}
//
//
//inline bool atom::operator == (::enum_topic etopic) const
//{
//
//   return order(etopic) == 0;
//
//}
//
//
//inline bool atom::operator != (::enum_topic etopic) const
//{
//
//   return order(etopic) != 0;
//
//}
//
//
//inline bool atom::operator < (::enum_topic etopic) const
//{
//
//   return order(etopic) < 0;
//
//}
//
//
//inline bool atom::operator <= (::enum_topic etopic) const
//{
//
//   return order(etopic) <= 0;
//
//}
//
//
//inline bool atom::operator > (::enum_topic etopic) const
//{
//
//   return order(etopic) > 0;
//
//}
//
//
//inline bool atom::operator >= (::enum_topic etopic) const
//{
//
//   return order(etopic) >= 0;
//
//}


inline bool atom::operator == (::enum_dialog_result edialogresult) const
{

   return ::comparison::tuple
           (
                   [&]() { return m_etype == e_type_dialog_result; },
                   [&]() { return m_edialogresult == edialogresult; }
           );

}


inline ::std::strong_ordering atom::operator <=>(::enum_dialog_result edialogresult) const
{

   return ::comparison::tuple
           (
                   [&]() { return m_etype <=> e_type_dialog_result; },
                   [&]() { return m_edialogresult <=> edialogresult; }
           );

}


//inline bool atom::operator != (::enum_dialog_result edialogresult) const
//{
//
//   return order(edialogresult) != 0;
//
//}
//
//
//inline bool atom::operator < (::enum_dialog_result edialogresult) const
//{
//
//   return order(edialogresult) < 0;
//
//}
//
//
//inline bool atom::operator <= (::enum_dialog_result edialogresult) const
//{
//
//   return order(edialogresult) <= 0;
//
//}
//
//
//inline bool atom::operator > (::enum_dialog_result edialogresult) const
//{
//
//   return order(edialogresult) > 0;
//
//}
//
//
//inline bool atom::operator >= (::enum_dialog_result edialogresult) const
//{
//
//   return order(edialogresult) >= 0;
//
//}



inline bool atom::operator == (::enum_happening ehappening) const
{

   return ::comparison::tuple
           (
                   [&]() { return m_etype == e_type_happening; },
                   [&]() { return m_ehappening == ehappening; }
           );

}


inline ::std::strong_ordering atom::operator <=>(::enum_happening ehappening) const
{

   return ::comparison::tuple
           (
                   [&]() { return m_etype <=> e_type_happening; },
                   [&]() { return m_ehappening <=> ehappening; }
           );

}


//inline bool atom::operator != (::enum_happening eid) const
//{
//
//   return order(eid) != 0;
//
//}
//
//
//inline bool atom::operator < (::enum_happening eid) const
//{
//
//   return order(eid) < 0;
//
//}
//
//
//inline bool atom::operator <= (::enum_happening eid) const
//{
//
//   return order(eid) <= 0;
//
//}
//
//
//inline bool atom::operator > (::enum_happening eid) const
//{
//
//   return order(eid) > 0;
//
//}
//
//
//inline bool atom::operator >= (::enum_happening eid) const
//{
//
//   return order(eid) >= 0;
//
//}
//

//inline atom::operator ::iptr () const
//{
//
//   return as_iptr();
//
//}


inline ::i64 atom::as_i64() const
{

   return primitive_type() == e_type_integer ? m_i : 0x8000000000000000ll;

}


inline ::iptr atom::as_iptr() const
{

   return primitive_type() == e_type_integer ? m_i : INTPTR_MIN;

}


inline enum_message atom::as_emessage() const
{

   return m_etype == e_type_message ? m_emessage : (enum_message) MESSAGE_UNDEFINED;

}


//inline atom::operator enum_dialog_result () const
//{
//
//   return m_etype == e_type_dialog_result ? m_edialogresult : e_dialog_result_none;
//
//}


inline bool atom::is_null() const
{

   return m_etype == e_type_null || (is_text() && m_str.is_empty());

}


inline bool atom::has_char() const
{

   return is_text() && m_str.has_char();

}


inline void atom::Empty()
{

   m_etype  = e_type_empty;

   m_i      = 0;

}


inline void atom::clear()
{

   m_etype = e_type_null;

}


//inline CLASS_DECL_ACME atom & atom::operator += (const ::scoped_string & scopedstr) { return operator = (string(*this) + string(psz)); }


inline ::std::strong_ordering atom::case_insensitive_order(const ::scoped_string & scopedstr) const
{

   if(is_empty())
   {

      if (scopedstr.is_empty())
      {

         return ::std::strong_ordering::equal;

      }
      else
      {

         return ::std::strong_ordering::less;

      }

   }
   else if(scopedstr.is_empty())
   {

      return ::std::strong_ordering::greater;

   }
   else
   {

      return m_str.case_insensitive_order(scopedstr);

   }

}


template < >
inline bool EqualElements< atom >(atom element1, atom element2)
{

   return element1 == element2;

}



//inline string CLASS_DECL_ACME operator + (const ::scoped_string & scopedstr, const ::atom & atom);

//
//namespace acme
//{
//
//   CLASS_DECL_ACME ::atom atom(const ::scoped_string & scopedstr);
//
//}
//
//
//class CLASS_DECL_ACME __atom :
//public atom
//{
//
//public:
//
//   using atom::atom;
//
//};


inline bool atom::begins(const ::scoped_string & scopedstrCandidatePrefix) const
{

   if (scopedstrCandidatePrefix.is_empty())
   {

      return true;

   }

   if (is_empty() || is_integer())
   {

      return false;

   }
   else if (is_text())
   {

      return m_str.begins(scopedstrCandidatePrefix);

   }
   else
   {

      throw "Unexpected::atom m_etype";

      return false;

   }

}


inline bool atom::case_insensitive_begins(const ::scoped_string & scopedstrCandidatePrefix) const
{

   if (scopedstrCandidatePrefix.is_empty())
   {

      return true;

   }

   if (is_empty())
   {

      return false;

   }
   else if (is_text())
   {

      return m_str.case_insensitive_begins(scopedstrCandidatePrefix);

   }
   else
   {

      throw "Unexpected ::atom m_etype";

      return false;

   }

}


inline bool atom::ends(const ::scoped_string & scopedstrCandidateSuffix) const
{

   if (scopedstrCandidateSuffix.is_empty())
   {

      return true;

   }

   if (is_empty() || is_integer())
   {

      return false;

   }
   else if (is_text())
   {

      return m_str.ends(scopedstrCandidateSuffix);

   }
   else
   {

      throw "Unexpected::atom m_etype";

      return false;

   }

}


inline bool atom::case_insensitive_ends(const ::scoped_string & scopedstrCandidateSuffix) const
{

   if (scopedstrCandidateSuffix.is_empty())
   {

      return true;

   }

   if (is_empty())
   {

      return false;

   }
   else if (is_text())
   {

      return m_str.case_insensitive_ends(scopedstrCandidateSuffix);

   }
   else
   {

      throw "Unexpected ::atom m_etype";

      return false;

   }

}






inline void from_string(::atom & atom, const ::ansi_character * psz)
{

   atom = psz;

}


//inline atom::atom(const ::ansi_character * psz) :
//        m_str(psz)
//{
//
//   m_etype = e_type_text;
//
//   //m_str.::string::string(psz);
//
//}


//inline atom::atom(const ::lparam & lparam)
//{
//
//   m_etype = e_type_integer;
//
//   m_u = lparam.m_lparam;
//
//}
//
//
//inline atom::atom(const ::string& str) :
//        m_str(str)
//{
//
//   m_etype = e_type_text;
//
//}
//
//
//inline atom::atom(const const_ansi_range & range) :
//        m_range(range)
//{
//
//   m_etype = e_type_range;
//
//}
//
//inline atom::atom(const_ansi_range && range) :
//        m_range(::transfer(range))
//{
//
//   m_etype = e_type_range;
//
//}
//
//
//inline atom::atom(const const_ansi_range && range) :
//        m_range(::transfer(range))
//{
//
//   m_etype = e_type_range;
//
//}
//
//
//inline atom::atom(const ::inline_number_string& inlinenumberstring) :
//        m_str(inlinenumberstring)
//{
//
//   m_etype = e_type_text;
//
//}


//template < typename CHAR >
//inline string_base < CHAR >::string_base(const ::atom & atom) :
//   string_base(atom.string())
//{
//
//
//}


template < typename CHAR >
string_base < CHAR > & string_base < CHAR >::operator+=(const ::atom & atom)
{

   return append(atom);

}


template < typename CHAR >
string_base < CHAR > & string_base < CHAR >::append(const ::atom & atom)
{

   if (atom.is_text())
   {

      return append(atom.m_range);

   }
   else
   {

      return append(atom.as_string());

   }

}


//
//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR > string_base < TYPE_CHAR >::operator +(const ::atom & atom) const
//{
//
//   string_base < TYPE_CHAR > str(*this);
//
//   str += atom;
//
//   return str;
//
//}


//template < primitive_character CHARACTER, strsize sizeMaximumLength >
//inline ::string_base < const CHARACTER * > operator+(const inline_string < CHARACTER, sizeMaximumLength > & inlinestring, const ::atom & atom)
//{
//
//   return ::string_base< const CHARACTER *>(inlinestring) + ::string_base< const CHARACTER *>(atom);
//
//}


//inline ::string operator+(const ::ansi_character * psz, const ::atom & atom)
//{
//
//   return ::string(psz) + atom.as_string();
//
//}


//inline ::string operator+(const ::string & str, const ::atom & atom)
//{
//
//   return str + atom.as_string();
//
//}


//template < ::count c >
//inline ::string operator +(const char(&sz)[c], const ::atom & atom)
//{
//
//   return ::string(sz) + atom.as_string();
//
//}


//template < primitive_character CHARACTER, primitive_character CHARACTER2 >
//inline ::string_base<CHARACTER2> operator+(const ::range < CHARACTER > & block, const ::string_base < CHARACTER2 > & str)
//{
//
//   return ::string_base<CHARACTER2>(block) + str;
//
//}

//template < primitive_character CHARACTER >
//inline ::string_base < CHARACTER > & operator+=(::string_base < CHARACTER > & str, const ::atom & atom)
//{
//
//   return str.operator += ((::string) atom);
//
//}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE >::string_base(const ::atom & atom) :
        string_base(atom.as_string())
{


}


template < typename ITERATOR_TYPE >
inline string_range <  ITERATOR_TYPE >::string_range(const atom & atom)
{


   throw_exception(error_not_supported);


}


template < typename ITERATOR_TYPE >
inline string_range <  ITERATOR_TYPE >::string_range(const block & block)
{


   throw_exception(error_not_supported);


}


//template < >
//inline string_range <  const ::ansi_character * >::string_range(const atom & atom)
//{
//
//   if (atom.is_text())
//   {
//
//      this->m_begin =  atom.m_str.m_begin;
//      this->m_end = atom.m_str.m_end;
//
//   }
//   else
//   {
//
//      this->m_begin = nullptr;
//      this->m_end = nullptr;
//
//   }
//
//}
//
//
//template < >
//inline string_range <  const ::ansi_character * >::string_range(const block & block)
//{
//
//   this->m_begin = (const ::ansi_character *) block.m_begin;
//   this->m_end = (const ::ansi_character *)block.m_end;
//
//}


//template < typename ITERATOR_TYPE >
//inline string_range < ITERATOR_TYPE > & string_range < ITERATOR_TYPE >::operator = (const atom & atom)
//{
//
//   throw_exception(error_not_supported);
//
//
//}


template <  >
inline string_range < const ::ansi_character * > & string_range <  const ::ansi_character * >::operator = (const atom & atom)
{

   if (atom.is_text())
   {

      BASE_RANGE::operator=(atom.m_str);

   }
   else
   {

      this->m_begin = nullptr;
      this->m_end = nullptr;

   }

   return *this;

}



template < typename ITERATOR_TYPE >
inline string_range < ITERATOR_TYPE > & string_range < ITERATOR_TYPE >::operator = (const block & block)
{

   this->m_begin = (const CHARACTER *)block.data();
   this->m_end = (const CHARACTER *)block.end();

   return *this;

}


//template <  >
//inline string_range < const ::ansi_character * > & string_range <  const ::ansi_character * >::operator = (const block & block)
//{
//
//
//   this->m_begin = (const ::ansi_character *)block.m_begin;
//   this->m_end = (const ::ansi_character *)block.m_end;
//
//   return *this;
//
//}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator = (const ::atom & atom)
{

   assign(atom.as_string());

   return *this;

}


//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator += (const ::atom & atom)
//{
//
//   return operator+=(atom.operator ::string());
//
//}


//template < typename ITERATOR_TYPE >
//inline scoped_string_base < ITERATOR_TYPE >::scoped_string_base(const ::atom & atom) :
//   m_str(e_no_initialize), RANGE(e_no_initialize)
//{
//
//   m_str = atom.as_string();
//
//   RANGE::operator = (m_str);
//
//}


//template < >
//inline scoped_string_base < const ::ansi_character * >::scoped_string_base(const ::atom & atom) :
//   m_str(e_no_initialize), RANGE(e_no_initialize)
//{
//
//   if (atom.is_text())
//   {
//
//      RANGE::operator=(atom.m_str);
//
//   }
//   else
//   {
//
//      this->m_begin = nullptr;
//      this->m_end = nullptr;
//
//   }
//
//}




template < primitive_payload PAYLOAD >
atom::atom(const PAYLOAD & payload)
{

   m_etype = e_type_integer;

   m_u = 0;

   if (payload.is_null())
   {

      operator = (e_type_null);

   }
   else if (payload.is_empty())
   {

      operator = (e_type_empty);

   }
   else if (payload.get_type() == ::e_type_atom)
   {

      operator = (payload.m_atom);

   }
   else if (payload.get_type() == ::e_type_enum_command)
   {

      operator = (payload.m_ecommand);

   }
   else if (payload.is_integer())
   {

      operator = (payload.as_iptr());

   }
   else
   {

      operator = (payload.get_string());

   }

}



