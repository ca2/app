#pragma once




class user_parent
{
public:
   ::user::interaction_base* m_puserinteraction;
   user_parent(::user::interaction_base* pinteraction) :m_puserinteraction(pinteraction) {}
};

inline ::user_parent parent(::user::interaction_base* pinteraction) { return pinteraction; }


inline ::payload operator + (::payload payload, const ::function_arg& functionarg)
{

   if (payload.get_type() != e_type_property_set)
   {

      payload["message"] = payload.get_string();

   }

   payload["function_arg"] = functionarg;

   return ::payload;

}

inline ::payload operator + (::payload payload, const ::user_parent& parent)
{

   if (payload.get_type() != e_type_property_set)
   {

      payload["message"] = payload.get_string();

   }

   payload["parent"] = parent.m_puserinteraction;

   return ::payload;

}

