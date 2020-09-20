#pragma once


class CLASS_DECL_ACME callback :
   public function_base
{
public:


   callback(const ::id & id = ::id(), ::generic* p = nullptr) : function_base(id, p) {}
   callback(const ::callback& callback) : function_base((const ::function_base &) callback) { }
   callback(const ::function_base& function) : function_base(function) { }
   template < typename PRED >
   callback(const ::id & id, PRED pred, ::generic * pobjectHold = nullptr) : function_base(id, __pred_callback < PRED >(pred, pobjectHold)) { }


   void receive_response(const var& var) const;


   template < typename PRED > void pred(PRED pred);
   inline callback& operator = (const ::callback& function) { m_pobjectTask = function.m_pobjectTask;  return *this; }
   callback& operator = (const ::var& var);

};



inline var operator + (var var, const ::callback& callback)
{

   if (var.get_type() != type_propset)
   {

      var["message"] = var.get_string();

   }

   var["callback"] = callback;

   return var;

}


template < const ::i64 m_idObject >
class callback_template :
   public callback
{
public:


   callback_template(::generic* p = nullptr) : ::callback(m_idObject, p) {}
   callback_template(const ::callback & callback) : ::callback((const ::function_base&) callback) { ASSERT(callback.m_id == m_idObject); }
   callback_template(const ::function_base& function) : ::callback(function) { ASSERT(function.m_id == m_idObject); }
   template < typename PRED >
   callback_template(PRED pred, ::generic* pobjectHold = nullptr) : ::callback(pred, pobjectHold) { }


};


using finish_callback = callback_template < FINISH_CALLBACK >;
using dialog_callback = callback_template < DIALOG_RESULT_CALLBACK >;
using complete_procedure = callback_template < COMPLETE_CALLBACK >;


