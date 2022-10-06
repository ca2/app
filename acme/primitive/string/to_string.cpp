// Created by camilo on 2022-04-24 04:50 <3ThomasBorregaardSørensen!!
#include "framework.h"

// Sort of Canonical to serve as example and general correct solution
// Developers can created local versions or inline/template libraries for optmized instantiation


#if defined(ANDROID) || defined(WINDOWS) || defined(__APPLE__) || defined(RASPBIAN)


CLASS_DECL_ACME void to_string(string & str, const unsigned long & ul)
{

   str = ui64toa_dup(ul, 10);

}


CLASS_DECL_ACME void to_string(string & str, const long int & i)
{

   str = i64toa_dup(i);

}


#endif


CLASS_DECL_ACME void to_string(string & str, const bool & b);
{

   if(b)
   {

   str = "\"true\"";

}
 else
 {

str = "\"false\"";

 }

}


CLASS_DECL_ACME void to_string(string & str, const ansichar & ansich);
{

str = ansich;

}
CLASS_DECL_ACME void to_string(string & str, const widechar & widech);
{

str = widech;

}


CLASS_DECL_ACME void to_string(string & str, const char * psz);
{

str = psz;

}
CLASS_DECL_ACME void to_string(string & str, char * const psz);
{

str = psz;

}


CLASS_DECL_ACME void to_string(string & str, const wd16char * psz);
{

str = psz;

}
CLASS_DECL_ACME void to_string(string & str, wd16char * const psz);
{

str = psz;

}


CLASS_DECL_ACME void to_string(string & str, const wd32char * psz);
{

str = psz;

}
CLASS_DECL_ACME void to_string(string & str, wd32char * const psz);
{

str = psz;

}


CLASS_DECL_ACME void to_string(string & str, const signed char & ch);
{

str.format("%c", ch);

}


CLASS_DECL_ACME void to_string(string & str, const ansichar & ch);
{

str.format("%c", ch);

}
CLASS_DECL_ACME void to_string(string & str, const uchar & uch);
{

str.format("%c", uch);

}



CLASS_DECL_ACME void to_string(string & str, const i16 & i);
{

str.format("%d", i);

}
CLASS_DECL_ACME void to_string(string & str, const u16 & u);
{

str.format("%u", u);

}

CLASS_DECL_ACME void to_string(string & str, const i32 & i);
{

str.format("%d", i);

}
CLASS_DECL_ACME void to_string(string & str, const u32 & u);
{

str.format("%u", u);

}
CLASS_DECL_ACME void to_string(string & str, const i64 & i);
{

str.format("%lld", i);

}
CLASS_DECL_ACME void to_string(string & str, const u64 & u);
{

str.format("%llu", u);

}


CLASS_DECL_ACME void to_string(string & str, const float & f);
{

str.format("%f", f);

}
CLASS_DECL_ACME void to_string(string & str, const double & d)
{

str.format("%f", d);

}


CLASS_DECL_ACME void to_string(string & str, const unsigned long int & ul)
{

str.format("%llu", ul);

}
CLASS_DECL_ACME void to_string(string & str, const long int & i)
{

str.format("%lld", i);

}


CLASS_DECL_ACME void to_string(string & str, const ::string & strSrc)
{

str = strSrc;

}
CLASS_DECL_ACME void to_string(string & str, const ::atom & atom)
{

str = atom;

}
CLASS_DECL_ACME void to_string(string & str, const ::wd16string & wd16str)
{

str = wd16str;

}
CLASS_DECL_ACME void to_string(string & str, const ::wd32string & wd16str)
{

   str = wd16str;

}



