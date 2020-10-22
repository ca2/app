#pragma once


class CLASS_DECL_ACME future :
   public function_base
{
public:


   future(const ::id & id = ::id(), ::matter* p = nullptr) : function_base(id, p) {}
   future(const ::future& future) : function_base((const ::function_base &) future) { }
   future(const ::function_base& function) : function_base(function) { }
   template < typename PRED >
   future(const ::id & id, PRED pred, ::matter * pobjectHold = nullptr) : function_base(id, __future < PRED >(pred, pobjectHold)) { }


   void send(const var& var) const;


   template < typename PRED > void pred(PRED pred);
   inline future& operator = (const ::future& future) { m_pobjectTask = future.m_pobjectTask;  return *this; }
   future& operator = (const ::var& var);

};



//template < typename PRED >
//inline auto __future(PRED pred)
//{
//
//   return ::future(::id(), pred);
//
//}


inline auto __async_future()
{

   return __future([](const ::var& var){ });

}





inline var operator + (var var, const ::future& future)
{

   if (var.get_type() != type_propset)
   {

      var["message"] = var.get_string();

   }

   var["future"] = future;

   return var;

}


template < const ::i64 m_idObject >
class future_template :
   public future
{
public:


   future_template(::matter* p = nullptr) : ::future(m_idObject, p) {}
   future_template(const ::future & future) : ::future((const ::function_base&) future) { ASSERT(future.m_id == m_idObject); }
   future_template(const ::function_base& function) : ::future(function) { ASSERT(function.m_id == m_idObject); }
   template < typename PRED >
   future_template(PRED pred, ::matter* pobjectHold = nullptr) : ::future(pred, pobjectHold) { }


};


using finish_future = future_template < FINISH_FUTURE >;
using dialog_future = future_template < DIALOG_RESULT_FUTURE >;
using complete_procedure = future_template < COMPLETE_FUTURE >;


