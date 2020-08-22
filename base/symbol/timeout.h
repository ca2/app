#pragma once

class timeout :
   public duration
{
public:

   timeout(const class ::duration& dur) : duration(dur) {}

};



inline var operator + (var var, const ::timeout& timeout)
{

   if (var.get_type() != type_propset)
   {

      var["message"] = var.get_string();

   }

   var["timeout"] = (const ::duration&) timeout;

   return var;

}


inline var operator + (const char* psz, const ::timeout& timeout)
{

   return var(psz) + timeout;

}



template < typename TYPE_CHAR >
inline var operator + (const string_base < TYPE_CHAR >& str, const ::timeout& timeout)
{

   return var(str) + timeout;

}



