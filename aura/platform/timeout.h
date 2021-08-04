#pragma once

class timeout :
   public duration
{
public:

   timeout(const class ::duration& dur) : duration(dur) {}

};



inline ::payload operator + (::payload payload, const ::timeout& timeout)
{

   if (payload.get_type() != e_type_property_set)
   {

      payload["message"] = payload.get_string();

   }

   payload["timeout"] = (const ::duration&) timeout;

   return ::payload;

}


inline ::payload operator + (const ::string & psz, const ::timeout& timeout)
{

   return ::payload(psz) + timeout;

}



template < typename TYPE_CHAR >
inline ::payload operator + (const string_base < TYPE_CHAR >& str, const ::timeout& timeout)
{

   return ::payload(str) + timeout;

}



