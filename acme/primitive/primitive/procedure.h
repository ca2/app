#pragma once


class CLASS_DECL_ACME procedure :
   public function_base
{
public:


   procedure(const ::id& id = ::id(), ::generic* p = nullptr) : function_base(id, p) {}
   procedure(const ::procedure& procedure) : function_base((const ::function_base&) procedure) { }
   procedure(const ::function_base& function) : function_base(function) { }
   template < typename PRED >
   procedure(const ::id& id, PRED pred, ::generic* pobjectHold = nullptr);
   template < typename PRED >
   procedure(PRED pred, ::generic* pobjectHold = nullptr);


   ::estatus call() { return ::is_set(m_pobjectTask) ? m_pobjectTask->call() : (::estatus) ::success_none; }

   template < typename PRED >
   void pred(PRED pred);
   inline procedure& operator = (const ::procedure& function) { m_pobjectTask = function.m_pobjectTask;  return *this; }
   procedure& operator = (const ::var& var);

};


inline ::var operator + (::var var, const ::procedure& procedure)
{

   if (var.get_type() != type_propset)
   {

      var["message"] = var.get_string();

   }

   var["procedure"] = procedure;

   return var;

}


template < const ::i64 m_idObject >
class procedure_template :
   public procedure
{
public:


   procedure_template(::generic* p = nullptr) : ::procedure(m_idObject, p) {}
   procedure_template(const ::procedure& procedure) : ::procedure((const ::function_base&) procedure) { ASSERT(procedure.m_id == m_idObject); }
   procedure_template(const ::function_base& function) : ::procedure(function) { ASSERT(function.m_id == m_idObject); }
   template < typename PRED >
   procedure_template(PRED pred, ::generic* pobjectHold = nullptr) : ::procedure(pred, pobjectHold) { }


};


using create_procedure = procedure_template < CREATE_PROCEDURE >;
using destroy_procedure = procedure_template < DESTROY_PROCEDURE >;



