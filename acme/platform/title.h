#pragma once


class title
{
public:

   ::string m_str;

   title(const ::scoped_string & scopedstr) : m_str(str) {}

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



//inline ::payload operator + (const ::scoped_string & scopedstr, const ::title& title)
//{
//
//   return operator +((payload)psz, title);
//
//}

