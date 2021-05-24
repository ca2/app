#include "framework.h"



//
//id::id(uptr u)
//{
//   m_all ={};
//
//   operator = ((iptr)u);
//}
//
//#if defined(_LP64) || defined(_AMD64_)
//id::id(::i32 i)
//{
//   m_all = {};
//
//   operator = (i);
//}
//
//id::id(u32 u)
//{
//   m_all ={};
//
//   operator = ((iptr)u);
//}
//#endif

//id::id(const string & str)
//{
//   m_all ={};
//
//   operator = (::acme::id((const char *)str));
//}

//
//id::id(const char* psz)
//{
//   m_all = {};
//
//   operator = (::acme::id(psz));
//
//}

//id::id(const string_interface & str)
//{
//   m_all ={};
//
//   operator = (::acme::id(string(str)));
//}

id & id::operator = (const char * psz)
{
   operator = (::acme::id(psz));
   return *this;
}

id & id::operator = (const string & str)
{
   operator = (::acme::id(str));
   return *this;
}

//id & id::operator = (const string_interface & str)
//{
//   operator = (::acme::system::id(string(str)));
//   return *this;
//}



//
//CLASS_DECL_ACME::id id(const char* psz)
//{
//
//
//
//}