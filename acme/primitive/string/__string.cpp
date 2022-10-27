// Created by camilo on 2022-04-24 04:50 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "string.h"
#include "from_integer.h"
//#include "acme/primitive/primitive/particle.h"


// Sort of Canonical to serve as example and general correct solution
// Developers can created local versions or inline/template libraries for optmized instantiation


#if !defined(LINUX)

CLASS_DECL_ACME ::string __string(const unsigned long & ul)
{

   return ui64toa_dup(ul, 10);

}

CLASS_DECL_ACME::string __string(const long int & i)
{

   return i64toa_dup(i);

}

#endif


CLASS_DECL_ACME::string __string(const bool & b)
{

   if(b)
   {

   return "\"true\"";

}
 else
 {

return "\"false\"";

 }

}


CLASS_DECL_ACME::string __string(const ansichar & ansich)
{

   return ansich;

}


CLASS_DECL_ACME::string __string(const widechar & widech)
{

   return widech;

}


CLASS_DECL_ACME::string __string(const char * psz)
{

   return psz;

}


CLASS_DECL_ACME::string __string(char * const psz)
{

   return psz;

}


CLASS_DECL_ACME::string __string(const wd16char * psz)
{

   return psz;

}


CLASS_DECL_ACME::string __string(wd16char * const psz)
{

   return psz;

}


CLASS_DECL_ACME::string __string(const wd32char * psz)
{

   return psz;

}


CLASS_DECL_ACME::string __string(wd32char * const psz)
{

   return psz;

}


CLASS_DECL_ACME::string __string(const signed char & ch)
{

   return __string_format("%c", ch);

}



CLASS_DECL_ACME::string __string(const uchar & uch)
{

   return __string_format("%c", uch);

}


CLASS_DECL_ACME::string __string(const i16 & i)
{

   return i64toa_dup(i);

}


CLASS_DECL_ACME::string __string(const u16 & u)
{

   return ui64toa_dup(u);

}


CLASS_DECL_ACME::string __string(const i32 & i)
{

   return i64toa_dup(i);

}


CLASS_DECL_ACME::string __string(const u32 & u)
{

   return ui64toa_dup(u);

}


CLASS_DECL_ACME::string __string(const i64 & i)
{

   return i64toa_dup(i);

}


CLASS_DECL_ACME::string __string(const u64 & u)
{

   return ui64toa_dup(u, 10);

}



CLASS_DECL_ACME::string __string(const float & f)
{

   return __string_format("%f", f);

}


CLASS_DECL_ACME::string __string(const double & d)
{

   return __string_format("%f", d);

}



//CLASS_DECL_ACME::string __string(const ::string & strSrc)
//{
//
//   return strSrc;
//
//}


//CLASS_DECL_ACME ::string __string(const ::wd16string & wd16str)
//{
//
//   return wd16str;
//
//}

//
//CLASS_DECL_ACME::string __string(const ::wd32string & wd16str)
//{
//
//   return wd16str;
//
//}


//CLASS_DECL_ACME::string __string(const ::atom & atom)
//{
//
//   return atom.as_string();
//
//}


CLASS_DECL_ACME ::string __string(const particle & particle)
{

   ::string str;

   auto len = particle.sz_len();

   auto psz = str.get_string_buffer(len);

   particle.to_sz(psz, len);

   str.release_string_buffer();

   return ::move(str);

}



