#pragma once




class user_parent
{
public:
   ::user::primitive* m_puserinteraction;
   user_parent(::user::primitive* pinteraction) :m_puserinteraction(pinteraction) {}
};

inline ::user_parent parent(::user::primitive* pinteraction) { return pinteraction; }


inline var operator + (var var, const ::function_arg& functionarg)
{

   if (var.get_type() != type_propset)
   {

      var["message"] = var.get_string();

   }

   var["function_arg"] = functionarg;

   return var;

}

inline var operator + (var var, const ::user_parent& parent)
{

   if (var.get_type() != type_propset)
   {

      var["message"] = var.get_string();

   }

   var["parent"] = parent.m_puserinteraction;

   return var;

}

