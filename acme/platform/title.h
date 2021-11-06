#pragma once


class title :
   public string
{
public:

   title(const ::string & str) : string(str) {}

};



//inline ::payload operator + (::payload payload, const ::title& title)
//{
//
//   if (payload.get_type() != e_type_property_set)
//   {
//
//      payload["message"] = payload.get_string();
//
//   }
//
//   payload["title"] = (const ::string&) title;
//
//   return ::payload;
//
//}



//inline ::payload operator + (const char* psz, const ::title& title)
//{
//
//   return operator +((payload)psz, title);
//
//}

