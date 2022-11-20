#include "framework.h"
#include "type.h"
#include "acme/primitive/primitive/particle.h"
#include "acme/primitive/string/string.h"


type::type(const ::particle * pparticle)
{

   auto name = typeid(*(::particle *)pparticle).name();

   ::atom::operator = (demangle(name));

}



string cxxabi_demangle (const char* name);


#if defined(WINDOWS)



string demangle(const char* psz)
{

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

}


#else





char * g_pszDemangle = nullptr;
size_t g_sizeDemangle = 0;
critical_section * g_pcsDemangle = nullptr;


#include <cxxabi.h>


string demangle(const char* name)
{

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

   return ::move(str);

}


#endif


//
//type::type(const atom & atom, const ::atom & idFriendly)
//{
//
//   m_pfactoryitem = nullptr;
//   m_atom              = atom;
//   m_atomFriendly      = idFriendly;
//
//}
//
//
//type::type()
//{
//
//   m_pfactoryitem = nullptr;
//
//}
//
//type::~type()
//{
//
//}
//
//
//type::type(const type & info)
//{
//
//   m_atom              = info.m_atom;
//   m_atomFriendly      = info.m_atomFriendly;
//   m_pfactoryitem    = info.m_pfactoryitem;
//
//}
//
//
//type::type(const ::std::type_info & info)
//{
//
//   m_pfactoryitem = nullptr;
//#ifdef WINDOWS
//   m_atomFriendly      = info.name();
//   m_atom              = info.raw_name();
//#elif defined(ANDROID)
//   m_atomFriendly	   = info.name();
//   m_atom			      = info.name();
//#elif defined(__APPLE__)
//   m_atomFriendly      = info.name();
//   m_atom              = info.name();
//#else
//   m_atomFriendly      = info.name();
//   m_atom              = info.name();
//#endif
//
//}
//
//
//type::type(const ::string & strName, const ::string & strFriendlyName)
//{
//
//   m_pfactoryitem = nullptr;
//   m_atom              = strName;
//   m_atomFriendly      = strFriendlyName;
//
//}
//
//
//type & type::operator = (const type & info)
//{
//
//   m_atom              = info.m_atom;
//   m_atomFriendly      = info.m_atomFriendly;
//   m_pfactoryitem    = info.m_pfactoryitem;
//
//   return *this;
//
//}
//
//
//type & type::operator = (const ::std::type_info & info)
//{
//
//#ifdef WINDOWS
//   m_atomFriendly      = info.name();
//   m_atom              = info.raw_name();
//#elif defined(ANDROID)
//   m_atomFriendly      = info.name();
//   m_atom              = info.name();
//#elif defined(__APPLE__)
//   m_atomFriendly      = info.name();
//   m_atom              = info.name();
//#else
//   m_atomFriendly      = info.name();
//   m_atom              = info.name();
//#endif
////   m_pfactoryitem.release();
//
//   return *this;
//
//}
//
//
//bool type::operator == (const type & info) const
//{
//
//   return m_atom == info.m_atom;
//
//}
//
//
//bool type::operator == (const ::std::type_info & info) const
//{
//
//#ifdef WINDOWS
//
//   return m_atom == info.raw_name();
//
//#else
//
//   return m_atom == info.name();
//
//#endif // WINDOWS
//
//}
//
//
//bool type::operator == (const ::string & strName) const
//{
//
//   return m_atom == strName;
//
//}
//
//
//bool type::operator == (const atom & atom ) const
//{
//
//   return m_atom == atom ;
//
//}
//
//
//bool type::operator != (const type & info) const
//{
//
//   return m_atom != info.m_atom;
//
//}
//
//
//bool type::operator != (const ::std::type_info & info) const
//{
//
//#ifdef WINDOWS
//
//   return m_atom != info.raw_name();
//
//#else
//
//   return m_atom != info.name();
//
//#endif // WINDOWS
//
//}
//
//
//bool type::operator != (const ::string & strName) const
//{
//
//   return m_atom != strName;
//
//}
//
//
//bool type::operator != (const atom & atom ) const
//{
//
//   return m_atom != atom ;
//
//}
//
//
//const char * type::name() const
//{
//
//   return m_atom;
//
//}
//
//const char * type::friendly_name() const
//{
//
//   return m_atomFriendly;
//
//}
//
//
//ptra * type::new_ptra()
//{
//
//   return memory_new ptra();
//
//}
//
//
//CLASS_DECL_ACME bool operator == (const ::std::type_info & info1, const ::type info2)
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
//CLASS_DECL_ACME bool operator != (const ::std::type_info & info1, const ::type info2)
//{
//
//   return !operator == (info1, info2);
//
//}
//



//type& type::operator = (const ::std::type_info& typeinfo)
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


//type& type::operator = (const ::type& type)
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


bool type::operator == (const ::std::type_info& typeinfo) const
{

   ::string strName = ::type(typeinfo);

   strName = demangle(strName);

   return operator==(strName);

}


bool type::operator == (const ::type& type) const
{

   return ::atom::operator == (type);

}


bool type::operator == (const ::string& strType) const
{

   return ::atom::operator == (strType);

}


bool type::operator != (const ::std::type_info& typeinfo) const
{

   return !operator==(typeinfo);

}



//type& type::operator = (const ::type& type)
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


//const ::atom& type::name() const
//{ 
//   
//   return *this; 
//
//}


//bool type::operator == (const ::std::type_info& typeinfo) const
//{
//
//   ::string strName = ::type(typeinfo);
//
//   strName = demangle(strName);
//
//   return operator==(strName);
//
//}


//bool typea::operator == (const ::type& type) const
//{
//
//   return ::atom::operator == (type);
//
//}
//
//
//bool typea:: operator == (const ::string& strType) const
//{
//
//   return ::atom::operator == (strType);
//
//}


//bool type::operator == (const ::atom& atom) const
//{
//
//   return ::atom::operator==(atom);
//
//}
//
//
//bool type::operator != (const ::std::type_info& typeinfo) const
//{
//
//   return !operator==(typeinfo);
//
//}


bool type::operator != (const ::type& type) const
{

   return !operator==(type);

}


bool type::operator == (const ::particle* pparticle) const
{

   return operator ==(::type(pparticle));

}


bool type::operator != (const ::particle* pparticle) const
{

   return !operator==(pparticle);

}


