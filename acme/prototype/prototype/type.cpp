#include "framework.h"
#include "type.h"




string cxxabi_demangle (const_char_pointer name);


#if defined(WINDOWS)


//string demangle_typeid(const ::std::type_info& typeinfo)
//{
//
//   return demangle_name(typeinfo.name());
//
//}


string type_name(const ::std::type_info & typeinfo)
{

   auto psz = typeinfo.name();

   if (psz[0] == 'c' &&
      psz[1] == 'l' &&
      psz[2] == 'a' &&
      psz[3] == 's' &&
      psz[4] == 's' &&
      psz[5] == ' ')
   {

      return psz + 6;

   }
   else if (psz[0] == 's' &&
      psz[1] == 't' &&
      psz[2] == 'r' &&
      psz[3] == 'u' &&
      psz[4] == 'c' &&
      psz[5] == 't' &&
      psz[6] == ' ')
   {

      return psz + 7;

   }
   else
   {

      return psz;

   }

   return psz;

}


#else


//string demangle_typeid(const ::std::type_info& typeinfo)
//{
//
//   return demangle_name(typeinfo.name());
//
//}


char * g_pszDemangle = nullptr;
size_t g_sizeDemangle = 0;
critical_section * g_pcsDemangle = nullptr;


#include <cxxabi.h>


string type_name(const ::std::type_info& typeinfo)
{

   auto name = typeinfo.name();

   int status = -4;

   char* res = abi::__cxa_demangle(name, 0, 0, &status);

   string str;

   if (status == 0)
   {

      str = res;

   }
   else
   {

      str = name;

   }

   if (res != nullptr)
   {

      free(res);

   }

   return ::transfer(str);

}


#endif


//
//type_name::platform::type(const atom & atom, const ::atom & idFriendly)
//{
//
//   m_pfactoryitem = nullptr;
//   id()              = atom;
//   m_atomFriendly      = idFriendly;
//
//}
//
//
//type_name::platform::type()
//{
//
//   m_pfactoryitem = nullptr;
//
//}
//
//type_name::~type_name()
//{
//
//}
//
//
//type_name::platform::type(const type_name & info)
//{
//
//   id()              = info.id();
//   m_atomFriendly      = info.m_atomFriendly;
//   m_pfactoryitem    = info.m_pfactoryitem;
//
//}
//
//
//type_name::platform::type(const ::std::type_info & info)
//{
//
//   m_pfactoryitem = nullptr;
//#ifdef WINDOWS
//   m_atomFriendly      = info.name();
//   id()              = info.raw_name();
//#elif defined(__ANDROID__)
//   m_atomFriendly	   = info.name();
//   id()			      = info.name();
//#elif defined(__APPLE__)
//   m_atomFriendly      = info.name();
//   id()              = info.name();
//#else
//   m_atomFriendly      = info.name();
//   id()              = info.name();
//#endif
//
//}
//
//
//type_name::platform::type(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrFriendlyName)
//{
//
//   m_pfactoryitem = nullptr;
//   id()              = strName;
//   m_atomFriendly      = strFriendlyName;
//
//}
//
//
//type_name & type_name::operator = (const type_name & info)
//{
//
//   id()              = info.id();
//   m_atomFriendly      = info.m_atomFriendly;
//   m_pfactoryitem    = info.m_pfactoryitem;
//
//   return *this;
//
//}
//
//
//type_name & type_name::operator = (const ::std::type_info & info)
//{
//
//#ifdef WINDOWS
//   m_atomFriendly      = info.name();
//   id()              = info.raw_name();
//#elif defined(__ANDROID__)
//   m_atomFriendly      = info.name();
//   id()              = info.name();
//#elif defined(__APPLE__)
//   m_atomFriendly      = info.name();
//   id()              = info.name();
//#else
//   m_atomFriendly      = info.name();
//   id()              = info.name();
//#endif
////   m_pfactoryitem.release();
//
//   return *this;
//
//}
//
//
//bool type_name::operator == (const type_name & info) const
//{
//
//   return id() == info.id();
//
//}
//
//
//bool type_name::operator == (const ::std::type_info & info) const
//{
//
//#ifdef WINDOWS
//
//   return id() == info.raw_name();
//
//#else
//
//   return id() == info.name();
//
//#endif // WINDOWS
//
//}
//
//
//bool type_name::operator == (const ::scoped_string & scopedstrName) const
//{
//
//   return id() == strName;
//
//}
//
//
//bool type_name::operator == (const atom & atom ) const
//{
//
//   return id() == atom ;
//
//}
//
//
//bool type_name::operator != (const type_name & info) const
//{
//
//   return id() != info.id();
//
//}
//
//
//bool type_name::operator != (const ::std::type_info & info) const
//{
//
//#ifdef WINDOWS
//
//   return id() != info.raw_name();
//
//#else
//
//   return id() != info.name();
//
//#endif // WINDOWS
//
//}
//
//
//bool type_name::operator != (const ::scoped_string & scopedstrName) const
//{
//
//   return id() != strName;
//
//}
//
//
//bool type_name::operator != (const atom & atom ) const
//{
//
//   return id() != atom ;
//
//}
//
//
//const_char_pointer type_name::name() const
//{
//
//   return id();
//
//}
//
//const_char_pointer type_name::friendly_name() const
//{
//
//   return m_atomFriendly;
//
//}
//
//
//ptra * type_name::new_ptra()
//{
//
//   return ___new ptra();
//
//}
//
//
//CLASS_DECL_ACME bool operator == (const ::std::type_info & info1, const ::platform::type info2)
//{
//
//#ifdef WINDOWS
//
//   return strcmp(info1.raw_name(), info2->name()) == 0;
//
//#else
//
//   return strcmp(info1.name(), info2->name()) == 0;
//
//#endif
//
//}
//
//CLASS_DECL_ACME bool operator != (const ::std::type_info & info1, const ::platform::type info2)
//{
//
//   return !operator == (info1, info2);
//
//}
//



//type_name& type_name::operator = (const ::std::type_info& typeinfo)
//{
//
//   ::string strName = typeinfo.name();
//
//   strName = demangle(strName);
//
//   ::atom::operator =(strName);
//
//   return *this;
//
//}


//type_name& type_name::operator = (const ::platform::type & type)
//{
//
//   if (this != &type)
//   {
//
//      ::atom::operator =(type);
//
//   }
//
//   return *this;
//
//}
//
//
//bool type_name::operator == (const ::std::type_info& typeinfo) const
//{
//
//   ::string strName = typeinfo.name();
//
//   strName = demangle(strName);
//
//   return operator==(strName);
//
//}
//
//
//bool type_name::operator == (const ::platform::type & type) const
//{
//
//   return ::atom::operator == (type);
//
//}
//
//
//bool type_name::operator == (const ::scoped_string & scopedstrType) const
//{
//
//   return ::atom::operator == (strType);
//
//}


//bool type_name::operator != (const ::std::type_info& typeinfo) const
//{
//
//   return !operator==(typeinfo);
//
//}


//type_name& type_name::operator = (const ::platform::type & type)
//{
//
//   if (this != &type)
//   {
//
//      ::atom::operator =(type);
//
//   }
//
//   return *this;
//
//}


//const ::atom& type_name::name() const
//{ 
//   
//   return *this; 
//
//}


//bool type_name::operator == (const ::std::type_info& typeinfo) const
//{
//
//   ::string strName = ::platform::type(typeinfo);
//
//   strName = demangle(strName);
//
//   return operator==(strName);
//
//}


//bool type_name::operator == (const ::platform::type & type) const
//{
//
//   return ::atom::operator == (type);
//
//}
//
//
//bool typea:: operator == (const ::scoped_string & scopedstrType) const
//{
//
//   return ::atom::operator == (strType);
//
//}


//bool type_name::operator == (const ::atom& atom) const
//{
//
//   return ::atom::operator==(atom);
//
//}
//
//
//bool type_name::operator != (const ::std::type_info& typeinfo) const
//{
//
//   return !operator==(typeinfo);
//
//}


//bool type_name::operator != (const ::platform::type & type) const
//{
//
//   return !operator==(type);
//
//}


//bool type_name::operator == (const ::particle* pparticle) const
//{
//
//   return operator ==(::platform::type(pparticle));
//
//}


//bool type_name::operator != (const ::particle* pparticle) const
//{
//
//   return !operator==(pparticle);
//
//}




namespace platform
{



   ::string type::as_string() const
   {

      ::string str;

      if (m_typeid.is_set())
      {

         str = "typeid={" + m_typeid.as_string() +"};";

      }

      if (m_customid.is_set())
      {

         str = "customid={" + m_customid.as_string() +"};";

      }

      return str;

   }

} // namespace platform

::string type_id::as_string() const
{

   ::string str;

   if (::is_type_index_set(m_typeindex))
   {

      str += "typeindex.name=" + ::string(m_typeindex.name())+";";

   }

   if (m_strTypeName.has_character())
   {

      str+="typename="+m_strTypeName+";";

   }

   return str;

}



::string type_custom_id::as_string() const
{

   ::string str;

   if (m_ipairId.is_set())
   {

      str+= "ipair=" + m_ipairId.as_string()+ ";";

   }

   if (m_strNameId.has_character())
   {

      str += "name=" + m_strNameId + ";";

   }

   return str;


}

const char * as_const_char_pointer(::enum_task_tool etasktool)
{

switch (etasktool)
{
   case e_task_tool_draw2d:
      return "e_task_tool_draw2d";
   default:
      return nullptr;
}

}

::string type_iptr_pair::as_string() const
{
   ::string str;

   auto i1=normal1();
   auto i2 = normal2();
   if (i1 >= 0)
   {
      str += "i1="+::as_string(i1)+ ";";
      if (i2 >= 0)
      {

         str += "i2="+::as_string(i2)+ ";";

      }
   }
   if (i1 >= 0 && i2 >= 0)
   {

      const char * psz = nullptr;

      if (i1 == ::atom::e_type_task_tool && (psz =as_const_char_pointer((::enum_task_tool)i2)))
      {

         str+="maybe e_type_task_tool?=" + ::string(psz);

      }

   }

   return str;

}
