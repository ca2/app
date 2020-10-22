#pragma once


class CLASS_DECL_ACME method :
   public function_base
{
public:


   method(const ::id& id = ::id()) : function_base(id) {}
   method(const ::method& method) : function_base((const ::function_base&) method) { }
   method(const ::function_base& function) : function_base(function) { }
   template < typename PRED >
   method(const ::id& id, PRED pred);
   template < typename PRED >
   method(PRED pred);


   ::estatus call() { return ::is_set(m_pobjectTask) ? m_pobjectTask->call() : (::estatus) ::success_none; }

   template < typename PRED >
   void pred(PRED pred);
   inline method& operator = (const ::method& function) { m_pobjectTask = function.m_pobjectTask;  return *this; }
   method& operator = (const ::var& var);

};


inline ::var operator + (::var var, const ::method& method)
{

   if (var.get_type() != type_propset)
   {

      var["message"] = var.get_string();

   }

   var["method"] = method;

   return var;

}


template < const ::i64 m_idObject >
class method_template :
   public method
{
public:


   method_template(::matter* p = nullptr) : ::method(m_idObject, p) {}
   method_template(const ::method& method) : ::method((const ::function_base&) method) { ASSERT(method.m_id == m_idObject); }
   method_template(const ::function_base& function) : ::method(function) { ASSERT(function.m_id == m_idObject); }
   template < typename PRED >
   method_template(PRED pred, ::matter* pobjectHold = nullptr) : ::method(pred, pobjectHold) { }


};


using create_method = method_template < CREATE_METHOD >;
using destroy_method = method_template < DESTROY_METHOD >;

//
//
//template < typename PRED >
//inline auto __method(PRED pred)
//{
//
//   return ::method(::id(), pred);
//
//}
//
//
//
//template < typename PRED >
//inline auto __method(PRED pred)
//{
//
//   return ::method(::id(), pred);
//
//}
