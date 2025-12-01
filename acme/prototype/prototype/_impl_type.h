//
// Created by camilo on 23/12/2022 02:48 <3ThomasBorregaardSorensen!!
// ::platform::type by camilo on 2025-11-29 <3ThomasBorregaardSørensen!!
//
#pragma once


//inline type_name::platform::type(const ::std::type_info & typeinfo) :
//   m_pszRawName(typeinfo.raw_name()){}
//inline bool type_name::operator == (const ::platform::type & type) const
//{   return m_pszRawName == type.m_pszRawName
//      || !strcmp(m_pszRawName, type.m_pszRawName)
//      || m_strDemangled == type.m_strDemangled; }
//inline bool type_name::operator == (const ::atom& atom) const
//{   return atom.as_string() == m_pszRawName ||
//      m_strDemangled == atom.as_string();}
//inline type_name::platform::type(const ::quantum * p)
//{   if(::is_null(p))   {
//      m_pszRawName = void;
//      m_strDemangled.empty();
//   }   else  {
//      this->operator=(typeid(*(::quantum*)p));  }}
//template < primitive_object_not_type_atom OBJECT_NOT_TYPE_ATOM >
//type_name::platform::type(OBJECT_NOT_TYPE_ATOM & objectnottypeatom)
//{  this->operator = (typeid(*(&(non_const < OBJECT_NOT_TYPE_ATOM > &)objectnottypeatom)));}
//template < typename BASE >
//inline type_name::platform::type(const ::pointer<BASE>& p)
//{  this->operator = (typeid(*((BASE*)p.m_p))); }
//template < typename TYPE >
//inline string __type_name()
//{   auto pszType = ::type<TYPE>().name();
//   string strName = demangle(scopedstrType);
//   return strName; }
//template < typename TYPE >
//inline string __type_name(const TYPE * p)
//{   auto pszType = typeid(*p).name();
//   string strName = demangle(scopedstrType);   return strName;}
//template < typename TYPE >
//inline string __type_name(const TYPE & t)
//{  auto pszType = ::type<t>().name();  string strName = demangle(scopedstrType);
//   return strName;}
//inline bool type_name::operator == (const ::quantum * p) const
//{ return operator ==(::platform::type(p));}
//template < typename TYPE >
//inline bool type_name::operator == (const ::pointer < TYPE > & p) const
//{ return this->operator==(p.m_p);}


namespace platform
{


   inline type::type(){}


   inline type::type(const ::platform::type &type) :
      m_typeid(type.m_typeid),
      m_customid(type.m_customid)
   {
   }


   inline type::type(const ::std::type_info &info) :
       m_typeid(info)
   {
   }


   inline type::type(const ::scoped_string &scopedstrTypeName) :
       m_customid(scopedstrTypeName)
   {
   }


   inline type::type(const ::type_iptr_pair &ipairId):
   m_customid(ipairId)
      {}
   

   
   inline type::type(const ::atom & atom) :
   m_customid(atom)
   {



   }
   

   template<typename TYPE>
   inline type::type(const TYPE *p) : type(typeid(*(TYPE *)p))
   {
   }
   template<typename TYPE>
   inline type::type(const TYPE &t) : type(typeid(t))
   {
   }
   template<typename BASE>
   inline type::type(const ::pointer<BASE> &p) : type(p.m_p)
   {
   }


   inline const ::string &type::raw_name() const { return m_typeid.m_strRawTypeName; }
   inline const ::string &type::name() const { return m_typeid.m_strTypeName; }
   inline const ::string &type::text() const { return m_typeid.m_strTypeName.has_character() ? m_typeid.m_strTypeName : m_customid.m_strNameId; }
   inline const char *type::c_str() const { return m_typeid.m_strTypeName.c_str(); }
   inline bool type::is_set() const
   {
      return m_typeid.is_set() || m_customid.is_set();
   }

   inline bool type::is_empty() const { return !is_set(); }
   inline type::operator bool() const { return is_set(); }
   // explicit operator pointer_key() const { return m_pszRawTypeName; }
   // explicit operator ::string() const { return m_strTypeName; }
   // bool boolean_test() const { return !is_empty(); }


   inline bool type::operator==(const ::platform::type &type) const
   {

      if (m_typeid.is_set() && type.m_typeid.is_set())
      {

         return m_typeid == type.m_typeid;

      }
      else if (m_customid.is_set() && type.m_customid.is_set())
      {

         return m_customid == type.m_customid;

      }

      return false;

   }


  inline ::std::strong_ordering type::operator<=>(const ::platform::type &type) const
   {

      if (m_typeid.is_set() && type.m_typeid.is_set())
      {

         return m_typeid <=> type.m_typeid;

      }
      else if (m_customid.is_set() && type.m_customid.is_set())
      {

         return m_customid <=> type.m_customid;

      }

      return ::order(this->is_set(), type.is_set());

   }


} // namespace platform




template<typename TYPE>
inline ::platform::type type()
{
   return typeid(TYPE);
}


inline ::platform::type type(const ::std::type_info &info) { return info; }


inline ::platform::type type(const ::scoped_string &scopedstrTypeName) { return scopedstrTypeName; }


template<typename TYPE>
inline ::platform::type type(const TYPE *p)
{
   return typeid(*(TYPE *)p);
}


template<typename TYPE>
inline ::platform::type type(const TYPE &t)
{
   return typeid(t);
}


template<typename BASE>
inline ::platform::type type(const ::pointer<BASE> &p)
{
   return p.m_p;
}





inline type_custom_id::type_custom_id()
{

}
inline type_custom_id::type_custom_id(const_char_pointer pszNameId):
m_strNameId(pszNameId)
{


}
inline type_custom_id::type_custom_id(const ::scoped_string & scopedstrNameId):
m_strNameId(scopedstrNameId)
{


}
inline type_custom_id::type_custom_id(const ::type_iptr_pair & ipairId) :
m_ipairId(ipairId)
{

}
inline type_custom_id::type_custom_id(const ::scoped_string & scopedstrNameId, const ::type_iptr_pair & ipairId):
m_strNameId(scopedstrNameId),
m_ipairId(ipairId)
{


}

inline type_custom_id::type_custom_id(enum_task_tool etasktool) :
m_ipairId(etasktool)
{


}


inline type_custom_id::type_custom_id(const ::atom & atom)
{

   if (atom.is_text())
   {
      m_strNameId = atom.as_string();
   }
   else if (atom.is_integer())
   {
      m_ipairId.m_element1 = (::iptr)atom.m_etype;
      m_ipairId.m_element2 = (::iptr)atom.m_iLargest;
   }


}


inline constexpr bool type_custom_id::is_set() const
{
   return m_strNameId.has_character() || m_ipairId.is_set();
}



type_id::type_id() :m_typeindex(::std::type_index(typeid(void)))

{


}

type_id::type_id(const ::type_id &type_id):
m_typeindex(type_id.m_typeindex),
m_strRawTypeName(type_id.m_strRawTypeName),
m_strTypeName(type_id.m_strTypeName)
{


}

type_id::type_id(const ::std::type_info &info) :
m_typeindex(info),
m_strRawTypeName(::type_raw_name(info)),
m_strTypeName(::type_name(info))
{


}





inline bool type_id::is_set() const
{

   return m_typeindex != ::std::type_index(typeid(void)) || m_strRawTypeName.has_character() ||
          m_strTypeName.has_character();

}


bool type_id::operator == (const ::type_id & type_id) const
{

   if (::is_type_index_set(m_typeindex) && ::is_type_index_set(type_id.m_typeindex))
   {

      return m_typeindex == type_id.m_typeindex;

   }
   else if (m_strRawTypeName.has_character() && type_id.m_strRawTypeName.has_character())
   {

      return m_strRawTypeName == type_id.m_strRawTypeName;

   }
   else if (m_strTypeName.has_character() && type_id.m_strTypeName.has_character())
   {

      return m_strTypeName == type_id.m_strTypeName;

   }

   return ::is_equivalent(this->is_set(), type_id.is_set());

}


::std::strong_ordering type_id::operator <=> (const ::type_id & type_id) const
{

   if (::is_type_index_set(m_typeindex) && ::is_type_index_set(type_id.m_typeindex))
   {

      return m_typeindex <=> type_id.m_typeindex;

   }
   else if (m_strRawTypeName.has_character() && type_id.m_strRawTypeName.has_character())
   {

      return m_strRawTypeName <=> type_id.m_strRawTypeName;

   }
   else if (m_strTypeName.has_character() && type_id.m_strTypeName.has_character())
   {

      return m_strTypeName <=> type_id.m_strTypeName;

   }

   return ::order(this->is_set(), type_id.is_set());

}


inline bool type_custom_id::operator == (const ::type_custom_id & typecustomid) const
{

   if (m_ipairId.is_set() && typecustomid.m_ipairId.is_set())
   {

      return m_ipairId == typecustomid.m_ipairId;

   }
   else if (m_strNameId.has_character() && typecustomid.m_strNameId.has_character())
   {

      return m_strNameId == typecustomid.m_strNameId;

   }

   return ::is_equivalent(this->is_set(), typecustomid.is_set());

}


inline ::std::strong_ordering type_custom_id::operator <=> (const ::type_custom_id & typecustomid) const
{

   if (m_ipairId.is_set() && typecustomid.m_ipairId.is_set())
   {

      return m_ipairId <=> typecustomid.m_ipairId;

   }
   else if (m_strNameId.has_character() && typecustomid.m_strNameId.has_character())
   {

      return m_strNameId <=> typecustomid.m_strNameId;

   }

   return ::order(this->is_set(), typecustomid.is_set());

}
