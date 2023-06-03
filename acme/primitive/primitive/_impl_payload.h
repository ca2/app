//
// Created by camilo on 23/12/2022 01:48 <3ThomasBorregaardSørensen!!
//
#pragma once


//inline ::property & payload::operator[] (const ::scoped_string & scopedstr) { return get_property(scopedstr); }
//inline ::payload payload::operator[] (const ::scoped_string & scopedstr) const { return find_property(scopedstr); }


//inline ::property & operator[] (const ::string & str) { return get_property(::atom(str)); }
//inline ::payload operator[] (const ::string & str) const { return find_property(::atom(str)); }


//inline ::property & payload::operator[] (::iptr i) { return get_property(i); }
//inline ::payload payload::operator[] (::iptr i) const { return find_property(i); }


//inline ::payload payload::operator + (const ::string & str) const { return ::transfer(*this + ::scoped_string(str)); }
//inline ::payload payload::operator + (const ::inline_number_string & inline_number_string) const { return ::transfer(*this + ::scoped_string(inline_number_string)); }


//inline ::payload & payload::operator += (const ::scoped_string & scopedstr) { return *this = (*this + scopedstr); }
//inline ::payload & payload::operator += (const ::string & str) { return *this += ::scoped_string(str); }
//inline ::payload & payload::operator += (const ::inline_number_string & inline_number_string) { return *this = (*this + inline_number_string); }


inline ::string payload::as_string() const
{

   return this->as_string(nullptr);

}


inline class payload & payload::operator = (const ::scoped_string & scopedstr)
{

   set_string(scopedstr);

   return *this;

}


inline class payload & payload::operator = (const ::string & str)
{

   set_string(str);

   return *this;

}


inline class payload & payload::operator = (::string && str)
{

   set_string(::transfer(str));

   return *this;

}


inline class payload & payload::operator = (::const_ansi_range ansirange)
{

   set_string(ansirange);

   return *this;

}


inline class payload & payload::operator = (const inline_number_string & inlinenumberstring)
{

   set_string(inlinenumberstring);

   return *this;

}





//inline void payload::set_string(const ::scoped_string & scopedstr, strsize size)
//{
//
//   if (get_type() == e_type_pstring)
//   {
//
//      m_pstr->assign(psz, size);
//
//   }
//   else if (get_type() == e_type_payload_pointer)
//   {
//
//      m_ppayload->set_string(psz, size);
//
//   }
//   else if (get_type() == e_type_property)
//   {
//
//      m_pproperty->set_string(psz, size);
//
//   }
//   else
//   {
//
//      set_type(e_type_string, false);
//
//      m_str.assign(psz, size);
//
//   }
//
//}


//inline void payload::set_string(const ::string & str)
//{
//
//   if(get_type() == e_type_pstring)
//   {
//
//      *m_pstr = str;
//
//   }
//   else if(get_type() == e_type_payload_pointer)
//   {
//
//      *m_ppayload = str;
//
//   }
//   else if (get_type() == e_type_property)
//   {
//
//      ((payload&)*m_pproperty) = str;
//
//   }
//   else
//   {
//
//      set_type(e_type_string,false);
//
//      m_str = str;
//
//   }
//
//}


//inline void payload::set_string(const ::inline_number_string & inlinenumberstring)
//{
//
//   if (get_type() == e_type_pstring)
//   {
//
//      m_pstr->assign(inlinenumberstring);
//
//   }
//   else if (get_type() == e_type_payload_pointer)
//   {
//
//      m_ppayload->set_string(inlinenumberstring);
//
//   }
//   else if (get_type() == e_type_property)
//   {
//
//      m_pproperty->set_string(inlinenumberstring);
//
//   }
//   else
//   {
//
//      set_type(e_type_string, false);
//
//      m_str.assign(inlinenumberstring);
//
//   }
//
//}


class CLASS_DECL_ACME payload_object :
   virtual public particle
{
public:

   payload m_payload;

};



//class CLASS_DECL_ACME pack :
//   public payload
//{
//public:
//
//
//   using payload::payload;
//
//
//   template < typename TYPE >
//   pack(const ::pointer<TYPE>& p) { set_pointer(p); }
//   pack(const ::std::initializer_list < pack >& list);
//
//};


inline payload __visible(payload varOptions, bool bVisible = true);

inline payload __visible(bool bVisible) { return __visible(::e_type_new, bVisible); }





template < primitive_integral INTEGRAL >
inline ::payload payload::operator - (INTEGRAL i) const
{
   return ((INTEGRAL)*this) - i;
}


template < primitive_floating FLOATING >
inline ::payload payload::operator - (FLOATING f) const
{
   return ((FLOATING)*this) - f;
}


template < primitive_integral INTEGRAL >
inline ::payload payload::operator + (INTEGRAL i) const
{
   return ((INTEGRAL)*this) + i;
}


template < primitive_floating FLOATING >
inline ::payload payload::operator + (FLOATING f) const
{
   return ((FLOATING)*this) + f;
}


template < primitive_integral INTEGRAL >
inline ::payload payload::operator / (INTEGRAL i) const
{
   return ((INTEGRAL)*this) / i;
}


template < primitive_floating FLOATING >
inline ::payload payload::operator / (FLOATING f) const
{
   return ((FLOATING)*this) / f;
}


template < primitive_integral INTEGRAL >
inline ::payload payload::operator * (INTEGRAL i) const
{
   return ((INTEGRAL)*this) * i;
}


template < primitive_floating FLOATING >
inline ::payload payload::operator * (FLOATING f) const
{
   return ((FLOATING)*this) * f;
}


#include "__payload_cast.h"


template < primitive_integral INTEGRAL, primitive_payload PAYLOAD >
inline ::payload operator - (INTEGRAL i, const PAYLOAD & payload)
{
   return i - ((INTEGRAL)payload_cast(payload));
}


template < primitive_floating FLOATING, primitive_payload PAYLOAD >
inline ::payload operator - (FLOATING i, const PAYLOAD & payload)
{
   return i - ((FLOATING)payload_cast(payload));
}


template < primitive_integral INTEGRAL, primitive_payload PAYLOAD >
inline ::payload operator + (INTEGRAL i, const PAYLOAD & payload)
{
   return i + ((INTEGRAL)payload_cast(payload));
}


template < primitive_floating FLOATING, primitive_payload PAYLOAD >
inline ::payload operator + (FLOATING i, const PAYLOAD & payload)
{
   return i + ((FLOATING)payload_cast(payload));
}


template < primitive_integral INTEGRAL, primitive_payload PAYLOAD >
inline ::payload operator / (INTEGRAL i, const PAYLOAD & payload)
{
   return i / ((INTEGRAL)payload_cast(payload));
}


template < primitive_floating FLOATING, primitive_payload PAYLOAD >
inline ::payload operator / (FLOATING i, const PAYLOAD & payload)
{
   return i / ((FLOATING)payload_cast(payload));
}


template < primitive_integral INTEGRAL, primitive_payload PAYLOAD >
inline ::payload operator * (INTEGRAL i, const PAYLOAD & payload)
{
   return i * ((INTEGRAL)payload_cast(payload));
}


template < primitive_floating FLOATING, primitive_payload PAYLOAD >
inline ::payload operator * (FLOATING i, const PAYLOAD & payload)
{
   return i * ((FLOATING)payload_cast(payload));
}



template < primitive_integral INTEGRAL >
inline ::payload & payload::operator -= (INTEGRAL i)
{
   return *this = ((INTEGRAL)payload_cast(*this)) - i;
}


template < primitive_floating FLOATING >
inline ::payload & payload::operator -= (FLOATING f)
{
   return *this = ((FLOATING)payload_cast(*this)) - f;
}


template < primitive_integral INTEGRAL >
inline ::payload & payload::operator += (INTEGRAL i)
{
   return *this = ((INTEGRAL)(payload_cast(*this))) + i;
}


template < primitive_floating FLOATING >
inline ::payload & payload::operator += (FLOATING f)
{
   return *this = ((FLOATING)payload_cast(*this)) + f;
}


template < primitive_integral INTEGRAL >
inline ::payload & payload::operator /= (INTEGRAL i)
{
   return *this = ((INTEGRAL)payload_cast(*this)) / i;
}


template < primitive_floating FLOATING >
inline ::payload & payload::operator /= (FLOATING f)
{
   return *this = ((FLOATING)payload_cast(*this)) / f;
}


template < primitive_integral INTEGRAL >
inline ::payload & payload::operator *= (INTEGRAL i)
{
   return *this = ((INTEGRAL)payload_cast(*this)) * i;
}


template < primitive_floating FLOATING >
inline ::payload & payload::operator *= (FLOATING f)
{
   return *this = ((FLOATING)payload_cast(*this)) * f;
}







//template < primitive_payload PAYLOAD >
//inline bool strictly_equal(const ::scoped_string & scopedstr, const PAYLOAD & payload);
//template < primitive_payload PAYLOAD >
//inline bool strictly_equal(const ::string & str, const PAYLOAD & payload);
//template < primitive_payload PAYLOAD >
//inline bool strictly_equal(double d, const PAYLOAD & payload);
//template < primitive_payload PAYLOAD >
//inline bool strictly_equal(::i32 i, const PAYLOAD & payload);
//template < primitive_payload PAYLOAD >
//inline bool strictly_equal(bool b, const PAYLOAD & payload);


template < primitive_payload PAYLOAD >
inline bool strictly_different(const ::scoped_string & scopedstr, const PAYLOAD & payload);
template < primitive_payload PAYLOAD >
inline bool strictly_different(const ::string & str, const PAYLOAD & payload);
template < primitive_payload PAYLOAD >
inline bool strictly_different(double d, const PAYLOAD & payload);
template < primitive_payload PAYLOAD >
inline bool strictly_different(::i32 i, const PAYLOAD & payload);
template < primitive_payload PAYLOAD >
inline bool strictly_different(bool b, const PAYLOAD & payload);


inline ::payload_reference __reference(payload & payload)
{

   return payload;

}



//#include "payload_reference.h"
//
//
//template < typename TYPE >
//TYPE & payload::reference(TYPE & t)
//{
//
//   return t = payload_reference(*this);
//
//}
//

CLASS_DECL_ACME::string as_string(const ::payload & payload);


inline payload & copy(payload & payload, const class time & time)
{

   payload.set_type(e_type_time);

   payload.m_time = time;

   return payload;

}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR >::string_base(const ::payload & payload) :
//   string_base(payload.string())
//{
//
//
//}


template < class T >
inline pointer < T > payload::cast(T * pDefault)
{

   if (m_etype == e_type_payload_pointer && m_ppayload != nullptr)
   {

      return m_ppayload->cast < T >(pDefault);

   }
   else if (m_etype == e_type_property && m_pproperty != nullptr)
   {

      return m_pproperty->cast < T >(pDefault);

   }

   auto p = cast < T >();

   if (!p)
   {

      return pDefault;

   }

   return p;

}





template < class T >
inline T & payload::get_cast(T * pDefault)
{

   if (m_etype == e_type_payload_pointer && m_ppayload != nullptr)
   {

      return m_ppayload->get_cast <T>(pDefault);

   }

   if (m_etype == e_type_property && m_pproperty != nullptr)
   {

      return m_pproperty->get_cast <T>(pDefault);

   }

   if (m_etype != e_type_element)
   {

      return defer_create_type < T >(pDefault);

   }

   auto p = cast < T >();

   if (!p)
   {

      return defer_create_type < T >(pDefault);

   }

   return *p;

}


template < class T >
inline pointer < T > payload::cast()
{

   if (m_etype == e_type_payload_pointer && m_ppayload != nullptr)
   {

      return m_ppayload->cast < T >();

   }

   if (m_etype == e_type_property && m_pproperty != nullptr)
   {

      return m_pproperty->cast < T >();

   }


   return get_particle();

}



template < typename T >
inline pointer < T > payload::pointer() const
{

   auto pproperty = find_pointer < T >();

   if (!pproperty)
   {

      return nullptr;

   }

   return pproperty->template cast < T >();

}


inline ::payload __visible(::payload varOptions, bool bVisible)
{

   varOptions["visible"] = bVisible;

   return varOptions;

}



//inline ::payload operator + (::payload payload, const ::procedure & procedure)
//{
//
//   if (payload.get_type() != e_type_property_set)
//   {
//
//      payload["message"] = payload;
//
//   }
//
//   payload["routine"] = procedure.m_p;
//
//   return payload;
//
//}




inline void assign(bool & b, const payload & payload)
{

   b = payload.get_bool();

}


inline void assign(::block & block, const ::payload & r)
{

   block.operator=(r.as_block());

}


#if defined(__APPLE__) || defined(ANDROID) || defined(RASPBERRYPIOS) || defined(WINDOWS)


inline void assign(long & l, const payload & payload)
{

   l = payload.get_long();

}


inline void assign(unsigned long & ul, const payload & payload)
{

   ul = payload.get_unsigned_long();

}


#endif // defined(__APPLE__) || defined(ANDROID) || defined(RASPBERRYPIOS) || defined(WINDOWS)


namespace file
{


   // inline path::path(const ::payload & payload,e_path epath): path(payload.get_file_path(),epath){}
   // inline path::path(const property & property,e_path epath, int iDir): path(property.get_file_path(),epath, iDir) {}
   //inline path & path::operator = (const ::payload & payload) { return operator = (payload.get_string()); }
   //inline path & path::operator += (const ::payload & payload) { return operator += (payload.get_string()); }
   //inline path & path::operator = (const property & property) { return operator = ((const ::payload &)property); }
   //inline path & path::operator += (const property & property) { return operator += ((const ::payload &)property); }
   //inline path path::operator + (const ::atom & atom) const { return operator + (::string(atom)); }
   //inline path path::operator / (const ::atom & atom) const { return operator /(::file::path(atom)); }
   //inline path path::operator * (const property & property) const { return operator *(::file::path(property)); }
   //inline path & path::operator *= (const property & property) { return operator *=(::file::path(property)); }
   inline path path::folder() const { return { ::file_path_folder(c_str()), m_epath }; }
//   inline path path::sibling(const path& path) const { return { ::file_path_folder(c_str()) + ::string("/") + ::sz::trim_left_path_sep(path.c_str()), m_epath }; }
   inline path path::sibling(const ::scoped_string & scopedstr) const { return { ::file_path_folder(c_str()) + ::string("/") + ::sz::trim_left_path_sep(scopedstr.begin()), m_epath }; }
//   inline path path::sibling(const ::ansi_string & str) const { return this->sibling((const ::scoped_string &)str); }

   inline ::const_ansi_range path::all_extensions() const
   { 

      auto p = this->rear_find('/');

      if (::is_null(p))
      {

         p = this->begin();

      }

      auto range = substr(p);

      p = range.find_skip_or_end('.');

      return { p, this->end() };
   
   }


   inline ::const_ansi_range path::final_extension() const
   { 
      
      auto rangeName = this->name();

      auto last_dot = rangeName.rear_find('.');

      if (!last_dot)
      {

         return {};

      }

      return { last_dot + 1, rangeName.end() };

   }
   //inline bool path::operator == (const ::payload & payload) const { return operator == (payload.file_path()); }
   //inline bool path::operator != (const ::payload & payload) const { return operator != (payload.file_path()); }


} // namespace file





//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator+=(const ::payload & payload)
//{
//
//   return append(payload);
//
//}
//
//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR > string_base < TYPE_CHAR >::operator +(const ::payload & payload) const
//{
//
//   string_base < TYPE_CHAR > ansistr(*this);
//
//   ansistr += payload;
//
//   return ansistr;
//
//}


//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR > string_base < TYPE_CHAR >::operator +(const ::property & property) const
//{
//
//   string_base < TYPE_CHAR > ansistr(*this);
//
//   ansistr += property;
//
//   return ansistr;
//
//}


////template < primitive_payload PAYLOAD >
//inline payload payload::operator +(const ::payload & payload) const
//{
//
//   return ::transfer(addition(payload));
//
//}


//template < primitive_payload PAYLOAD >
inline payload payload::operator -(const ::payload & payload) const
{

   return ::transfer(subtraction(payload));

}


//template < primitive_payload PAYLOAD >
inline payload payload::operator *(const payload & payload) const

{

   return ::transfer(multiplication(payload));

}

///template < primitive_payload PAYLOAD >
inline payload payload:: operator /(const ::payload & payload) const
{

   return ::transfer(division(payload));

}


////template < primitive_payload PAYLOAD >
//inline payload & payload::operator +=(const ::payload & payload)
//{
//
//   return add(payload);
//
//}


inline payload & payload::operator -=(const ::payload & payload)
{

   return subtract(payload);

}


//template < primitive_payload PAYLOAD >
inline payload & payload::operator *=(const ::payload & payload)
{

   return multiply(payload);

}


//template < primitive_payload PAYLOAD >
inline payload & payload::operator /=(const ::payload & payload)
{

   return divide(payload);

}


template < typename CHAR_TYPE >
inline ::string_base < CHAR_TYPE > & copy(::string_base < CHAR_TYPE > & string, const ::payload & payload)
{

   string = payload.as_string();

   return string;

}


template < primitive_integral INTEGRAL >
inline void copy(INTEGRAL & integral, const ::payload & payload)
{

   integral = (INTEGRAL)payload.as_i64();

}


inline void copy(f32 & f, const ::payload & payload)
{

   f = payload.as_f32();

}


inline void copy(::f64 & f, const ::payload & payload)
{

   f = payload.as_f64();

}


template < primitive_number NUMBER >
inline void copy(::payload & payload, const NUMBER & number)
{

   payload = number;

}


template < typename CHAR_TYPE >
inline ::payload & copy(::payload & payload, const ::string_base < CHAR_TYPE > & string)
{

   payload = string;

   return payload;

}


inline void copy(::payload & payload1, const ::payload & payload2)
{

   payload1 = payload2;

}





//inline ::string operator +(const ::string & str, const ::payload & payload)
//{
//
//   return ::transfer(str + payload.as_string());
//
//}


//inline ::string operator+(const ::scoped_string & scopedstr, const ::payload & payload)
//{
//
//   return ::string(psz) + ::string(payload);
//
//}


//template < primitive_character CHARACTER >
//inline ::string_base < CHARACTER > & operator+=(::string_base < CHARACTER > & str, const ::payload & payload)
//{
//
//   return str.operator += ((::string) payload);
//
//}
//
//
//template < ::count c >
//inline ::string operator +(const char(&sz)[c], const ::payload & payload)
//{
//
//   return ::transfer(::string(sz) + payload);
//
//}
//
//
//inline ::file::path operator + (const ::file::path & path, const ::payload& payload)
//{
//
//   return path + payload.as_file_path();
//
//}


//inline ::file::path operator / (const ::file::path& path, const ::payload& payload)
//{
//
//   return path / payload.file_path();
//
//}


//inline ::file::path & operator += (::file::path& path, const ::payload& payload)
//{
//
//   return path += payload.file_path();
//
//}


//inline ::file::path & operator /= ( ::file::path& path, const ::payload& payload)
//{
//
//   return path /= payload.file_path();
//
//}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE >::string_base(const ::payload & payload) :
   string(payload.as_string())
{


}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator = (const ::payload & payload)
{

   assign_range(payload.as_string());

   return *this;

}


template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator += (const ::payload & payload)
{

   return append(payload);

}


template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append(const ::payload & payload)
{

   if (payload.m_etype == e_type_string)
   {

      return append(payload.m_str);

   }
   else
   {

      return append(payload.as_string());

   }

}


namespace file
{


   inline path::path(const ::payload & payload) :
      path(payload.as_file_path())
   {

   }


} // namespace file






//template < typename ITERATOR_TYPE >
//inline scoped_string_base < ITERATOR_TYPE >::scoped_string_base(const ::payload & payload) :
//   m_str(e_no_initialize), RANGE(e_no_initialize)
//{
//
//   m_str = payload.as_string();
//
//   RANGE::operator = (m_str);
//
//}


//template <  >
//inline scoped_string_base < const ::ansi_character * >::scoped_string_base(const ::payload & payload) :
//   m_str(e_no_initialize), RANGE(e_no_initialize)
//{
//
//   if (payload.has_string_reference())
//   {
//
//      BASE_RANGE::operator = (payload.string_reference());
//
//   }
//   else
//   {
//
//      m_str = payload.as_string();
//
//      BASE_RANGE::operator = (m_str);
//
//   }
//
//}



//template < character_range RANGE, primitive_payload PAYLOAD >
//::string operator + (const RANGE & range, const PAYLOAD & payload)
//{
//
//   string str(range);
//
//   str.append(payload.get_string());
//
//   return str;
//
//}


