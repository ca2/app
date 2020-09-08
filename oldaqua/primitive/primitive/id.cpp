#include "framework.h"




//id::id(uptr ui)
//{
//   m_all ={};
//
//   operator = ((iptr)ui);
//}
//
#if defined(_LP64) || defined(_AMD64_)
//id::id(::i32 i)
//{
//   m_all = {};
//
//   operator = (i);
//}
//
//id::id(u32 ui)
//{
//   m_all ={};
//
//   operator = ((iptr)ui);
//}
#endif

//id::id(const string & str)
//{
//   m_all ={};
//
//   operator = (::aqua::system::id((const char *)str));
//}

//id::id(const string_interface & str)
//{
//   m_all ={};
//
//   operator = (::aqua::system::id(string(str)));
//}

id & id::operator = (const char * psz)
{
   operator = (::aqua::system::id(psz));
   return *this;
}

id & id::operator = (const string & str)
{
   operator = (::aqua::system::id(str));
   return *this;
}

//id & id::operator = (const string_interface & str)
//{
//   operator = (::aqua::system::id(string(str)));
//   return *this;
//}


