#pragma once




class user_parent
{
public:
   ::user::prototype* m_puserinteraction;
   user_parent(::user::prototype* pinteraction) :m_puserinteraction(pinteraction) {}
};

inline ::user_parent parent(::user::prototype* pinteraction) { return pinteraction; }


//inline ::payload operator + (::payload payload, const ::function_arg& functionarg)
//{
//
//   if (payload.get_type() != e_type_property_set)
//   {
//
//      payload["message"] = payload.get_string();
//
//   }
//
//   payload["function_arg"] = functionarg;
//
//   return ::payload;
//
//}

//inline ::payload operator + (::payload payload, const ::user_parent& parent)
//{
//
//   if (payload.get_type() != e_type_property_set)
//   {
//
//      payload["message"] = payload.get_string();
//
//   }
//
//   payload["parent"] = parent.m_puserinteraction;
//
//   return ::payload;
//
//}

