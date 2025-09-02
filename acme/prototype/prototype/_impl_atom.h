//
// Created by camilo on 23/12/2022 <3ThomasBorregaardSorensen!!!
//
#pragma once


#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/constant/user_message.h"


template < typename ITERATOR_TYPE >
inline const_string_range < ITERATOR_TYPE >::const_string_range(const block & block)
{

   *this = block;

}


template < typename ITERATOR_TYPE >
inline const_string_range < ITERATOR_TYPE > & const_string_range < ITERATOR_TYPE >::operator = (const block & block)
{

   if (block.size() % sizeof(decltype(*block.m_begin)) != 0)
   {

      throw ::exception(error_failed, "data type misalignment");

   }

   this->m_begin = (ITERATOR_TYPE)block.m_begin;
   this->m_end = (ITERATOR_TYPE)block.m_end;

   return *this;

}


//template < typename ITERATOR_TYPE >
//inline const_string_range <  ITERATOR_TYPE >::const_string_range(const block & block)
//{
//
//
//   throw_exception(error_not_supported);
//
//
//}



//template < >
//inline string_range <  const_char_pointer >::string_range(const atom & atom)
//{
//
//   if (atom.is_text())
//   {
//
//      this->m_begin = atom.m_str.m_begin;
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


template < typename ITERATOR_TYPE >
template < primitive_block BLOCK >
inline string_range < ITERATOR_TYPE >::string_range(const BLOCK & block) :
   const_string_range < ITERATOR_TYPE >(block)
{

   //this->m_begin = (ITERATOR_TYPE)block.m_begin;
   //this->m_end = (ITERATOR_TYPE)block.m_end;

}


//template <  >
//inline string_range < const_char_pointer >& string_range <  const_char_pointer >::operator = (const atom & atom)
//{
//
//   if (atom.is_text())
//   {
//
//      BASE_RANGE::operator=(atom.m_str);
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
//   return *this;
//
//}


//template <  >
//inline string_range < const_char_pointer >& string_range <  const_char_pointer >::operator = (const block & block)
//{
//
//
//   this->m_begin = (const_char_pointer )block.m_begin;
//   this->m_end = (const_char_pointer )block.m_end;
//
//   return *this;
//
//}


//template < typename ITERATOR_TYPE >
//inline string_range <  ITERATOR_TYPE >::string_range(const atom & atom)
//{
//
//
//   throw_exception(error_not_supported);
//
//
//}


//template < typename ITERATOR_TYPE >
//inline string_range <  ITERATOR_TYPE >::string_range(const block & block)
//{
//
//
//   throw_exception(error_not_supported);
//
//
//}


//template < typename ITERATOR_TYPE >
//inline mutable_string_range <  ITERATOR_TYPE >::mutable_string_range(const atom & atom)
//{
//
//
//   throw_exception(error_not_supported);
//
//
//}


template < typename ITERATOR_TYPE >
inline mutable_string_range < ITERATOR_TYPE >::mutable_string_range(const block & block) :
   string_range < ITERATOR_TYPE >(block)
{


   //throw_exception(error_not_supported);


}


//template < typename ITERATOR_TYPE >
//inline string_range < ITERATOR_TYPE > & string_range < ITERATOR_TYPE >::operator = (const atom & atom)
//{
//
//   throw_exception(error_not_supported);
//
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator = (const ::atom & atom)
//{
//
//   assign_range(atom.as_string());
//
//   return *this;
//
//}


//template < typename ITERATOR_TYPE >
//string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator += (const ::atom & atom)
//{
//
//   return operator +=(atom.operator ::string());
//
//}


//template < typename ITERATOR_TYPE >
//inline scoped_string_base < ITERATOR_TYPE >::scoped_string_base(const ::atom & atom) :
//   m_str(no_initialize_t{}), RANGE(no_initialize_t{})
//{
//
//   m_str = atom.as_string();
//
//   RANGE::operator = (m_str);
//
//}


//template < >
//inline scoped_string_base < const_char_pointer >::scoped_string_base(const ::atom & atom) :
//   m_str(no_initialize_t{}), RANGE(no_initialize_t{})
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


// template < typename ITERATOR_TYPE >
// inline string_range < ITERATOR_TYPE > & string_range < ITERATOR_TYPE >::operator = (const block & block)
// {
//
//    this->m_begin = (const CHARACTER *)block.data();
//    this->m_end = (const CHARACTER *)block.end();
//
//    return *this;
//
// }


inline atom::atom()
{

   m_etype = e_type_null;

   m_uLargest = 0;

}


inline atom::atom(enum_type etype)
{

   m_etype = etype;

   m_uLargest = 0;

}


inline atom::atom(enum_id eid) :
        m_etype(e_type_id),
        m_iLargest((::iptr) eid) // used m_iLargest to reset 64-bit field
{

}


inline atom::atom(enum_element eelement) :
   m_etype(e_type_element),
   m_iLargest((::iptr)eelement) // used m_iLargest to reset 64-bit field
{

}


//inline atom::atom(const ::e_command & ecommand) :
//        m_etype(e_type_command),
//        m_iLargest((::iptr) ecommand) // used m_iLargest to reset 64-bit field
//{
//
//}


// inline atom::atom(::enum_id EID) :
//         atom((::enum_id)EID) // used m_iLargest to reset 64-bit field
// {
//
// }


inline atom::atom(::user::enum_message eusermessage) :
        m_etype(e_type_user_message),
        m_iLargest((::iptr)eusermessage) // used m_iLargest to reset 64-bit field
{

}
inline atom::atom(::enum_message emessage) :
    m_etype(e_type_message), m_iLargest((::iptr)emessage) // used m_iLargest to reset 64-bit field
{
}


// inline atom::atom(ENUM_MESSAGE EMESSAGE) :
//         atom((::user::enum_message)EMESSAGE)
// {
//
// }


inline atom::atom(enum_impact eimpact) :
        m_etype(e_type_impact),
        m_iLargest((::iptr)eimpact) // used m_iLargest to reset 64-bit field
{

}


inline atom::atom(ENUM_IMPACT EIMPACT) :
        atom((::enum_impact) EIMPACT)
{

}


inline atom::atom(enum_property eproperty) :
        m_etype(e_type_property),
        m_iLargest((::iptr)eproperty) // used m_iLargest to reset 64-bit field
{

}


inline atom::atom(enum_factory efactory) :
        m_etype(e_type_factory),
        m_iLargest((long long)efactory) // used m_iLargest to reset 64-bit field
{

}


inline atom::atom(enum_task_tool etasktool) :
        m_etype(e_type_task_tool),
        m_iLargest((::iptr)etasktool) // used m_iLargest to reset 64-bit field
{

}


inline atom::atom(enum_timer etimer) :
        m_etype(e_type_timer),
        m_iLargest((::iptr)etimer) // used m_iLargest to reset 64-bit field
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
        m_iLargest((::iptr)edialogresult) // used m_iLargest to reset 64-bit field
{

}


inline atom::atom(enum_happening ehappening) :
        m_etype(e_type_happening),
        m_iLargest((::iptr)ehappening) // used m_iLargest to reset 64-bit field
{

}


inline atom::atom(enum_check echeck) :
        m_etype(e_type_check),
        m_iLargest((::iptr)echeck) // used m_iLargest to reset 64-bit field
{

}


inline atom::atom(enum_status estatus) :
        m_etype(e_type_status),
        m_iLargest((::iptr)estatus) // used m_iLargest to reset 64-bit field
{

}


// This constructor shouldn't change the primitive type of
// the atom argument.
inline atom::atom(enum_type etypeAdd, const ::atom & atom)
{

   if (atom.is_text())
   {

      m_etype = (enum_type) (etypeAdd | e_type_text);

      m_str.construct_from_string(atom.m_str);

   }
   else if (atom.is_integer())
   {

      m_etype = etypeAdd;

      m_iLargest = atom.m_iLargest;

   }
   else
   {

      m_etype = etypeAdd;

      m_iLargest = 0;

   }

}


inline atom::atom(::atom && atom)
{
   m_etype = atom.m_etype;
   if (atom.m_etype >= 0)
   {
      if (atom.m_etype & e_type_text)
      {
         m_str.construct_from_string(::transfer(atom.m_str));
      }
      else
      {
         m_uLargest = atom.m_uLargest;
      }
   }
   atom.m_etype = e_type_integer;
   atom.m_uLargest = 0;
}


inline atom::atom(const atom & atom)
{

   if (atom.is_text())
   {

      m_etype = atom.m_etype;

      m_str.construct_from_string(atom.m_str);

   }
   else
   {

      m_uLargest = atom.m_uLargest;
      m_etype = atom.m_etype;

   }

}


inline atom::atom(const domain_id & domainid)  :
   m_etype(e_type_domainid),
   m_iLargest(0)
{

   m_domainid = domainid;

}

inline atom::atom(const_char_pointer psz) :
   m_str(psz)
{

   m_etype = e_type_text;

}


inline atom::atom(const ::scoped_string & scopedstr) :
   m_str(scopedstr)
{

   m_etype = e_type_text;

}


inline atom::atom(const ::inline_number_string & inline_number_string) :
   m_str(inline_number_string)
{

   m_etype = e_type_text;

}



template < primitive_signed SIGNED >
inline atom::atom(SIGNED i)
{

   m_etype = e_type_integer;

   m_iLargest = (::iptr) i;

}


template < primitive_unsigned UNSIGNED >
inline atom::atom(UNSIGNED u)
{

   m_etype = e_type_integer;

   m_uLargest = u;

}


template < primitive_enum ENUM >
inline atom::atom(ENUM e)
{

   m_etype = e_type_integer;

   m_iLargest = ::as_long_long(e);

}


inline bool atom::operator == (const atom & atom) const
{

   if (m_etype != atom.m_etype)
   {

      return false;

   }
           
   if (is_text())
   {

      return m_str == atom.m_str;

   }
   else
   {
    
      return m_iLargest == atom.m_iLargest;

   }

}


inline ::std::strong_ordering atom::operator <=>(const atom & atom) const
{

   auto compare = m_etype <=> atom.m_etype;

   if (compare != 0)
   {

      return compare;

   }
                   
   if (is_text())
   {

      return m_str <=> atom.m_str;

   }
   else
   {
      
      return m_iLargest <=> atom.m_iLargest;

   }

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

   if (is_text() && !is_range())
   {

      if(atom.is_text() && !atom.is_range())
      {

         m_str = atom.m_str;

      }
      else
      {

         _defer_free();

         if (atom.is_range())
         {

            m_range = atom.m_range;

         }
         else
         {

            m_uLargest = atom.m_uLargest;

         }

      }

   }
   else
   {

      if (atom.is_range())
      {

         m_range = atom.m_range;

      }
      else if (atom.is_text())
      {

         m_str.construct_from_string(atom.m_str);

      }
      else
      {

         m_uLargest = atom.m_uLargest;

      }

   }

   m_etype = atom.m_etype;

   return *this;

}


template < primitive_character_range RANGE >
inline bool atom::operator == (const RANGE & range) const
{

   return is_text() ? m_str == range : false;

}


//inline ::std::strong_ordering atom::operator <=>(const ::scoped_string & scopedstr) const
//{
//
//   return is_text() ? m_str <=> str : m_etype <=> e_type_text;
//
//}



//inline ::std::strong_ordering atom::operator <=> (const ::scoped_string & scopedstr) const
//{
//
//   return order(str);
//
//}
//
//
//inline bool atom::operator < (const ::scoped_string & scopedstr) const
//{
//
//   return order(str) < 0;
//
//}
//
//
//inline bool atom::operator <= (const ::scoped_string & scopedstr) const
//{
//
//   return order(str) <= 0;
//
//}
//
//
//inline bool atom::operator > (const ::scoped_string & scopedstr) const
//{
//
//   return order(str) > 0;
//
//}
//
//
//inline bool atom::operator >= (const ::scoped_string & scopedstr) const
//{
//
//   return order(str) >= 0;
//
//}


//inline void atom::as(::string & str) const
//{
//
//   str = this->string();
//
//}


//#endif


//inline atom::operator const_char_pointer () const
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

template < character_pointer CHARACTER_POINTER >
inline bool atom::operator == (CHARACTER_POINTER p) const
{

   return is_text() ? m_str == p : false;

}


template < primitive_character_range RANGE >
inline ::std::strong_ordering atom::operator<=>(const RANGE & range) const
{

   return is_text() ? m_str <=> range : m_etype <=> e_type_text;

}




//inline bool atom::operator != (const ::scoped_string & scopedstr) const
//{
//
//   return order(scopedstr) != 0;
//
//
//}
//
//inline bool atom::operator < (const ::scoped_string & scopedstr) const
//{
//
//   return order(scopedstr) < 0;
//
//}
//
//
//inline bool atom::operator > (const ::scoped_string & scopedstr) const
//{
//
//   return order(scopedstr) > 0;
//
//}
//
//
//
//inline bool atom::operator <= (const ::scoped_string & scopedstr) const
//{
//
//   return order(scopedstr) <= 0;
//
//}
//
//
//inline bool atom::operator >= (const ::scoped_string & scopedstr) const
//{
//
//   return order(scopedstr) >= 0;
//
//}


template < primitive_integral INTEGRAL >
inline bool atom::operator == (INTEGRAL i) const
{

return ::comparison::tuple
(
[&]() { return m_etype == e_type_integer; },
[&]() { return m_iLargest == i; }
);

}


template < primitive_integral INTEGRAL >
inline ::std::strong_ordering atom::operator <=>(INTEGRAL i) const
{

return ::comparison::tuple
(
[&]() { return m_etype <=> e_type_integer; },
[&]() { return m_iLargest <=> i; }
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
                   [&]() { return m_etype == e_type_id; },
                   [&]() { return m_eid == eid; }
           );

}


inline ::std::strong_ordering atom::operator <=>(::enum_id eid) const
{

   return ::comparison::tuple
           (
                   [&]() { return m_etype <=> e_type_id; },
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



inline bool atom::operator == (const ::domain_id & domainid) const
{

   return ::comparison::tuple
           (
                   [&]() { return m_etype == e_type_domainid; },
                   [&]() { return m_domainid == domainid; }
           );

}


inline ::std::strong_ordering atom::operator <=>(const ::domain_id & domainid) const
{

   return ::comparison::tuple
           (
                   [&]() { return m_etype <=> e_type_domainid; },
                   [&]() { return m_domainid <=> domainid; }
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


inline bool atom::operator == (::user::enum_message eusermessage) const
{

   return ::comparison::tuple
           (
                   [&]() { return m_etype == e_type_message; },
                   [&]() { return m_eusermessage == eusermessage; }
           );

}



inline ::std::strong_ordering atom::operator <=>(::user::enum_message eusermessage) const
{

   return ::comparison::tuple
           (
                   [&]() { return m_etype <=> e_type_message; },
                   [&]() { return m_eusermessage <=> eusermessage; }
           );

}




inline bool atom::operator==(::enum_message emessage) const
{

   return ::comparison::tuple([&]() { return m_etype == e_type_message; },
                              [&]() { return m_emessage == emessage; });
}


inline ::std::strong_ordering atom::operator<=>(::enum_message emessage) const
{

   return ::comparison::tuple([&]() { return m_etype <=> e_type_message; },
                              [&]() { return m_emessage <=> emessage; });
}


//inline bool atom::operator != (::user::enum_message eusermessage) const
//{
//
//   return order(emessage) != 0;
//
//}
//
//
//inline bool atom::operator < (::user::enum_message eusermessage) const
//{
//
//   return order(emessage) < 0;
//
//}
//
//
//inline bool atom::operator <= (::user::enum_message eusermessage) const
//{
//
//   return order(emessage) <= 0;
//
//}
//
//
//inline bool atom::operator > (::user::enum_message eusermessage) const
//{
//
//   return order(emessage) > 0;
//
//}
//
//
//inline bool atom::operator >= (::user::enum_message eusermessage) const
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


inline long long atom::as_long_long() const
{

   return primitive_type() == e_type_integer ? m_iLargest : 0x8000000000000000ll;

}


inline ::iptr atom::as_iptr() const
{

   return primitive_type() == e_type_integer ? m_iLargest : INTPTR_MIN;

}


inline ::user::enum_message atom::as_eusermessage() const
{

   return m_etype == e_type_user_message ? m_eusermessage : (::user::enum_message) ::user::e_message_undefined;

}


inline ::enum_message atom::as_emessage1() const
{

   return m_etype == e_type_message ? m_emessage : (::enum_message)::e_message_undefined;
}


inline enum_id atom::as_eid() const
{

   return m_etype == e_type_id ? m_eid : (enum_id)id_none;

}


//inline e_check atom::as_echeck() const
//{
//
//   return m_etype == e_type_check ? m_echeck : (enum_check) e_check_undefined;
//
//}


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


inline bool atom::has_character() const
{

   return is_text() && m_str.has_character();

}


inline void atom::Empty()
{

   m_etype  = e_type_empty;

   m_iLargest      = 0;

}


inline void atom::clear()
{

   m_etype = e_type_null;

}


//inline CLASS_DECL_ACME atom & atom::operator += (const ::scoped_string & scopedstr) { return operator = (string(*this) + string(scopedstr)); }


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

      //throw "Unexpected ::atom m_etype";

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






inline void from_string(::atom & atom, const_char_pointer psz)
{

   atom = psz;

}


//inline atom::atom(const_char_pointer psz) :
//        m_str(scopedstr)
//{
//
//   m_etype = e_type_text;
//
//   //m_str.::string::string(scopedstr);
//
//}


//inline atom::atom(const ::lparam & lparam)
//{
//
//   m_etype = e_type_integer;
//
//   m_uLargest = lparam.m_lparam;
//
//}
//
//
//inline atom::atom(const ::scoped_string & scopedstr) :
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
string_base < CHAR > & string_base < CHAR >::operator +=(const ::atom & atom)
{

   return append(atom);

}


//template < typename ITERATOR_TYPE >
//template < int t_size >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append(const const_string_range_static_array< const CHARACTER *, t_size > & a)
//{
//
//   auto old_len = size();
//
//   auto add_len = a.size();
//
//   auto new_len = old_len + add_len;
//
//   auto p = get_buffer<true>(new_len);
//
//   a.block_concatenate_to(p);
//
//   *p = {};
//
//   return *this;
//
//}


//template < typename ITERATOR_TYPE >
//template < other_primitive_character < typename string_base < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER, int t_size >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append(const const_string_range_static_array< const OTHER_CHARACTER *, t_size >& a)
//{
//
//   auto old_len = size();
//
//   character_count iaLen[t_size];
//
//   character_count* plen = iaLen;
//
//   auto newLen = oldLen + a.__utf_length(this->m_begin, plen);
//
//   set_size(newLen);
//
//   auto p = (CHARACTER*)this->m_begin;
//
//   p += oldLen;
//
//   plen = iaLen;
//
//   a.__utf_concatenate_to(p, plen);
//
//   *p = {};
//
//   return *this;
//
//}


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


//template < primitive_character CHARACTER, character_count sizeMaximumLength >
//inline ::string_base < const CHARACTER * > operator +(const inline_string < CHARACTER, sizeMaximumLength > & inlinestring, const ::atom & atom)
//{
//
//   return ::string_base< const CHARACTER *>(inlinestring) + ::string_base< const CHARACTER *>(atom);
//
//}


//inline ::string operator +(const_char_pointer psz, const ::atom & atom)
//{
//
//   return ::string(scopedstr) + atom.as_string();
//
//}


//inline ::string operator +(const ::scoped_string & scopedstr, const ::atom & atom)
//{
//
//   return str + atom.as_string();
//
//}


//template < ::collection::count c >
//inline ::string operator +(const char(&sz)[c], const ::atom & atom)
//{
//
//   return ::string(sz) + atom.as_string();
//
//}


//template < primitive_character CHARACTER, primitive_character CHARACTER2 >
//inline ::string_base<CHARACTER2> operator +(const ::range < CHARACTER > & block, const ::string_base < CHARACTER2 > & str)
//{
//
//   return ::string_base<CHARACTER2>(block) + str;
//
//}

//template < primitive_character CHARACTER >
//inline ::string_base < CHARACTER > & operator +=(::string_base < CHARACTER > & str, const ::atom & atom)
//{
//
//   return str.operator += ((::string) atom);
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE >::string_base(const ::atom & atom) :
//        string_base(atom.as_string())
//{
//
//
//}
//

//template < typename ITERATOR_TYPE >
//inline const_string_range <  ITERATOR_TYPE >::const_string_range(const atom & atom)
//{
//
//
//   throw_exception(error_not_supported);
//
//
//}


template < primitive_payload PAYLOAD >
atom::atom(const PAYLOAD & payload)
{

   m_etype = e_type_integer;

   m_uLargest = 0;

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

      operator = (payload.as_atom());

   }
//   else if (payload.get_type() == ::e_type_enum_command)
//   {
//
//      operator = (payload.m_ecommand);
//
//   }
   else if (payload.is_integer())
   {

      operator = (payload.as_iptr());

   }
   else
   {

      operator = (payload.as_string());

   }

}



//template < has_as_string_not_payload HAS_AS_STRING_NOT_PAYLOAD >
//atom::atom(const HAS_AS_STRING_NOT_PAYLOAD & has_as_string_not_payload) :
//   m_str(has_as_string_not_payload)
//{
//
//   m_etype = e_type_text;
//
//}


inline ::string atom::operator +(const_char_pointer psz) const
{

   return this->as_string() + psz;

}


inline ::string atom::operator +(const ::scoped_string & scopedstr) const
{

   return this->as_string() + scopedstr;

}


template < character_count n >
inline bool atom::operator == (const ::ansi_character (&cha)[n]) const
{

   return *this == ::scoped_string(cha);

}


template < character_count n >
inline ::std::strong_ordering atom::operator <=> (const ::ansi_character (&cha)[n]) const
{

   return *this <=> ::scoped_string(cha);

}


