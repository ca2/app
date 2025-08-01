#pragma once

class timeout :
   public time
{
public:

   timeout(const class ::time& dur) : time(dur) {}

};



inline ::payload operator + (::payload payload, const ::timeout& timeout)
{

   if (payload.get_type() != e_type_property_set)
   {

      payload["message"] = payload.get_string();

   }

   payload["timeout"] = (const class ::time&) timeout;

   return ::payload;

}


inline ::payload operator + (const ::scoped_string & scopedstr, const ::timeout& timeout)
{

   return ::payload(scopedstr) + timeout;

}



template < typename TYPE_CHAR >
inline ::payload operator + (const string_base < TYPE_CHAR >& str, const ::timeout& timeout)
{

   return ::payload(str) + timeout;

}



